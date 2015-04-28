#include "musicplayer.h"
#include "ui_musicplayer.h"
#include <QtGui>
#include <QTime>
#include "playlist.h"
#include "musiclrc.h"
#include "iconButton.h"
#include <QTextCodec>
#include <QMenu>//���ڴ���ϵͳ���̲˵�
#include <QCloseEvent>
#include "setwidget.h"
#include "ui_setWidget.h"
#include <QDebug>

MusicPlayer::MusicPlayer(QWidget *parent) :
        QWidget(parent),ui(new Ui::MusicPlayer)
{ 
    ui->setupUi(this);
    this->setWindowOpacity(1);
    this->setWindowFlags(Qt::FramelessWindowHint);
    init_ui();

    press=false;
    playmod=1;
    i=0;
}

MusicPlayer::~MusicPlayer()
{
    delete ui;
}

void MusicPlayer::init_ui()
{
    setWindowTitle(tr("���찮����"));

    setFixedSize(800,600);
    move(400,60);
    setStyleSheet("background-color:lightblue");

    closeButton=new IconButton(":/images/largeclose.png",":/images/smallclose.png",this);
    closeButton->setPosition(770,2);
    closeButton->setIconTip(tr("�ر�"));
    connect(closeButton,SIGNAL(isclicked()),this,SLOT(close()));
     //����ý��ͼ
    mediaObject = new Phonon::MediaObject(this);
    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    Phonon::createPath(mediaObject, audioOutput);
    connect(mediaObject,SIGNAL(tick(qint64)),this,SLOT(updateTime(qint64)));

    modAction=new QAction(this);
    modAction->setToolTip(tr("�б�ѭ��"));
    modAction->setIcon(QIcon(":/images/listcircle.png"));
    connect(modAction,SIGNAL(triggered()),this,SLOT(setMod()));

    previousAction=new QAction(this);
    previousAction->setText(tr("��һ��"));
    previousAction->setIcon(QIcon(":/images/previous.png"));
    connect(previousAction,SIGNAL(triggered()),this,SLOT(previousSong()));

    playAction=new QAction(this);
    playAction->setText(tr("����"));
    playAction->setIcon(QIcon(":/images/pause.png"));
    connect(playAction,SIGNAL(triggered()),this,SLOT(playOrpause()));

    nextAction=new QAction(this);
    nextAction->setText(tr("��һ��"));
    nextAction->setIcon(QIcon(":/images/next.png"));
    connect(nextAction,SIGNAL(triggered()),this,SLOT(nextSong()));

    volumeSlider=new Phonon::VolumeSlider(audioOutput,this);
    volumeSlider->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    openAction=new QAction(this);
    openAction->setText(tr("�������ļ�"));
    openAction->setIcon(QIcon(":/images/open.png"));
    connect(openAction,SIGNAL(triggered()),this,SLOT(openFile()));

    likeButton=new IconButton(":/images/smalllove.png",":/images/largelove.png",this);
    likeButton->setPosition(740,2);
    likeButton->setIconTip(tr("��ϲ���ĸ���"));
    connect(likeButton,SIGNAL(isclicked()),this,SLOT(whatiLike()));

    lrcButton=new IconButton(":/images/largelrc.png",":/images/smalllrc.png",this);
    lrcButton->setPosition(710,2);
    lrcButton->setIconTip(tr("��ʾ������"));
    connect(lrcButton,SIGNAL(isclicked()),this,SLOT(showLrc()));

    setButton=new IconButton(":/images/largeset.png",":/images/smallset.png",this);
    setButton->setPosition(680,0);
    setButton->setIconTip(tr("����"));
    connect(setButton,SIGNAL(isclicked()),this,SLOT(setPlayer()));

    listAction=new QAction(this);
    listAction->setText(tr("��ʾ�����б�"));
    listAction->setIcon(QIcon(":/images/list.png"));
    connect(listAction,SIGNAL(triggered()),this,SLOT(showPlayList()));

    lrc = new MusicLrc(this,900,60,true);

    namePoint.setX(-70);
    namePoint.setY(60);
    disPoint.setX(0);
    disPoint.setY(25);
    constPoint.setX(40);
    constPoint.setY(140);
    lrc->move(400,640);

    mLrc= new MusicLrc(this,400,40,false);
    mLrc->move(constPoint);
    mLrc->show();

    lrc1 = new MusicLrc(this,400,40,false);
    lrc1->move(constPoint+disPoint);
    lrc1->show();

    lrc2 = new MusicLrc(this,400,40,false);
    lrc2->move(constPoint+2*disPoint);
    lrc2->show();

    lrc3 = new MusicLrc(this,400,40,false);
    lrc3->move(constPoint+3*disPoint);
    lrc3->show();

    lrc4 = new MusicLrc(this,400,40,false);
    lrc4->move(constPoint+4*disPoint);
    lrc4->show();

    lrc5 = new MusicLrc(this,400,40,false);
    lrc5->move(constPoint+5*disPoint);
    lrc5->show();

    lrc6 = new MusicLrc(this,400,40,false);
    lrc6->move(constPoint+6*disPoint);
    lrc6->show();

    lrc7 = new MusicLrc(this,400,40,false);
    lrc7->move(constPoint+7*disPoint);
    lrc7->show();

    lrc8 = new MusicLrc(this,400,40,false);
    lrc8->move(constPoint+8*disPoint);
    lrc8->show();

    lrc9 = new MusicLrc(this,400,40,false);
    lrc9->move(constPoint+9*disPoint);
    lrc9->show();

    lrc10 = new MusicLrc(this,400,40,false);
    lrc10->move(constPoint+10*disPoint);
    lrc10->show();

    musicName = new MusicLrc(this,400,40,false);
    musicName->move(constPoint-namePoint);
    musicName->show();

    seekSlider = new Phonon::SeekSlider(this);//����������
    seekSlider->setMediaObject(mediaObject);
    totalTimeLabel=new QLabel(tr("00:00"),this);
    timeLabel=new QLabel(tr("00:00"),this);
    timeLabel->setFixedHeight(60);

    QToolBar *bar1=new QToolBar;
    bar1->addAction(openAction);
    bar1->addAction(modAction);
    bar1->addAction(previousAction);
    bar1->addAction(playAction);
    bar1->addAction(nextAction);
    bar1->addWidget(totalTimeLabel);
    bar1->addWidget(seekSlider);
    bar1->addWidget(timeLabel);
    bar1->addSeparator();
    bar1->addWidget(volumeSlider); 
    bar1->addAction(listAction);

    QVBoxLayout *mainLayout=new QVBoxLayout;
    mainLayout->addWidget(ui->view);
    mainLayout->addWidget(bar1);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    playList=new PlayList(this);

    connect(playList->tableWidget, SIGNAL(cellClicked(int, int)), this, SLOT(tableWidgetClicked(int)));
    connect(playList,SIGNAL(playListClear()),this,SLOT(clearSources()));
    // ������������ý�����Ϣ��Ԫ��Ϣ������
    metaInformationResolver = new Phonon::MediaObject(this);
    // ��Ҫ��AudioOutput���Ӻ����ʹ��metaInformationResolver����ȡ��������ʱ��
    Phonon::AudioOutput *metaInformationAudioOutput =
            new Phonon::AudioOutput(Phonon::MusicCategory, this);
    Phonon::createPath(metaInformationResolver, metaInformationAudioOutput);
    connect(metaInformationResolver, SIGNAL(stateChanged(Phonon::State, Phonon::State)),
            this, SLOT(metaStateChanged(Phonon::State, Phonon::State)));
    connect(mediaObject,SIGNAL(aboutToFinish()),this,SLOT(aboutToFinish()));
    //mediaObject->setCurrentSource(Phonon::MediaSource("../MusicPlayer/music/beyond.mp3"));
    settingWidget=new SetWidget(this,this);
    settingWidget->hide();

    LoadMusicListData();
    LoadSettingData();
    if(sources.size()==0)
    {
        playAction->setEnabled(false);
        previousAction->setEnabled(false);
        nextAction->setEnabled(false);
    }

    trayIcon=new QSystemTrayIcon(QIcon(":/images/trayIcon.png"),this);
    trayIcon->setToolTip(tr("���찮���ֲ�����"));
    QMenu *menu=new QMenu;
    QList<QAction *> actions;
    actions<<playAction<<previousAction<<nextAction;
    menu->addActions(actions);
    menu->addAction(tr("�˳�"),this,SLOT(saveAndQuit()));
    trayIcon->setContextMenu(menu);
    // ����ͼ�걻�������д���
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));
    // ��ʾ����ͼ��
    trayIcon->show();
}
void MusicPlayer::LoadMusicListData()
{
    QFile file("musiclist.dat");
    if(file.open(QIODevice::ReadOnly)==true)
        qDebug("open success");
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_4_0);
    qint32 filelabel;
    QStringList musicFileList;

    in>>filelabel>>musicFileList;
    if(filelabel==0x56432659&&file.size()>0)
    {
        if (musicFileList.isEmpty()){
            qDebug("list is empty");
        }
        else
       {
            // ��ȡ��ǰý��Դ�б�Ĵ�С
            int index = sources.size();
            qDebug("index :%d",index);

            // ���򿪵������ļ���ӵ�ý��Դ�б��
            foreach (QString string, musicFileList) {
                Phonon::MediaSource source(string);
                sources.append(source);
            }
            qDebug("sources.size() :%d",sources.size());
            // ���ý��Դ�б�Ϊ�գ����¼���ĵ�һ��ý��Դ��Ϊ��ǰý��Դ��
            // ��ʱ�ᷢ��stateChanged()�źţ��Ӷ�����metaStateChanged()��������ý��Դ�Ľ���
            if (!sources.isEmpty())
            {
                qDebug("source is not empty");
                metaInformationResolver->setCurrentSource(sources.at(index));
            }
        }

    }
    file.close();
}
void MusicPlayer::LoadSettingData()
{

    QFile comboxfile("setting.dat");
    if(comboxfile.open(QIODevice::ReadOnly)==true)
        qDebug("open success");
    QDataStream in(&comboxfile);
    in.setVersion(QDataStream::Qt_4_0);
    qint32 comboxlabel;
    QString comboxData;
    QString fontStr;
    QColor ColorData;
    qint16 fontSize;
    in>>comboxlabel>>comboxData>>fontStr>>ColorData>>fontSize;
    if(comboxlabel==0x01020304&&comboxfile.size()>0)
    {
        qDebug()<<"comboxdata"<<comboxData<<"fontStr:"<<fontStr;
        qDebug("fontSize is %d",fontSize);
        setStyleSheet("background-color:" + comboxData);

        lrc->font.setFamily(fontStr);
        mLrc->font.setFamily(fontStr);
        lrc1->font.setFamily(fontStr);
        lrc2->font.setFamily(fontStr);
        lrc3->font.setFamily(fontStr);
        lrc4->font.setFamily(fontStr);
        lrc5->font.setFamily(fontStr);
        lrc6->font.setFamily(fontStr);
        lrc7->font.setFamily(fontStr);
        lrc8->font.setFamily(fontStr);
        lrc9->font.setFamily(fontStr);
        lrc10->font.setFamily(fontStr);

        lrc->linearGradient.setColorAt(0.1,ColorData);
        lrc->linearGradient.setColorAt(0.5,ColorData);
        lrc->linearGradient.setColorAt(0.9,ColorData);

        mLrc->linearGradient.setColorAt(0.1,ColorData);
        mLrc->linearGradient.setColorAt(0.5,ColorData);
        mLrc->linearGradient.setColorAt(0.9,ColorData);

        lrc1->linearGradient.setColorAt(0.1,ColorData);
        lrc1->linearGradient.setColorAt(0.5,ColorData);
        lrc1->linearGradient.setColorAt(0.9,ColorData);

        lrc2->linearGradient.setColorAt(0.1,ColorData);
        lrc2->linearGradient.setColorAt(0.5,ColorData);
        lrc2->linearGradient.setColorAt(0.9,ColorData);

        lrc3->linearGradient.setColorAt(0.1,ColorData);
        lrc3->linearGradient.setColorAt(0.5,ColorData);
        lrc3->linearGradient.setColorAt(0.9,ColorData);

        lrc4->linearGradient.setColorAt(0.1,ColorData);
        lrc4->linearGradient.setColorAt(0.5,ColorData);
        lrc4->linearGradient.setColorAt(0.9,ColorData);

        lrc5->linearGradient.setColorAt(0.1,ColorData);
        lrc5->linearGradient.setColorAt(0.5,ColorData);
        lrc5->linearGradient.setColorAt(0.9,ColorData);

        lrc6->linearGradient.setColorAt(0.1,ColorData);
        lrc6->linearGradient.setColorAt(0.5,ColorData);
        lrc6->linearGradient.setColorAt(0.9,ColorData);

        lrc7->linearGradient.setColorAt(0.1,ColorData);
        lrc7->linearGradient.setColorAt(0.5,ColorData);
        lrc7->linearGradient.setColorAt(0.9,ColorData);

        lrc8->linearGradient.setColorAt(0.1,ColorData);
        lrc8->linearGradient.setColorAt(0.5,ColorData);
        lrc8->linearGradient.setColorAt(0.9,ColorData);

        lrc9->linearGradient.setColorAt(0.1,ColorData);
        lrc9->linearGradient.setColorAt(0.5,ColorData);
        lrc9->linearGradient.setColorAt(0.9,ColorData);

        lrc10->linearGradient.setColorAt(0.1,ColorData);
        lrc10->linearGradient.setColorAt(0.5,ColorData);
        lrc10->linearGradient.setColorAt(0.9,ColorData);

        musicName->linearGradient.setColorAt(0.1,ColorData);
        musicName->linearGradient.setColorAt(0.5,ColorData);
        musicName->linearGradient.setColorAt(0.9,ColorData);

        lrc->font.setPointSize(fontSize+15);

    }
    comboxfile.close();
}

