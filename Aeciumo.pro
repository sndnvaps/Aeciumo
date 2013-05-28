#-------------------------------------------------
#
# Project created by QtCreator 2013-05-03T19:06:14
#
#-------------------------------------------------

QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Aeciumo
TEMPLATE = app


SOURCES += \
    main.cpp \
    aeciumo.cpp \
    connectInternet.cpp

HEADERS  += \
    qssReader.h \
    aeciumo.h \
    networkState.h \
    connectInternet.h

OTHER_FILES += \
    Qss/styleSheet_lineEdit_password.qss \
    Qss/styleSheet_label_title.qss \
    Qss/styleSheet_comboBox_id.qss \
    Qss/styleSheet_checkBox.qss \
    Qss/styleSheet_button_settings.qss \
    Qss/styleSheet_button_minimum.qss \
    Qss/styleSheet_button_close.qss \
    Qss/styleSheet_black_button.qss

RESOURCES += \
    aeciumo.qrc

FORMS +=
