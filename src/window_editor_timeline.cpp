#include "window_editor_timeline.h"

#include "draw.h"

#include <QMouseEvent>
#include <complex>
#include <QApplication>

#include "window_editor_main.h"

#include "global.h"

float Window_editor_timeline::view_max = 18000;
float Window_editor_timeline::view_left = 18000;
float Window_editor_timeline::view_right = 18000;

Window_editor_timeline_insert::Window_editor_timeline_insert(Database *_db, int _time, int _stage_type, int _stage_id, QWidget *parent) : SmallWindow(parent)
{
    setFixedSize(1200, 400);
    setWindowTitle("选择一种事件");

    db = _db;
    time = _time;
    stage_type = _stage_type;
    stage_id = _stage_id;

}

void Window_editor_timeline_insert::paintEvent(QPaintEvent *)
{
    Draw::smallWindow(this, this);

    QStringList _text;
    _text << "设置背景" <<
             "设置音乐" <<
             "播放音效" <<
             "播放特效" <<

             "道中小怪" <<
             "道中小怪队列" <<
             "剧情" <<
             "计时剧情" <<

             "BOSS开始" <<
             "BOSS结束" <<
             "BOSS弹幕" <<
             "BOSS符卡" <<

             "清场" <<
             "跳转" <<
             "结束" <<
             "断点";

    Draw::begin(this);
    Draw::setAntialising(true);
    Draw::setTextDefault();
    Draw::setTextSize(16);

    auto tmp = QMatrix().scale(0.5, 0.5);

    float _l, _r, _t, _b;
    for(int i = 0; i < 16; i ++) {
        _l = 16 + (i % 4) * 292 + 8;
        _r = _l + 276;
        _t = 64 + int(i / 4) * 80 + 8;
        _b = _t + 64;
        setPenColor_c(c_theme);
        setBrushColor_false();
        Draw::roundRect(_l, _t, _r, _b, 4, 2.0);
        Draw::sprite(Spr::sprite_event_icon[i].transformed(tmp, Qt::SmoothTransformation), _l + 16, _t + 16);
        setPenColor_c(c_textMain);
        Draw::text(_l + 138, _t + 32, _text[i], Qt::AlignCenter);
    }

    Draw::end();
}

void Window_editor_timeline_insert::mousePressEvent(QMouseEvent *event)
{
    if(_isClosing){
        return;
    }
    SmallWindow::mousePressEvent(event);
    if(event->button() == Qt::LeftButton) {
        float mx = event->x();
        float my = event->y();
        float _l, _r, _t, _b;
        for(int i = 0; i < 16; i ++) {
            _l = 16 + (i % 4) * 292 + 8;
            _r = _l + 276;
            _t = 64 + int(i / 4) * 80 + 8;
            _b = _t + 64;
            if(_l < mx && mx < _r && _t < my && my < _b) {
                createEvent(i);
                break;
            }
        }

    }
}

void Window_editor_timeline_insert::createEvent(int _index)
{
    DB_STAGE_EVENT _event;
    _event.time = time;
    _event.id = ++Global::stage_event_id_top;
    _event.type = _index;
    _event.init(db);

    float tmp = Window_editor_timeline::view_right - Window_editor_timeline::view_left;
    Window_editor_timeline::view_left = time / Window_editor_timeline::view_max * 100.0 - tmp / 2.0;
    Window_editor_timeline::view_right = time / Window_editor_timeline::view_max * 100.0 + tmp / 2.0;
    if(Window_editor_timeline::view_left < 0) {
        Window_editor_timeline::view_left = 0;
        Window_editor_timeline::view_right = tmp;
    }
    if(Window_editor_timeline::view_right > 100) {
        Window_editor_timeline::view_left = 100 - tmp;
        Window_editor_timeline::view_right = 100;
    }
    db->stage[stage_type][stage_id].events.append(_event);
    Global::databaseUpdate(Database(*db));
    end();
}


