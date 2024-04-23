#ifndef WINDOW_EDITOR_MENUBAR_H
#define WINDOW_EDITOR_MENUBAR_H

#include <QWidget>

#include <QTimer>

#include "window_small.h"

#include "window_ask.h"

#include "window_editor_menubar_setting.h"
#include "window_editor_menubar_hero.h"
#include "window_editor_menubar_bullet.h"
#include "window_editor_menubar_audio.h"
#include "window_editor_menubar_image.h"
#include "window_editor_menubar_effect.h"
#include "window_editor_menubar_text.h"



class Window_editor_menubar : public QWidget
{
    Q_OBJECT
public:
    explicit Window_editor_menubar(QWidget *parent = nullptr);

    void drawItems(float left, float top);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    float items_alpha[12];

    BaseThread *timer;

    Window_ask *window_ask;

    float mouse_x;
    float mouse_y;

    Window_editor_menubar_setting    *window_func0;
    Window_editor_menubar_hero       *window_func1;
    Window_editor_menubar_bullet     *window_func2;
    Window_editor_menubar_image      *window_func3;
    Window_editor_menubar_effect     *window_func4;
    Window_editor_menubar_audio      *window_func5;
    Window_editor_menubar_text       *window_func6;

    void pack_final();

signals:
    void requestUndo();
    void requestRedo();

    void requestUpdate(int _request_id);

    void requestBackToHome();

public slots:
    void timeoutRepaint();

    void backToHome();
    void save();
    void pack();

    void func0(); // setting
    void func1(); // hero
    void func2(); // bullet
    void func3(); // image
    void func4(); // effect
    void func5(); // audio
    void func6(); // text
    void func7(); // help

    void stageUpdateListCall();

};

#endif // WINDOW_EDITOR_MENUBAR_H