void MusicPlayer::updateTime(qint64 time)
{
    qint64 totalTimeValue = mediaObject->totalTime();
    QTime totalTime(0, (totalTimeValue / 60000) % 60, (totalTimeValue / 1000) % 60);
    QTime currentTime(0, (time / 60000) % 60, (time / 1000) % 60);
    QString str1 = currentTime.toString("mm:ss");
    QString str2=totalTime.toString("mm:ss");
    timeLabel->setText(str1);
    totalTimeLabel->setText(str2);
    // ��ȡ����ʱ���Ӧ�ĸ��
    if(!lrcMap.isEmpty()) {
        // ��ȡ��ǰʱ���ڸ���е�ǰ������ʱ���
        qint64 previous = 0;
        qint64 later = 0;
        int i=0;
        foreach (qint64 value, lrcMap.keys()) {
            if (time >= value) {
                previous = value;
                i++;
                if(i==lrcMap.count()-10)
                {
                    i=lrcMap.count()-11;
                }
            } else {
                later = value;
                break;
            }

        }
        qDebug("i=%d",i);
        // �ﵽ���һ��,��later����Ϊ������ʱ���ֵ
        if (later == 0)
            later = totalTimeValue;

        // ��ȡ��ǰʱ������Ӧ�ĸ������
        QString currentLrc = lrcMap.value(previous);
        if(i==0)i=1;
        mLrc->setText(lrcMap.value(timeList.at(0+i-1)));
        lrc1->setText(lrcMap.value(timeList.at(1+i-1)));
        lrc2->setText(lrcMap.value(timeList.at(2+i-1)));
        lrc3->setText(lrcMap.value(timeList.at(3+i-1)));
        lrc4->setText(lrcMap.value(timeList.at(4+i-1)));
        lrc5->setText(lrcMap.value(timeList.at(5+i-1)));
        lrc6->setText(lrcMap.value(timeList.at(6+i-1)));
        lrc7->setText(lrcMap.value(timeList.at(7+i-1)));
        lrc8->setText(lrcMap.value(timeList.at(8+i-1)));
        lrc9->setText(lrcMap.value(timeList.at(9+i-1)));
        lrc10->setText(lrcMap.value(timeList.at(10+i-1)));
        musicName->setText(QFileInfo(mediaObject->
                                   currentSource().fileName()).baseName());

        // û������ʱ
        if(currentLrc.length() < 2)
            currentLrc = tr("���찮���֡�Designed by GQL");
        // ������µ�һ�и�ʣ���ô���¿�ʼ��ʾ�������
        if(currentLrc != lrc->text()) {
            lrc->setText(currentLrc);
            qint64 intervalTime = later - previous;
            lrc->startLrcMask(intervalTime);
            mLrc->startLrcMask(intervalTime);
        }
    } else {  // ���û�и���ļ������ڶ�����ǩ����ʾ��������
        musicName->setText(QFileInfo(mediaObject->
                                   currentSource().fileName()).baseName());
      mLrc->clear();
      lrc1->clear();
      lrc2->clear();
      lrc3->clear();
      lrc4->clear();
      lrc5->clear();
      lrc6->clear();
      lrc7->clear();
      lrc8->clear();
      lrc9->clear();
      lrc10->clear();
    }
}
void MusicPlayer::playOrpause()
{
    if(mediaObject->state() == Phonon::PlayingState){
        mediaObject->pause();
        playAction->setIcon(QIcon(":/images/pause.png"));
    }
    else{
        mediaObject->play();
        resolveLrc(mediaObject->currentSource().fileName());
        playAction->setIcon(QIcon(":/images/play.png"));
    }

}