Window_editor_timeline::Window_editor_timeline(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);

    setFixedHeight(192.0 * Global::setting.editor_scale);

    setMouseTracking(true);


    timer = new BaseThread();
    connect(timer, SIGNAL(timeout()), this, SLOT(timeoutRepaint()));
    timer->start();

    toolBox_selected = 0;
    alpha_toolBoxSelected[0] = 1;

    // arraw, 7
    poly0[0].setPoints(QPointF(-13, 19), QPointF(0, 6));
    poly0[1].setPoints(QPointF(0, 6), QPointF(4, 20));
    poly0[2].setPoints(QPointF(4, 20), QPointF(17, -17));
    poly0[3].setPoints(QPointF(17, -17), QPointF(-20, -4));
    poly0[4].setPoints(QPointF(-20, -4), QPointF(-6, 0));
    poly0[5].setPoints(QPointF(-6, 0), QPointF(-19, 13));
    poly0[6].setPoints(QPointF(-19, 13), QPointF(-13, 19));

    // move, 10
    poly1[0].setPoints(QPointF(0, -20), QPointF(0, 20));
    poly1[1].setPoints(QPointF(-20, 0), QPointF(20, 0));
    poly1[2].setPoints(QPointF(0, -20), QPointF(- 6, -14));
    poly1[3].setPoints(QPointF(0, -20), QPointF(6, -14));

    poly1[4].setPoints(QPointF(0, 20), QPointF(-6, 14));
    poly1[5].setPoints(QPointF(0, 20), QPointF(6, 14));
    poly1[6].setPoints(QPointF(-20, 0), QPointF(-14, -6));
    poly1[7].setPoints(QPointF(-20, 0), QPointF(-14, 6));
    poly1[8].setPoints(QPointF(20, 0), QPointF(14, -6));
    poly1[9].setPoints(QPointF(20, 0), QPointF(14, 6));

    // cut, 18
    for(int i = 0; i < 8; i ++) {
        float dir1 = (i * 45.0 + 12.0) / 180.0 * 3.1416;
        float dir2 = (i * 45.0 + 33.0) / 180.0 * 3.1416;
        poly2[i].setPoints(QPointF(-16.0 + 6.0 * cos(dir1), -6.0 * sin(dir1)), QPointF(-16.0 + 6.0 * cos(dir2), -6.0 * sin(dir2)));
        poly2[i + 8].setPoints(QPointF(6.0 * cos(dir1), 16.0 - 6.0 * sin(dir1)), QPointF(6.0 * cos(dir2), 16.0 - 6.0 * sin(dir2)));
    }
    poly2[16].setPoints(QPointF(-10.0, 4.0), QPointF(20.0, -8.0));
    poly2[17].setPoints(QPointF(-4.0, 10.0), QPointF(8.0, -20.0));

    // select, 12
    poly3[0].setPoints(QPointF(-18, -18), QPointF(-18 + 6, -18));
    poly3[1].setPoints(QPointF(-18, -18), QPointF(-18, -18 + 6));
    poly3[2].setPoints(QPointF(18, -18), QPointF(18 - 6, -18));
    poly3[3].setPoints(QPointF(18, -18), QPointF(18, -18 + 6));
    poly3[4].setPoints(QPointF(18, 18), QPointF(18 - 6, 18));
    poly3[5].setPoints(QPointF(18, 18), QPointF(18, 18 - 6));
    poly3[6].setPoints(QPointF(-18, 18), QPointF(-18 + 6, 18));
    poly3[7].setPoints(QPointF(-18, 18), QPointF(-18, 18 - 6));

    poly3[8].setPoints(QPointF(-5, -18), QPointF(5, -18));
    poly3[9].setPoints(QPointF(-5, 18), QPointF(5, 18));
    poly3[10].setPoints(QPointF(-18, -5), QPointF(-18, 5));
    poly3[11].setPoints(QPointF(18, -5), QPointF(18, 5));

    // brush, 12
    for(int i = 0; i < 4; i ++) {
        float dir1 = (i * 45.0 + 12.0 + 135.0) / 180.0 * 3.1416;
        float dir2 = (i * 45.0 + 33.0 + 135.0) / 180.0 * 3.1416;
        poly4[i].setPoints(QPointF(-12.0 + 6.0 * cos(dir1), 12.0 - 6.0 * sin(dir1)), QPointF(-12.0 + 6.0 * cos(dir2), 12.0 - 6.0 * sin(dir2)));
    }
    poly4[4].setPoints(QPointF(-16, 8), QPointF(-8, 0));
    poly4[5].setPoints(QPointF(-8, 16), QPointF(0, 8));

    poly4[6].setPoints(QPointF(-8, 0), QPointF(-12, -12));
    poly4[7].setPoints(QPointF(0, 8), QPointF(12, 12));

    poly4[8].setPoints(QPointF(0, -24), QPointF(-12, -12));
    poly4[9].setPoints(QPointF(24, 0), QPointF(12, 12));

    poly4[10].setPoints(QPointF(-8, -16), QPointF(16, 8));
    poly4[11].setPoints(QPointF(1, -23), QPointF(23, -1));

    eventHotPoint.clear();

    for(int i = 0; i <= view_max; i += 1) eventHotPoint.append((cos(i * 3.1416 / 300.0) / 2.0 + 0.5) * 100.0);

    updateFromOutside(-1);
}

Window_editor_timeline::~Window_editor_timeline()
{
}

void Window_editor_timeline::updateFromOutside(int _request_id)
{
    if(_request_id == 3) return;
    db = Global::database();
    if(Window_editor_main::id1 >= 1 && Window_editor_main::id2 != -1 &&
            Window_editor_main::id2 < db.stage[Window_editor_main::id1 - 1].size()) {
        view_max = db.stage[Window_editor_main::id1 - 1][Window_editor_main::id2].length;
        DB_STAGE *_stage = &db.stage[Window_editor_main::id1 - 1][Window_editor_main::id2];
        for(int i = 0; i < _stage->events.size(); i ++) {
            if(_stage->events[i].id == Window_editor_main::id3) {
                float tmp = view_right - view_left;
                view_left = _stage->events[i].time / view_max * 100.0 - tmp / 2.0;
                view_right = _stage->events[i].time / view_max * 100.0 + tmp / 2.0;
                if(view_left < 0) {
                    view_left = 0;
                    view_right = tmp;
                }
                if(view_right > 100) {
                    view_left = 100 - tmp;
                    view_right = 100;
                }
                break;
            }
        }
    } else {
        view_left = 0;
        view_right = 100;
        view_max = 18000;
    }

    repaintTimer = qMin(repaintTimer + 2, 4);
    buff_update = 1;
}

