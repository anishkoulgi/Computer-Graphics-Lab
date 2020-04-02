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
    void Bresenham(float x1,float y1,float x2,float y2,QRgb value);
    void floodfill(float x1,float y1);
    int sign(float a,float b);
    void on_pushButton_clicked();
    void rotate(float x1,float y1,float x2,float y2);
    void clearScreen();
    void on_pushButton_2_clicked();

private:
    float mat[2][3];
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
