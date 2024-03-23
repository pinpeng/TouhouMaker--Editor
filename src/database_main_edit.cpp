#include "database_main.h"

#include <QDir>
#include <QLabel>
#include "global.h"
#include "database.h"

#include "window_editor_stage.h"
#include "window_editor_main.h"
#include "window_find.h"

#include "window_editor_menubar_text.h"

void DB_STAGE_EVENT::init(Database *db)
{
    data["enable"] = 1;

    switch (type) {
    case THMK_EVENT_TYPE::SET_BACKGROUND: {
        for(int i = 0; i < 4; i ++) {
            QString tmp = "background" + QString::number(i);
            data[tmp] = -1;
            data[tmp + "direction"] = 0;
            data[tmp + "speed"] = 0;
            data[tmp + "slope"] = 0;
            data[tmp + "repeat"] = 0;
        }
        data["fog_alpha"] = 100;
        data["fog_r"] = 0;
        data["fog_g"] = 0;
        data["fog_b"] = 0;

    } break;

    case THMK_EVENT_TYPE::SET_BGM: {
        data["bgm"] = -1;
    } break;

    case THMK_EVENT_TYPE::PLAY_SE: {
        data["se"] = -1;
        data["volume"] = 100;
        data["pitch"] = 100;
    } break;

    case THMK_EVENT_TYPE::PLAY_EFFECT: {
        data["effect"] = -1;
    } break;

    case THMK_EVENT_TYPE::CREATE_ENEMY: //"即刻生成小怪";
    case THMK_EVENT_TYPE::CREATE_ENEMY_TIME: {//"生成小怪队列";
        data["number"] = 1;
        data["enemy"] = -1;
        data["type"] = 0;
        data["x0"] = 0;
        data["y0"] = 0;
        data["dir"] = 0;
        data["step"] = 128;
        data["radius"] = 0;
        data["angle"] = 30;
        data["spd"] = 4;

        if(type == THMK_EVENT_TYPE::CREATE_ENEMY_TIME) data["time"] = 1;

        data_str["code"] = "";
    } break;

    case THMK_EVENT_TYPE::PLAY_STORY: { //"播放剧情";
        data["size"] = 0;
    } break;
    case THMK_EVENT_TYPE::PLAY_STORY_TIME: { //"播放计时剧情";
        data["size"] = 0;
    } break;
    case THMK_EVENT_TYPE::BOSS_START: //"BOSS战斗开始";
        data["boss"] = -1;
        data["hp"] = 100;
        break;
    case THMK_EVENT_TYPE::BOSS_END: //"BOSS战斗结束";
        break;
    case THMK_EVENT_TYPE::BOSS_BULLET://"BOSS发射弹幕";
    case THMK_EVENT_TYPE::BOSS_SPELL_CARD: {  //"BOSS发射符卡";
        if(type == 11) data["name"] = db->text_append("新建符卡");
        data["timetype"] = 0;
        data["t1"] = 0;
        data["t2"] = 0;
        data["condition"] = 0;
        data_str["condition"] = "";
        data["size"] = 1;
        QString str = "0_";
        data[str + "type1"] = 0;
        data[str + "type1time"] = 0;
        data[str + "type2"] = 0;
        data[str + "type2time"] = 1;
        data[str + "size"] = 0;
        data_str[str + "init"] = "val1 = 0\nval2 = 0";
        data_str[str + "step"] = "val1 = val1 + 1\nval2 = val2 + val1";
    } break;
    case THMK_EVENT_TYPE::CLS: //"清理场上弹幕和小怪";
        break;
    case THMK_EVENT_TYPE::GOTO: { //"跳转至";
        data_str["condition"] = "true";
        data["t1"] = 0;
        data["t2"] = 0;
    } break;
    case THMK_EVENT_TYPE::STAGE_CHANGE: { // "结束本关卡";
        data_str["condition"] = "true";
        data["next"] = 0;
    } break;
        break;
    case THMK_EVENT_TYPE::POINT: // "断点";
        break;

    default:
        break;
    }

}

QStringList DB_STAGE_EVENT::getDescribe(Database *db)
{
    QStringList _text;
    _text << QString::number(floor(time / 60)) + ":" + QString::number(time % 60);

    switch (type) {
    case THMK_EVENT_TYPE::SET_BACKGROUND: _text << "设置背景图像";
        break;

    case THMK_EVENT_TYPE::SET_BGM: {
        auto tmp = db->audio[0].find(data["bgm"]);
        if(tmp == db->audio[0].end()) {
            _text << "设置背景音乐为关闭";
        } else {
            _text << "设置背景音乐为<" + tmp.value().name + ">";
        }
    } break;

    case THMK_EVENT_TYPE::PLAY_SE: {
        auto tmp = db->audio[1].find(data["se"]);
        if(tmp == db->audio[1].end()) {
            _text << "播放音效<无音效>";
        } else {
            _text << "播放音效<" + tmp.value().name + ">";
        }
    } break;

    case THMK_EVENT_TYPE::PLAY_EFFECT: {
        auto tmp = db->effect[1].find(data["effect"]);
        if(tmp == db->effect[1].end()) {
            _text << "播放特效<无特效>";
        } else {
            _text << "播放特效<" + tmp.value().name + ">";
        }
    } break;

    case THMK_EVENT_TYPE::CREATE_ENEMY: {
        _text << "即刻生成" + QString::number(data["number"]) + "个小怪";
    } break;

    case THMK_EVENT_TYPE::CREATE_ENEMY_TIME: _text << "逐渐生成" + QString::number(data["number"]) + "个小怪";
        break;
    case THMK_EVENT_TYPE::PLAY_STORY: _text << "播放剧情";
        break;
    case THMK_EVENT_TYPE::PLAY_STORY_TIME: _text << "播放计时剧情";
        break;
    case THMK_EVENT_TYPE::BOSS_START: {
        QString _text1 = "<未选择>";
        auto tmp = db->boss.find(data["boss"]);
        if(tmp != db->boss.end()) {
            _text1 = "<" + db->getText(tmp.value().name, 0) + ">";
        }
        _text << "开始与BOSS" + _text1 + "的战斗";
    } break;
    case THMK_EVENT_TYPE::BOSS_END: _text << "BOSS战斗结束";
        break;
    case THMK_EVENT_TYPE::BOSS_BULLET: _text << "BOSS发射弹幕";
        break;
    case THMK_EVENT_TYPE::BOSS_SPELL_CARD: _text << "BOSS发射符卡";
        break;
    case THMK_EVENT_TYPE::CLS: _text << "清理场上弹幕和小怪";
        break;
    case THMK_EVENT_TYPE::GOTO: _text << "跳转至" + QString::number(floor(data["t1"])) + ":" + QString::number(floor(data["t2"]));
        break;
    case THMK_EVENT_TYPE::STAGE_CHANGE: {
        QStringList _list2 = {"进入下一关", "进入上一关", "结束游戏"};
        _text << _list2[data["next"]];
    }

        break;
    case THMK_EVENT_TYPE::POINT: _text << "断点";
        break;

    default:
        _text << "<Undefined Event>";
        break;
    }

    return _text;

}

