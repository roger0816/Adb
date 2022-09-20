#include "Common.h"

Common *Common ::m_pInstance =nullptr;

Common::Common(QObject *parent)
    : QObject{parent}
{

}

Common &Common::INS()
{
  if(m_pInstance == nullptr)
      m_pInstance = new Common();

  return *m_pInstance;
}

