#include "window_editor_stage.h"

#include "draw.h"

#include <QMouseEvent>
#include <complex>
#include <QApplication>

#include "window/editor/mainEditorWindow.h"

#include "dataSet/cacheAgent.h"
#include <qmath.h>

#include <QBitmap>

#include <windows.h>
#include <QWindow>
#include <QLabel>
#include <QDesktopServices>

#include <processthreadsapi.h>

Window_editor_stage::Window_editor_stage(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setMouseTracking(true);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeoutRepaint()));
    timer->start(1000 / 60);

    if(CacheAgent::getInstance().setting.tipsAction() != 2) {
        //tips = new Window_editor_stage_tips(this);
    }

    file_id = 0;

    for(int i = 0; i < 8; i ++) {
        label[i] = new QLabel(this);
        label[i]->setScaledContents(true);
        label[i]->setGeometry(10000, 10000, 1, 1);
    }

    runnerProcess = new QProcess(this);
}

Window_editor_stage::~Window_editor_stage()
{
}

void Window_editor_stage::updateFromOutside(int _request_id)
{
    if(_request_id == 2) return;
    db = CacheAgent::getInstance().database();

    event_list.clear();
    if(!(MainEditorWindow::id1 < 1 || MainEditorWindow::id2 == -1 || MainEditorWindow::id2 >= db.stage[MainEditorWindow::id1 - 1].size())) {
        DB_STAGE *_stage = &db.stage[MainEditorWindow::id1 - 1][MainEditorWindow::id2];
        for(int i = 0; i < _stage->events.size(); i ++) {
            int pos = 0;
            int _time = _stage->events[i].time;
            for(int j = 0; j < event_list.size(); j ++) {
                if(_time < _stage->events[event_list[j]].time) break;
                pos ++;
            }
            event_list.insert(pos, i);
        }
    }

    repaint();
}

void Window_editor_stage::codeEditFinished()
{
    CacheAgent::getInstance().databaseUpdate(db);
    emit requestUpdate(2);
    repaintTimer = qMin(repaintTimer + 2, 4);
}

void Window_editor_stage::codeEditBossAddEventFinished()
{

    if(MainEditorWindow::id1 < 1 || MainEditorWindow::id2 == -1 || MainEditorWindow::id2 >= db.stage[MainEditorWindow::id1 - 1].size()) {
    } else {
        auto *_events = &db.stage[MainEditorWindow::id1 - 1][MainEditorWindow::id2].events;

        for(auto i = _events->begin(); i != _events->end(); i ++) {
            if(i->id == buff_id3) {
                for(int j = 0; j < i->data["size"]; j ++) {
                    QString str = QString::number(j) + "_";
                    for(int k = i->data[str + "size"] - 1; k >= 0; k --) {
                        QString tmp = str + QString::number(k) + "_";
                        if(i->data.find(tmp + "type") == i->data.end() || i->data[tmp + "type"] == -1) {
                            i->data[str + "size"] --;
                            for(auto k = i->data.begin(); k != i->data.end(); k ++) {
                                if(k.key().indexOf(tmp) != -1) i->data.remove(k.key());
                            }
                        } else if(i->data[tmp + "inited"] == 0) {
                            i->data[tmp + "inited"] = 1;

                            i->data_str[tmp + "timer"] = "1";
                            i->data_str[tmp + "time"] = "0";
                            i->data[tmp + "index"] = -1;
                            i->data_str[tmp + "num"] = "1";

                            i->data_str[tmp + "code"] = "";

                            i->data_str[tmp + "x0"] = "x";
                            i->data_str[tmp + "y0"] = "y";
                            i->data_str[tmp + "spd"] = "8";

                            if(i->data[tmp + "type"] == 0) { // line

                                i->data_str[tmp + "dir"] = "0";
                                i->data_str[tmp + "step"] = "128";

                            } else if(i->data[tmp + "type"] == 1) { // circle

                                i->data_str[tmp + "dir"] = "0";
                                i->data_str[tmp + "radius"] = "0";

                            } else if(i->data[tmp + "type"] == 2) { // fan

                                i->data_str[tmp + "dir"] = "0";
                                i->data_str[tmp + "radius"] = "0";
                                i->data_str[tmp + "angle"] = "30";

                            } else if(i->data[tmp + "type"] == 3) { // random rect

                                i->data_str[tmp + "x0"] = "-128";
                                i->data_str[tmp + "y0"] = "-128";
                                i->data_str[tmp + "x1"] = "128";
                                i->data_str[tmp + "y1"] = "128";

                            } else if(i->data[tmp + "type"] == 4) { // random circle

                                i->data_str[tmp + "radius"] = "128";

                            } else {

                                i->data_str[tmp + "create"] = "";

                            }
                        }
                    }
                }
                break;
            }
        }
    }



    CacheAgent::getInstance().databaseUpdate(db);
    emit requestUpdate(2);
    repaintTimer = qMin(repaintTimer + 2, 4);
}

