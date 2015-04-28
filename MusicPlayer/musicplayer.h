#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H
#include <phonon/audiooutput.h>
#include <phonon/seekslider.h>
#include <phonon/mediaobject.h>
#include <phonon/volumeslider.h>
#include <phonon/backendcapabilities.h>
#include <QWidget>
#include <QSystemTrayIcon>//系统托盘头文件
class QGraphicsView;
class QGraphicsWidget;
class QLabel;
class QPoint;
class PlayList;
class MusicLrc;
class IconButton;
class SetWidget;
namespace Ui {
    class MusicPlayer;
}

class MusicPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit MusicPlayer(QWidget *parent = 0);
    ~MusicPlayer();

    MusicLrc *lrc,*mLrc,*lrc1,*lrc2,*lrc3,*lrc4,*lrc5,*lrc6,*lrc7,*lrc8,*lrc9,*lrc10;
    MusicLrc *musicName;
    Ui::MusicPlayer *ui;
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void closeEvent(QCloseEvent *event);
private slots:
    void updateTime(qint64 time);
    void playOrpause();
    void openFile();
    void setMod();
    void previousSong();
    void nextSong();
    void whatiLike();
    void showLrc();
    void setPlayer();
    void showPlayList();
    void metaStateChanged(Phonon::State newState, Phonon::State oldState);
    void tableWidgetClicked(int);
    void aboutToFinish();
    void clearSources();
    void saveAndQuit();
    //系统托盘激活
    void trayIconActivated(QSystemTrayIcon::ActivationReason activationReason);
private:
    void init_ui();
    void LoadSettingData();
    void LoadMusicListData();
    void saveMusicList();
    void saveSettingWidgetData();
    QLabel *totalTimeLabel;
    QLabel *timeLabel;
    QAction *modAction;
    QAction *previousAction;
    QAction *playAction;
    QAction *nextAction;
    QAction *openAction;
    IconButton *likeButton;
    IconButton *lrcButton;
    IconButton *setButton;
    QAction *listAction;
    //QGraphicsView *view;

    Phonon::MediaObject *mediaObject;
    Phonon::VolumeSlider *volumeSlider;
    Phonon::SeekSlider *seekSlider;
    Phonon::AudioOutput *audioOutput;
    PlayList *playList;
    QList<Phonon::MediaSource> sources;
    Phonon::MediaObject *metaInformationResolver;


    IconButton *closeButton;
    QMap<qint64, QString> lrcMap;
    void resolveLrc(const QString &sourceFileName);

    QPoint oldPos;
    QPoint constPoint;
    bool press;
    QPoint disPoint;
    QPoint namePoint;

    QList<qint64> timeList;
    QSystemTrayIcon *trayIcon;

    SetWidget *settingWidget;
    int playmod;
    int i;
    QStringList offerToSave;
};

#endif // MUSICPLAYER_H
