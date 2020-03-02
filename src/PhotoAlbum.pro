TEMPLATE = app
CONFIG += c++17

QT += core network quick

RESOURCES += qml.qrc

SOURCES += \
        core/abstractdatafetcher.cpp \
        core/datasource.cpp \
        core/entitydatabank.cpp \
        core/jsonalbumsparser.cpp \
        core/jsonphotosparser.cpp \
        core/jsonuserparser.cpp \
        core/networkfetcher.cpp \
        core/networkfetcherprivate.cpp \
        data/album.cpp \
        data/entity.cpp \
        data/entitydatamodel.cpp \
        data/entitydatapool.cpp \
        data/photo.cpp \
        data/user.cpp \
        main.cpp \
        photoalbummanager.cpp

HEADERS += \
    core/abstractdatafetcher.h \
    core/datasource.h \
    core/entitydatabank.h \
    core/jsonalbumsparser.h \
    core/jsonphotosparser.h \
    core/jsonuserparser.h \
    core/networkfetcher.h \
    core/networkfetcherprivate.h \
    data/album.h \
    data/entity.h \
    data/entitydatamodel.h \
    data/entitydatapool.h \
    data/photo.h \
    data/user.h \
    photoalbummanager.h

QML_IMPORT_PATH = ./
