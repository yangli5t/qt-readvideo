#include "readvideo.h"
#include <QDebug>


readVideo::readVideo(QObject *parent) :
    QThread(parent)
{
    init();
    qDebug()<<"Default constructor";
}

readVideo::readVideo(QObject *parent, cv::VideoCapture *cap):QThread(parent),capture(cap)
{
    init();
    qDebug()<<"Constructor";
}

void readVideo::init(){
    stop = 0;
}

void readVideo::run(){
    ProcessFrame();
}

void readVideo::ProcessFrame(){
    cv::Mat imgOriginal;
    bool getframe;
    //QImage qimgOriginal;

    while(!stop){
        getframe = capture->read(imgOriginal);
        if(!getframe){
            qDebug()<<"Video End!";
            break;
        }
        cv::cvtColor(imgOriginal, imgOriginal, CV_BGR2RGB);
        QImage qimgOriginal((uchar*)imgOriginal.data, imgOriginal.cols, imgOriginal.rows, imgOriginal.step, QImage::Format_RGB888);

        emit imgProcessed(qimgOriginal);
        qDebug()<<"processing frames";
    }
    emit stopProcess();
    qDebug()<<"Stop thread";
}