void MusicPlayer::openFile(){

    // ��ϵͳ����Ŀ¼�򿪶�������ļ�
    QStringList list = QFileDialog::getOpenFileNames(this, tr("�������ļ�"),
                      QDesktopServices::storageLocation(QDesktopServices::MusicLocation));

    if (list.isEmpty())
        return;
    offerToSave=list;
    // ��ȡ��ǰý��Դ�б�Ĵ�С
    int index = sources.size();
    qDebug("index :%d",index);

    // ���򿪵������ļ���ӵ�ý��Դ�б��
    foreach (QString string, list) {
        Phonon::MediaSource source(string);
        sources.append(source);
    }
    // ���ý��Դ�б�Ϊ�գ����¼���ĵ�һ��ý��Դ��Ϊ��ǰý��Դ��
    // ��ʱ�ᷢ��stateChanged()�źţ��Ӷ�����metaStateChanged()��������ý��Դ�Ľ���
    if (!sources.isEmpty())
    {
        metaInformationResolver->setCurrentSource(sources.at(index));
    }

}
void MusicPlayer::setMod(){

    qDebug("setMod");
    switch(i){
        case 1: playmod=1;
                modAction->setIcon(QIcon(":/images/listcircle.png"));
                modAction->setToolTip(tr("�б�ѭ��"));
                qDebug("listCircle is true");
                break;
        case 0: playmod=2;
                modAction->setIcon(QIcon(":/images/random.png"));
                modAction->setToolTip(tr("�������"));
                qDebug("randomPlay is true");
                break;
        case 2: playmod=3;
                modAction->setIcon(QIcon(":/images/singlecircle.png"));
                modAction->setToolTip(tr("����ѭ��"));
                qDebug("singleCircle is true");
                break;
        default:break;
    }
    i++;
    if(i>=3)i=0;
}
void MusicPlayer::previousSong(){

    qDebug("previousSong");
    int index=sources.indexOf(mediaObject->currentSource())-1;
    qDebug("index:%d",index);
    if(index<0){
      mediaObject->setCurrentSource(sources.at(sources.size()-1));
      playList->tableWidget->selectRow(sources.size()-1);
    }
    else{
        mediaObject->setCurrentSource(sources.at(index));
        playList->tableWidget->selectRow(index);
    }
    mediaObject->play();
    resolveLrc(mediaObject->currentSource().fileName());
    playOrpause();
}
void MusicPlayer::nextSong(){
    int index=sources.indexOf(mediaObject->currentSource())+1;
    qDebug("index:%d",index);
    qDebug("sourcessize:%d",sources.size());
    if(index>=sources.size()){
        mediaObject->setCurrentSource(sources.at(0));
        playList->tableWidget->selectRow(0);
    }
    else{
        mediaObject->setCurrentSource(sources.at(index));
        playList->tableWidget->selectRow(index);
    }
    mediaObject->play();
    resolveLrc(mediaObject->currentSource().fileName());
    playOrpause();
}
void MusicPlayer::whatiLike(){

    qDebug("iLike");
}
void MusicPlayer::showLrc(){

    qDebug("showLrc");
    if (lrc->isHidden())
        lrc->show();
    else
        lrc->hide();
}
void MusicPlayer::setPlayer(){

    qDebug("setPlayer");
    if(settingWidget->isHidden())
    {
      settingWidget->show();
    }
    else
    {
       settingWidget->hide();
    }
}
void MusicPlayer::showPlayList(){

    qDebug("showPlayList");
    if(playList->isHidden()){
        playList->show();
    }
    else{
        playList->hide();
    }
}

