#include "window_editor_menubar_hero_edit.h"

#include "widget/transparentDialog.h"

#include <QFileDialog>
#include <QDesktopServices>
#include <QLabel>

Window_editor_menubar_hero_edit0::Window_editor_menubar_hero_edit0(Database *_db, DB_hero *_file, QWidget *parent) : SmallWindow(parent)
{
    setFixedSize(1400, 640);
    setWindowTitle("编辑主角");

    db = _db;
    file = _file;

    chooseButton_language = new ChooseButton(this);
    // chooseButton_language->setTimer(_timer);
    chooseButton_language->addTextList(db->info.language);
    chooseButton_language->setGeometry(32 + 160, 64, 480, 80);
    connect(chooseButton_language, SIGNAL(indexChanged(int)), this, SLOT(languageChanged(int)));

    lineEdit = new EllipticalLineEdit(this);
    lineEdit->setGeometry(32 + 160, 64 + 80 * 1, 480, 80);
    lineEdit->setText(db->getText(file->name, 0));

    chooseButton_bullet = new ChooseButton(this);
    // chooseButton_bullet->setTimer(_timer);
    chooseButton_bullet->addTextList({"无弹幕", "仅弹幕1", "仅弹幕2", "两种弹幕"});
    chooseButton_bullet->setGeometry(32 + 320, 64 + 80 * 2, 320, 80);
    chooseButton_bullet->setIndex(file->bullet_type);

    button_bullet1 = new GradientButton(this);
    // button_bullet1->setTimer(_timer);
    button_bullet1->setText("设置弹幕1");
    button_bullet1->setGeometry(24, 64 + 80 * 3, 320, 80);
    button_bullet2 = new GradientButton(this);
    // button_bullet2->setTimer(_timer);
    button_bullet2->setText("设置弹幕2");
    button_bullet2->setGeometry(32 + 320, 64 + 80 * 3, 320, 80);

    chooseButton_skill = new ChooseButton(this);
    // chooseButton_skill->setTimer(_timer);
    chooseButton_skill->addTextList({"无符卡", "仅符卡1", "仅符卡2", "两种符卡"});
    chooseButton_skill->setGeometry(32 + 320, 64 + 80 * 4, 320, 80);
    chooseButton_skill->setIndex(file->skill_type);

    lineEdit_s1 = new EllipticalLineEdit(this);
    lineEdit_s1->setText(db->getText(file->skill[0].name, 0));
    lineEdit_s1->setGeometry(240 - 28, 64 + 80 * 5, 920, 80);
    button_skill1 = new GradientButton(this);
    // button_skill1->setTimer(_timer);
    button_skill1->setText("设置");
    button_skill1->setGeometry(1140, 64 + 80 * 5, 240, 80);

    lineEdit_s2 = new EllipticalLineEdit(this);
    lineEdit_s2->setText(db->getText(file->skill[1].name, 0));
    lineEdit_s2->setGeometry(240 - 28, 64 + 80 * 6, 920, 80);
    button_skill2 = new GradientButton(this);
    // button_skill2->setTimer(_timer);
    button_skill2->setText("设置");
    button_skill2->setGeometry(1140, 64 + 80 * 6, 240, 80);

}

void Window_editor_menubar_hero_edit0::paintEvent(QPaintEvent *)
{
    Draw::smallWindow(this, this);

    Draw::begin(this);
    Draw::setAntialising();
    Draw::setTextDefault();
    setPenColor_c(c_textMain);

    Draw::text(32, 104 + 80 * 0, "当前语言：", Qt::AlignLeft | Qt::AlignVCenter);
    Draw::text(32, 104 + 80 * 1, "主角名称", Qt::AlignLeft | Qt::AlignVCenter);
    Draw::text(32, 104 + 80 * 2, "慢速时弹幕是否区别", Qt::AlignLeft | Qt::AlignVCenter);
    Draw::text(32, 104 + 80 * 4, "慢速时符卡是否区别", Qt::AlignLeft | Qt::AlignVCenter);
    Draw::text(32, 104 + 80 * 5, "符卡1名称", Qt::AlignLeft | Qt::AlignVCenter);
    Draw::text(32, 104 + 80 * 6, "符卡2名称", Qt::AlignLeft | Qt::AlignVCenter);

    Draw::painter->drawTiledPixmap(672 + 8, 72, 1400 - 32 - 680, 84 + 80 * 5 - 32 - 72, Sprite(ui_background), 0, 0);

    setPenColor_c(c_theme);
    setBrushColor_false();
    Draw::rect(672 + 8, 72, 1400 - 32, 84 + 80 * 5 - 32, 2);

    Draw::setTextSize(14);

    QString _str[6] = { "待机", "左移", "右移", "装饰", "减速" , "立绘" };

    for(int i = 0; i < 3; i ++) {
        float mid_x = (672 + 8 + 1400 - 32) / 2 + (i - 1) * 200;
        float mid_y = (72 + 84 + 80 * 5 - 32) / 2 - 100;
        setPenColor_c(c_theme);
        Draw::text(mid_x, mid_y, "<未设置>", Qt::AlignCenter);
        Draw::rect(mid_x - 72, mid_y - 72, mid_x + 72, mid_y + 72, 1);
        Draw::text(mid_x, mid_y + 76, _str[i], Qt::AlignTop | Qt::AlignHCenter);
    }

    for(int i = 0; i < 3; i ++) {
        float mid_x = (672 + 8 + 1400 - 32) / 2 + (i - 1) * 200;
        float mid_y = (72 + 84 + 80 * 5 - 32) / 2 + 80;
        setPenColor_c(c_theme);
        Draw::text(mid_x, mid_y, "<未设置>", Qt::AlignCenter);
        Draw::rect(mid_x - 72, mid_y - 72, mid_x + 72, mid_y + 72, 1);
        Draw::text(mid_x, mid_y + 76, _str[i + 3], Qt::AlignTop | Qt::AlignHCenter);
    }

    Draw::end();
}

