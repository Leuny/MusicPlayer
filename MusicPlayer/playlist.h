#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <QWidget>
class QLabel;
class QTableWidget;

class PlayList:public QWidget
{
    Q_OBJECT
public:
    PlayList(QWidget *parent=0);
    QTableWidget *tableWidget;
    QLabel *numLabel;
signals:
    void playListClear();
private:
    QLabel *listLabel;
    QAction *clearAction;
    QFont font;
private slots:
    void listClean();

};

#endif // PLAYLIST_H
