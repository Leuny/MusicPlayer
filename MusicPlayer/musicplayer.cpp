#include "musicplayer.h"
#include "ui_musicplayer.h"
#include <QtGui>
#include <QTime>
#include "playlist.h"
#include "musiclrc.h"
#include "iconButton.h"
#include <QTextCodec>
#include <QMenu>//用于创建系统托盘菜单
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
    setWindowTitle(tr("天天爱音乐"));

    setFixedSize(800,600);
    move(400,60);
    setStyleSheet("background-color:lightblue");

    closeButton=new IconButton(":/images/largeclose.png",":/images/smallclose.png",this);
    closeButton->setPosition(770,2);
    closeButton->setIconTip(tr("关闭"));
    connect(closeButton,SIGNAL(isclicked()),this,SLOT(close()));
     //创建媒体图
    mediaObject = new Phonon::MediaObject(this);
    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    Phonon::createPath(mediaObject, audioOutput);
    connect(mediaObject,SIGNAL(tick(qint64)),this,SLOT(updateTime(qint64)));

    modAction=new QAction(this);
    modAction->setToolTip(tr("列表循环"));
    modAction->setIcon(QIcon(":/images/listcircle.png"));
    connect(modAction,SIGNAL(triggered()),this,SLOT(setMod()));

    previousAction=new QAction(this);
    previousAction->setText(tr("上一首"));
    previousAction->setIcon(QIcon(":/images/previous.png"));
    connect(previousAction,SIGNAL(triggered()),this,SLOT(previousSong()));

    playAction=new QAction(this);
    playAction->setText(tr("播放"));
    playAction->setIcon(QIcon(":/images/pause.png"));
    connect(playAction,SIGNAL(triggered()),this,SLOT(playOrpause()));

    nextAction=new QAction(this);
    nextAction->setText(tr("下一首"));
    nextAction->setIcon(QIcon(":/images/next.png"));
    connect(nextAction,SIGNAL(triggered()),this,SLOT(nextSong()));

    volumeSlider=new Phonon::VolumeSlider(audioOutput,this);
    volumeSlider->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    openAction=new QAction(this);
    openAction->setText(tr("打开音乐文件"));
    openAction->setIcon(QIcon(":/images/open.png"));
    connect(openAction,SIGNAL(triggered()),this,SLOT(openFile()));

    likeButton=new IconButton(":/images/smalllove.png",":/images/largelove.png",this);
    likeButton->setPosition(740,2);
    likeButton->setIconTip(tr("我喜爱的歌曲"));
    connect(likeButton,SIGNAL(isclicked()),this,SLOT(whatiLike()));

    lrcButton=new IconButton(":/images/largelrc.png",":/images/smalllrc.png",this);
    lrcButton->setPosition(710,2);
    lrcButton->setIconTip(tr("显示桌面歌词"));
    connect(lrcButton,SIGNAL(isclicked()),this,SLOT(showLrc()));

    setButton=new IconButton(":/images/largeset.png",":/images/smallset.png",this);
    setButton->setPosition(680,0);
    setButton->setIconTip(tr("设置"));
    connect(setButton,SIGNAL(isclicked()),this,SLOT(setPlayer()));

    listAction=new QAction(this);
    listAction->setText(tr("显示播放列表"));
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

    seekSlider = new Phonon::SeekSlider(this);//歌曲进度条
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
    // 创建用来解析媒体的信息的元信息解析器
    metaInformationResolver = new Phonon::MediaObject(this);
    // 需要与AudioOutput连接后才能使用metaInformationResolver来获取歌曲的总时间
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
    trayIcon->setToolTip(tr("天天爱音乐播放器"));
    QMenu *menu=new QMenu;
    QList<QAction *> actions;
    actions<<playAction<<previousAction<<nextAction;
    menu->addActions(actions);
    menu->addAction(tr("退出"),this,SLOT(saveAndQuit()));
    trayIcon->setContextMenu(menu);
    // 托盘图标被激活后进行处理
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));
    // 显示托盘图标
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
            // 获取当前媒体源列表的大小
            int index = sources.size();
            qDebug("index :%d",index);

            // 将打开的音乐文件添加到媒体源列表后
            foreach (QString string, musicFileList) {
                Phonon::MediaSource source(string);
                sources.append(source);
            }
            qDebug("sources.size() :%d",sources.size());
            // 如果媒体源列表不为空，则将新加入的第一个媒体源作为当前媒体源，
            // 这时会发射stateChanged()信号，从而调用metaStateChanged()函数进行媒体源的解析
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
    // 获取当期时间对应的歌词
    if(!lrcMap.isEmpty()) {
        // 获取当前时间在歌词中的前后两个时间点
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
        // 达到最后一行,将later设置为歌曲总时间的值
        if (later == 0)
            later = totalTimeValue;

        // 获取当前时间所对应的歌词内容
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

        // 没有内容时
        if(currentLrc.length() < 2)
            currentLrc = tr("天天爱音乐—Designed by GQL");
        // 如果是新的一行歌词，那么重新开始显示歌词遮罩
        if(currentLrc != lrc->text()) {
            lrc->setText(currentLrc);
            qint64 intervalTime = later - previous;
            lrc->startLrcMask(intervalTime);
            mLrc->startLrcMask(intervalTime);
        }
    } else {  // 如果没有歌词文件，则在顶部标签中显示歌曲标题
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

    // 从系统音乐目录打开多个音乐文件
    QStringList list = QFileDialog::getOpenFileNames(this, tr("打开音乐文件"),
                      QDesktopServices::storageLocation(QDesktopServices::MusicLocation));

    if (list.isEmpty())
        return;
    offerToSave=list;
    // 获取当前媒体源列表的大小
    int index = sources.size();
    qDebug("index :%d",index);

    // 将打开的音乐文件添加到媒体源列表后
    foreach (QString string, list) {
        Phonon::MediaSource source(string);
        sources.append(source);
    }
    // 如果媒体源列表不为空，则将新加入的第一个媒体源作为当前媒体源，
    // 这时会发射stateChanged()信号，从而调用metaStateChanged()函数进行媒体源的解析
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
                modAction->setToolTip(tr("列表循环"));
                qDebug("listCircle is true");
                break;
        case 0: playmod=2;
                modAction->setIcon(QIcon(":/images/random.png"));
                modAction->setToolTip(tr("随机播放"));
                qDebug("randomPlay is true");
                break;
        case 2: playmod=3;
                modAction->setIcon(QIcon(":/images/singlecircle.png"));
                modAction->setToolTip(tr("单曲循环"));
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
    // 错误状态，则从媒体源列表中除去新添加的媒体源
    if(newState == Phonon::ErrorState) {
        QMessageBox::warning(this, tr("打开文件时出错"), metaInformationResolver->errorString());
        while (!sources.isEmpty() &&
               !(sources.takeLast() == metaInformationResolver->currentSource()))
        {};
        return;
    }

    // 如果既不处于停止状态也不处于暂停状态，则直接返回
    if(newState != Phonon::StoppedState && newState != Phonon::PausedState)
        return;

    // 如果媒体源类型错误，则直接返回
    if(metaInformationResolver->currentSource().type() == Phonon::MediaSource::Invalid)
        return;

    // 获取媒体信息
    QMap<QString, QString> metaData = metaInformationResolver->metaData();

    // 获取标题，如果为空，则使用文件名
    QString title = metaData.value("TITLE");
    if (title == "") {
        QString str = metaInformationResolver->currentSource().fileName();
        title = QFileInfo(str).baseName();
    }
    QTableWidgetItem *titleItem = new QTableWidgetItem(title);
    // 设置数据项不可编辑
    titleItem->setFlags(titleItem->flags() ^ Qt::ItemIsEditable);
    // 获取艺术家信息
    QTableWidgetItem *artistItem = new QTableWidgetItem(metaData.value("ARTIST"));
    artistItem->setFlags(artistItem->flags() ^ Qt::ItemIsEditable);

    int currentRow = playList->tableWidget->rowCount();
    playList->tableWidget->insertRow(currentRow);
    playList->tableWidget->setItem(currentRow, 0, artistItem);
    playList->tableWidget->setItem(currentRow, 1, titleItem);

    // 如果添加的媒体源还没有解析完，那么继续解析下一个媒体源
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

// 解析LRC歌词，在stateChanged()函数的Phonon::PlayingState处和aboutToFinish()函数中调用了该函数
void MusicPlayer::resolveLrc(const QString &sourceFileName)
{
    // 先清空以前的内容
    lrcMap.clear();
    timeList.clear();

    // 获取LRC歌词的文件名
    if(sourceFileName.isEmpty())
        return ;
    QString fileName = sourceFileName;
    QString lrcFileName = fileName.remove(fileName.right(3)) + "lrc";

    // 打开歌词文件
    QFile file(lrcFileName);
    if (!file.open(QIODevice::ReadOnly)) {
        lrc->setText(QFileInfo(mediaObject->currentSource().fileName()).baseName()
                     + tr(" --未找到歌词文件！"));
        mLrc->setText(QFileInfo(mediaObject->currentSource().fileName()).baseName()
                     + tr(" --未找到歌词文件！"));
        return ;
    }
    // 设置字符串编码
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    // 获取全部歌词信息
    QString allText = QString(file.readAll());
    // 关闭歌词文件
    file.close();
    // 将歌词按行分解为歌词列表
    QStringList lines = allText.split("\n");

    // 使用正则表达式将时间标签和歌词内容分离
    QRegExp rx("\\[\\d{2}:\\d{2}\\.\\d{2}\\]");
    foreach (QString oneLine, lines) {
        // 先在当前行的歌词的备份中将时间内容清除，这样就获得了歌词文本
        QString temp = oneLine;
        qint64 totalTime;
        temp.replace(rx, "");
        // 然后依次获取当前行中的所有时间标签，并分别与歌词文本存入QMap中
        int pos = rx.indexIn(oneLine, 0);
        while (pos != -1) {
            QString cap = rx.cap(0);
            // 将时间标签转换为时间数值，以毫秒为单位
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
            // 插入到lrcMap中
            lrcMap.insert(totalTime, temp);
            pos += rx.matchedLength();
            pos = rx.indexIn(oneLine, pos);
            timeList.push_back(totalTime);
        }
    }
    // 如果lrcMap为空
    if (lrcMap.isEmpty()) {
        lrc->setText(QFileInfo(mediaObject->currentSource().fileName()).baseName()
                     + tr(" --歌词文件内容错误！"));
        mLrc->setText(QFileInfo(mediaObject->currentSource().fileName()).baseName()
                     + tr(" --歌词文件内容错误！"));
        return;
    }
}


void MusicPlayer::tableWidgetClicked(int row)
{
    qDebug("clicked");
    // 首先获取媒体对象当前的状态，然后停止播放并清空播放队列
    bool wasPlaying = mediaObject->state() == Phonon::PlayingState;
    mediaObject->stop();
    mediaObject->clearQueue();

    // 如果单击的播放列表中的行号大于媒体源列表的大小，则直接返回
    if(row >= sources.size())
        return;
    // 设置单击的行对应的媒体源为媒体对象的当前媒体源
    mediaObject->setCurrentSource(sources.at(row));
    // 如果以前媒体对象处于播放状态，那么开始播放选中的曲目
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
                // 停止歌词遮罩并重新解析歌词
                lrc->stopLrcMask();
                mLrc->stopLrcMask();
                resolveLrc(sources.at(index).fileName());
            }
            else
            {
               mediaObject->setCurrentSource(sources.at(0));
               playList->tableWidget->selectRow(0);
               mediaObject->play();
               // 停止歌词遮罩并重新解析歌词
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
            // 停止歌词遮罩并重新解析歌词
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
            // 停止歌词遮罩并重新解析歌词
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

// 系统托盘图标被激活
void MusicPlayer::trayIconActivated(QSystemTrayIcon::ActivationReason activationReason)
{
    // 如果单击了系统托盘图标,则显示应用程序界面
    if (activationReason == QSystemTrayIcon::Trigger) {
        show();
    }
}

// 关闭事件处理函数
void MusicPlayer::closeEvent(QCloseEvent *event)
{
    if (isVisible()) {
        hide();
        trayIcon->showMessage(tr("天天爱音乐"), tr(""));
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




