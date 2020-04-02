#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMouseEvent>
#include<math.h>

QImage image(601,601,QImage::Format_RGB888);

int i=0,j=0,edges=0;
int fx,fy;
bool flag=true;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    for (int i=0;i<10;++i) {
        for (int j=0;j<3;++j) {
            mat[i][j]=0;
        }
    }
    for (int j=0;j<10;++j) {
        mat[j][2]=1;
    }
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *ev) {
    if(flag) {
        i--;
        edges=i;
        QRgb val=qRgb(0,255,0);
        QRgb val1=qRgb(255,255,255);
        DDA(mat[i-1][0],mat[i-1][1],mat[0][0],mat[0][1],val);
        DDA(300,0,300,600,val1);
        DDA(0,300,600,300,val1);
        flag=false;
    }
}

void MainWindow::mousePressEvent(QMouseEvent *ev) {
    QRgb val=qRgb(0,255,0);
    if(flag) {
        if(ev->button()== Qt::LeftButton) {
            mat[i][0] = ev->pos().x();
            mat[i][1] = ev->pos().y();
            fx=mat[i][0],fy=mat[i][1];
            i++;
        }
        else if(ev->button()==Qt::RightButton) {
            mat[i][0] = ev->pos().x();
            mat[i][1] = ev->pos().y();
            DDA(mat[i][0],mat[i][1],fx,fy,val);
            fx=mat[i][0],fy=mat[i][1];
            i++;
        }
    }

}

void MainWindow::on_pushButton_clicked()
{
    QRgb val=qRgb(255,0,0);
    //DDA(mat[edges-1][0],mat[edges-1][1],mat[0][0],mat[0][1],val);
    int ans[4][3];
    QString s= ui->textEdit->toPlainText();
    int tx = s.toInt();
    s= ui->textEdit_2->toPlainText();
    int ty = s.toInt();
    int trans[3][3];
    for (int i=0;i<edges;++i) {
        mat[i][0]-=300;
        mat[i][1]-=300;
    }
    trans[0][0]=1;   trans[0][1]=0;  trans[0][2]=0;
    trans[1][0]=0;   trans[1][1]=1;  trans[1][2]=0;
    trans[2][0]=tx;  trans[2][1]=ty; trans[2][2]=1;
    int sum;
    for(int i=0;i<4;i++)
        {
            for(int j=0;j<3;j++)
            {sum=0;
                for(int k=0;k<3;k++)
                {
                    sum+=mat[i][k]*trans[k][j];
                }
                ans[i][j]=sum;
            }
        }
    for(int i=1;i<edges;++i) {
        DDA(ans[i][0]+300,ans[i][1]+300,ans[i-1][0]+300,ans[i-1][1]+300,val);
        if(i==edges-1) {
            DDA(ans[i][0]+300,ans[i][1]+300,ans[0][0]+300,ans[0][1]+300,val);
            break;
        }
    }
}

void MainWindow::DDA(float x1,float y1,float x2,float y2,QRgb value)
{
    float dx,dy;
    int steps;
    float xinc,yinc,x,y;
    dx=x2-x1;
    dy=y2-y1;

    if(abs(dx)>abs(dy))
        {steps=abs(dx);}
    else {steps=abs(dy);}
    xinc=dx/steps;
    yinc=dy/steps;
    x=x1;y=y1;
    for(int i=1;i<=steps;i++)
    {
        image.setPixel(x,y,value);
        x=x+xinc;
        y=y+yinc;
    }
    image.setPixel(x2,y2,value);
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    /*int tx,ty;
    QRgb val=qRgb(255,0,0);
    QString s= ui->textEdit_3->toPlainText();
    int sx = s.toInt();
    s= ui->textEdit_4->toPlainText();
    int sy = s.toInt();
    int trans[3][3];
    for (int i=0;i<edges;++i) {
        mat[i][0]-=300;
        mat[i][1]-=300;
    }
    int ans[4][3];
    trans[0][0]=sx;   trans[0][1]=0;  trans[0][2]=0;
    trans[1][0]=0;   trans[1][1]=sy;  trans[1][2]=0;
    trans[2][0]=0;  trans[2][1]=0; trans[2][2]=1;
    int sum;
    for(int i=0;i<4;i++)
        {
            for(int j=0;j<3;j++)
            {sum=0;
                for(int k=0;k<3;k++)
                {
                    sum+=mat[i][k]*trans[k][j];
                }
                ans[i][j]=sum;
            }
        }
    tx=mat[1][0]-ans[1][0];   ty=mat[1][1]-ans[1][1];
    trans[0][0]=1;   trans[0][1]=0;  trans[0][2]=0;
    trans[1][0]=0;   trans[1][1]=1;  trans[1][2]=0;
    trans[2][0]=tx;  trans[2][1]=ty; trans[2][2]=1;
    for(int i=0;i<4;i++)
        {
            for(int j=0;j<3;j++)
            {sum=0;
                for(int k=0;k<3;k++)
                {
                    sum+=ans[i][k]*trans[k][j];
                }
                ans[i][j]=sum;
            }
        }
    for(int i=1;i<edges;++i) {
        DDA(ans[i][0]+300,ans[i][1]+300,ans[i-1][0]+300,ans[i-1][1]+300,val);
        if(i==edges-1) {
            DDA(ans[i][0]+300,ans[i][1]+300,ans[0][0]+300,ans[0][1]+300,val);
            break;
        }
    }*/

    QRgb val=qRgb(255,0,0);

    int tx,ty;
    int medianx=0,mediany=0;
    QString s= ui->textEdit_3->toPlainText();
    float sx = s.toFloat();
    s= ui->textEdit_4->toPlainText();
    float sy = s.toFloat();
    float trans[3][3];
    for (int i=0;i<edges;++i) {
        mat[i][0]-=300;
        mat[i][1]-=300;
    }

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
    rot[0][0]=sx;   rot[0][1]=0;  rot[0][2]=0;
       rot[1][0]=0;   rot[1][1]=sy;  rot[1][2]=0;
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
           DDA(ansss[i][0]+300,ansss[i][1]+300,ansss[i-1][0]+300,ansss[i-1][1]+300,val);
           if(i==edges-1) {
               DDA(ansss[i][0]+300,ansss[i][1]+300,ansss[0][0]+300,ansss[0][1]+300,val);
               break;
           }
       }


}

void MainWindow::on_pushButton_2_clicked()
{
    QRgb val=qRgb(255,0,0);
    QString str=ui->textEdit_5->toPlainText();
        float angle=str.toFloat();
        angle=((3.14*angle)/180);

    int tx,ty;
    int medianx=0,mediany=0;

    float trans[3][3];
    for (int i=0;i<edges;++i) {
        mat[i][0]-=300;
        mat[i][1]-=300;
    }

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
           DDA(ansss[i][0]+300,ansss[i][1]+300,ansss[i-1][0]+300,ansss[i-1][1]+300,val);
           if(i==edges-1) {
               DDA(ansss[i][0]+300,ansss[i][1]+300,ansss[0][0]+300,ansss[0][1]+300,val);
               break;
           }
       }

}
