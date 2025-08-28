/****************************************************************************
** Meta object code from reading C++ file 'GrafTwo.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../GrafTwo.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GrafTwo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GrafTwo_t {
    QByteArrayData data[9];
    char stringdata0[99];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GrafTwo_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GrafTwo_t qt_meta_stringdata_GrafTwo = {
    {
QT_MOC_LITERAL(0, 0, 7), // "GrafTwo"
QT_MOC_LITERAL(1, 8, 14), // "highlightPoint"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 11), // "point_index"
QT_MOC_LITERAL(4, 36, 14), // "updateMAGColor"
QT_MOC_LITERAL(5, 51, 5), // "color"
QT_MOC_LITERAL(6, 57, 14), // "updateMSGColor"
QT_MOC_LITERAL(7, 72, 12), // "updateKColor"
QT_MOC_LITERAL(8, 85, 13) // "updateMuColor"

    },
    "GrafTwo\0highlightPoint\0\0point_index\0"
    "updateMAGColor\0color\0updateMSGColor\0"
    "updateKColor\0updateMuColor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GrafTwo[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x0a /* Public */,
       4,    1,   42,    2, 0x0a /* Public */,
       6,    1,   45,    2, 0x0a /* Public */,
       7,    1,   48,    2, 0x0a /* Public */,
       8,    1,   51,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QColor,    5,
    QMetaType::Void, QMetaType::QColor,    5,
    QMetaType::Void, QMetaType::QColor,    5,
    QMetaType::Void, QMetaType::QColor,    5,

       0        // eod
};

void GrafTwo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GrafTwo *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->highlightPoint((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->updateMAGColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 2: _t->updateMSGColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 3: _t->updateKColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 4: _t->updateMuColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GrafTwo::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_GrafTwo.data,
    qt_meta_data_GrafTwo,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GrafTwo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GrafTwo::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GrafTwo.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int GrafTwo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
