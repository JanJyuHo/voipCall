/****************************************************************************
** Meta object code from reading C++ file 'voipaccount.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../voipaccount.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'voipaccount.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_voip__voipAccount_t {
    QByteArrayData data[5];
    char stringdata0[62];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_voip__voipAccount_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_voip__voipAccount_t qt_meta_stringdata_voip__voipAccount = {
    {
QT_MOC_LITERAL(0, 0, 17), // "voip::voipAccount"
QT_MOC_LITERAL(1, 18, 12), // "incomingCall"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 24), // "pj::OnIncomingCallParam*"
QT_MOC_LITERAL(4, 57, 4) // "iprm"

    },
    "voip::voipAccount\0incomingCall\0\0"
    "pj::OnIncomingCallParam*\0iprm"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_voip__voipAccount[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void voip::voipAccount::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        voipAccount *_t = static_cast<voipAccount *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->incomingCall((*reinterpret_cast< pj::OnIncomingCallParam*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (voipAccount::*)(pj::OnIncomingCallParam * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&voipAccount::incomingCall)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject voip::voipAccount::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_voip__voipAccount.data,
      qt_meta_data_voip__voipAccount,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *voip::voipAccount::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *voip::voipAccount::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_voip__voipAccount.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "pj::Account"))
        return static_cast< pj::Account*>(this);
    return QObject::qt_metacast(_clname);
}

int voip::voipAccount::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void voip::voipAccount::incomingCall(pj::OnIncomingCallParam * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