void Window_editor_stage::codeEditBossAddThreadFinished()
{
    if(MainEditorWindow::id1 < 1 || MainEditorWindow::id2 == -1 || MainEditorWindow::id2 >= db.stage[MainEditorWindow::id1 - 1].size()) {
    } else {
        auto *_events = &db.stage[MainEditorWindow::id1 - 1][MainEditorWindow::id2].events;

        for(auto i = _events->begin(); i != _events->end(); i ++) {
            if(i->id == buff_id3) {

                for(auto j = i->data.begin(); j != i->data.end(); j ++) {
                    auto tmp = j.key().indexOf("_");
                    if(tmp != -1) {
                        auto str = j.key().leftRef(tmp).toInt();
                        if(str >= i->data["size"]) i->data.remove(j.key());
                    }
                }

                for(int j = 0; j < i->data["size"]; j ++) {
                    QString str = QString::number(j) + "_";
                    if(i->data.find(str + "type1") == i->data.end()) {
                        i->data[str + "type1"] = 0;
                        i->data[str + "type1time"] = 0;
                        i->data[str + "type2"] = 0;
                        i->data[str + "type2time"] = 1;
                        i->data[str + "size"] = 0;
                        i->data_str[str + "init"] = "val1 = 0\nval2 = 0";
                        i->data_str[str + "step"] = "val1 = val1 + 1\nval2 = val2 + val1";
                    }
                }

            }

        }
    }


    CacheAgent::getInstance().databaseUpdate(db);
    emit requestUpdate(2);
    repaintTimer = qMin(repaintTimer + 2, 4);

}

void Window_editor_stage::stageEditFinished()
{
    DB_STAGE *_stage = &db.stage[MainEditorWindow::id1 - 1][MainEditorWindow::id2];
    for(int i = 0; i < _stage->events.size(); i ++) {
        if(_stage->events[i].time > _stage->length) {
            _stage->events.removeAt(i);
            i --;
        }
    }
    CacheAgent::getInstance().databaseUpdate(db);
    emit requestUpdate(2);
    repaintTimer = qMin(repaintTimer + 2, 4);
}

void Window_editor_stage::timeoutRepaint()
{
    event_list.clear();

    bool _changed = false;
    if(buff_id3 != MainEditorWindow::id3) {
        if(MainEditorWindow::id1 < 1 || MainEditorWindow::id2 == -1 || MainEditorWindow::id2 >= db.stage[MainEditorWindow::id1 - 1].size()) {
            buff_id3 = -1;
            event_scroll_top = 0;
            repaintTimer = qMin(repaintTimer + 2, 4);
        } else {
            QList<DB_STAGE_EVENT> *_events = &db.stage[MainEditorWindow::id1 - 1][MainEditorWindow::id2].events;

            bool flag = true;
            for(auto i = _events->begin(); i != _events->end(); i ++) {
                if(i->id == MainEditorWindow::id3) {
                    if(buff_id3 != MainEditorWindow::id3) _changed = true;
                    buff_id3 = MainEditorWindow::id3;
                    flag = false;
                    break;
                }
            }
            if(flag) {
                MainEditorWindow::id3 = -1;
                buff_id3 = -1;
                event_scroll_top = 0;
            }
            repaintTimer = qMin(repaintTimer + 2, 4);
        }
    }

    if(!(MainEditorWindow::id1 < 1 || MainEditorWindow::id2 == -1 || MainEditorWindow::id2 >= db.stage[MainEditorWindow::id1 - 1].size())) {
        DB_STAGE *_stage = &db.stage[MainEditorWindow::id1 - 1][MainEditorWindow::id2];
        for(int i = 0; i < _stage->events.size(); i ++) {
            int pos = 0;
            int _time = _stage->events[i].time;
            for(int j = 0; j < event_list.size(); j ++) {
                if(_time < _stage->events[event_list[j]].time) break;
                pos ++;
            }
            event_list.insert(pos, i);
        }
        if(_changed && buff_id3 != -1) {
            for(int i = 0; i < event_list.size(); i ++) {
                auto *_event = &_stage->events[event_list[i]];
                if(_event->id == buff_id3) {
                    float ss = CacheAgent::getInstance().setting.editorScale();
                    int scroll_num = int(event_scroll_top) + int((rect().bottom() - 4 - rect().top() - 116 * ss) / 40 / ss);
                    if(i < event_scroll_top || i > event_scroll_top + scroll_num) {
                        event_scroll_top = qMin(i, event_list.size() - scroll_num);
                    }
                    break;
                }
            }
        }
    }


    if(repaintTimer) {
        repaintTimer --;
        repaint();
    }
}


