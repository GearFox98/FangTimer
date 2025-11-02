QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    clock.cpp \
    comment.cpp \
    main.cpp \
    fangwindow.cpp \
    statsdialog.cpp \
    tprogressarcstatic.cpp

HEADERS += \
    clock.h \
    comment.h \
    fangwindow.h \
    statsdialog.h \
    tprogressarcstatic.h

FORMS += \
    comment.ui \
    fangwindow.ui \
    statsdialog.ui

TRANSLATIONS += \
    FangTimer_es_419.ts \
    FangTimer_es_ES.ts \
    FangTimer_es_MX.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
