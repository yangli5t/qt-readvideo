#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "videoobj.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void stopVideoProcessing();

    videoObj* video_obj_;
    QThread* video_thread_;
    
private slots:
    void on_btnStart_clicked();
    void on_btnPause_clicked();
    void on_btnLoad_clicked();

    void on_videoSlider_sliderMoved(int position);
    void on_videoSlider_sliderPressed();
    void on_videoSlider_sliderReleased();

public slots:
    void onImgProcssed(QImage);
    void onStopProcess();


private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
