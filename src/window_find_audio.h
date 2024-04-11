#ifndef WINDOW_FIND_AUDIO_H
#define WINDOW_FIND_AUDIO_H

#include "window/smallWindow.h"
#include "widget/gradientButton.h"
#include "widget/ellipticalLineEdit.h"
#include "widget/itemlist.h"
#include "widget/roundButton.h"

#include "dataSet/cacheAgent.h"

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
    RoundButton *roundButton_all;
    RoundButton *roundButton_1;
    RoundButton *roundButton_2;
    RoundButton *roundButton_3;

    EllipticalLineEdit *lineEdit;
    GradientButton *button_find;
    ItemList *itemList;

public slots:
    void find();
    void getPosition(int pos);

signals:
    void doubleClicked(int id);
};

#endif // WINDOW_FIND_AUDIO_H
