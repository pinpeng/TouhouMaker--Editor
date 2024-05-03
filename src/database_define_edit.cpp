#include "database_define.h"

#include "window_editor_menubar_bullet_edit.h"
#include "window_editor_menubar_effect_edit.h"
#include "window_editor_menubar_hero_edit.h"

#include "window_ask.h"

void DB_bullet::init()
{
    data["type"] = 0;
    data["range"] = 0;
    data["collision"] = 4;
    data["stage"] = 0;
    updateData();
}


void DB_bullet::updateData()
{
    for(int i = 0; i < 20; i ++) {
        QString tmp = QString::number(i) + "_";
        if(i < data["stage"]) {
            if(data.find(tmp + "type") == data.end()) {
                data[tmp + "event"] = 0;
                data[tmp + "type"] = 0;
                data[tmp + "time"] = 1;
                data_str[tmp + "init"] = "val1 = 0\nval2 = 0";
                data_str[tmp + "step"] = "val1 = val1 + 1\nval2 = val2 + 2";
            }
        } else {
            if(data.find(tmp + "type") != data.end()) {
                data.remove(tmp + "type");
            }
        }
    }

    for(int i = 0; i < data["stage"]; i ++) {
        QString tmp = QString::number(i) + "_";

        while(data[tmp + "event"]) {
            QString tmp1 = tmp + QString::number(data[tmp + "event"] - 1) + "_type";
            if(data.find(tmp1) == data.end() || data[tmp1] == -1) {
                data[tmp + "event"] --;
                data.remove(tmp1);
            } else break;
        }

        for(int j = 0; j < data[tmp + "event"]; j ++) {
            QString tmp1 = tmp + QString::number(j) + "_";
            if(!data[tmp1 + "inited"]) {
                data[tmp1 + "inited"] = 1;
                if(data[tmp1 + "condition"] == 0) {
                    data_str[tmp1 + "condition"] = "true";
                } else if(data[tmp1 + "condition"] == 1) {
                    data_str[tmp1 + "condition"] = "timer == 1";
                } else if(data[tmp1 + "condition"] == 2) {
                    data_str[tmp1 + "condition"] = "timer == timer_end";
                } else {
                    data_str[tmp1 + "condition"] = "false";
                }
                if(data[tmp1 + "type"] == 0) {
                    data_str[tmp1 + "code"] = "destroy()";
                } else if(data[tmp1 + "type"] == 1) {
                    data_str[tmp1 + "code"] = "bullet_create(\"<子弹名称>\", x, y, dir, spd)";
                } else if(data[tmp1 + "type"] == 2) {
                    data_str[tmp1 + "code"] = "effect_create(\"<特效名称>\", x, y, <强度>)";
                } else if(data[tmp1 + "type"] == 3) {
                    data_str[tmp1 + "code"] = "stage = <阶段号>";
                } else {
                    data_str[tmp1 + "code"] = "";
                }
            }

        }
    }

}

