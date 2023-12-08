/****************************************************************************
** Meta object code from reading C++ file 'softkey.h'
**
** Created: Fri Oct 7 23:26:07 2022
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "softkey.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'softkey.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SoftKey[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,
      17,    8,    8,    8, 0x05,
      25,    8,    8,    8, 0x05,
      33,    8,    8,    8, 0x05,
      41,    8,    8,    8, 0x05,
      49,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      57,    8,    8,    8, 0x08,
      84,    8,    8,    8, 0x08,
     111,    8,    8,    8, 0x08,
     140,    8,    8,    8, 0x08,
     168,    8,    8,    8, 0x08,
     196,    8,    8,    8, 0x08,
     223,    8,    8,    8, 0x08,
     252,    8,    8,    8, 0x08,
     281,    8,    8,    8, 0x08,
     309,    8,    8,    8, 0x08,
     337,    8,    8,    8, 0x08,
     367,    8,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SoftKey[] = {
    "SoftKey\0\0Send1()\0Send2()\0Send3()\0"
    "Send4()\0Send5()\0Send6()\0"
    "on_onepushButton_clicked()\0"
    "on_twopushButton_clicked()\0"
    "on_threepushButton_clicked()\0"
    "on_fourpushButton_clicked()\0"
    "on_fivepushButton_clicked()\0"
    "on_sixpushButton_clicked()\0"
    "on_sevenpushButton_clicked()\0"
    "on_eightpushButton_clicked()\0"
    "on_ninepushButton_clicked()\0"
    "on_zeropushButton_clicked()\0"
    "on_deletepushButton_clicked()\0"
    "on_confirmpushButton_clicked()\0"
};

const QMetaObject SoftKey::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SoftKey,
      qt_meta_data_SoftKey, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SoftKey::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SoftKey::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SoftKey::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SoftKey))
        return static_cast<void*>(const_cast< SoftKey*>(this));
    return QWidget::qt_metacast(_clname);
}

int SoftKey::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: Send1(); break;
        case 1: Send2(); break;
        case 2: Send3(); break;
        case 3: Send4(); break;
        case 4: Send5(); break;
        case 5: Send6(); break;
        case 6: on_onepushButton_clicked(); break;
        case 7: on_twopushButton_clicked(); break;
        case 8: on_threepushButton_clicked(); break;
        case 9: on_fourpushButton_clicked(); break;
        case 10: on_fivepushButton_clicked(); break;
        case 11: on_sixpushButton_clicked(); break;
        case 12: on_sevenpushButton_clicked(); break;
        case 13: on_eightpushButton_clicked(); break;
        case 14: on_ninepushButton_clicked(); break;
        case 15: on_zeropushButton_clicked(); break;
        case 16: on_deletepushButton_clicked(); break;
        case 17: on_confirmpushButton_clicked(); break;
        default: ;
        }
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void SoftKey::Send1()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void SoftKey::Send2()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void SoftKey::Send3()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void SoftKey::Send4()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void SoftKey::Send5()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void SoftKey::Send6()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}
QT_END_MOC_NAMESPACE
