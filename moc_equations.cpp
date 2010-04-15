/****************************************************************************
** Meta object code from reading C++ file 'equations.h'
**
** Created: Thu Feb 25 18:29:22 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "equations.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'equations.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Equations[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x08,
      28,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Equations[] = {
    "Equations\0\0argsChanged(int)\0eqChanged(int)\0"
};

const QMetaObject Equations::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Equations,
      qt_meta_data_Equations, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Equations::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Equations::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Equations::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Equations))
        return static_cast<void*>(const_cast< Equations*>(this));
    return QWidget::qt_metacast(_clname);
}

int Equations::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: argsChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: eqChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
