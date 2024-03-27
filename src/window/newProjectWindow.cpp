#include "window/newProjectWindow.h"

#include <QFileDialog>

#include "widget/transparentDialog.h"

#include "draw.h"

#include "global.h"

NewProjectWindow::NewProjectWindow(QWidget *parent) : SmallWindow(parent)
{
    setFixedSize(1200, 480);
    setWindowTitle("新建项目");

    // 项目名文本框
    _projectNameLineEdit = new EllipticalLineEdit("New Project",QRect(32, 116, 1136, 80),this);
    // 项目路径文本框
    _projectDirLineEdit = new EllipticalLineEdit("",QRect(32, 248, 896, 80),this);
    // 浏览本地文件按钮
    _findProjectButton = new GradientButton("浏览",QRect(32 + 896, 248, 240, 80),this);

    {
        // TODO... 按钮组现在未实装，等待后续版本实装
        round_base = new Widget_RoundButton(this);
        round_base->setText("基本项目");
        round_base->setGeometry(250, 336, 240, 40);
        round_base->setTimer(_timer);
        round_base->setChecked(true);

        round_empty = new Widget_RoundButton(this);
        round_empty->setText("空白项目");
        round_empty->setGeometry(450, 336, 240, 40);
        round_empty->setTimer(_timer);

        round_example = new Widget_RoundButton(this);
        round_example->setText("示例项目");
        round_example->setGeometry(650, 336, 240, 40);
        round_example->setTimer(_timer);

        buttonBox_type = new QButtonGroup(this);
        buttonBox_type->addButton(round_base);
        buttonBox_type->addButton(round_empty);
        buttonBox_type->addButton(round_example);
    }

    _acceptButton = new GradientButton("创建",QRect(320, 386, 240, 80),this);
    _cancelButton = new GradientButton("取消",QRect(640, 386, 240, 80),this);

    connect(_findProjectButton, SIGNAL(pressed()), this, SLOT(findOldProjectSlot()));
    connect(_acceptButton, SIGNAL(pressed()), this, SLOT(createProjectSlot()));
    connect(_cancelButton, SIGNAL(pressed()), this, SLOT(end()));
}

NewProjectWindow::~NewProjectWindow() {

}

void NewProjectWindow::paintEvent(QPaintEvent *)
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

void NewProjectWindow::findOldProjectSlot()
{
    QString pos = QFileDialog::getExistingDirectory();
    if(pos != "") {
        _projectDirLineEdit->setText(pos);
    }
}

void NewProjectWindow::createProjectSlot()
{
    if(_projectDirLineEdit->text().isEmpty()) {
        TransparentDialog::play("目录不能为空");
        return;
    }
    QDir dir = _projectDirLineEdit->text();
    if(!dir.exists()) {
        TransparentDialog::play("目录不存在");
        return;
    }

    Global::databaseInit(_projectNameLineEdit->text(), dir.path());
    Database db = Global::database();

    if(round_base->isChecked()) {
        db.projectInitBase();
        Global::databaseClean();
        Global::databaseUpdate(db);
        db.save();
    }
    if(round_empty->isChecked()) {
        db.projectInitEmpty();
        Global::databaseClean();
        Global::databaseUpdate(db);
        db.save();
    }
    if(round_example->isChecked()) {
        TransparentDialog::play("功能开发中");
        return;
        db.projectInitExample();
        Global::databaseClean();
        Global::databaseUpdate(db);
        db.save();
    }
    Global::setting.global_last_name = Global::databaseInfo().projectName;
    Global::setting.global_last_path = Global::databaseInfo().projectPosition;
    Global::setting.save();
    emit requestClose();
    close();
}




