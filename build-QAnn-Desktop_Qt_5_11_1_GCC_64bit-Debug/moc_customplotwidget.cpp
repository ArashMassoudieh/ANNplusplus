/****************************************************************************
** Meta object code from reading C++ file 'customplotwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../QAnn/customplotwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'customplotwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CustomPlotWidget_t {
    QByteArrayData data[26];
    char stringdata0[343];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CustomPlotWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CustomPlotWidget_t qt_meta_stringdata_CustomPlotWidget = {
    {
QT_MOC_LITERAL(0, 0, 16), // "CustomPlotWidget"
QT_MOC_LITERAL(1, 17, 17), // "On_Legend_Clicked"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 20), // "axisLabelDoubleClick"
QT_MOC_LITERAL(4, 57, 8), // "QCPAxis*"
QT_MOC_LITERAL(5, 66, 4), // "axis"
QT_MOC_LITERAL(6, 71, 23), // "QCPAxis::SelectablePart"
QT_MOC_LITERAL(7, 95, 4), // "part"
QT_MOC_LITERAL(8, 100, 17), // "legendDoubleClick"
QT_MOC_LITERAL(9, 118, 10), // "QCPLegend*"
QT_MOC_LITERAL(10, 129, 6), // "legend"
QT_MOC_LITERAL(11, 136, 22), // "QCPAbstractLegendItem*"
QT_MOC_LITERAL(12, 159, 4), // "item"
QT_MOC_LITERAL(13, 164, 18), // "contextMenuRequest"
QT_MOC_LITERAL(14, 183, 3), // "pos"
QT_MOC_LITERAL(15, 187, 10), // "moveLegend"
QT_MOC_LITERAL(16, 198, 12), // "graphClicked"
QT_MOC_LITERAL(17, 211, 21), // "QCPAbstractPlottable*"
QT_MOC_LITERAL(18, 233, 9), // "plottable"
QT_MOC_LITERAL(19, 243, 9), // "dataIndex"
QT_MOC_LITERAL(20, 253, 19), // "removeSelectedGraph"
QT_MOC_LITERAL(21, 273, 10), // "mousePress"
QT_MOC_LITERAL(22, 284, 10), // "mouseWheel"
QT_MOC_LITERAL(23, 295, 16), // "selectionChanged"
QT_MOC_LITERAL(24, 312, 21), // "turnSelectedtoSymbols"
QT_MOC_LITERAL(25, 334, 8) // "Deselect"

    },
    "CustomPlotWidget\0On_Legend_Clicked\0\0"
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

static const uint qt_meta_data_CustomPlotWidget[] = {

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

void CustomPlotWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CustomPlotWidget *_t = static_cast<CustomPlotWidget *>(_o);
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
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAxis* >(); break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAxis::SelectablePart >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAbstractLegendItem* >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPLegend* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAbstractPlottable* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CustomPlotWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CustomPlotWidget.data,
      qt_meta_data_CustomPlotWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CustomPlotWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CustomPlotWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CustomPlotWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CustomPlotWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
