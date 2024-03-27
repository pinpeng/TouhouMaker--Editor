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
    dataSet/database/database.cpp \
    dataSet/database/entity/database_define.cpp \
    dataSet/database/database_define_edit.cpp \
    dataSet/database/database_info.cpp \
    dataSet/database/database_main.cpp \
    dataSet/database/database_main_edit.cpp \
    dataSet/database/database_save.cpp \
    draw.cpp \
    global.cpp \
    logModule/logmodule.cpp \
    main.cpp \
    widget/transparentDialog.cpp \
    sprite.cpp \
    toolkit/fileoperator.cpp \
    toolkit/timeoperator.cpp \
    widget/gradientButton.cpp \
    widget/closeButton.cpp \
    widget/widget_choosebutton.cpp \
    widget/widget_dragstick.cpp \
    widget/widget_itemlist.cpp \
    widget/ellipticalLineEdit.cpp \
    widget/widget_roundbutton.cpp \
    widget/widget_textEdit.cpp \
    window/interduceWindow.cpp \
    window/newProjectWindow.cpp \
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
    window/smallWindow.cpp \
    window_welcome_setting.cpp \

HEADERS += \
    basethread.h \
    globalSource/SourceAgent.h \
    globalSource/fontManager.h \
    globalSource/timerManager.h \
    # database
    dataSet/database/sqliteUtil.h \
    dataSet/database/database.h \
    dataSet/database/entity/database_define.h \
    dataSet/database/database_info.h \
    dataSet/database/database_main.h \
    draw.h \
    global.h \
    logModule/logmodule.h \
    widget/transparentDialog.h \
    qzipreader_p.h \
    qzipwriter_p.h \
    setting.h \
    sprite.h \
    toolkit/fileoperator.h \
    toolkit/timeoperator.h \
    widget/gradientButton.h \
    widget/closeButton.h \
    widget/widget_choosebutton.h \
    widget/widget_dragstick.h \
    widget/widget_itemlist.h \
    widget/ellipticalLineEdit.h \
    widget/widget_roundbutton.h \
    widget/widget_textEdit.h \
    window/interduceWindow.h \
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
    window/smallWindow.h \
    window/newProjectWindow.h \
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

