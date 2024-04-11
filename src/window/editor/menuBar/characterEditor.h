#ifndef WINDOW_EDITOR_MENUBAR_HERO_H
#define WINDOW_EDITOR_MENUBAR_HERO_H

#include "window/smallWindow.h"
#include "widget/gradientButton.h"
#include "widget/roundButton.h"
#include "widget/chooseButton.h"
#include "widget/ellipticalLineEdit.h"
#include "widget/itemlist.h"

#include "dataSet/cacheAgent.h"

#include "window_editor_menubar_hero_edit.h"


class CharacterEditor : public SmallWindow
{
    Q_OBJECT

public:

    explicit CharacterEditor(QWidget *parent = nullptr);

private:

    Database db;

    ItemList *_itemList;

    ChooseButton *chooseButton;

    QButtonGroup *_characterGroup;
    RoundButton *roundButton[3];

    GradientButton *_addButton;
    GradientButton *_delButton;

    GradientButton *_acceptButton;
    GradientButton *_cancelButton;

    Window_editor_menubar_hero_edit0 *window_editor0;
    Window_editor_menubar_hero_edit1 *window_editor1;
    Window_editor_menubar_hero_edit2 *window_editor2;

    void editHeroStart(int index);

public slots:
    /**
     * @brief 刷新列表
    */
    void updateList();
    void accept();

    void editHero(int index);

    void add();
    void del();
};

#endif // WINDOW_EDITOR_MENUBAR_HERO_H
