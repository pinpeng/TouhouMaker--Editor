#ifndef WINDOW_EDITOR_TIMELINE_H
#define WINDOW_EDITOR_TIMELINE_H

#include <QWidget>
#include <QTimer>

#include "database.h"
#include "draw.h"

#include <QWidget>
#include <QTimer>

#include "database.h"
#include "draw.h"

#include "window/smallWindow.h"
#include "widget_button.h"
#include "widget_roundbutton.h"

class Window_editor_timeline_insert : public SmallWindow
{
    Q_OBJECT
public:
    explicit Window_editor_timeline_insert(Database *_db, int _time, int _stage_type, int _stage_id, QWidget *parent = nullptr);

private:

    void paintEvent(QPaintEvent *);

    void mousePressEvent(QMouseEvent *event);

    Database *db;
    int time;
    int stage_type;
    int stage_id;

    void createEvent(int _index);

};

struct _pair {
    int a, b;
    _pair() { a = 0; b = 0; }
    _pair(int _a, int _b) { a = _a; b = _b; }
};

class Window_editor_timeline : public QWidget
{
    Q_OBJECT
public:
    explicit Window_editor_timeline(QWidget *parent = nullptr);
    ~Window_editor_timeline();

    void paintEvent(QPaintEvent *);

    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *event);

    static float view_max;
    static float view_left;
    static float view_right;

private:
    BaseThread *timer;

    Database db;

    float mx, my;
    float rbx, rby, rbt, rbi;

    QLineF poly0[7];
    QLineF poly1[10];
    QLineF poly2[18];
    QLineF poly3[12];
    QLineF poly4[12];

    float buff_x = -10000;
    float buff_update = 0;

    QPixmap pixmap_timeline;
    QPixmap pixmap_timeline_final;

    float mouse_x = 0.0;
    float mouse_y = 0.0;
    int mouse_down = 0;
    float mouse_scale_pos = 0.0f;

    int repaintTimer = 0;

    float alpha_toolBox[4] = { 0.0, 0.0, 0.0, 0.0 };
    int toolBox_selected = 0;
    float alpha_toolBoxSelected[4] = { 0.0, 0.0, 0.0, 0.0 };


    QList<_pair> eventBossTime;

    QList<int> eventHotPoint;
    int eventIndex = -1;

    void lb_main(float mx, float my);
    void rb_main(float mx, float my);

    void lb_toolBox(float mx, float my);
    void lb_scale(float mx, float my);

    bool lbr_brush();

    void drawMain(QRectF _rect);

    void drawToolBox(QRectF _rect);
    void drawScale(QRectF _rect);

    void drawMenu();

    Window_editor_timeline_insert *window_insertEvent;


    void insertEvent(int _time);
    void deleteEvent(int _index);

signals:
    void requestUpdate(int _request_id);

private slots:
    void timeoutRepaint();

    void insertEventFinished();
/*
    void keyArrow();
    void keyMove();
    void keyCut();
    void keySelect();
    void keyBrush();
*/
    void updateFromOutside(int _request_id);

};

#endif // WINDOW_EDITOR_TIMELINE_H