void MusicPlayer::metaStateChanged(Phonon::State newState, Phonon::State oldState)
{
    // ����״̬�����ý��Դ�б��г�ȥ����ӵ�ý��Դ
    if(newState == Phonon::ErrorState) {
        QMessageBox::warning(this, tr("���ļ�ʱ����"), metaInformationResolver->errorString());
        while (!sources.isEmpty() &&
               !(sources.takeLast() == metaInformationResolver->currentSource()))
        {};
        return;
    }

    // ����Ȳ�����ֹͣ״̬Ҳ��������ͣ״̬����ֱ�ӷ���
    if(newState != Phonon::StoppedState && newState != Phonon::PausedState)
        return;

    // ���ý��Դ���ʹ�����ֱ�ӷ���
    if(metaInformationResolver->currentSource().type() == Phonon::MediaSource::Invalid)
        return;

    // ��ȡý����Ϣ
    QMap<QString, QString> metaData = metaInformationResolver->metaData();

    // ��ȡ���⣬���Ϊ�գ���ʹ���ļ���
    QString title = metaData.value("TITLE");
    if (title == "") {
        QString str = metaInformationResolver->currentSource().fileName();
        title = QFileInfo(str).baseName();
    }
    QTableWidgetItem *titleItem = new QTableWidgetItem(title);
    // ����������ɱ༭
    titleItem->setFlags(titleItem->flags() ^ Qt::ItemIsEditable);
    // ��ȡ��������Ϣ
    QTableWidgetItem *artistItem = new QTableWidgetItem(metaData.value("ARTIST"));
    artistItem->setFlags(artistItem->flags() ^ Qt::ItemIsEditable);

    int currentRow = playList->tableWidget->rowCount();
    playList->tableWidget->insertRow(currentRow);
    playList->tableWidget->setItem(currentRow, 0, artistItem);
    playList->tableWidget->setItem(currentRow, 1, titleItem);

    // �����ӵ�ý��Դ��û�н����꣬��ô����������һ��ý��Դ
    int index = sources.indexOf(metaInformationResolver->currentSource()) + 1;
    if (sources.size() > index) {
        metaInformationResolver->setCurrentSource(sources.at(index));
    }
    else
    {
        if (playList->tableWidget->selectedItems().isEmpty())
        {
            if (mediaObject->state() != Phonon::PlayingState &&
                    mediaObject->state() != Phonon::PausedState) {
                mediaObject->setCurrentSource(sources.at(0));
                playList->tableWidget->selectRow(0);
            }
        }

        playAction->setEnabled(true);
        previousAction->setEnabled(true);
        nextAction->setEnabled(true);
    }
    QString str="("+ tr("%1").arg(sources.count()) + ")" + "                 ";
    playList->numLabel->setText(str);
}

