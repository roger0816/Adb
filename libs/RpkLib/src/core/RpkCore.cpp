#include "RpkCore.h"

#ifndef nullptr

#define nullptr 0

#endif


//RpkCore *RpkCore::m_pInstance = nullptr;



RpkCore::RpkCore()
{
}

RpkCore &RpkCore::INS()
{

//    if(m_pInstance==0)
//        m_pInstance=new RpkCore();
//    return *m_pInstance;

    static RpkCore core;

    return core;

}
