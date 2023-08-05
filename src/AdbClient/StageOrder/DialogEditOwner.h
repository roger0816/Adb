#ifndef DIALOGEDITOWNER_H
#define DIALOGEDITOWNER_H

#include <QDialog>

namespace Ui {
class DialogEditOwner;
}

class DialogEditOwner : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEditOwner(QWidget *parent = nullptr);
    ~DialogEditOwner();

private:
    Ui::DialogEditOwner *ui;
};

#endif // DIALOGEDITOWNER_H