void Window_editor_timeline::timeoutRepaint()
{
    //static int buff_clear_timer = 0;
    if(!underMouse()) {
        if(mouse_down != 4) mouse_down = 0;
    }
    /*buff_clear_timer ++;
    if(buff_clear_timer >= 60) {
        buff_clear_timer = 0;
        buff_update = 1;
        repaintTimer = 4;
    }*/


    if(!underMouse() || Window_editor_main::id1 < 1 || Window_editor_main::id2 == -1) {
        for(int i = 0; i < 4; i ++) {
            alpha_toolBox[i] = qMax(0.0f, alpha_toolBox[i] - 0.1f);
            if(toolBox_selected == i) {
                alpha_toolBoxSelected[i] = qMin(1.0f, alpha_toolBoxSelected[i] + 0.1f);
            } else {
                alpha_toolBoxSelected[i] = qMax(0.0f, alpha_toolBoxSelected[i] - 0.1f);
            }
        }
    } else {
        float ss = Global::setting.editor_scale;
        for(int i = 0; i < 4; i ++) {
            if(abs(rect().left() + 96 * ss - mx) < 18 * ss &&
               abs(rect().top() + i * 42 * ss + 36 * ss - my) < 18 * ss) {
                alpha_toolBox[i] = qMin(1.0f, alpha_toolBox[i] + 0.1f);
            } else {
                alpha_toolBox[i] = qMax(0.0f, alpha_toolBox[i] - 0.1f);
            }
            if(toolBox_selected == i) {
                alpha_toolBoxSelected[i] = qMin(1.0f, alpha_toolBoxSelected[i] + 0.1f);
            } else {
                alpha_toolBoxSelected[i] = qMax(0.0f, alpha_toolBoxSelected[i] - 0.1f);
            }
        }
    }

    for(int i = 0; i < 4; i ++) {
        if((0 < alpha_toolBox[i] && alpha_toolBox[i] < 1) ||
           (0 < alpha_toolBoxSelected[i] && alpha_toolBoxSelected[i] < 1)) {
            repaintTimer = qMin(repaintTimer + 2, 4);
            //break;
        }
        //qDebug() << i << alpha_toolBox[i] << alpha_toolBoxSelected[i];
    }

    if(repaintTimer) {
        repaintTimer --;
        repaint();
    }
    /**/
}

void Window_editor_timeline::mousePressEvent(QMouseEvent *event)
{
    mx = event->x();
    my = event->y();

    if(Window_editor_main::id1 < 1 || Window_editor_main::id2 == -1) return;
    float ss = Global::setting.editor_scale;

    mx = event->x();
    my = event->y();

    if(event->button() == Qt::LeftButton) {
        if(mx < rect().left() + 128 * ss) {
            lb_toolBox(mx, my);
        } else if(my > rect().bottom() - 32 * ss) {
            lb_scale(mx, my);
        } else {
            lb_main(mx, my);
        }
    } else if(event->button() == Qt::RightButton) {
        if(mx > rect().left() + 128 * ss && my < rect().bottom() - 32 * ss) {
            rb_main(mx, my);
        }
    }
    repaintTimer = qMin(repaintTimer + 2, 4);

}

void Window_editor_timeline::lb_main(float mx, float my)
{
    float ss = Global::setting.editor_scale;
    if(mouse_down == 0) {

        float _l = rect().left() + 128 * ss;
        float _r = rect().right();
        float _w = _r - _l + 1;

        float _scale = (_w - 128) / ((view_right - view_left) / 100.0 * view_max);
        rbt = int(((mx - _l - 64) + view_left / 100.0 * view_max * _scale) / _scale);

        float _mag = 0.1;
        float _abs = 1000;
        if(_scale < 4) _mag = 4 / _scale;

        if(0 <= rbt && rbt < view_max) {
            QList<DB_STAGE_EVENT> *_events = &db.stage[Window_editor_main::id1 - 1][Window_editor_main::id2].events;
            rbi = -1;
            for(int i = 0; i < _events->size(); i ++) {
                if(abs(_events->at(i).time - rbt) <= _mag) {
                    if(abs(_events->at(i).time - rbt) < _abs) {
                        _abs = abs(_events->at(i).time - rbt);
                        Window_editor_main::id3 = _events->at(i).id;
                    }
                }
            }
        }
        buff_update = 1;

    } else if(mouse_down == 4) {
        if(rbx < mx && mx < rbx + 160 * ss) {
            if(rby < my && my < rby + 32 * ss) {
                insertEvent(rbt + (rbi == -1? 0: 1));
            } else if(rby + 32 * ss < my && my < rby + 64 * ss) {
                if(rbi != -1) deleteEvent(rbi);
            }
        }
        mouse_down = 0;
        buff_update = 1;
    }

}

void Window_editor_timeline::rb_main(float mx, float my)
{
    float ss = Global::setting.editor_scale;
    if(mouse_down == 0 || mouse_down == 4) {
        if(rect().left() + 128 * ss + 64 < mx && mx < rect().right() - 64) {

            float _l = rect().left() + 128 * ss;
            float _r = rect().right();
            float _w = _r - _l + 1;

            rbx = mx;
            rby = my;

            float _scale = (_w - 128) / ((view_right - view_left) / 100.0 * view_max);
            rbt = int(((mx - _l - 64) + view_left / 100.0 * view_max * _scale) / _scale);

            float _mag = 0.1;
            float _abs = 1000;
            if(_scale < 4) _mag = 4 / _scale;

            if(0 <= rbt && rbt < view_max) {
                mouse_down = 4;
                QList<DB_STAGE_EVENT> *_events = &db.stage[Window_editor_main::id1 - 1][Window_editor_main::id2].events;
                rbi = -1;
                for(int i = 0; i < _events->size(); i ++) {
                    if(abs(_events->at(i).time - rbt) <= _mag) {
                        if(abs(_events->at(i).time - rbt) < _abs) {
                            _abs = abs(_events->at(i).time - rbt);
                            rbi = i;
                        }
                    }
                }
            } else mouse_down = 0;
            buff_update = 1;
        }
    }

}

void Window_editor_timeline::lb_toolBox(float mx, float my)
{
    float ss = Global::setting.editor_scale;

    for(int i = 0; i < 4; i ++) {
        if(abs(rect().left() + 96 * ss - mx) < 18 * ss &&
           abs(rect().top() + i * 42 * ss + 36 * ss - my) < 18 * ss) {
            toolBox_selected = i;
            break;
        }
    }
}

