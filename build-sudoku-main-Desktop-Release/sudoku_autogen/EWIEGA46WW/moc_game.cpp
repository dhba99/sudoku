/****************************************************************************
** Meta object code from reading C++ file 'game.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../sudoku-main/game.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'game.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSGameENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSGameENDCLASS = QtMocHelpers::stringData(
    "Game",
    "signalSelectedPress",
    "",
    "signalMovement",
    "exitGameSignal",
    "updateTime",
    "selectedEvent",
    "movementEvent",
    "pauseMenuEvent",
    "exitGameEvent",
    "makeMovement",
    "x",
    "y",
    "value",
    "lapizOn",
    "lapiz",
    "deshacer",
    "borrar",
    "generateGame",
    "Difficulty",
    "difficulty"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSGameENDCLASS_t {
    uint offsetsAndSizes[42];
    char stringdata0[5];
    char stringdata1[20];
    char stringdata2[1];
    char stringdata3[15];
    char stringdata4[15];
    char stringdata5[11];
    char stringdata6[14];
    char stringdata7[14];
    char stringdata8[15];
    char stringdata9[14];
    char stringdata10[13];
    char stringdata11[2];
    char stringdata12[2];
    char stringdata13[6];
    char stringdata14[8];
    char stringdata15[6];
    char stringdata16[9];
    char stringdata17[7];
    char stringdata18[13];
    char stringdata19[11];
    char stringdata20[11];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSGameENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSGameENDCLASS_t qt_meta_stringdata_CLASSGameENDCLASS = {
    {
        QT_MOC_LITERAL(0, 4),  // "Game"
        QT_MOC_LITERAL(5, 19),  // "signalSelectedPress"
        QT_MOC_LITERAL(25, 0),  // ""
        QT_MOC_LITERAL(26, 14),  // "signalMovement"
        QT_MOC_LITERAL(41, 14),  // "exitGameSignal"
        QT_MOC_LITERAL(56, 10),  // "updateTime"
        QT_MOC_LITERAL(67, 13),  // "selectedEvent"
        QT_MOC_LITERAL(81, 13),  // "movementEvent"
        QT_MOC_LITERAL(95, 14),  // "pauseMenuEvent"
        QT_MOC_LITERAL(110, 13),  // "exitGameEvent"
        QT_MOC_LITERAL(124, 12),  // "makeMovement"
        QT_MOC_LITERAL(137, 1),  // "x"
        QT_MOC_LITERAL(139, 1),  // "y"
        QT_MOC_LITERAL(141, 5),  // "value"
        QT_MOC_LITERAL(147, 7),  // "lapizOn"
        QT_MOC_LITERAL(155, 5),  // "lapiz"
        QT_MOC_LITERAL(161, 8),  // "deshacer"
        QT_MOC_LITERAL(170, 6),  // "borrar"
        QT_MOC_LITERAL(177, 12),  // "generateGame"
        QT_MOC_LITERAL(190, 10),  // "Difficulty"
        QT_MOC_LITERAL(201, 10)   // "difficulty"
    },
    "Game",
    "signalSelectedPress",
    "",
    "signalMovement",
    "exitGameSignal",
    "updateTime",
    "selectedEvent",
    "movementEvent",
    "pauseMenuEvent",
    "exitGameEvent",
    "makeMovement",
    "x",
    "y",
    "value",
    "lapizOn",
    "lapiz",
    "deshacer",
    "borrar",
    "generateGame",
    "Difficulty",
    "difficulty"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSGameENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   92,    2, 0x06,    1 /* Public */,
       3,    0,   93,    2, 0x06,    2 /* Public */,
       4,    0,   94,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    0,   95,    2, 0x0a,    4 /* Public */,
       6,    0,   96,    2, 0x0a,    5 /* Public */,
       7,    0,   97,    2, 0x0a,    6 /* Public */,
       8,    0,   98,    2, 0x0a,    7 /* Public */,
       9,    0,   99,    2, 0x0a,    8 /* Public */,
      10,    4,  100,    2, 0x0a,    9 /* Public */,
      15,    0,  109,    2, 0x0a,   14 /* Public */,
      16,    0,  110,    2, 0x0a,   15 /* Public */,
      17,    0,  111,    2, 0x0a,   16 /* Public */,
      18,    1,  112,    2, 0x0a,   17 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Bool,   11,   12,   13,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 19,   20,

       0        // eod
};

Q_CONSTINIT const QMetaObject Game::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSGameENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSGameENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSGameENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Game, std::true_type>,
        // method 'signalSelectedPress'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'signalMovement'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'exitGameSignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateTime'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'selectedEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'movementEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pauseMenuEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'exitGameEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'makeMovement'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'lapiz'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'deshacer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'borrar'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'generateGame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Difficulty, std::false_type>
    >,
    nullptr
} };

void Game::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Game *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->signalSelectedPress(); break;
        case 1: _t->signalMovement(); break;
        case 2: _t->exitGameSignal(); break;
        case 3: _t->updateTime(); break;
        case 4: _t->selectedEvent(); break;
        case 5: _t->movementEvent(); break;
        case 6: _t->pauseMenuEvent(); break;
        case 7: _t->exitGameEvent(); break;
        case 8: _t->makeMovement((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[4]))); break;
        case 9: _t->lapiz(); break;
        case 10: _t->deshacer(); break;
        case 11: _t->borrar(); break;
        case 12: _t->generateGame((*reinterpret_cast< std::add_pointer_t<Difficulty>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Game::*)();
            if (_t _q_method = &Game::signalSelectedPress; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Game::*)();
            if (_t _q_method = &Game::signalMovement; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Game::*)();
            if (_t _q_method = &Game::exitGameSignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject *Game::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Game::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSGameENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Game::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void Game::signalSelectedPress()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Game::signalMovement()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Game::exitGameSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
