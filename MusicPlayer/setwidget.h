#ifndef SETWIDGET_H
#define SETWIDGET_H
#include <QWidget>
class QTimer;
namespace Ui {
    class SetWidget;
}
class MusicPlayer;
class SetWidget:public QWidget
{
    Q_OBJECT
public:
    SetWidget(QWidget *parent=0,MusicPlayer *MP=0);
     Ui::SetWidget *ui;
     QColor LrcColor;
private slots:
    void saveAll();
    void chooseColor();
    void changeBackground();
private:

    MusicPlayer *MP;

    QTimer *time;
    int i;
};

#endif // SETWIDGET_H
