#include "window_editor_menubar_bullet_edit.h"

#include "message_box.h"

#include <QFileDialog>
#include <QDesktopServices>

#include "window_find.h"

#include "global.h"
#include <QApplication>
#include <qt_windows.h>
#include <QDesktopWidget>

Window_editor_menubar_bullet_edit::Window_editor_menubar_bullet_edit(Database *_db, DB_bullet *_file, int _group, QWidget *parent) : Window_small(parent)
{
    QRect rect = QApplication::desktop()->screenGeometry();
    if(rect.width() >= 1900 && rect.height() >= 1000)
    {
        setFixedSize(1600, 900);
    }
    else
    {
        setFixedSize(1200, rect.height() - 150);
    }
    setWindowTitle("编辑子弹");

    db = _db;
    file = _file;
    group = _group;

    //名称
    lineEdit_name = new Widget_LineEdit(this);
    if(rect.width() >= 1900 && rect.height() >= 1000)
    {
        lineEdit_name->setGeometry(32 + 200, 64 + 80 * 0, 440, 80);
    }
    else
    {
        lineEdit_name->setGeometry(32 + 150, 64 + 80 * 0, 300, 80);
    }
    lineEdit_name->setText(file->name);

    QStringList _list;
    _list << "圆形" << "激光（开发中）";
    chooseButton_type = new Widget_ChooseButton(this);
    //子弹类型
    if(rect.width() >= 1900 && rect.height() >= 1000)
    {
        chooseButton_type->setGeometry(32 + 900, 64 + 80 * 0, 440, 80);
    }
    else
    {
        chooseButton_type->setGeometry(32 + 650, 64 + 80 * 0, 300, 80);
    }
    chooseButton_type->addTextList(_list);
    chooseButton_type->setIndex(file->data["type"]);
    chooseButton_type->setTimer(timer);

    _list.clear();
    _list << "离开屏幕" << "离开较远" << "不消失";
    chooseButton_range = new Widget_ChooseButton(this);
    if(rect.width() >= 1900 && rect.height() >= 1000)
    {
        chooseButton_range->setGeometry(32 + 200, 64 + 80 * 1, 440, 80);
    }
    else
    {
        chooseButton_range->setGeometry(32 + 150, 64 + 80 * 1, 300, 80);
    }
    chooseButton_range->addTextList(_list);
    chooseButton_range->setIndex(file->data["range"]);
    chooseButton_range->setTimer(timer);

    lineEdit_collision = new Widget_LineEdit(this);
    if(rect.width() >= 1900 && rect.height() >= 1000)
    {
        lineEdit_collision->setGeometry(32 + 900, 64 + 80 * 1, 440, 80);
    }
    else
    {
        lineEdit_collision->setGeometry(32 + 650, 64 + 80 * 1, 300, 80);
    }
    lineEdit_collision->setText(QString::number(file->data["collision"]));

    label = new QLabel(this);
    label->setScaledContents(false);
    //
    if(rect.width() >= 1900 && rect.height() >= 1000)
    {
        label->setGeometry(1382, 72, 192, 144);
    }
    else
    {
        label->setGeometry(1382 - 400, 72, 192, 144);
    }

    if(file->image_id != -1 &&
            db->image[3].find(file->image_id) != db->image[3].end() &&
            db->image[3][file->image_id].state) {

        QString _spr_key = QString::number(file->image_id) + "_" +
                QString::number(db->image[3][file->image_id].editTimer);
        auto j = Global::sprite_buffer.find(_spr_key);
        if(j != Global::sprite_buffer.end()) {
            if(db->image[3][file->image_id].state == 1) label->setPixmap(j.value().png);
            if(db->image[3][file->image_id].state == 2) {
                label->setMovie(j.value().gif);
                j.value().gif->start();
            }
        }

    }

}

