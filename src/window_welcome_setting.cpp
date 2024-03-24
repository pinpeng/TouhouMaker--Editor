#include "window_welcome_setting.h"

#include <QDesktopServices>
#include <QApplication>

Window_welcome_setting::Window_welcome_setting(QWidget *parent) : SmallWindow(parent)
{
    setFixedSize(1200, 640);
    setWindowTitle("设置（部分设置可能需要重启程序才能应用）");

    button_accept = new Widget_Button(this);
    button_accept->setGeometry(320, 546, 240, 80);
    button_accept->setText("确定");
    button_accept->setTimer(_timer);

    button_cancel = new Widget_Button(this);
    button_cancel->setGeometry(640, 546, 240, 80);
    button_cancel->setText("取消");
    button_cancel->setTimer(_timer);

    connect(button_accept, SIGNAL(pressed()), this, SLOT(save()));
    connect(button_cancel, SIGNAL(pressed()), this, SLOT(end()));

    ////////////////////////////////////////////////////////////////////////////////////////////////////////

    chooseButton_color = new Widget_ChooseButton(this);
    chooseButton_color->setGeometry(640 - 32, 64, 320, 70);
    chooseButton_color->addText("默认");
    chooseButton_color->addText("浅灰");
    chooseButton_color->addText("深色");
    chooseButton_color->addText("自定义");
    chooseButton_color->setTimer(_timer);

    chooseButton_color->setIndex(Global::setting.global_color_group);

    button_custom = new Widget_Button(this);
    button_custom->setGeometry(960 - 32, 64, 240, 80);
    button_custom->setText("参数文件");
    button_custom->setTimer(_timer);
    connect(button_custom, SIGNAL(pressed()), this, SLOT(color_custom()));

    ////////////////////////////////////////////////////////////////////////////////////////////////////////

    dragStick_scale_editor = new Widget_DragStick(this);
    dragStick_scale_editor->setGeometry(640 - 32, 144, 560, 80);
    dragStick_scale_editor->setTimer(_timer);
    dragStick_scale_editor->setRange(50, 150);
    dragStick_scale_editor->setValue(Global::setting.editor_scale * 100.0);

    dragStick_scale_timeline = new Widget_DragStick(this);
    dragStick_scale_timeline->setGeometry(640 - 32, 224, 560, 80);
    dragStick_scale_timeline->setTimer(_timer);
    dragStick_scale_timeline->setRange(50, 150);
    dragStick_scale_timeline->setValue(Global::setting.timeline_scale * 100.0);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////

    chooseButton_antialising = new Widget_ChooseButton(this);
    chooseButton_antialising->setGeometry(640 - 32, 304, 560, 70);
    chooseButton_antialising->addText("开启（较慢）");
    chooseButton_antialising->addText("关闭（较快）");
    chooseButton_antialising->setTimer(_timer);
    if(Global::setting.stage_antialising == true)  chooseButton_antialising->setIndex(0);
    if(Global::setting.stage_antialising == false) chooseButton_antialising->setIndex(1);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*chooseButton_tips = new Widget_ChooseButton(this);
    chooseButton_tips->setGeometry(640 - 32, 384, 560, 70);
    chooseButton_tips->addText("全部开启");
    chooseButton_tips->addText("仅重要提示");
    chooseButton_tips->addText("关闭并隐藏");
    chooseButton_tips->setTimer(_timer);
    chooseButton_tips->setIndex(Global::setting.tips_action);
*/
}

void Window_welcome_setting::paintEvent(QPaintEvent *)
{
    Draw::smallWindow(this, this);
    Draw::begin(this);
    Draw::setAntialising();
    Draw::setTextDefault();
    setPenColor_c(c_textMain);
    Draw::text(32, 100, "全局配色", Qt::AlignLeft | Qt::AlignVCenter);
    Draw::text(32, 180, "主界面缩放倍数", Qt::AlignLeft | Qt::AlignVCenter);
    Draw::text(32, 260, "时间轴区域缩放倍数", Qt::AlignLeft | Qt::AlignVCenter);
    Draw::text(32, 340, "抗锯齿", Qt::AlignLeft | Qt::AlignVCenter);
    //Draw::text(32, 420, "看板娘功能", Qt::AlignLeft | Qt::AlignVCenter);
    Draw::end();
}

void Window_welcome_setting::color_custom()
{
    if(!QFile::exists(QApplication::applicationDirPath() + "/color.ini")) Col::save();
    if(!QDesktopServices::openUrl(QUrl::fromLocalFile(QApplication::applicationDirPath() + "/color.ini"))) {
        Message("打不开文件啊");
    }
}

void Window_welcome_setting::save()
{
    if(chooseButton_color->getIndex() == 0) {
        Global::setting.global_color_group = 0;
        Col::list[Col::c_backgroundMain] = QColor(255, 255, 255);
        Col::list[Col::c_backgroundSub] =  QColor(236, 236, 236);
        Col::list[Col::c_textMain] =       QColor(32, 32, 32);
        Col::list[Col::c_textTitle] =      QColor(64, 64, 64);
        Col::list[Col::c_symbol] =         QColor(192, 192, 192);
        Col::list[Col::c_theme] =          QColor(0, 128, 255);
        Col::list[Col::c_itemEdge] =       QColor(128, 128, 128);
        Col::list[Col::c_inactive] =       QColor(32, 32, 32);
    } else if(chooseButton_color->getIndex() == 1) {
        Global::setting.global_color_group = 1;
        Col::list[Col::c_backgroundMain] =    QColor(236, 236, 236);
        Col::list[Col::c_backgroundSub] =     QColor(212, 212, 212);
        Col::list[Col::c_textMain] =          QColor(0, 0, 0);
        Col::list[Col::c_textTitle] =         QColor(32, 32, 32);
        Col::list[Col::c_symbol] =            QColor(160, 160, 160);
        //Col::list[Col::c_theme] =             QColor(0, 108, 255);
        Col::list[Col::c_theme] =             QColor(0, 128, 255);
        Col::list[Col::c_itemEdge] =          QColor(108, 108, 108);
        Col::list[Col::c_inactive] =          QColor(16, 16, 16);
    } else if(chooseButton_color->getIndex() == 2) {
        Global::setting.global_color_group = 2;
        Col::list[Col::c_backgroundMain] =    QColor(45, 45, 45);
        Col::list[Col::c_backgroundSub] =     QColor(32, 32, 32);
        Col::list[Col::c_textMain] =          QColor(224, 224, 224);
        Col::list[Col::c_textTitle] =         QColor(192, 192, 192);
        Col::list[Col::c_symbol] =            QColor(128, 128, 128);
        //Col::list[Col::c_theme] =             QColor(16, 144, 255);
        Col::list[Col::c_theme] =             QColor(0, 128, 255);
        Col::list[Col::c_itemEdge] =          QColor(160, 160, 160);
        Col::list[Col::c_inactive] =          QColor(128, 128, 128);
    } else { // custom
        Global::setting.global_color_group = 3;
        Col::read();
    }

    Global::setting.editor_scale = dragStick_scale_editor->getValue() / 100.0;
    Global::setting.timeline_scale = dragStick_scale_timeline->getValue() / 100.0;

    Global::setting.stage_antialising = chooseButton_antialising->getIndex() == 0? true: false;
    Global::setting.tips_action = 0;//chooseButton_tips->getIndex();

    Global::setting.save();
    end();
}
