#include "window_editor_menubar_image.h"

#include "qdesktopservices.h"
#include <QLabel>

Window_editor_menubar_image::Window_editor_menubar_image(QWidget *parent) : SmallWindow(parent)
{
    setFixedSize(1600, 900);
    setWindowTitle("编辑图像");

    db = Global::database();

    button_accept = new Widget_Button(this);
    button_accept->setGeometry(1120 - 28, 900 - 96, 240, 80);
    button_accept->setText("确定");
    button_accept->setTimer(timer);

    button_cancel = new Widget_Button(this);
    button_cancel->setGeometry(1360 - 20, 900 - 96, 240, 80);
    button_cancel->setText("取消");
    button_cancel->setTimer(timer);

    connect(button_accept, SIGNAL(pressed()), this, SLOT(accept()));
    connect(button_cancel, SIGNAL(pressed()), this, SLOT(end()));


    QString _text[4] = { "背景", "特效", "立绘", "子弹" };

    select_group = new QButtonGroup(this);
    for(int i = 0; i < 4; i ++) {
        roundButton[i] = new Widget_RoundButton(this);
        roundButton[i]->setText(_text[i]);
        roundButton[i]->setGeometry(48 + 120 * i, 84, 120, 60);
        roundButton[i]->setTimer(timer);
        select_group->addButton(roundButton[i]);
        connect(roundButton[i], SIGNAL(stateChanged()), this, SLOT(updateList()));
    }

    button_openFolder = new Widget_Button(this);
    button_openFolder->setTimer(timer);
    button_openFolder->setText("打开图像文件夹");
    button_openFolder->setGeometry(616 - 60, 64, 400 - 36, 80);
    connect(button_openFolder, SIGNAL(pressed()), this, SLOT(openFolder()));

    itemList = new Widget_ItemList(this);
    itemList->setGeometry(16, 64 + 80, 1000 - 36 - 60, 580);

    button_add = new Widget_Button(this);
    button_del = new Widget_Button(this);
    button_add->setGeometry(12, 724, 450, 80);
    button_add->setText("新建");
    button_add->setTimer(timer);
    button_del->setGeometry(500 - 30, 724, 450, 80);
    button_del->setText("删除");
    button_del->setTimer(timer);

    connect(button_add, SIGNAL(pressed()), this, SLOT(add()));
    connect(button_del, SIGNAL(pressed()), this, SLOT(del()));

    connect(button_accept, SIGNAL(pressed()), this, SLOT(accept()));
    connect(button_cancel, SIGNAL(pressed()), this, SLOT(end()));

    connect(itemList, SIGNAL(doubleClicked(int)), this, SLOT(editAudio(int)));
    connect(itemList, SIGNAL(select(int)), this, SLOT(repaint()));

    label = new QLabel(this);
    label->setScaledContents(true);
    label->setGeometry(932, 72, 640, 724);

    roundButton[0]->setChecked(true);
    updateList();
}

void Window_editor_menubar_image::paintEvent(QPaintEvent *)
{
    Draw::smallWindow(this, this);

    label->setPixmap(QPixmap());
    label->setMovie(nullptr);

    Draw::begin(this);
    Draw::painter->drawTiledPixmap(932, 72, 640, 724, Sprite(ui_background));

    //bool flag = false;
    //QPixmap *pixmap_s;
    QString _spr_key;
    if(itemList->index() != -1 && itemList->index() < itemList->getItemSize()) {
        int tmp = itemList->getItem(itemList->index()).text[0].toInt();
        for(int i = 0; i < 4; i ++) if(roundButton[i]->isChecked()) {
            DB_image *file = &db.image[i][tmp];
            _spr_key = QString::number(file->__id) + "_" + QString::number(file->editTimer);
            auto j = Global::sprite_buffer.find(_spr_key);
            if(j != Global::sprite_buffer.end()) {
                //flag = true;
                if(file->state == 1) label->setPixmap(j.value().png);
                if(file->state == 2) {
                    label->setMovie(j.value().gif);
                    j.value().gif->start();
                }
                break;
            }
        }
    }

    /*if(flag) {
        float _w = pixmap_s->width();
        float _h = pixmap_s->height();
        float ss = qMin(640 /_w, 724 / _h);
        QPixmap pixmap_f = pixmap_s->transformed(QMatrix().scale(ss, ss), Qt::SmoothTransformation);

        _w = pixmap_f.width();
        _h = pixmap_f.height();

        Draw::sprite(pixmap_f, 932 + 320 - _w / 2, 72 + 362 - _h / 2);
    }*/

    setPenColor_c(c_theme);
    setBrushColor_false();
    Draw::rect(932, 72, 932 + 640, 72 + 724, 2);

    Draw::end();
}

void Window_editor_menubar_image::updateList()
{

    QList<itemSTR> tmpList;
    QList<QString> text_list;
    text_list << "ID" << "名称" << "状态";
    itemList->setHeadTextList(text_list);
    itemList->setHeadWidthList({120, 540, 240});

    int tmp = -1;
    for(int i = 0; i < 4; i ++) if(roundButton[i]->isChecked()) tmp = i;

    for(auto i = db.image[tmp].begin(); i != db.image[tmp].end(); i ++) {
        itemSTR tmp_item;
        tmp_item.text.append(QString::number(i.value().__id));
        tmp_item.text.append(i.value().name);
        tmp_item.text.append(state_arr[i.value().state]);
        tmpList.append(tmp_item);
    }
    itemList->setItemList(tmpList);
}

void Window_editor_menubar_image::accept()
{
    Global::databaseUpdate(db);
    end();
}

void Window_editor_menubar_image::editAudio(int _index)
{
    if(_index == -1) return;
    if(itemList->index() == -1) return;

    editAudioStart(itemList->getItem(_index).text[0].toInt());
}

void Window_editor_menubar_image::openFolder()
{
    if(!QDesktopServices::openUrl(QUrl::fromLocalFile(Global::databaseInfo().projectPosition + "/image"))) {
        Message("无法打开文件夹");
    }
}

void Window_editor_menubar_image::editAudioStart(int _index)
{

    for(int i = 0; i < 4; i ++) if(roundButton[i]->isChecked()) {
        window_editor = new Window_editor_menubar_image_edit(&db, &db.image[i][_index]);
        connect(window_editor, SIGNAL(closed()), this, SLOT(updateList()));
        window_editor->setWindowModality(Qt::ApplicationModal);
        window_editor->setAttribute(Qt::WA_DeleteOnClose);
        window_editor->show();
    }

}

void Window_editor_menubar_image::add()
{
    for(int i = 0; i < 4; i ++) if(roundButton[i]->isChecked()) db.image_append(i);

    itemList->resetIndex();
    updateList();
}

void Window_editor_menubar_image::del()
{
    int index = itemList->index();
    if(index == -1) { Message_Box::play(this, "未选中项目"); return; }

    for(int i = 0; i < 4; i ++) if(roundButton[i]->isChecked()) db.image_delete(i, itemList->getItem(index).text[0].toInt());

    itemList->resetIndex();
    updateList();
}


