/****************************************************************************
** Meta object code from reading C++ file 'applicationui.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/applicationui.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'applicationui.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ApplicationUI[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      32,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,
      26,   14,   14,   14, 0x08,
      37,   14,   14,   14, 0x08,
      52,   14,   14,   14, 0x08,
      69,   14,   14,   14, 0x08,
      83,   14,   14,   14, 0x08,
      97,   14,   14,   14, 0x08,
     115,   14,   14,   14, 0x08,
     127,   14,   14,   14, 0x08,
     137,   14,   14,   14, 0x08,
     147,   14,   14,   14, 0x08,
     161,   14,   14,   14, 0x08,
     181,   14,   14,   14, 0x08,
     201,   14,   14,   14, 0x08,
     213,   14,   14,   14, 0x08,
     222,   14,   14,   14, 0x08,
     247,   14,   14,   14, 0x08,
     260,   14,   14,   14, 0x08,
     284,   14,   14,   14, 0x08,
     311,   14,   14,   14, 0x08,
     347,   14,   14,   14, 0x08,
     367,   14,   14,   14, 0x08,
     404,   14,   14,   14, 0x08,
     438,   14,   14,   14, 0x08,
     447,   14,   14,   14, 0x08,
     456,   14,   14,   14, 0x08,
     525,   14,   14,   14, 0x08,
     545,   14,   14,   14, 0x08,
     565,   14,   14,   14, 0x08,
     576,   14,   14,   14, 0x08,
     597,   14,   14,   14, 0x08,
     618,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ApplicationUI[] = {
    "ApplicationUI\0\0changeFB()\0changeLI()\0"
    "clearTheList()\0deleteSelected()\0"
    "displayHelp()\0displayInfo()\0"
    "displaySettings()\0enableNFC()\0getFbID()\0"
    "getLiID()\0goToAppPage()\0goToAppReviewPage()\0"
    "goToPrivacyPolicy()\0goToRubus()\0"
    "goToSV()\0handleConnector(QString)\0"
    "handleExit()\0handleHelpSlider(float)\0"
    "handleHelpSliderImm(float)\0"
    "handleTabChange(bb::cascades::Tab*)\0"
    "handleToastFinish()\0"
    "onInvoked(bb::system::InvokeRequest)\0"
    "onListViewTriggered(QVariantList)\0"
    "openFB()\0openLI()\0"
    "registrationStateUpdated(bb::platform::bbm::RegistrationState::Type)\0"
    "setContentForHelp()\0setContentToShare()\0"
    "shareApp()\0shareFBChanged(bool)\0"
    "shareLIChanged(bool)\0submitted()\0"
};

void ApplicationUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ApplicationUI *_t = static_cast<ApplicationUI *>(_o);
        switch (_id) {
        case 0: _t->changeFB(); break;
        case 1: _t->changeLI(); break;
        case 2: _t->clearTheList(); break;
        case 3: _t->deleteSelected(); break;
        case 4: _t->displayHelp(); break;
        case 5: _t->displayInfo(); break;
        case 6: _t->displaySettings(); break;
        case 7: _t->enableNFC(); break;
        case 8: _t->getFbID(); break;
        case 9: _t->getLiID(); break;
        case 10: _t->goToAppPage(); break;
        case 11: _t->goToAppReviewPage(); break;
        case 12: _t->goToPrivacyPolicy(); break;
        case 13: _t->goToRubus(); break;
        case 14: _t->goToSV(); break;
        case 15: _t->handleConnector((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 16: _t->handleExit(); break;
        case 17: _t->handleHelpSlider((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 18: _t->handleHelpSliderImm((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 19: _t->handleTabChange((*reinterpret_cast< bb::cascades::Tab*(*)>(_a[1]))); break;
        case 20: _t->handleToastFinish(); break;
        case 21: _t->onInvoked((*reinterpret_cast< const bb::system::InvokeRequest(*)>(_a[1]))); break;
        case 22: _t->onListViewTriggered((*reinterpret_cast< const QVariantList(*)>(_a[1]))); break;
        case 23: _t->openFB(); break;
        case 24: _t->openLI(); break;
        case 25: _t->registrationStateUpdated((*reinterpret_cast< bb::platform::bbm::RegistrationState::Type(*)>(_a[1]))); break;
        case 26: _t->setContentForHelp(); break;
        case 27: _t->setContentToShare(); break;
        case 28: _t->shareApp(); break;
        case 29: _t->shareFBChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 30: _t->shareLIChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 31: _t->submitted(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ApplicationUI::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ApplicationUI::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ApplicationUI,
      qt_meta_data_ApplicationUI, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ApplicationUI::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ApplicationUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ApplicationUI::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ApplicationUI))
        return static_cast<void*>(const_cast< ApplicationUI*>(this));
    return QObject::qt_metacast(_clname);
}

int ApplicationUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 32)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 32;
    }
    return _id;
}
static const uint qt_meta_data_MyItemClass[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x08,
      27,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MyItemClass[] = {
    "MyItemClass\0\0connectToFB()\0connectToLI()\0"
};

void MyItemClass::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MyItemClass *_t = static_cast<MyItemClass *>(_o);
        switch (_id) {
        case 0: _t->connectToFB(); break;
        case 1: _t->connectToLI(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData MyItemClass::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MyItemClass::staticMetaObject = {
    { &bb::cascades::CustomControl::staticMetaObject, qt_meta_stringdata_MyItemClass,
      qt_meta_data_MyItemClass, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MyItemClass::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MyItemClass::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MyItemClass::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyItemClass))
        return static_cast<void*>(const_cast< MyItemClass*>(this));
    if (!strcmp(_clname, "ListItemListener"))
        return static_cast< ListItemListener*>(const_cast< MyItemClass*>(this));
    typedef bb::cascades::CustomControl QMocSuperClass;
    return QMocSuperClass::qt_metacast(_clname);
}

int MyItemClass::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    typedef bb::cascades::CustomControl QMocSuperClass;
    _id = QMocSuperClass::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
