#ifndef WINDOW_EDITOR_MENUBAR_BULLET_H
#define WINDOW_EDITOR_MENUBAR_BULLET_H

#include "window/smallWindow.h"
#include "widget/gradientButton.h"
#include "widget/roundButton.h"
#include "widget/ellipticalLineEdit.h"
#include "widget/itemlist.h"

#include "dataSet/cacheAgent.h"

#include "window/editor/menuBar/bulletEditor.h"


class BulletInfoList : public SmallWindow
{
    Q_OBJECT

public:

    explicit BulletInfoList(QWidget *parent = nullptr);

private:

    Database db;

    QButtonGroup *_bulletselectgroup;
    RoundButton *roundButton[3];

    ItemList *itemList;

    GradientButton *_addbutton;
    GradientButton *_delbutton;

    GradientButton *_acceptbutton;
    GradientButton *_cancelbutton;

    BulletEditor *window_editor;

    int _curListGroup;
private:

    void editBulletStart(int index);

public slots:
    void updateList();
    void accept();

    void editBullet(int index);

    void add();
    void del();
};

#endif // WINDOW_EDITOR_MENUBAR_BULLET_H
