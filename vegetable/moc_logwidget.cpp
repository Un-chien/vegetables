/****************************************************************************
** Meta object code from reading C++ file 'logwidget.h'
**
** Created: Fri Oct 7 23:26:04 2022
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "logwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'logwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Logwidget[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,
      19,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      34,   10,   10,   10, 0x08,
      64,   10,   10,   10, 0x08,
      93,   10,   10,   10, 0x08,
     121,   10,   10,   10, 0x08,
     153,   10,   10,   10, 0x08,
     167,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Logwidget[] = {
    "Logwidget\0\0login()\0close_window()\0"
    "on_longonpushButton_clicked()\0"
    "on_resetpushButton_clicked()\0"
    "on_namepushButton_clicked()\0"
    "on_passwordpushButton_clicked()\0"
    "namereceive()\0passwordreceive()\0"
};

const QMetaObject Logwidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Logwidget,
      qt_meta_data_Logwidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Logwidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Logwidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Logwidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Logwidget))
        return static_cast<void*>(const_cast< Logwidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int Logwidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: login(); break;
        case 1: close_window(); break;
        case 2: on_longonpushButton_clicked(); break;
        case 3: on_resetpushButton_clicked(); break;
        case 4: on_namepushButton_clicked(); break;
        case 5: on_passwordpushButton_clicked(); break;
        case 6: namereceive(); break;
        case 7: passwordreceive(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Logwidget::login()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Logwidget::close_window()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
