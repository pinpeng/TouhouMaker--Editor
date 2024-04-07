#include "window/editor/mainEditorWindow.h"

#include <QApplication>
#include <QDesktopServices>

#include "window/editor/editorConfig.h"

int MainEditorWindow::id1 = -1;
int MainEditorWindow::id2 = -1;
int MainEditorWindow::id3 = -1;

MainEditorWindow::MainEditorWindow(QWidget *parent) : QWidget(parent)
{
    setWindowIcon(QIcon(":/logo/mscb_icon.ico"));
    setWindowState(Qt::WindowMaximized);
    setMinimumSize(1600, 960);

    setWindowTitle("Touhou Maker ~ 车万没课儿");
    setStyleSheet("background-color:rgb(" +
                  QString::number(Color(c_backgroundSub).red()) + "," +
                  QString::number(Color(c_backgroundSub).green()) + "," +
                  QString::number(Color(c_backgroundSub).blue()) + ");");

    id1 = -1;
    id2 = -1;
    id3 = -1;

    _mainLayout = new QVBoxLayout(this);

    _menubar = new Window_editor_menubar(this);
    window_stage = new Window_editor_stage(this);
    window_timeline = new Window_editor_timeline(this);

    _mainLayout->addWidget(_menubar);
    _mainLayout->addWidget(window_stage);
    _mainLayout->addWidget(window_timeline);

    setLayout(_mainLayout);

    connect(_menubar, SIGNAL(requestBackToHome()), this, SLOT(backToHome()));
    connect(_menubar, SIGNAL(requestUndo()), this, SLOT(undo()));
    connect(_menubar, SIGNAL(requestRedo()), this, SLOT(redo()));


    window_treelist = new Window_editor_treelist(this);
    window_treelist->fatherWindow = this;


    connect(window_treelist,    SIGNAL(requestUpdate(int)), this, SLOT(stageUpdateListCall(int)));
    connect(window_stage,       SIGNAL(requestUpdate(int)), this, SLOT(stageUpdateListCall(int)));
    connect(_menubar,     SIGNAL(requestUpdate(int)), this, SLOT(stageUpdateListCall(int)));
    connect(window_timeline,    SIGNAL(requestUpdate(int)), this, SLOT(stageUpdateListCall(int)));
}

void MainEditorWindow::syncWidget(int updateType){
    window_stage->updateFromOutside(updateType);
    window_timeline->updateFromOutside(updateType);
    window_treelist->updateFromOutside(updateType);
}

void MainEditorWindow::keyPressEvent(QKeyEvent *event)
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
    } 
}

void MainEditorWindow::closeEvent(QCloseEvent *event)
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

void MainEditorWindow::backToHome()
{
    isEnding = true;
    homepage->show();
    close();
}

void MainEditorWindow::undo()
{
    if(CacheAgent::getInstance().databaseUndo()) {
        TransparentDialog::play(this, "撤销");
        syncWidget(EditorWindow::ENUM_UPDATE_BY_UNDO);
    } else TransparentDialog::play(this, "撤销失败");
}

void MainEditorWindow::redo()
{

    if(CacheAgent::getInstance().databaseRedo()) {
        TransparentDialog::play(this, "重做");
        syncWidget(EditorWindow::ENUM_UPDATE_BY_REDO);
    } else TransparentDialog::play(this, "重做失败");
}

void MainEditorWindow::save()
{
    if(CacheAgent::getInstance().database().save()) {
        TransparentDialog::play("保存失败");
        send_tips(2);
    } else {
        TransparentDialog::play("保存成功");
        send_tips(1);
    }
}

void MainEditorWindow::pack()
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

void MainEditorWindow::ending()
{
    isEnding = true;
    backToHome();
}

void MainEditorWindow::stageUpdateListCall(int i)
{
    syncWidget(i);
}



