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
    void mousePressEvent(QMouseEvent *ev);
    void DDA(float x1,float y1,float x2,float y2,QRgb value);
    void mouseDoubleClickEvent(QMouseEvent *ev);

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    int mat[10][3];
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
