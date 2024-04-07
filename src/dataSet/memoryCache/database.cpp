#include "dataSet/memoryCache/database.h"

#include <QDir>
#include <QTextStream>

#include "dataSet/cacheAgent.h"

Database::Database() {
}

Database::Database(QString _name, QString _position) {
    init();
    info.projectName = _name;
    info.projectPosition = _position;


}

int Database::lanSize()
{
    return info.language.size();
}

void Database::clear()
{
    info.clear();

    text.clear();

    ui_title.clear();

    stage[0].clear();
    stage[1].clear();

    hero.clear();
    enemy.clear();
    boss.clear();

    bullet[0].clear();
    bullet[1].clear();
    bullet[2].clear();

    effect[0].clear();
    effect[1].clear();
    effect[2].clear();

    audio[0].clear();
    audio[1].clear();
    audio[2].clear();

    image[0].clear();
    image[1].clear();
    image[2].clear();
    image[3].clear();

}

void Database::init() {
    clear();
    info.init();
}

////////////////////////////////////////////////////////// dialog


int Database::text_append(QString _text)
{
    int tmp = ++CacheAgent::getInstance().text_id_top;
    text.insert(tmp, DB_text(tmp, _text));
    return tmp;
}

void Database::text_delete(int _index)
{
    auto tmp = text.find(_index);
    if(tmp != text.end()) text.remove(tmp.key());
}

void Database::setText(int _index, int _lan, QString _text)
{
    auto tmp = text.find(_index);
    if(tmp == text.end()) tmp = text.insert(_index, DB_text());
    tmp->setText(_lan, _text);
}

QString Database::getText(int _index, int _lan)
{
    if(_index < 0) return "<undefined>";
    auto tmp = text.find(_index);
    if(tmp == text.end()) return "<undefined>";
    return tmp.value().getText(_lan);
}

void Database::stage_append(int _type, QString _name)
{
    stage[_type].append(DB_STAGE(++CacheAgent::getInstance().stage_id_top, _name));
}

// void Database::stage_delete_id(int _type, int _id)
// {
//     for(auto i = stage[_type].begin(); i != stage[_type].end(); i ++) {
//         if(i->id == _id) {
//             stage[_type].erase(i);
//             break;
//         }
//     }
// }

void Database::stage_delete_pos(int _type, int _pos)
{
    stage[_type].removeAt(_pos);
}

void Database::hero_append(QString _name)
{
    int tmp = ++CacheAgent::getInstance().hero_id_top;
    hero.insert(tmp, DB_hero(this, tmp, _name));
}

void Database::hero_delete(int _id)
{
    auto tmp = hero.find(_id);
    if(tmp != hero.end()) hero.remove(tmp.key());
}

void Database::enemy_append(QString _name)
{
    int tmp = ++CacheAgent::getInstance().enemy_id_top;
    enemy.insert(tmp, DB_enemy(tmp, _name));
}

void Database::enemy_delete(int _id)
{
    auto tmp = enemy.find(_id);
    if(tmp != enemy.end()) {
        image_delete(4, tmp.value().image_id);
        enemy.remove(tmp.key());
    }
}

void Database::boss_append(QString _name)
{
    int tmp = ++CacheAgent::getInstance().boss_id_top;
    boss.insert(tmp, DB_boss(this, tmp, _name));
}

void Database::boss_delete(int _id)
{
    auto tmp = boss.find(_id);
    if(tmp != boss.end()) boss.remove(tmp.key());
}

void Database::bullet_append(int _type, QString _name)
{
    int tmp = ++CacheAgent::getInstance().bullet_id_top;
    bullet[_type].insert(tmp, DB_bullet(tmp, _name));
}

void Database::bullet_delete(int _type, int _id)
{
    auto tmp = bullet[_type].find(_id);
    if(tmp != bullet[_type].end()) bullet[_type].remove(tmp.key());
}

void Database::effect_append(int _type, QString _name)
{
    int tmp = ++CacheAgent::getInstance().effect_id_top;
    effect[_type].insert(tmp, DB_effect(tmp, _name));
}

void Database::effect_delete(int _type, int _id)
{
    auto tmp = effect[_type].find(_id);
    if(tmp != effect[_type].end()) effect[_type].remove(tmp.key());
}

void Database::audio_append(int _type, QString _name)
{
    int tmp = ++CacheAgent::getInstance().audio_id_top;
    audio[_type].insert(tmp, DB_audio(tmp, _name));
}

void Database::audio_delete(int _type, int _id)
{
    auto tmp = audio[_type].find(_id);
    if(tmp != audio[_type].end()) audio[_type].remove(tmp.key());
}

void Database::image_append(int _type, QString _name)
{
    int tmp = ++CacheAgent::getInstance().image_id_top;
    image[_type].insert(tmp, DB_image(tmp, _name));
}

void Database::image_delete(int _type, int _id)
{
    auto tmp = image[_type].find(_id);
    if(tmp != image[_type].end()) image[_type].remove(tmp.key());
}


void Database::projectInitBase()
{
    stage_append(0, "Stage 1");
    stage_append(0, "Stage 2");
    stage_append(0, "Stage 3");
    stage_append(0, "Stage 4");
    stage_append(0, "Stage 5");
    stage_append(0, "Stage 6");
    stage_append(1, "EX Stage 1");
}

void Database::projectInitEmpty()
{

}

void Database::projectInitExample()
{

}








