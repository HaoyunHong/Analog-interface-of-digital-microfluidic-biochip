/****************************************************************************
** Meta object code from reading C++ file 'settingwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../BigProject/settingwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'settingwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SettingWidget_t {
    QByteArrayData data[15];
    char stringdata0[256];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SettingWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SettingWidget_t qt_meta_stringdata_SettingWidget = {
    {
QT_MOC_LITERAL(0, 0, 13), // "SettingWidget"
QT_MOC_LITERAL(1, 14, 8), // "setAgain"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 6), // "sendRC"
QT_MOC_LITERAL(4, 31, 16), // "backToMainWindow"
QT_MOC_LITERAL(5, 48, 19), // "backToSettingWidget"
QT_MOC_LITERAL(6, 68, 26), // "setInputPointsNumberSignal"
QT_MOC_LITERAL(7, 95, 14), // "sendInputPoint"
QT_MOC_LITERAL(8, 110, 20), // "outputFinishedSignal"
QT_MOC_LITERAL(9, 131, 17), // "outputCheckSignal"
QT_MOC_LITERAL(10, 149, 10), // "setAllDone"
QT_MOC_LITERAL(11, 160, 24), // "on_confirmButton_clicked"
QT_MOC_LITERAL(12, 185, 21), // "on_inOKButton_clicked"
QT_MOC_LITERAL(13, 207, 21), // "on_saveButton_clicked"
QT_MOC_LITERAL(14, 229, 26) // "on_confirmButton_2_clicked"

    },
    "SettingWidget\0setAgain\0\0sendRC\0"
    "backToMainWindow\0backToSettingWidget\0"
    "setInputPointsNumberSignal\0sendInputPoint\0"
    "outputFinishedSignal\0outputCheckSignal\0"
    "setAllDone\0on_confirmButton_clicked\0"
    "on_inOKButton_clicked\0on_saveButton_clicked\0"
    "on_confirmButton_2_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SettingWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,
       3,    2,   80,    2, 0x06 /* Public */,
       4,    0,   85,    2, 0x06 /* Public */,
       5,    0,   86,    2, 0x06 /* Public */,
       6,    1,   87,    2, 0x06 /* Public */,
       7,    1,   90,    2, 0x06 /* Public */,
       8,    2,   93,    2, 0x06 /* Public */,
       9,    2,   98,    2, 0x06 /* Public */,
      10,    0,  103,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,  104,    2, 0x08 /* Private */,
      12,    0,  105,    2, 0x08 /* Private */,
      13,    0,  106,    2, 0x08 /* Private */,
      14,    0,  107,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SettingWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SettingWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setAgain(); break;
        case 1: _t->sendRC((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->backToMainWindow(); break;
        case 3: _t->backToSettingWidget(); break;
        case 4: _t->setInputPointsNumberSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->sendInputPoint((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 6: _t->outputFinishedSignal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->outputCheckSignal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->setAllDone(); break;
        case 9: _t->on_confirmButton_clicked(); break;
        case 10: _t->on_inOKButton_clicked(); break;
        case 11: _t->on_saveButton_clicked(); break;
        case 12: _t->on_confirmButton_2_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SettingWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SettingWidget::setAgain)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SettingWidget::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SettingWidget::sendRC)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SettingWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SettingWidget::backToMainWindow)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SettingWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SettingWidget::backToSettingWidget)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SettingWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SettingWidget::setInputPointsNumberSignal)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (SettingWidget::*)(QPoint );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SettingWidget::sendInputPoint)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (SettingWidget::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SettingWidget::outputFinishedSignal)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (SettingWidget::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SettingWidget::outputCheckSignal)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (SettingWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SettingWidget::setAllDone)) {
                *result = 8;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SettingWidget::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_SettingWidget.data,
    qt_meta_data_SettingWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SettingWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SettingWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SettingWidget.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int SettingWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void SettingWidget::setAgain()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SettingWidget::sendRC(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SettingWidget::backToMainWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void SettingWidget::backToSettingWidget()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void SettingWidget::setInputPointsNumberSignal(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void SettingWidget::sendInputPoint(QPoint _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void SettingWidget::outputFinishedSignal(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void SettingWidget::outputCheckSignal(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void SettingWidget::setAllDone()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
