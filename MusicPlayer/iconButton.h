#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include <QtGui/QWidget>
class IconButton : public QWidget
{
    Q_OBJECT
public:
    IconButton(QString iconStr1,QString iconStr2,QWidget *parent = 0);
    void setPosition(int x,int y);
    void setIconTip(QString iconTip);

protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
signals:
    void isclicked();
private:
    QPixmap m_Pixmap,m_Pixmap1;
    int x,y;
    QString iconTip;
    bool leave;
};


#endif // ICONBUTTON_H