void DB_bullet::renderCode(Window_editor_menubar_bullet_edit *window, ProjectData *db, QRectF _rect, float *_line, int _group)
{

    int line_show_max = floor(_rect.height() / 40) - 2;
    float mid_x = _rect.left() + 16;
    float mid_y = _rect.top() + 24;
    float line_num = 0;
    setPenColor_c(c_theme);
    Draw::text(mid_x, mid_y, "共有" + QString::number(data["stage"]) + "个阶段", Qt::AlignLeft | Qt::AlignVCenter);
    setPenColor_c(c_symbol);
    Draw::line(_rect.left() + 8, mid_y + 20, _rect.right() - 8, mid_y + 20, 2);

    int line_max = 0;
    for(int i = 0; i < data["stage"]; i ++) {
        QString tmp = QString::number(i) + "_";
        line_max += 3;
        for(int j = 0; j < data[tmp + "event"]; j ++) {
            QString tmp1 = tmp + QString::number(j) + "_type";
            if(data.find(tmp1) != data.end() && data[tmp1] != -1) line_max += 1;
        }
    }

    setPenColor_false();
    float _t = _rect.top() + 56;
    float _b = _rect.bottom() - 12;
    float _r = _rect.right() - 12;
    setBrushColor_c(c_symbol);
    Draw::circle(_r, _t, 4);
    Draw::rect(_r - 4, _t, _r + 4, _b);
    Draw::circle(_r, _b, 4);
    setBrushColor_c(c_theme);
    if(line_max <= 2) {
        Draw::circle(_r, _t, 4);
        Draw::rect(_r - 4, _t, _r + 4, _b);
        Draw::circle(_r, _b, 4);
    } else {
        Draw::circle(_r, _t + (_b - _t) * (*_line / line_max), 4);
        Draw::rect(_r - 4, _t + (_b - _t) * (*_line / line_max),
                   _r + 4, _t + (_b - _t) * qBound(0.0f, (*_line + line_show_max) / (line_max - 1), 1.0f), 4);
        Draw::circle(_r, _t + (_b - _t) * qBound(0.0f, (*_line + line_show_max) / (line_max - 1), 1.0f), 4);
    }

    for(int i = 0; i < data["stage"]; i ++) {
        QString tmp = QString::number(i) + "_";
        //if(data.find(tmp) == data.end()) continue;

        if(line_num > *_line + line_show_max) return;
        if(line_num >= *_line) {
            if(line_num != *_line) {
                setPenColor_c(c_symbol);
                Draw::line(_rect.left() + 8, mid_y + 20, _rect.right() - 28, mid_y + 20, 2);
            }
            mid_y += 40;
            setPenColor_c(c_theme);
            if(data[tmp + "type"] == 0) {
                Draw::text(mid_x, mid_y, "阶段" + QString::number(i + 1) + "，无限持续", Qt::AlignLeft | Qt::AlignVCenter);
            } else {
                Draw::text(mid_x, mid_y, "阶段" + QString::number(i + 1) + "，持续时间为" + QString::number(data[tmp + "time"]) + "分秒",
                           Qt::AlignLeft | Qt::AlignVCenter);
            }
        }
        line_num ++;

        setPenColor_c(c_textMain);
        for(int j = 0; j < data[tmp + "event"]; j ++) {
            QString tmp1 = tmp + QString::number(j) + "_";

            if(data.find(tmp1 + "type") == data.end() || data[tmp1 + "type"] == -1) continue;

            if(line_num > *_line + line_show_max) return;
            if(line_num >= *_line) {

                mid_y += 40;
                QString _text = "若条件 " + data_str[tmp1 + "condition"] + " 成立，则：" + data_str[tmp1 + "code"].replace("\n", "\\n");
                if(j >= data[tmp + "event"] - 1) _text = "(X) " + _text;

                Draw::text(mid_x, mid_y, _text, Qt::AlignLeft | Qt::AlignVCenter);
            }
            line_num ++;
        }

        if(line_num > *_line + line_show_max) return;
        if(line_num >= *_line) {
            mid_y += 40;
            setPenColor_c(c_theme);
            Draw::text(mid_x, mid_y, "点此添加特殊事件...", Qt::AlignLeft | Qt::AlignVCenter);
        }
        line_num ++;
    }

}

