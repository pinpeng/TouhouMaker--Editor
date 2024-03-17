#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "widget_button.h"
#include "widget_buttonClose.h"

#include "window_welcome_newproject.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void newProj();
    void openProj();
    void setting();

private:
    Ui::MainWindow *ui;

    bool isMoving = false;
    QPoint startMovingPos;

    Widget_ButtonClose *buttonClose;
    QPixmap sprite_logo;

    Widget_Button *buttonNewProj;
    Widget_Button *buttonOpenProj;
    Widget_Button *buttonSetting;

    Window_welcome_newProject *win_newProj;


};
#endif // MAINWINDOW_H
