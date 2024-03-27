// #ifndef WINDOW_FIND_VIDEO_H
// #define WINDOW_FIND_VIDEO_H

// #include "window_small.h"
// #include "widget/gradientButton.h"
// #include "widget/ellipticalLineEdit.h"
// #include "widget/widget_itemlist.h"
// #include "widget/widget_roundbutton.h"

// #include "global.h"

// class Window_find_video : public Window_small
// {
//     Q_OBJECT

// public:

//     explicit Window_find_video(Database *_db, QWidget *parent = nullptr);

//     void paintEvent(QPaintEvent *);

// private:
//     Database *db;

//     QString type_arr[6] = {"长视频", "长视频文件夹", "短视频", "短视频文件夹", "脚本", "脚本文件夹"};
//     QButtonGroup *buttonBox_type;
//     Widget_RoundButton *roundButton_all;
//     Widget_RoundButton *roundButton_1;
//     Widget_RoundButton *roundButton_2;
//     Widget_RoundButton *roundButton_3;

//     EllipticalLineEdit *lineEdit;
//     GradientButton *button_find;
//     Widget_ItemList *itemList;

// public slots:
//     void find();
//     void getPosition(int pos);

// signals:
//     void doubleClicked(int id);
// };

// #endif // WINDOW_FIND_VIDEO_H