void Window_editor_timeline::lb_scale(float mx, float my)
{
    float ss = Global::setting.editor_scale;
    float _l = rect().left() + 152 * ss;
    float _r = rect().right() - 24 * ss;
    float _w = _r - _l;
    float _view_l = _l + _w * view_left / 100.0;
    float _view_r = _l + _w * view_right / 100.0;

    if(abs(mx - _view_l) < 16 * ss) {
        mouse_down = 10;
    } else if(abs(mx - _view_r) < 16 * ss) {
        mouse_down = 11;
    } else if(_view_l < mx && mx < _view_r) {
        mouse_down = 12;
        mouse_scale_pos = (mx - _view_l) / (_view_r - _view_l);
    }
}

void Window_editor_timeline::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(Window_editor_main::id1 < 1 || Window_editor_main::id2 == -1) return;
    repaintTimer = qMin(repaintTimer + 2, 4);

}

void Window_editor_timeline::mouseMoveEvent(QMouseEvent *event)
{
    mx = event->x();
    my = event->y();

    if(Window_editor_main::id1 < 1 || Window_editor_main::id2 == -1) return;
    float ss = Global::setting.editor_scale;


    switch(mouse_down) {
    case 10: case 11:
    {
        float _l = rect().left() + 152 * ss;
        float _r = rect().right() - 24 * ss;
        float _w = _r - _l;
        float _mid_y = rect().bottom() - 24 * ss;

        if(my > _mid_y - 64 * ss && _l - 16 * ss < mx && mx < _r + 16 * ss) {
            float _tmp_l = view_left;
            float _tmp_r = view_right;
            if(mouse_down == 10) {
                view_left = qMax(0.0f, (mx - _l) / _w * 100.0f);
                view_left = qMin(view_left, view_right - 1.0f);
            } else if(mouse_down == 11) {
                view_right = qMin(100.0f, (mx - _l) / _w * 100.0f);
                view_right = qMax(view_right, view_left + 1.0f);
            }
            if(_tmp_l != view_left || _tmp_r != view_right) buff_update = 1;
        } else {
            mouse_down = 0;
        }

    } break;
    case 12:
    {
        float _l = rect().left() + 152 * ss;
        float _r = rect().right() - 24 * ss;
        float _w = _r - _l;
        float _mid_y = rect().bottom() - 24 * ss;

        if(my > _mid_y - 64 * ss && _l < mx && mx < _r) {

            float tmp = view_right - view_left;

            float _pos_left = ((mx - _l) / _w * 100.0 - tmp * mouse_scale_pos);
            float _pos_right = _pos_left + tmp;
            if(_pos_left < 0) {
                view_left = 0;
                view_right = view_left + tmp;
            } else if(_pos_right > 100) {
                view_left = 100 - tmp;
                view_right = 100;
            } else {
                view_left = _pos_left;
                view_right = _pos_right;
            }
        } else {
            mouse_down = 0;
        }
    } break;

    case 4:
        break;

    default:
        mouse_down = 0;
        break;
    }
    repaintTimer = qMin(repaintTimer + 2, 4);
}

void Window_editor_timeline::mouseReleaseEvent(QMouseEvent *)
{
    if(Window_editor_main::id1 < 1 || Window_editor_main::id2 == -1) return;
    if(mouse_down != 4) mouse_down = 0;
    repaintTimer = qMin(repaintTimer + 2, 4);
}

void Window_editor_timeline::wheelEvent(QWheelEvent *event)
{
    if(mouse_down == 0) {
        float tmp = view_right - view_left;
        float _pos_left = view_left - float(event->angleDelta().y()) / 3000.0 * sqrt(view_right - view_left);
        float _pos_right = _pos_left + tmp;

        if(_pos_left < 0) {
            view_left = 0;
            view_right = view_left + tmp;
        } else if(_pos_right > 100) {
            view_left = 100 - tmp;
            view_right = 100;
        } else {
            view_left = _pos_left;
            view_right = _pos_right;
        }
        repaintTimer = qMin(repaintTimer + 2, 4);

    }
}

bool Window_editor_timeline::lbr_brush() {
}

float drawSmooth(float _x1, float _y1, float _x2, float _y2, float _t1) {
    float _w = _x2 - _x1;
    float _h = _y2 - _y1;
    float _t2 = _h / _w;
    _t1 = (_t1 + _t2) / 2.0;
    float _tx = _x1;
    float _ty = _y1;
    if(Global::setting.stage_antialising) {
        for(int i = 1; i <= 4; i ++) {
            float _pos = float(i) / 4.0;
            Draw::line(_tx, _ty, _x1 + _pos * _w, _y1 + _pos * _w * lerp(_t1, _t2, _pos), 2.0);
            _tx = _x1 + _pos * _w;
            _ty = _y1 + _pos * _w * lerp(_t1, _t2, _pos);
        }
    } else {
        Draw::line(_x1, _y1, _x1 + _w / 2.0, _y1 + _w * (_t1 + _t2) / 4.0, 2.0);
        Draw::line(_x1 + _w / 2.0, _y1 + _w * (_t1 + _t2) / 4.0, _x2, _y2, 2.0);
    }
    Draw::circle(_x1, _y1, 2);
    Draw::circle(_x2, _y2, 2);
    return _t2;
}