bool DB_bullet::editCode(Window_editor_menubar_bullet_edit *window, ProjectData *db, QRectF _rect, float *_line, float mx, float my, int _group)
{
    static QStringList _type = {"无限持续", "有限时间"};

    static QStringList _addCondition = {"无条件", "阶段开始", "阶段结束"};
    static QStringList _addType = {"消失", "生成新子弹", "发射特效", "改变阶段", "自定义"};

    int line_show_max = floor(_rect.height() / 40) - 1;
    float mid_x = _rect.left() + 16;
    float mid_y = _rect.top() + 24;
    float line_num = 0;
    if(abs(my - mid_y) < 20) {
        ask_create("设置阶段数");
        ask_add_lineEdit_int("阶段数量", &data["stage"], 0, 20);
        window->connect(window_ask_ex, SIGNAL(closed()), window, SLOT(updateData()));
    }

    for(int i = 0; i < data["stage"]; i ++) {
        QString tmp = QString::number(i) + "_";

        if(line_num > *_line + line_show_max) return false;
        if(line_num >= *_line) {
            mid_y += 40;
            if(abs(mid_y - my) < 20) {
                ask_create("设置阶段");
                ask_set_page_number(2);

                ask_set_current_page(0);
                ask_add_chooseButton("阶段持续方式", &data[tmp + "type"], _type);
                ask_add_textEdit("在此输入初始化代码...", &data_str[tmp + "init"]);

                ask_set_current_page(1);
                ask_add_lineEdit_int("持续时间（分秒）", &data[tmp + "time"], 1, 3599);
                ask_add_textEdit("在此输入步事件代码...", &data_str[tmp + "step"]);

                return false;
            }
        }
        line_num ++;

        for(int j = 0; j < data[tmp + "event"]; j ++) {
            QString tmp1 = tmp + QString::number(j) + "_";

            if(data.find(tmp1 + "type") == data.end() || data[tmp1 + "type"] == -1) continue;

            if(line_num > *_line + line_show_max) return false;
            if(line_num >= *_line) {
                QString tmp1 = tmp + QString::number(j) + "_";

                mid_y += 40;
                if(abs(mid_y - my) < 20) {
                    if(j >= data[tmp + "event"] - 1) {
                        if(abs(mid_y - my) < 20 && mid_x - 8 < mx && mx < mid_x + 48) {
                            data[tmp1 + "type"] = -1;
                            data[tmp + "event"] --;
                            updateData();
                            return true;
                        } else {
                            ask_create("设置事件");
                            ask_add_lineEdit_str("条件为", &data_str[tmp1 + "condition"]);
                            ask_add_textEdit("在此输入执行代码...", &data_str[tmp1 + "code"]);
                        }
                    } else {
                        ask_create("设置事件");
                        ask_add_lineEdit_str("条件为", &data_str[tmp1 + "condition"]);
                        ask_add_textEdit("在此输入执行代码...", &data_str[tmp1 + "code"]);
                    }
                    return false;
                }
            }
            line_num ++;
        }

        if(line_num > *_line + line_show_max) return false;
        if(line_num >= *_line) {
            mid_y += 40;
            if(abs(mid_y - my) < 20) {
                data[tmp + "event"] ++;
                QString tmp1 = tmp + QString::number(data[tmp + "event"] - 1) + "_";
                data[tmp1 + "inited"] = 0;
                data[tmp1 + "type"] = -1;
                data[tmp1 + "condition"] = -1;
                ask_create("添加事件");
                ask_add_chooseButton("条件", &data[tmp1 + "condition"], _addCondition);
                ask_add_chooseButton("类型", &data[tmp1 + "type"], _addType);
                window->connect(window_ask_ex, SIGNAL(closed()), window, SLOT(updateData()));
            }
        }
        line_num ++;
    }
    return false;
}

void DB_bullet::wheelEvent(Window_editor_menubar_bullet_edit *window, ProjectData *db, QRectF _rect, float *_line)
{
    int line_show_max = floor(_rect.height() / 40) - 2;
    int line_max = 0;
    for(int i = 0; i < data["stage"]; i ++) {
        QString tmp = QString::number(i) + "_";
        line_max += 2;
        for(int j = 0; j < data[tmp + "event"]; j ++) {
            QString tmp1 = tmp + QString::number(j) + "_type";
            if(data.find(tmp1) != data.end() && data[tmp1] != -1) line_max += 1;
        }
    }
    *_line = qBound(0.0f, *_line, float(line_max - line_show_max - 1));
}