// void Window_editor_menubar_hero_edit0::mousePressEvent(QMouseEvent *event)
// {
//     SmallWindow::mousePressEvent(event);
//     // if(mousePressFunc(event)) return;

// }

void Window_editor_menubar_hero_edit0::end()
{
    db->setText(file->name,          language_last, lineEdit->text());
    db->setText(file->skill[0].name, language_last, lineEdit_s1->text());
    db->setText(file->skill[1].name, language_last, lineEdit_s2->text());
    file->bullet_type = chooseButton_bullet->getIndex();
    file->skill_type = chooseButton_skill->getIndex();

    _isClosing = true;
    emit closed();

}

void Window_editor_menubar_hero_edit0::languageChanged(int _index)
{
    db->setText(file->name,          language_last, lineEdit->text());
    db->setText(file->skill[0].name, language_last, lineEdit_s1->text());
    db->setText(file->skill[1].name, language_last, lineEdit_s2->text());

    lineEdit->setText(db->getText(file->name, _index));
    lineEdit_s1->setText(db->getText(file->skill[0].name, _index));
    lineEdit_s2->setText(db->getText(file->skill[1].name, _index));

    language_last = _index;
}


Window_editor_menubar_hero_edit1::Window_editor_menubar_hero_edit1(Database *_db, DB_enemy *_file, QWidget *parent) : SmallWindow(parent)
{
    setFixedSize(1600, 900);
    setWindowTitle("编辑小怪");

    db = _db;
    file = _file;

    lineEdit_name = new EllipticalLineEdit(this);
    lineEdit_name->setGeometry(32 + 200, 64 + 80 * 0, 440, 80);
    lineEdit_name->setText(file->name);

    lineEdit_hp = new EllipticalLineEdit(this);
    lineEdit_hp->setGeometry(32 + 900, 64 + 80 * 0, 440, 80);
    lineEdit_hp->setText(QString::number(file->data["hp"]));

    QStringList _list;
    _list << "离开屏幕" << "离开较远" << "不消失";
    chooseButton_range = new ChooseButton(this);
    chooseButton_range->setGeometry(32 + 200, 64 + 80 * 1, 440, 80);
    chooseButton_range->addTextList(_list);
    chooseButton_range->setIndex(file->data["range"]);
    // chooseButton_range->setTimer(_timer);

    lineEdit_collision = new EllipticalLineEdit(this);
    lineEdit_collision->setGeometry(32 + 900, 64 + 80 * 1, 440, 80);
    lineEdit_collision->setText(QString::number(file->data["collision"]));

    label = new QLabel(this);
    label->setScaledContents(false);
    label->setGeometry(1382, 72, 192, 144);

    if(file->image_id != -1 &&
            db->image[4].find(file->image_id) != db->image[4].end() &&
            db->image[4][file->image_id].state) {

        QString _spr_key = QString::number(file->image_id) + "_" +
                QString::number(db->image[4][file->image_id].editTimer);
        auto j = CacheAgent::getInstance().sprite_buffer.find(_spr_key);
        if(j != CacheAgent::getInstance().sprite_buffer.end()) {
            if(db->image[4][file->image_id].state == 1) label->setPixmap(j.value().png);
            if(db->image[4][file->image_id].state == 2) {
                label->setMovie(j.value().gif);
                j.value().gif->start();
            }
        }

    }
}

