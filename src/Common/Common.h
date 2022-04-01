#ifndef COMMON_H
#define COMMON_H

#include <QObject>

#define COMMON Common::INS()

class Common : public QObject
{
    Q_OBJECT
public:
    explicit Common(QObject *parent = nullptr);

    static Common &INS();

private:
    static Common* m_pInstance;


signals:

};

#endif // COMMON_H
