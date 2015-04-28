#include "playlist.h"
#include <QTableWidget>
#include <QtGui>
#include <QTextCodec>

PlayList::PlayList(QWidget *parent):
        QWidget(parent)
{
    setWindowTitle(tr("播放列表"));
    setFixedSize(295,380);
    move(510,160);
    tableWidget=new QTableWidget;
    tableWidget->setRowCount(0);
    tableWidget->setColumnCount(2);


    listLabel=new QLabel(tr("                  播放列表"));
    numLabel=new QLabel(tr("(0)                 "));
    font.setFamily("Times New Roman");
    font.setBold(true);
    font.setPointSize(12);
    listLabel->setFont(font);
    numLabel->setFont(font);

    QStringList list;
    list<<tr("歌手")<<tr("歌名");
    tableWidget->setHorizontalHeaderLabels(list);
    tableWidget->setShowGrid(false);
    // 设置只能选择单行
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setColumnWidth(0,70);
    tableWidget->setColumnWidth(1,190);
    clearAction=new QAction(this);
    clearAction->setToolTip(tr("清空"));
    clearAction->setIcon(QIcon(":/images/clear.png"));
    connect(clearAction,SIGNAL(triggered()),this,SLOT(listClean()));

    QToolBar *listBar=new QToolBar;
    listBar->addWidget(listLabel);
    listBar->addWidget(numLabel);
    listBar->addAction(clearAction);

    QVBoxLayout *mainLayout=new QVBoxLayout;
    mainLayout->addWidget(listBar);
    mainLayout->addWidget(tableWidget);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);
    this->hide();
}

void PlayList::listClean()
{
    if(tableWidget->rowCount()==0){
        return;
    }
    while(tableWidget->rowCount()){
        tableWidget->removeRow(0);
    }
    emit playListClear();
}



