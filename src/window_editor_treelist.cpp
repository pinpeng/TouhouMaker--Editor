#include "window_editor_treelist.h"

#include "draw.h"
#include "window/editor/mainEditorWindow.h"

#include "dataSet/cacheAgent.h"

#include <QLineF>
#include <complex>
#include <QMouseEvent>
#include <QWheelEvent>

#include <QApplication>

#include "widget/transparentDialog.h"

#include "sprite.h"

Window_editor_treelist::Window_editor_treelist(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    fatherWindow = nullptr;

    timer = new BaseThread();
    connect(timer, SIGNAL(timeout()), this, SLOT(timeoutRepaint()));
    timer->start();

    setFixedWidth(480 * CacheAgent::getInstance().setting.editorScale());

    db = CacheAgent::getInstance().database();
    id_now = -1;
}

void Window_editor_treelist::updateFromOutside(int _request_id)
{
    if(_request_id == 0) return;
    db = CacheAgent::getInstance().database();
    bool flag = true;
    if(MainEditorWindow::id1 >= 1) {
        if(id_now != -1) {
            for(int i = 0; i < db.stage[MainEditorWindow::id1 - 1].size(); i ++) {
                if(db.stage[MainEditorWindow::id1 - 1][i]._stageId == id_now) {
                    MainEditorWindow::id2 = i;
                    flag = false;
                    break;
                }
            }
        }
    } else {
        flag = false;
    }
    if(flag) {
        MainEditorWindow::id1 = -1;
        MainEditorWindow::id2 = -1;
    }
}


void Window_editor_treelist::paintEvent(QPaintEvent *)
{
    db = CacheAgent::getInstance().database();
    float ss = CacheAgent::getInstance().setting.editorScale();
    float _offset = 0.5 - state_timer;

    if(state_timer <= 0) {
        Draw::begin(this);
        Draw::setAntialising(true);

        setPenColor_c(c_itemEdge);
        setBrushColor_c(c_backgroundMain);

        Draw::roundRect(rect().right() - 72 * ss,
                        (rect().top() + rect().bottom()) / 2.0 - 64 * ss,
                        rect().right() - 16 * ss,
                        (rect().top() + rect().bottom()) / 2.0 + 64 * ss,
                        6, 2);
        setPenColor_c(c_theme);
        Draw::line(rect().right() - 32 * ss + _offset * 8 * ss,
                   (rect().top() + rect().bottom()) / 2.0,
                   rect().right() - 32 * ss - _offset * 8 * ss,
                   (rect().top() + rect().bottom()) / 2.0 + 8 * ss, 4 * ss);
        Draw::line(rect().right() - 32 * ss + _offset * 8 * ss,
                   (rect().top() + rect().bottom()) / 2.0,
                   rect().right() - 32 * ss - _offset * 8 * ss,
                   (rect().top() + rect().bottom()) / 2.0 - 8 * ss, 4 * ss);
        Draw::end();
        return;
    }

    Draw::begin(this);
    Draw::setAntialising(true);

    Draw::setTextDefault();


    setPenColor_c(c_itemEdge);
    setBrushColor_c(c_backgroundMain);

    Draw::roundRect(rect().left() + 16 * ss,
                    rect().top() + 16 * ss,
                    rect().right() - 48 * ss,
                    rect().bottom() - 16 * ss,
                    6, 2);

    Draw::roundRect(rect().right() - 72 * ss,
                    (rect().top() + rect().bottom()) / 2.0 - 64 * ss,
                    rect().right() - 16 * ss,
                    (rect().top() + rect().bottom()) / 2.0 + 64 * ss,
                    6, 2);
    setPenColor_false();
    Draw::rect(rect().right() - 74 * ss,
                    (rect().top() + rect().bottom()) / 2.0 - 68 * ss,
                    rect().right() - 48.6 * ss,
                    (rect().top() + rect().bottom()) / 2.0 + 68 * ss);

    setPenColor_c(c_theme);
    Draw::line(rect().right() - 32 * ss + _offset * 8 * ss,
               (rect().top() + rect().bottom()) / 2.0,
               rect().right() - 32 * ss - _offset * 8 * ss,
               (rect().top() + rect().bottom()) / 2.0 + 8 * ss, 4 * ss);
    Draw::line(rect().right() - 32 * ss + _offset * 8 * ss,
               (rect().top() + rect().bottom()) / 2.0,
               rect().right() - 32 * ss - _offset * 8 * ss,
               (rect().top() + rect().bottom()) / 2.0 - 8 * ss, 4 * ss);

    drawTop();
    setPenColor_c(c_inactive);

    float _top;
    _top = rect().top() + 80 * ss;
    drawItems_0(_top);
    _top = rect().top() + 80 * ss + 60 * ss - item_top * 60 * ss;
    bool flag = false;
    if(_top < rect().bottom() - 16 * ss) flag = drawItems_1(_top);
    if(!flag) {
        _top = rect().top() + 80 * ss + 60 * ss - item_top * 60 * ss + db.stage[0].size() * 60 * ss + 120 * ss;
        if(_top < rect().bottom() - 16 * ss) flag = drawItems_2(_top);
    }
    if(flag) {
        setPenColor_false();
        setBrushColor_c(c_theme);
        float _b = rect().bottom() - 32 * ss;
        float _x = (rect().left() + rect().right() - 48 * ss) / 2;
        Draw::circle(_x, _b, 4 * ss);
        Draw::circle(_x - 32 * ss, _b, 4 * ss);
        Draw::circle(_x + 32 * ss, _b, 4 * ss);
    }
    Draw::end();
}