void DB_bullet::toJson(int _group, QMap<int, int> map_text, QMap<int, int> map_hero, QMap<int, int> map_enemy, QMap<int, int> map_boss, QMap<int, int> map_bullet[], QMap<int, int> map_effect[], QMap<int, int> map_audio[], QMap<int, int> map_image[], QJsonObject *jObj)
{
    jObj->insert("type",          data["type"]);
    jObj->insert("range",       data["range"]);
    jObj->insert("collision",   data["collision"]);
    jObj->insert("stage",       data["stage"]);

    QJsonArray jArr_stage_list;

    for(int i = 0; i < data["stage"]; i ++) {
        QJsonObject jObj_stage;
        QString tmp = QString::number(i) + "_";

        jObj_stage.insert("event",       data[tmp + "event"]);
        jObj_stage.insert("type",        data[tmp + "type"]);
        jObj_stage.insert("time",        data[tmp + "time"]);

        jObj_stage.insert("init",    data_str[tmp + "init"].replace("\n", "\\n"));
        jObj_stage.insert("step",    data_str[tmp + "step"].replace("\n", "\\n"));

        QJsonArray jArr_event_list;

        for(int j = 0; j < data[tmp + "event"]; j ++) {
            QJsonObject jObj_event;
            QString tmp1 = tmp + QString::number(i) + "_";

            jObj_event.insert("condition",   data_str[tmp1 + "condition"].replace("\n", "\\n"));
            jObj_event.insert("code",   data_str[tmp1 + "code"].replace("\n", "\\n"));

            jArr_event_list.append(jObj_event);
        }

        jObj_stage.insert("eventList", jArr_event_list);

        jArr_stage_list.append(jObj_stage);
    }

    jObj->insert("stageList", jArr_stage_list);
}

void DB_enemy::init()
{
    data["hp"] = 10;
    data["range"] = 0;
    data["collision"] = 8;
    data["stage"] = 0;
    updateData();
}

void DB_enemy::updateData()
{
    for(int i = 0; i < 20; i ++) {
        QString tmp = QString::number(i) + "_";
        if(i < data["stage"]) {
            if(data.find(tmp + "type") == data.end()) {
                data[tmp + "event"] = 0;
                data[tmp + "type"] = 0;
                data[tmp + "time"] = 1;
                data_str[tmp + "init"] = "val1 = 0\nval2 = 0";
                data_str[tmp + "step"] = "val1 = val1 + 1\nval2 = val2 + 2";
            }
        } else {
            if(data.find(tmp + "type") != data.end()) {
                data.remove(tmp + "type");
            }
        }
    }

    for(int i = 0; i < data["stage"]; i ++) {
        QString tmp = QString::number(i) + "_";

        while(data[tmp + "event"]) {
            QString tmp1 = tmp + QString::number(data[tmp + "event"] - 1) + "_type";
            if(data.find(tmp1) == data.end() || data[tmp1] == -1) {
                data[tmp + "event"] --;
                data.remove(tmp1);
            } else break;
        }

        for(int j = 0; j < data[tmp + "event"]; j ++) {
            QString tmp1 = tmp + QString::number(j) + "_";
            if(!data[tmp1 + "inited"]) {
                data[tmp1 + "inited"] = 1;
                if(data[tmp1 + "condition"] == 0) {
                    data_str[tmp1 + "condition"] = "true";
                } else if(data[tmp1 + "condition"] == 1) {
                    data_str[tmp1 + "condition"] = "timer == 1";
                } else if(data[tmp1 + "condition"] == 2) {
                    data_str[tmp1 + "condition"] = "timer == timer_end";
                } else {
                    data_str[tmp1 + "condition"] = "false";
                }
                if(data[tmp1 + "type"] == 0) {
                    data_str[tmp1 + "code"] = "destroy()";
                } else if(data[tmp1 + "type"] == 1) {
                    data_str[tmp1 + "code"] = "bullet_create(\"<子弹名称>\", x, y, dir, spd)";
                } else if(data[tmp1 + "type"] == 2) {
                    data_str[tmp1 + "code"] = "effect_create(\"<特效名称>\", x, y, <强度>)";
                } else if(data[tmp1 + "type"] == 3) {
                    data_str[tmp1 + "code"] = "stage = <阶段号>";
                } else {
                    data_str[tmp1 + "code"] = "";
                }
            }

        }
    }

}

