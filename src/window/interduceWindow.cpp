#include "window/interduceWindow.h"
#include <QFileDialog>
#include "global.h"
#include "sprite.h"

#include <QMouseEvent>
#include <QDesktopServices>
#include <QApplication>

InterduceWindow::InterduceWindow(QWidget *parent) : SmallWindow(parent)
{
    setFixedSize(720, 560);
    setWindowTitle("欢迎使用THMK");
    setWindowIcon(QIcon(":/logo/mscb_icon.ico"));

    QDir dir(Global::setting.global_last_path);
    if(dir.exists() && !Global::setting.global_last_path.isEmpty()) {
        show_last = true;
        show_last_name = Global::setting.global_last_name;
    }

    _newProjectButton   =   new GradientButton("新建项目",QRect(240, 185, 240, 80),this);
    _openProjectButton  =   new GradientButton("打开...",QRect(240, 265, 240, 80),this);
    _settingButton      =   new GradientButton("程序设置",QRect(240, 345, 240, 80),this);
    _helpButton         =   new GradientButton("帮助",QRect(240, 425, 240, 80),this);

    connect(_newProjectButton, SIGNAL(pressed()), this, SLOT(newProjectSlot()));
    connect(_openProjectButton, SIGNAL(pressed()), this, SLOT(openProjectSlot()));
    connect(_settingButton, SIGNAL(pressed()), this, SLOT(settingSlot()));
    connect(_helpButton, SIGNAL(pressed()), this, SLOT(helpSlot()));
}

InterduceWindow::~InterduceWindow() {

}

void InterduceWindow::paintEvent(QPaintEvent *event) {

    SmallWindow::paintEvent(event);

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

    // TODO... 后续修改成按钮
    Draw::sprite(Sprite(logo_mscb), width() / 2 - 256, w_t + 50);
    setPenColor_c(c_theme);
    Draw::setTextDefault();
    Draw::setTextSize(12);
    Draw::text(w_l + 32, w_b - 12, "Ver 0.1.1 测试版\n(C)2024 Meboxen Studio", Qt::AlignLeft | Qt::AlignBottom);

    Draw::sprite_size(Sprite(ui_author_web), w_r - 160, w_b - 144, 144, 144);

    if(show_last) {
        // TODO... 后续修改成按钮
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

void InterduceWindow::mousePressEvent(QMouseEvent *event)
{
    SmallWindow::mousePressEvent(event);
    if(event->button() == Qt::LeftButton) {
        // TODO... 后续修改成按钮
        float w_l = rect().x() + 8;
        float w_r = rect().right() - 8;
        float w_t = rect().y() + 8;
        float w_b = rect().bottom() - 8;

        float mx = event->pos().x();
        float my = event->pos().y();
        if(w_r - 160 < mx && w_b - 100 < my) {
            QDesktopServices::openUrl(QUrl("https://space.bilibili.com/179047896"));
        }
        // TODO... 后续修改成按钮
        if(show_last) {
            if(w_l + 490 < mx && mx < w_l + 690 && w_t + 280 - 50 < my && my < w_t + 280 + 30) {
                QString str = Global::setting.global_last_path;
                Database db;
                if(db.read(str)) {
                    TransparentDialog::play("无法打开文件");
                } else {
                    TransparentDialog::play("打开成功");
                    db.info.projectPosition = str;
                    Global::databaseClean();
                    Global::databaseUpdate(db);
                    Global::setting.global_last_name = Global::databaseInfo().projectName;
                    Global::setting.global_last_path = Global::databaseInfo().projectPosition;
                    Global::setting.save();
                    openStartSlot();
                }
            }
        }
    }
}

void InterduceWindow::newProjectSlot()
{
    _newProjectWindow = new NewProjectWindow();
    _newProjectWindow->setWindowModality(Qt::ApplicationModal);
    _newProjectWindow->setAttribute(Qt::WA_DeleteOnClose);
    _newProjectWindow->show();
    connect(_newProjectWindow, SIGNAL(requestClose()), this, SLOT(newStartSlot()));
}

void InterduceWindow::openProjectSlot()
{
    QString str = QFileDialog::getOpenFileName(this, "打开项目文件", "./", "(*.thmkproj)");
    if(!str.isEmpty())
    {
        str = QFileInfo(str).absoluteDir().absolutePath();
        Database db;
        if(db.read(str)) {
            TransparentDialog::play("无法打开文件");
        } else {
            TransparentDialog::play("打开成功");
            db.info.projectPosition = str;
            Global::databaseClean();
            Global::databaseUpdate(db);
            Global::setting.global_last_name = Global::databaseInfo().projectName;
            Global::setting.global_last_path = Global::databaseInfo().projectPosition;
            Global::setting.save();
            openStartSlot();
        }
    }
}

void InterduceWindow::settingSlot()
{
    win_setting = new Window_welcome_setting();
    win_setting->setWindowModality(Qt::ApplicationModal);
    win_setting->setAttribute(Qt::WA_DeleteOnClose);
    win_setting->show();
}

void InterduceWindow::helpSlot()
{
    if(!QDesktopServices::openUrl(QUrl::fromLocalFile(QApplication::applicationDirPath() + "/help.pdf"))) {
        TransparentDialog::play(this, "帮不了你了");
    }
}

void InterduceWindow::newStartSlot()
{
    win_editor = new Window_editor_main();
    win_editor->homepage = this;
    win_editor->setWindowModality(Qt::ApplicationModal);
    win_editor->setAttribute(Qt::WA_DeleteOnClose);
    win_editor->show();
    close();
}

void InterduceWindow::openStartSlot()
{
    win_editor = new Window_editor_main();
    win_editor->homepage = this;
    win_editor->setWindowModality(Qt::ApplicationModal);
    win_editor->setAttribute(Qt::WA_DeleteOnClose);
    win_editor->show();
    close();
}