void Window_editor_stage::mousePressEvent(QMouseEvent *event)
{

    mouse_x = event->x();
    mouse_y = event->y();


    float mx = event->x();
    float my = event->y();


    float _w = rect().width();
    float _h = rect().height();
    float _gwindow_w = _h * 5.0 / 6.0;

    float ss = CacheAgent::getInstance().setting.editorScale();
    if(event->button() == Qt::LeftButton) {
        lb_game(QRectF(rect().left() + (_w - _gwindow_w) / 2, rect().top(), _gwindow_w, _h), mx, my, ss);
    }
    if(MainEditorWindow::id1 < 1 || MainEditorWindow::id2 == -1) return;

    if(event->button() == Qt::LeftButton) {
        if(!(MainEditorWindow::id1 < 1 || MainEditorWindow::id2 == -1 || MainEditorWindow::id2 >= db.stage[MainEditorWindow::id1 - 1].size())) {
            lb_event(QRectF(rect().left(), rect().top(), (_w - _gwindow_w) / 2, _h), mx, my, ss);
            lb_code(QRectF(rect().left() + (_w - _gwindow_w) / 2 + _gwindow_w, rect().top(), (_w - _gwindow_w) / 2, _h), mx, my, ss);
        }
    }

    repaintTimer = qMin(repaintTimer + 2, 4);

}

void Window_editor_stage::lb_event(QRectF _rect, float mx, float my, float ss)
{
    if(mx > _rect.right()) return;
    if(my < _rect.top() + 96 * ss) { // edit stage
        ask_create("设置关卡");
        connect(window_ask_ex, SIGNAL(OK()), this, SLOT(stageEditFinished()));
        DB_STAGE *_stage = &db.stage[MainEditorWindow::id1 - 1][MainEditorWindow::id2];

        ask_add_lineEdit_str("关卡名称", &_stage->name);
        ask_add_dragStick("持续时间", &_stage->length, 6000, 36000, "秒", 1.0 / 60.0);
    } else {
        DB_STAGE *_stage = &db.stage[MainEditorWindow::id1 - 1][MainEditorWindow::id2];
        int scroll_max = qMin(event_list.size(), int(event_scroll_top) + int((_rect.bottom() - 4 - _rect.top() - 116 * ss) / 40 / ss));
        for(int i = int(event_scroll_top); i < scroll_max; i ++) {
            DB_STAGE_EVENT *_event = &_stage->events[event_list[i]];
            int tmp = i - int(event_scroll_top);
            if(buff_id3 == _event->id) {
                if(abs(_rect.top() + 136 * ss + 40 * tmp * ss - my) < 16 * ss &&
                   abs(_rect.right() - 48 * ss - mx) < 16 * ss) {
                    buff_id3 = -1;
                    _stage->events.removeAt(event_list[i]);
                    CacheAgent::getInstance().databaseUpdate(db);
                    emit requestUpdate(2);
                    return;
                }
            } else {
                if(_rect.top() + 116 * ss + 40 * tmp * ss < my && my < _rect.top() + 116 * ss + 40 * (tmp + 1) * ss) {
                    buff_id3 = _event->id;
                    code_scroll_top = 0;
                    MainEditorWindow::id3 = buff_id3;
                    emit requestUpdate(2);
                    return;
                }

            }
        }
    }


}