void DB_enemy::renderCode(Window_editor_menubar_hero_edit1 *window, ProjectData *db, QRectF _rect, float *_line)
{

    int line_show_max = floor(_rect.height() / 40) - 2;
    float mid_x = _rect.left() + 16;
    float mid_y = _rect.top() + 24;
    float line_num = 0;
    setPenColor_c(c_theme);
    Draw::text(mid_x, mid_y, "共有" + QString::number(data["stage"]) + "个阶段", Qt::AlignLeft | Qt::AlignVCenter);
    setPenColor_c(c_symbol);
    Draw::line(_rect.left() + 8, mid_y + 20, _rect.right() - 8, mid_y + 20, 2);

    int line_max = 0;
    for(int i = 0; i < data["stage"]; i ++) {
        QString tmp = QString::number(i) + "_";
        line_max += 3;
        for(int j = 0; j < data[tmp + "event"]; j ++) {
            QString tmp1 = tmp + QString::number(j) + "_type";
            if(data.find(tmp1) != data.end() && data[tmp1] != -1) line_max += 1;
        }
    }

    setPenColor_false();
    float _t = _rect.top() + 56;
    float _b = _rect.bottom() - 12;
    float _r = _rect.right() - 12;
    setBrushColor_c(c_symbol);
    Draw::circle(_r, _t, 4);
    Draw::rect(_r - 4, _t, _r + 4, _b);
    Draw::circle(_r, _b, 4);
    setBrushColor_c(c_theme);
    if(line_max <= 2) {
        Draw::circle(_r, _t, 4);
        Draw::rect(_r - 4, _t, _r + 4, _b);
        Draw::circle(_r, _b, 4);
    } else {
        Draw::circle(_r, _t + (_b - _t) * (*_line / line_max), 4);
        Draw::rect(_r - 4, _t + (_b - _t) * (*_line / line_max),
                   _r + 4, _t + (_b - _t) * qBound(0.0f, (*_line + line_show_max) / (line_max - 1), 1.0f), 4);
        Draw::circle(_r, _t + (_b - _t) * qBound(0.0f, (*_line + line_show_max) / (line_max - 1), 1.0f), 4);
    }

    for(int i = 0; i < data["stage"]; i ++) {
        QString tmp = QString::number(i) + "_";
        //if(data.find(tmp) == data.end()) continue;

        if(line_num > *_line + line_show_max) return;
        if(line_num >= *_line) {
            if(line_num != *_line) {
                setPenColor_c(c_symbol);
                Draw::line(_rect.left() + 8, mid_y + 20, _rect.right() - 28, mid_y + 20, 2);
            }
            mid_y += 40;
            setPenColor_c(c_theme);
            if(data[tmp + "type"] == 0) {
                Draw::text(mid_x, mid_y, "阶段" + QString::number(i + 1) + "，无限持续", Qt::AlignLeft | Qt::AlignVCenter);
            } else {
                Draw::text(mid_x, mid_y, "阶段" + QString::number(i + 1) + "，持续时间为" + QString::number(data[tmp + "time"]) + "分秒",
                           Qt::AlignLeft | Qt::AlignVCenter);
            }
        }
        line_num ++;

        setPenColor_c(c_textMain);
        for(int j = 0; j < data[tmp + "event"]; j ++) {
            QString tmp1 = tmp + QString::number(j) + "_";

            if(data.find(tmp1 + "type") == data.end() || data[tmp1 + "type"] == -1) continue;

            if(line_num > *_line + line_show_max) return;
            if(line_num >= *_line) {

                mid_y += 40;
                QString _text = "若条件 " + data_str[tmp1 + "condition"] + " 成立，则：" + data_str[tmp1 + "code"].replace("\n", "\\n");
                if(j >= data[tmp + "event"] - 1) _text = "(X) " + _text;

                Draw::text(mid_x, mid_y, _text, Qt::AlignLeft | Qt::AlignVCenter);
            }
            line_num ++;
        }

        if(line_num > *_line + line_show_max) return;
        if(line_num >= *_line) {
            mid_y += 40;
            setPenColor_c(c_theme);
            Draw::text(mid_x, mid_y, "点此添加特殊事件...", Qt::AlignLeft | Qt::AlignVCenter);
        }
        line_num ++;
    }


}

