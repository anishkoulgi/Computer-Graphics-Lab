#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"
#include "QStack"

QStack<int> s;
float xi,yi,l,b;
int x1,y1,x2,y2,xmin,ymin,xmax,ymax;
point a[2];
QImage image(600,600,QImage::Format_RGB888);

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

point MainWindow::setcode(point p1)
{
    point temp;
    for(int i=0;i<4;i++)
        {temp.code[i]=0;}
    if(p1.y<ymax) {temp.code[0]=1;}
    if(p1.y>ymin) {temp.code[1]=1;}
    if(p1.x>xmax) {temp.code[2]=1;}
    if(p1.x<xmin) {temp.code[3]=1;}
temp.x=p1.x; temp.y=p1.y;
return temp;
}

int MainWindow::visibility(point p1, point p2)
{
    int flag;
    for(int j=0;j<4;j++)
    {
        if((!p1.code[j]) && (!p2.code[j]))
        {flag=0;}
        else {flag=1; break;}
    }
    if(flag==0)
        {return 1;}
    flag=0;
    for(int j=0;j<4;j++)
    {
        if((p1.code[j]) && (p2.code[j]))
        {flag=1; break;}
    }
    if(flag==0) {return 2;}
    return 0;
}

point MainWindow::clipline(point p1,point p2)
{
    point n1;
    float m;
    m=(float)((p2.y-p1.y)/(p2.x-p1.x));
    if(p1.code[3]==1)
    {n1.y=m*(xmin-p2.x)+p2.y;
        n1.x=xmin;
        return n1;}
    if(p1.code[1]==1)
    {n1.x=(1/m)*(ymin-p2.y)+p2.x;
        n1.y=ymin;
        return n1;}
    if(p1.code[2]==1)
    {n1.y=m*(xmax-p2.x)+p2.y;
        n1.x=xmax;
        return n1;}
    if(p1.code[0]==1)
    {n1.x=(1/m)*(ymax-p2.y)+p2.x;
        n1.y=ymax;
        return n1;}
    return p1;
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    QRgb value;
    value=qRgb(0,255,0);
    if(event->button()==Qt::LeftButton) {
        x1 = event->x();
        y1 = event->y();
        s.push(x1);
        s.push(y1);
    }
    else if(event->button()==Qt::RightButton) {
        x2 = event->x();
        y2 = event->y();
        s.push(x2);
        s.push(y2);
        DDA(x1,y1,x2,y2,value);
    }
}



void MainWindow::DDA(float x1,float y1,float x2,float y2,QRgb value)
{
    int i,steps;
    float dx,dy;
    float xinc,yinc;
    float x,y;

    dx=x2-x1;
    dy=y2-y1;

    if(abs(dy)>abs(dx))
        {steps=abs(dy);}
    else
        {steps=abs(dx);}

    xinc=dx/steps;
    yinc=dy/steps;
    x=x1;
    y=y1;
    for(i=1;i<=steps;i++)
         {
           image.setPixel(x,y,value);
           x=x+xinc;
           y=y+yinc;
        }
   image.setPixel(x2,y2,value);
ui->label->setPixmap(QPixmap::fromImage(image));
ui->label->show();
}

void MainWindow::on_pushButton_clicked()
{
    QRgb value;
    value=qRgb(255,255,255);
    QString s = ui->textEdit->toPlainText();
    xi = s.toFloat();
    s = ui->textEdit_2->toPlainText();
    yi = s.toFloat();
    s = ui->textEdit_3->toPlainText();
    l = s.toFloat();
    s = ui->textEdit_4->toPlainText();
    b = s.toFloat();
    DDA(xi,yi,xi+l,yi,value);
    DDA(xi+l,yi,xi+l,yi+b,value);
    DDA(xi+l,yi+b,xi,yi+b,value);
    DDA(xi,yi+b,xi,yi,value);
    xmin=xi;
    ymax=yi;
    xmax=xi+l;
    ymin=yi+b;
}

void MainWindow::on_pushButton_2_clicked()
{
    while(!s.empty()) {
        a[1].y=s.pop();
        a[1].x=s.pop();
        a[0].y=s.pop();
        a[0].x=s.pop();

            QRgb val=qRgb(0,0,0);
            QRgb val1=qRgb(0,255,0);
            int v;
            a[0]=setcode(a[0]);
            a[1]=setcode(a[1]);
            v=visibility(a[0],a[1]);
            if(v==1) {return;}
            if(v==0)
                {DDA(a[0].x,a[0].y,a[1].x,a[1].y,val);
                DDA(a[1].x,a[1].y,a[0].x,a[0].y,val);
                return;}
            if(v==2)
            {
                point new1,new2;
                new1=clipline(a[0],a[1]);
                new2=clipline(a[1],a[0]);
                DDA(a[0].x,a[0].y,a[1].x,a[1].y,val);
                DDA(a[1].x,a[1].y,a[0].x,a[0].y,val);
                DDA(new1.x,new1.y,new2.x,new2.y,val1);
            }
    }
}
