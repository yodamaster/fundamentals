/****************************************************************************
** Meta object code from reading C++ file 'windowtitlebar.h'
**
** Created: Sat Apr 16 18:04:43 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "windowtitlebar.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'windowtitlebar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WindowTitleBar[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x0a,
      36,   15,   15,   15, 0x0a,
      48,   15,   15,   15, 0x0a,
      60,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_WindowTitleBar[] = {
    "WindowTitleBar\0\0UpdateWindowTitle()\0"
    "Minimized()\0Maximized()\0Quit()\0"
};

const QMetaObject WindowTitleBar::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_WindowTitleBar,
      qt_meta_data_WindowTitleBar, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WindowTitleBar::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WindowTitleBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WindowTitleBar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WindowTitleBar))
        return static_cast<void*>(const_cast< WindowTitleBar*>(this));
    return QWidget::qt_metacast(_clname);
}

int WindowTitleBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: UpdateWindowTitle(); break;
        case 1: Minimized(); break;
        case 2: Maximized(); break;
        case 3: Quit(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
