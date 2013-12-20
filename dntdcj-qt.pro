#-------------------------------------------------
#
# Project created by QtCreator 2013-11-14T15:08:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dntdcj
TEMPLATE = app

CONFIG += qwt

INCLUDEPATH += ../dntdiag-qt/native\
               ../dntdiag-qt/ \

win32 {
INCLUDEPATH += $$(BOOST_INCLUDE)
}

LIBS += -ldntdiag

SOURCES += \
    TroubleCodeWidget.cpp \
    TroubleCodePresenter.cpp \
    TroubleCodeModel.cpp \
    PlotWidget.cpp \
    PlotTimeScaleDraw.cpp \
    PlotCurve.cpp \
    PlotBackground.cpp \
    MikuniWidget.cpp \
    MikuniPresenter.cpp \
    MenuWidget.cpp \
    MenuPresenter.cpp \
    MenuItem.cpp \
    MainWindow.cpp \
    MainMenuPresenter.cpp \
    main.cpp \
    LiveDataWidget.cpp \
    LiveDataDelegate.cpp \
    HJ125T_16CPresenter.cpp \
    HJ125T_16APresenter.cpp \
    HJ125T_10Presenter.cpp \
    GW250Widget.cpp \
    GW250Presenter.cpp \
    ECUPresenter.cpp \
    App.cpp \
    LiveDataModel.cpp

HEADERS  += \
    TroubleCodeWidget.h \
    TroubleCodePresenter.h \
    TroubleCodeModel.h \
    PlotWidget.h \
    PlotTimeScaleDraw.h \
    PlotCurve.h \
    PlotBackground.h \
    MikuniWidget.h \
    MikuniPresenter.h \
    MenuWidget.h \
    MenuPresenter.h \
    MenuItem.h \
    MainWindow.h \
    MainMenuPresenter.h \
    LiveDataWidget.h \
    LiveDataDelegate.h \
    HJ125T_16CPresenter.h \
    HJ125T_16APresenter.h \
    HJ125T_10Presenter.h \
    GW250Widget.h \
    GW250Presenter.h \
    ECUPresenter.h \
    App.h \
    LiveDataModel.h

FORMS    += \
    TroubleCodeWidget.ui \
    MikuniWidget.ui \
    MenuWidget.ui \
    LiveDataWidget.ui \
    GW250Widget.ui

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    README.md
