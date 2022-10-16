#ifndef STAGEREPORT_H
#define STAGEREPORT_H

#include <QWidget>
#include <QButtonGroup>
//#include <QChart>
//#include <QtCharts/QChartView>
//#include <QtCharts>
//#include <QChartView>
//#include <QChartGlobal>
//#include <QtCharts/QtCharts>


//using namespace QtCharts;

namespace Ui {
class StageReport;
}

class StageReport : public QWidget
{
    Q_OBJECT

public:
    explicit StageReport(QWidget *parent = nullptr);
    ~StageReport();

private:
    Ui::StageReport *ui;

    QButtonGroup m_btns;
};

#endif // STAGEREPORT_H
