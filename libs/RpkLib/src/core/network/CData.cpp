#include "CData.h"

CData::CData()
{

}

CData::CData(QByteArray data):CData()
{
    deCodeJson(data);
}