void Window_editor_menubar_bullet_edit::paintEvent(QPaintEvent *)
{
    QRect rect_scr = QApplication::desktop()->screenGeometry();
    if(rect_scr.width() >= 1900 && rect_scr.height() >= 1000)
    {
        Draw::smallWindow(this, this);

        Draw::begin(this);
        Draw::setAntialising();
        Draw::setTextDefault();
        setPenColor_c(c_textMain);



        Draw::text(32, 104 + 80 * 0, "名称", Qt::AlignLeft | Qt::AlignVCenter);
        Draw::text(32 + 680, 104 + 80 * 0, "子弹类型", Qt::AlignLeft | Qt::AlignVCenter);
        Draw::text(32, 104 + 80 * 1, "消失条件", Qt::AlignLeft | Qt::AlignVCenter);
        Draw::text(32 + 680, 104 + 80 * 1, "碰撞范围", Qt::AlignLeft | Qt::AlignVCenter);

        Draw::painter->drawTiledPixmap(1382, 72, 192, 144, Sprite(ui_background), 0, 0);

        setPenColor_c(c_theme);
        setBrushColor_false();
        Draw::rect(1382, 72, 1382 + 192, 72 + 144, 2);

        if(file->image_id == -1) {
            Draw::setTextSize(16);
            Draw::text(1382 + 192 / 2, 72 + 144 / 2 + 2, "未设置图像\n点此设置", Qt::AlignCenter);
        }

        setPenColor_c(c_itemEdge);
        setBrushColor_c(c_backgroundMain);
        Draw::roundRect(rect().left() + 24, 234, rect().right() - 24, rect().bottom() - 24, 4, 2);

        Draw::setTextSize(16);
        file->renderCode(this, db, QRectF(rect().left() + 24, 234, rect().right() - 48 - rect().left(), rect().bottom() - 258), &code_scroll_top, group);

        Draw::end();
    }
    else
    {
        Draw::smallWindow(this, this);

        Draw::begin(this);
        Draw::setAntialising();
        Draw::setTextDefault();
        setPenColor_c(c_textMain);



        Draw::text(32, 104 + 80 * 0, "名称", Qt::AlignLeft | Qt::AlignVCenter);
        Draw::text(32 + 480, 104 + 80 * 0, "子弹类型", Qt::AlignLeft | Qt::AlignVCenter);
        Draw::text(32, 104 + 80 * 1, "消失条件", Qt::AlignLeft | Qt::AlignVCenter);
        Draw::text(32 + 480, 104 + 80 * 1, "碰撞范围", Qt::AlignLeft | Qt::AlignVCenter);

        Draw::painter->drawTiledPixmap(1382 - 400, 72, 192, 144, Sprite(ui_background), 0, 0);

        setPenColor_c(c_theme);
        setBrushColor_false();
        Draw::rect(1382 - 400, 72, 1382 - 400 + 192, 72 + 144, 2);

        if(file->image_id == -1) {
            Draw::setTextSize(16);
            Draw::text(1382 - 400 + 192 / 2, 72 + 144 / 2 + 2, "未设置图像\n点此设置", Qt::AlignCenter);
        }

        setPenColor_c(c_itemEdge);
        setBrushColor_c(c_backgroundMain);
        Draw::roundRect(rect().left() + 24, 234, rect().right() - 24, rect().bottom() - 24, 4, 2);

        Draw::setTextSize(16);
        file->renderCode(this, db, QRectF(rect().left() + 24, 234, rect().right() - 48 - rect().left(), rect().bottom() - 258), &code_scroll_top, group);

        Draw::end();
    }
}

void Window_editor_menubar_bullet_edit::mousePressEvent(QMouseEvent *event)
{
    QRect rect_scr = QApplication::desktop()->screenGeometry();
    if(rect_scr.width() >= 1900 && rect_scr.height() >= 1000)
    {
        mousePressFunc(event);

        float mx = event->pos().x();
        float my = event->pos().y();
        bool flag = false;
        if(1382 < mx && mx < 1382 + 192 &&
           72 < my && my < 72 + 144) {
            Window_find *window_find = new Window_find(db, Window_find::type_image, 3, &file->image_id);
            window_find->setWindowModality(Qt::ApplicationModal);
            window_find->setAttribute(Qt::WA_DeleteOnClose);
            window_find->show();
            connect(window_find, SIGNAL(closed()), this, SLOT(updateImage()));
        }

        if(rect().left() + 24 < mx && mx < rect().right() - 24 &&
           234 < my && my < rect().bottom() - 24) {
            flag = file->editCode(this, db, QRectF(rect().left() + 24, 234, rect().right() - 48 - rect().left(), rect().bottom() - 258),
                                  &code_scroll_top, mx, my, group);
        }
        if(flag) repaint();
    }
    else
    {
        mousePressFunc(event);

        float mx = event->pos().x();
        float my = event->pos().y();
        bool flag = false;
        if(1382 - 400 < mx && mx < 1382 - 400 + 192 &&
           72 < my && my < 72 + 144) {
            Window_find *window_find = new Window_find(db, Window_find::type_image, 3, &file->image_id);
            window_find->setWindowModality(Qt::ApplicationModal);
            window_find->setAttribute(Qt::WA_DeleteOnClose);
            window_find->show();
            connect(window_find, SIGNAL(closed()), this, SLOT(updateImage()));
        }

        if(rect().left() + 24 < mx && mx < rect().right() - 24 &&
           234 < my && my < rect().bottom() - 24) {
            flag = file->editCode(this, db, QRectF(rect().left() + 24, 234, rect().right() - 48 - rect().left(), rect().bottom() - 258),
                                  &code_scroll_top, mx, my, group);
        }
        if(flag) repaint();
    }
}