void DB_STAGE_EVENT::renderCode(Window_editor_stage *window, Database *db, QRectF _rect, float *_line, float ss)
{
    setPenColor_c(c_theme);
    Draw::text(_rect.left() + 24 * ss, _rect.top() - 4 * ss,
               data["enable"]? "当前事件：启用": "当前事件：禁用",
               Qt::AlignLeft | Qt::AlignVCenter);

    if(type != 0) {

        for(int i = 0; i < 8; i ++) {
            if(window->label[i]->x() < 9000) {
                window->label[i]->setPixmap(QPixmap());
                window->label[i]->setMovie(nullptr);
                window->label[i]->setGeometry(10000, 10000, 1, 1);
            }
        }

    }

    switch (type) {
    case THMK_EVENT_TYPE::SET_BACKGROUND: {// 设置背景图像为
        float _r = _rect.right() - 24 * ss;
        float _l = _rect.left() + 24 * ss;
        float _t = _rect.top() + 36 * ss;

        setPenColor_c(c_textMain);

        Draw::text(_l, _t, "背景雾强度为" + QString::number(data["fog_alpha"]) + "%，颜色RGB("
                + QString::number(data["fog_r"]) + ","
                + QString::number(data["fog_g"]) + ","
                + QString::number(data["fog_b"]) + ")",
                   Qt::AlignLeft | Qt::AlignVCenter);

        setPenColor_false();
        QLinearGradient ling;
        ling.setColorAt(0, QColor(data["fog_r"], data["fog_g"], data["fog_b"], 0));
        ling.setColorAt(1, QColor(data["fog_r"], data["fog_g"], data["fog_b"], 128.0 * data["fog_alpha"] / 100.0));

        ling.setStart(_r - 384 * ss, 0);
        ling.setFinalStop(_r, 0);

        Draw::painter->setBrush(ling);
        Draw::painter->drawRect(_r - 384 * ss, _t - 16 * ss, 384 * ss, 32 * ss);

        for(int i = 0; i < 4; i ++) {
            _t = _rect.top() + 56 * ss + 120 * i * ss;
            setPenColor_c(c_theme);
            Draw::line(_l, _t, _r, _t, 2 * ss);
            QString tmp = "background" + QString::number(i);
            QString _text[3];
            _text[0] = "图层" + QString::number(i + 1) + "--";
            _text[1] = "运动方向" + QString::number(data[tmp + "direction"]) +
                    "度，速度" + QString::number(data[tmp + "speed"]) + "像素每帧";
            _text[2] = /*"坡度" + QString::number(data[tmp + "slope"]) +
                    "度，" + */ (data[tmp + "repeat"]? "重复": "不重复");
            int _index = data[tmp];
            if(db->image[0].find(_index) == db->image[0].end()) {
                _text[0] += "未选择图片";
                setPenColor_c(c_theme);
                Draw::line(_r - 60 * ss - 48 * ss, _t + 60 * ss - 48 * ss,
                           _r - 60 * ss + 48 * ss, _t + 60 * ss + 48 * ss, 2 * ss);
                Draw::line(_r - 60 * ss - 48 * ss, _t + 60 * ss + 48 * ss,
                           _r - 60 * ss + 48 * ss, _t + 60 * ss - 48 * ss, 2 * ss);
                window->label[i]->setPixmap(QPixmap());
                window->label[i]->setMovie(nullptr);
                window->label[i]->setGeometry(10000, 10000, 1, 1);
            } else {
                auto _file = &db->image[0][_index];
                _text[0] += "背景为<" + _file->name + ">";
                auto j = Global::sprite_buffer.find(QString::number(_file->__id) + "_" + QString::number(_file->editTimer));
                if(j != Global::sprite_buffer.end()) {
                    window->label[i]->setGeometry(_r - 60 * ss - 48 * ss, _t + 60 * ss - 48 * ss, 96 * ss, 96 * ss);
                    if(_file->state == 1) {
                        window->label[i]->setPixmap(j.value().png);
                    }
                    if(_file->state == 2) {
                        window->label[i]->setMovie(j.value().gif);
                        j.value().gif->start();
                    }
                    /*
                    if(pixmap[i].isNull()) {
                        pixmap[i] = QPixmap(basePath).scaled(96 * ss, 96 * ss);
                    }
                    Draw::sprite(pixmap[i], _r - 60 * ss - 48 * ss, _t + 60 * ss - 48 * ss);*/
                } else {
                    setPenColor_c(c_theme);
                    Draw::line(_r - 60 * ss - 48 * ss, _t + 60 * ss - 48 * ss,
                               _r - 60 * ss + 48 * ss, _t + 60 * ss + 48 * ss, 2 * ss);
                    Draw::line(_r - 60 * ss - 48 * ss, _t + 60 * ss + 48 * ss,
                               _r - 60 * ss + 48 * ss, _t + 60 * ss - 48 * ss, 2 * ss);
                    window->label[i]->setPixmap(QPixmap());
                    window->label[i]->setMovie(nullptr);
                    window->label[i]->setGeometry(10000, 10000, 1, 1);
                }
            }
            setPenColor_c(c_theme);
            setBrushColor_false();
            Draw::rect(_r - 60 * ss - 48 * ss, _t + 60 * ss - 48 * ss,
                       _r - 60 * ss + 48 * ss, _t + 60 * ss + 48 * ss, 2 * ss);
            setPenColor_c(c_textMain);
            _t += 20 * ss;
            for(int j = 0; j < 3; j ++) Draw::text(_l, _t + 40 * ss * j, _text[j], Qt::AlignLeft | Qt::AlignVCenter);
        }
    } break;

    case THMK_EVENT_TYPE::SET_BGM: {// 设置背景音乐为
        setPenColor_c(c_textMain);
        QString _text = "没有选择音乐";
        auto tmp = db->audio[0].find(data["bgm"]);
        if(tmp != db->audio[0].end()) {
            _text = "设置音乐为<" + tmp.value().name + ">";
        }
        Draw::text(_rect.left() + 24 * ss, _rect.top() + 36 * ss, _text, Qt::AlignLeft | Qt::AlignVCenter);
    } break;

    case THMK_EVENT_TYPE::PLAY_SE: {// 播放音效
        setPenColor_c(c_textMain);
        QString _text = "没有选择音效";
        auto tmp = db->audio[1].find(data["se"]);
        if(tmp != db->audio[1].end()) {
            _text = "播放音效<" + db->audio[1][data["se"]].name + ">";
        }
        Draw::text(_rect.left() + 24 * ss, _rect.top() + 36 * ss, _text, Qt::AlignLeft | Qt::AlignVCenter);
        _text = "音量" + QString::number(data["volume"]) +
                "%，音高" + QString::number(data["pitch"]) + "%";
        Draw::text(_rect.left() + 24 * ss, _rect.top() + 76 * ss, _text, Qt::AlignLeft | Qt::AlignVCenter);
    } break;

    case THMK_EVENT_TYPE::PLAY_EFFECT: {// 播放特效
        setPenColor_c(c_textMain);
        QString _text = "没有选择特效";
        auto tmp = db->effect[1].find(data["effect"]);
        if(tmp != db->effect[1].end()) {
            _text = "播放特效<" + tmp.value().name + ">";
        }
        Draw::text(_rect.left() + 24 * ss, _rect.top() + 36 * ss, _text, Qt::AlignLeft | Qt::AlignVCenter);
    } break;

    case THMK_EVENT_TYPE::CREATE_ENEMY:// 即刻生成小怪
    case THMK_EVENT_TYPE::CREATE_ENEMY_TIME: {// 生成小怪队列
        setPenColor_c(c_textMain);
        QString _text = "<未选择>";
        auto tmp = db->enemy.find(data["enemy"]);
        if(tmp != db->enemy.end()) {
            _text = "<" + tmp.value().name + ">";
        }
        if(type == 5) _text += "，间隔" + QString::number(data["time"]) + "分秒";
        if(data["type"] == 0) {
            Draw::text(_rect.left() + 24 * ss, _rect.top() + (36 + 40 * 0) * ss,
                       "直线生成" + QString::number(data["number"]) + "个" + _text, Qt::AlignLeft | Qt::AlignVCenter);
            Draw::text(_rect.left() + 24 * ss, _rect.top() + (36 + 40 * 1) * ss,
                       "直线起点为(" + QString::number(data["x0"]) + "," + QString::number(data["y0"]) + ")",
                    Qt::AlignLeft | Qt::AlignVCenter);
            Draw::text(_rect.left() + 24 * ss, _rect.top() + (36 + 40 * 2) * ss,
                       "方向为" + QString::number(data["dir"]) + "度，间隔" + QString::number(data["step"]) + "px，初速度" + QString::number(data["spd"]),
                    Qt::AlignLeft | Qt::AlignVCenter);

        } else if(data["type"] == 1) {
            Draw::text(_rect.left() + 24 * ss, _rect.top() + (36 + 40 * 0) * ss,
                       "环状生成" + QString::number(data["number"]) + "个" + _text, Qt::AlignLeft | Qt::AlignVCenter);
            Draw::text(_rect.left() + 24 * ss, _rect.top() + (36 + 40 * 1) * ss,
                       "圆心为(" + QString::number(data["x0"]) + "," + QString::number(data["y0"]) + ")，半径" + QString::number(data["radius"]) + "px",
                    Qt::AlignLeft | Qt::AlignVCenter);
            Draw::text(_rect.left() + 24 * ss, _rect.top() + (36 + 40 * 2) * ss,
                       "初始方向为" + QString::number(data["dir"]) + "度，初速度" + QString::number(data["spd"]),
                    Qt::AlignLeft | Qt::AlignVCenter);

        } else if(data["type"] == 2) {
            Draw::text(_rect.left() + 24 * ss, _rect.top() + (36 + 40 * 0) * ss,
                       "扇形生成" + QString::number(data["number"]) + "个" + _text, Qt::AlignLeft | Qt::AlignVCenter);
            Draw::text(_rect.left() + 24 * ss, _rect.top() + (36 + 40 * 1) * ss,
                       "原点为(" + QString::number(data["x0"]) + "," + QString::number(data["y0"]) + ")，半径" + QString::number(data["radius"]) + "px",
                    Qt::AlignLeft | Qt::AlignVCenter);
            Draw::text(_rect.left() + 24 * ss, _rect.top() + (36 + 40 * 2) * ss,
                       "初始方向为" + QString::number(data["dir"]) + "度，间隔" + QString::number(data["angle"]) + "度，初速度" + QString::number(data["spd"]),
                    Qt::AlignLeft | Qt::AlignVCenter);

        }
        setPenColor_c(c_theme);

        Draw::text(_rect.left() + 24 * ss, _rect.top() + (36 + 40 * 3) * ss,
                "点此设置初始状态...",
                Qt::AlignLeft | Qt::AlignVCenter);

        float _h = _rect.bottom() - _rect.top() - (16 + 40 * 4) * ss - 64 * ss;
        float _w = _rect.width() - 32 * ss;

        setPenColor_c(c_theme);
        setBrushColor_c(c_backgroundMain);

        float meta1 = _w / 5;
        float meta2 = _h / 6;
        float w, h;
        if(meta1 < meta2) {
            w = meta1 * 5;
            h = meta1 * 6;
        } else {
            w = meta2 * 5;
            h = meta2 * 6;
        }

        float _x = _rect.left() + _rect.width() / 2 - w / 2;
        float _y = (_rect.bottom() + _rect.top() + (24 + 40 * 4) * ss - 64 * ss) / 2 - h / 2;

        Draw::rect(_x, _y, _x + w, _y + h, 2.0 * ss);
        Draw::rect(_x + w / 4, _y + h / 4 + h / 2 * 5 / 18, _x + w * 3 / 4, _y + h * 3 / 4 + h / 2 * 5 / 18, 2.0 * ss);

        Draw::line(_x + w / 2, _y, _x + w / 2, _y + h, ss);
        Draw::line(_x, _y + h / 4 + h * 5 / 18, _x + w, _y + h / 4 + h * 5 / 18, ss);

        Draw::setTextSize(6 * ss);
        Draw::text(_x + w / 2 + 4 * ss, _y + h / 4 + h * 5 / 18 + 4 * ss, "(0,0)", Qt::AlignLeft | Qt::AlignTop);

        Draw::text(_x + w * 3 / 4 + 4 * ss, _y + h / 4 + h * 5 / 18 + 4 * ss, "(375,0)", Qt::AlignLeft | Qt::AlignTop);
        Draw::text(_x + w + 4 * ss, _y + h / 4 + h * 5 / 18 + 4 * ss, "(750,0)", Qt::AlignLeft | Qt::AlignTop);

        Draw::text(_x + w / 4 + 4 * ss, _y + h / 4 + h * 5 / 18 + 4 * ss, "(-375,0)", Qt::AlignLeft | Qt::AlignTop);
        Draw::text(_x + 4 * ss, _y + h / 4 + h * 5 / 18 + 4 * ss, "(-750,0)", Qt::AlignLeft | Qt::AlignTop);

        Draw::text(_x + w / 2 + 4 * ss, _y + h / 4 + h / 2 * 5 / 18 + 4 * ss, "(0,-250)", Qt::AlignLeft | Qt::AlignTop);
        Draw::text(_x + w / 2 + 4 * ss, _y + 4 * ss, "(0,-950)", Qt::AlignLeft | Qt::AlignTop);

        Draw::text(_x + w / 2 + 4 * ss, _y + h * 3 / 4 + h / 2 * 5 / 18 + 4 * ss, "(0,650)", Qt::AlignLeft | Qt::AlignTop);
        Draw::text(_x + w / 2 + 4 * ss, _y + h + 4 * ss, "(0,850)", Qt::AlignLeft | Qt::AlignTop);

        if(data["type"] == 0) {
            setPenColor_c(c_symbol);
            float dir = data["dir"] / 180 * 3.14159;
            float x0 = _x + w / 2 + data["x0"] / 1500 * w;
            float y0 = _y + h / 4 + h * 5 / 18 + data["y0"] / 1500 * w;
            float step = data["step"] / 1500 * w;
            Draw::line(x0, y0,
                       x0 + qMax(64.0 * ss, (data["number"] - 1.0) * step) * cos(dir),
                       y0 - qMax(64.0 * ss, (data["number"] - 1.0) * step) * sin(dir), 4 * ss);
            setPenColor_c(c_textMain);
            setBrushColor_c(c_backgroundMain);
            for(int i = 0; i < data["number"]; i ++) {
                float x1 = x0 + step * i * cos(dir);
                float y1 = y0 - step * i * sin(dir);
                if(x1 < _x || x1 > _x + w || y1 < _y || y1 > _y + h) continue;
                Draw::circle(x1, y1, 10 * ss);
                Draw::text(x1, y1 + 0.5, QString::number(i + 1), Qt::AlignCenter);
            }

        } else if(data["type"] == 1) {
            setPenColor_c(c_symbol);
            setBrushColor_false();
            float dir = data["dir"] / 180 * 3.14159;
            float r = data["radius"] / 1500 * w;
            float x0 = _x + w / 2 + data["x0"] / 1500 * w;
            float y0 = _y + h / 4 + h * 5 / 18 + data["y0"] / 1500 * w;

            Draw::circle(x0, y0, r, 4 * ss);
            setPenColor_c(c_textMain);
            setBrushColor_c(c_backgroundMain);
            float _angle = 360 / data["number"];
            for(int i = 0; i < data["number"]; i ++) {
                float x1 = x0 + r * cos(dir + _angle * i / 180 * 3.14159);
                float y1 = y0 - r * sin(dir + _angle * i / 180 * 3.14159);
                if(x1 < _x || x1 > _x + w || y1 < _y || y1 > _y + h) continue;
                Draw::circle(x1, y1, 10 * ss);
                Draw::text(x1, y1 + 0.5, QString::number(i + 1), Qt::AlignCenter);
            }
        } else if(data["type"] == 2) {
            setPenColor_c(c_symbol);
            setBrushColor_false();
            float dir = data["dir"] / 180 * 3.14159;
            float r = data["radius"] / 1500 * w;
            float x0 = _x + w / 2 + data["x0"] / 1500 * w;
            float y0 = _y + h / 4 + h * 5 / 18 + data["y0"] / 1500 * w;
            float _angle = data["angle"];
            float _num = data["number"];
            Draw::pie(x0, y0, r, data["dir"] + _angle * (-_num / 2 + 0.5), data["dir"] + _angle * (_num / 2 - 0.5), 4 * ss);
            setPenColor_c(c_textMain);
            setBrushColor_c(c_backgroundMain);
            for(int i = 0; i < _num; i ++) {
                float x1 = x0 + r * cos(dir + _angle * (i - _num / 2 + 0.5) / 180 * 3.14159);
                float y1 = y0 - r * sin(dir + _angle * (i - _num / 2 + 0.5) / 180 * 3.14159);
                if(x1 < _x || x1 > _x + w || y1 < _y || y1 > _y + h) continue;
                Draw::circle(x1, y1, 10 * ss);
                Draw::text(x1, y1 + 0.5, QString::number(i + 1), Qt::AlignCenter);
            }
        }

    } break;

    case THMK_EVENT_TYPE::PLAY_STORY: { // 播放剧情
        float _r = _rect.right() - 24 * ss;
        float _l = _rect.left() + 24 * ss;
        float _t = _rect.top() + 36 * ss;

        setPenColor_c(c_textMain);

        Draw::text(_l, _t, "共有" + QString::number(data["size"]) + "句对话",
                   Qt::AlignLeft | Qt::AlignVCenter);

        setPenColor_c(c_theme);
        float mid_x = _r - 64 * ss;
        Draw::line(mid_x, _t - 12 * ss, mid_x, _t + 12 * ss, 2 * ss);
        Draw::line(mid_x - 12 * ss, _t, mid_x + 12 * ss, _t, 2 * ss);
        mid_x = _r - 24 * ss;
        Draw::line(mid_x - 12 * ss, _t, mid_x + 12 * ss, _t, 2 * ss);

        _t = _rect.top() + 56 * ss;
        Draw::line(_l - 8, _t, _r + 8, _t, 4 * ss);

        int line_max = _rect.height() / 40 / ss - 2.5;

        int i;
        for(i = qMax(0, int(floor(*_line / 3)) - 1); i < data["size"]; i ++) {
            if(i * 3 - *_line >= line_max) break;
            _t = _rect.top() + 56 * ss + 120 * i * ss - *_line * 40 * ss;

            if(i * 3 - *_line >= 0) {
                setPenColor_c(c_theme);
                Draw::line(_l, _t, _r - 16 * ss, _t, 2 * ss);
            }

            QString _text[3], _list[3] = {"无显示", "非活跃", "活跃"};
            _text[0] = QString::number(i + 1) + "> " + db->getText(data[QString::number(i) + "text"], 0).replace("\n", "\\n");

            int tmp;

            tmp = data[QString::number(i) + "image0"];
            if(db->image[2].find(tmp) != db->image[2].end()) {
                _text[1] = "左边立绘为<" + db->image[2][tmp].name + ">，状态为";
            } else {
                _text[1] = "左边无立绘，状态为";
            }
            _text[1] += _list[int(data[QString::number(i) + "state0"])];

            tmp = data[QString::number(i) + "image1"];
            if(db->image[2].find(tmp) != db->image[2].end()) {
                _text[2] = "右边立绘为<" + db->image[2][tmp].name + ">，状态为";
            } else {
                _text[2] = "右边无立绘，状态为";
            }
            _text[2] += _list[int(data[QString::number(i) + "state1"])];

            setPenColor_c(c_textMain);
            _t += 20 * ss;
            for(int j = 0; j < 3; j ++) {
                if(i * 3 + j - *_line < line_max && i * 3 + j - *_line >= 0) {
                    Draw::text(_l, _t + 40 * ss * j + 2, _text[j], Qt::AlignLeft | Qt::AlignVCenter);
                }
            }
        }

        setPenColor_false();
        setBrushColor_c(c_symbol);
        Draw::rect(_rect.right() - 24 * ss, _rect.top() + 74 * ss, _rect.right() - 16 * ss, _rect.bottom() - 60 * ss);
        Draw::circle(_rect.right() - 20 * ss, _rect.top() + 74 * ss, 4 * ss);
        Draw::circle(_rect.right() - 20 * ss, _rect.bottom() - 60 * ss, 4 * ss);

        float line_real = data["size"] * 3 + 1;
        float _h = (_rect.bottom() - 60 * ss) - (_rect.top() + 74 * ss);
        float pos1 = _rect.top() + 74 * ss + _h * qMin(1.0f, *_line / line_real);
        float pos2 = _rect.top() + 74 * ss + _h * qMin(1.0f, (*_line + line_max) / line_real);

        setBrushColor_c(c_theme);
        Draw::rect(_rect.right() - 24 * ss, pos1, _rect.right() - 16 * ss, pos2);
        Draw::circle(_rect.right() - 20 * ss, pos1, 4 * ss);
        Draw::circle(_rect.right() - 20 * ss, pos2, 4 * ss);


        setPenColor_c(c_theme);
        if(0 <= i * 3 - *_line && i * 3 - *_line < line_max) {
            _t = qMax(_rect.top() + 56 * ss + 120 * i * ss - *_line * 40 * ss, _rect.top() + 56 * ss);
            Draw::line(_l, _t, _r - 16 * ss, _t, 2 * ss);
            Draw::text(_l, _t + 20 * ss + 2, "点击此处添加...", Qt::AlignLeft | Qt::AlignVCenter);
        }

    } break;

    case THMK_EVENT_TYPE::PLAY_STORY_TIME: { // 播放计时剧情
        float _r = _rect.right() - 24 * ss;
        float _l = _rect.left() + 24 * ss;
        float _t = _rect.top() + 36 * ss;

        setPenColor_c(c_textMain);

        int i;
        int _tmp = 0;

        for(i = 0; i < data["size"]; i ++) {
            _tmp += data[QString::number(i) + "time0"] * 60 + data[QString::number(i) + "time1"];
        }

        Draw::text(_l, _t, "共有" + QString::number(data["size"]) + "句对话，共持续" +
                QString::number(floor(_tmp / 60)) + ":" + QString::number(floor(_tmp % 60)),
                   Qt::AlignLeft | Qt::AlignVCenter);

        setPenColor_c(c_theme);
        float mid_x = _r - 64 * ss;
        Draw::line(mid_x, _t - 12 * ss, mid_x, _t + 12 * ss, 2 * ss);
        Draw::line(mid_x - 12 * ss, _t, mid_x + 12 * ss, _t, 2 * ss);
        mid_x = _r - 24 * ss;
        Draw::line(mid_x - 12 * ss, _t, mid_x + 12 * ss, _t, 2 * ss);

        _t = _rect.top() + 56 * ss;
        Draw::line(_l, _t, _r, _t, 4 * ss);

        int line_max = _rect.height() / 40 / ss - 2.5;

        for(i = qMax(0, int(floor(*_line / 4)) - 1); i < data["size"]; i ++) {
            if(i * 4 - *_line >= line_max) break;
            _t = _rect.top() + 56 * ss + 160 * i * ss - *_line * 40 * ss;

            if(i * 4 - *_line >= 0) {
                setPenColor_c(c_theme);
                Draw::line(_l, _t, _r - 16 * ss, _t, 2 * ss);
            }

            QString _text[4], _list[3] = {"无显示", "非活跃", "活跃"};
            _text[0] = QString::number(i + 1) + "> " + db->getText(data[QString::number(i) + "text"], 0).replace("\n", "\\n");

            int tmp;

            tmp = data[QString::number(i) + "image0"];
            if(db->image[2].find(tmp) != db->image[2].end()) {
                _text[1] = "左边立绘为<" + db->image[2][tmp].name + ">，状态为";
            } else {
                _text[1] = "左边无立绘，状态为";
            }
            _text[1] += _list[int(data[QString::number(i) + "state0"])];

            tmp = data[QString::number(i) + "image1"];
            if(db->image[2].find(tmp) != db->image[2].end()) {
                _text[2] = "右边立绘为<" + db->image[2][tmp].name + ">，状态为";
            } else {
                _text[2] = "右边无立绘，状态为";
            }
            _text[2] += _list[int(data[QString::number(i) + "state1"])];

            _text[3] += "持续时间为" + QString::number(data[QString::number(i) + "time0"]) +
                    ":" + QString::number(data[QString::number(i) + "time1"]);

            setPenColor_c(c_textMain);
            _t += 20 * ss;
            for(int j = 0; j < 4; j ++) {
                if(i * 4 + j - *_line < line_max && i * 4 + j - *_line >= 0) {
                    Draw::text(_l, _t + 40 * ss * j + 2, _text[j], Qt::AlignLeft | Qt::AlignVCenter);
                }
            }
        }


        setPenColor_false();
        setBrushColor_c(c_symbol);
        Draw::rect(_rect.right() - 24 * ss, _rect.top() + 74 * ss, _rect.right() - 16 * ss, _rect.bottom() - 60 * ss);
        Draw::circle(_rect.right() - 20 * ss, _rect.top() + 74 * ss, 4 * ss);
        Draw::circle(_rect.right() - 20 * ss, _rect.bottom() - 60 * ss, 4 * ss);

        float line_real = data["size"] * 4 + 1;
        float _h = (_rect.bottom() - 60 * ss) - (_rect.top() + 74 * ss);
        float pos1 = _rect.top() + 74 * ss + _h * qMin(1.0f, *_line / line_real);
        float pos2 = _rect.top() + 74 * ss + _h * qMin(1.0f, (*_line + line_max) / line_real);

        setBrushColor_c(c_theme);
        Draw::rect(_rect.right() - 24 * ss, pos1, _rect.right() - 16 * ss, pos2);
        Draw::circle(_rect.right() - 20 * ss, pos1, 4 * ss);
        Draw::circle(_rect.right() - 20 * ss, pos2, 4 * ss);

        setPenColor_c(c_theme);
        if(0 <= i * 4 - *_line && i * 4 - *_line < line_max) {
            _t = qMax(_rect.top() + 56 * ss + 160 * i * ss - *_line * 40 * ss, _rect.top() + 56 * ss);
            Draw::line(_l, _t, _r - 16 * ss, _t, 2 * ss);
            Draw::text(_l, _t + 20 * ss + 2, "点击此处添加...", Qt::AlignLeft | Qt::AlignVCenter);
        }
    } break;

    case THMK_EVENT_TYPE::BOSS_START: { // BOSS战斗开始
        setPenColor_c(c_textMain);
        QString _text = "<未选择>";
        auto tmp = db->boss.find(data["boss"]);
        if(tmp != db->boss.end()) {
            _text = "<" + db->getText(tmp.value().name, 0) + ">";
        }
        Draw::text(_rect.left() + 24 * ss, _rect.top() + (36 + 40 * 0) * ss,
                   "BOSS" + _text + "登场，生命值" + QString::number(data["hp"]), Qt::AlignLeft | Qt::AlignVCenter);
        //Draw::text(_rect.left() + 24 * ss, _rect.top() + (36 + 40 * 0) * ss,
          //         "不限制时间", Qt::AlignLeft | Qt::AlignVCenter);
    } break;

    case THMK_EVENT_TYPE::BOSS_END: { // BOSS战斗结束
    } break;

    case THMK_EVENT_TYPE::BOSS_BULLET:  // BOSS发射弹幕
    case THMK_EVENT_TYPE::BOSS_SPELL_CARD: { // BOSS发射符卡
        float _r = _rect.right() - 24 * ss;
        float _l = _rect.left() + 24 * ss;
        float _t = _rect.top() + 36 * ss;
        int num = 0;
        setPenColor_c(c_textMain);

        if(type == THMK_EVENT_TYPE::BOSS_SPELL_CARD) {
            Draw::text(_l, _t + 40 * num * ss, "符卡<" + db->getText(data["name"], 0) + ">",
                       Qt::AlignLeft | Qt::AlignVCenter);
            num ++;
        }

        QString _text;
        if(data["timetype"] == 0) _text = "持续无限时间";
        else if(data["timetype"] == 1) {
            _text = "持续" + QString::number(floor(data["t1"])) + ":" + QString::number(floor(data["t2"]));
        } else if(data["timetype"] == 2) {
            _text = "持续" + QString::number(floor(data["t1"])) + ":" + QString::number(floor(data["t2"])) + "且隐藏";
        } else {
            _text = "持续至BOSS战结束";
        }
        Draw::text(_l, _t + 40 * num * ss, _text,
                   Qt::AlignLeft | Qt::AlignVCenter);
        num ++;
        if(data["condition"] == 0) _text = "被击败或超时";
        if(data["condition"] == 1) _text = "场上没有小怪";
        if(data["condition"] == 2) _text = "生命低于一半";
        if(data["condition"] == 3) _text = data_str["condition"];
        Draw::text(_l, _t + 40 * num * ss, "条件 " + _text + " 成立时继续",
                   Qt::AlignLeft | Qt::AlignVCenter);
        num ++;
        Draw::text(_l, _t + 40 * num * ss, "共有" + QString::number(data["size"]) + "个线程",
                   Qt::AlignLeft | Qt::AlignVCenter);
        num ++;

        setPenColor_c(c_theme);
        _t = _rect.top() + (16 + 40 * num) * ss;
        Draw::line(_l - 8, _t, _r + 8, _t, 4 * ss);

        int line_max = _rect.height() / 40 / ss - 4.5;
        if(type == THMK_EVENT_TYPE::BOSS_SPELL_CARD) line_max -= 1;

        int sub = (type == THMK_EVENT_TYPE::BOSS_SPELL_CARD)? 4: 3;

        Draw::setTextSize(12 * ss);
        for(int i = 0; i < data["size"]; i ++) {
            _t = _rect.top() + 16 * ss + 40 * num * ss - *_line * 40 * ss;

            if(num - sub - *_line >= line_max) break;
            if(num - sub >= *_line) {
                setPenColor_c(c_theme);
                Draw::line(_l, _t, _r - 16 * ss, _t, 2 * ss);
            }

            setPenColor_c(c_theme);
            _t += 20 * ss;
            QString str = QString::number(i) + "_";

            if(num - sub - *_line >= line_max) break;
            if(num - sub >= *_line) {
                _text = "线程" + QString::number(i + 1) + "，";
                if(data[str + "type2"] == 0) {
                    _text += "无限持续";
                } else {
                    _text += "每" + QString::number(data[str + "type2time"]) + "分秒循环";
                }
                if(data[str + "type1"] == 0) {
                    _text += "，立即生效";
                } else {
                    _text += "，" + QString::number(floor(data[str + "type1time"])) + "分秒后生效";
                }
                Draw::text(_l, _t + 40 * 0 * ss, _text,
                           Qt::AlignLeft | Qt::AlignVCenter);

            }
            num ++;

            int j, empty = 0;
            for(j = 0; j < data[str + "size"]; j ++) {
                QString tmp = str + QString::number(j) + "_";
                if(data[tmp + "type"] == -1) {
                    empty ++;
                    continue;
                }

                setPenColor_c(c_textMain);
                if(num - sub - *_line >= line_max) break;
                if(num - sub >= *_line) {
                    QStringList _type_list = {"直线", "环形", "扇形", "矩形内随机", "圆形内随机", "自定义"};
                    _text = QString::number(j + 1) + ". ";
                    if(data_str[tmp + "timer"] == "0") {
                        _text += "一次性";
                    } else {
                        _text += "每" + data_str[tmp + "timer"] + "分秒，";
                    }
                    _text += _type_list[data[tmp + "type"]] + "发射总共" + data_str[tmp + "num"] + "个";

                    auto _bullet = db->bullet[0].find(data[tmp + "index"]);
                    if(_bullet == db->bullet[0].end()) {
                        _text += "<未选择>";
                    } else {
                        _text += "<" + _bullet->name + ">";
                    }
                    _text += "，冷却" + data_str[tmp + "time"] + "分秒";
                    if(j >= data[str + "size"] - 1) {
                        Draw::text(_l, _t + 40 * (j * 2 + 1) * ss, "(X)" + _text,
                                   Qt::AlignLeft | Qt::AlignVCenter);
                    } else {
                        Draw::text(_l, _t + 40 * (j * 2 + 1) * ss, _text,
                                   Qt::AlignLeft | Qt::AlignVCenter);
                    }

                }
                num ++;

                if(num - sub - *_line >= line_max) break;
                if(num - sub >= *_line) {
                    if(data[tmp + "type"] == 0) {
                        _text = "原点(" + data_str[tmp + "x0"] + "," + data_str[tmp + "y0"] + ")，角度" +
                                data_str[tmp + "dir"] + "度，间隔" + data_str[tmp + "step"] + "px，初速度" + data_str[tmp + "spd"];
                    } else if(data[tmp + "type"] == 1) {
                        _text = "原点(" + data_str[tmp + "x0"] + "," + data_str[tmp + "y0"] + ")，角度" +
                                data_str[tmp + "dir"] + "度，半径" + data_str[tmp + "radius"] + "px，初速度" + data_str[tmp + "spd"];
                    } else if(data[tmp + "type"] == 2) {
                        _text = "原点(" + data_str[tmp + "x0"] + "," + data_str[tmp + "y0"] + ")，角度" +
                                data_str[tmp + "dir"] + "度，半径" + data_str[tmp + "radius"] + "px，间隔" +
                                data_str[tmp + "angle"] + "度，初速度" + data_str[tmp + "spd"];
                    } else if(data[tmp + "type"] == 3) {
                        _text = "左上角(" + data_str[tmp + "x0"] + "," +
                                data_str[tmp + "x0"] + ")，" +
                                "右下角(" + data_str[tmp + "x0"] + "," +
                                data_str[tmp + "x0"] + ")，初速度" + data_str[tmp + "spd"];
                    } else if(data[tmp + "type"] == 4) {
                        _text = "原点(" + data_str[tmp + "x0"] + "," + data_str[tmp + "y0"] + ")，半径" +
                                data_str[tmp + "radius"] + "px，初速度" + data_str[tmp + "spd"];
                    } else {
                        setPenColor_c(c_theme);
                        _text = "点此编辑初始化代码...";
                    }
                    Draw::text(_l, _t + 40 * (j * 2 + 2) * ss, _text,
                               Qt::AlignLeft | Qt::AlignVCenter);

                }
                num ++;


            }

            if(num - sub - *_line >= line_max) break;
            if(num - sub >= *_line) {
                setPenColor_c(c_theme);
                Draw::text(_l, _t + 40 * (j * 2 + 1 - empty * 2) * ss, "点此添加弹幕...",
                           Qt::AlignLeft | Qt::AlignVCenter);
            }
            num ++;
        }

        setPenColor_false();
        setBrushColor_c(c_symbol);
        float _top = (type == 11)? (_rect.top() + 194 * ss): (_rect.top() + 154 * ss);
        Draw::rect(_rect.right() - 24 * ss, _top, _rect.right() - 16 * ss, _rect.bottom() - 60 * ss);
        Draw::circle(_rect.right() - 20 * ss, _top, 4 * ss);
        Draw::circle(_rect.right() - 20 * ss, _rect.bottom() - 60 * ss, 4 * ss);

        float line_real = 0;
        for(int i = 0; i < data["size"]; i ++) {
            line_real += 2 + data[QString::number(i) + "_size"] * 2;
        }
        float _h = (_rect.bottom() - 60 * ss) - _top;
        float pos1 = _top + _h * qMin(1.0f, *_line / line_real);
        float pos2 = _top + _h * qMin(1.0f, (*_line + line_max) / line_real);

        setBrushColor_c(c_theme);
        Draw::rect(_rect.right() - 24 * ss, pos1, _rect.right() - 16 * ss, pos2);
        Draw::circle(_rect.right() - 20 * ss, pos1, 4 * ss);
        Draw::circle(_rect.right() - 20 * ss, pos2, 4 * ss);


    } break;

    case THMK_EVENT_TYPE::CLS: { // 清理场上弹幕和小怪
    } break;

    case THMK_EVENT_TYPE::GOTO: { // 跳转
        setPenColor_c(c_textMain);
        Draw::text(_rect.left() + 24 * ss, _rect.top() + 36 * ss, "若条件 " + data_str["condition"] + " 成立",
                Qt::AlignLeft | Qt::AlignVCenter);
        Draw::text(_rect.left() + 24 * ss, _rect.top() + 76 * ss,"跳转至 " + QString::number(floor(data["t1"])) + ":" + QString::number(floor(data["t2"])),
                Qt::AlignLeft | Qt::AlignVCenter);
    } break;

    case THMK_EVENT_TYPE::STAGE_CHANGE: { // 结束
        setPenColor_c(c_textMain);
        Draw::text(_rect.left() + 24 * ss, _rect.top() + 36 * ss, "若条件 " + data_str["condition"] + " 成立",
                Qt::AlignLeft | Qt::AlignVCenter);
        QStringList _list2 = {"进入下一关", "进入上一关", "结束游戏"};
        Draw::text(_rect.left() + 24 * ss, _rect.top() + 76 * ss, _list2[data["next"]],
                Qt::AlignLeft | Qt::AlignVCenter);
    } break;

    case THMK_EVENT_TYPE::POINT: { // 断点
    } break;

    default: {
        setPenColor_c(c_textMain);
        Draw::text(_rect.left() + 24 * ss, _rect.top() + 36 * ss,
                   "id=" + QString::number(id) + ", type=" + QString::number(type), Qt::AlignLeft | Qt::AlignVCenter);
    } break;

    }

}

