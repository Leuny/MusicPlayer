/****************************************************************************
** Meta object code from reading C++ file 'musicplayer.h'
**
** Created: Fri Nov 21 16:16:29 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MusicPlayer/musicplayer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'musicplayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MusicPlayer[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   13,   12,   12, 0x08,
      37,   12,   12,   12, 0x08,
      51,   12,   12,   12, 0x08,
      62,   12,   12,   12, 0x08,
      71,   12,   12,   12, 0x08,
      86,   12,   12,   12, 0x08,
      97,   12,   12,   12, 0x08,
     109,   12,   12,   12, 0x08,
     119,   12,   12,   12, 0x08,
     131,   12,   12,   12, 0x08,
     164,  146,   12,   12, 0x08,
     210,   12,   12,   12, 0x08,
     234,   12,   12,   12, 0x08,
     250,   12,   12,   12, 0x08,
     265,   12,   12,   12, 0x08,
     296,  279,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MusicPlayer[] = {
    "MusicPlayer\0\0time\0updateTime(qint64)\0"
    "playOrpause()\0openFile()\0setMod()\0"
    "previousSong()\0nextSong()\0whatiLike()\0"
    "showLrc()\0setPlayer()\0showPlayList()\0"
    "newState,oldState\0"
    "metaStateChanged(Phonon::State,Phonon::State)\0"
    "tableWidgetClicked(int)\0aboutToFinish()\0"
    "clearSources()\0saveAndQuit()\0"
    "activationReason\0"
    "trayIconActivated(QSystemTrayIcon::ActivationReason)\0"
};

const QMetaObject MusicPlayer::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MusicPlayer,
      qt_meta_data_MusicPlayer, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MusicPlayer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MusicPlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MusicPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MusicPlayer))
        return static_cast<void*>(const_cast< MusicPlayer*>(this));
    return QWidget::qt_metacast(_clname);
}

int MusicPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateTime((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 1: playOrpause(); break;
        case 2: openFile(); break;
        case 3: setMod(); break;
        case 4: previousSong(); break;
        case 5: nextSong(); break;
        case 6: whatiLike(); break;
        case 7: showLrc(); break;
        case 8: setPlayer(); break;
        case 9: showPlayList(); break;
        case 10: metaStateChanged((*reinterpret_cast< Phonon::State(*)>(_a[1])),(*reinterpret_cast< Phonon::State(*)>(_a[2]))); break;
        case 11: tableWidgetClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: aboutToFinish(); break;
        case 13: clearSources(); break;
        case 14: saveAndQuit(); break;
        case 15: trayIconActivated((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
