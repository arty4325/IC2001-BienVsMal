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

1elem/21, 5000
2 raiz/2 , raiz/2 + raiz
3 raiz/2^2, raiz/2^2 + raiz/2

*/
