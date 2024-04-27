#include "window_editor_menubar.h"

#include "draw.h"
#include "global.h"
#include "message_box.h"

#include <QDesktopServices>
#include <QApplication>
#include <QMouseEvent>

#include <complex>

#include "window_editor_stage_tips.h"

#include "qzipwriter_p.h"

Window_editor_menubar::Window_editor_menubar(QWidget *parent) : QWidget(parent)
{

    setAttribute(Qt::WA_TranslucentBackground);
    setFixedHeight(80.0 * Global::setting.editor_scale);
    setMouseTracking(true);

    memset(items_alpha, 0, sizeof(items_alpha));

    timer = new BaseThread();
    connect(timer, SIGNAL(timeout()), this, SLOT(timeoutRepaint()));
    timer->start();

}

void Window_editor_menubar::drawItems(float left, float top)
{
    static QString text_arr[12] = {"保存", "导出", "撤销", "重做", "设置", "角色", "子弹", "图像", "特效", "音频", "文本", "帮助"};

    float ss = Global::setting.editor_scale;

    setPenColor_c(c_symbol);
    Draw::line(left + 80 * ss * 4 - 4 * ss, top + 12 * ss, left + 80 * ss * 4 - 4 * ss, top + 64 * ss, 2 * ss);
    setBrushColor_false();
    Draw::setTextDefault();
    Draw::setTextSize(12 * ss);
    for(int i = 0; i < 12; i ++) {

        if(left + 80 * ss * i <= mouse_x && mouse_x < left + 80 * ss * i + 80 * ss) {
            items_alpha[i] = qMin(float(items_alpha[i] + 0.1), float(1.0));
        } else {
            items_alpha[i] = qMax(float(items_alpha[i] - 0.1), float(0.0));
        }
        setPenColor_ca(c_theme, items_alpha[i] * 255.0);

        float mid_x = left + 80 * ss * i + 40 * ss;

        Draw::text(mid_x, top + 60 * ss, text_arr[i], Qt::AlignCenter);
        float _size = (64 - items_alpha[i] * 16) * ss;

        Draw::sprite(Spr::sprite_menu_func[i].transformed(
                         QMatrix().scale(_size / 128.0, _size / 128.0), Qt::SmoothTransformation),
                    mid_x - _size / 2, top + 4 * ss);
    }

}

void Window_editor_menubar::paintEvent(QPaintEvent *)
{
    float ss = Global::setting.editor_scale;

    if(!underMouse()) {
        mouse_x = 0;
        mouse_y = 0;
    }
    Draw::begin(this);
    Draw::setAntialising(true);

    float left = rect().left() + 4;
    float top = rect().top() + 4;

    Draw::sprite(Sprite(logo_msc).transformed(QMatrix().scale(ss * 142.0 / 284.0, ss * 64.0 / 128.0), Qt::SmoothTransformation),
                      left, top);

    ////////////////////////////////////////

    left += 160 * ss;

    setPenColor_false();
    setBrushColor_c(c_backgroundMain);
    Draw::roundRect(left, rect().top(), rect().right() - 4, rect().bottom(), 6);

    drawItems(left, top);

    Draw::end();
}

void Window_editor_menubar::mousePressEvent(QMouseEvent *event)
{
    float ss = Global::setting.editor_scale;
    mouse_x = event->pos().x();
    mouse_y = event->pos().y();
    float w_l = rect().left() + 4 + 160 * ss;
    if(mouse_x < w_l) {
        window_ask = new Window_ask("  确定要回到主菜单吗？未保存的内容将消失！");
        window_ask->setWindowModality(Qt::ApplicationModal);
        window_ask->setAttribute(Qt::WA_DeleteOnClose);
        window_ask->show();
        connect(window_ask, SIGNAL(OK()), this, SLOT(backToHome()));
    }
    if(w_l < mouse_x) {
        if(mouse_x < w_l + 12 * 80 * ss) {
            if(mouse_x < w_l + 1 * 80 * ss) { // save
                save();
            } else if(mouse_x < w_l + 2 * 80 * ss) { // pack
                pack();
            } else if(mouse_x < w_l + 3 * 80 * ss) { // undo
                emit requestUndo();
            } else if(mouse_x < w_l + 4 * 80 * ss) { // redo
                emit requestRedo();
            } else if(mouse_x < w_l + 5 * 80 * ss) { // game setting
                func0();
            } else if(mouse_x < w_l + 6 * 80 * ss) { // character
                func1();
            } else if(mouse_x < w_l + 7 * 80 * ss) { // bullet
                func2();
            } else if(mouse_x < w_l + 8 * 80 * ss) { // image
                func3();
            } else if(mouse_x < w_l + 9 * 80 * ss) { // effect
                func4();
            } else if(mouse_x < w_l + 10 * 80 * ss) { // audio
                func5();
            } else if(mouse_x < w_l + 11 * 80 * ss) { // text
                func6();
            } else if(mouse_x < w_l + 12 * 80 * ss) { // help
                func7();
            }
        }
    }

}

void Window_editor_menubar::mouseMoveEvent(QMouseEvent *event)
{
    mouse_x = event->pos().x();
    mouse_y = event->pos().y();
}

