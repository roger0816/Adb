#ifndef RPKCORE_H
#define RPKCORE_H

#include "Network.h"
#include "DataBase.h"

#define varName(x) #x


#define RPKCORE RpkCore::INS()



class RpkCore
{
public:
    RpkCore();


    Network network;

    DataBase database;

    static RpkCore& INS();


private :
    static RpkCore * m_pInstance;
};

#endif // RPKCORE_H