void Window_editor_stage::lb_game(QRectF _rect, float mx, float my, float ss)
{
    if(mx < _rect.left() || mx > _rect.right()) return;
    if(my < _rect.top() || my > _rect.bottom()) return;

    float mid_x = _rect.left() + (_rect.right() - _rect.left()) / 2;
    float mid_y = _rect.top() + (_rect.bottom() - 48 * ss - _rect.top()) / 2;

    float scale = qMin((_rect.width() - 32 * ss) / 10.0f, (_rect.height() - 80 * ss) / 12.0f) / 2.0;

    float _left = mid_x - 10 * scale - 1;
    float _right = mid_x + 10 * scale - 1;
    float _top = mid_y - 12 * scale;
    float _bottom = mid_y + 12 * scale;
    int _pos = _rect.bottom() - 46 * ss - 2 * ss - 4;

    switch(runner_state) {
    case RUNNER_STATE::IDLE: {

        int _flag = -1;
        if(abs(my - _pos) < 24 * ss) {
            if(abs((_left + _right) / 2 - 96 * ss - mx) < 24 * ss) _flag = 0;
            if(abs((_left + _right) / 2 - 32 * ss - mx) < 24 * ss) _flag = 1;
            if(abs((_left + _right) / 2 + 32 * ss - mx) < 24 * ss) _flag = 2;
            if(abs((_left + _right) / 2 + 96 * ss - mx) < 24 * ss) _flag = 3;
        }

        if(_flag == -1) return;
        if(runnerProcess->state() == QProcess::Running) {
            runnerProcess->close();
            Sleep(1000);
        }

        if(_flag != 3) {
            auto runner_path = QApplication::applicationDirPath() + "/debug/debugger.exe";
            if(!QFile::exists(runner_path)) {
                TransparentDialog::play(this, "解释器丢失");
                return;
            }

            bool flag = CacheAgent::getInstance().database().pack();
            if(flag) {
                TransparentDialog::play(this, "导出失败");
                return;
            }

            QString basePath = CacheAgent::getInstance().databaseInfo().projectPosition;

            QFile resFile;
            QByteArray buffer;

            buffer.clear();

            resFile.setFileName(QApplication::applicationDirPath() + "/debug/debug.txt");
            if(!resFile.open(QIODevice::WriteOnly)) {
                TransparentDialog::play(this, "数据写入失败");
                return;
            }

            buffer += basePath + "/output\n";
            if(_flag == 0) { // go!!!
                if(MainEditorWindow::id1 >= 1 && MainEditorWindow::id2 != -1
                        && MainEditorWindow::id2 < db.stage[MainEditorWindow::id1 - 1].size()) {
                    buffer += QString::number(MainEditorWindow::id1) + "\n";
                    buffer += QString::number(MainEditorWindow::id2) + "\n";
                    buffer += "0\n0\n";
                } else {
                    buffer += "-123\n0\n0\n0\n";
                }
            } else if(_flag == 1) { // point
                if(MainEditorWindow::id1 >= 1 && MainEditorWindow::id2 != -1
                        && MainEditorWindow::id2 < db.stage[MainEditorWindow::id1 - 1].size()) {
                    buffer += QString::number(MainEditorWindow::id1) + "\n";
                    buffer += QString::number(MainEditorWindow::id2) + "\n";
                    auto *_events = &db.stage[MainEditorWindow::id1 - 1][MainEditorWindow::id2].events;
                    bool flag = false;
                    int min_time = 6000;
                    for(auto i = _events->begin(); i != _events->end(); i ++) {
                        if(i->type == DB_STAGE_EVENT::POINT && i->data["enable"]) {
                            flag = true;
                            if(i->time < min_time) min_time = i->time;
                        }
                    }
                    if(!flag) buffer += "0\n0\n";
                    else buffer += QString::number(min_time) + "\n0\n";
                } else {
                    buffer += "-123\n0\n0\n0\n";
                }
            } else if(_flag == 2) { // now
                if(MainEditorWindow::id1 >= 1 && MainEditorWindow::id2 != -1
                        && MainEditorWindow::id2 < db.stage[MainEditorWindow::id1 - 1].size()) {
                    buffer += QString::number(MainEditorWindow::id1) + "\n";
                    buffer += QString::number(MainEditorWindow::id2) + "\n";
                    auto *_events = &db.stage[MainEditorWindow::id1 - 1][MainEditorWindow::id2].events;
                    bool flag = false;
                    if(buff_id3 != -1) {
                        for(auto i = _events->begin(); i != _events->end(); i ++) {
                            if(i->id == buff_id3) {
                                flag = true;
                                buffer += QString::number(i->time) + "\n0\n";
                                break;
                            }
                        }
                    }
                    if(!flag) buffer += "0\n0\n";
                } else {
                    buffer += "-123\n0\n0\n0\n";
                }
            }

            resFile.write(buffer);
            resFile.close();

            runnerProcess->start(runner_path, QStringList(runner_path));
            Sleep(200);
            TransparentDialog::play(this, "开始启动");

            HWND hwnd = FindWindow(nullptr, L"THMK DEBUG RUNNER");
            if(hwnd != nullptr) {
                QWindow *m_window;
                m_window = QWindow::fromWinId((WId)hwnd);

                runnerWidget = QWidget::createWindowContainer(m_window, this, Qt::Widget);
                runnerWidget->setWindowFlag(Qt::FramelessWindowHint);
                runnerWidget->setFocusProxy(this);
                runnerWidget->setFocus(Qt::ActiveWindowFocusReason);

                float _w = rect().width();
                float _h = rect().height();
                float _gwindow_w = _h * 5.0 / 6.0;

                float ss = CacheAgent::getInstance().setting.editorScale();

                QRect _rect(rect().left() + (_w - _gwindow_w) / 2, rect().top(), _gwindow_w, _h);

                float mid_x = _rect.left() + (_rect.right() - _rect.left()) / 2;
                float mid_y = _rect.top() + (_rect.bottom() - 48 * ss - _rect.top()) / 2;

                float scale = qMin((_rect.width() - 32 * ss) / 10.0f, (_rect.height() - 80 * ss) / 12.0f) / 2.0;

                float _left = mid_x - 10 * scale;
                float _right = mid_x + 10 * scale;
                float _top = mid_y - 12 * scale;
                float _bottom = mid_y + 12 * scale;

                runnerWidget->setGeometry(QRect(_left, _top, _right - _left, _bottom - _top));
                runnerWidget->show();

                runnerWidget->repaint();

                runner_state = RUNNER_STATE::TEST_FROM_BEGINING;
                runnerWidget->setEnabled(true);
                repaint();
            } else {
                TransparentDialog::play(this, "无法连接程序");
                return;
            }

        }

    } break;

    case RUNNER_STATE::TEST_FROM_BEGINING: {
        int _flag = -1;
        if(abs(my - _pos) < 24 * ss) {
            if(abs((_left + _right) / 2 - 96 * ss - mx) < 24 * ss) _flag = 0;
            if(abs((_left + _right) / 2 - 32 * ss - mx) < 24 * ss) _flag = 1;
            if(abs((_left + _right) / 2 + 32 * ss - mx) < 24 * ss) _flag = 2;
            if(abs((_left + _right) / 2 + 96 * ss - mx) < 24 * ss) _flag = 3;
        }
        if(_flag == -1) return;

        if(_flag == 3) {
            if(runnerProcess->state() == QProcess::Running) {
                runnerProcess->close();
            }
            runner_state = RUNNER_STATE::IDLE;
            TransparentDialog::play(this, "停止");

            runnerWidget->close();
            repaint();

        } else {
            TransparentDialog::play(this, "请先关闭程序");
        }
    } break;

    default:
        break;
    }

}

