#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QtCore/QUrl>
#include "videodevice.h"
#include <QDebug>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QImage *frame;
    int rs;
    unsigned int len;
    int convert_yuv_to_rgb_buffer();
    void print_quartet(unsigned int i);

    VideoDevice *vd;
    FILE * yuvfile;
    unsigned char rgb_buffer[640*480*3];
    unsigned char * yuv_buffer_pointer;

    char Y_frame[640*480];
    char Cr_frame[240*320];
    char Cb_frame[240*320];

    int write420();

private slots:
    void on_pushButton_start_clicked();
    void paintEvent(QPaintEvent *);

};

#endif // MAINWINDOW_H