void Window_editor_treelist::mousePressEvent(QMouseEvent *event)
{
    db = CacheAgent::getInstance().database();
    float ss = CacheAgent::getInstance().setting.editorScale();
    if(event->button() == Qt::LeftButton) {

        float mx = event->pos().x();
        float my = event->pos().y();
        if(state) {
            if(mx > rect().right() - 64 * ss) changeState();
            else {
                float _top;
                _top = rect().top() + 80 * ss;
                if(my > _top) mouseClickSelect0(mx, my, _top);
                _top = rect().top() + 80 * ss + 60 * ss - item_top * 60 * ss;
                if(my > _top || _top < rect().bottom() - 16 * ss) mouseClickSelect1(mx, my, _top);
                _top = rect().top() + 80 * ss + 60 * ss - item_top * 60 * ss + db.stage[0].size() * 60 * ss + 120 * ss;
                if(my > _top || _top < rect().bottom() - 16 * ss) mouseClickSelect2(mx, my, _top);
            }
        } else {
            if(mx < rect().right() - 16 * ss) changeState();
        }
    }
    repaint();
}

void Window_editor_treelist::mouseClickSelect0(float mx, float my, float _top)
{
    float ss = CacheAgent::getInstance().setting.editorScale();
    if(my > _top + 60 * ss) return;
    if(rect().left() + 32 * ss < mx && mx < rect().right() - 72 * ss) {
        if(_top < my && my < _top + 60 * ss) {
            MainEditorWindow::id1 = 0;
            MainEditorWindow::id2 = 0;
            id_now = -1;
            emit requestUpdate(0);
        }
    }
}

