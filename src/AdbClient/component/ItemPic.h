#ifndef ITEMPIC_H
#define ITEMPIC_H

#include "ItemPicObj.h"
#include "Global.h"
#include "GlobalUi.h"

class ItemPic : public ItemPicObj
{
    Q_OBJECT

public:
    explicit ItemPic(QWidget *parent = nullptr);
    ~ItemPic();

    void showEvent(QShowEvent *e) override;

    void setMd5(QString sMd5);

    QString md5();

    QString uploadPic() override;

signals:
    void sendLock(bool b);
private:

};

#endif // ITEMPIC_H
