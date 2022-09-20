#ifndef STAGEHOMEPAGE_H
#define STAGEHOMEPAGE_H

#include <QWidget>

namespace Ui {
class StageHomePage;
}

class StageHomePage : public QWidget
{
    Q_OBJECT

public:
    explicit StageHomePage(QWidget *parent = nullptr);
    ~StageHomePage();

private:
    Ui::StageHomePage *ui;
};

#endif // STAGEHOMEPAGE_H
