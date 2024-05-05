#include "window_editor_menubar_image_edit.h"

#include "message_box.h"

#include "memoryCache/cacheAgent.h"

#include <QFileDialog>
#include <QDesktopServices>
#include "globalSource/sourceAgent.h"

Window_editor_menubar_image_edit::Window_editor_menubar_image_edit(ProjectData *_db, MemoryCache::ImageInfo *_file, QWidget *parent) : Window_small(parent)
{
    setFixedSize(800, 240);
    setWindowTitle("编辑图像");

    db = _db;
    file = _file;

    lineEdit = new Widget_LineEdit(this);
    lineEdit->setGeometry(32 + 120, 64 + 80 * 0, 620, 80);
    lineEdit->setText(file->_imageName);

    button_open = new Widget_Button(this);
    button_open->setGeometry(32 + 260, 64 + 80 * 1, 240, 80);
    button_open->setText("打开...");
    button_open->setTimer(timer);

    button_preview = new Widget_Button(this);
    button_preview->setGeometry(32 + 500, 64 + 80 * 1, 240, 80);
    button_preview->setText("预览");
    button_preview->setTimer(timer);

    connect(button_open, SIGNAL(pressed()), this, SLOT(open()));
    connect(button_preview, SIGNAL(pressed()), this, SLOT(preview()));

    if(file->_imageType != MemoryCache::ImageType::UNKNOWN) {
        QString basePath = CacheAgent::getInstance().database().info.projectPosition;
        if(file->_imageType == MemoryCache::ImageType::PNG){
            basePath = basePath + "/image/" + QString::number(file->_imageId) + ".png";
        }
        if(file->_imageType == MemoryCache::ImageType::GIF){
            basePath = basePath + "/image/" + QString::number(file->_imageId) + ".gif";
        }
        if(!QFile::exists(basePath)) {
            Message_Box::play(this, "图像已丢失");
            file->_imageType = MemoryCache::ImageType::UNKNOWN;
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
    Draw::text(32, 104 + 80 * 1, "状态：" + state_arr[static_cast<int>(file->_imageType)], Qt::AlignLeft | Qt::AlignVCenter);
    Draw::end();
}

void Window_editor_menubar_image_edit::open()
{
    QString basePath = CacheAgent::getInstance().database().info.projectPosition;
    // TODO... 使用fileOperator替换当前的projectPosition
    // QString basePath = ToolKit::FileOperator::getProjectSubModulePath(ToolKit::ProjectModule::IMAGE);
    QString str = QFileDialog::getOpenFileName(this, "打开图像", basePath, "(*.png *.gif)");
    if(!str.isEmpty()) {
        QFile fin(str);
        if(!fin.exists()) {
            Message_Box::play(this, "文件不存在");
            return;
        } else {
            // 为了避免回退后找不到文件，当文件不被使用时不清除缓存

            QString suffix = QFileInfo(fin).suffix();
            QString filePath = basePath + QString::number(file->_imageId) + "." + suffix;

            if(QFile::exists(filePath)){
                QFile::remove(filePath);
            }

            if(!fin.copy(str, filePath)) {
                Message_Box::play(this, "导入失败");
                return;
            }

            if(suffix == "png"){
                file->_imageType = MemoryCache::ImageType::PNG;
                QSharedPointer<QPixmap> pngPtr = QSharedPointer<QPixmap>::create(filePath);
                SourceAgent::getInstance().setImage(QString::number(file->_imageId),pngPtr);
            }
            else if(suffix == "gif"){
                file->_imageType = MemoryCache::ImageType::GIF;
                QSharedPointer<QMovie> gifPtr = QSharedPointer<QMovie>::create(filePath);
                SourceAgent::getInstance().setImage(QString::number(file->_imageId),gifPtr);
            }

            repaint();
        }
    }
}

void Window_editor_menubar_image_edit::preview()
{
    if(file->_imageType == MemoryCache::ImageType::UNKNOWN) {
        Message_Box::play(this, "还没导入哦");
        return;
    }

    QString basePath = CacheAgent::getInstance().database().info.projectPosition;
    if(file->_imageType == MemoryCache::ImageType::PNG){
        basePath = basePath + "/image/" + QString::number(file->_imageId) + ".png";
    }
    if(file->_imageType == MemoryCache::ImageType::GIF){
        basePath = basePath + "/image/" + QString::number(file->_imageId) + ".gif";
    }
    if(!QFile::exists(basePath)) {
        Message_Box::play(this, "图像已丢失");
        file->_imageType = MemoryCache::ImageType::UNKNOWN;
        return;
    }
    QDesktopServices::openUrl(QUrl::fromLocalFile(basePath));
}

void Window_editor_menubar_image_edit::end()
{
    file->_imageName = lineEdit->text();

    isClosing = true;
    emit closed();
}