bool DB_enemy::editCode(Window_editor_menubar_hero_edit1 *window, ProjectData *db, QRectF _rect, float *_line, float mx, float my)
{
    static QStringList _type = {"无限持续", "有限时间"};

    static QStringList _addCondition = {"无条件", "阶段开始", "阶段结束"};
    static QStringList _addType = {"消失", "生成新子弹", "发射特效", "改变阶段", "自定义"};

    int line_show_max = floor(_rect.height() / 40) - 1;
    float mid_x = _rect.left() + 16;
    float mid_y = _rect.top() + 24;
    float line_num = 0;
    if(abs(my - mid_y) < 20) {
        ask_create("设置阶段数");
        ask_add_lineEdit_int("阶段数量", &data["stage"], 0, 20);
        window->connect(window_ask_ex, SIGNAL(closed()), window, SLOT(updateData()));
    }

    for(int i = 0; i < data["stage"]; i ++) {
        QString tmp = QString::number(i) + "_";

        if(line_num > *_line + line_show_max) return false;
        if(line_num >= *_line) {
            mid_y += 40;
            if(abs(mid_y - my) < 20) {
                ask_create("设置阶段");
                ask_set_page_number(2);

                ask_set_current_page(0);
                ask_add_chooseButton("阶段持续方式", &data[tmp + "type"], _type);
                ask_add_textEdit("在此输入初始化代码...", &data_str[tmp + "init"]);

                ask_set_current_page(1);
                ask_add_lineEdit_int("持续时间（分秒）", &data[tmp + "time"], 1, 3599);
                ask_add_textEdit("在此输入步事件代码...", &data_str[tmp + "step"]);

                return false;
            }
        }
        line_num ++;

        for(int j = 0; j < data[tmp + "event"]; j ++) {
            QString tmp1 = tmp + QString::number(j) + "_";

            if(data.find(tmp1 + "type") == data.end() || data[tmp1 + "type"] == -1) continue;

            if(line_num > *_line + line_show_max) return false;
            if(line_num >= *_line) {
                QString tmp1 = tmp + QString::number(j) + "_";

                mid_y += 40;
                if(abs(mid_y - my) < 20) {
                    if(j >= data[tmp + "event"] - 1) {
                        if(abs(mid_y - my) < 20 && mid_x - 8 < mx && mx < mid_x + 48) {
                            data[tmp1 + "type"] = -1;
                            data[tmp + "event"] --;
                            updateData();
                            return true;
                        } else {
                            ask_create("设置事件");
                            ask_add_lineEdit_str("条件为", &data_str[tmp1 + "condition"]);
                            ask_add_textEdit("在此输入执行代码...", &data_str[tmp1 + "code"]);
                        }
                    } else {
                        ask_create("设置事件");
                        ask_add_lineEdit_str("条件为", &data_str[tmp1 + "condition"]);
                        ask_add_textEdit("在此输入执行代码...", &data_str[tmp1 + "code"]);
                    }
                    return false;
                }
            }
            line_num ++;
        }

        if(line_num > *_line + line_show_max) return false;
        if(line_num >= *_line) {
            mid_y += 40;
            if(abs(mid_y - my) < 20) {
                data[tmp + "event"] ++;
                QString tmp1 = tmp + QString::number(data[tmp + "event"] - 1) + "_";
                data[tmp1 + "inited"] = 0;
                data[tmp1 + "type"] = -1;
                data[tmp1 + "condition"] = -1;
                ask_create("添加事件");
                ask_add_chooseButton("条件", &data[tmp1 + "condition"], _addCondition);
                ask_add_chooseButton("类型", &data[tmp1 + "type"], _addType);
                window->connect(window_ask_ex, SIGNAL(closed()), window, SLOT(updateData()));
            }
        }
        line_num ++;
    }
    return false;
}

