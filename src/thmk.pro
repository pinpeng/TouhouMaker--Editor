QT       += core gui
QT       += gui-private
QT       += opengl
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += thread exceptions rtti stl
macx: LIBS += -framework AppKit

win32:CONFIG(release, debug|release): {
LIBS += -L$$PWD/thirdParty/qBreakPad/lib/release/ -lqBreakpad
DEPENDPATH += $$PWD/thirdParty/qBreakPad/lib/release
}
else:win32:CONFIG(debug, debug|release): {
LIBS += -L$$PWD/thirdParty/qBreakPad/lib/debug/ -lqBreakpad
DEPENDPATH += $$PWD/thirdParty/qBreakPad/lib/debug
}

INCLUDEPATH += $$PWD/thirdParty/qBreakPad/include

QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO

VERSION = 0.0.1

DEFINES += APP_VERSION=\\\"$$VERSION\\\"

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    # memoryCache
        # interface
    memoryCache/interface/IMemoryData.cpp \
        # globalEntity
    memoryCache/globalEntity/editorSetting.cpp \
    memoryCache/globalEntity/projectInfo.cpp \
        # projectEntity
    memoryCache/projectEntity/audioInfo.cpp \
    memoryCache/projectEntity/bulletInfo.cpp \
    memoryCache/projectEntity/characterInfo.cpp \
    memoryCache/projectEntity/enemyInfo.cpp \
    memoryCache/projectEntity/imageInfo.cpp \
    memoryCache/projectEntity/playerInfo.cpp \
    memoryCache/projectEntity/projectData.cpp \
    memoryCache/projectEntity/textInfo.cpp \
    # globalSource
    globalSource/sourceAgent.cpp \
    globalSource/fontManager.cpp \
    globalSource/imageManager.cpp \
    globalSource/timerManager.cpp \
    # logModule
    logModule/logmodule.cpp \
    # toolkit
    toolkit/fileoperator.cpp \
    toolkit/timeoperator.cpp \
    database.cpp \
    database_define.cpp \
    database_define_edit.cpp \
    database_info.cpp \
    database_main.cpp \
    database_main_edit.cpp \
    database_save.cpp \
    draw.cpp \
    global.cpp \
    main.cpp \
    message_box.cpp \
    sprite.cpp \
    widget_button.cpp \
    widget_buttonClose.cpp \
    widget_choosebutton.cpp \
    widget_dragstick.cpp \
    widget_itemlist.cpp \
    widget_lineEdit.cpp \
    widget_roundbutton.cpp \
    widget_textEdit.cpp \
    window_ask.cpp \
    window_editor_main.cpp \
    window_editor_menubar.cpp \
    window_editor_menubar_audio.cpp \
    window_editor_menubar_audio_edit.cpp \
    window_editor_menubar_bullet.cpp \
    window_editor_menubar_bullet_edit.cpp \
    window_editor_menubar_effect.cpp \
    window_editor_menubar_effect_edit.cpp \
    window_editor_menubar_hero.cpp \
    window_editor_menubar_hero_edit.cpp \
    window_editor_menubar_image.cpp \
    window_editor_menubar_image_edit.cpp \
    window_editor_menubar_setting.cpp \
    window_editor_menubar_setting_language.cpp \
    window_editor_menubar_text.cpp \
    window_editor_stage.cpp \
    window_editor_stage_tips.cpp \
    window_editor_timeline.cpp \
    window_editor_treelist.cpp \
    window_find.cpp \
    window_small.cpp \
    window_welcome_main.cpp \
    window_welcome_newproject.cpp \
    window_welcome_setting.cpp

HEADERS += \
    # memoryCache
        # interface
    memoryCache/interface/IMemoryData.h \
        # globalEntity
    memoryCache/globalEntity/editorSetting.h \
    memoryCache/globalEntity/projectInfo.h \
        # projectEntity
    memoryCache/projectEntity/audioInfo.h \
    memoryCache/projectEntity/bulletInfo.h \
    memoryCache/projectEntity/characterInfo.h \
    memoryCache/projectEntity/enemyInfo.h \
    memoryCache/projectEntity/imageInfo.h \
    memoryCache/projectEntity/playerInfo.h \
    memoryCache/projectEntity/projectData.h \
    memoryCache/projectEntity/textInfo.h \
    # globalSource
    globalSource/sourceAgent.h \
    globalSource/fontManager.h \
    globalSource/imageManager.h \
    globalSource/timerManager.h \
    # logmodule
    logModule/logmodule.h \
    # toolkit
    toolkit/fileoperator.h \
    toolkit/timeoperator.h \
    database.h \
    database_define.h \
    database_info.h \
    database_main.h \
    draw.h \
    global.h \
    message_box.h \
    qzipreader_p.h \
    qzipwriter_p.h \
    setting.h \
    sprite.h \
    widget_button.h \
    widget_buttonClose.h \
    widget_choosebutton.h \
    widget_dragstick.h \
    widget_itemlist.h \
    widget_lineEdit.h \
    widget_roundbutton.h \
    widget_textEdit.h \
    window_ask.h \
    window_editor_main.h \
    window_editor_menubar.h \
    window_editor_menubar_audio.h \
    window_editor_menubar_audio_edit.h \
    window_editor_menubar_bullet.h \
    window_editor_menubar_bullet_edit.h \
    window_editor_menubar_effect.h \
    window_editor_menubar_effect_edit.h \
    window_editor_menubar_hero.h \
    window_editor_menubar_hero_edit.h \
    window_editor_menubar_image.h \
    window_editor_menubar_image_edit.h \
    window_editor_menubar_setting.h \
    window_editor_menubar_setting_language.h \
    window_editor_menubar_text.h \
    window_editor_stage.h \
    window_editor_stage_tips.h \
    window_editor_timeline.h \
    window_editor_treelist.h \
    window_find.h \
    window_small.h \
    window_welcome_main.h \
    window_welcome_newproject.h \
    window_welcome_setting.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images/images.qrc \
    shaders/shaders.qrc

DISTFILES += \
    mscb临时标题.png

RC_ICONS = thmk.ico

#LIBS     += -luser32
LIBS     += -lgdi32
LIBS     += -lOpenGl32

