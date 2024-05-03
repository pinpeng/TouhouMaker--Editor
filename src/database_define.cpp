#include "database_define.h"

#include "memoryCache/cacheAgent.h"
#include <QDir>


DB_text::DB_text()
{
}

DB_text::DB_text(int _id, QString _text)
{
    __id = _id;
    while(__text.length() < CacheAgent::getInstance().databaseLanSize()) __text.append("<undefined>");
    __text[0] = _text;
}

QString DB_text::getText(int _lan)
{
    while(__text.length() < CacheAgent::getInstance().databaseLanSize()) __text.append("");
    while(__text.length() > CacheAgent::getInstance().databaseLanSize()) __text.pop_back();

    return __text[_lan];
}

void DB_text::setText(int _lan, QString _text)
{
    while(__text.length() < CacheAgent::getInstance().databaseLanSize()) __text.append("");
    while(__text.length() > CacheAgent::getInstance().databaseLanSize()) __text.pop_back();

    __text[_lan] = _text;
}


DB_hero_bullet::DB_hero_bullet()
{

}

DB_hero_skill::DB_hero_skill()
{

}

DB_hero_skill::DB_hero_skill(ProjectData *db, QString _name)
{
    name = db->text_append(_name);
}

DB_hero::DB_hero() {

}

DB_hero::DB_hero(ProjectData *db, int _id, QString _name)
{
    __id = _id;
    name = db->text_append(_name);
    bullet[0] = DB_hero_bullet();
    bullet[1] = DB_hero_bullet();
    skill[0] = DB_hero_skill(db, "新建符卡");
    skill[1] = DB_hero_skill(db, "新建符卡");
    image_id[0] = -1;
    image_id[1] = -1;
    image_id[2] = -1;
    image_id[3] = -1;
    image_id[4] = -1;
    image_id[5] = -1;

    bullet_type = 0;
    skill_type = 0;
}

DB_enemy::DB_enemy()
{
    __id = 0;
    name = "";
    image_id = -1;
    init();
}

DB_enemy::DB_enemy(int _id, QString _name)
{
    __id = _id;
    name = _name;
    image_id = -1;
    init();
}

DB_boss::DB_boss()
{
    __id = 0;
    name = -1;
    image_id[0] = -1;
    image_id[1] = -1;
    image_id[2] = -1;
}

DB_boss::DB_boss(ProjectData *db, int _id, QString _name)
{
    __id = _id;
    name = db->text_append(_name);
    image_id[0] = -1;
    image_id[1] = -1;
    image_id[2] = -1;
}

DB_bullet::DB_bullet()
{
    __id = 0;
    name = "";
    image_id = -1;
    init();
}

DB_bullet::DB_bullet(int _id, QString _name)
{
    __id = _id;
    name = _name;
    image_id = -1;
    init();
}

DB_effect::DB_effect()
{
    __id = 0;
    name = "";
    init();
}

DB_effect::DB_effect(int _id, QString _name)
{
    __id = _id;
    name = _name;
    init();
}

DB_audio::DB_audio()
{
    __id = 0;
    name = "";
    state = 0;
}

DB_audio::DB_audio(int _id, QString _name)
{
    __id = _id;
    name = _name;
    state = 0;
}

DB_image::DB_image()
{
    __id = 0;
    name = "";
    state = 0;
    editTimer = 0;
}

DB_image::DB_image(int _id, QString _name)
{
    __id = _id;
    name = _name;
    state = 0;
    editTimer = 0;
}
