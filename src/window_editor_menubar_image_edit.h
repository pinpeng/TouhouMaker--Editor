#ifndef WINDOW_EDITOR_MENUBAR_IMAGE_EDIT_H
#define WINDOW_EDITOR_MENUBAR_IMAGE_EDIT_H

#include "window_small.h"

#include "widget_lineEdit.h"
#include "widget_button.h"
#include "widget_roundbutton.h"

#include "memoryCache/cacheAgent.h"

class Window_editor_menubar_image_edit : public Window_small
{

    Q_OBJECT

public:
    explicit Window_editor_menubar_image_edit(ProjectData *_db, MemoryCache::ImageInfo *_file, QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *) override;

private:
    ProjectData *db;
    MemoryCache::ImageInfo *file;

    Widget_LineEdit *lineEdit;
    Widget_Button *button_open;
    Widget_Button *button_preview;

    QString state_arr[3] = {"未保存", "已保存", "已保存"};

public slots:
    void end() override;

    void open();
    void preview();

};

#endif // WINDOW_EDITOR_MENUBAR_IMAGE_EDIT_H
