#include "iconButton.h"
#include <QtGui>

IconButton::IconButton(QString iconStr1,QString iconStr2,QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint)
{

    //加载一幅有部分区域是透明的图片作为程序的界面
    m_Pixmap.load(iconStr1);
    m_Pixmap1.load(iconStr2);
    if(m_Pixmap1.size().width()<m_Pixmap.size().width())
    {
        m_Pixmap.load(iconStr2);
        m_Pixmap1.load(iconStr1);
    }
    //setStyleSheet("background-color:lightblue");
    leave=true;
    this->x=0;
    this->y=0;

}

void IconButton::mousePressEvent(QMouseEvent *event)
{
    //按住左键关闭程序
    if(event->button() == Qt::LeftButton)
    {
        emit isclicked();
    }
}
void IconButton::setPosition(int x,int y)
{
    this->x=x;
    this->y=y;
}
void IconButton::setIconTip(QString iconTip)
{
    this->iconTip=iconTip;
}

void IconButton::paintEvent(QPaintEvent *event)
{
    qDebug("paint");
    QPainter painter(this);
    if(leave)
    {
        resize( m_Pixmap.size() );
        //setMask( m_Pixmap.mask() );
        painter.drawPixmap(0,0, m_Pixmap);
        move(x+(m_Pixmap1.size().width()-m_Pixmap.size().width())/2,y+(m_Pixmap1.size().width()-m_Pixmap.size().width())/2);
    }
   else
    {
        resize( m_Pixmap1.size() );
        //setMask( m_Pixmap1.mask() );
        painter.drawPixmap(0, 0, m_Pixmap1);
        move(x,y);
        this->setToolTip(iconTip);
    }
}

void IconButton::leaveEvent(QEvent *event)
{
    //鼠标离开窗口时是普通的指针
    setCursor(Qt::ArrowCursor);
    leave=true;
    update();
}

void IconButton::enterEvent(QEvent *event)
{
    //鼠标留在窗口上时是一个手指
    setCursor(Qt::PointingHandCursor);
    leave=false;
    update();
}
