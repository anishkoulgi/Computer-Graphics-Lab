#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void hilbert(int u,int r,int d, int l, int h,int i,int& x,int& y);
    void dda( float x1, float y1, float x2, float y2,QRgb value);
    void move( int j, int h, int&x, int &y);
    int sign(int x);


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