bool DB_STAGE_EVENT::editCode(Window_editor_stage *window, Database *db, QRectF _rect, float *_line, float ss, float mx, float my)
{
    switch (type) {
    case THMK_EVENT_TYPE::SET_BACKGROUND: {// 设置背景图像为
        float _t = _rect.top() + 36 * ss;
        float _r = _rect.right() - 24 * ss;
        if(abs(_t - my) < 20 * ss) {
            ask_create("设置背景雾");
            ask_add_dragStick("背景雾强度", &data["fog_alpha"], 0, 100, "%", 1);
            ask_add_dragStick("雾颜色 - 红", &data["fog_r"], 0, 255, "", 1);
            ask_add_dragStick("雾颜色 - 绿", &data["fog_g"], 0, 255, "", 1);
            ask_add_dragStick("雾颜色 - 蓝", &data["fog_b"], 0, 255, "", 1);
            window->connect(window_ask_ex, SIGNAL(OK()), window, SLOT(codeEditFinished()));
        } else {
            for(int i = 0; i < 4; i ++) {
                _t = _rect.top() + 76 * ss + 120 * i * ss;
                QString tmp = "background" + QString::number(i);
                if(abs(_t - my) < 20 * ss || (_r - 120 * ss < mx && mx < _r && _t - 20 * ss < my && my < _t + 100 * ss)) {
                    find_create(db, Window_find::type_image, 0, &data[tmp]);
                    window->connect(window_find, SIGNAL(OK()), window, SLOT(codeEditFinished()));
                } else if(_t + 20 * ss < my && my < _t + 100 * ss) {
                    ask_create("设置图像运动");
                    window->connect(window_ask_ex, SIGNAL(OK()), window, SLOT(codeEditFinished()));
                    ask_add_lineEdit_float("方向（0-360度）", &data[tmp + "direction"], 0, 359.99);
                    ask_add_lineEdit_float("速度（像素每秒）", &data[tmp + "speed"], -100, 100);
                    //ask_add_dragStick("倾斜度", &data[tmp + "slope"], -90, 90, "", 1);
                    ask_add_chooseButton("重复图形", &data[tmp + "repeat"], QStringList({"不重复", "重复"}));

                }
            }

        }
    } break;

    case THMK_EVENT_TYPE::SET_BGM: {// 设置背景音乐为
        if(_rect.top() + 16 * ss < my && my < _rect.top() + 56 * ss) {
            find_create(db, Window_find::type_audio, 0, &data["bgm"]);
            window->connect(window_find, SIGNAL(OK()), window, SLOT(codeEditFinished()));
        }
    } break;

    case THMK_EVENT_TYPE::PLAY_SE: {// 播放音效
        if(_rect.top() + 16 * ss < my && my < _rect.top() + 56 * ss) {
            find_create(db, Window_find::type_audio, 1, &data["se"]);
            window->connect(window_find, SIGNAL(OK()), window, SLOT(codeEditFinished()));
        } else if(_rect.top() + 56 * ss < my && my < _rect.top() + 96 * ss) {
            ask_create("设置音效");
            ask_add_dragStick("音量", &data["volume"], 0, 200, "%", 1);
            ask_add_dragStick("音高", &data["pitch"], 0, 200, "%", 1);
            window->connect(window_ask_ex, SIGNAL(OK()), window, SLOT(codeEditFinished()));
        }
    } break;

    case THMK_EVENT_TYPE::PLAY_EFFECT: {// 播放特效
        if(_rect.top() + 16 * ss < my && my < _rect.top() + 56 * ss) {
            find_create(db, Window_find::type_effect, 1, &data["effect"]);
            window->connect(window_find, SIGNAL(OK()), window, SLOT(codeEditFinished()));
        }
    } break;

    case THMK_EVENT_TYPE::CREATE_ENEMY: // 即刻生成小怪
    case THMK_EVENT_TYPE::CREATE_ENEMY_TIME: { // 生成小怪队列
        if(_rect.top() + (16 + 40 * 0) * ss < my && my < _rect.top() + (16 + 40 * 1) * ss) {
            ask_create_db("设置小怪", db);
            QStringList _list_type = {"直线", "环形", "扇形"};
            ask_add_chooseButton("生成方式", &data["type"], _list_type);
            ask_add_lineEdit_int("数量", &data["number"], 1, 20);
            ask_add_findButton("小怪", Window_find::type_enemy, 0, &data["enemy"]);
            if(type == 5) ask_add_lineEdit_float("间隔时间（分秒）", &data["time"], 1, 32767);
            window->connect(window_ask_ex, SIGNAL(OK()), window, SLOT(codeEditFinished()));
        }

        if(data["type"] == 0) {
            if(_rect.top() + (16 + 40 * 1) * ss < my && my < _rect.top() + (16 + 40 * 3) * ss) {
                ask_create("设置直线生成");
                ask_add_lineEdit_float("x0", &data["x0"], -1000, 1000);
                ask_add_lineEdit_float("y0", &data["y0"], -1000, 1000);
                ask_add_lineEdit_float("发射方向", &data["dir"], 0, 359.99);
                ask_add_lineEdit_float("间隔长度", &data["step"], 0, 32767);
                ask_add_lineEdit_float("初速度", &data["spd"], 0, 32767);
                window->connect(window_ask_ex, SIGNAL(OK()), window, SLOT(codeEditFinished()));
            }
        } else if(data["type"] == 1) {
            if(_rect.top() + (16 + 40 * 1) * ss < my && my < _rect.top() + (16 + 40 * 3) * ss) {
                ask_create("设置环形生成");
                ask_add_lineEdit_float("x0", &data["x0"], -1000, 1000);
                ask_add_lineEdit_float("y0", &data["y0"], -1000, 1000);
                ask_add_lineEdit_float("圆半径", &data["radius"], 0, 32767);
                ask_add_lineEdit_float("初始方向", &data["dir"], 0, 359.99);
                ask_add_lineEdit_float("初速度", &data["spd"], 0, 32767);
                window->connect(window_ask_ex, SIGNAL(OK()), window, SLOT(codeEditFinished()));
            }
        } else if(data["type"] == 2) {
            if(_rect.top() + (16 + 40 * 1) * ss < my && my < _rect.top() + (16 + 40 * 3) * ss) {
                ask_create("设置扇形生成");
                ask_add_lineEdit_float("x0", &data["x0"], -1000, 1000);
                ask_add_lineEdit_float("y0", &data["y0"], -1000, 1000);
                ask_add_lineEdit_float("圆半径", &data["radius"], 0, 32767);
                ask_add_lineEdit_float("初始方向", &data["dir"], 0, 359.99);
                ask_add_lineEdit_float("间隔角度", &data["angle"], 0, 359.99);
                ask_add_lineEdit_float("初速度", &data["spd"], 0, 32767);
                window->connect(window_ask_ex, SIGNAL(OK()), window, SLOT(codeEditFinished()));
            }
        }
        if(_rect.top() + (16 + 40 * 3) * ss < my && my < _rect.top() + (16 + 40 * 4) * ss) {
            ask_create_db("设置初始状态", db);
            ask_add_textEdit("在此输入初始化代码...", &data_str["code"]);
            window->connect(window_ask_ex, SIGNAL(OK()), window, SLOT(codeEditFinished()));
        }

    } break;

    case THMK_EVENT_TYPE::PLAY_STORY: { // 播放剧情

        float _r = _rect.right() - 24 * ss;
        float _t = _rect.top() + 36 * ss;
        if(abs(_t - my) < 20 * ss) {
            if(abs(_r - 64 * ss - mx) < 20 * ss) {
                data["size"] += 1;
                QString tmp = QString::number(data["size"] - 1);
                data[tmp + "text"] = db->text_append("");
                data[tmp + "image0"] = -1;
                data[tmp + "state0"] = 1;
                data[tmp + "image1"] = -1;
                data[tmp + "state1"] = 1;
                return true;
            } else if(abs(_r - 24 * ss - mx) < 20 * ss) {
                if(data["size"] > 0) {
                    data["size"] -= 1;
                    QString tmp = QString::number(data["size"]);
                    db->text_delete(data[tmp + "text"]);
                    data.remove(tmp + "text");
                    data.remove(tmp + "image0");
                    data.remove(tmp + "state0");
                    data.remove(tmp + "image1");
                    data.remove(tmp + "state1");
                    float line_max = _rect.height() / 40 * ss - 2.5;
                    float line_real = data["size"] * 3 + 2;
                    if(line_real < line_max) *_line = 0;
                    else *_line = qMin(*_line, line_real - line_max);
                    return true;
                }
            }
        } else {
            int line_max = _rect.height() / 40 / ss - 2.5;
            int i;
            for(i = qMax(0, int(floor(*_line / 3)) - 1); i < data["size"]; i ++) {
                if(i * 3 - *_line >= line_max) break;
                _t = _rect.top() + 76 * ss + 120 * i * ss - *_line * 40 * ss;
                if(abs(_t - my) < 20 * ss) {
                    Window_editor_menubar_text_edit *window_edit =
                            new Window_editor_menubar_text_edit(db, &db->text[data[QString::number(i) + "text"]]);
                    window_edit->setWindowModality(Qt::ApplicationModal);
                    window_edit->setAttribute(Qt::WA_DeleteOnClose);
                    window_edit->show();
                    window->connect(window_edit, SIGNAL(closed()), window, SLOT(codeEditFinished()));

                } else if(_t + 20 * ss < my && my < _t + 100 * ss) {

                    ask_create_db("设置立绘", db);
                    window->connect(window_ask_ex, SIGNAL(OK()), window, SLOT(codeEditFinished()));
                    QStringList _list = {"无显示", "非活跃", "活跃"};
                    ask_add_findButton("左边立绘", Window_find::type_image, 2, &data[QString::number(i) + "image0"]);
                    ask_add_chooseButton("状态为", &data[QString::number(i) + "state0"], _list);
                    ask_add_findButton("右边立绘", Window_find::type_image, 2, &data[QString::number(i) + "image1"]);
                    ask_add_chooseButton("状态为", &data[QString::number(i) + "state1"], _list);

                }
            }
            _t = _rect.top() + 76 * ss + 120 * i * ss - *_line * 40 * ss;
            if((0 <= i * 3 - *_line && i * 3 - *_line < line_max) && abs(_t - my) < 20 * ss) {
                data["size"] += 1;
                QString tmp = QString::number(data["size"] - 1);
                data[tmp + "text"] = db->text_append("");
                data[tmp + "image0"] = -1;
                data[tmp + "state0"] = 1;
                data[tmp + "image1"] = -1;
                data[tmp + "state1"] = 1;
                return true;
            }
        }
    } break;

    case THMK_EVENT_TYPE::PLAY_STORY_TIME: { // 播放计时剧情

        float _r = _rect.right() - 24 * ss;
        float _t = _rect.top() + 36 * ss;
        if(abs(_t - my) < 20 * ss) {
            if(abs(_r - 64 * ss - mx) < 20 * ss) {
                data["size"] += 1;
                QString tmp = QString::number(data["size"] - 1);
                data[tmp + "text"] = db->text_append("");
                data[tmp + "image0"] = -1;
                data[tmp + "state0"] = 0;
                data[tmp + "image1"] = -1;
                data[tmp + "state1"] = 0;
                data[tmp + "time0"] = 5;
                data[tmp + "time1"] = 0;
                return true;
            } else if(abs(_r - 24 * ss - mx) < 20 * ss) {
                if(data["size"] > 0) {
                    data["size"] -= 1;
                    QString tmp = QString::number(data["size"]);
                    db->text_delete(data[tmp + "text"]);
                    data.remove(tmp + "text");
                    data.remove(tmp + "image0");
                    data.remove(tmp + "state0");
                    data.remove(tmp + "image1");
                    data.remove(tmp + "state1");
                    data.remove(tmp + "time0");
                    data.remove(tmp + "time1");
                    float line_max = _rect.height() / 40 * ss - 2.5;
                    float line_real = data["size"] * 4 + 2;
                    if(line_real < line_max) *_line = 0;
                    else *_line = qMin(*_line, line_real - line_max);
                    return true;
                }
            }
        } else {
            int line_max = _rect.height() / 40 / ss - 2.5;
            int i;
            for(i = qMax(0, int(floor(*_line / 4)) - 1); i < data["size"]; i ++) {
                if(i * 4 - *_line >= line_max) break;
                _t = _rect.top() + 76 * ss + 160 * i * ss - *_line * 40 * ss;
                if(abs(_t - my) < 20 * ss) {
                    Window_editor_menubar_text_edit *window_edit =
                            new Window_editor_menubar_text_edit(db, &db->text[data[QString::number(i) + "text"]]);
                    window_edit->setWindowModality(Qt::ApplicationModal);
                    window_edit->setAttribute(Qt::WA_DeleteOnClose);
                    window_edit->show();
                    window->connect(window_edit, SIGNAL(closed()), window, SLOT(codeEditFinished()));

                } else if(_t + 20 * ss < my && my < _t + 100 * ss) {

                    ask_create_db("设置立绘", db);
                    window->connect(window_ask_ex, SIGNAL(OK()), window, SLOT(codeEditFinished()));
                    QStringList _list = {"无显示", "非活跃", "活跃"};
                    ask_add_findButton("左边立绘", Window_find::type_image, 2, &data[QString::number(i) + "image0"]);
                    ask_add_chooseButton("状态为", &data[QString::number(i) + "state0"], _list);
                    ask_add_findButton("右边立绘", Window_find::type_image, 2, &data[QString::number(i) + "image1"]);
                    ask_add_chooseButton("状态为", &data[QString::number(i) + "state1"], _list);

                } else if(_t + 100 * ss < my && my < _t + 140 * ss) {
                    ask_create_db("设置持续时间", db);
                    ask_add_lineEdit_int("秒", &data[QString::number(i) + "time0"], 0, 59);
                    ask_add_lineEdit_int("分秒", &data[QString::number(i) + "time1"], 0, 59);
                }
            }
            _t = _rect.top() + 76 * ss + 160 * i * ss - *_line * 40 * ss;
            if((0 <= i * 4 - *_line && i * 4 - *_line < line_max) && abs(_t - my) < 20 * ss) {
                data["size"] += 1;
                QString tmp = QString::number(data["size"] - 1);
                data[tmp + "text"] = db->text_append("");
                data[tmp + "image0"] = -1;
                data[tmp + "state0"] = 0;
                data[tmp + "image1"] = -1;
                data[tmp + "state1"] = 0;
                data[tmp + "time0"] = 5;
                data[tmp + "time1"] = 0;
                return true;
            }
        }
    } break;

    case THMK_EVENT_TYPE::BOSS_START: { // BOSS战斗开始
        if(_rect.top() + (16 + 40 * 0) * ss < my && my < _rect.top() + (16 + 40 * 1) * ss) {
            ask_create_db("设置BOSS", db);
            ask_add_findButton("BOSS为", Window_find::type_boss, 0, &data["boss"]);
            ask_add_lineEdit_int("生命值", &data["hp"], 1, 32767);
            window->connect(window_ask_ex, SIGNAL(OK()), window, SLOT(codeEditFinished()));
        }
    } break;

    case THMK_EVENT_TYPE::BOSS_END: { // BOSS战斗结束
    } break;

    case THMK_EVENT_TYPE::BOSS_BULLET: // BOSS发射弹幕
    case THMK_EVENT_TYPE::BOSS_SPELL_CARD: { // BOSS发射符卡


        int num = 0;
        if(type == THMK_EVENT_TYPE::BOSS_SPELL_CARD) {
            if(_rect.top() + (16 + 40 * num) * ss < my && my < _rect.top() + (16 + 40 * (num + 1)) * ss) {
                ask_create_db("设置符卡", db);
                ask_add_lineEdit_str("符卡名称", &db->text[data["name"]].__text[0]);
                window->connect(window_ask_ex, SIGNAL(OK()), window, SLOT(codeEditFinished()));
            }
            num ++;

        }

        if(_rect.top() + (16 + 40 * num) * ss < my && my < _rect.top() + (16 + 40 * (num + 1)) * ss) {
            ask_create_db("设置弹幕", db);
            QStringList _list = {"无限", "有限", "有限且隐藏BOSS", "持续至BOSS战结束"};
            ask_add_chooseButton("弹幕持续时间", &data["timetype"], _list);
            ask_add_lineEdit_int("秒", &data["t1"], 0, 599);
            ask_add_lineEdit_int("分秒", &data["t2"], 0, 59);
            window->connect(window_ask_ex, SIGNAL(OK()), window, SLOT(codeEditFinished()));
        }
        num ++;
        if(_rect.top() + (16 + 40 * num) * ss < my && my < _rect.top() + (16 + 40 * (num + 1)) * ss) {
            ask_create_db("设置结束条件", db);
            QStringList _list = {"被击败或超时", "场上没有小怪", "生命低于一半", "自定义"};
            ask_add_chooseButton("结束条件", &data["condition"], _list);
            ask_add_lineEdit_str("自定义条件", &data_str["condition"]);
            window->connect(window_ask_ex, SIGNAL(OK()), window, SLOT(codeEditFinished()));
        }
        num ++;
        if(_rect.top() + (16 + 40 * num) * ss < my && my < _rect.top() + (16 + 40 * (num + 1)) * ss) {
            ask_create_db("设置线程数", db);
            ask_add_lineEdit_int("线程数量", &data["size"], 1, 20);
            window->connect(window_ask_ex, SIGNAL(OK()), window, SLOT(codeEditBossAddThreadFinished()));
        }
        num ++;

        int sub = (type == THMK_EVENT_TYPE::BOSS_SPELL_CARD)? 4: 3;

        int line_max = _rect.height() / 40 / ss - 4.5;
        if(type == THMK_EVENT_TYPE::BOSS_SPELL_CARD) line_max -= 1;

        for(int i = 0; i < data["size"]; i ++) {
            QString str = QString::number(i) + "_";

            if(num - sub - *_line >= line_max) break;
            if(num - sub >= *_line) {
                if(_rect.top() + (16 + 40 * (num - *_line)) * ss < my && my < _rect.top() + (16 + 40 * (num - *_line + 1)) * ss) {
                    ask_create("设置线程");
                    ask_set_page_number(2);
                    ask_set_current_page(0);
                    QStringList _list2 = {"无限持续", "循环"};
                    ask_add_chooseButton("持续形式", &data[str + "type2"], _list2);
                    ask_add_lineEdit_int("循环时间（分秒）", &data[str + "type2time"], 1, 3599);
                    ask_add_textEdit("在此输入初始化代码...", &data_str[str + "init"]);
                    ask_set_current_page(1);
                    QStringList _list1 = {"立即生效", "一段时间后生效"};
                    ask_add_chooseButton("生效条件", &data[str + "type1"], _list1);
                    ask_add_lineEdit_int("等待时间（分秒）", &data[str + "type1time"], 0, 3599);
                    ask_add_textEdit("在此输入步事件代码...", &data_str[str + "step"]);
                    window->connect(window_ask_ex, SIGNAL(OK()), window, SLOT(codeEditFinished()));
                }
            }
            num ++;

            for(int j = 0; j < data[str + "size"]; j ++) {
                QString tmp = str + QString::number(j) + "_";
                if(data[tmp + "type"] == -1) {
                    continue;
                }

                if(num - sub - *_line >= line_max) break;
                if(num - sub >= *_line) {
                    if(_rect.top() + (16 + 40 * (num - *_line)) * ss < my && my < _rect.top() + (16 + 40 * (num - *_line + 1)) * ss) {

                        if(j >= data[str + "size"] - 1) {
                            if(mx < _rect.left() + 72 * ss) {
                                data[tmp + "type"] = -1;
                                data[tmp + "inited"] = 0;
                                window->codeEditBossAddEventFinished();
                                return false;
                            }
                        }

                        ask_create_db("设置弹幕", db);
                        ask_add_findButton("子弹为", Window_find::type_bullet, 0, &data[tmp + "index"]);
                        ask_add_lineEdit_str("发射数量", &data_str[tmp + "num"]);
                        ask_add_lineEdit_str("发射间隔", &data_str[tmp + "timer"]);
                        ask_add_lineEdit_str("冷却时间", &data_str[tmp + "time"]);

                        if(data[tmp + "type"] == 0) {

                            ask_add_lineEdit_str("原点x0", &data_str[tmp + "x0"]);
                            ask_add_lineEdit_str("原点y0", &data_str[tmp + "y0"]);
                            ask_add_lineEdit_str("射线角度", &data_str[tmp + "dir"]);
                            ask_add_lineEdit_str("间隔", &data_str[tmp + "step"]);
                            ask_add_lineEdit_str("初速度", &data_str[tmp + "spd"]);

                        } else if(data[tmp + "type"] == 1) {

                            ask_add_lineEdit_str("原点x0", &data_str[tmp + "x0"]);
                            ask_add_lineEdit_str("原点y0", &data_str[tmp + "y0"]);
                            ask_add_lineEdit_str("初始角度", &data_str[tmp + "dir"]);
                            ask_add_lineEdit_str("圆半径", &data_str[tmp + "radius"]);
                            ask_add_lineEdit_str("初速度", &data_str[tmp + "spd"]);

                        } else if(data[tmp + "type"] == 2) {

                            ask_add_lineEdit_str("原点x0", &data_str[tmp + "x0"]);
                            ask_add_lineEdit_str("原点y0", &data_str[tmp + "y0"]);
                            ask_add_lineEdit_str("中心角度", &data_str[tmp + "dir"]);
                            ask_add_lineEdit_str("圆半径", &data_str[tmp + "radius"]);
                            ask_add_lineEdit_str("间隔角度", &data_str[tmp + "angle"]);
                            ask_add_lineEdit_str("初速度", &data_str[tmp + "spd"]);

                        } else if(data[tmp + "type"] == 3) {

                            ask_add_lineEdit_str("左上角x0", &data_str[tmp + "x0"]);
                            ask_add_lineEdit_str("左上角y0", &data_str[tmp + "y0"]);
                            ask_add_lineEdit_str("右下角角x1", &data_str[tmp + "x0"]);
                            ask_add_lineEdit_str("右下角y1", &data_str[tmp + "y0"]);
                            ask_add_lineEdit_str("初速度", &data_str[tmp + "spd"]);

                        } else if(data[tmp + "type"] == 4) {

                            ask_add_lineEdit_str("原点x0", &data_str[tmp + "x0"]);
                            ask_add_lineEdit_str("原点y0", &data_str[tmp + "y0"]);
                            ask_add_lineEdit_str("圆半径", &data_str[tmp + "radius"]);
                            ask_add_lineEdit_str("初速度", &data_str[tmp + "spd"]);

                        } else {

                            ask_add_textEdit("在此输入子弹生成代码...", &data_str[tmp + "create"]);

                        }
                        window->connect(window_ask_ex, SIGNAL(OK()), window, SLOT(codeEditFinished()));
                    }
                }
                num ++;

                if(num - sub - *_line >= line_max) break;
                if(num - sub >= *_line) {
                    if(_rect.top() + (16 + 40 * (num - *_line)) * ss < my && my < _rect.top() + (16 + 40 * (num - *_line + 1)) * ss) {

                        ask_create_db("设置弹幕", db);
                        ask_add_textEdit("在此输入初始化代码...", &data_str[tmp + "code"]);

                        window->connect(window_ask_ex, SIGNAL(OK()), window, SLOT(codeEditFinished()));
                    }

                }
                num ++;
            }

            if(num - sub - *_line >= line_max) break;
            if(num - sub >= *_line) {
                if(_rect.top() + (16 + 40 * (num - *_line)) * ss < my && my < _rect.top() + (16 + 40 * (num - *_line + 1)) * ss) {
                    data[str + QString::number(data[str + "size"]) + "_type"] = -1;
                    data[str + QString::number(data[str + "size"]) + "_inited"] = 0;
                    QStringList _list = {"直线", "环形", "扇形", "矩形内随机", "圆形内随机", "自定义"};
                    ask_create("添加弹幕");
                    ask_add_chooseButton("弹幕类型", &data[str + QString::number(data[str + "size"]) + "_type"], _list);
                    window->connect(window_ask_ex, SIGNAL(closed()), window, SLOT(codeEditBossAddEventFinished()));
                    data[str + "size"] ++;
                }
            }
            num ++;
        }

    } break;

    case THMK_EVENT_TYPE::CLS: { // 清理场上弹幕和小怪
    } break;

    case THMK_EVENT_TYPE::GOTO: { // 跳转
        if(_rect.top() + 16 * ss < my && my < _rect.top() + 96 * ss) {
            ask_create("设置跳转事件");
            window->connect(window_ask_ex, SIGNAL(OK()), window, SLOT(codeEditFinished()));
            ask_add_lineEdit_str("条件", &data_str["condition"]);
            ask_add_lineEdit_int("秒", &data["t1"], 0, 599);
            ask_add_lineEdit_int("分秒", &data["t2"], 0, 59);
        }
    } break;

    case THMK_EVENT_TYPE::STAGE_CHANGE: { // 结束
        if(_rect.top() + 16 * ss < my && my < _rect.top() + 96 * ss) {
            ask_create("设置结束事件");
            window->connect(window_ask_ex, SIGNAL(OK()), window, SLOT(codeEditFinished()));
            QStringList _list2 = {"进入下一关", "进入上一关", "结束游戏"};
            ask_add_lineEdit_str("条件", &data_str["condition"]);
            ask_add_chooseButton("行为", &data["next"], _list2);
        }
    } break;

    case THMK_EVENT_TYPE::POINT: { // 断点
    } break;

    default: {
    } break;

    }
    return false;
}