// ����LRC��ʣ���stateChanged()������Phonon::PlayingState����aboutToFinish()�����е����˸ú���
void MusicPlayer::resolveLrc(const QString &sourceFileName)
{
    // �������ǰ������
    lrcMap.clear();
    timeList.clear();

    // ��ȡLRC��ʵ��ļ���
    if(sourceFileName.isEmpty())
        return ;
    QString fileName = sourceFileName;
    QString lrcFileName = fileName.remove(fileName.right(3)) + "lrc";

    // �򿪸���ļ�
    QFile file(lrcFileName);
    if (!file.open(QIODevice::ReadOnly)) {
        lrc->setText(QFileInfo(mediaObject->currentSource().fileName()).baseName()
                     + tr(" --δ�ҵ�����ļ���"));
        mLrc->setText(QFileInfo(mediaObject->currentSource().fileName()).baseName()
                     + tr(" --δ�ҵ�����ļ���"));
        return ;
    }
    // �����ַ�������
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    // ��ȡȫ�������Ϣ
    QString allText = QString(file.readAll());
    // �رո���ļ�
    file.close();
    // ����ʰ��зֽ�Ϊ����б�
    QStringList lines = allText.split("\n");

    // ʹ��������ʽ��ʱ���ǩ�͸�����ݷ���
    QRegExp rx("\\[\\d{2}:\\d{2}\\.\\d{2}\\]");
    foreach (QString oneLine, lines) {
        // ���ڵ�ǰ�еĸ�ʵı����н�ʱ����������������ͻ���˸���ı�
        QString temp = oneLine;
        qint64 totalTime;
        temp.replace(rx, "");
        // Ȼ�����λ�ȡ��ǰ���е�����ʱ���ǩ�����ֱ������ı�����QMap��
        int pos = rx.indexIn(oneLine, 0);
        while (pos != -1) {
            QString cap = rx.cap(0);
            // ��ʱ���ǩת��Ϊʱ����ֵ���Ժ���Ϊ��λ
            QRegExp regexp;
            regexp.setPattern("\\d{2}(?=:)");
            regexp.indexIn(cap);
            int minute = regexp.cap(0).toInt();
            regexp.setPattern("\\d{2}(?=\\.)");
            regexp.indexIn(cap);
            int second = regexp.cap(0).toInt();
            regexp.setPattern("\\d{2}(?=\\])");
            regexp.indexIn(cap);
            int millisecond = regexp.cap(0).toInt();
            totalTime = minute * 60000 + second * 1000 + millisecond * 10;
            // ���뵽lrcMap��
            lrcMap.insert(totalTime, temp);
            pos += rx.matchedLength();
            pos = rx.indexIn(oneLine, pos);
            timeList.push_back(totalTime);
        }
    }
    // ���lrcMapΪ��
    if (lrcMap.isEmpty()) {
        lrc->setText(QFileInfo(mediaObject->currentSource().fileName()).baseName()
                     + tr(" --����ļ����ݴ���"));
        mLrc->setText(QFileInfo(mediaObject->currentSource().fileName()).baseName()
                     + tr(" --����ļ����ݴ���"));
        return;
    }
}


