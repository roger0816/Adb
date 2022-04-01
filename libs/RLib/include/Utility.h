#ifndef UTILITY_H
#define UTILITY_H

#include <QObject>
#include <QMap>
#include <QStringList>
#include <QPropertyAnimation>
#include <QEventLoop>
#include <QTranslator>
#include <QTime>
#include <QCoreApplication>
#include <QPoint>
#include <QFile>

struct CData
{
    QString sAction;
    QString sType;
    QStringList listData;
    QList<QStringList> dData;
};



class Utility :public QObject
{
    Q_OBJECT
public:
    Utility(QObject *parent = 0);
    ~Utility();

    QByteArray encode(CData data);

    CData decode(QByteArray arrData);

    void creatConfig(QString sFile, QString sBeginGroup, QMap<QString, QString *> &data);

    bool loadConfig(QString sFile, QString sBeginGroup, QMap<QString, QString *> &data,bool bIsNoneAutoCreat=true);

    int checkLogin(QString sUser,QString sPassWord);

    void sleep(unsigned int msec);

    QByteArray readFile(const QString &fileName);

    bool writeFile(const QString &fileName, const QByteArray &dat);

//    void aniMove(QObject *obj, QPoint pStart,QPoint pEnd, int iMsec=200);

//    void aniMove(QObject *obj, QPoint pEnd, int iMsec=200);

    void setTranslatroFiles(QStringList list);

    void reloadTranslator(int i=-1);

private:
    QPropertyAnimation m_ani;

    QEventLoop m_eventLoop;

    QStringList m_listLanguageFile;

    int m_iIdxLanguage;

    QTranslator m_translator;
signals:

    void signalChangeLanguage(int i);

};

#endif // UTILITY_H
