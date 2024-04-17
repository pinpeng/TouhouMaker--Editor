#ifndef WINDOW_EDITOR_MENUBAR_IMAGE_H
#define WINDOW_EDITOR_MENUBAR_IMAGE_H

#include "window/smallWindow.h"
#include "widget/gradientButton.h"
#include "widget/roundButton.h"
#include "widget/ellipticalLineEdit.h"
#include "widget/itemlist.h"

#include "dataSet/cacheAgent.h"

#include "window/editor/menuBar/imageEditor.h"

#include "window_find.h"

class ImageInfoList : public SmallWindow
{
    Q_OBJECT

public:

    explicit ImageInfoList(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);

private:

    Database db;

    QButtonGroup *select_group;
    RoundButton *roundButton[4];

    GradientButton *button_openFolder;

    ItemList *itemList;

    GradientButton *button_add;
    GradientButton *button_del;

    GradientButton *button_accept;
    GradientButton *button_cancel;

    QString state_arr[3] = {"未保存", "已保存", "已保存"};

    QLabel *label;

    ImageEditor *window_editor;

    void editAudioStart(int index);

public slots:
    void updateList();
    void accept();

    void editAudio(int index);
    void openFolder();

    void add();
    void del();
};

#endif // WINDOW_EDITOR_MENUBAR_IMAGE_H
