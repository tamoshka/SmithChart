/****************************************************************************
** Meta object code from reading C++ file 'TuneWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../TuneWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TuneWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TuneWidget_t {
    QByteArrayData data[14];
    char stringdata0[132];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TuneWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TuneWidget_t qt_meta_stringdata_TuneWidget = {
    {
QT_MOC_LITERAL(0, 0, 10), // "TuneWidget"
QT_MOC_LITERAL(1, 11, 6), // "remove"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 8), // "Element*"
QT_MOC_LITERAL(4, 28, 9), // "removeAll"
QT_MOC_LITERAL(5, 38, 16), // "OKButton_clicked"
QT_MOC_LITERAL(6, 55, 20), // "MinMaxButton_clicked"
QT_MOC_LITERAL(7, 76, 12), // "ValueChanged"
QT_MOC_LITERAL(8, 89, 5), // "value"
QT_MOC_LITERAL(9, 95, 6), // "Remove"
QT_MOC_LITERAL(10, 102, 9), // "RemoveAll"
QT_MOC_LITERAL(11, 112, 9), // "GetSignal"
QT_MOC_LITERAL(12, 122, 4), // "elem"
QT_MOC_LITERAL(13, 127, 4) // "path"

    },
    "TuneWidget\0remove\0\0Element*\0removeAll\0"
    "OKButton_clicked\0MinMaxButton_clicked\0"
    "ValueChanged\0value\0Remove\0RemoveAll\0"
    "GetSignal\0elem\0path"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TuneWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    0,   57,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   58,    2, 0x08 /* Private */,
       6,    0,   59,    2, 0x08 /* Private */,
       7,    1,   60,    2, 0x08 /* Private */,
       9,    0,   63,    2, 0x08 /* Private */,
      10,    0,   64,    2, 0x08 /* Private */,
      11,    2,   65,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString,   12,   13,

       0        // eod
};

void TuneWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TuneWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->remove((*reinterpret_cast< Element*(*)>(_a[1]))); break;
        case 1: _t->removeAll(); break;
        case 2: _t->OKButton_clicked(); break;
        case 3: _t->MinMaxButton_clicked(); break;
        case 4: _t->ValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->Remove(); break;
        case 6: _t->RemoveAll(); break;
        case 7: _t->GetSignal((*reinterpret_cast< Element*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TuneWidget::*)(Element * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TuneWidget::remove)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TuneWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TuneWidget::removeAll)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TuneWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_TuneWidget.data,
    qt_meta_data_TuneWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TuneWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TuneWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TuneWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int TuneWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void TuneWidget::remove(Element * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TuneWidget::removeAll()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
