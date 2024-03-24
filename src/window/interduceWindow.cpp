#include "window/interduceWindow.h"

#include <QFileDialog>
#include "global.h"
#include "sprite.h"

#include <QMouseEvent>
#include <QDesktopServices>
#include <QApplication>

Window_welcome_main::Window_welcome_main(QWidget *parent) : SmallWindow(parent)
{
    setFixedSize(720, 560);
    setWindowTitle("欢迎使用THMK");
    setWindowIcon(QIcon(":/logo/mscb_icon.ico"));

    QDir dir(Global::setting.global_last_path);
    if(dir.exists() && !Global::setting.global_last_path.isEmpty()) {
        show_last = true;
        show_last_name = Global::setting.global_last_name;
    }

    buttonNewProj   = new Widget_Button(this);
    buttonOpenProj  = new Widget_Button(this);
    buttonSetting   = new Widget_Button(this);
    buttonHelp      = new Widget_Button(this);


    buttonNewProj->setText("新建项目");
    buttonNewProj->setGeometry(240, 185, 240, 80);
    buttonNewProj->show();
    buttonNewProj->setTimer(_timer);
    connect(buttonNewProj, SIGNAL(pressed()), this, SLOT(newProj()));

    buttonOpenProj->setText("打开...");
    buttonOpenProj->setGeometry(240, 265, 240, 80);
    buttonOpenProj->show();
    buttonOpenProj->setTimer(_timer);
    connect(buttonOpenProj, SIGNAL(pressed()), this, SLOT(openProj()));

    buttonSetting->setText("程序设置");
    buttonSetting->setGeometry(240, 345, 240, 80);
    buttonSetting->show();
    buttonSetting->setTimer(_timer);
    connect(buttonSetting, SIGNAL(pressed()), this, SLOT(setting()));

    buttonHelp->setText("帮助");
    buttonHelp->setGeometry(240, 425, 240, 80);
    buttonHelp->show();
    buttonHelp->setTimer(_timer);
    connect(buttonHelp, SIGNAL(pressed()), this, SLOT(help()));

    //Window_editor_stage_tips *tips = new Window_editor_stage_tips();
    //tips->show();
//    connect(buttonHelp, SIGNAL(pressed()), this, SLOT(help()));

    //newStart();
}

Window_welcome_main::~Window_welcome_main() {

}

void Window_welcome_main::paintEvent(QPaintEvent *) {

    Draw::smallWindow(this, this);

    QDir dir(Global::setting.global_last_path);
    if(dir.exists() && !Global::setting.global_last_path.isEmpty()) {
        show_last = true;
        show_last_name = Global::setting.global_last_name;
    }

    float w_l = rect().x() + 8;
    float w_r = rect().right() - 8;
    float w_t = rect().y() + 8;
    float w_b = rect().bottom() - 8;

    Draw::begin(this);
    Draw::setAntialising(true);

    Draw::sprite(Sprite(logo_mscb), width() / 2 - 256, w_t + 50);
    setPenColor_c(c_theme);
    Draw::setTextDefault();
    Draw::setTextSize(12);
    Draw::text(w_l + 32, w_b - 12, "Ver 0.1.1 测试版\n(C)2024 Meboxen Studio", Qt::AlignLeft | Qt::AlignBottom);

    Draw::sprite_size(Sprite(ui_author_web), w_r - 160, w_b - 144, 144, 144);

    if(show_last) {
        setPenColor_c(c_theme);
        setBrushColor_c(c_theme);
        Draw::triangle(w_l + 480, w_t + 310, w_l + 480 + 20, w_t + 300 - 15, w_l + 480 + 30, w_t + 300, 4);
        setBrushColor_c(c_backgroundMain);
        Draw::roundRect(w_l + 495, w_t + 280 - 40, w_l + 685, w_t + 280 + 20, 4, 4);
        Draw::setTextSize(10);
        Draw::font.setBold(1);
        Draw::text_line_with_length(w_l + 505, w_t + 246, "上次打开的项目：", 155, Qt::AlignLeft | Qt::AlignTop);
        Draw::text_line_with_length(w_l + 505, w_t + 270, show_last_name, 155, Qt::AlignLeft | Qt::AlignTop);
        Draw::font.setBold(0);
    }

    Draw::end();
}

void Window_welcome_main::mousePressEvent(QMouseEvent *event)
{
    SmallWindow::mousePressEvent(event);
    if(event->button() == Qt::LeftButton) {
        float w_l = rect().x() + 8;
        float w_r = rect().right() - 8;
        float w_t = rect().y() + 8;
        float w_b = rect().bottom() - 8;

        float mx = event->pos().x();
        float my = event->pos().y();
        if(w_r - 160 < mx && w_b - 100 < my) {
            QDesktopServices::openUrl(QUrl("https://space.bilibili.com/179047896"));
        }
        if(show_last) {
            if(w_l + 490 < mx && mx < w_l + 690 && w_t + 280 - 50 < my && my < w_t + 280 + 30) {
                QString str = Global::setting.global_last_path;
                Database db;
                if(db.read(str)) {
                    Message("无法打开文件");
                } else {
                    Message("打开成功");
                    db.info.projectPosition = str;
                    Global::databaseClean();
                    Global::databaseUpdate(db);
                    Global::setting.global_last_name = Global::databaseInfo().projectName;
                    Global::setting.global_last_path = Global::databaseInfo().projectPosition;
                    Global::setting.save();
                    openStart();
                }
            }
        }
    }
}

void Window_welcome_main::newProj()
{
    win_newProj = new Window_welcome_newProject();
    win_newProj->setWindowModality(Qt::ApplicationModal);
    win_newProj->setAttribute(Qt::WA_DeleteOnClose);
    win_newProj->show();
    connect(win_newProj, SIGNAL(requestClose()), this, SLOT(newStart()));
}

void Window_welcome_main::openProj()
{
    QString str = QFileDialog::getOpenFileName(this, "打开项目文件", "./", "(*.thmkproj)");
    if(!str.isEmpty())
    {
        str = QFileInfo(str).absoluteDir().absolutePath();
        Database db;
        if(db.read(str)) {
            Message("无法打开文件");
        } else {
            Message("打开成功");
            db.info.projectPosition = str;
            Global::databaseClean();
            Global::databaseUpdate(db);
            Global::setting.global_last_name = Global::databaseInfo().projectName;
            Global::setting.global_last_path = Global::databaseInfo().projectPosition;
            Global::setting.save();
            openStart();
        }
    }
}

void Window_welcome_main::setting()
{
    win_setting = new Window_welcome_setting();
    win_setting->setWindowModality(Qt::ApplicationModal);
    win_setting->setAttribute(Qt::WA_DeleteOnClose);
    win_setting->show();
}

void Window_welcome_main::help()
{
    if(!QDesktopServices::openUrl(QUrl::fromLocalFile(QApplication::applicationDirPath() + "/help.pdf"))) {
        Message_Box::play(this, "帮不了你了");
    }
}

void Window_welcome_main::newStart()
{
    win_editor = new Window_editor_main();
    win_editor->homepage = this;
    win_editor->setWindowModality(Qt::ApplicationModal);
    win_editor->setAttribute(Qt::WA_DeleteOnClose);
    win_editor->show();
    close();
}

void Window_welcome_main::openStart()
{
    win_editor = new Window_editor_main();
    win_editor->homepage = this;
    win_editor->setWindowModality(Qt::ApplicationModal);
    win_editor->setAttribute(Qt::WA_DeleteOnClose);
    win_editor->show();
    close();
}
