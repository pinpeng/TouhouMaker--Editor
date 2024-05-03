#include "window_welcome_newproject.h"

#include <QFileDialog>

#include "message_box.h"

#include "draw.h"

#include "memoryCache/cacheAgent.h"

Window_welcome_newProject::Window_welcome_newProject(QWidget *parent) : Window_small(parent)
{
    setFixedSize(1200, 480);
    setWindowTitle("新建项目");

    lineEdit_projectName = new Widget_LineEdit(this);
    lineEdit_projectName->setGeometry(32, 116, 1136, 80);
    lineEdit_projectName->setText("New Project");

    lineEdit_projectPosition = new Widget_LineEdit(this);
    lineEdit_projectPosition->setGeometry(32, 248, 896, 80);
    lineEdit_projectPosition->setText("");

    button_changePostion = new Widget_Button(this);
    button_changePostion->setGeometry(32 + 896, 248, 240, 80);
    button_changePostion->setText("浏览...");
    button_changePostion->setTimer(timer);

    connect(button_changePostion, SIGNAL(pressed()), this, SLOT(findDir()));

    buttonBox_type = new QButtonGroup(this);

    round_base = new Widget_RoundButton(this);
    round_base->setText("基本项目");
    round_base->setGeometry(250, 336, 240, 40);
    round_base->setTimer(timer);
    round_base->setChecked(true);

    round_empty = new Widget_RoundButton(this);
    round_empty->setText("空白项目");
    round_empty->setGeometry(450, 336, 240, 40);
    round_empty->setTimer(timer);

    round_example = new Widget_RoundButton(this);
    round_example->setText("示例项目");
    round_example->setGeometry(650, 336, 240, 40);
    round_example->setTimer(timer);

    buttonBox_type->addButton(round_base);
    buttonBox_type->addButton(round_empty);
    buttonBox_type->addButton(round_example);

    button_accept = new Widget_Button(this);
    button_accept->setGeometry(320, 386, 240, 80);
    button_accept->setText("创建");
    button_accept->setTimer(timer);

    button_cancel = new Widget_Button(this);
    button_cancel->setGeometry(640, 386, 240, 80);
    button_cancel->setText("取消");
    button_cancel->setTimer(timer);

    connect(button_accept, SIGNAL(pressed()), this, SLOT(createProject()));
    connect(button_cancel, SIGNAL(pressed()), this, SLOT(end()));
}

Window_welcome_newProject::~Window_welcome_newProject() {

}

void Window_welcome_newProject::paintEvent(QPaintEvent *)
{
    Draw::smallWindow(this, this);
    Draw::begin(this);
    setPenColor_c(c_textMain);
    Draw::setTextDefault();
    Draw::text(64, 106 - 24 + 10, "项目名称", Qt::AlignLeft | Qt::AlignVCenter);
    Draw::text(64, 228 - 24 + 20, "项目位置", Qt::AlignLeft | Qt::AlignVCenter);
    Draw::text(64, 356, "预设类型", Qt::AlignLeft | Qt::AlignVCenter);

    Draw::end();
}

void Window_welcome_newProject::findDir()
{
    QString pos = QFileDialog::getExistingDirectory();
    if(pos != "") {
        lineEdit_projectPosition->setText(pos);
    }
}

void Window_welcome_newProject::createProject()
{
    if(lineEdit_projectPosition->text().isEmpty()) {
        Message_Box::play(this, "目录不能为空");
        return;
    }
    QDir dir = lineEdit_projectPosition->text();
    if(!dir.exists()) {
        Message_Box::play(this, "目录不存在");
        return;
    }

    CacheAgent::getInstance().databaseInit(lineEdit_projectName->text(), dir.path());
    ProjectData db = CacheAgent::getInstance().database();

    if(round_base->isChecked()) {
        db.projectInitBase();
        CacheAgent::getInstance().databaseClean();
        CacheAgent::getInstance().databaseUpdate(db);
        db.save();
    }
    if(round_empty->isChecked()) {
        db.projectInitEmpty();
        CacheAgent::getInstance().databaseClean();
        CacheAgent::getInstance().databaseUpdate(db);
        db.save();
    }
    if(round_example->isChecked()) {
        Message("功能开发中");
        return;
        db.projectInitExample();
        CacheAgent::getInstance().databaseClean();
        CacheAgent::getInstance().databaseUpdate(db);
        db.save();
    }
    CacheAgent::getInstance().setting.setLastProject(CacheAgent::getInstance().databaseInfo().projectPosition,CacheAgent::getInstance().databaseInfo().projectName);
    CacheAgent::getInstance().setting.SaveToFile();
    emit requestClose();
    close();
}




