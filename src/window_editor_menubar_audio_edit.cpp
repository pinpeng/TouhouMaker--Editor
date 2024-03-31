#include "window_editor_menubar_audio_edit.h"

#include "widget/transparentDialog.h"

#include <QFileDialog>
#include <QDesktopServices>

Window_editor_menubar_audio_edit::Window_editor_menubar_audio_edit(Database *_db, DB_audio *_file, QWidget *parent) : SmallWindow(parent)
{
    setFixedSize(800, 240);
    setWindowTitle("编辑音频");

    db = _db;
    file = _file;

    lineEdit = new EllipticalLineEdit(this);
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
        QString basePath = CacheAgent::getInstance().database().info.projectPosition;
        basePath = basePath + "/audio/" + QString::number(file->__id) + ".ogg";
        if(!QFile::exists(basePath)) {
            TransparentDialog::play(this, "音频已丢失");
            file->state = 0;
        }
    }

}

void Window_editor_menubar_audio_edit::paintEvent(QPaintEvent *)
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

void Window_editor_menubar_audio_edit::open()
{
    QString basePath = CacheAgent::getInstance().database().info.projectPosition;
    QString str = QFileDialog::getOpenFileName(this, "打开音频", basePath, "(*.ogg)");
    if(!str.isEmpty()) {
        QFile fin(str);
        if(!fin.exists()) {
            TransparentDialog::play(this, "文件不存在");
            return;
        } else {
            basePath = basePath + "/audio/" + QString::number(file->__id) + ".ogg";
            if(QFile::exists(basePath)) QFile::remove(basePath);
            if(!fin.copy(str, basePath)) {
                TransparentDialog::play(this, "导入失败");
                return;
            }
            file->state = 1;
            repaint();
        }
    }
}

void Window_editor_menubar_audio_edit::preview()
{
    if(file->state == 0) {
        TransparentDialog::play(this, "还没导入哦");
        return;
    }

    QString basePath = CacheAgent::getInstance().database().info.projectPosition;
    basePath = basePath + "/audio/" + QString::number(file->__id) + ".ogg";
    if(!QFile::exists(basePath)) {
        TransparentDialog::play(this, "音频已丢失");
        file->state = 0;
        return;
    }
    QDesktopServices::openUrl(QUrl::fromLocalFile(basePath));
}

void Window_editor_menubar_audio_edit::end()
{
    file->name = lineEdit->text();
    _isClosing = true;
    emit closed();
}


