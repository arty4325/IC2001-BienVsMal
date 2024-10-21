#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

/*
cant = 10000
1 = cant / 2 ^nivel  = 5000
2 =
    izquierda = cant /2 ^2 = 2500
    derecha = cant /2 ^2 + cant /2 ^2-1 = 7500
3 =
    izquierda = el anterior - cant / 2^3 = 1250
    derecha = el anterior + cant / 2^3 =  3750

    izquierda = el anterior - cant / 2^3 = 6250
    derecha = el anterior + cant / 2^3 =  8750

1elem/21, 5000
2 raiz/2 , raiz/2 + raiz
3 raiz/2^2, raiz/2^2 + raiz/2

*/
