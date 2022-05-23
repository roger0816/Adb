#ifndef ACTION_H
#define ACTION_H

#include <QObject>
//#include "CSqlClass.h"
#include "RpkCore.h"
#include "DEF.h"
#include "QueryObj.h"
#include "VojData.h"


namespace _KEY {
static QString isRememberLogin="isRememberLogin";

static QString lastLogin="lastLogin";

}


// client action
class Action : public QObject
{
    Q_OBJECT
public:
    explicit Action(QObject *parent = nullptr);

    VojData VojData;

    void setDataFromServer(bool b = true);

    bool action(ACT::_KEY act, QVariantList listData, QString &sError);

    bool action(ACT::_KEY act, QVariantMap data, QString &sError);

    bool action(ACT::_KEY act, QVariantMap data, QVariantMap &out, QString &sError);


    bool action(ACT::_KEY act, QVariantMap data,QVariantList &listOut, QString &sError);

    bool action(ACT::_KEY act, QVariantList listData, QVariantList &listOut, QString &sError);


    bool checkLogin(QString sUser,QString sPass,QString &sError);

    bool addUser(QString sUser, QString sPass, QString sCid, QString sName, int iLv, QDate startDate, QString &sError);

    bool editUser(QVariantMap userData, QString &sError);

    bool delUser(QString sUser, QString &sError);

    // QVariantList queryUser(QString sId="");

    QList<UserData> queryUser(QString sId="");

    bool setKeyValue(QString key, QString value,bool inLocal=true);

    QString getKeyValue(QString key, bool inLocal=true);

    //    QString m_sCurrentLoginUser ="";

    //    int m_iUserLv=-1;

    UserData m_currentUser;

private :

    QueryObj m_queryObj;

    CData query(CData data);


    CData callServer(CData data);


    bool m_bDataFromServer = true;

    //CSqlClass m_sql;

signals:

};

#endif // ACTION_H
