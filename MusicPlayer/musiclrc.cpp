#include "musiclrc.h"
#include <QPainter>
#include <QTimer>
#include <QMouseEvent>
MusicLrc::MusicLrc(QWidget *parent,int w, int h,bool acceptEvent):
        QLabel(parent)
{
    this->w=w;
    this->h=h;
    this->acceptEvent=acceptEvent;
    if(acceptEvent)
    setWindowFlags(Qt::Window|Qt::FramelessWindowHint);
    else
    setWindowFlags(Qt::FramelessWindowHint);
    //setStyleSheet(QString::fromUtf8("border-image: url(:/images/background.png);"));
    setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(w,h);
    // ��ʵ����Խ������
    linearGradient.setStart(0, 10);
    linearGradient.setFinalStop(0, 40);
    linearGradient.setColorAt(0.1, QColor(14, 179, 255));
    linearGradient.setColorAt(0.5, QColor(114, 232, 255));
    linearGradient.setColorAt(0.9, QColor(14, 179, 255));
    // ���ֵ����Խ������
    maskLinearGradient.setStart(0, 10);
    maskLinearGradient.setFinalStop(0, 40);
    maskLinearGradient.setColorAt(0.1, QColor(222, 54, 4));
    maskLinearGradient.setColorAt(0.5, QColor(255, 72, 16));
    maskLinearGradient.setColorAt(0.9, QColor(222, 54, 4));
    // ��������
    font.setFamily("Times New Roman");
    font.setBold(true);
    font.setPointSize(12);
    // ���ö�ʱ��
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
    lrcMaskWidth = 0;
    lrcMaskWidthInterval = 0;
}


void MusicLrc::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setFont(font);
    // �Ȼ��Ƶײ����֣���Ϊ��Ӱ��������ʹ��ʾЧ�������������Ҹ����ʸ�
    painter.setPen(QColor(0, 0, 0, 200));
    painter.drawText(1, 1, w, h, Qt::AlignLeft, text());
    // ����������ƽ�������
    painter.setPen(QPen(linearGradient, 0));
    painter.drawText(0, 0, w, h, Qt::AlignLeft, text());

    // ���ø������
    painter.setPen(QPen(maskLinearGradient, 0));
    painter.drawText(0, 0, lrcMaskWidth, h, Qt::AlignLeft, text());
}

void MusicLrc::startLrcMask(qint64 intervalTime)
{
    // ��������ÿ��30�������һ�����ֵĿ�ȣ���Ϊ�������̫Ƶ��
    // ������CPUռ���ʣ������ʱ����̫���򶯻�Ч���Ͳ�������
    qreal count = intervalTime / 30;
    // ��ȡ����ÿ����Ҫ���ӵĿ�ȣ������800�ǲ����Ĺ̶����
    lrcMaskWidthInterval = 800 / count;
    lrcMaskWidth = 0;
    timer->start(30);
}
void MusicLrc::stopLrcMask()
{
    timer->stop();
    lrcMaskWidth = 0;
    update();
}

// ��������¼�������ʵ���˲������϶�
void MusicLrc::mousePressEvent(QMouseEvent *event)
{
    if(acceptEvent){
    if (event->button() == Qt::LeftButton)
        offset = event->globalPos() - frameGeometry().topLeft();
    }
}
void MusicLrc::mouseMoveEvent(QMouseEvent *event)
{
    if(acceptEvent)
    {
        if (event->buttons() & Qt::LeftButton)
        {
         setCursor(Qt::PointingHandCursor);
         move(event->globalPos() - offset);
        }
    }
}

// ��ʱ�����ʱ�������ֵĿ�ȣ���������ʾ
void MusicLrc::timeout()
{
    lrcMaskWidth += lrcMaskWidthInterval;
    update();
}