void Window_editor_menubar_hero_edit1::paintEvent(QPaintEvent *)
{
    Draw::smallWindow(this, this);

    Draw::begin(this);
    Draw::setAntialising();
    Draw::setTextDefault();
    setPenColor_c(c_textMain);

    Draw::text(32, 104 + 80 * 0, "名称", Qt::AlignLeft | Qt::AlignVCenter);
    Draw::text(32 + 680, 104 + 80 * 0, "血量", Qt::AlignLeft | Qt::AlignVCenter);
    Draw::text(32, 104 + 80 * 1, "消失条件", Qt::AlignLeft | Qt::AlignVCenter);
    Draw::text(32 + 680, 104 + 80 * 1, "碰撞范围", Qt::AlignLeft | Qt::AlignVCenter);

    Draw::painter->drawTiledPixmap(1382, 72, 192, 144, Sprite(ui_background), 0, 0);

    setPenColor_c(c_theme);
    setBrushColor_false();
    Draw::rect(1382, 72, 1382 + 192, 72 + 144, 2);

    if(file->image_id == -1 || db->image[4].find(file->image_id) == db->image[4].end() ||
            !db->image[4][file->image_id].state) {
        Draw::setTextSize(16);
        Draw::text(1382 + 192 / 2, 72 + 144 / 2 + 2, "未设置图像\n点此设置", Qt::AlignCenter);
    }

    setPenColor_c(c_itemEdge);
    setBrushColor_c(c_backgroundMain);
    Draw::roundRect(rect().left() + 24, 234, rect().right() - 24, rect().bottom() - 24, 4, 2);

    Draw::setTextSize(16);
    file->renderCode(this, db, QRectF(rect().left() + 24, 234, rect().right() - 48 - rect().left(), rect().bottom() - 258), &code_scroll_top);

    Draw::end();
}

void Window_editor_menubar_hero_edit1::mousePressEvent(QMouseEvent *event)
{
    SmallWindow::mousePressEvent(event);

    float mx = event->pos().x();
    float my = event->pos().y();
    bool flag = false;

    if(1382 < mx && mx < 1382 + 192 &&
       72 < my && my < 72 + 144) {
        if(file->image_id == -1) {
            int tmp = ++CacheAgent::getInstance().image_id_top;
            db->image[4].insert(tmp, DB_image(tmp, ""));
            file->image_id = tmp;
        }

        QString basePath = CacheAgent::getInstance().database().info.projectPosition;
        QString str = QFileDialog::getOpenFileName(this, "打开图像", basePath, "(*.png *.gif)");
        if(!str.isEmpty()) {
            QFile fin(str);
            if(!fin.exists()) {
                TransparentDialog::play(this, "文件不存在");
                return;
            } else {
                QString suffix = QFileInfo(fin).suffix();
                basePath = basePath + "/image/" + QString::number(file->image_id) + "." + suffix;
                if(QFile::exists(basePath)) QFile::remove(basePath);
                if(!fin.copy(str, basePath)) {
                    TransparentDialog::play(this, "导入失败");
                    return;
                }
                if(suffix == "png") db->image[4][file->image_id].state = 1;
                if(suffix == "gif") db->image[4][file->image_id].state = 2;

                db->image[4][file->image_id].editTimer ++;
                if(db->image[4][file->image_id].state) {
                    flag = true;
                    sprite_buff _tmp_buff;
                    QString basePath = CacheAgent::getInstance().database().info.projectPosition;
                    if(db->image[4][file->image_id].state == 1) _tmp_buff.png = QPixmap(basePath + "/image/" + QString::number(file->image_id) + ".png");
                    if(db->image[4][file->image_id].state == 2) {
                        _tmp_buff.gif = new QMovie(basePath + "/image/" + QString::number(file->image_id) + ".gif");
                    }
                    QString _spr_key = QString::number(file->image_id) + "_" +
                            QString::number(db->image[4][file->image_id].editTimer);

                    CacheAgent::getInstance().sprite_buffer.insert(_spr_key, _tmp_buff);

                    auto j = CacheAgent::getInstance().sprite_buffer.find(_spr_key);
                    if(j != CacheAgent::getInstance().sprite_buffer.end()) {
                        if(db->image[4][file->image_id].state == 1) label->setPixmap(j.value().png);
                        if(db->image[4][file->image_id].state == 2) {
                            label->setMovie(j.value().gif);
                            j.value().gif->start();
                        }
                    }
                }
            }
        }
    }

    if(rect().left() + 24 < mx && mx < rect().right() - 24 &&
       234 < my && my < rect().bottom() - 24) {
        flag = file->editCode(this, db, QRectF(rect().left() + 24, 234, rect().right() - 48 - rect().left(), rect().bottom() - 258),
                              &code_scroll_top, mx, my);
    }
    if(flag) repaint();

}