void Window_editor_stage::lb_code(QRectF _rect, float mx, float my, float ss)
{
    if(mx < _rect.left() || my < _rect.top() + 16 * ss) return;

    if(MainEditorWindow::id1 < 1 || MainEditorWindow::id2 == -1 || MainEditorWindow::id2 >= db.stage[MainEditorWindow::id1 - 1].size()) {
    } else {
        auto *_events = &db.stage[MainEditorWindow::id1 - 1][MainEditorWindow::id2].events;

        for(auto i = _events->begin(); i != _events->end(); i ++) {
            if(i->id == buff_id3) {
                if(my < _rect.top() + 56 * ss) {
                    i->data["enable"] = !i->data["enable"];
                    CacheAgent::getInstance().databaseUpdate(db);
                    emit requestUpdate(2);
                } else {
                    bool ret =
                    i->editCode(this, &db,
                                QRectF(_rect.left(), _rect.top() + 40 * ss, _rect.width(), rect().height()), &code_scroll_top, ss, mx, my);
                    if(ret) {
                        CacheAgent::getInstance().databaseUpdate(db);
                        emit requestUpdate(2);
                    }
                }
                break;
            }
        }
    }
}

void Window_editor_stage::mouseDoubleClickEvent(QMouseEvent *event)
{
}

void Window_editor_stage::mouseMoveEvent(QMouseEvent *event)
{
    mouse_x = event->x();
    mouse_y = event->y();

}

void Window_editor_stage::mouseReleaseEvent(QMouseEvent *event)
{
    mouse_x = event->x();
    mouse_y = event->y();

}