void DB_enemy::wheelEvent(Window_editor_menubar_hero_edit1 *window, ProjectData *db, QRectF _rect, float *_line)
{
    int line_show_max = floor(_rect.height() / 40) - 2;
    int line_max = 0;
    for(int i = 0; i < data["stage"]; i ++) {
        QString tmp = QString::number(i) + "_";
        line_max += 2;
        for(int j = 0; j < data[tmp + "event"]; j ++) {
            QString tmp1 = tmp + QString::number(j) + "_type";
            if(data.find(tmp1) != data.end() && data[tmp1] != -1) line_max += 1;
        }
    }
    *_line = qBound(0.0f, *_line, float(line_max - line_show_max - 1));
}

void DB_enemy::toJson(QMap<int, int> map_text, QMap<int, int> map_hero, QMap<int, int> map_enemy, QMap<int, int> map_boss, QMap<int, int> map_bullet[], QMap<int, int> map_effect[], QMap<int, int> map_audio[], QMap<int, int> map_image[], QJsonObject *jObj)
{
    jObj->insert("hp",        data["hp"]);
    jObj->insert("range",       data["range"]);
    jObj->insert("collision",   data["collision"]);
    jObj->insert("stage",       data["stage"]);

    QJsonArray jArr_stage_list;

    for(int i = 0; i < data["stage"]; i ++) {
        QJsonObject jObj_stage;
        QString tmp = QString::number(i) + "_";

        jObj_stage.insert("event",       data[tmp + "event"]);
        jObj_stage.insert("type",        data[tmp + "type"]);
        jObj_stage.insert("time",        data[tmp + "time"]);

        jObj_stage.insert("init",    data_str[tmp + "init"].replace("\n", "\\n"));
        jObj_stage.insert("step",    data_str[tmp + "step"].replace("\n", "\\n"));

        QJsonArray jArr_event_list;

        for(int j = 0; j < data[tmp + "event"]; j ++) {
            QJsonObject jObj_event;
            QString tmp1 = tmp + QString::number(i) + "_";

            jObj_event.insert("condition",   data_str[tmp1 + "condition"].replace("\n", "\\n"));
            jObj_event.insert("code",   data_str[tmp1 + "code"].replace("\n", "\\n"));

            jArr_event_list.append(jObj_event);
        }

        jObj_stage.insert("eventList", jArr_event_list);

        jArr_stage_list.append(jObj_stage);
    }

    jObj->insert("stageList", jArr_stage_list);
}


void DB_effect::init()
{

}

void DB_effect::renderCode(Window_editor_menubar_effect_edit *window, ProjectData *db, QRectF _rect, float *_line)
{

}

bool DB_effect::editCode(Window_editor_menubar_effect_edit *window, ProjectData *db, QRectF _rect, float *_line, float mx, float my)
{

}

void DB_effect::wheelEvent(Window_editor_menubar_effect_edit *window, ProjectData *db, QRectF _rect, float *_line)
{

}