void Window_editor_timeline::paintEvent(QPaintEvent *)
{
    float ss = Global::setting.editor_scale;

    drawMain(QRectF(rect().left() + 128 * ss, rect().top() - 2, rect().width() - 128 * ss, rect().height() - 48 * ss));

    Draw::begin(this);
    setPenColor_false();
    Draw::setAntialising(Global::setting.stage_antialising);

    drawToolBox(QRectF(rect().left(), rect().top(), 128 * ss, rect().height()));
    drawScale(QRectF(rect().left() + 128 * ss, rect().height() - 48 * ss + 2, rect().width() - 128 * ss, 48 * ss));

    if(mouse_down == 4) drawMenu();

    Draw::end();
}

void drawBossTime(int _time1, int _time2, float _scale, float buff_x,
                  float _w, float _l, float _r, float _t, float _b, float ss) {

    float _pos1 = _time1 * _scale - buff_x + 256 + 64;
    float _pos2 = _time2 * _scale - buff_x + 256 + 64;

    if(_pos2 < 0.0 || _w + 512.0 < _pos1) return;

    setPenColor_false();
    Draw::painter->setBrush(Sprite(ui_ban_area));
    Draw::rect(qMax(0.0f, _pos1), _t, qMin(_pos2, _w + 512.0f), _b);

}

void drawEvent(QList<DB_STAGE_EVENT>::iterator _event, float _scale, float buff_x,
               float _w, float _l, float _r, float _t, float _b, float ss, bool _selected) {

    int _time = _event->time;

    float _pos = _time * _scale - buff_x + 256 + 64;
    if(_pos < 0.0 || _w + 512.0 < _pos) return;

    if(_scale > 3) {
        setPenColor_false();
        if(_selected) {
            setBrushColor_c(c_theme);
            Draw::triangle(_pos - 8 * ss + _scale / 2 - 0.5, _t - 4 * ss,
                           _pos + 8 * ss + _scale / 2 - 0.5, _t - 4 * ss,
                           _pos + _scale / 2 - 0.5, _t + 8 * ss);
            Draw::triangle(_pos - 8 * ss + _scale / 2 - 0.5, _b + 4 * ss,
                           _pos + 8 * ss + _scale / 2 - 0.5, _b + 4 * ss,
                           _pos + _scale / 2 - 0.5, _b - 8 * ss);
            Draw::rect(_pos, _t + 12 * ss, _pos + _scale - 1, _b - 12 * ss);
        } else {
            if(_event->type == 15) {
                setPenColor_ca(c_theme, 255);
                Draw::line(_pos + 1, _t + 20 * ss, _pos + 1, _b, 2.0);

                Draw::line(_pos + 1 - 7 * ss, _t + 8 * ss, _pos + 1 + 7 * ss, _t + 8 * ss, 2.0);
                Draw::line(_pos + 1 - 4 * ss, _t + 8 * ss - 6 * ss, _pos + 1 + 4 * ss, _t + 8 * ss + 6 * ss, 2.0);
                Draw::line(_pos + 1 - 4 * ss, _t + 8 * ss + 6 * ss, _pos + 1 + 4 * ss, _t + 8 * ss - 6 * ss, 2.0);

            } else {

                setBrushColor_ca(c_theme, 128);
                Draw::rect(_pos, _t, _pos + _scale - 1, _b);
                setPenColor_ca(c_theme, 128);
                if(_event->type == 8) {
                    Draw::line(_pos + _scale - 1, _t, _pos + _scale + 16 * ss, _t, 2.0);
                    Draw::line(_pos + _scale - 1, _t + 16 * ss, _pos + _scale + 16 * ss, _t, 2.0);
                } else if(_event->type == 9) {
                    Draw::line(_pos, _t, _pos - 16 * ss, _t, 2.0);
                    Draw::line(_pos, _t + 16 * ss, _pos - 16 * ss, _t, 2.0);
                }
            }
        }
    } else {
        setPenColor_false();
        if(_selected) {
            setBrushColor_c(c_theme);
            Draw::triangle(_pos - 8 * ss, _t - 4 * ss, _pos + 8 * ss, _t - 4 * ss, _pos, _t + 8 * ss);
            Draw::triangle(_pos - 8 * ss, _b + 4 * ss, _pos + 8 * ss, _b + 4 * ss, _pos, _b - 8 * ss);
            setPenColor_c(c_theme);
            Draw::line(_pos + 1, _t + 12 * ss, _pos + 1, _b - 12 * ss, 2.0);
        } else {
            if(_event->type == 15) {
                setPenColor_ca(c_theme, 255);
                Draw::line(_pos + 1, _t + 20 * ss, _pos + 1, _b, 2.0);

                Draw::line(_pos + 1 - 7 * ss, _t + 8 * ss, _pos + 1 + 7 * ss, _t + 8 * ss, 2.0);
                Draw::line(_pos + 1 - 4 * ss, _t + 8 * ss - 6 * ss, _pos + 1 + 4 * ss, _t + 8 * ss + 6 * ss, 2.0);
                Draw::line(_pos + 1 - 4 * ss, _t + 8 * ss + 6 * ss, _pos + 1 + 4 * ss, _t + 8 * ss - 6 * ss, 2.0);
            } else {
                setPenColor_ca(c_theme, 128);
                Draw::line(_pos + 1, _t, _pos + 1, _b, 2.0);
                if(_event->type == 8) {
                    Draw::line(_pos + 1, _t, _pos + 1 + 16 * ss, _t, 2.0);
                    Draw::line(_pos + 1, _t + 16 * ss, _pos + 1 + 16 * ss, _t, 2.0);
                } else if(_event->type == 9) {
                    Draw::line(_pos + 1, _t, _pos + 1 - 16 * ss, _t, 2.0);
                    Draw::line(_pos + 1, _t + 16 * ss, _pos + 1 - 16 * ss, _t, 2.0);
                }
            }
        }
    }
}

