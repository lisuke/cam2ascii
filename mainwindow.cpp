#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCamera>
#include <QVideoWidget>
#include <QVideoFrame>
#include <QCameraImageCapture>
#include <QTimer>
#include <QDebug>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);

    camera = new QCamera(this);

    viewer=new QVideoWidget(this);
    ui->cam_view->addWidget(viewer);
    viewer->autoFillBackground();
    camera->setViewfinder(viewer);

    camera->setCaptureMode(QCamera::CaptureStillImage);

    imageCapture=new QCameraImageCapture(camera,this);
    camera->start();
    QTimer *timer = new QTimer( this );

    connect(imageCapture,SIGNAL(imageCaptured(int,QImage)),this,SLOT(decode(int,QImage)));
    connect(timer,SIGNAL(timeout()),this,SLOT(check()));
    timer->start( 1000 );
    ui->textBrowser->setFont(QFont("Sans",3));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::decode(int id, QImage image)
{
    QString characters(" .,:;i1tfLCG08@");
    image=image.scaled(image.width()/4,image.height()/4);
    id = id;
    QString tmp;
    for(int i =0;i<image.height();i++)
    {
         for(int j=0;j<image.width();j++)
         {
              QRgb pixel=image.pixel(j,i);
              int r=qRed(pixel);
              int g=qGreen(pixel);
              int b=qBlue(pixel);

              float brightness = (0.299 * r + 0.587 * g + 0.114 * b) / 255;
              int index = (characters.length() - 1) - int(brightness * (characters.length() - 1));
              QChar pix_char = characters[index];
              tmp += pix_char;
              qDebug() << pix_char;
         }
         tmp+=QString("\n");
    }
    ui->textBrowser->setHtml(QString("<code>%1</code>").arg(tmp));
}

void MainWindow::check()
{
    imageCapture->capture();
}