void Window_editor_stage::wheelEvent(QWheelEvent *event)
{

    if(!(MainEditorWindow::id1 < 1 || MainEditorWindow::id2 == -1 || MainEditorWindow::id2 >= db.stage[MainEditorWindow::id1 - 1].size())) {

        auto *_events = &db.stage[MainEditorWindow::id1 - 1][MainEditorWindow::id2].events;

        float _w = rect().width();
        float _h = rect().height();
        float _gwindow_w = _h * 5.0 / 6.0;

        float ss = CacheAgent::getInstance().setting.editorScale();

        if(mouse_x < (_w - _gwindow_w) / 2) {
            int _pre = event_scroll_top;

            int scroll_num = (rect().bottom() - 4 - (rect().top() + 116 * ss)) / 40 / ss;
            event_scroll_top -= float(event->angleDelta().y()) / 120.0;
            event_scroll_top = qMax(0.0f, event_scroll_top);
            event_scroll_top = qMin(event_scroll_top, float(event_list.size() - scroll_num));
            event_scroll_top = qMax(0.0f, event_scroll_top);
            event_scroll_top = floor(event_scroll_top);
            if(_pre != event_scroll_top) repaintTimer = qMin(repaintTimer + 2, 4);

        } else if(mouse_x > rect().right() - (_w - _gwindow_w) / 2) {
            int _pre = code_scroll_top;

            auto *_events = &db.stage[MainEditorWindow::id1 - 1][MainEditorWindow::id2].events;
            code_scroll_top -= float(event->angleDelta().y()) / 120.0;
            code_scroll_top = qMax(0.0f, code_scroll_top);
            for(auto i = _events->begin(); i != _events->end(); i ++) {
                if(i->id == buff_id3) {
                    i->wheelEvent(this, &db, QRectF(rect().left() + (_w - _gwindow_w) / 2 + _gwindow_w, rect().top(), (_w - _gwindow_w) / 2, _h),
                                  &code_scroll_top, ss);
                    break;
                }
            }

            code_scroll_top = floor(code_scroll_top);
            if(_pre != code_scroll_top) repaintTimer = qMin(repaintTimer + 2, 4);
        }
    }
}

void Window_editor_stage::resizeEvent(QResizeEvent *event)
{
    float _w = rect().width();
    float _h = rect().height();
    float _gwindow_w = _h * 5.0 / 6.0;

    float ss = CacheAgent::getInstance().setting.editorScale();

    QRect _rect(rect().left() + (_w - _gwindow_w) / 2, rect().top(), _gwindow_w, _h);

    float mid_x = _rect.left() + (_rect.right() - _rect.left()) / 2;
    float mid_y = _rect.top() + (_rect.bottom() - 48 * ss - _rect.top()) / 2;

    float scale = qMin((_rect.width() - 32 * ss) / 10.0f, (_rect.height() - 80 * ss) / 12.0f) / 2.0;

    float _left = mid_x - 10 * scale;
    float _right = mid_x + 10 * scale;
    float _top = mid_y - 12 * scale;
    float _bottom = mid_y + 12 * scale;

    if(runnerWidget != nullptr) {
        runnerWidget->setGeometry(QRect(_left, _top, _right - _left, _bottom - _top));
        runnerWidget->setEnabled(true);
        runnerWidget->repaint();
    }
}

void Window_editor_stage::paintEvent(QPaintEvent *)
{

    Draw::begin(this);
    Draw::setTextDefault();

    Draw::setAntialising(CacheAgent::getInstance().setting.stageAntialising());

    float _w = rect().width();
    float _h = rect().height();
    float _gwindow_w = _h * 5.0 / 6.0;

    draw_event(QRectF(rect().left(), rect().top(), (_w - _gwindow_w) / 2, _h));
    draw_game(QRectF(rect().left() + (_w - _gwindow_w) / 2, rect().top(), _gwindow_w, _h));
    draw_code(QRectF(rect().left() + (_w - _gwindow_w) / 2 + _gwindow_w, rect().top(), (_w - _gwindow_w) / 2, _h));
    Draw::end();
}

