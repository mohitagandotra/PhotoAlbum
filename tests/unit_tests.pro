GOOGLETEST_DIR = $$PWD/../../googletest
include($$PWD/gmock_dependency.pri)


CONFIG += console c++17
CONFIG -= app_bundle
TEMPLATE = app

QT += quick network


INCLUDEPATH += ../src

SOURCES += \
        ../src/core/abstractdatafetcher.cpp \
        ../src/core/datasource.cpp \
        ../src/core/entitydatabank.cpp \
        ../src/core/jsonalbumsparser.cpp \
        ../src/core/jsonphotosparser.cpp \
        ../src/core/jsonuserparser.cpp \
        ../src/core/networkfetcher.cpp \
        ../src/core/networkfetcherprivate.cpp \
        ../src/data/album.cpp \
        ../src/data/entity.cpp \
        ../src/data/entitydatamodel.cpp \
        ../src/data/entitydatapool.cpp \
        ../src/data/photo.cpp \
        ../src/data/user.cpp \
        main.cpp \
        test_entities.cpp

HEADERS += \
    ../src/core/abstractdatafetcher.h \
    ../src/core/datasource.h \
    ../src/core/entitydatabank.h \
    ../src/core/jsonalbumsparser.h \
    ../src/core/jsonphotosparser.h \
    ../src/core/jsonuserparser.h \
    ../src/core/networkfetcher.h \
    ../src/core/networkfetcherprivate.h \
    ../src/data/album.h \
    ../src/data/entity.h \
    ../src/data/entitydatamodel.h \
    ../src/data/entitydatapool.h \
    ../src/data/photo.h \
    ../src/data/user.h

