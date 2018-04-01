#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <fcntl.h>

#define TOTALFRAMES 151
#define CAPTURE_IDLE 0
#define CAPTURE_START 1
#define CAPTURE_STOP 2
#define CAPTURE_COMPRESS 3

char last_state = 2;
char state = 0;
long framecnt=0;
char yuvfilename[11] = {'r','c','q','0','0','0','.','y','u','v','\0'};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    vd = new VideoDevice(tr("/dev/video0"));
    qDebug("a");
    frame = new QImage(rgb_buffer,640,480,QImage::Format_RGB888);
    qDebug("a");
    //timer = new QTimer(this);
    //connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    //timer->start(500);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    rs = vd->get_frame(&yuv_buffer_pointer,&len);

    if(last_state==2 && state == 0)
    {
        yuvfile = fopen(yuvfilename,"wb+");             //?
        yuvfilename[5]++;
    }

    if(state == 1)
    {
        rs = write420();

    }

    if(last_state==1 && state==2)
    {
        fclose(yuvfile);
    }

    last_state=state;

    convert_yuv_to_rgb_buffer();

  //  frame->loadFromData(rgb_buffer,640 * 480 * 3);
   // ui->label->setAutoFillBackground(true);
    ui->label->setPixmap(QPixmap::fromImage(*frame,Qt::AutoColor));
    qDebug("c");

    rs = vd->unget_frame();
}
int MainWindow::write420()
{
    int x,y;
    long int index1 =0;

        if (yuv_buffer_pointer[0] == '\0')
        {
            return -1;
        }
        //change to YUV420 by rcq
        // YUV420 and YUV411
        for(x=0;x<640;x++)
        {
                for(y=0;y<480;y++)
                {
                        Y_frame[index1]=yuv_buffer_pointer[2*index1];
                        index1++;
                }
        }

        index1=0;
        for(x=0;x<480;x++,x++)
        {
                for(y=0;y<640;y++,y++)
                {
                        Cb_frame[index1]=yuv_buffer_pointer[(x*640+y)*2+1];
                        Cr_frame[index1]=yuv_buffer_pointer[(x*640+y)*2+3];
                        index1++;
                }
        }

        fwrite(Y_frame, 307200, 1, yuvfile);
        fwrite(Cb_frame,76800, 1, yuvfile);
        fwrite(Cr_frame,76800, 1, yuvfile);

        framecnt++;
        printf("writed frame %ld\n",framecnt);
}

/*yuv格式转换为rgb格式*/
int MainWindow::convert_yuv_to_rgb_buffer()
{
    unsigned long in, out = 0;
    int y0, u, y1, v;
    int r, g, b;
    for(in = 0; in < IMG_WIDTH * IMG_HEIGTH * 2; in += 4)
    {
        y0 = yuv_buffer_pointer[in + 0];
        u  = yuv_buffer_pointer[in + 1];
        y1 = yuv_buffer_pointer[in + 2];
        v  = yuv_buffer_pointer[in + 3];

        r = y0 + (1.370705 * (v-128));
        g = y0 - (0.698001 * (v-128)) - (0.337633 * (u-128));
        b = y0 + (1.732446 * (u-128));

        if(r > 255) r = 255;
        if(g > 255) g = 255;
        if(b > 255) b = 255;
        if(r < 0) r = 0;
        if(g < 0) g = 0;
        if(b < 0) b = 0;
        rgb_buffer[out++] = r;
        rgb_buffer[out++] = g;
        rgb_buffer[out++] = b;

        r = y1 + (1.370705 * (v-128));
        g = y1 - (0.698001 * (v-128)) - (0.337633 * (u-128));
        b = y1 + (1.732446 * (u-128));

        if(r > 255) r = 255;
        if(g > 255) g = 255;
        if(b > 255) b = 255;
        if(r < 0) r = 0;
        if(g < 0) g = 0;
        if(b < 0) b = 0;
        rgb_buffer[out++] = r;
        rgb_buffer[out++] = g;
        rgb_buffer[out++] = b;
    }
    return 0;
}


void MainWindow::on_pushButton_start_clicked()
{

    switch(state)
    {
    case 0:
        {
        ui->pushButton_start->setText("stop");
        state = 1;
        break;
        }
    case 1:
        {
        ui->pushButton_start->setText("compress");
        state = 2;
        break;
        }
    case 2:
        {
        ui->pushButton_start->setText("start");
        framecnt=0;
        state = 0;
        break;
        }
    default :break;
    }

}
