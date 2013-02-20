#include "videoobj.h"

videoObj::videoObj(QObject *parent) :
    QObject(parent)
{
}

void videoObj::ProcessFrame(){
    bool getframe;
    //QImage qimgOriginal;
    qDebug()<<"get in ProcessFrame";
    while(!stop_){
        getframe = capture_.read(imgOriginal_);
        if(!getframe){
            qDebug()<<"Video End!";
            break;
        }
        cv::cvtColor(imgOriginal_, imgOriginal_, CV_BGR2RGB);
        QImage qimgOriginal((uchar*)imgOriginal_.data, imgOriginal_.cols, imgOriginal_.rows, imgOriginal_.step, QImage::Format_RGB888);

        emit imgProcessed(qimgOriginal);
        this->thread()->msleep(10);
        //qDebug()<<"processing frames";
    }

    //emit stopProcess();
    QThread::currentThread()->quit();
    qDebug()<<"Stop thread";
}

void videoObj::onStopProcess(){
    qDebug()<<"the thread is finished!";
}
