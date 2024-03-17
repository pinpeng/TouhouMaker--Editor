#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "draw.h"
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(640, 480);

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    buttonNewProj   = new Widget_Button(this);
    buttonOpenProj  = new Widget_Button(this);
    buttonSetting   = new Widget_Button(this);

    buttonNewProj->setText("新建项目");
    buttonNewProj->setGeometry(200, 190, 240, 80);
    buttonNewProj->show();
    connect(buttonNewProj, SIGNAL(pressed()), this, SLOT(newProj()));

    buttonOpenProj->setText("打开...");
    buttonOpenProj->setGeometry(200, 270, 240, 80);
    buttonOpenProj->show();
    connect(buttonOpenProj, SIGNAL(pressed()), this, SLOT(openProj()));

    buttonSetting->setText("设置");
    buttonSetting->setGeometry(200, 350, 240, 80);
    buttonSetting->show();
    connect(buttonSetting, SIGNAL(pressed()), this, SLOT(setting()));


    buttonClose = new Widget_ButtonClose(this);
    buttonClose->show();
    connect(buttonClose, SIGNAL(pressed()), this, SLOT(close()));

    sprite_logo.load(":/logo/mscb.png");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *) {
    buttonClose->setGeometry(rect().right() - 60, rect().top() + 12, 40, 40);

    float w_l = rect().x() + 8;
    float w_r = rect().right() - 8;
    float w_t = rect().y() + 8;
    float w_b = rect().bottom() - 8;

    Draw::begin(this);
    Draw::setAntialising(true);

    if(isActiveWindow()) Draw::setPenColor(0, 128, 255);
    else Draw::setPenColor(32, 32, 32);

    Draw::setBrushColor(255, 255, 255);
    Draw::roundRect(w_l, w_t, w_r, w_b, 8, 3);

    Draw::setPenColor(128, 128, 128);
    Draw::line(w_l + 12, w_t + 48, w_r - 8, w_t + 48, 1);

    Draw::setTextFont("微软雅黑");
    Draw::setTextSize(18);
    Draw::setPenColor(64, 64, 64);
    Draw::text(w_l + 32, w_t + 24, "欢迎使用MSC", Qt::AlignLeft | Qt::AlignVCenter);

    Draw::sprite(w_l + 88, w_t + 56, sprite_logo);
    Draw::setPenColor(0, 128, 255);
    Draw::setTextSize(12);
    Draw::text(w_l + 32, w_b - 6, "(C)2022-2023 Meboxen Studio", Qt::AlignLeft | Qt::AlignBottom);
    Draw::text(w_r - 24, w_b - 6, "Ver 0.0.0.1", Qt::AlignRight | Qt::AlignBottom);

    Draw::end();
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        if(event->pos().y() > rect().y() + 8 && event->pos().y() < rect().y() + 56) {
            isMoving = true;
            startMovingPos = event->pos();
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if(isMoving) {
        move(pos() + event->pos() - startMovingPos);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    isMoving = false;
}

void MainWindow::newProj()
{
    win_newProj = new Window_welcome_newProject();
    win_newProj->setWindowModality(Qt::ApplicationModal);
    win_newProj->setAttribute(Qt::WA_DeleteOnClose);
    win_newProj->show();
}

void MainWindow::openProj()
{

}

void MainWindow::setting()
{

}


