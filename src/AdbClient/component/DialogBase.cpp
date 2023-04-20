#include "DialogBase.h"

DialogBase::DialogBase(QWidget *parent)
    : QDialog{parent}
{

}

int DialogBase::exec()
{


    QDesktopWidget* desktop = QApplication::desktop();
      QRect screenRect = desktop->screenGeometry();

      // 獲取主窗口位置
      QWidget* mainWindow = QApplication::topLevelWidgets().at(0);
      QRect mainWindowRect = mainWindow->geometry();

      // 計算主窗口在畫面上的位置
      int x = screenRect.x() + (screenRect.width() - mainWindowRect.width()) / 2;
      int y = screenRect.y() + (screenRect.height() - mainWindowRect.height()) / 2;

      qDebug() << "Main window position:" << x << y;



   //QRect rec= qApp->desktop()->rect();

   //this->move(rec.x()+(rec.width()-width()/2),rec.y()+(rec.height()-height())/2);

  // this->setGeometry(0,0,100,100);

   return QDialog::exec();
}
