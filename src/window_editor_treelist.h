#ifndef WINDOW_EDITOR_TREELIST_H
#define WINDOW_EDITOR_TREELIST_H

#include <QWidget>

#include <QTimer>

#include <QGraphicsEffect>

#include "widget_button.h"



#include "dataSet/database/database.h"

class Window_editor_main;


class Window_editor_treelist : public QWidget
{
    Q_OBJECT
public:
    explicit Window_editor_treelist(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

    void drawTop();

    void mouseClickSelect0(float mx, float my, float _top);
    void mouseClickSelect1(float mx, float my, float _top);
    void mouseClickSelect2(float mx, float my, float _top);

    void drawItems_0(float _top);
    bool drawItems_1(float _top);
    bool drawItems_2(float _top);

    void renameFromOutside();

    void changeState();

private:
    BaseThread *timer;

    Database db;

    float item_top = 0.0;
    int item_checked = -1;

    int id_now = -1;


signals:
    void requestUpdate(int _request_id);

public slots:
    void timeoutRepaint();

    void updateFromOutside(int _request_id);

public:

    bool state = 0;
    float state_timer = 0;
    float state_change = 0;

    Window_editor_main *fatherWindow;

};

#endif // WINDOW_EDITOR_TREELIST_H
