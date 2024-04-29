#include "window_editor_menubar_text.h"

#include "memoryCache/cacheAgent.h"
#include <QApplication>
#include <qt_windows.h>
#include <QDesktopWidget>

Window_editor_menubar_text_edit::Window_editor_menubar_text_edit(Database *_db, DB_text *_file, QWidget *parent) : Window_small(parent)
{
    setFixedSize(960, 600);

    db = _db;
    file = _file;
    setWindowTitle("编辑文本 ID=" + QString::number(file->__id));

    chooseButton_language = new Widget_ChooseButton(this);
    chooseButton_language->setTimer(timer);
    chooseButton_language->addTextList(db->info.language);
    chooseButton_language->setGeometry(32 + 548, 64, 360, 80);
    connect(chooseButton_language, SIGNAL(indexChanged(int)), this, SLOT(languageChanged(int)));


    textEdit = new Widget_TextEdit(this);
    textEdit->setGeometry(16, 64 + 80 * 1, 924, 440);
    textEdit->setText(file->getText(0));

}

void Window_editor_menubar_text_edit::paintEvent(QPaintEvent *)
{
    Draw::smallWindow(this, this);

    Draw::begin(this);
    Draw::setAntialising();
    Draw::setTextDefault();
    setPenColor_c(c_textMain);

    Draw::text(32, 104 + 80 * 0, "当前语言：", Qt::AlignLeft | Qt::AlignVCenter);
    Draw::end();
}

void Window_editor_menubar_text_edit::languageChanged(int _index)
{
    file->setText(language_last, textEdit->text());
    textEdit->setText(file->getText(_index));

    language_last = _index;
}


void Window_editor_menubar_text_edit::end()
{
    file->setText(language_last, textEdit->text());

    isClosing = true;
    emit closed();
}


Window_editor_menubar_text::Window_editor_menubar_text(QWidget *parent) : Window_small(parent)
{
    QRect rect = QApplication::desktop()->screenGeometry();

    if(rect.height() > 150)
    {
        setFixedSize(1200, rect.height() - 150);
    }
    else
    {
        setFixedSize(1200, 900);
    }
    setWindowTitle("编辑文本");

    db = CacheAgent::getInstance().database();

    button_accept = new Widget_Button(this);
    button_accept->setGeometry(720 - 28, rect.height() - 150 - 96, 240, 80);
    button_accept->setText("确定");
    button_accept->setTimer(timer);

    button_cancel = new Widget_Button(this);
    button_cancel->setGeometry(960 - 20, rect.height() - 150 - 96, 240, 80);
    button_cancel->setText("取消");
    button_cancel->setTimer(timer);

    connect(button_accept, SIGNAL(pressed()), this, SLOT(accept()));
    connect(button_cancel, SIGNAL(pressed()), this, SLOT(end()));

    chooseButton = new Widget_ChooseButton(this);
    chooseButton->setTimer(timer);
    chooseButton->addTextList(db.info.language);
    chooseButton->setGeometry(816, 64, 400 - 36, 80);
    connect(chooseButton, SIGNAL(indexChanged(int)), this, SLOT(updateList()));

    itemList = new Widget_ItemList(this);
    itemList->setGeometry(16, 64 + 80, 1200 - 36, rect.height() - 150 - 240);

    connect(button_accept, SIGNAL(pressed()), this, SLOT(accept()));
    connect(button_cancel, SIGNAL(pressed()), this, SLOT(end()));

    connect(itemList, SIGNAL(doubleClicked(int)), this, SLOT(editAudio(int)));

    updateList();
}

void Window_editor_menubar_text::paintEvent(QPaintEvent *)
{
    Draw::smallWindow(this, this);

    Draw::begin(this);
    Draw::setAntialising();
    Draw::setTextDefault();
    setPenColor_c(c_textMain);

    Draw::text(32, 104 + 80 * 0, "当前语言：", Qt::AlignLeft | Qt::AlignVCenter);
    Draw::end();
}

void Window_editor_menubar_text::updateList()
{
    QList<itemSTR> tmpList;
    QList<QString> text_list;
    text_list << "ID" << "文本";
    itemList->setHeadTextList(text_list);
    itemList->setHeadWidthList({120, 720});

    for(auto i = db.text.begin(); i != db.text.end(); i ++) {
        itemSTR tmp_item;
        tmp_item.text.append(QString::number(i.value().__id));
        tmp_item.text.append(i.value().getText(chooseButton->getIndex()));
        tmpList.append(tmp_item);
    }
    itemList->setItemList(tmpList);
}

void Window_editor_menubar_text::accept()
{
    CacheAgent::getInstance().databaseUpdate(db);
    end();
}

void Window_editor_menubar_text::editAudio(int _index)
{
    if(_index == -1) return;
    if(itemList->index() == -1) return;

    editAudioStart(itemList->getItem(_index).text[0].toInt());
}


void Window_editor_menubar_text::editAudioStart(int _index)
{

    window_editor = new Window_editor_menubar_text_edit(&db, &db.text[_index]);
    connect(window_editor, SIGNAL(closed()), this, SLOT(updateList()));
    window_editor->setWindowModality(Qt::ApplicationModal);
    window_editor->setAttribute(Qt::WA_DeleteOnClose);
    window_editor->show();

}




