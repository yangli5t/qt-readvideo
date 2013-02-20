#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore>
#include <QtGui>
#include <QDebug>
#include <QThread>
#include <QMessageBox>
#include <QString>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    video_obj_ = new videoObj();
    video_thread_ = new QThread;
    this->connect(video_obj_, SIGNAL(imgProcessed(QImage)), SLOT(onImgProcssed(QImage)));
    video_obj_->connect(video_thread_, SIGNAL(started()), SLOT(ProcessFrame()));
    video_obj_->moveToThread(video_thread_);
    //video_thread_->connect(video_obj_, SIGNAL(stopProcess()), SLOT(quit()));
    //video_thread_->connect(video_thread_, SIGNAL(finished()), SLOT(deleteLater()));
    //this->connect(video_obj_, SIGNAL(stopProcess()), SLOT(onStopProcess()));
    video_obj_->connect(video_thread_, SIGNAL(finished()), SLOT(onStopProcess()));
}

MainWindow::~MainWindow()
{
    stopVideoProcessing();
    video_obj_->deleteLater();
    video_thread_->deleteLater();
    delete ui;
}

void MainWindow::stopVideoProcessing(){
    video_obj_->setVideoStop(1);
    this->thread()->currentThread()->msleep(10);
}

void MainWindow::on_btnStart_clicked()
{
    stopVideoProcessing();
    video_obj_->capture_.release();
    video_obj_->capture_.open(ui->lineEditVidoeAddress->text().toStdString());
    if(!video_obj_->capture_.isOpened()){
        qDebug()<<"open video failed";
        //should have warn message here
        QMessageBox::warning(this, "Warning", "Failed to load video!", QMessageBox::Ok);
    }
    qDebug()<<"**************Video Info*************";
    qDebug()<<"CV_CAP_PROP_POS_MSEC "<<video_obj_->capture_.get(CV_CAP_PROP_POS_MSEC);
    qDebug()<<"CV_CAP_PROP_POS_FRAMES "<<video_obj_->capture_.get(CV_CAP_PROP_POS_FRAMES );
    qDebug()<<"CV_CAP_PROP_POS_AVI_RATIO "<<video_obj_->capture_.get(CV_CAP_PROP_POS_AVI_RATIO);
    qDebug()<<"CV_CAP_PROP_FRAME_WIDTH "<<video_obj_->capture_.get(CV_CAP_PROP_FRAME_WIDTH );
    qDebug()<<"CV_CAP_PROP_FRAME_HEIGHT "<<video_obj_->capture_.get(CV_CAP_PROP_FRAME_HEIGHT);
    qDebug()<<"CV_CAP_PROP_FPS "<<video_obj_->capture_.get(CV_CAP_PROP_FPS);
    qDebug()<<"CV_CAP_PROP_FOURCC "<<video_obj_->capture_.get(CV_CAP_PROP_FOURCC);
    qDebug()<<"CV_CAP_PROP_FRAME_COUNT "<<video_obj_->capture_.get(CV_CAP_PROP_FRAME_COUNT);
    qDebug()<<"CV_CAP_PROP_FORMAT "<<video_obj_->capture_.get(CV_CAP_PROP_FORMAT);
    qDebug()<<"CV_CAP_PROP_MODE "<<video_obj_->capture_.get(CV_CAP_PROP_MODE);
    qDebug()<<"CV_CAP_PROP_BRIGHTNESS "<<video_obj_->capture_.get(CV_CAP_PROP_BRIGHTNESS);
    qDebug()<<"CV_CAP_PROP_CONTRAST "<<video_obj_->capture_.get(CV_CAP_PROP_CONTRAST);
    qDebug()<<"CV_CAP_PROP_SATURATION "<<video_obj_->capture_.get(CV_CAP_PROP_SATURATION);
    qDebug()<<"CV_CAP_PROP_HUE "<<video_obj_->capture_.get(CV_CAP_PROP_HUE);
    qDebug()<<"CV_CAP_PROP_GAIN "<<video_obj_->capture_.get(CV_CAP_PROP_GAIN);
    qDebug()<<"CV_CAP_PROP_EXPOSURE "<<video_obj_->capture_.get(CV_CAP_PROP_EXPOSURE);
    qDebug()<<"CV_CAP_PROP_CONVERT_RGB "<<video_obj_->capture_.get(CV_CAP_PROP_CONVERT_RGB);
    //qDebug()<<"CV_CAP_PROP_WHITE_BALANCE "<<video_obj_->capture_.get(CV_CAP_PROP_WHITE_BALANCE);
    qDebug()<<"CV_CAP_PROP_RECTIFICATION "<<video_obj_->capture_.get(CV_CAP_PROP_RECTIFICATION);
    qDebug()<<"*************************************";

    QRect label_geometry= ui->label->geometry();
    label_geometry.setWidth(video_obj_->capture_.get(CV_CAP_PROP_FRAME_WIDTH));
    label_geometry.setHeight(video_obj_->capture_.get(CV_CAP_PROP_FRAME_HEIGHT));
    ui->label->setGeometry(label_geometry);
    ui->videoSlider->setRange(0,video_obj_->capture_.get(CV_CAP_PROP_FRAME_COUNT));


    video_obj_->capture_.set(CV_CAP_PROP_POS_FRAMES, 0);
    video_obj_->setVideoStop(0);

    if(video_thread_->isRunning()){
        qDebug()<<"The thread is still running?!!!";
    }
    qDebug()<<"about to start";
    ui->btnPause->setText("Pause");
    video_thread_->start();
}

