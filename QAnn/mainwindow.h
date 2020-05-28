#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tinydnnwrapper.h"

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

private:
    Ui::MainWindow *ui;

    void train();
    void traintiny();

public slots:
    void on_train();

};
#endif // MAINWINDOW_H