void DB_STAGE_EVENT::wheelEvent(Window_editor_stage *window, Database *db, QRectF _rect, float *_line, float ss)
{
    *_line = qMax(0.0f, *_line);
    switch (type) {

    case THMK_EVENT_TYPE::PLAY_STORY: {
        float line_max = _rect.height() / 40 / ss - 2.5;
        float line_real = data["size"] * 3 + 2;
        if(line_real < line_max) *_line = 0;
        else *_line = qMin(*_line, line_real - line_max);
    } break;

    case THMK_EVENT_TYPE::PLAY_STORY_TIME: {
        float line_max = _rect.height() / 40 / ss - 2.5;
        float line_real = data["size"] * 4 + 2;
        if(line_real < line_max) *_line = 0;
        else *_line = qMin(*_line, line_real - line_max);
    } break;

    case THMK_EVENT_TYPE::BOSS_BULLET:
    case THMK_EVENT_TYPE::BOSS_SPELL_CARD: {
        float line_max = _rect.height() / 40 / ss - 4.5;
        if(type == THMK_EVENT_TYPE::BOSS_SPELL_CARD) line_max -= 1;
        float line_real = 1;
        for(int i = 0; i < data["size"]; i ++) {
            line_real += 2 + data[QString::number(i) + "_size"] * 2;
        }
        if(line_real < line_max) *_line = 0;
        else *_line = qMin(*_line, line_real - line_max);

    } break;

    case THMK_EVENT_TYPE::SET_BGM:
        break;
    default:
        *_line = 0;
        break;
    }

    *_line = qMax(0.0f, *_line);
}