void Window_editor_treelist::mouseClickSelect1(float mx, float my, float _top)
{
    float ss = CacheAgent::getInstance().setting.editorScale();
    if(my > _top + db.stage[0].size() * 60 * ss + 120 * ss) return;
    if(rect().left() + 32 * ss < mx && mx < rect().right() - 72 * ss) {

        float _htop = qMax(_top, rect().top() + 80 * ss + 60 * ss);
        int i = 1;

        for(; i <= db.stage[0].size(); i ++) {
            float top_y = _top + i * 60 * ss;

            if(top_y < _htop + 30 * ss) continue;
            if(top_y > rect().bottom() - 64 * ss) return;
            if(top_y < my && my < top_y + 60 * ss) {
                if(MainEditorWindow::id1 == 1 && MainEditorWindow::id2 == i - 1) {
                    float mid_x, mid_y;
                    mid_x = rect().right() - 72 * ss - 96 * ss;
                    mid_y = _top + 60 * ss + (i - 1) * 60 * ss + 30 * ss;
                    if(abs(mx - mid_x) < 14 * ss && abs(my - mid_y) < 14 * ss) {
                        if(i - 1 <= 0) {
                            TransparentDialog::play(fatherWindow, "无法上移");
                        } else {
                            db.stage[0].swap(i - 1, i - 2);
                            CacheAgent::getInstance().databaseUpdate(db);
                            db = CacheAgent::getInstance().database();
                            MainEditorWindow::id1 = -1;
                            MainEditorWindow::id2 = -1;
                            id_now = -1;
                            emit requestUpdate(0);
                        }
                        return;
                    }
                    mid_x = rect().right() - 72 * ss - 64 * ss;
                    if(abs(mx - mid_x) < 14 * ss && abs(my - mid_y) < 14 * ss) {
                        if(i >= db.stage[0].size()) {
                            TransparentDialog::play(fatherWindow, "无法下移");
                        } else {
                            db.stage[0].swap(i - 1, i);
                            CacheAgent::getInstance().databaseUpdate(db);
                            db = CacheAgent::getInstance().database();
                            MainEditorWindow::id1 = -1;
                            MainEditorWindow::id2 = -1;
                            id_now = -1;
                            emit requestUpdate(0);
                        }
                        return;
                    }
                    mid_x = rect().right() - 72 * ss - 32 * ss;
                    if(abs(mx - mid_x) < 14 * ss && abs(my - mid_y) < 14 * ss) {
                        if(db.stage[0].size() <= 1) {
                            TransparentDialog::play(fatherWindow, "至少保留一个");
                        } else {
                            db.stage[0].removeAt(i - 1);
                            CacheAgent::getInstance().databaseUpdate(db);
                            db = CacheAgent::getInstance().database();
                            MainEditorWindow::id1 = -1;
                            MainEditorWindow::id2 = -1;
                            id_now = -1;
                            emit requestUpdate(0);
                        }
                        return;
                    }
                } else {
                    MainEditorWindow::id1 = 1;
                    MainEditorWindow::id2 = i - 1;
                    id_now = db.stage[0][MainEditorWindow::id2]._stageId;
                    emit requestUpdate(0);
                    return;
                }
            }
        }

        float _b = _top + 60 * ss + db.stage[0].size() * 60 * ss;
        if(_b > _htop && _b < rect().bottom() - 64 * ss) {
            if(_b < my && my < _b + 60 * ss) {
                db.stage_append(0, "Stage " + QString::number(i));
                CacheAgent::getInstance().databaseUpdate(db);
                db = CacheAgent::getInstance().database();
                MainEditorWindow::id1 = -1;
                MainEditorWindow::id2 = -1;
                id_now = -1;
                emit requestUpdate(0);
            }
        }
    }
}