void Window_editor_timeline::drawMain(QRectF _rect)
{
    float ss = Global::setting.editor_scale;

    if(pixmap_timeline_final.width() != int(_rect.width() + 128 * ss) ||
       pixmap_timeline_final.height() != int(_rect.height())) {
        pixmap_timeline_final = QPixmap(int(_rect.width() + 128 * ss), int(_rect.height()));
    }
    if(pixmap_timeline.width() != int(_rect.width()) + 512 ||
       pixmap_timeline.height() != int(_rect.height())) {
        pixmap_timeline = QPixmap(int(_rect.width()) + 512, int(_rect.height()));
        buff_update = 1;
    }


    float _l = _rect.left();
    float _r = _rect.right();
    float _t = _rect.top();
    float _b = _rect.bottom();
    float _w = _rect.width();

    float _scale = (_w - 128) / ((view_right - view_left) / 100.0 * view_max);

    if(abs(buff_x - view_left / 100.0 * view_max * _scale) > 224) buff_update = 1;


    if(buff_update) {
        buff_update = 0;

        buff_x = view_left / 100.0 * view_max * _scale;

        pixmap_timeline.fill(Color(c_backgroundMain));
        Draw::begin(&pixmap_timeline);
        Draw::setAntialising(Global::setting.stage_antialising);

        if(Window_editor_main::id1 >= 1 && Window_editor_main::id2 != -1) {

            Draw::setTextDefault();
            Draw::setTextSize(8 * ss);

            float mid_y = (_b - _t) / 2.0;
            setPenColor_ca(c_symbol, 255);

            Draw::line(qMax(0.0f, -buff_x + 256 + 64), mid_y, qMin(_r + 512, view_max * _scale - buff_x + 256 + 64), mid_y, 4 * ss);

            int _step = qMax(30, int(floor(100.0 / _scale / 60)) * 60);
            bool _one = true;
            for(int i = 0; i <= 36000; i += _step) {
                float _pos = i * _scale - buff_x + 256 + 64;
                if(_pos < 0) continue;
                if(_pos > _r + 512) break;
                if(_one) Draw::line(_pos, mid_y - 32 * ss, _pos, mid_y + 32 * ss, 1.0);
                else     Draw::line(_pos, mid_y - 16 * ss, _pos, mid_y + 16 * ss, 1.0);

                Draw::text(_pos + 4 * ss, mid_y + 2 * ss,
                           QString::number(floor(i / 60)) + ":" + QString::number(i % 60),
                           Qt::AlignLeft | Qt::AlignTop);
                _one = !_one;
            }


            if(Window_editor_main::id2 < db.stage[Window_editor_main::id1 - 1].size()) {
                QList<DB_STAGE_EVENT> *_list = &db.stage[Window_editor_main::id1 - 1][Window_editor_main::id2].events;

                QList<_pair> _tmp_list;

                for(auto i = _list->begin(); i != _list->end(); i ++) {
                    if(i->type == 8) _tmp_list.append(_pair(0, i->time));
                    if(i->type == 9) _tmp_list.append(_pair(1, i->time));
                }

                eventBossTime.clear();
                for(int i = 0; i < _tmp_list.size(); i ++) {
                    auto tmp1 = _tmp_list[i];
                    if(tmp1.a != 0) continue;
                    int tmp3 = 100000000;
                    for(int j = 0; j < _tmp_list.size(); j ++) {
                        if(i == j) continue;
                        auto tmp2 = _tmp_list[j];
                        if(tmp2.a != 1) continue;
                        if(tmp1.b < tmp2.b && tmp2.b - tmp1.b < tmp3 - tmp1.b) {
                            tmp3 = tmp2.b;
                        }
                    }
                    eventBossTime.append(_pair(tmp1.b, tmp3));
                }

                for(auto i = eventBossTime.begin(); i != eventBossTime.end(); i ++) {
                    drawBossTime(i->a, i->b, _scale, buff_x, _w,
                                 _l, _r, _t + 12 * ss, _b - 12 * ss, ss);

                }

                for(auto i = _list->begin(); i != _list->end(); i ++)
                    drawEvent(i, _scale, buff_x, _w,
                              _l, _r, _t + 12 * ss, _b - 12 * ss, ss, i->id == Window_editor_main::id3);

            }
        }

        Draw::end();
    }

    pixmap_timeline_final.fill(Color(c_backgroundMain));
    Draw::begin(&pixmap_timeline_final);
    Draw::setAntialising(Global::setting.stage_antialising);


    if(Window_editor_main::id1 < 1) {
        setPenColor_c(c_theme);
        Draw::setTextSize(20 * ss);
        Draw::text(_l + 16 * ss, _t + 16 * ss, "选择关卡进行编辑...", Qt::AlignLeft | Qt::AlignTop);
    } else {

        Draw::painter->drawTiledPixmap(_l, 0, pixmap_timeline.width(),
                                       _b - _t, pixmap_timeline,
                                       256 - (buff_x - view_left / 100.0 * view_max * _scale), 0);

        setPenColor_c(c_theme);
        setBrushColor_false();
        if(mouse_down == 4) {
            float _pos = int(rbt) * _scale - view_left / 100.0 * view_max * _scale + 64 + _l;
            float __s = qMax(4.0f, _scale);
            Draw::roundRect(_pos , _t + 8 * ss, _pos + __s, _b - 8 * ss, 2, 2 * ss);
        } else if(mouse_down == 0 && isActiveWindow() && underMouse() && my < rect().bottom() - 48 * ss) {

            float _scale = (_w - 128) / ((view_right - view_left) / 100.0 * view_max);
            int __t = ((mx - _l - 64) + view_left / 100.0 * view_max * _scale) / _scale;
            if(__t >= 0 && __t < view_max) {
                float __s = qMax(4.0f, _scale);
                float _pos = __t * _scale - view_left / 100.0 * view_max * _scale + 64 + _l;
                Draw::roundRect(_pos, _t + 8 * ss, _pos + __s, _b - 8 * ss, 2, 2 * ss);
                Draw::setTextSize(10 * ss);
                Draw::text(_pos + 8 * ss + __s, _t + 8 * ss,
                           QString::number(floor(__t / 60)) + ":" + QString::number(__t % 60),
                           Qt::AlignLeft | Qt::AlignTop);
            }
        }

        setPenColor_false();
        QLinearGradient ling;
        ling.setColorAt(0, ColorAlpha(c_backgroundMain, 255));
        ling.setColorAt(0.0625, ColorAlpha(c_backgroundMain, 255));
        ling.setColorAt(1, ColorAlpha(c_backgroundMain, 0));

        ling.setStart(_r, 0);
        ling.setFinalStop(_r - 64, 0);
        Draw::painter->setBrush(ling);
        Draw::painter->drawRect(_r - 64, 0, 64, _b);

        ling.setStart(_l, 0);
        ling.setFinalStop(_l + 64, 0);
        Draw::painter->setBrush(ling);
        Draw::painter->drawRect(_l, 0, 64, _b);

    }

    Draw::end();

    Draw::begin(this);
    Draw::setAntialising(Global::setting.stage_antialising);

    setPenColor_false();
    Draw::painter->setBrush(pixmap_timeline_final);
    Draw::roundRect(_rect.left() + 4, _rect.top() + 2, _rect.right() - 4, _rect.bottom() - 2, 6);

    Draw::end();
}

