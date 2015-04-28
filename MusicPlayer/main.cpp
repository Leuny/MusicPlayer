#include <QtGui/QApplication>
#include "musicplayer.h"
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    MusicPlayer w;
    w.show();

    return a.exec();
}
