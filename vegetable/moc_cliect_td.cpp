/****************************************************************************
** Meta object code from reading C++ file 'cliect_td.h'
**
** Created: Fri Oct 7 23:26:09 2022
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "server/cliect_td.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cliect_td.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Cliect[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x05,
      30,   23,    7,    7, 0x05,
      55,   49,    7,    7, 0x05,
      74,    7,    7,    7, 0x05,
      96,    7,    7,    7, 0x05,
     118,    7,    7,    7, 0x05,
     139,    7,    7,    7, 0x05,
     161,    7,    7,    7, 0x05,
     183,    7,    7,    7, 0x05,
     204,    7,    7,    7, 0x05,
     223,  219,    7,    7, 0x05,
     232,  219,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
     254,  242,    7,    7, 0x0a,
     276,    7,    7,    7, 0x0a,
     306,    7,    7,    7, 0x0a,
     336,    7,    7,    7, 0x0a,
     360,    7,    7,    7, 0x0a,
     383,    7,    7,    7, 0x0a,
     423,  410,    7,    7, 0x0a,
     461,    7,    7,    7, 0x0a,
     500,  487,    7,    7, 0x0a,
     548,  538,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Cliect[] = {
    "Cliect\0\0StateChanged()\0sensor\0"
    "sendMsgsignal(int)\0value\0sendTempHum(ulong)\0"
    "Irda_StateChanged_1()\0Smog_StateChanged_1()\0"
    "Int_StateChanged_1()\0Irda_StateChanged_0()\0"
    "Smog_StateChanged_0()\0Int_StateChanged_0()\0"
    "Rfid_Changed()\0sim\0Sim(int)\0Send(int)\0"
    "ipaddr,port\0GetConnect(char*,int)\0"
    "Api_Cliect_GetZigBeeNwkInfo()\0"
    "Api_Cliect_GetZigBeeNwkTopo()\0"
    "Api_Cliect_GetTempHum()\0Api_Cliect_GetRfidId()\0"
    "Api_Cliect_GetGPRSSignal()\0phone,sensor\0"
    "Api_Cliect_SendGprsMessage(char*,int)\0"
    "Api_Cliect_ClearIntlock()\0nwkaddr,Mode\0"
    "Api_Cliect_SetSensorStatus(uint,uint)\0"
    "coorstate\0Layer(int)\0"
};

const QMetaObject Cliect::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_Cliect,
      qt_meta_data_Cliect, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Cliect::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Cliect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Cliect::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Cliect))
        return static_cast<void*>(const_cast< Cliect*>(this));
    return QThread::qt_metacast(_clname);
}

int Cliect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: StateChanged(); break;
        case 1: sendMsgsignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: sendTempHum((*reinterpret_cast< ulong(*)>(_a[1]))); break;
        case 3: Irda_StateChanged_1(); break;
        case 4: Smog_StateChanged_1(); break;
        case 5: Int_StateChanged_1(); break;
        case 6: Irda_StateChanged_0(); break;
        case 7: Smog_StateChanged_0(); break;
        case 8: Int_StateChanged_0(); break;
        case 9: Rfid_Changed(); break;
        case 10: Sim((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: Send((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: GetConnect((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 13: Api_Cliect_GetZigBeeNwkInfo(); break;
        case 14: Api_Cliect_GetZigBeeNwkTopo(); break;
        case 15: Api_Cliect_GetTempHum(); break;
        case 16: Api_Cliect_GetRfidId(); break;
        case 17: Api_Cliect_GetGPRSSignal(); break;
        case 18: Api_Cliect_SendGprsMessage((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 19: Api_Cliect_ClearIntlock(); break;
        case 20: Api_Cliect_SetSensorStatus((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 21: Layer((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 22;
    }
    return _id;
}

// SIGNAL 0
void Cliect::StateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Cliect::sendMsgsignal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Cliect::sendTempHum(unsigned long _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Cliect::Irda_StateChanged_1()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void Cliect::Smog_StateChanged_1()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void Cliect::Int_StateChanged_1()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void Cliect::Irda_StateChanged_0()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void Cliect::Smog_StateChanged_0()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void Cliect::Int_StateChanged_0()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}

// SIGNAL 9
void Cliect::Rfid_Changed()
{
    QMetaObject::activate(this, &staticMetaObject, 9, 0);
}

// SIGNAL 10
void Cliect::Sim(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void Cliect::Send(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}
QT_END_MOC_NAMESPACE