void Window_editor_timeline::drawToolBox(QRectF _rect)
{

    float ss = Global::setting.editor_scale;

    setPenColor_false();
    setBrushColor_c(c_backgroundMain);
    Draw::roundRect(_rect.left() + 4, _rect.top(), _rect.right() - 4, _rect.bottom(), 6);

    float mid_x = _rect.left() + 96 * ss;
    float top = _rect.top() + 18 * ss;
    float mid_y = top + 18 * ss;

    setPenColor_c(c_theme);

    Draw::setTextDefault();
    Draw::setTextSize(12 * ss);

    if(alpha_toolBoxSelected[0] > 0.0) { // arrow
        setPenColor_false();
        setBrushColor_ca(c_theme, 255.0 * alpha_toolBoxSelected[0]);
        Draw::circle(mid_x, mid_y, 20 * ss);
        setPenColor_m(c_theme, c_backgroundMain, alpha_toolBoxSelected[0]);
        Draw::painter->translate(mid_x, mid_y);
        Draw::painter->scale(ss / 2.0, ss / 2.0);
        Draw::lines(poly0, 7, 3);
        Draw::painter->resetTransform();
    } else {
        setPenColor_m(c_symbol, c_theme, alpha_toolBox[0]);
        Draw::painter->translate(mid_x, mid_y);
        Draw::painter->scale(ss / 2.0, ss / 2.0);
        Draw::lines(poly0, 7, 3);
        Draw::painter->resetTransform();
    }
    setPenColor_c(c_theme);
    Draw::text(mid_x - 28 * ss, mid_y, "选择", Qt::AlignRight | Qt::AlignVCenter);

    mid_y += 42 * ss;
    if(alpha_toolBoxSelected[1] > 0.0) { // select
        setPenColor_false();
        setBrushColor_ca(c_theme, 255.0 * alpha_toolBoxSelected[1]);
        Draw::circle(mid_x, mid_y, 20 * ss);
        setPenColor_m(c_theme, c_backgroundMain, alpha_toolBoxSelected[1]);
        Draw::painter->translate(mid_x, mid_y);
        Draw::painter->scale(ss / 2.0, ss / 2.0);
        Draw::lines(poly3, 12, 3);
        Draw::painter->resetTransform();
    } else {
        setPenColor_m(c_symbol, c_theme, alpha_toolBox[1]);
        Draw::painter->translate(mid_x, mid_y);
        Draw::painter->scale(ss / 2.0, ss / 2.0);
        Draw::lines(poly3, 12, 3);
        Draw::painter->resetTransform();
    }
    setPenColor_c(c_theme);
    Draw::text(mid_x - 28 * ss, mid_y, "框选", Qt::AlignRight | Qt::AlignVCenter);

    mid_y += 42 * ss;
    if(alpha_toolBoxSelected[2] > 0.0) { // move
        setPenColor_false();
        setBrushColor_ca(c_theme, 255.0 * alpha_toolBoxSelected[2]);
        Draw::circle(mid_x, mid_y, 20 * ss);
        setPenColor_m(c_theme, c_backgroundMain, alpha_toolBoxSelected[2]);
        Draw::painter->translate(mid_x, mid_y);
        Draw::painter->scale(ss / 2.0, ss / 2.0);
        Draw::lines(poly1, 10, 3);
        Draw::painter->resetTransform();
    } else {
        setPenColor_m(c_symbol, c_theme, alpha_toolBox[2]);
        Draw::painter->translate(mid_x, mid_y);
        Draw::painter->scale(ss / 2.0, ss / 2.0);
        Draw::lines(poly1, 10, 3);
        Draw::painter->resetTransform();
    }
    setPenColor_c(c_theme);
    Draw::text(mid_x - 28 * ss, mid_y, "移动", Qt::AlignRight | Qt::AlignVCenter);



    mid_y += 42 * ss;
    if(alpha_toolBoxSelected[3] > 0.0) { // brush
        setPenColor_false();
        setBrushColor_ca(c_theme, 255.0 * alpha_toolBoxSelected[3]);
        Draw::circle(mid_x, mid_y, 20 * ss);
        setPenColor_m(c_theme, c_backgroundMain, alpha_toolBoxSelected[3]);
        Draw::painter->translate(mid_x, mid_y);
        Draw::painter->scale(ss / 2.0, ss / 2.0);
        Draw::lines(poly4, 12, 3);
        Draw::painter->resetTransform();
    } else {
        setPenColor_m(c_symbol, c_theme, alpha_toolBox[3]);
        Draw::painter->translate(mid_x, mid_y);
        Draw::painter->scale(ss / 2.0, ss / 2.0);
        Draw::lines(poly4, 12, 3);
        Draw::painter->resetTransform();
    }
    setPenColor_c(c_theme);
    Draw::text(mid_x - 28 * ss, mid_y, "刷子", Qt::AlignRight | Qt::AlignVCenter);
}

