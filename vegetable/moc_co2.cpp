/****************************************************************************
** Meta object code from reading C++ file 'co2.h'
**
** Created: Fri Oct 7 23:26:03 2022
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "co2.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'co2.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CO2[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
       5,    4,    4,    4, 0x05,
      27,    4,    4,    4, 0x05,
      49,    4,    4,    4, 0x05,
      70,    4,    4,    4, 0x05,
      92,    4,    4,    4, 0x05,
     114,    4,    4,    4, 0x05,

 // slots: signature, parameters, type, tag, flags
     135,    4,    4,    4, 0x0a,
     151,    4,    4,    4, 0x0a,
     166,    4,    4,    4, 0x0a,
     182,    4,    4,    4, 0x0a,
     198,    4,    4,    4, 0x0a,
     213,    4,    4,    4, 0x0a,
     229,    4,    4,    4, 0x0a,
     240,    4,    4,    4, 0x0a,
     252,    4,    4,    4, 0x0a,
     268,  264,    4,    4, 0x0a,
     281,  264,    4,    4, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CO2[] = {
    "CO2\0\0Irda_StateChanged_1()\0"
    "Smog_StateChanged_1()\0Int_StateChanged_1()\0"
    "Irda_StateChanged_0()\0Smog_StateChanged_0()\0"
    "Int_StateChanged_0()\0Smog_change_1()\0"
    "Int_change_1()\0Irda_change_1()\0"
    "Smog_change_0()\0Int_change_0()\0"
    "Irda_change_0()\0int_show()\0smog_show()\0"
    "irda_show()\0sim\0Set_Sim(int)\0Set_Send(int)\0"
};

const QMetaObject CO2::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CO2,
      qt_meta_data_CO2, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CO2::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CO2::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CO2::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CO2))
        return static_cast<void*>(const_cast< CO2*>(this));
    return QWidget::qt_metacast(_clname);
}

int CO2::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: Irda_StateChanged_1(); break;
        case 1: Smog_StateChanged_1(); break;
        case 2: Int_StateChanged_1(); break;
        case 3: Irda_StateChanged_0(); break;
        case 4: Smog_StateChanged_0(); break;
        case 5: Int_StateChanged_0(); break;
        case 6: Smog_change_1(); break;
        case 7: Int_change_1(); break;
        case 8: Irda_change_1(); break;
        case 9: Smog_change_0(); break;
        case 10: Int_change_0(); break;
        case 11: Irda_change_0(); break;
        case 12: int_show(); break;
        case 13: smog_show(); break;
        case 14: irda_show(); break;
        case 15: Set_Sim((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: Set_Send((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void CO2::Irda_StateChanged_1()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void CO2::Smog_StateChanged_1()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void CO2::Int_StateChanged_1()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void CO2::Irda_StateChanged_0()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void CO2::Smog_StateChanged_0()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void CO2::Int_StateChanged_0()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}
QT_END_MOC_NAMESPACE
