#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tinydnnwrapper.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum class model {fish};

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
    void runODE(model model_number=model::fish);


public slots:
    void on_train();
    void on_runODE();


};
#endif // MAINWINDOW_H
