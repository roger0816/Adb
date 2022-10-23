#include "CData.h"
#include <QDebug>
CData::CData()
{

}

CData::CData(QByteArray data):CData()
{
    deCodeJson(data);
}