void Window_editor_menubar::pack_final()
{
    QDir path = QApplication::applicationDirPath() + "/output";
    if(!path.exists()) {
        path.mkdir(path.path());
    }
    QString pack_path = Global::databaseInfo().projectPosition + "/output/";
    QString runner_path = QApplication::applicationDirPath() + "/runner/";

    QString file_path = path.path() + "/" + Global::databaseInfo().projectName + ".zip";
    if(QFile::exists(file_path)) {
        QFile test(file_path);
        if(!test.open(QIODevice::ReadWrite)) {
            Message("文件占用中");
            return;
        }
        test.close();
        QFile::remove(file_path);
    }

    auto zip = new QZipWriter(file_path);

    QFile file;
    QStringList file_name_list0 = {
        "audio.thmk",
        "image.thmk",
        "effect.thmk",
        "bullet.thmk",
        "character.thmk",
        "audio.thmk",
        "main.thmk",
        "setting.txt",
        "text.json"
    };
    QStringList file_name_list1 = {
        "runner.exe",
        "options.ini",
        "mword.json",
        "msetting.json",
        "jcyt500W.ttf",
        "data.win"
    };

    for(int i = 0; i < file_name_list0.size(); i ++) {
        file.setFileName(pack_path + file_name_list0[i]);
        if(!file.exists()) {
            Message("打包失败");
            delete zip;
            return;
        }
        file.open(QIODevice::ReadOnly);
        zip->addFile(file_name_list0[i], file.readAll());
        file.close();
    }
    for(int i = 0; i < file_name_list1.size(); i ++) {
        file.setFileName(runner_path + file_name_list1[i]);
        if(!file.exists()) {
            Message("打包失败");
            delete zip;
            return;
        }
        file.open(QIODevice::ReadOnly);
        zip->addFile(file_name_list1[i], file.readAll());
        file.close();
    }
    zip->close();

    delete zip;

    if(!QDesktopServices::openUrl(QUrl::fromLocalFile(path.path()))) {
        Message("无法打开文件夹");
    }

}

void Window_editor_menubar::timeoutRepaint()
{
    if(!isActiveWindow()) return;
    repaint();
}

void Window_editor_menubar::backToHome()
{
    emit requestBackToHome();
}

void Window_editor_menubar::save()
{
    if(Global::database().save()) {
        Message("保存失败");
        send_tips(2);
    } else {
        Message("保存成功");
        send_tips(1);
    }
}

void Window_editor_menubar::pack()
{
    if(Global::database().save()) {
        Message("保存失败");
        send_tips(4);
    } else {
        if(Global::database().pack()) {
            Message("导出失败");
            send_tips(4);
        } else {
            send_tips(3);
            pack_final();
        }
    }
}

void Window_editor_menubar::func0()
{
    Message("功能开发中");
    /*
    window_func0 = new Window_editor_menubar_setting();
    window_func0->setWindowModality(Qt::ApplicationModal);
    window_func0->setAttribute(Qt::WA_DeleteOnClose);
    connect(window_func0, SIGNAL(closed()), this, SLOT(stageUpdateListCall()));
    window_func0->show();
    */
}

void Window_editor_menubar::func1()
{
    window_func1 = new Window_editor_menubar_hero();
    window_func1->setWindowModality(Qt::ApplicationModal);
    window_func1->setAttribute(Qt::WA_DeleteOnClose);
    connect(window_func1, SIGNAL(closed()), this, SLOT(stageUpdateListCall()));
    window_func1->show();
}

void Window_editor_menubar::func2()
{
    window_func2 = new Window_editor_menubar_bullet();
    window_func2->setWindowModality(Qt::ApplicationModal);
    window_func2->setAttribute(Qt::WA_DeleteOnClose);
    connect(window_func2, SIGNAL(closed()), this, SLOT(stageUpdateListCall()));
    window_func2->show();
}

void Window_editor_menubar::func3()
{
    window_func3 = new Window_editor_menubar_image();
    window_func3->setWindowModality(Qt::ApplicationModal);
    window_func3->setAttribute(Qt::WA_DeleteOnClose);
    connect(window_func3, SIGNAL(closed()), this, SLOT(stageUpdateListCall()));
    window_func3->show();
}

void Window_editor_menubar::func4()
{
    //Message("功能开发中");
    window_func4 = new Window_editor_menubar_effect();
    window_func4->setWindowModality(Qt::ApplicationModal);
    window_func4->setAttribute(Qt::WA_DeleteOnClose);
    connect(window_func4, SIGNAL(closed()), this, SLOT(stageUpdateListCall()));
    window_func4->show();
}

void Window_editor_menubar::func5()
{
    window_func5 = new Window_editor_menubar_audio();
    window_func5->setWindowModality(Qt::ApplicationModal);
    window_func5->setAttribute(Qt::WA_DeleteOnClose);
    connect(window_func5, SIGNAL(closed()), this, SLOT(stageUpdateListCall()));
    window_func5->show();
}

void Window_editor_menubar::func6()
{
    window_func6 = new Window_editor_menubar_text();
    window_func6->setWindowModality(Qt::ApplicationModal);
    window_func6->setAttribute(Qt::WA_DeleteOnClose);
    connect(window_func6, SIGNAL(closed()), this, SLOT(stageUpdateListCall()));
    window_func6->show();
}


void Window_editor_menubar::func7()
{
    if(!QDesktopServices::openUrl(QUrl::fromLocalFile(QApplication::applicationDirPath() + "/help.pdf"))) {
        Message_Box::play(this, "帮不了你了");
        send_tips(0);
    }
}

void Window_editor_menubar::stageUpdateListCall()
{
    emit requestUpdate(1);
}