void Window_editor_stage::draw_event(QRectF _rect)
{
    float ss = CacheAgent::getInstance().setting.editorScale();

    setPenColor_false();
    setBrushColor_c(c_backgroundMain);
    Draw::roundRect(_rect.left() + 4, _rect.top(), _rect.right() - 4, _rect.bottom(), 6);
    Draw::setTextDefault();

    if(MainEditorWindow::id1 < 1 || MainEditorWindow::id2 == -1 || MainEditorWindow::id2 >= db.stage[MainEditorWindow::id1 - 1].size()) {
        setPenColor_c(c_theme);
        Draw::setTextSize(20 * ss);
        Draw::text(_rect.left() + 24 * ss, _rect.top() + 16 * ss, "未选择关卡", Qt::AlignLeft | Qt::AlignTop);
    } else {
        DB_STAGE *_stage = &db.stage[MainEditorWindow::id1 - 1][MainEditorWindow::id2];

        setPenColor_c(c_theme);
        Draw::setTextSize(20 * ss);
        Draw::text_line_with_length(_rect.left() + 24 * ss, _rect.top() + 16 * ss,
                                    _stage->name, _rect.width() - 96 * ss,
                                    Qt::AlignLeft | Qt::AlignTop);
        Draw::setTextSize(16 * ss);
        Draw::text(_rect.left() + 24 * ss, _rect.top() + 64 * ss,
                   "持续" + QString::number(floor(_stage->length / 60)) + "秒，共" + QString::number(_stage->events.size()) + "个事件",
                   Qt::AlignLeft | Qt::AlignTop);

        setPenColor_c(c_theme);
        Draw::line(_rect.left() + 16 * ss, _rect.top() + 108 * ss, _rect.right() - 16 * ss, _rect.top() + 108 * ss, 4 * ss);

        setPenColor_false();
        setBrushColor_c(c_symbol);
        Draw::rect(_rect.right() - 24 * ss, _rect.top() + 128 * ss, _rect.right() - 16 * ss, _rect.bottom() - 20 * ss);
        Draw::circle(_rect.right() - 20 * ss, _rect.top() + 128 * ss, 4 * ss);
        Draw::circle(_rect.right() - 20 * ss, _rect.bottom() - 20 * ss, 4 * ss);

        setBrushColor_c(c_theme);

        int scroll_num = (_rect.bottom() - 4 - (_rect.top() + 116 * ss)) / 40 / ss;

        float _pos1 = _rect.top() + 128 * ss + ((_rect.bottom() - 20 * ss) - (_rect.top() + 128 * ss)) *
                qMin(1.0f, (event_scroll_top) / event_list.size());
        float _pos2 = _rect.top() + 128 * ss + ((_rect.bottom() - 20 * ss) - (_rect.top() + 128 * ss)) *
                qMin(1.0f, (event_scroll_top + scroll_num) / event_list.size());

        Draw::rect(_rect.right() - 24 * ss, _pos1,
                   _rect.right() - 16 * ss, _pos2);
        Draw::circle(_rect.right() - 20 * ss, _pos1, 4 * ss);
        Draw::circle(_rect.right() - 20 * ss, _pos2, 4 * ss);

        int scroll_max = qMin(event_list.size(), int(event_scroll_top) + scroll_num);

        auto tmp_mat = QMatrix().scale(ss * 32.0 / 64.0, ss * 32.0 / 64.0);
        for(int i = int(event_scroll_top); i < scroll_max; i ++) {
            DB_STAGE_EVENT *_event = &_stage->events[event_list[i]];
            int tmp = i - int(event_scroll_top);
            if(_event->type >= 0 && _event->type < 16) {
                Draw::painter->drawTiledPixmap(_rect.left() + 136 * ss - 16 * ss, _rect.top() + 136 * ss + 40 * tmp * ss - 16 * ss,
                                               32 * ss, 32 * ss, Spr::sprite_event_icon[_event->type].transformed(tmp_mat, Qt::SmoothTransformation));
            }
            auto text = _event->getDescribe(&db);
            setPenColor_ca(c_textMain, _event->data["enable"]? 255: 128);
            Draw::text(_rect.left() + 24 * ss, _rect.top() + 136 * ss + 40 * tmp * ss + 2,
                       text[0], Qt::AlignLeft | Qt::AlignVCenter);
            Draw::text_line_with_length(_rect.left() + 160 * ss, _rect.top() + 136 * ss + 40 * tmp * ss + 2,
                       text[1], _rect.right() - 256 * ss, Qt::AlignLeft | Qt::AlignVCenter);
            if(_event->id == buff_id3) {
                setPenColor_c(c_theme);
                setBrushColor_false();
                Draw::rect(_rect.left() + 18 * ss, _rect.top() + 118 * ss + 40 * tmp * ss,
                           _rect.right() - 32 * ss, _rect.top() + 114 * ss + 40 * (tmp + 1) * ss,
                           2 * ss);
                Draw::line(_rect.right() - 48 * ss - 8 * ss, _rect.top() + 136 * ss + 40 * tmp * ss - 8 * ss,
                           _rect.right() - 48 * ss + 8 * ss, _rect.top() + 136 * ss + 40 * tmp * ss + 8 * ss, 2);
                Draw::line(_rect.right() - 48 * ss + 8 * ss, _rect.top() + 136 * ss + 40 * tmp * ss - 8 * ss,
                           _rect.right() - 48 * ss - 8 * ss, _rect.top() + 136 * ss + 40 * tmp * ss + 8 * ss, 2);
            }
        }
    }
}

