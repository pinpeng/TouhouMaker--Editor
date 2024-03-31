#include "window_editor_main.h"

#include <QApplication>
#include <QDesktopServices>

int Window_editor_main::id1 = -1;
int Window_editor_main::id2 = -1;
int Window_editor_main::id3 = -1;

Window_editor_main::Window_editor_main(QWidget *parent) : QWidget(parent)
{
    setWindowIcon(QIcon(":/logo/mscb_icon.ico"));
    setWindowState(Qt::WindowMaximized);
    setMinimumSize(1600, 960);
    //Database_info *info = &CacheAgent::getInstance().database_list.top().info;

    setWindowTitle("Tou Hou Maker ~ 车万没课儿");
    setStyleSheet("background-color:rgb(" +
                  QString::number(Color(c_backgroundSub).red()) + "," +
                  QString::number(Color(c_backgroundSub).green()) + "," +
                  QString::number(Color(c_backgroundSub).blue()) + ");");

    id1 = -1;
    id2 = -1;
    id3 = -1;

    mainLayout = new QVBoxLayout(this);

    window_menubar = new Window_editor_menubar(this);
    window_stage = new Window_editor_stage(this);
    window_timeline = new Window_editor_timeline(this);

    mainLayout->addWidget(window_menubar);
    mainLayout->addWidget(window_stage);
    mainLayout->addWidget(window_timeline);

    setLayout(mainLayout);

    connect(window_menubar, SIGNAL(requestBackToHome()), this, SLOT(backToHome()));
    connect(window_menubar, SIGNAL(requestUndo()), this, SLOT(undo()));
    connect(window_menubar, SIGNAL(requestRedo()), this, SLOT(redo()));


    /*connect(this, SIGNAL(stageKeyArrow() ), window_stage, SLOT(keyArrow()));
    connect(this, SIGNAL(stageKeyMove()  ), window_stage, SLOT(keyMove()));
    connect(this, SIGNAL(stageKeyCut()   ), window_stage, SLOT(keyCut()));
    connect(this, SIGNAL(stageKeySelect()), window_stage, SLOT(keySelect()));
    connect(this, SIGNAL(stageKeyBrush() ), window_stage, SLOT(keyBrush()));*/

    window_treelist = new Window_editor_treelist(this);
    window_treelist->fatherWindow = this;

    connect(this, SIGNAL(stageUpdateList(int)), window_stage,       SLOT(updateFromOutside(int)));
    connect(this, SIGNAL(stageUpdateList(int)), window_timeline,    SLOT(updateFromOutside(int)));
    connect(this, SIGNAL(stageUpdateList(int)), window_treelist,    SLOT(updateFromOutside(int)));


    connect(window_treelist,    SIGNAL(requestUpdate(int)), this, SLOT(stageUpdateListCall(int)));
    connect(window_stage,       SIGNAL(requestUpdate(int)), this, SLOT(stageUpdateListCall(int)));
    connect(window_menubar,     SIGNAL(requestUpdate(int)), this, SLOT(stageUpdateListCall(int)));
    connect(window_timeline,    SIGNAL(requestUpdate(int)), this, SLOT(stageUpdateListCall(int)));

    //Window_editor_stage_tips *tips = new Window_editor_stage_tips();
    //tips->show();
    //connect(this, SIGNAL(destroyed()), tips, SLOT(close()));
    //tips->show();
}

void Window_editor_main::keyPressEvent(QKeyEvent *event)
{
    if(event->modifiers() == Qt::ControlModifier) {
        switch(event->key()) {
        case Qt::Key_Z: undo(); break;
        case Qt::Key_Y: redo(); break;
        case Qt::Key_S: save(); break;
        //case Qt::Key_P: pack(); break;
        case Qt::Key_V: {
            window_treelist->changeState();
        }
            break;
        default: break;
        }
    } else {
        switch (event->key()) {
        //case Qt::Key_F2: window_treelist->renameFromOutside(); break;
        /*case Qt::Key_D: emit stageKeyArrow(); break;
        case Qt::Key_V: emit stageKeyMove(); break;
        case Qt::Key_E: emit stageKeyCut(); break;
        case Qt::Key_S: emit stageKeySelect(); break;
        case Qt::Key_B: emit stageKeyBrush(); break;*/
        default: break;
        }
    }
}

void Window_editor_main::closeEvent(QCloseEvent *event)
{
    if(!isEnding) {
        event->ignore();
        window_ask = new Window_ask("  确定要回到主菜单吗？未保存的内容将消失！");
        window_ask->setWindowModality(Qt::ApplicationModal);
        window_ask->setAttribute(Qt::WA_DeleteOnClose);
        window_ask->show();
        connect(window_ask, SIGNAL(OK()), this, SLOT(ending()));
    }
}

void Window_editor_main::backToHome()
{
    isEnding = true;
    homepage->show();
    close();
}

void Window_editor_main::undo()
{
    if(CacheAgent::getInstance().databaseUndo()) {
        TransparentDialog::play(this, "撤销");
        emit stageUpdateList(-1);
    } else TransparentDialog::play(this, "撤销失败");
}

void Window_editor_main::redo()
{

    if(CacheAgent::getInstance().databaseRedo()) {
        TransparentDialog::play(this, "重做");
        emit stageUpdateList(-1);
    } else TransparentDialog::play(this, "重做失败");
}

void Window_editor_main::save()
{
    if(CacheAgent::getInstance().database().save()) {
        TransparentDialog::play("保存失败");
        send_tips(2);
    } else {
        TransparentDialog::play("保存成功");
        send_tips(1);
    }
}

void Window_editor_main::pack()
{
    if(CacheAgent::getInstance().database().save()) {
        TransparentDialog::play("保存失败");
        send_tips(4);
    } else {
        if(CacheAgent::getInstance().database().pack()) {
            TransparentDialog::play("导出失败");
            send_tips(4);
        } else {
            send_tips(3);
            if(!QDesktopServices::openUrl(QUrl::fromLocalFile(CacheAgent::getInstance().databaseInfo().projectPosition + "/output"))) {
                TransparentDialog::play("无法打开文件夹");
            }
        }
    }
}

void Window_editor_main::ending()
{
    isEnding = true;
    backToHome();
}

void Window_editor_main::stageUpdateListCall(int i)
{
    emit stageUpdateList(i);
}



