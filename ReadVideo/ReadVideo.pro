#-------------------------------------------------
#
# Project created by QtCreator 2012-12-18T00:30:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ReadVideo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    videoobj.cpp

HEADERS  += mainwindow.h \
    videoobj.h

FORMS    += mainwindow.ui

win32{
INCLUDEPATH += C:\\opencv2.4.3\\include

LIBS += -LC:\\opencv2.4.3_compiled\\myBuild\\lib\\Debug \
    -lopencv_calib3d243d \
    -lopencv_contrib243d \
    -lopencv_core243d \
    -lopencv_features2d243d \
    -lopencv_flann243d \
    -lopencv_gpu243d \
    -lopencv_haartraining_engined \
    -lopencv_highgui243d \
    -lopencv_imgproc243d \
    -lopencv_legacy243d \
    -lopencv_ml243d \
    -lopencv_nonfree243d \
    -lopencv_objdetect243d \
    -lopencv_photo243d \
    -lopencv_stitching243d \
    -lopencv_ts243d \
    -lopencv_video243d \
    -lopencv_videostab243d
}
unix{
INCLUDEPATH += /usr/local/include

LIBS += -L /usr/local/lib \
        /usr/local/lib/libopencv_calib3d.so \
        /usr/local/lib/libopencv_core.so \
        /usr/local/lib/libopencv_contrib.so \
        /usr/local/lib/libopencv_features2d.so \
        /usr/local/lib/libopencv_flann.so \
        /usr/local/lib/libopencv_gpu.so \
        /usr/local/lib/libopencv_highgui.so \
        /usr/local/lib/libopencv_imgproc.so \
        /usr/local/lib/libopencv_legacy.so
}
