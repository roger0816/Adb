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

    QString uploadPic() override;
private:

};

#endif // ITEMPIC_H
