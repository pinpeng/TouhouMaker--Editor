#include "window_editor_menubar_image_edit.h"

#include "message_box.h"

#include <QFileDialog>
#include <QDesktopServices>

Window_editor_menubar_image_edit::Window_editor_menubar_image_edit(Database *_db, DB_image *_file, QWidget *parent) : SmallWindow(parent)
{
    setFixedSize(800, 240);
    setWindowTitle("编辑图像");

    db = _db;
    file = _file;

    lineEdit = new Widget_LineEdit(this);
    lineEdit->setGeometry(32 + 120, 64 + 80 * 0, 620, 80);
    lineEdit->setText(file->name);

    button_open = new GradientButton(this);
    button_open->setGeometry(32 + 260, 64 + 80 * 1, 240, 80);
    button_open->setText("打开...");
    // button_open->setTimer(_timer);

    button_preview = new GradientButton(this);
    button_preview->setGeometry(32 + 500, 64 + 80 * 1, 240, 80);
    button_preview->setText("预览");
    // button_preview->setTimer(_timer);

    connect(button_open, SIGNAL(pressed()), this, SLOT(open()));
    connect(button_preview, SIGNAL(pressed()), this, SLOT(preview()));

    if(file->state != 0) {
        QString basePath = Global::database().info.projectPosition;
        if(file->state == 1) basePath = basePath + "/image/" + QString::number(file->__id) + ".png";
        if(file->state == 2) basePath = basePath + "/image/" + QString::number(file->__id) + ".gif";
        if(!QFile::exists(basePath)) {
            Message_Box::play(this, "图像已丢失");
            file->state = 0;
        }
    }

}

void Window_editor_menubar_image_edit::paintEvent(QPaintEvent *)
{
    Draw::smallWindow(this, this);

    Draw::begin(this);
    Draw::setAntialising();
    Draw::setTextDefault();
    setPenColor_c(c_textMain);

    Draw::text(32, 104 + 80 * 0, "名称", Qt::AlignLeft | Qt::AlignVCenter);
    Draw::text(32, 104 + 80 * 1, "状态：" + state_arr[file->state], Qt::AlignLeft | Qt::AlignVCenter);
    Draw::end();
}

void Window_editor_menubar_image_edit::open()
{
    QString basePath = Global::database().info.projectPosition;
    QString str = QFileDialog::getOpenFileName(this, "打开图像", basePath, "(*.png *.gif)");
    if(!str.isEmpty()) {
        QFile fin(str);
        if(!fin.exists()) {
            Message_Box::play(this, "文件不存在");
            return;
        } else {
            QString _spr_key = QString::number(file->__id) + "_" + QString::number(file->editTimer);

            if(Global::sprite_buffer.find(_spr_key) != Global::sprite_buffer.end()) {
                auto tmp = &Global::sprite_buffer[_spr_key];
                if(tmp->gif != nullptr) delete tmp->gif;
                Global::sprite_buffer.remove(_spr_key);
            }

            QString suffix = QFileInfo(fin).suffix();
            basePath = basePath + "/image/" + QString::number(file->__id) + "." + suffix;
            if(QFile::exists(basePath)) QFile::remove(basePath);
            if(!fin.copy(str, basePath)) {
                Message_Box::play(this, "导入失败");
                return;
            }

            if(suffix == "png") file->state = 1;
            if(suffix == "gif") file->state = 2;

            file->editTimer ++;
            sprite_buff _tmp_buff;
            if(file->state == 1) _tmp_buff.png = QPixmap(basePath);
            if(file->state == 2) {
                _tmp_buff.gif = new QMovie(basePath);
            }
            Global::sprite_buffer.insert(QString::number(file->__id) + "_" + QString::number(file->editTimer), _tmp_buff);

            repaint();
        }
    }
}

void Window_editor_menubar_image_edit::preview()
{
    if(file->state == 0) {
        Message_Box::play(this, "还没导入哦");
        return;
    }

    QString basePath = Global::database().info.projectPosition;
    if(file->state == 1) basePath = basePath + "/image/" + QString::number(file->__id) + ".png";
    if(file->state == 2) basePath = basePath + "/image/" + QString::number(file->__id) + ".gif";
    if(!QFile::exists(basePath)) {
        Message_Box::play(this, "图像已丢失");
        file->state = 0;
        return;
    }
    QDesktopServices::openUrl(QUrl::fromLocalFile(basePath));
}

void Window_editor_menubar_image_edit::end()
{
    file->name = lineEdit->text();

    _isClosing = true;
    emit closed();
}




