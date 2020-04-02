#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QStack"
#include "math.h"

QImage image(600,600,QImage::Format_RGB888);
QRgb value;
QRgb val= qRgb(255,0,0);
QRgb val2= qRgb(255,255,255);
QStack<float> s;
float X,Y;
int side;

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

void MainWindow::Bresenham(float x1,float y1,float x2,float y2,QRgb value)
{
    float dx,dy,temp;
    float x,y,e;
    int s1,s2,i;
    bool interchange;

    dx=abs(x2-x1);
    dy=abs(y2-y1);

    x=x1;
    y=y1;

    s1=sign(x1,x2);
    s2=sign(y1,y2);

    if(dy>dx)
    {
        temp=dx;
        dx=dy;
        dy=temp;
        interchange=1;
    }
    else
        {interchange=0;}

    e=(2*dy)-dx;
    for(i=1;i<=dx;i++)
    {
        image.setPixel(x,y,value);
        while(e>0)
        {
            if(interchange==1)
                {x=x+s1;}
            else
                {y=y+s2;}
            e=e-(2*dx);
        }
        if(interchange==1)
            {y=y+s2;}
        else
            {x=x+s1;}
        e=e+(2*dy);
    }
    image.setPixel(x1,y1,value);
    image.setPixel(x2,y2,value);
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}
int MainWindow::sign(float a,float b)
{
    if(b>a)
        {return 1;}
    else if(b<a)
        {return -1;}
    else
        {return 0;}
}

void MainWindow::floodfill(float x1,float y1)
{

    QRgb temp=image.pixel(x1,y1);
    float x,y;
    image.setPixel(x1,y1,val2);
    s.push(y1);
    s.push(x1);
    while(!s.empty()) {
        x= s.pop();
        y= s.pop();
        image.setPixel(x,y,val2);
        if(image.pixel(x+1,y)==qRgb(0,0,0)) {
            s.push(y);
            s.push(x+1);
        }
        if(image.pixel(x-1,y)==qRgb(0,0,0)) {
            s.push(y);
            s.push(x-1);
        }
        if(image.pixel(x,y+1)==qRgb(0,0,0)) {
            s.push(y+1);
            s.push(x);
        }
        if(image.pixel(x,y-1)==qRgb(0,0,0)) {
            s.push(y-1);
            s.push(x);
        }
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}


void MainWindow::on_pushButton_clicked()
{
    value = qRgb(255,0,0);
    QString str=ui->textEdit->toPlainText();
    float x= str.toFloat();
    str=ui->textEdit_2->toPlainText();
    float y= str.toFloat();
    str=ui->textEdit_3->toPlainText();
    side = str.toInt();
     X=x;Y=y;
    float inc = side/4;
    for(int i=0;i<5;++i) {
        Bresenham(x,y,x+side,y,value);
        y+=inc;
    }
    x=X;
    y=Y;
    for(int i=0;i<5;++i) {
        Bresenham(x,y,x,y+side,value);
        x+=inc;
    }

    x=X;
    y=Y;
    for(int i=0;i<4;++i) {
        for(int j=0;j<4;++j) {
            if(i%2==0 && j%2!=0) {
                floodfill(x+(j*inc)+(inc/2),y+(i*inc)+(inc/2));
            }
            if(i%2!=0 && j%2==0) {
                floodfill(x+(j*inc)+(inc/2),y+(i*inc)+(inc/2));
            }
        }
    }
}

void MainWindow::clearScreen() {
    value = qRgb(0,0,0);
    for(int i=0;i<600;i++) {
        for(int j=0;j<600;j++) {
            image.setPixel(i,j,value);
        }
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    int x=X,y=Y;
    int inc= side/4;
   // clearScreen();
    Bresenham(150-(100/sqrt(2)),150,150,150-(100/sqrt(2)),val);
    Bresenham(150,150-(100/sqrt(2)),150-(100/sqrt(2))+ 100*sqrt(2),150,val);
    //rotate(X,Y+100,X+side,Y+100);
    //rotate(X,Y+150,X+side,Y+150);
}

void MainWindow::rotate(float x1,float y1,float x2,float y2)
{
    QRgb val=qRgb(255,0,0);
    float angle=((3.14*45)/180);
    int edges=2;
    int tx,ty;
    int medianx=0,mediany=0;

    float trans[3][3];
    mat[0][0] = x1-300;
    mat[0][1] = y1-300;
    mat[1][0] = x2-300;
    mat[1][1] = y2-300;
    mat[0][2] = 1;
    mat[1][2] = 1;

    for(int i=0;i<edges;++i) {
        medianx+=mat[i][0];
        mediany+=mat[i][1];
    }
    medianx/=edges;
    mediany/=edges;
    tx=medianx;
    ty=mediany;

    float ans[3][3];
    trans[0][0]=1.0;   trans[0][1]=0.0;  trans[0][2]=0.0;
    trans[1][0]=0.0;   trans[1][1]=1.0;  trans[1][2]=0.0;
    trans[2][0]=-(float)tx;  trans[2][1]=-(float)ty; trans[2][2]=1.0;
    double sum;
    float rot[3][3];
    rot[0][0]=cos(angle);   rot[0][1]=sin(angle);  rot[0][2]=0;
       rot[1][0]=-sin(angle);   rot[1][1]=cos(angle);  rot[1][2]=0;
       rot[2][0]=0;
       rot[2][1]=0; rot[2][2]=1;
       for(int i=0;i<4;i++)
          {
              for(int j=0;j<3;j++)
              {sum=0;
                  for(int k=0;k<3;k++)
                  {
                      sum+=((float)trans[i][k])*rot[k][j];
                  }
                  ans[i][j]=sum;
              }
          }
       trans[0][0]=1.0;   trans[0][1]=0.0;  trans[0][2]=0.0;
       trans[1][0]=0.0;   trans[1][1]=1.0;  trans[1][2]=0.0;
       trans[2][0]=(float)tx;  trans[2][1]=(float)ty; trans[2][2]=1.0;
       float anss[3][3];
       for(int i=0;i<4;i++)
          {
              for(int j=0;j<3;j++)
              {sum=0;
                  for(int k=0;k<3;k++)
                  {
                      sum+=((float)ans[i][k])*trans[k][j];
                  }
                  anss[i][j]=sum;
              }
          }
        float ansss[4][3];
       for(int i=0;i<4;i++)
          {
              for(int j=0;j<3;j++)
              {sum=0;
                  for(int k=0;k<3;k++)
                  {
                      sum+=((float)mat[i][k])*anss[k][j];
                  }
                  ansss[i][j]=sum;
              }
          }

       for(int i=1;i<edges;++i) {
           Bresenham(ansss[i][0]+300,ansss[i][1]+300,ansss[i-1][0]+300,ansss[i-1][1]+300,val);
           if(i==edges-1) {
               Bresenham(ansss[i][0]+300,ansss[i][1]+300,ansss[0][0]+300,ansss[0][1]+300,val);
               break;
           }
       }

}