void Window_editor_timeline::drawScale(QRectF _rect)
{
    setPenColor_false();
    setBrushColor_c(c_backgroundMain);
    Draw::roundRect(_rect.left() + 4, _rect.top() + 2, _rect.right() - 4, _rect.bottom() - 2, 6);

    float ss = Global::setting.editor_scale;
    float _l = _rect.left() + 24 * ss;
    float _r = _rect.right() - 24 * ss;
    float _mid_y = _rect.bottom() - 24 * ss;
    float _w = _r - _l;

    setPenColor_c(c_theme);
    setBrushColor_c(c_backgroundMain);
    Draw::circle(_l + _w * view_left / 100.0, _mid_y, 10 * ss, 2 * ss);
    Draw::circle(_l + _w * view_right / 100.0, _mid_y, 10 * ss, 2 * ss);

    setPenColor_false();
    setBrushColor_c(c_symbol);
    Draw::rect(_l, _mid_y - 4 * ss, _r, _mid_y + 4 * ss);
    Draw::circle(_l, _mid_y, 4 * ss);
    Draw::circle(_r, _mid_y, 4 * ss);


    setPenColor_false();
    setBrushColor_c(c_theme);
    Draw::rect(_l + _w * view_left / 100.0, _mid_y - 4 * ss, _l + _w * view_right / 100.0, _mid_y + 4 * ss);

    setPenColor_c(c_theme);
    setBrushColor_c(c_backgroundMain);
    Draw::circle(_l + _w * view_left / 100.0, _mid_y, 10 * ss, 2 * ss);
    Draw::circle( _l + _w * view_right / 100.0, _mid_y, 10 * ss, 2 * ss);

    setPenColor_false();
    setBrushColor_c(c_theme);
    Draw::circle(_l + _w * view_left / 100.0, _mid_y, 6 * ss);
    Draw::circle( _l + _w * view_right / 100.0, _mid_y, 6 * ss);

}

void Window_editor_timeline::drawMenu()
{
    float ss = Global::setting.editor_scale;
    setPenColor_c(c_theme);
    setBrushColor_c(c_backgroundMain);
    Draw::roundRect(rbx - 8 * ss, rby, rbx + 168 * ss, rby + 64 * ss, 4, 2 * ss);
    setPenColor_c(c_symbol);
    Draw::line(rbx + 4 * ss, rby + 32 * ss, rbx + 154 * ss, rby + 32 * ss, 2 * ss);
    Draw::setTextSize(12 * ss);
    if(rbi == -1) {
        setPenColor_c(c_textMain);
        Draw::text(rbx + 80 * ss, rby + 16 * ss, "在" + QString::number(floor(rbt / 60))
                   + ":" + QString::number(int(rbt) % 60) + "插入", Qt::AlignCenter);
        setPenColor_ca(c_textMain, 128);
        Draw::text(rbx + 80 * ss, rby + 48 * ss, "删除选中事件", Qt::AlignCenter);
    } else {
        setPenColor_c(c_textMain);
        Draw::text(rbx + 80 * ss, rby + 16 * ss, "在此后插入", Qt::AlignCenter);
        setPenColor_c(c_textMain);
        Draw::text(rbx + 80 * ss, rby + 48 * ss, "删除选中事件", Qt::AlignCenter);

    }
}

void Window_editor_timeline::insertEvent(int _time)
{
    mouse_down = 0;
    QList<DB_STAGE_EVENT> *_events = &db.stage[Window_editor_main::id1 - 1][Window_editor_main::id2].events;
    for(int i = 0; i < _events->size(); i ++) {
        if(_events->at(i).time == _time) {
            Message("此处已有事件");
            return;
        }
    }
    window_insertEvent = new Window_editor_timeline_insert(&db, _time, Window_editor_main::id1 - 1, Window_editor_main::id2);
    window_insertEvent->setWindowModality(Qt::ApplicationModal);
    window_insertEvent->setAttribute(Qt::WA_DeleteOnClose);
    connect(window_insertEvent, SIGNAL(closed()), this, SLOT(insertEventFinished()));
    window_insertEvent->show();
}

void Window_editor_timeline::insertEventFinished()
{

    emit requestUpdate(3);
    buff_update = 1;
}

void Window_editor_timeline::deleteEvent(int _index)
{
    db.stage[Window_editor_main::id1 - 1][Window_editor_main::id2].events.removeAt(_index);

    Global::databaseUpdate(db);
    emit requestUpdate(3);
    buff_update = 1;
}
























