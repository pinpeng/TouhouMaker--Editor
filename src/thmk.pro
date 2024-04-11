QT       += core gui
QT       += gui-private
QT       += opengl
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

VERSION = 0.0.1

DEFINES += APP_VERSION=\\\"$$VERSION\\\"

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    basethread.cpp \
    globalSource/SourceAgent.cpp \
    globalSource/fontManager.cpp \
    globalSource/timerManager.cpp \
    # database
    dataSet/database/sqliteUtil.cpp \
    dataSet/memoryCache/database.cpp \
    dataSet/memoryCache/database_define.cpp \
    dataSet/memoryCache/database_define_edit.cpp \
    dataSet/memoryCache/database_info.cpp \
    dataSet/memoryCache/database_main.cpp \
    dataSet/memoryCache/database_main_edit.cpp \
    dataSet/memoryCache/database_save.cpp \
    dataSet/editorSetting.cpp \
    draw.cpp \
    dataSet/cacheAgent.cpp \
    logModule/logmodule.cpp \
    main.cpp \
    widget/transparentDialog.cpp \
    sprite.cpp \
    toolkit/fileoperator.cpp \
    toolkit/timeoperator.cpp \
    widget/gradientButton.cpp \
    widget/closeButton.cpp \
    widget/choosebutton.cpp \
    widget/widget_dragstick.cpp \
    widget/itemlist.cpp \
    widget/ellipticalLineEdit.cpp \
    widget/roundbutton.cpp \
    widget/widget_textEdit.cpp \
    window/interduceWindow.cpp \
    window/newProjectWindow.cpp \
    window_ask.cpp \
    window/editor/mainEditorWindow.cpp \
    window/editor/menuBar/editorMenubar.cpp \
    window_editor_menubar_audio.cpp \
    window_editor_menubar_audio_edit.cpp \
    window_editor_menubar_bullet.cpp \
    window_editor_menubar_bullet_edit.cpp \
    window_editor_menubar_effect.cpp \
    window_editor_menubar_effect_edit.cpp \
    window/editor/menuBar/characterEditor.cpp \
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
    window/smallWindow.cpp \
    window/editorSettingWindow.cpp \

HEADERS += \
    basethread.h \
    globalSource/SourceAgent.h \
    globalSource/fontManager.h \
    globalSource/timerManager.h \
    # dataSet
    dataSet/database/sqliteUtil.h \
    dataSet/memoryCache/database.h \
    dataSet/memoryCache/database_define.h \
    dataSet/memoryCache/database_info.h \
    dataSet/memoryCache/database_main.h \
    draw.h \
    dataSet/cacheAgent.h \
    logModule/logmodule.h \
    widget/transparentDialog.h \
    qzipreader_p.h \
    qzipwriter_p.h \
    dataSet/editorSetting.h \
    sprite.h \
    toolkit/fileoperator.h \
    toolkit/timeoperator.h \
    widget/gradientButton.h \
    widget/closeButton.h \
    widget/choosebutton.h \
    widget/widget_dragstick.h \
    widget/itemlist.h \
    widget/ellipticalLineEdit.h \
    widget/roundbutton.h \
    widget/widget_textEdit.h \
    window/interduceWindow.h \
    window_ask.h \
    window/editor/mainEditorWindow.h \
    window/editor/menuBar/editorMenubar.h \
    window_editor_menubar_audio.h \
    window_editor_menubar_audio_edit.h \
    window_editor_menubar_bullet.h \
    window_editor_menubar_bullet_edit.h \
    window_editor_menubar_effect.h \
    window_editor_menubar_effect_edit.h \
    window/editor/menuBar/characterEditor.h \
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
    window/smallWindow.h \
    window/newProjectWindow.h \
    window/editorSettingWindow.h

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

