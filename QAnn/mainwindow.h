#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ANN_class.h"
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
    ANN_class ANN;
    void train();
    void traintiny();
};
#endif // MAINWINDOW_H
