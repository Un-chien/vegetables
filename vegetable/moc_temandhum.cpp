/****************************************************************************
** Meta object code from reading C++ file 'temandhum.h'
**
** Created: Fri Oct 7 23:26:07 2022
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "temandhum.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'temandhum.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TemandHum[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      23,   10,   10,   10, 0x08,
      54,   10,   10,   10, 0x08,
      70,   10,   10,   10, 0x08,
      86,   10,   10,   10, 0x08,
     102,   10,   10,   10, 0x08,
     118,   10,   10,   10, 0x08,
     144,   10,   10,   10, 0x08,
     170,   10,   10,   10, 0x08,
     196,   10,   10,   10, 0x08,
     222,   10,   10,   10, 0x08,
     251,  249,   10,   10, 0x08,
     275,  271,   10,   10, 0x08,
     288,  271,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TemandHum[] = {
    "TemandHum\0\0SendLight()\0"
    "on_refreshpushButton_clicked()\0"
    "temminreceive()\0humminreceive()\0"
    "temmaxreceive()\0hummaxreceive()\0"
    "on_temminButton_clicked()\0"
    "on_temmaxButton_clicked()\0"
    "on_humminButton_clicked()\0"
    "on_hummaxButton_clicked()\0"
    "pushButton_light_clicked()\0x\0"
    "show_TempHum(ulong)\0sim\0Set_Sim(int)\0"
    "Set_Send(int)\0"
};

const QMetaObject TemandHum::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TemandHum,
      qt_meta_data_TemandHum, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TemandHum::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TemandHum::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TemandHum::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TemandHum))
        return static_cast<void*>(const_cast< TemandHum*>(this));
    return QWidget::qt_metacast(_clname);
}

int TemandHum::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: SendLight(); break;
        case 1: on_refreshpushButton_clicked(); break;
        case 2: temminreceive(); break;
        case 3: humminreceive(); break;
        case 4: temmaxreceive(); break;
        case 5: hummaxreceive(); break;
        case 6: on_temminButton_clicked(); break;
        case 7: on_temmaxButton_clicked(); break;
        case 8: on_humminButton_clicked(); break;
        case 9: on_hummaxButton_clicked(); break;
        case 10: pushButton_light_clicked(); break;
        case 11: show_TempHum((*reinterpret_cast< ulong(*)>(_a[1]))); break;
        case 12: Set_Sim((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: Set_Send((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void TemandHum::SendLight()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
