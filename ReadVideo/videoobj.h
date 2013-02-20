#ifndef VIDEOOBJ_H
#define VIDEOOBJ_H

#include <QObject>
#include <QThread>
#include <QImage>
#include <QDebug>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class videoObj : public QObject
{
    Q_OBJECT
public:
    explicit videoObj(QObject *parent = 0);

    cv::VideoCapture capture_;
    //accessor and mutator
    //inline const cv::VideoCapture& getCap() const {return capture_;}
    //inline void setCap(const cv::VideoCapture& cap){capture_ = cap;}
    inline const cv::Mat& getImgOriginal() const {return imgOriginal_;}
    inline void setImgOriginal(const cv::Mat& img){imgOriginal_ = img;}
    inline const bool& isVideoStop() const {return stop_;}
    inline void setVideoStop(const bool& stop) {stop_ = stop;}


signals:
    void imgProcessed(QImage);
    //void stopProcess();
    
public slots:
    void ProcessFrame();
    void onStopProcess();

private:
    cv::Mat imgOriginal_;
    bool stop_;
    
};

#endif // VIDEOOBJ_H