void Window_editor_treelist::mouseClickSelect2(float mx, float my, float _top)
{
    float ss = CacheAgent::getInstance().setting.editorScale();
    if(my > _top + db.stage[1].size() * 60 * ss + 120 * ss) return;
    if(rect().left() + 32 * ss < mx && mx < rect().right() - 72 * ss) {

        float _htop = qMax(_top, rect().top() + 80 * ss + 60 * ss);
        int i = 1;

        for(; i <= db.stage[1].size(); i ++) {
            float top_y = _top + i * 60 * ss;

            if(top_y < _htop + 60 * ss) continue;
            if(top_y > rect().bottom() - 64 * ss) return;

            if(top_y < my && my < top_y + 60 * ss) {
                if(MainEditorWindow::id1 == 2 && MainEditorWindow::id2 == i - 1) {
                    float mid_x, mid_y;
                    mid_x = rect().right() - 72 * ss - 96 * ss;
                    mid_y = _top + 80 * ss + (i - 1) * 60 * ss;
                    if(abs(mx - mid_x) < 14 * ss && abs(my - mid_y) < 14 * ss) {
                        if(i - 1 <= 0) {
                            TransparentDialog::play(fatherWindow, "无法上移");
                        } else {
                            db.stage[1].swap(i - 1, i - 2);
                            CacheAgent::getInstance().databaseUpdate(db);
                            db = CacheAgent::getInstance().database();
                            MainEditorWindow::id1 = -1;
                            MainEditorWindow::id2 = -1;
                            id_now = -1;
                            emit requestUpdate(0);
                        }
                        return;
                    }
                    mid_x = rect().right() - 72 * ss - 64 * ss;
                    if(abs(mx - mid_x) < 14 * ss && abs(my - mid_y) < 14 * ss) {
                        if(i >= db.stage[1].size()) {
                            TransparentDialog::play(fatherWindow, "无法下移");
                        } else {
                            db.stage[1].swap(i - 1, i);
                            CacheAgent::getInstance().databaseUpdate(db);
                            db = CacheAgent::getInstance().database();
                            MainEditorWindow::id1 = -1;
                            MainEditorWindow::id2 = -1;
                            id_now = -1;
                            emit requestUpdate(0);
                        }
                        return;
                    }
                    mid_x = rect().right() - 72 * ss - 32 * ss;
                    if(abs(mx - mid_x) < 14 * ss && abs(my - mid_y) < 14 * ss) {
                        if(db.stage[1].size() <= 1) {
                            TransparentDialog::play(fatherWindow, "至少保留一个");
                        } else {
                            db.stage[1].removeAt(i - 1);
                            CacheAgent::getInstance().databaseUpdate(db);
                            db = CacheAgent::getInstance().database();
                            MainEditorWindow::id1 = -1;
                            MainEditorWindow::id2 = -1;
                            id_now = -1;
                            emit requestUpdate(0);
                        }
                        return;
                    }
                } else {
                    MainEditorWindow::id1 = 2;
                    MainEditorWindow::id2 = i - 1;
                    id_now = db.stage[1][MainEditorWindow::id2]._stageId;
                    emit requestUpdate(0);
                    return;
                }
            }
        }

        float _b = _top + 60 * ss + db.stage[1].size() * 60 * ss;
        if(_b > _htop && _b < rect().bottom() - 64 * ss) {
            if(_b < my && my < _b + 60 * ss) {
                db.stage_append(1, "EX Stage " + QString::number(i));
                CacheAgent::getInstance().databaseUpdate(db);
                db = CacheAgent::getInstance().database();
                MainEditorWindow::id1 = -1;
                MainEditorWindow::id2 = -1;
                id_now = -1;
                emit requestUpdate(0);
            }
        }
    }
}

void Window_editor_treelist::mouseDoubleClickEvent(QMouseEvent *event)
{
}

void Window_editor_treelist::wheelEvent(QWheelEvent *event)
{
    float ss = CacheAgent::getInstance().setting.editorScale();

    int _pre = item_top;

    int scroll_num = (rect().bottom() - 64 * ss - (rect().top() + 320 * ss)) / 60 / ss;
    item_top -= float(event->angleDelta().y()) / 120.0;
    item_top = qMax(0.0f, item_top);
    item_top = qMin(item_top, float(db.stage[0].size() + db.stage[1].size() - scroll_num));
    item_top = qMax(0.0f, item_top);
    item_top = floor(item_top);

    if(_pre != item_top) repaint();
}

void Window_editor_treelist::drawTop()
{
    float ss = CacheAgent::getInstance().setting.editorScale();

    Draw::setTextSize(24 * ss);
    setPenColor_c(c_theme);
    QString tmp = "关卡列表";
    Draw::text((rect().left() + rect().right() - 48 * ss) / 2, rect().top() + 48 * ss + 2, tmp, Qt::AlignHCenter | Qt::AlignVCenter);

}

void Window_editor_treelist::drawItems_0(float _top)
{
    float ss = CacheAgent::getInstance().setting.editorScale();

    setPenColor_c(c_symbol);
    Draw::line(rect().left() + 24 * ss, _top, rect().right() - 72 * ss, _top, 2);

    Draw::setTextSize(18 * ss);
    setPenColor_c(c_textMain);
    Draw::text_line_with_length(rect().left() + 36 * ss, _top + 32 * ss,
               "主界面", rect().width() - 120 * ss,
               Qt::AlignLeft | Qt::AlignVCenter);

    if(MainEditorWindow::id1 == 0) {
        setPenColor_c(c_theme);
        setBrushColor_false();
        Draw::roundRect(rect().left() + 32 * ss, _top + 8 * ss, rect().right() - 72 * ss, _top + 56 * ss, 3, 2 * ss);
    }

}