void DB_STAGE_EVENT::toJson(QMap<int, int> map_text, QMap<int, int> map_hero, QMap<int, int> map_enemy, QMap<int, int> map_boss, QMap<int, int> map_bullet[], QMap<int, int> map_effect[], QMap<int, int> map_audio[], QMap<int, int> map_image[], QJsonObject *jObj)
{
    jObj->insert("enable", data["enable"]);

    switch (type) {
    case THMK_EVENT_TYPE::SET_BACKGROUND: {
        QJsonArray jArr_bcklist;

        for(int i = 0; i < 4; i ++) {
            QJsonObject jObj_bck;
            QString tmp = "background" + QString::number(i);

            jObj_bck.insert("id", map_image[0][data[tmp]]);
            jObj_bck.insert("direction", data[tmp + "direction"]);
            jObj_bck.insert("speed",     data[tmp + "speed"]);
            jObj_bck.insert("slope",     data[tmp + "slope"]);
            jObj_bck.insert("repeat",    data[tmp + "repeat"]);

            jArr_bcklist.append(jObj_bck);
        }

        jObj->insert("backgroundList", jArr_bcklist);

        jObj->insert("fog_alpha", data["fog_alpha"] / 100);
        jObj->insert("fog_r", data["fog_r"]);
        jObj->insert("fog_g", data["fog_g"]);
        jObj->insert("fog_b", data["fog_b"]);

    } break;

    case THMK_EVENT_TYPE::SET_BGM: {
        jObj->insert("id", map_audio[0][data["bgm"]]);
    } break;

    case THMK_EVENT_TYPE::PLAY_SE: {
        jObj->insert("id", map_audio[1][data["se"]]);
        jObj->insert("volume", data["volume"]);
        jObj->insert("pitch", data["pitch"]);
    } break;

    case THMK_EVENT_TYPE::PLAY_EFFECT: {
        jObj->insert("id", map_effect[1][data["effect"]]);
    } break;

    case THMK_EVENT_TYPE::CREATE_ENEMY: //"即刻生成小怪";
    case THMK_EVENT_TYPE::CREATE_ENEMY_TIME: { //"生成小怪队列";
        jObj->insert("number", data["number"]);
        jObj->insert("id", map_enemy[data["enemy"]]);
        jObj->insert("type", data["type"]);
        if(type == THMK_EVENT_TYPE::CREATE_ENEMY_TIME) jObj->insert("time", data["time"]);

        jObj->insert("x0", data["x0"]);
        jObj->insert("y0", data["y0"]);
        jObj->insert("dir", data["dir"]);
        jObj->insert("step", data["step"]);
        jObj->insert("radius", data["radius"]);
        jObj->insert("angle", data["angle"]);
        jObj->insert("spd", data["spd"]);

        jObj->insert("code", data_str["code"].replace("\n", "\\n"));
    } break;

    case THMK_EVENT_TYPE::PLAY_STORY: //"播放剧情";
    case THMK_EVENT_TYPE::PLAY_STORY_TIME: { //"播放计时剧情";
        jObj->insert("size", data["size"]);

        QJsonArray jArr_digList;
        for(int i = 0; i < data["size"]; i ++) {
            QJsonObject jObj_dig;
            QString tmp = QString::number(i);
            jObj_dig.insert("text", map_text[data[tmp + "text"]]);
            jObj_dig.insert("image0", map_image[2][int(data[tmp + "image0"])]);
            jObj_dig.insert("state0", data[tmp + "state0"]);
            jObj_dig.insert("image1", map_image[2][int(data[tmp + "image1"])]);
            jObj_dig.insert("state1", data[tmp + "state1"]);
            if(type == 7) jObj_dig.insert("time", data[tmp + "time0"] * 60 + data[tmp + "time1"]);

            jArr_digList.append(jObj_dig);
        }

        jObj->insert("dialogList", jArr_digList);

    } break;

    case THMK_EVENT_TYPE::BOSS_START: {//"BOSS战斗开始";
        jObj->insert("boss", map_boss[data["boss"]]);
        jObj->insert("hp", data["hp"]);
    } break;

    case THMK_EVENT_TYPE::BOSS_END: //"BOSS战斗结束";
        break;

    case THMK_EVENT_TYPE::BOSS_BULLET://"BOSS发射弹幕";
    case THMK_EVENT_TYPE::BOSS_SPELL_CARD: {  //"BOSS发射符卡";
        if(type == THMK_EVENT_TYPE::BOSS_SPELL_CARD) jObj->insert("name", map_text[data["name"]]);
        jObj->insert("timeType", data["timetype"]);
        jObj->insert("time", data["t1"] * 60 + data["t2"]);
        jObj->insert("condition", data["condition"]);
        jObj->insert("condition_code", data_str["condition"].replace("\n", "\\n"));
        jObj->insert("size", data["size"]);

        QJsonArray jArr_threadList;
        for(int i = 0; i < data["size"]; i ++) {
            QJsonObject jObj_thread;

            QString str = QString::number(i) + "_";

            jObj_thread.insert("size", data[str + "size"]);
            jObj_thread.insert("type1", data[str + "type1"]);
            jObj_thread.insert("type1Time", data[str + "type1time"]);
            jObj_thread.insert("type2", data[str + "type2"]);
            jObj_thread.insert("type2Time", data[str + "type2time"]);
            jObj_thread.insert("init", data_str[str + "init"].replace("\n", "\\n"));
            jObj_thread.insert("step", data_str[str + "step"].replace("\n", "\\n"));

            QJsonArray jArr_bulletList;

            for(int j = 0; j < data[str + "size"]; j ++) {
                QString tmp = str + QString::number(j) + "_";
                QJsonObject jObj_bullet;

                jObj_bullet.insert("type", data[tmp + "type"]);

                jObj_bullet.insert("num", data_str[tmp + "num"].replace("\n", "\\n"));
                jObj_bullet.insert("timer_end", data_str[tmp + "timer"].replace("\n", "\\n"));
                jObj_bullet.insert("wait_timer_end", data_str[tmp + "time"].replace("\n", "\\n"));
                jObj_bullet.insert("index", map_bullet[0][data[tmp + "index"]]);

                jObj_bullet.insert("code", data_str[tmp + "code"].replace("\n", "\\n"));

                jObj_bullet.insert("x0", data_str[tmp + "x0"].replace("\n", "\\n"));
                jObj_bullet.insert("y0", data_str[tmp + "y0"].replace("\n", "\\n"));
                jObj_bullet.insert("spd", data_str[tmp + "spd"].replace("\n", "\\n"));

                if(data[tmp + "type"] == 0) { // line

                    jObj_bullet.insert("dir", data_str[tmp + "dir"].replace("\n", "\\n"));
                    jObj_bullet.insert("step", data_str[tmp + "step"].replace("\n", "\\n"));

                } else if(data[tmp + "type"] == 1) { // circle

                    jObj_bullet.insert("dir", data_str[tmp + "dir"].replace("\n", "\\n"));
                    jObj_bullet.insert("radius", data_str[tmp + "radius"].replace("\n", "\\n"));

                } else if(data[tmp + "type"] == 2) { // fan

                    jObj_bullet.insert("dir", data_str[tmp + "dir"].replace("\n", "\\n"));
                    jObj_bullet.insert("radius", data_str[tmp + "radius"].replace("\n", "\\n"));
                    jObj_bullet.insert("angle", data_str[tmp + "angle"].replace("\n", "\\n"));

                } else if(data[tmp + "type"] == 3) { // random rect

                    jObj_bullet.insert("x1", data_str[tmp + "x1"].replace("\n", "\\n"));
                    jObj_bullet.insert("y1", data_str[tmp + "y1"].replace("\n", "\\n"));

                } else if(data[tmp + "type"] == 4) { // random circle

                    jObj_bullet.insert("radius", data_str[tmp + "radius"].replace("\n", "\\n"));

                } else {

                    jObj_bullet.insert("create", data_str[tmp + "create"].replace("\n", "\\n"));
                }

                jArr_bulletList.append(jObj_bullet);
            }

            jObj_thread.insert("bulletList", jArr_bulletList);
            jArr_threadList.append(jObj_thread);
        }

        jObj->insert("threadList", jArr_threadList);
    } break;

    case THMK_EVENT_TYPE::CLS: //"清理场上弹幕和小怪";
        break;

    case THMK_EVENT_TYPE::GOTO: { //"跳转至";
        jObj->insert("condition", data_str["condition"].replace("\n", "\\n"));
        jObj->insert("t1", data["t1"]);
        jObj->insert("t2", data["t2"]);
    } break;

    case THMK_EVENT_TYPE::STAGE_CHANGE: { // "结束本关卡";
        jObj->insert("condition", data_str["condition"].replace("\n", "\\n"));
        jObj->insert("next", data["next"]);
    } break;
        break;

    case THMK_EVENT_TYPE::POINT: // "断点";
        break;

    default:
        break;
    }

}
