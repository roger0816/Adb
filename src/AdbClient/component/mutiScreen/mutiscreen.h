#ifndef MUTISCREEN_H
#define MUTISCREEN_H

#include <QObject>
#include <QPixmap>
#include <QMutex>
#include <QEventLoop>
#include <QBuffer>
class mutiScreen : public QObject
{
    Q_OBJECT
public:
    explicit mutiScreen(QObject *parent = nullptr);
    ~mutiScreen();

    QPixmap *get_screen();

    static mutiScreen *Instance()
    {
        static QMutex mutex;

        if (!_instance) {
            QMutexLocker locker(&mutex);

            if (!_instance) {
                _instance = new mutiScreen;
            }
        }

        return _instance;
    }

    QPixmap* getCaptureScreen();

    QByteArray getCaptureData();




signals:

    void capture_done();

public slots:

   void showCaptureScreen();


private:
    static mutiScreen *_instance;
    QPixmap capicture_pix;


private slots:
    void screenImageReady();

};

#endif // MUTISCREEN_H
