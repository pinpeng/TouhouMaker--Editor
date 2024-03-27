#ifndef WINDOW_EDITOR_MAIN_H
#define WINDOW_EDITOR_MAIN_H

#include <QWidget>
#include <QTimer>

#include <QLayout>

#include <QGraphicsEffect>

#include "window_editor_stage.h"
#include "window_editor_menubar.h"
#include "window_editor_treelist.h"
#include "window_editor_timeline.h"


#include "widget/transparentDialog.h"

#include "window_ask.h"

class Window_editor_main : public QWidget
{
    Q_OBJECT

private:

    QVBoxLayout *mainLayout;

    Window_editor_menubar  *window_menubar;
    Window_editor_stage    *window_stage;
    Window_editor_treelist *window_treelist;
    Window_editor_timeline *window_timeline;

    Window_ask *window_ask;

public:
    explicit Window_editor_main(QWidget *parent = nullptr);
    QWidget *homepage;

    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *event);

    bool isEnding = false;

    static int id1;
    static int id2;
    static int id3;

public slots:
    void backToHome();
    void undo();
    void redo();
    void save();
    void pack();

    void ending();

    void stageUpdateListCall(int);

signals:
    void stageKeyArrow();
    void stageKeyMove();
    void stageKeyCut();
    void stageKeySelect();
    void stageKeyBrush();

    void stageUpdateList(int);

};

#endif // WINDOW_EDITOR_MAIN_H
