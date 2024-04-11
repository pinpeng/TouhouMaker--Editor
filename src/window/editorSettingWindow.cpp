#include "window/editorSettingWindow.h"

#include <QDesktopServices>
#include <QApplication>

EditorSettingWindow::EditorSettingWindow(QWidget *parent) : SmallWindow(parent)
{
    setFixedSize(1200, 640);
    setWindowTitle("设置（部分设置可能需要重启程序才能应用）");

    button_accept = new GradientButton(this);
    button_accept->setGeometry(320, 546, 240, 80);
    button_accept->setText("确定");
    // button_accept->setTimer(_timer);

    button_cancel = new GradientButton(this);
    button_cancel->setGeometry(640, 546, 240, 80);
    button_cancel->setText("取消");
    // button_cancel->setTimer(_timer);

    connect(button_accept, SIGNAL(pressed()), this, SLOT(save()));
    connect(button_cancel, SIGNAL(pressed()), this, SLOT(end()));

    ////////////////////////////////////////////////////////////////////////////////////////////////////////

    chooseButton_color = new ChooseButton(this);
    chooseButton_color->setGeometry(640 - 32, 64, 320, 70);
    chooseButton_color->addText("默认");
    chooseButton_color->addText("浅灰");
    chooseButton_color->addText("深色");
    chooseButton_color->addText("自定义");
    // chooseButton_color->setTimer(_timer);

    chooseButton_color->setIndex(CacheAgent::getInstance().setting.themeColor());

    button_custom = new GradientButton(this);
    button_custom->setGeometry(960 - 32, 64, 240, 80);
    button_custom->setText("参数文件");
    // button_custom->setTimer(_timer);
    connect(button_custom, SIGNAL(pressed()), this, SLOT(color_custom()));

    ////////////////////////////////////////////////////////////////////////////////////////////////////////

    dragStick_scale_editor = new Widget_DragStick(this);
    dragStick_scale_editor->setGeometry(640 - 32, 144, 560, 80);
    dragStick_scale_editor->setTimer(_timer);
    dragStick_scale_editor->setRange(50, 150);
    dragStick_scale_editor->setValue(CacheAgent::getInstance().setting.editorScale() * 100.0);

    dragStick_scale_timeline = new Widget_DragStick(this);
    dragStick_scale_timeline->setGeometry(640 - 32, 224, 560, 80);
    dragStick_scale_timeline->setTimer(_timer);
    dragStick_scale_timeline->setRange(50, 150);
    dragStick_scale_timeline->setValue(CacheAgent::getInstance().setting.timelineScale() * 100.0);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////

    chooseButton_antialising = new ChooseButton(this);
    chooseButton_antialising->setGeometry(640 - 32, 304, 560, 70);
    chooseButton_antialising->addText("开启（较慢）");
    chooseButton_antialising->addText("关闭（较快）");
    // chooseButton_antialising->setTimer(_timer);
    if(CacheAgent::getInstance().setting.stageAntialising() == true){
        chooseButton_antialising->setIndex(0);
    }
    else{
        chooseButton_antialising->setIndex(1);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*chooseButton_tips = new ChooseButton(this);
    chooseButton_tips->setGeometry(640 - 32, 384, 560, 70);
    chooseButton_tips->addText("全部开启");
    chooseButton_tips->addText("仅重要提示");
    chooseButton_tips->addText("关闭并隐藏");
    chooseButton_tips->setTimer(_timer);
    chooseButton_tips->setIndex(CacheAgent::getInstance().setting.tips_action);
*/
}

void EditorSettingWindow::paintEvent(QPaintEvent *)
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

void EditorSettingWindow::color_custom()
{
    if(!QFile::exists(QApplication::applicationDirPath() + "/color.ini")) Col::save();
    if(!QDesktopServices::openUrl(QUrl::fromLocalFile(QApplication::applicationDirPath() + "/color.ini"))) {
        TransparentDialog::play("打不开文件啊");
    }
}

void EditorSettingWindow::save()
{
    // TODO... 后续Draw当中的主题画笔配置，用json在外部记录
    if(chooseButton_color->getIndex() == 0) {
        CacheAgent::getInstance().setting.setThemeColor(ThemeColor::DEFAULT);
        // Col::list[Col::c_backgroundMain] = QColor(255, 255, 255);
        // Col::list[Col::c_backgroundSub] =  QColor(236, 236, 236);
        // Col::list[Col::c_textMain] =       QColor(32, 32, 32);
        // Col::list[Col::c_textTitle] =      QColor(64, 64, 64);
        // Col::list[Col::c_symbol] =         QColor(192, 192, 192);
        // Col::list[Col::c_theme] =          QColor(0, 128, 255);
        // Col::list[Col::c_itemEdge] =       QColor(128, 128, 128);
        // Col::list[Col::c_inactive] =       QColor(32, 32, 32);
    } else if(chooseButton_color->getIndex() == 1) {
        CacheAgent::getInstance().setting.setThemeColor(ThemeColor::GRAY);
        // Col::list[Col::c_backgroundMain] =    QColor(236, 236, 236);
        // Col::list[Col::c_backgroundSub] =     QColor(212, 212, 212);
        // Col::list[Col::c_textMain] =          QColor(0, 0, 0);
        // Col::list[Col::c_textTitle] =         QColor(32, 32, 32);
        // Col::list[Col::c_symbol] =            QColor(160, 160, 160);
        // //Col::list[Col::c_theme] =             QColor(0, 108, 255);
        // Col::list[Col::c_theme] =             QColor(0, 128, 255);
        // Col::list[Col::c_itemEdge] =          QColor(108, 108, 108);
        // Col::list[Col::c_inactive] =          QColor(16, 16, 16);
    } else if(chooseButton_color->getIndex() == 2) {
        CacheAgent::getInstance().setting.setThemeColor(ThemeColor::DARK);
        // Col::list[Col::c_backgroundMain] =    QColor(45, 45, 45);
        // Col::list[Col::c_backgroundSub] =     QColor(32, 32, 32);
        // Col::list[Col::c_textMain] =          QColor(224, 224, 224);
        // Col::list[Col::c_textTitle] =         QColor(192, 192, 192);
        // Col::list[Col::c_symbol] =            QColor(128, 128, 128);
        // //Col::list[Col::c_theme] =             QColor(16, 144, 255);
        // Col::list[Col::c_theme] =             QColor(0, 128, 255);
        // Col::list[Col::c_itemEdge] =          QColor(160, 160, 160);
        // Col::list[Col::c_inactive] =          QColor(128, 128, 128);
    } else { // custom
        CacheAgent::getInstance().setting.setThemeColor(ThemeColor::CUSTOM);
        // Col::read();
    }

    CacheAgent::getInstance().setting.setEditorScale(dragStick_scale_editor->getValue() / 100.0);
    // CacheAgent::getInstance().setting.editor_scale = dragStick_scale_editor->getValue() / 100.0;
    CacheAgent::getInstance().setting.setTimelineScale(dragStick_scale_timeline->getValue() / 100.0);

    CacheAgent::getInstance().setting.setStageAntialising(chooseButton_antialising->getIndex() == 0? true: false);
    CacheAgent::getInstance().setting.setTipsAction(0);//chooseButton_tips->getIndex();

    CacheAgent::getInstance().setting.save();
    end();
}
