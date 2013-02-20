#ifndef READVIDEO_H
#define READVIDEO_H

#include <QImage>
#include <QThread>
#include <QtCore>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class readVideo : public QThread
{
    Q_OBJECT
public:
    explicit readVideo(QObject *parent = 0); //default constructor
    explicit readVideo(QObject *parent , cv::VideoCapture *cap);
    void init();
    void run();
    void ProcessFrame();

    /*parameters*/
    bool stop;
    cv::VideoCapture *capture;

signals:
    void imgProcessed(QImage);
    void stopProcess();

public slots:   
    
};

#endif // READVIDEO_H