void Window_editor_menubar_hero_edit1::wheelEvent(QWheelEvent *event)
{
    float tmp = code_scroll_top;
    code_scroll_top -= float(event->angleDelta().y()) / 120.0;
    code_scroll_top = qMax(0.0f, code_scroll_top);
    file->wheelEvent(this, db, QRectF(rect().left() + 24, 234, rect().right() - 48 - rect().left(), rect().bottom() - 258), &code_scroll_top);
    if(tmp != code_scroll_top) repaint();

}

void Window_editor_menubar_hero_edit1::end()
{
    file->name = lineEdit_name->text();
    file->data["hp"] = qBound(1, lineEdit_hp->text().toInt(), 32767);
    file->data["range"] = chooseButton_range->getIndex();
    float tmp = lineEdit_collision->text().toFloat();
    file->data["collision"] = qBound(-1.0f, tmp, 100.0f);
    _isClosing = true;
    emit closed();

}

void Window_editor_menubar_hero_edit1::updateData()
{
    file->updateData();

    QRectF _rect = QRectF(rect().left() + 24, 234, rect().right() - 48 - rect().left(), rect().bottom() - 258);

    int line_show_max = floor(_rect.height() / 40) - 2;
    int line_max = 0;
    for(int i = 0; i < file->data["stage"]; i ++) {
        QString tmp = QString::number(i) + "_";
        if(file->data.find(tmp) == file->data.end()) continue;
        line_max += 3;
        for(int j = 0; j < file->data[tmp + "event"]; j ++) {
            QString tmp1 = tmp + QString::number(j) + "_type";
            if(file->data.find(tmp1) != file->data.end() && file->data[tmp1] != -1) line_max += 1;
        }
    }
    code_scroll_top = qBound(0.0f, code_scroll_top, float(line_max - line_show_max - 1));

    repaint();
}

Window_editor_menubar_hero_edit2::Window_editor_menubar_hero_edit2(Database *_db, DB_boss *_file, QWidget *parent) : SmallWindow(parent)
{
    setFixedSize(800, 640);
    setWindowTitle("编辑BOSS");

    db = _db;
    file = _file;

    chooseButton_language = new ChooseButton(this);
    // chooseButton_language->setTimer(_timer);
    chooseButton_language->addTextList(db->info.language);
    chooseButton_language->setGeometry(32 + 160, 64, 540, 80);
    connect(chooseButton_language, SIGNAL(indexChanged(int)), this, SLOT(languageChanged(int)));

    lineEdit = new EllipticalLineEdit(this);
    lineEdit->setGeometry(32 + 160, 64 + 80 * 1, 540, 80);
    lineEdit->setText(db->getText(file->name, 0));

    for(int i = 0; i < 3; i ++) {
        label[i] = new QLabel(this);
        label[i]->setScaledContents(false);
        label[i]->setGeometry(156 + i * 244 - 100, 224 + 8 + 180 - 100, 200, 200);

        if(file->image_id[i] != -1 &&
                db->image[4].find(file->image_id[i]) != db->image[4].end() &&
                db->image[4][file->image_id[i]].state) {

            QString _spr_key = QString::number(file->image_id[i]) + "_" +
                    QString::number(db->image[4][file->image_id[i]].editTimer);
            auto j = CacheAgent::getInstance().sprite_buffer.find(_spr_key);
            if(j != CacheAgent::getInstance().sprite_buffer.end()) {
                if(db->image[4][file->image_id[i]].state == 1) label[i]->setPixmap(j.value().png);
                if(db->image[4][file->image_id[i]].state == 2) {
                    label[i]->setMovie(j.value().gif);
                    j.value().gif->start();
                }
            }

        }
    }

}