void MainWindow::onImgProcssed(QImage qimg){
    ui->label->setPixmap(QPixmap::fromImage(qimg));
    ui->videoSlider->setValue(video_obj_->capture_.get(CV_CAP_PROP_POS_FRAMES));
}

void MainWindow::onStopProcess(){
    if(video_thread_->isFinished()) {
        qDebug()<<"thread is finished";
    }
    if(video_thread_->isRunning()){
        qDebug()<<"thread is still running!";
    }

}

void MainWindow::on_btnPause_clicked()
{
    if(video_obj_->isVideoStop()){
        video_obj_->setVideoStop(0);
        ui->btnPause->setText("Pause");
        video_thread_->start();
    }else{
        stopVideoProcessing();
        ui->btnPause->setText("Resume");
    }
}

void MainWindow::on_btnLoad_clicked()
{
    /*
    video_obj_->capture_.open(ui->lineEditVidoeAddress->text().toStdString());
    if(!video_obj_->capture_.isOpened()){
        qDebug()<<"open video failed";
        //should have warn message here
        QMessageBox::warning(this, "Warning", "Failed to load video!", QMessageBox::Ok);
    }
    QRect label_geometry= ui->label->geometry();
    label_geometry.setWidth(video_obj_->capture_.get(CV_CAP_PROP_FRAME_WIDTH));
    label_geometry.setHeight(video_obj_->capture_.get(CV_CAP_PROP_FRAME_HEIGHT));
    ui->label->setGeometry(label_geometry);
    ui->videoSlider->setRange(0,video_obj_->capture_.get(CV_CAP_PROP_FRAME_COUNT));
    */
    QString filename = QFileDialog::getOpenFileName(this, tr("Load Video File"), "D:/Dropbox/tmep/", tr("Files(*.*)"));
    ui->lineEditVidoeAddress->setText(filename);
}

void MainWindow::on_videoSlider_sliderMoved(int position)
{  
    video_obj_->capture_.set(CV_CAP_PROP_POS_FRAMES, position);
}

void MainWindow::on_videoSlider_sliderPressed()
{
    if(!video_obj_->isVideoStop()){
        stopVideoProcessing();
        ui->btnPause->setText("Resume");
    }
}

void MainWindow::on_videoSlider_sliderReleased()
{

}
