/****************************************************************************
** Meta object code from reading C++ file 'plotter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/plotter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plotter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Plotter_t {
    QByteArrayData data[26];
    char stringdata0[334];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Plotter_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Plotter_t qt_meta_stringdata_Plotter = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Plotter"
QT_MOC_LITERAL(1, 8, 17), // "On_Legend_Clicked"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 20), // "axisLabelDoubleClick"
QT_MOC_LITERAL(4, 48, 8), // "QCPAxis*"
QT_MOC_LITERAL(5, 57, 4), // "axis"
QT_MOC_LITERAL(6, 62, 23), // "QCPAxis::SelectablePart"
QT_MOC_LITERAL(7, 86, 4), // "part"
QT_MOC_LITERAL(8, 91, 17), // "legendDoubleClick"
QT_MOC_LITERAL(9, 109, 10), // "QCPLegend*"
QT_MOC_LITERAL(10, 120, 6), // "legend"
QT_MOC_LITERAL(11, 127, 22), // "QCPAbstractLegendItem*"
QT_MOC_LITERAL(12, 150, 4), // "item"
QT_MOC_LITERAL(13, 155, 18), // "contextMenuRequest"
QT_MOC_LITERAL(14, 174, 3), // "pos"
QT_MOC_LITERAL(15, 178, 10), // "moveLegend"
QT_MOC_LITERAL(16, 189, 12), // "graphClicked"
QT_MOC_LITERAL(17, 202, 21), // "QCPAbstractPlottable*"
QT_MOC_LITERAL(18, 224, 9), // "plottable"
QT_MOC_LITERAL(19, 234, 9), // "dataIndex"
QT_MOC_LITERAL(20, 244, 19), // "removeSelectedGraph"
QT_MOC_LITERAL(21, 264, 10), // "mousePress"
QT_MOC_LITERAL(22, 275, 10), // "mouseWheel"
QT_MOC_LITERAL(23, 286, 16), // "selectionChanged"
QT_MOC_LITERAL(24, 303, 21), // "turnSelectedtoSymbols"
QT_MOC_LITERAL(25, 325, 8) // "Deselect"

    },
    "Plotter\0On_Legend_Clicked\0\0"
    "axisLabelDoubleClick\0QCPAxis*\0axis\0"
    "QCPAxis::SelectablePart\0part\0"
    "legendDoubleClick\0QCPLegend*\0legend\0"
    "QCPAbstractLegendItem*\0item\0"
    "contextMenuRequest\0pos\0moveLegend\0"
    "graphClicked\0QCPAbstractPlottable*\0"
    "plottable\0dataIndex\0removeSelectedGraph\0"
    "mousePress\0mouseWheel\0selectionChanged\0"
    "turnSelectedtoSymbols\0Deselect"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Plotter[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    2,   75,    2, 0x08 /* Private */,
       8,    2,   80,    2, 0x08 /* Private */,
      13,    1,   85,    2, 0x08 /* Private */,
      15,    0,   88,    2, 0x08 /* Private */,
      16,    2,   89,    2, 0x08 /* Private */,
      20,    0,   94,    2, 0x08 /* Private */,
      21,    0,   95,    2, 0x08 /* Private */,
      22,    0,   96,    2, 0x08 /* Private */,
      23,    0,   97,    2, 0x08 /* Private */,
      24,    0,   98,    2, 0x08 /* Private */,
      25,    0,   99,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Bool,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 6,    5,    7,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 11,   10,   12,
    QMetaType::Void, QMetaType::QPoint,   14,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 17, QMetaType::Int,   18,   19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Plotter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Plotter *_t = static_cast<Plotter *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { bool _r = _t->On_Legend_Clicked();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 1: _t->axisLabelDoubleClick((*reinterpret_cast< QCPAxis*(*)>(_a[1])),(*reinterpret_cast< QCPAxis::SelectablePart(*)>(_a[2]))); break;
        case 2: _t->legendDoubleClick((*reinterpret_cast< QCPLegend*(*)>(_a[1])),(*reinterpret_cast< QCPAbstractLegendItem*(*)>(_a[2]))); break;
        case 3: _t->contextMenuRequest((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 4: _t->moveLegend(); break;
        case 5: _t->graphClicked((*reinterpret_cast< QCPAbstractPlottable*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->removeSelectedGraph(); break;
        case 7: _t->mousePress(); break;
        case 8: _t->mouseWheel(); break;
        case 9: _t->selectionChanged(); break;
        case 10: _t->turnSelectedtoSymbols(); break;
        case 11: _t->Deselect(); break;
        default: ;
        }
    }
}

const QMetaObject Plotter::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Plotter.data,
      qt_meta_data_Plotter,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Plotter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Plotter::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Plotter.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Plotter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