bool Window_editor_treelist::drawItems_1(float _top)
{

    float ss = CacheAgent::getInstance().setting.editorScale();

    float _htop = qMax(_top, rect().top() + 80 * ss + 60 * ss);
    setPenColor_c(c_symbol);
    Draw::line(rect().left() + 24 * ss, _htop, rect().right() - 72 * ss, _htop, 2);

    Draw::setTextSize(18 * ss);
    setPenColor_c(c_textMain);
    Draw::text(rect().left() + 36 * ss, _htop + 30 * ss + 2, "普通关卡 - 共" + QString::number(db.stage[0].size()) + "关",
               Qt::AlignLeft | Qt::AlignVCenter);

    float _b = _top + 60 * ss + db.stage[0].size() * 60 * ss;
    if(_top + 60 * ss < _htop + 60 * ss && _b > _htop) {
        setPenColor_false();
        setBrushColor_c(c_theme);
        float _x = (rect().left() + rect().right() - 48 * ss) / 2;
        Draw::circle(_x, _htop + 60 * ss, 4 * ss);
        Draw::circle(_x - 32 * ss, _htop + 60 * ss, 4 * ss);
        Draw::circle(_x + 32 * ss, _htop + 60 * ss, 4 * ss);
    }

    setPenColor_c(c_textMain);
    int num = 0;
    for(; num < db.stage[0].size(); num ++) {
        float mid_x, mid_y;
        mid_y = _top + 60 * ss + num * 60 * ss + 30 * ss;
        if(mid_y < _htop + 60 * ss) continue;
        if(mid_y > rect().bottom() - 64 * ss) return true;
        if(MainEditorWindow::id1 == 1 && MainEditorWindow::id2 == num) {
            setPenColor_c(c_textMain);
            Draw::text_line_with_length(rect().left() + 40 * ss, mid_y,
                                        "> " + db.stage[0][num].name, rect().width() - 256 * ss,
                       Qt::AlignLeft | Qt::AlignVCenter);
            setPenColor_c(c_theme);
            setBrushColor_false();
            Draw::roundRect(rect().left() + 32 * ss, mid_y - 24 * ss,
                       rect().right() - 72 * ss, mid_y + 24 * ss, 3, 2 * ss);
            mid_x = rect().right() - 72 * ss - 96 * ss;
            Draw::line(mid_x, mid_y - 4 * ss, mid_x - 8 * ss, mid_y + 4 * ss, 4 * ss);
            Draw::line(mid_x, mid_y - 4 * ss, mid_x + 8 * ss, mid_y + 4 * ss, 4 * ss);
            mid_x = rect().right() - 72 * ss - 64 * ss;
            Draw::line(mid_x, mid_y + 4 * ss, mid_x - 8 * ss, mid_y - 4 * ss, 4 * ss);
            Draw::line(mid_x, mid_y + 4 * ss, mid_x + 8 * ss, mid_y - 4 * ss, 4 * ss);
            mid_x = rect().right() - 72 * ss - 32 * ss;
            Draw::line(mid_x - 8 * ss, mid_y, mid_x + 8 * ss, mid_y, 4 * ss);
        } else {
            setPenColor_c(c_textMain);
            Draw::text_line_with_length(rect().left() + 40 * ss, mid_y,
                                        "> " + db.stage[0][num].name, rect().width() - 128 * ss,
                       Qt::AlignLeft | Qt::AlignVCenter);
        }
    }
    if(_b > _htop) {
        if(_b < rect().bottom() - 64 * ss) {
        setPenColor_c(c_theme);
        Draw::text(rect().left() + 36 * ss, _b + 24 * ss, "点击此处添加...",
                   Qt::AlignLeft | Qt::AlignVCenter);
        } else return true;
    }
    return false;
}

