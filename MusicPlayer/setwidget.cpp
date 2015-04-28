#include "setwidget.h"
#include <QtGui>
#include "ui_setWidget.h"
#include "musicplayer.h"
#include "musiclrc.h"
#include "ui_musicplayer.h"

SetWidget::SetWidget(QWidget *parent,MusicPlayer *MP):
        QWidget(parent),ui(new Ui::SetWidget)
{
    ui->setupUi(this);
    this->MP=MP;
    i=0;
    setWindowFlags(Qt::Window  | Qt::WindowTitleHint);
    setWindowTitle(tr("²¥·ÅÆ÷ÉèÖÃ"));
    setFixedSize(340,210);
    move(600,120);
    time=new QTimer(this);
    connect(time,SIGNAL(timeout()),this,SLOT(changeBackground()));
    connect(ui->okButton,SIGNAL(clicked()),this,SLOT(saveAll()));
    connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->chooseColorButton,SIGNAL(clicked()),this,SLOT(chooseColor()));
}

void SetWidget::saveAll()
{
    QString currentString=ui->comboBox->itemText(ui->comboBox->currentIndex());
    MP->setStyleSheet("background-color:" + currentString);
    QFont currentFont=ui->fontComboBox->currentFont();
    QString fontString=currentFont.toString();
    MP->lrc->font.setFamily(fontString);
    MP->mLrc->font.setFamily(fontString);
    MP->lrc1->font.setFamily(fontString);
    MP->lrc2->font.setFamily(fontString);
    MP->lrc3->font.setFamily(fontString);
    MP->lrc4->font.setFamily(fontString);
    MP->lrc5->font.setFamily(fontString);
    MP->lrc6->font.setFamily(fontString);
    MP->lrc7->font.setFamily(fontString);
    MP->lrc8->font.setFamily(fontString);
    MP->lrc9->font.setFamily(fontString);
    MP->lrc10->font.setFamily(fontString);
    QString sizeString=ui->sizecomboBox->itemText(ui->sizecomboBox->currentIndex());
    int fontSize=sizeString.toDouble();
    qDebug("fontsize :%d",fontSize);
    MP->lrc->font.setPointSize(fontSize+15);
    MP->lrc->linearGradient.setColorAt(0.1,LrcColor);
    MP->lrc->linearGradient.setColorAt(0.5,LrcColor);
    MP->lrc->linearGradient.setColorAt(0.9,LrcColor);

    MP->mLrc->linearGradient.setColorAt(0.1,LrcColor);
    MP->mLrc->linearGradient.setColorAt(0.5,LrcColor);
    MP->mLrc->linearGradient.setColorAt(0.9,LrcColor);

    MP->lrc1->linearGradient.setColorAt(0.1,LrcColor);
    MP->lrc1->linearGradient.setColorAt(0.5,LrcColor);
    MP->lrc1->linearGradient.setColorAt(0.9,LrcColor);

    MP->lrc2->linearGradient.setColorAt(0.1,LrcColor);
    MP->lrc2->linearGradient.setColorAt(0.5,LrcColor);
    MP->lrc2->linearGradient.setColorAt(0.9,LrcColor);

    MP->lrc3->linearGradient.setColorAt(0.1,LrcColor);
    MP->lrc3->linearGradient.setColorAt(0.5,LrcColor);
    MP->lrc3->linearGradient.setColorAt(0.9,LrcColor);

    MP->lrc4->linearGradient.setColorAt(0.1,LrcColor);
    MP->lrc4->linearGradient.setColorAt(0.5,LrcColor);
    MP->lrc4->linearGradient.setColorAt(0.9,LrcColor);

    MP->lrc5->linearGradient.setColorAt(0.1,LrcColor);
    MP->lrc5->linearGradient.setColorAt(0.5,LrcColor);
    MP->lrc5->linearGradient.setColorAt(0.9,LrcColor);

    MP->lrc6->linearGradient.setColorAt(0.1,LrcColor);
    MP->lrc6->linearGradient.setColorAt(0.5,LrcColor);
    MP->lrc6->linearGradient.setColorAt(0.9,LrcColor);

    MP->lrc7->linearGradient.setColorAt(0.1,LrcColor);
    MP->lrc7->linearGradient.setColorAt(0.5,LrcColor);
    MP->lrc7->linearGradient.setColorAt(0.9,LrcColor);

    MP->lrc8->linearGradient.setColorAt(0.1,LrcColor);
    MP->lrc8->linearGradient.setColorAt(0.5,LrcColor);
    MP->lrc8->linearGradient.setColorAt(0.9,LrcColor);

    MP->lrc9->linearGradient.setColorAt(0.1,LrcColor);
    MP->lrc9->linearGradient.setColorAt(0.5,LrcColor);
    MP->lrc9->linearGradient.setColorAt(0.9,LrcColor);

    MP->lrc10->linearGradient.setColorAt(0.1,LrcColor);
    MP->lrc10->linearGradient.setColorAt(0.5,LrcColor);
    MP->lrc10->linearGradient.setColorAt(0.9,LrcColor);

    MP->musicName->linearGradient.setColorAt(0.1,LrcColor);
    MP->musicName->linearGradient.setColorAt(0.5,LrcColor);
    MP->musicName->linearGradient.setColorAt(0.9,LrcColor);

    if(ui->checkBox->isChecked())
    {
        qDebug("time start");
        time->start(5000);
    }
    else{
        time->stop();
        qDebug("time stop");
    }
    close();
}

void SetWidget::chooseColor()
{
    QColor color=QColorDialog::getColor(Qt::blue);
    if(color.isValid())
    {
        LrcColor=color;
    }
}

void SetWidget::changeBackground()
{  
    switch(i)
    {
        case 0:MP->ui->view->setStyleSheet(QString::fromUtf8("border-image: url(:/images/background1.png);"));break;
        case 1:MP->ui->view->setStyleSheet(QString::fromUtf8("border-image: url(:/images/background2.png);"));break;
        case 2:MP->ui->view->setStyleSheet(QString::fromUtf8("border-image: url(:/images/background3.png);"));break;
        case 3:MP->ui->view->setStyleSheet(QString::fromUtf8("border-image: url(:/images/background4.png);"));break;
        case 4:MP->ui->view->setStyleSheet(QString::fromUtf8("border-image: url(:/images/background5.png);"));break;
        default:break;
    }
    i++;
    if(i>=5)i=0;
}
