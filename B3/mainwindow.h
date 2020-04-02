#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

typedef struct pt
{
    float x,y;
    bool code[4];
}point;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void DDA(float x1,float y1,float x2,float y2,QRgb value);
    void mousePressEvent(QMouseEvent *ev);
    point setcode(point p1);
    int visibility(point,point);
    point clipline(point,point);

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
