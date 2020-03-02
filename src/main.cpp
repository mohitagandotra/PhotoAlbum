#include <iostream>
#include "data/entity.h"
#include "core/datasource.h"
#include "data/entitydatamodel.h"
#include "photoalbummanager.h"

#include <QGuiApplication>
#include <QDebug>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSortFilterProxyModel>

using namespace std;
using namespace SUCore;
using namespace SUData;

int main(int argc, char **argv)
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    qmlRegisterUncreatableType<EntityDataBank_C>("sumup.com", 1, 0, "EntityDataBank", "Not creatable as it is an enum type");
    qRegisterMetaType<DataSource_I*>("DataSource_I*");
    qRegisterMetaType<Entity_C*>("Entity_C*");
    qRegisterMetaType<EntityDataModel_C*>("EntityDataModel_C*");
    qRegisterMetaType<QSortFilterProxyModel*>("QSortFilterProxyModel*");

    QGuiApplication app(argc, argv);
    PhotoAlbumManager_C manager;

    QQmlApplicationEngine engine;

    // Prevent JS garbage collector to delete model objects.
    QObject::connect(&manager, &PhotoAlbumManager_C::dataReady, &manager, [&engine, &manager]() {
       manager.entityDataBank()->preserveObjectOwnership(&engine);
    });

    QQmlContext* rootContext = engine.rootContext();

    rootContext->setContextProperty("Manager", &manager);
    rootContext->setContextProperty("DataBank", manager.entityDataBank());

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
