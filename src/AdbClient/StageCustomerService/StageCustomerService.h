#ifndef STAGECUSTOMERSERVICE_H
#define STAGECUSTOMERSERVICE_H

#include <QWidget>
#include <QButtonGroup>

namespace Ui {
class StageCustomerService;
}

class StageCustomerService : public QWidget
{
    Q_OBJECT

public:
    explicit StageCustomerService(QWidget *parent = nullptr);
    ~StageCustomerService();

private:
    Ui::StageCustomerService *ui;

    QButtonGroup m_btns;


};

#endif // STAGECUSTOMERSERVICE_H
