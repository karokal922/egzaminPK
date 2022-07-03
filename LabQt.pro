QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    exam.cpp \
    main.cpp \
    mainwindow.cpp \
    questions.cpp \
    student_list.cpp \
    studentlistwindow.cpp \
    summarywindow.cpp \
    tests.cpp

HEADERS += \
    exam.h \
    mainwindow.h \
    questions.hpp \
    student_list.hpp \
    studentlistwindow.h \
    summarywindow.h \
    tests.h \
    utils.hpp

FORMS += \
    mainwindow.ui \
    studentlistwindow.ui \
    summarywindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RC_ICONS=ikona.ico

RESOURCES += \
    exam_data.qrc