void Window_editor_stage::draw_game(QRectF _rect)
{
    float ss = CacheAgent::getInstance().setting.editorScale();

    setPenColor_false();
    setBrushColor_c(c_backgroundMain);
    Draw::roundRect(_rect.left() + 4, _rect.top(), _rect.right() - 4, _rect.bottom(), 6);

    float mid_x = _rect.left() + (_rect.right() - _rect.left()) / 2;
    float mid_y = _rect.top() + (_rect.bottom() - 48 * ss - _rect.top()) / 2;

    float scale = qMin((_rect.width() - 32 * ss) / 10.0f, (_rect.height() - 80 * ss) / 12.0f) / 2.0;

    float _left = mid_x - 10 * scale - 1;
    float _right = mid_x + 10 * scale - 1;
    float _top = mid_y - 12 * scale;
    float _bottom = mid_y + 12 * scale;

    if(runner_state == RUNNER_STATE::IDLE) {
        setPenColor_false();
        Draw::painter->setBrush(Sprite(ui_ban_area));

        Draw::rect(_left, _top, _right, _bottom);

        setPenColor_false();
        setBrushColor_c(c_theme);

        Draw::rect((_left + _right) / 2 - 144 * ss,
                   (_top + _bottom) / 2 - 48 * ss,
                   (_left + _right) / 2 + 144 * ss,
                   (_top + _bottom) / 2 + 48 * ss, 4);

        setPenColor_c(c_backgroundMain);
        Draw::setTextSize(20 * ss);
        Draw::text((_left + _right) / 2, (_top + _bottom) / 2 + 2, "P R O G R A M\nO F F L I N E", Qt::AlignHCenter | Qt::AlignVCenter);

    }
    setPenColor_c(c_theme);
    setBrushColor_false();
    Draw::rect(_left, _top, _right, _bottom, 4);

    int _pos = _rect.bottom() - 46 * ss - 2 * ss - 4;

    auto tmp_mat = QMatrix().scale(ss * 36.0 / 96.0, ss * 36.0 / 96.0);

    Draw::painter->drawTiledPixmap((_left + _right) / 2 - 96 * ss - 18 * ss, _pos, 36 * ss, 36 * ss,
                                   Sprite(icon_runner3).transformed(tmp_mat, Qt::SmoothTransformation));
    Draw::painter->drawTiledPixmap((_left + _right) / 2 - 32 * ss - 18 * ss, _pos, 36 * ss, 36 * ss,
                                   Sprite(icon_runner2).transformed(tmp_mat, Qt::SmoothTransformation));
    Draw::painter->drawTiledPixmap((_left + _right) / 2 + 32 * ss - 18 * ss, _pos, 36 * ss, 36 * ss,
                                   Sprite(icon_runner1).transformed(tmp_mat, Qt::SmoothTransformation));
    Draw::painter->drawTiledPixmap((_left + _right) / 2 + 96 * ss - 18 * ss, _pos, 36 * ss, 36 * ss,
                                   Sprite(icon_runner0).transformed(tmp_mat, Qt::SmoothTransformation));

}

void Window_editor_stage::draw_code(QRectF _rect)
{
    float ss = CacheAgent::getInstance().setting.editorScale();

    Draw::setTextSize(16 * ss);

    setPenColor_false();
    setBrushColor_c(c_backgroundMain);
    Draw::roundRect(_rect.left() + 4, _rect.top(), _rect.right() - 4, _rect.bottom(), 6);

    if(MainEditorWindow::id1 < 1 || MainEditorWindow::id2 == -1 || MainEditorWindow::id2 >= db.stage[MainEditorWindow::id1 - 1].size()) {
    } else {
        auto *_events = &db.stage[MainEditorWindow::id1 - 1][MainEditorWindow::id2].events;

        for(auto i = _events->begin(); i != _events->end(); i ++) {
            if(i->id == buff_id3) {
                i->renderCode(this, &db, QRectF(_rect.left(), _rect.top() + 40 * ss, _rect.width(), rect().height()), &code_scroll_top, ss);
                break;
            }
        }
    }


}




















