#ifndef DIALOGNOTE_H
#define DIALOGNOTE_H

#include <QDialog>

namespace Ui {
class DialogNote;
}

class DialogNote : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNote(QWidget *parent = nullptr);
    ~DialogNote();

    void setUser(QStringList list);

    void setData(QStringList list);

    void hideReport();

private:
    Ui::DialogNote *ui;
};

#endif // DIALOGNOTE_H
