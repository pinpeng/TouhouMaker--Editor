#ifndef WINDOW_FIND_AUDIO_H
#define WINDOW_FIND_AUDIO_H

#include "window/smallWindow.h"
#include "widget/gradientButton.h"
#include "widget/ellipticalLineEdit.h"
#include "widget/widget_itemlist.h"
#include "widget/widget_roundbutton.h"

#include "global.h"

class Window_find_audio : public SmallWindow
{
    Q_OBJECT

public:

    explicit Window_find_audio(Database *_db, QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);

private:
    Database *db;

    QString type_arr[6] = {"音乐", "音乐文件夹", "音效", "音效文件夹", "配音", "配音文件夹"};
    QButtonGroup *buttonBox_type;
    Widget_RoundButton *roundButton_all;
    Widget_RoundButton *roundButton_1;
    Widget_RoundButton *roundButton_2;
    Widget_RoundButton *roundButton_3;

    EllipticalLineEdit *lineEdit;
    GradientButton *button_find;
    Widget_ItemList *itemList;

public slots:
    void find();
    void getPosition(int pos);

signals:
    void doubleClicked(int id);
};

#endif // WINDOW_FIND_AUDIO_H
