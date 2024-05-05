// #include "memoryCache/projectEntity/projectData.h"

// #include <QDir>
// #include <QTextStream>

// #include "memoryCache/cacheAgent.h"

// ProjectData::ProjectData() {
// }

// ProjectData::ProjectData(QString _name, QString _position) {
//     init();
//     info.projectName = _name;
//     info.projectPosition = _position;


// }

// int ProjectData::lanSize()
// {
//     return info.language.size();
// }

// void ProjectData::clear()
// {
//     info.clear();

//     text.clear();

//     ui_title.clear();

//     stage[0].clear();
//     stage[1].clear();

//     hero.clear();
//     enemy.clear();
//     boss.clear();

//     bullet[0].clear();
//     bullet[1].clear();
//     bullet[2].clear();

//     effect[0].clear();
//     effect[1].clear();
//     effect[2].clear();

//     audio[0].clear();
//     audio[1].clear();
//     audio[2].clear();

//     image[0].clear();
//     image[1].clear();
//     image[2].clear();
//     image[3].clear();

// }

// void ProjectData::init() {
//     clear();
//     info.init();
// }

// ////////////////////////////////////////////////////////// dialog


// int ProjectData::text_append(QString _text)
// {
//     int tmp = ++CacheAgent::getInstance().text_id_top;
//     text.insert(tmp, DB_text(tmp, _text));
//     return tmp;
// }

// void ProjectData::text_delete(int _index)
// {
//     auto tmp = text.find(_index);
//     if(tmp != text.end()) text.remove(tmp.key());
// }

// void ProjectData::setText(int _index, int _lan, QString _text)
// {
//     auto tmp = text.find(_index);
//     if(tmp == text.end()) tmp = text.insert(_index, DB_text());
//     tmp->setText(_lan, _text);
// }

// QString ProjectData::getText(int _index, int _lan)
// {
//     if(_index < 0) return "<undefined>";
//     auto tmp = text.find(_index);
//     if(tmp == text.end()) return "<undefined>";
//     return tmp.value().getText(_lan);
// }

// void ProjectData::stage_append(int _type, QString _name)
// {
//     stage[_type].append(DB_STAGE(++CacheAgent::getInstance().stage_id_top, _name));
// }

// void ProjectData::stage_delete_id(int _type, int _id)
// {
//     for(auto i = stage[_type].begin(); i != stage[_type].end(); i ++) {
//         if(i->id == _id) {
//             stage[_type].erase(i);
//             break;
//         }
//     }
// }

// void ProjectData::stage_delete_pos(int _type, int _pos)
// {
//     stage[_type].removeAt(_pos);
// }

// void ProjectData::hero_append(QString _name)
// {
//     int tmp = ++CacheAgent::getInstance().hero_id_top;
//     hero.insert(tmp, DB_hero(this, tmp, _name));
// }

// void ProjectData::hero_delete(int _id)
// {
//     auto tmp = hero.find(_id);
//     if(tmp != hero.end()) hero.remove(tmp.key());
// }

// void ProjectData::enemy_append(QString _name)
// {
//     int tmp = ++CacheAgent::getInstance().enemy_id_top;
//     enemy.insert(tmp, DB_enemy(tmp, _name));
// }

// void ProjectData::enemy_delete(int _id)
// {
//     auto tmp = enemy.find(_id);
//     if(tmp != enemy.end()) {
//         deleteImage(4, tmp.value().image_id);
//         enemy.remove(tmp.key());
//     }
// }

// void ProjectData::boss_append(QString _name)
// {
//     int tmp = ++CacheAgent::getInstance().boss_id_top;
//     boss.insert(tmp, DB_boss(this, tmp, _name));
// }

// void ProjectData::boss_delete(int _id)
// {
//     auto tmp = boss.find(_id);
//     if(tmp != boss.end()) boss.remove(tmp.key());
// }

// void ProjectData::bullet_append(int _type, QString _name)
// {
//     int tmp = ++CacheAgent::getInstance().bullet_id_top;
//     bullet[_type].insert(tmp, DB_bullet(tmp, _name));
// }

// void ProjectData::bullet_delete(int _type, int _id)
// {
//     auto tmp = bullet[_type].find(_id);
//     if(tmp != bullet[_type].end()) bullet[_type].remove(tmp.key());
// }

// void ProjectData::effect_append(int _type, QString _name)
// {
//     int tmp = ++CacheAgent::getInstance().effect_id_top;
//     effect[_type].insert(tmp, DB_effect(tmp, _name));
// }

// void ProjectData::effect_delete(int _type, int _id)
// {
//     auto tmp = effect[_type].find(_id);
//     if(tmp != effect[_type].end()) effect[_type].remove(tmp.key());
// }

// void ProjectData::audio_append(int _type, QString _name)
// {
//     int tmp = ++CacheAgent::getInstance().audio_id_top;
//     audio[_type].insert(tmp, DB_audio(tmp, _name));
// }

// void ProjectData::audio_delete(int _type, int _id)
// {
//     auto tmp = audio[_type].find(_id);
//     if(tmp != audio[_type].end()) audio[_type].remove(tmp.key());
// }

// void ProjectData::addImage(int _type, QString _name)
// {
//     int tmp = ++CacheAgent::getInstance().image_id_top;
//     image[_type].insert(tmp, MemoryCache::ImageInfo(tmp, _name));
// }

// void ProjectData::deleteImage(int _type, int _id)
// {
//     auto tmp = image[_type].find(_id);
//     if(tmp != image[_type].end()) image[_type].remove(tmp.key());
// }


// void ProjectData::projectInitBase()
// {
//     stage_append(0, "Stage 1");
//     stage_append(0, "Stage 2");
//     stage_append(0, "Stage 3");
//     stage_append(0, "Stage 4");
//     stage_append(0, "Stage 5");
//     stage_append(0, "Stage 6");
//     stage_append(1, "EX Stage 1");
// }

// void ProjectData::projectInitEmpty()
// {

// }

// void ProjectData::projectInitExample()
// {

// }








