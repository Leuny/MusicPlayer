#ifndef MUSICLRC_H
#define MUSICLRC_H
#include <QLabel>
class QTimer;
class MusicLrc : public QLabel
{
    Q_OBJECT
public:
    MusicLrc(QWidget *parent=0,int w=0,int h=0,bool acceptEvent=true);
    void startLrcMask(qint64 intervalTime);
    void stopLrcMask();
    QFont font;
    QLinearGradient linearGradient;
    QLinearGradient maskLinearGradient;
protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
private slots:
    void timeout();
private: 
    QTimer *timer;
    qreal lrcMaskWidth;
    // 每次歌词遮罩增加的宽度
    qreal lrcMaskWidthInterval;
    QPoint offset;

    int w,h;
    bool acceptEvent;

};

#endif // MUSICLRC_H
