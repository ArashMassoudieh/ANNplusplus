#ifndef MULTIPLOTWINDOW_H
#define MULTIPLOTWINDOW_H

#include <QDialog>
#include <QVector>
#include "customplotwidget.h"

namespace Ui {
class MultiPlotWindow;
}

class MultiPlotWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MultiPlotWindow(QWidget *parent = nullptr);
    explicit MultiPlotWindow(int n_panels, QWidget *parent = nullptr);
    ~MultiPlotWindow();
    QVector<CustomPlotWidget*> plots;
    CustomPlotWidget* Plot(int i)
    {
        if (i>=plots.size())
            return nullptr;
        else
            return plots[i];

    }
    void AddData(int i, CBTC &BTC)
    {
        Plot(i)->AddData(BTC);
    }
    void SetData(int i, CBTC &BTC)
    {
        Plot(i)->PlotData(BTC);
    }
private:
    Ui::MultiPlotWindow *ui;
};

#endif // MULTIPLOTWINDOW_H
