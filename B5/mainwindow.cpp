#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "math.h"

QImage img=QImage(600,600,QImage::Format_RGB888);

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

void MainWindow::hilbert(int u,int r,int d, int l, int h,int i,int& x,int& y)
{
    if(i<=0)
    {
        return;
    }
    i--;
    hilbert(r,u,l,d,h,i,x,y);
    move(u,h,x,y);
    hilbert(u,r,d,l,h,i,x,y);
    move(r,h,x,y);
    hilbert(u,r,d,l,h,i,x,y);
    move(d,h,x,y);
    hilbert(l,d,r,u,h,i,x,y);

}
void MainWindow::move(int j,int h,int& x,int& y)
{
    QRgb val=qRgb(255,255,255);
    int x1=x,y1=y;
    switch(j)
    {

    case 1:
        y-=h; //up
        break;
    case 2:
        x+=h;  //right
        break;
    case 4:
        x-=h;  //left

        break;
    case 3 :
        y+=h;
        break;

    }
    dda(x1,y1,x,y,val);
}

void MainWindow::dda(float x1,float y1,float x2,float y2,QRgb val)
{

    float dx=x2-x1,dy=y2-y1,x=x1,y=y1;
    float steps=abs(dx)>abs(dy)?abs(dx):abs(dy);
    float xinc=dx/steps,yinc=dy/steps;
    for(int i=0;i<=steps;i++)
    {
        img.setPixel(x,y,val);
        x+=xinc;
        y+=yinc;
    }
    ui->label->setPixmap(QPixmap::fromImage(img));


}
int MainWindow::sign(int x)
{
    if(x==0)
    {
        return 0;
    }
    if(x>0)
    {
        return 1;
    }
    return -1;
}


void MainWindow::on_pushButton_clicked()
{
    QRgb val=qRgba(255,255,255,40);
    dda(100,100,500,100,val);
    dda(500,100,500,500,val);
    dda(500,500,100,500,val);
    dda(100,500,100,100,val);
    QString s = ui->textEdit->toPlainText();
    int i = s.toInt();
    int div = pow(2,i);
    int len = ceil(400/div);
    int x1=100,y1=100;
    for(int i=0;i<div;i++) {
        dda(x1,y1,x1,y1+400,val);
        x1+=len;
    }
    x1=100,y1=100;
    for(int i=0;i<div;i++) {
        dda(x1,y1,x1+400,y1,val);
        y1+=len;
    }
    int x=100+(len/2),y=500-(len/2);
    hilbert(1,2,3,4,len,i,x,y);
    ui->label->setPixmap(QPixmap::fromImage(img));
}
