/****************************************************************************
** Meta object code from reading C++ file 'myqlabel.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "myqlabel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myqlabel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyQLabel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,
      25,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      43,    9,    9,    9, 0x0a,
      51,    9,    9,    9, 0x0a,
      62,   60,    9,    9, 0x0a,
      77,   75,    9,    9, 0x0a,
      92,    9,    9,    9, 0x0a,
     101,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MyQLabel[] = {
    "MyQLabel\0\0enviaZero(int)\0radioOff2On(bool)\0"
    "setOn()\0setOff()\0h\0setHour(int)\0m\0"
    "setMinute(int)\0update()\0reset()\0"
};

void MyQLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MyQLabel *_t = static_cast<MyQLabel *>(_o);
        switch (_id) {
        case 0: _t->enviaZero((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 1: _t->radioOff2On((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 2: _t->setOn(); break;
        case 3: _t->setOff(); break;
        case 4: _t->setHour((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->setMinute((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->update(); break;
        case 7: _t->reset(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MyQLabel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MyQLabel::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_MyQLabel,
      qt_meta_data_MyQLabel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MyQLabel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MyQLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MyQLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyQLabel))
        return static_cast<void*>(const_cast< MyQLabel*>(this));
    return QLabel::qt_metacast(_clname);
}

int MyQLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void MyQLabel::enviaZero(const int & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MyQLabel::radioOff2On(const bool & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
