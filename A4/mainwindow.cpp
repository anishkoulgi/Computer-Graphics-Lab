#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"

QImage image(600, 600, QImage::Format_RGB888);
float ox,oy;
int R,G,B;
QRgb value;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    const QPoint p = event->pos();
    value= qRgb(R,G,B);
    image.setPixel(p.x(),p.y(),value);
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
    if(event->button()== Qt::RightButton) {
        DDA(ox,oy,p.x(),p.y());
    }
    ox=p.x();
    oy=p.y();
}

void MainWindow::DDA(float x1,float y1,float x2,float y2)
{
    int steps;
    float dx,dy;
    dx=x2-x1;
    dy=y2-y1;
    if(abs(dx)>abs(dy))
        steps=abs(dx);
    else
        steps=abs(dy);

    //QRgb value;
    float x=x1;
    float y=y1;
    value=qRgb(R,G,B);
    float xinc,yinc;
    xinc=dx/steps;
    yinc=dy/steps;
    for(int j=1;j<steps;j++)
    {
        image.setPixel(x,y,value);
        x=x+xinc;
        y=y+yinc;
    }

    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}


void MainWindow::on_horizontalSlider_valueChanged(int position)
{
    R=ui->horizontalSlider->value();
    G=ui->horizontalSlider_2->value();
    B=ui->horizontalSlider_3->value();
    value= qRgb(R,G,B);
    QImage image1(180,120,QImage::Format_RGB888);
    image1.fill(value);
    ui->label_2->setPixmap(QPixmap::fromImage(image1));
    ui->label_2->show();
}

void MainWindow::on_horizontalSlider_2_valueChanged(int position)
{
    R=ui->horizontalSlider->value();
    G=ui->horizontalSlider_2->value();
    B=ui->horizontalSlider_3->value();
    value= qRgb(R,G,B);
    QImage image1(180,120,QImage::Format_RGB888);
    image1.fill(value);
    ui->label_2->setPixmap(QPixmap::fromImage(image1));
    ui->label_2->show();
}

void MainWindow::on_horizontalSlider_3_valueChanged(int position)
{
    R=ui->horizontalSlider->value();
    G=ui->horizontalSlider_2->value();
    B=ui->horizontalSlider_3->value();
    value= qRgb(R,G,B);
    QImage image1(180,120,QImage::Format_RGB888);
    image1.fill(value);
    ui->label_2->setPixmap(QPixmap::fromImage(image1));
    ui->label_2->show();
}