void MusicPlayer::tableWidgetClicked(int row)
{
    qDebug("clicked");
    // ���Ȼ�ȡý�����ǰ��״̬��Ȼ��ֹͣ���Ų���ղ��Ŷ���
    bool wasPlaying = mediaObject->state() == Phonon::PlayingState;
    mediaObject->stop();
    mediaObject->clearQueue();

    // ��������Ĳ����б��е��кŴ���ý��Դ�б�Ĵ�С����ֱ�ӷ���
    if(row >= sources.size())
        return;
    // ���õ������ж�Ӧ��ý��ԴΪý�����ĵ�ǰý��Դ
    mediaObject->setCurrentSource(sources.at(row));
    // �����ǰý������ڲ���״̬����ô��ʼ����ѡ�е���Ŀ
    if (wasPlaying)
    {
        mediaObject->play();
        mLrc->stopLrcMask();
        resolveLrc(mediaObject->currentSource().fileName());
    }
}

void MusicPlayer::aboutToFinish()
{
    qDebug("about to finish");
    if(sources.size()==0)
    {
        mediaObject->stop();
        playOrpause();
        playAction->setEnabled(false);
    }
    else
    {
        if(playmod==1)
        {
            qDebug("listcircle");
            int index=sources.indexOf(mediaObject->currentSource())+1;
            if(sources.size()>index)
            {
                mediaObject->enqueue(sources.at(index));
                mediaObject->seek(mediaObject->totalTime());
                playList->tableWidget->selectRow(index);
                // ֹͣ������ֲ����½������
                lrc->stopLrcMask();
                mLrc->stopLrcMask();
                resolveLrc(sources.at(index).fileName());
            }
            else
            {
               mediaObject->setCurrentSource(sources.at(0));
               playList->tableWidget->selectRow(0);
               mediaObject->play();
               // ֹͣ������ֲ����½������
               lrc->stopLrcMask();
               mLrc->stopLrcMask();
               resolveLrc(mediaObject->currentSource().fileName());
            }
        }
        else if(playmod==2&&sources.size()>1){
            qDebug("random");
            int index=qrand()%(sources.size()-1);
            mediaObject->enqueue(sources.at(index));
            mediaObject->seek(mediaObject->totalTime());
            playList->tableWidget->selectRow(index);
            // ֹͣ������ֲ����½������
            lrc->stopLrcMask();
            mLrc->stopLrcMask();
            resolveLrc(sources.at(index).fileName());
        }
        else if(playmod==3)
        {
            qDebug("singlecircle");
            int index=sources.indexOf(mediaObject->currentSource());
            mediaObject->enqueue(sources.at(index));
            mediaObject->seek(mediaObject->totalTime());
            playList->tableWidget->selectRow(index);
            // ֹͣ������ֲ����½������
            lrc->stopLrcMask();
            mLrc->stopLrcMask();
            resolveLrc(sources.at(index).fileName());
        }
    }

}
void MusicPlayer::clearSources()
{
    mediaObject->stop();
    sources.clear();
    playOrpause();
    if(sources.count()==0)
    {
        if (mediaObject->state() != Phonon::PlayingState &&
                mediaObject->state() != Phonon::PausedState) {
            playAction->setEnabled(false);
        }
        previousAction->setEnabled(false);
        nextAction->setEnabled(false);
    }
    QString str="("+ tr("%1").arg(sources.count()) + ")" + "         ";
    playList->numLabel->setText(str);
}

