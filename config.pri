# Config.pri file version 2.0. Auto-generated by IDE. Any changes made by user will be lost!
BASEDIR = $$quote($$_PRO_FILE_PWD_)

device {
    CONFIG(debug, debug|release) {
        !profile {
            CONFIG += \
                config_pri_assets \
                config_pri_source_group1
        }
    }

    CONFIG(release, debug|release) {
        !profile {
            CONFIG += \
                config_pri_assets \
                config_pri_source_group1
        }
    }
}

config_pri_assets {
    OTHER_FILES += \
        $$quote($$BASEDIR/assets/images/fb.png) \
        $$quote($$BASEDIR/assets/images/fbLarge.png) \
        $$quote($$BASEDIR/assets/images/fbLargePressed.png) \
        $$quote($$BASEDIR/assets/images/fbPressed.png) \
        $$quote($$BASEDIR/assets/images/icons/ic_bbm.png) \
        $$quote($$BASEDIR/assets/images/icons/ic_clear_list.png) \
        $$quote($$BASEDIR/assets/images/icons/ic_done.png) \
        $$quote($$BASEDIR/assets/images/icons/ic_info.png) \
        $$quote($$BASEDIR/assets/images/icons/ic_nfc.png) \
        $$quote($$BASEDIR/assets/images/icons/ic_review.png) \
        $$quote($$BASEDIR/assets/images/icons/ic_save_as.png) \
        $$quote($$BASEDIR/assets/images/icons/ic_share.png) \
        $$quote($$BASEDIR/assets/images/icons/ic_view_list.png) \
        $$quote($$BASEDIR/assets/images/li.png) \
        $$quote($$BASEDIR/assets/images/liLarge.png) \
        $$quote($$BASEDIR/assets/images/liLargePressed.png) \
        $$quote($$BASEDIR/assets/images/liPressed.png) \
        $$quote($$BASEDIR/assets/images/logos/logo.png) \
        $$quote($$BASEDIR/assets/images/logos/logoPressed.png) \
        $$quote($$BASEDIR/assets/images/logos/rubus.png) \
        $$quote($$BASEDIR/assets/images/logos/rubusPressed.png) \
        $$quote($$BASEDIR/assets/images/logos/sv.png) \
        $$quote($$BASEDIR/assets/images/logos/svPressed.png) \
        $$quote($$BASEDIR/assets/main.qml)
}

config_pri_source_group1 {
    SOURCES += \
        $$quote($$BASEDIR/src/applicationui.cpp) \
        $$quote($$BASEDIR/src/main.cpp)

    HEADERS += $$quote($$BASEDIR/src/applicationui.hpp)
}

INCLUDEPATH += $$quote($$BASEDIR/src)

CONFIG += precompile_header

PRECOMPILED_HEADER = $$quote($$BASEDIR/precompiled.h)

lupdate_inclusion {
    SOURCES += \
        $$quote($$BASEDIR/../src/*.c) \
        $$quote($$BASEDIR/../src/*.c++) \
        $$quote($$BASEDIR/../src/*.cc) \
        $$quote($$BASEDIR/../src/*.cpp) \
        $$quote($$BASEDIR/../src/*.cxx) \
        $$quote($$BASEDIR/../assets/*.qml) \
        $$quote($$BASEDIR/../assets/*.js) \
        $$quote($$BASEDIR/../assets/*.qs) \
        $$quote($$BASEDIR/../assets/images/*.qml) \
        $$quote($$BASEDIR/../assets/images/*.js) \
        $$quote($$BASEDIR/../assets/images/*.qs) \
        $$quote($$BASEDIR/../assets/images/icons/*.qml) \
        $$quote($$BASEDIR/../assets/images/icons/*.js) \
        $$quote($$BASEDIR/../assets/images/icons/*.qs) \
        $$quote($$BASEDIR/../assets/images/logos/*.qml) \
        $$quote($$BASEDIR/../assets/images/logos/*.js) \
        $$quote($$BASEDIR/../assets/images/logos/*.qs)

    HEADERS += \
        $$quote($$BASEDIR/../src/*.h) \
        $$quote($$BASEDIR/../src/*.h++) \
        $$quote($$BASEDIR/../src/*.hh) \
        $$quote($$BASEDIR/../src/*.hpp) \
        $$quote($$BASEDIR/../src/*.hxx)
}

TRANSLATIONS = $$quote($${TARGET}.ts)
