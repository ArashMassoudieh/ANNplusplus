#ifndef CUSTOMPLOTWIDGET_H
#define CUSTOMPLOTWIDGET_H

#include <QWidget>
#include <QMap>
#include <QStringList>
#include <BTCSet.h>
#include "qcustomplot.h"
#include "plotter.h"


namespace Ui {
class CustomPlotWidget;
}

class CustomPlotWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CustomPlotWidget(QWidget *parent = nullptr);
    ~CustomPlotWidget();
    bool PlotData(CBTC& BTC);
    bool AddData(CBTC& BTC);
    void SetYAxisTitle(const QString& s);
    QCustomPlot *Plot() {return plot;}
private:
    Ui::CustomPlotWidget *ui;
    QMap<QString, _timeseries> BTCs;
    QCustomPlot *plot;
    double minx=1e12;
    double maxx=-1e12;
    double miny=1e12;
    double maxy=-1e12;

    QVector<QColor> colours = {QColor("cyan"), QColor("magenta"), QColor("red"),
                          QColor("darkRed"), QColor("darkCyan"), QColor("darkMagenta"),
                          QColor("green"), QColor("darkGreen"), QColor("yellow"),
                          QColor("blue")};
    bool showlegend = true;


private slots:
    bool On_Legend_Clicked();
    void axisLabelDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part);
    void legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item);
    void contextMenuRequest(QPoint pos);
    void moveLegend();
    void graphClicked(QCPAbstractPlottable *plottable, int dataIndex);
    void removeSelectedGraph();
    void mousePress();
    void mouseWheel();
    void selectionChanged();
    void turnSelectedtoSymbols();
    void Deselect();



};

#endif // CUSTOMPLOTWIDGET_H