void MusicPlayer::saveAndQuit()
{
    saveMusicList();
    saveSettingWidgetData();
    qApp->quit();
}

void MusicPlayer::saveMusicList()
{
    QFile file("musiclist.dat");
    file.open(QIODevice::ReadWrite);
    if(offerToSave.isEmpty())
    {
        QDataStream in(&file);
        qint32 magic;
        QStringList list;
        in>>magic>>list;
        offerToSave=list;
    }
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_0);
    out<<(qint32)0x56432659;
    out<<offerToSave;
    file.close();
}
void MusicPlayer::saveSettingWidgetData()
{
    QFile comboxfile("setting.dat");
    comboxfile.open(QIODevice::ReadWrite);
    QDataStream out(&comboxfile);
    qint32 comboxlable=0x01020304;
    out.setVersion(QDataStream::Qt_4_0);
    out<<comboxlable<<settingWidget->ui->comboBox->itemText(settingWidget->ui->comboBox->currentIndex());
    out<<settingWidget->ui->fontComboBox->currentFont().toString();
    out<<settingWidget->LrcColor;
    qint16 fontsize=settingWidget->ui->sizecomboBox->itemText(settingWidget->ui->sizecomboBox->currentIndex()).toDouble();
    qDebug("size is %d",fontsize);
    out<<fontsize;
    qDebug()<<settingWidget->ui->comboBox->itemText(settingWidget->ui->comboBox->currentIndex());
    comboxfile.close();
}

// ϵͳ����ͼ�걻����
void MusicPlayer::trayIconActivated(QSystemTrayIcon::ActivationReason activationReason)
{
    // ���������ϵͳ����ͼ��,����ʾӦ�ó������
    if (activationReason == QSystemTrayIcon::Trigger) {
        show();
    }
}

// �ر��¼�������
void MusicPlayer::closeEvent(QCloseEvent *event)
{
    if (isVisible()) {
        hide();
        trayIcon->showMessage(tr("���찮����"), tr(""));
        event->ignore();
    }
}
void MusicPlayer::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        oldPos = event->globalPos();
        press = true;
    }
}
void MusicPlayer::mouseMoveEvent(QMouseEvent *event)

{
    if (press)
    {
        this->move(this->pos() + event->globalPos() - oldPos);
        oldPos = event->globalPos();
    }
}

void MusicPlayer::mouseReleaseEvent(QMouseEvent *event)

{
    press = false;
}