void Window_editor_menubar_hero_edit2::paintEvent(QPaintEvent *)
{
    Draw::smallWindow(this, this);

    Draw::begin(this);
    Draw::setAntialising();
    Draw::setTextDefault();
    setPenColor_c(c_textMain);

    Draw::text(32, 104 + 80 * 0, "当前语言：", Qt::AlignLeft | Qt::AlignVCenter);
    Draw::text(32, 104 + 80 * 1, "BOSS名称", Qt::AlignLeft | Qt::AlignVCenter);

    Draw::painter->drawTiledPixmap(32, 224 + 8, 736, 376, Sprite(ui_background), 0, 0);

    setPenColor_c(c_theme);
    setBrushColor_false();
    Draw::rect(32, 224 + 8, 800 - 32, 224 + 8 + 376, 2);

    Draw::rect(156 - 100, 224 + 8 + 180 - 100, 156 + 100, 224 + 8 + 180 + 100, 1);
    Draw::rect(400 - 100, 224 + 8 + 180 - 100, 400 + 100, 224 + 8 + 180 + 100, 1);
    Draw::rect(644 - 100, 224 + 8 + 180 - 100, 644 + 100, 224 + 8 + 180 + 100, 1);

    for(int i = 0; i < 3; i ++) {
        if(file->image_id[i] == -1 ||
                db->image[4].find(file->image_id[i]) == db->image[4].end() ||
                !db->image[4][file->image_id[i]].state) {
            Draw::text(156 + i * 244, 224 + 8 + 182, "未设置", Qt::AlignCenter);
        }
    }

    Draw::setTextSize(16);

    QString _str[3] = { "待机", "左移", "右移" };
    Draw::text(156, 224 + 8 + 332, _str[0], Qt::AlignCenter);
    Draw::text(400, 224 + 8 + 332, _str[1], Qt::AlignCenter);
    Draw::text(644, 224 + 8 + 332, _str[2], Qt::AlignCenter);

    Draw::end();
}

void Window_editor_menubar_hero_edit2::mousePressEvent(QMouseEvent *event)
{
    float mx = event->pos().x();
    float my = event->pos().y();
    int ind = -1;

    if(224 + 8 + 180 - 100 < my && my < 224 + 8 + 180 + 100) {
        for(int i = 0; i < 3; i ++) {
            if(156 + i * 244 - 100 < mx && mx < 156 + i * 244 + 100) ind = i;
        }
    }

    if(ind != -1) {
        if(file->image_id[ind] == -1) {
            int tmp = ++CacheAgent::getInstance().image_id_top;
            db->image[4].insert(tmp, DB_image(tmp, ""));
            file->image_id[ind] = tmp;
        }

        QString basePath = CacheAgent::getInstance().database().info.projectPosition;
        QString str = QFileDialog::getOpenFileName(this, "打开图像", basePath, "(*.png *.gif)");

        if(!str.isEmpty()) {
            QFile fin(str);
            if(!fin.exists()) {
                TransparentDialog::play(this, "文件不存在");
                return;
            } else {
                QString suffix = QFileInfo(fin).suffix();
                basePath = basePath + "/image/" + QString::number(file->image_id[ind]) + "." + suffix;
                if(QFile::exists(basePath)) QFile::remove(basePath);
                if(!fin.copy(str, basePath)) {
                    TransparentDialog::play(this, "导入失败");
                    return;
                }
                if(suffix == "png") db->image[4][file->image_id[ind]].state = 1;
                if(suffix == "gif") db->image[4][file->image_id[ind]].state = 2;

                db->image[4][file->image_id[ind]].editTimer ++;
                if(db->image[4][file->image_id[ind]].state) {

                    sprite_buff _tmp_buff;
                    QString basePath = CacheAgent::getInstance().database().info.projectPosition;
                    if(db->image[4][file->image_id[ind]].state == 1) _tmp_buff.png = QPixmap(basePath + "/image/" + QString::number(file->image_id[ind]) + ".png");
                    if(db->image[4][file->image_id[ind]].state == 2) {
                        _tmp_buff.gif = new QMovie(basePath + "/image/" + QString::number(file->image_id[ind]) + ".gif");
                    }
                    QString _spr_key = QString::number(file->image_id[ind]) + "_" +
                            QString::number(db->image[4][file->image_id[ind]].editTimer);

                    CacheAgent::getInstance().sprite_buffer.insert(_spr_key, _tmp_buff);

                    auto j = CacheAgent::getInstance().sprite_buffer.find(_spr_key);
                    if(j != CacheAgent::getInstance().sprite_buffer.end()) {
                        if(db->image[4][file->image_id[ind]].state == 1) label[ind]->setPixmap(j.value().png);
                        if(db->image[4][file->image_id[ind]].state == 2) {
                            label[ind]->setMovie(j.value().gif);
                            j.value().gif->start();
                        }
                    }
                }
            }
        }
    } // if ind != -1 end

    repaint();
}

void Window_editor_menubar_hero_edit2::languageChanged(int _index)
{
    db->setText(file->name, language_last, lineEdit->text());
    lineEdit->setText(db->getText(file->name, _index));
    language_last = _index;
}

void Window_editor_menubar_hero_edit2::end()
{
    db->setText(file->name, language_last, lineEdit->text());
    _isClosing = true;
    emit closed();

}