void Window_editor_menubar_bullet_edit::wheelEvent(QWheelEvent *event)
{
    QRect rect_scr = QApplication::desktop()->screenGeometry();
    if(rect_scr.width() >= 1900 && rect_scr.height() >= 1000)
    {
        float tmp = code_scroll_top;
        code_scroll_top -= float(event->angleDelta().y()) / 120.0;
        code_scroll_top = qMax(0.0f, code_scroll_top);
        file->wheelEvent(this, db, QRectF(rect().left() + 24, 234, rect().right() - 48 - rect().left(), rect().bottom() - 258), &code_scroll_top);
        if(tmp != code_scroll_top) repaint();
    }
    else
    {
        float tmp = code_scroll_top;
        code_scroll_top -= float(event->angleDelta().y()) / 120.0;
        code_scroll_top = qMax(0.0f, code_scroll_top);
        file->wheelEvent(this, db, QRectF(rect().left() + 24, 234, rect().right() - 48 - rect().left(), rect().bottom() - 258), &code_scroll_top);
        if(tmp != code_scroll_top) repaint();
    }
}

void Window_editor_menubar_bullet_edit::end()
{
    file->name = lineEdit_name->text();
    file->data["type"] = chooseButton_type->getIndex();
    file->data["range"] = chooseButton_range->getIndex();
    float tmp = lineEdit_collision->text().toFloat();
    file->data["collision"] = qMax(-1.0f, qMin(tmp, 100.0f));
    isClosing = true;
    emit closed();
}

void Window_editor_menubar_bullet_edit::updateData()
{
    QRect rect_scr = QApplication::desktop()->screenGeometry();
    if(rect_scr.width() >= 1900 && rect_scr.height() >= 1000)
    {
        file->updateData();

        QRectF _rect = QRectF(rect().left() + 24, 234, rect().right() - 48 - rect().left(), rect().bottom() - 258);

        int line_show_max = floor(_rect.height() / 40) - 2;
        int line_max = 0;
        for(int i = 0; i < file->data["stage"]; i ++) {
            QString tmp = QString::number(i) + "_";
            line_max += 3;
            for(int j = 0; j < file->data[tmp + "event"]; j ++) {
                QString tmp1 = tmp + QString::number(j) + "_type";
                if(file->data.find(tmp1) != file->data.end() && file->data[tmp1] != -1) line_max += 1;
            }
        }
        code_scroll_top = qBound(0.0f, code_scroll_top, float(line_max - line_show_max - 1));

        repaint();
    }
    else
    {
        file->updateData();

        QRectF _rect = QRectF(rect().left() + 24, 234, rect().right() - 48 - rect().left(), rect().bottom() - 258);

        int line_show_max = floor(_rect.height() / 40) - 2;
        int line_max = 0;
        for(int i = 0; i < file->data["stage"]; i ++) {
            QString tmp = QString::number(i) + "_";
            line_max += 3;
            for(int j = 0; j < file->data[tmp + "event"]; j ++) {
                QString tmp1 = tmp + QString::number(j) + "_type";
                if(file->data.find(tmp1) != file->data.end() && file->data[tmp1] != -1) line_max += 1;
            }
        }
        code_scroll_top = qBound(0.0f, code_scroll_top, float(line_max - line_show_max - 1));

        repaint();
    }
}

void Window_editor_menubar_bullet_edit::updateImage()
{
    if(file->image_id == -1) {
        label->setPixmap(QPixmap());
        label->setMovie(nullptr);
    } else {

        if(db->image[3][file->image_id].state) {

            QString _spr_key = QString::number(file->image_id) + "_" +
                    QString::number(db->image[3][file->image_id].editTimer);

            auto j = Global::sprite_buffer.find(_spr_key);
            if(j != Global::sprite_buffer.end()) {
                if(db->image[3][file->image_id].state == 1) label->setPixmap(j.value().png);
                if(db->image[3][file->image_id].state == 2) {
                    label->setMovie(j.value().gif);
                    j.value().gif->start();
                }
            }
        } else {

            label->setPixmap(QPixmap());
            label->setMovie(nullptr);
        }
    }

    repaint();
}
