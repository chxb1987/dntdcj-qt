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

INCLUDEPATH += ../dntdiag/native\
               ../dntdiag/qt \

win32 {
INCLUDEPATH += $$(BOOST_INCLUDE)
}

LIBS += -ldntdiag

SOURCES += \
    qt/main.cpp \
    qt/MainWindow.cpp \
    qt/MenuItem.cpp \
    qt/MenuWidget.cpp \
    qt/App.cpp \
    qt/MenuPresenter.cpp \
    qt/ECUPresenter.cpp \
    qt/TroubleCodeModel.cpp \
    qt/TroubleCodeWidget.cpp \
    qt/TroubleCodePresenter.cpp \
    qt/LiveDataDelegate.cpp \
    qt/LiveDataModel.cpp \
    qt/LiveDataWidget.cpp \
    qt/GW250Widget.cpp \
    qt/GW250Presenter.cpp \
    qt/MikuniWidget.cpp \
    qt/MikuniPresenter.cpp \
    qt/PlotBackground.cpp \
    qt/PlotCurve.cpp \
    qt/PlotTimeScaleDraw.cpp \
    qt/PlotWidget.cpp \
    qt/HJ125T_16CPresenter.cpp \
    qt/HJ125T_16APresenter.cpp \
    qt/HJ125T_10Presenter.cpp \
    qt/MainMenuPresenter.cpp

HEADERS  += \
    qt/MainWindow.h \
    qt/MenuPresenter.h \
    qt/MenuItem.h \
    qt/MenuWidget.h \
    qt/App.h \
    qt/ECUPresenter.h \
    qt/TroubleCodeModel.h \
    qt/TroubleCodeWidget.h \
    qt/TroubleCodePresenter.h \
    qt/LiveDataDelegate.h \
    qt/LiveDataModel.h \
    qt/LiveDataWidget.h \
    qt/GW250Widget.h \
    qt/GW250Presenter.h \
    qt/MikuniWidget.h \
    qt/MikuniPresenter.h \
    qt/PlotBackground.h \
    qt/PlotCurve.h \
    qt/PlotTimeScaleDraw.h \
    qt/PlotWidget.h \
    qt/HJ125T_16CPresenter.h \
    qt/HJ125T_16APresenter.h \
    qt/HJ125T_10Presenter.h \
    qt/MainMenuPresenter.h

FORMS    += \
    qt/MenuWidget.ui \
    qt/TroubleCodeWidget.ui \
    qt/LiveDataWidget.ui \
    qt/MikuniWidget.ui \
    qt/GW250Widget.ui

RESOURCES += \
    qt/resources.qrc

OTHER_FILES += \
    README.md