bool Window_editor_treelist::drawItems_2(float _top)
{

    float ss = CacheAgent::getInstance().setting.editorScale();

    float _htop = qMax(_top, rect().top() + 80 * ss + 120 * ss);

    if(_htop > rect().bottom() - 64 * ss - 30 * ss) return true;
    setPenColor_c(c_symbol);
    Draw::line(rect().left() + 24 * ss, _htop, rect().right() - 72 * ss, _htop, 2);

    Draw::setTextSize(18 * ss);
    setPenColor_c(c_textMain);
    Draw::text(rect().left() + 36 * ss, _htop + 30 * ss + 2, "EX关卡 - 共" + QString::number(db.stage[0].size()) + "关",
               Qt::AlignLeft | Qt::AlignVCenter);


    float _b = _top + 60 * ss + db.stage[1].size() * 60 * ss;
    if(_top + 60 * ss < _htop + 60 * ss && _b > _htop) {
        setPenColor_false();
        setBrushColor_c(c_theme);
        float _x = (rect().left() + rect().right() - 48 * ss) / 2;
        Draw::circle(_x, _htop + 60 * ss, 4 * ss);
        Draw::circle(_x - 32 * ss, _htop + 60 * ss, 4 * ss);
        Draw::circle(_x + 32 * ss, _htop + 60 * ss, 4 * ss);
    }

    setPenColor_c(c_textMain);
    int num = 0;
    for(; num < db.stage[1].size(); num ++) {
        float mid_x, mid_y;
        mid_y = _top + 60 * ss + num * 60 * ss + 30 * ss;
        if(mid_y < _htop + 60 * ss) continue;
        if(mid_y > rect().bottom() - 64 * ss) return true;
        if(MainEditorWindow::id1 == 2 && MainEditorWindow::id2 == num) {
            setPenColor_c(c_textMain);
            Draw::text_line_with_length(rect().left() + 40 * ss, mid_y,
                                        "> " + db.stage[1][num].name, rect().width() - 256 * ss,
                       Qt::AlignLeft | Qt::AlignVCenter);
            setPenColor_c(c_theme);
            setBrushColor_false();
            Draw::roundRect(rect().left() + 32 * ss, mid_y - 24 * ss,
                       rect().right() - 72 * ss, mid_y + 24 * ss, 3, 2 * ss);
            mid_x = rect().right() - 72 * ss - 96 * ss;
            Draw::line(mid_x, mid_y - 4 * ss, mid_x - 8 * ss, mid_y + 4 * ss, 4 * ss);
            Draw::line(mid_x, mid_y - 4 * ss, mid_x + 8 * ss, mid_y + 4 * ss, 4 * ss);
            mid_x = rect().right() - 72 * ss - 64 * ss;
            Draw::line(mid_x, mid_y + 4 * ss, mid_x - 8 * ss, mid_y - 4 * ss, 4 * ss);
            Draw::line(mid_x, mid_y + 4 * ss, mid_x + 8 * ss, mid_y - 4 * ss, 4 * ss);
            mid_x = rect().right() - 72 * ss - 32 * ss;
            Draw::line(mid_x - 8 * ss, mid_y, mid_x + 8 * ss, mid_y, 4 * ss);
        } else {
            setPenColor_c(c_textMain);
            Draw::text_line_with_length(rect().left() + 40 * ss, mid_y,
                                        "> " + db.stage[1][num].name, rect().width() - 128 * ss,
                       Qt::AlignLeft | Qt::AlignVCenter);
        }
    }
    if(_b > _htop) {
        if(_b < rect().bottom() - 64 * ss) {
        setPenColor_c(c_theme);
        Draw::text(rect().left() + 36 * ss, _b + 24 * ss, "点击此处添加...",
                   Qt::AlignLeft | Qt::AlignVCenter);
        } else return true;
    }
    return false;
}

void Window_editor_treelist::changeState()
{
    state_change = 0;
    state = !state;
}

void Window_editor_treelist::timeoutRepaint()
{
    float cursor_x = QCursor::pos().x() - fatherWindow->x();
    if(state_change == 0 && cursor_x > rect().right()) state_change = 0.01;
    if(cursor_x < rect().right()) state_change = 0;

    if(state) {
        state_timer = qMin(state_timer + 0.05f, 1.0f);
        if(state_change > 0) state_change += 0.01;
        if(state_change > 1) {
            changeState();
        }
    } else {
        state_timer = qMax(state_timer - 0.05f, 0.0f);
    }
    if(fatherWindow != nullptr) {
        float tmp = -cos(state_timer * 3.1415926) * 0.5 + 0.5;
        setGeometry((tmp - 1) * 432 * CacheAgent::getInstance().setting.editorScale(), 0,
                    480 * CacheAgent::getInstance().setting.editorScale(), fatherWindow->height());
    }
    if(!isActiveWindow()) return;
    if(0 < state_timer && state_timer < 1) repaint();
}




















