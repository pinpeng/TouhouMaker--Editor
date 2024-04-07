#include "dataSet/memoryCache/database.h"

#include <QDir>
#include <QTextStream>
#include <QPainter>

#include <QBuffer>

#include "draw.h"

#include "dataSet/cacheAgent.h"

#include "qzipwriter_p.h"

#include <QJsonDocument>
#include <QJsonArray>

bool Database::read(QString basePath) {
    clear();

    if(!QDir(basePath).exists()) return 1;
    QFile file;
    QTextStream fin;

    file.setFileName(basePath + "/index.thmkproj");
    if(!file.open(QIODevice::ReadOnly)) return 1; fin.setDevice(&file);

    info.projectName = fin.readLine();
    CacheAgent::getInstance().stage_id_top = fin.readLine().toInt();
    CacheAgent::getInstance().stage_event_id_top = fin.readLine().toInt();

    CacheAgent::getInstance().text_id_top = fin.readLine().toInt();
    CacheAgent::getInstance().hero_id_top = fin.readLine().toInt();
    CacheAgent::getInstance().enemy_id_top = fin.readLine().toInt();
    CacheAgent::getInstance().boss_id_top = fin.readLine().toInt();
    CacheAgent::getInstance().bullet_id_top = fin.readLine().toInt();
    CacheAgent::getInstance().effect_id_top = fin.readLine().toInt();
    CacheAgent::getInstance().audio_id_top = fin.readLine().toInt();
    CacheAgent::getInstance().image_id_top = fin.readLine().toInt();

    int tmp_text_size = fin.readLine().toInt();
    int tmp_stage_size[2];
    tmp_stage_size[0] = fin.readLine().toInt();
    tmp_stage_size[1] = fin.readLine().toInt();

    int tmp_hero_size = fin.readLine().toInt();
    int tmp_enemy_size = fin.readLine().toInt();
    int tmp_boss_size = fin.readLine().toInt();

    int tmp_bullet_size[3];
    tmp_bullet_size[0] = fin.readLine().toInt();
    tmp_bullet_size[1] = fin.readLine().toInt();
    tmp_bullet_size[2] = fin.readLine().toInt();

    int tmp_effect_size[3];
    tmp_effect_size[0] = fin.readLine().toInt();
    tmp_effect_size[1] = fin.readLine().toInt();
    tmp_effect_size[2] = fin.readLine().toInt();

    int tmp_audio_size[3];
    tmp_audio_size[0] = fin.readLine().toInt();
    tmp_audio_size[1] = fin.readLine().toInt();
    tmp_audio_size[2] = fin.readLine().toInt();

    int tmp_image_size[5];
    tmp_image_size[0] = fin.readLine().toInt();
    tmp_image_size[1] = fin.readLine().toInt();
    tmp_image_size[2] = fin.readLine().toInt();
    tmp_image_size[3] = fin.readLine().toInt();
    tmp_image_size[4] = fin.readLine().toInt();

    file.close();

    file.setFileName(basePath + "/info.txt");
    if(!file.open(QIODevice::ReadOnly)) return 1; fin.setDevice(&file);

    info.projectName = fin.readLine();
    if(info.projectName.isEmpty()) info.projectName = "New Project";
    /*info.setting_ra.ra_image1 = fin.readLine().toInt();
    info.setting_ra.ra_image2 = fin.readLine().toInt();
    info.setting_ra.ra_image3 = fin.readLine().toInt();
    info.setting_ra.ra_audio1 = fin.readLine().toInt();
    info.setting_ra.ra_audio2 = fin.readLine().toInt();
    info.setting_ra.ra_audio3 = fin.readLine().toInt();
    info.setting_ra.ra_video1 = fin.readLine().toInt();
    info.setting_ra.ra_video2 = fin.readLine().toInt();
    info.setting_ra.ra_video3 = fin.readLine().toInt();
    info.setting_ra.ra_dictionary = fin.readLine().toInt();
    info.setting_ra.ra_character = fin.readLine().toInt();

    info.setting_start_with_logo = fin.readLine().toInt();
    info.setting_reading_aciton = fin.readLine().toInt();
    info.setting_using_cg_collection = fin.readLine().toInt();*/

    file.close();

    file.setFileName(basePath + "/language.txt");
    if(!file.open(QIODevice::ReadOnly)) return 1; fin.setDevice(&file);
    int tmp_language_size = fin.readLine().toInt();
    for(int i = 0; i < tmp_language_size; i ++) info.language.append(fin.readLine());
    file.close();


    file.setFileName(basePath + "/ui/index.txt");
    if(!file.open(QIODevice::ReadOnly)) return 1; fin.setDevice(&file);

    file.close();

    file.setFileName(basePath + "/stage/index0.txt");
    if(!file.open(QIODevice::ReadOnly)) return 1; fin.setDevice(&file);
    for(int i = 0; i < tmp_stage_size[0]; i ++) {
        // 读取关卡数据
        DB_STAGE _stage;
        _stage._stageId = fin.readLine().toInt();
        _stage.name = fin.readLine();
        _stage.length = fin.readLine().toInt();
        int _events_size = fin.readLine().toInt();
        // 从关卡数据中读取事件数据
        for(int j = 0; j < _events_size; j ++) {
            DB_STAGE_EVENT _event;
            _event.id = fin.readLine().toInt();
            _event.time = fin.readLine().toInt();
            _event.type = fin.readLine().toInt();
            int _data_size = fin.readLine().toInt();
            for(int k = 0; k < _data_size; k ++) {
                QString _tmp0 = fin.readLine();
                int _tmp1 = fin.readLine().toFloat();
                _event.data[_tmp0] = _tmp1;
            }
            int _data_str_size = fin.readLine().toInt();
            for(int j = 0; j < _data_str_size; j ++) {
                QString _tmp0 = fin.readLine();
                QString _tmp1 = fin.readLine().replace("\\n", "\n");
                _event.data_str[_tmp0] = _tmp1;
            }
            _stage.events.append(_event);
        }
        stage[0].append(_stage);
    }
    file.close();

    file.setFileName(basePath + "/stage/index1.txt");
    if(!file.open(QIODevice::ReadOnly)) return 1; fin.setDevice(&file);
    for(int i = 0; i < tmp_stage_size[1]; i ++) {
        DB_STAGE _stage;
        _stage._stageId = fin.readLine().toInt();
        _stage.name = fin.readLine();
        _stage.length = fin.readLine().toInt();
        int _events_size = fin.readLine().toInt();
        for(int j = 0; j < _events_size; j ++) {
            DB_STAGE_EVENT _event;
            _event.id = fin.readLine().toInt();
            _event.time = fin.readLine().toInt();
            _event.type = fin.readLine().toInt();
            int _data_size = fin.readLine().toInt();
            for(int k = 0; k < _data_size; k ++) {
                QString _tmp0 = fin.readLine();
                int _tmp1 = fin.readLine().toFloat();
                _event.data[_tmp0] = _tmp1;
            }
            int _data_str_size = fin.readLine().toInt();
            for(int j = 0; j < _data_str_size; j ++) {
                QString _tmp0 = fin.readLine();
                QString _tmp1 = fin.readLine().replace("\\n", "\n");
                _event.data_str[_tmp0] = _tmp1;
            }
            _stage.events.append(_event);
        }
        stage[1].append(_stage);
    }
    file.close();

    file.setFileName(basePath + "/hero/index.txt");
    if(!file.open(QIODevice::ReadOnly)) return 1; fin.setDevice(&file);

    file.close();

    file.setFileName(basePath + "/enemy/index.txt");
    if(!file.open(QIODevice::ReadOnly)) return 1; fin.setDevice(&file);
    for(int i = 0; i < tmp_enemy_size; i ++) {
        DB_enemy _enemy;
        int _tmp_id = fin.readLine().toInt();
        // _enemy.__id = fin.readLine().toInt();
        _enemy.name = fin.readLine();
        _enemy.image_id = fin.readLine().toInt();
        int _data_size = fin.readLine().toInt();
        for(int j = 0; j < _data_size; j ++) {
            QString _tmp0 = fin.readLine();
            int _tmp1 = fin.readLine().toFloat();
            _enemy.data[_tmp0] = _tmp1;
        }
        int _data_str_size = fin.readLine().toInt();
        for(int j = 0; j < _data_str_size; j ++) {
            QString _tmp0 = fin.readLine();
            QString _tmp1 = fin.readLine().replace("\\n", "\n");
            _enemy.data_str[_tmp0] = _tmp1;
        }
        enemy[_tmp_id] = _enemy;
    }
    file.close();

    file.setFileName(basePath + "/boss/index.txt");
    if(!file.open(QIODevice::ReadOnly)) return 1; fin.setDevice(&file);
    for(int i = 0; i < tmp_boss_size; i ++) {
        DB_boss _boss;
        int _tmp_id = fin.readLine().toInt();
        _boss.__id = fin.readLine().toInt();
        _boss.name = fin.readLine().toInt();
        _boss.image_id[0] = fin.readLine().toInt();
        _boss.image_id[1] = fin.readLine().toInt();
        _boss.image_id[2] = fin.readLine().toInt();
        boss[_tmp_id] = _boss;
    }
    file.close();

    file.setFileName(basePath + "/bullet/index.txt");
    if(!file.open(QIODevice::ReadOnly)) return 1; fin.setDevice(&file);
    for(int _t = 0; _t < 3; _t ++) {
        for(int i = 0; i < tmp_bullet_size[_t]; i ++) {
            DB_bullet _bullet;
            int _tmp_id = fin.readLine().toInt();
            _bullet.__id = fin.readLine().toInt();
            _bullet.name = fin.readLine();
            _bullet.image_id = fin.readLine().toInt();
            int _data_size = fin.readLine().toInt();
            for(int j = 0; j < _data_size; j ++) {
                QString _tmp0 = fin.readLine();
                int _tmp1 = fin.readLine().toFloat();
                _bullet.data[_tmp0] = _tmp1;
            }
            int _data_str_size = fin.readLine().toInt();
            for(int j = 0; j < _data_str_size; j ++) {
                QString _tmp0 = fin.readLine();
                QString _tmp1 = fin.readLine().replace("\\n", "\n");
                _bullet.data_str[_tmp0] = _tmp1;
            }
            bullet[_t][_tmp_id] = _bullet;
        }
    }
    file.close();

    file.setFileName(basePath + "/effect/index.txt");
    if(!file.open(QIODevice::ReadOnly)) return 1; fin.setDevice(&file);

    file.close();


    file.setFileName(basePath + "/audio/index.txt");
    if(!file.open(QIODevice::ReadOnly)) return 1; fin.setDevice(&file);
    for(int _t = 0; _t < 3; _t ++) {
        for(int i = 0; i < tmp_audio_size[_t]; i ++) {
            DB_audio _audio;
            int _tmp_id = fin.readLine().toInt();
            _audio.__id = fin.readLine().toInt();
            _audio.name = fin.readLine();
            _audio.state = fin.readLine().toInt();
            audio[_t][_tmp_id] = _audio;
        }
    }
    file.close();


    CacheAgent::getInstance().sprite_buffer.clear();
    file.setFileName(basePath + "/image/index.txt");
    if(!file.open(QIODevice::ReadOnly)) return 1; fin.setDevice(&file);
    for(int _t = 0; _t < 5; _t ++) {
        for(int i = 0; i < tmp_image_size[_t]; i ++) {
            DB_image _image;
            int _tmp_id = fin.readLine().toInt();
            _image.__id = fin.readLine().toInt();
            _image.name = fin.readLine();
            _image.state = fin.readLine().toInt();
            if(_image.state) {
                QString _file_path = basePath + "/image/" + QString::number(_tmp_id);
                sprite_buff _tmp_buff;
                if(_image.state == 1) {
                    if(!QFile::exists(_file_path + ".png")) _image.state = 0;
                    else {
                        _tmp_buff.png = QPixmap(_file_path + ".png");
                        CacheAgent::getInstance().sprite_buffer.insert(QString::number(_tmp_id) + "_0", _tmp_buff);
                    }
                }
                if(_image.state == 2) {
                    if(!QFile::exists(_file_path + ".gif")) _image.state = 0;
                    else {
                        _tmp_buff.gif = new QMovie(_file_path + ".gif");
                        CacheAgent::getInstance().sprite_buffer.insert(QString::number(_tmp_id) + "_0", _tmp_buff);
                    }
                }
            }
            image[_t][_tmp_id] = _image;
        }
    }
    file.close();

    int tmp = info.language.size();
    file.setFileName(basePath + "/text_index.txt");
    if(!file.open(QIODevice::ReadOnly)) return 1; fin.setDevice(&file);

    for(int i = 0; i < tmp_text_size; i ++) {
        DB_text _text;
        int _tmp_id = fin.readLine().toInt();
        _text.__id = fin.readLine().toInt();
        for(int j = 0; j < tmp; j ++) {
            _text.__text.append(fin.readLine().replace("#", "\n"));
        }
        text[_tmp_id] = _text;
    }
    file.close();


    return false;
}

bool Database::save() {

    QString basePath = info.projectPosition;
    QDir dir(basePath);
    if(!dir.exists()) return true;

    dir.setPath(basePath + "/stage");
    if(!dir.exists()) dir.mkdir(dir.path());
    dir.setPath(basePath + "/ui");
    if(!dir.exists()) dir.mkdir(dir.path());
    dir.setPath(basePath + "/hero");
    if(!dir.exists()) dir.mkdir(dir.path());
    dir.setPath(basePath + "/enemy");
    if(!dir.exists()) dir.mkdir(dir.path());
    dir.setPath(basePath + "/boss");
    if(!dir.exists()) dir.mkdir(dir.path());
    dir.setPath(basePath + "/bullet");
    if(!dir.exists()) dir.mkdir(dir.path());
    dir.setPath(basePath + "/effect");
    if(!dir.exists()) dir.mkdir(dir.path());
    dir.setPath(basePath + "/audio");
    if(!dir.exists()) dir.mkdir(dir.path());
    dir.setPath(basePath + "/image");
    if(!dir.exists()) dir.mkdir(dir.path());

    CacheAgent::getInstance().setting.setLastProjectPosition(CacheAgent::getInstance().databaseInfo().projectPosition,CacheAgent::getInstance().databaseInfo().projectName);
    CacheAgent::getInstance().setting.save();

    QFile file;
    QTextStream fout;

    file.setFileName(basePath + "/index.thmkproj");
    if(!file.open(QIODevice::WriteOnly)) return 1; fout.setDevice(&file);

    fout << info.projectName << "\n" <<
            QString::number( CacheAgent::getInstance().stage_id_top ) << "\n" <<
            QString::number( CacheAgent::getInstance().stage_event_id_top ) << "\n" <<
            QString::number( CacheAgent::getInstance().text_id_top ) << "\n" <<
            QString::number( CacheAgent::getInstance().hero_id_top ) << "\n" <<
            QString::number( CacheAgent::getInstance().enemy_id_top ) << "\n" <<
            QString::number( CacheAgent::getInstance().boss_id_top ) << "\n" <<
            QString::number( CacheAgent::getInstance().bullet_id_top ) << "\n" <<
            QString::number( CacheAgent::getInstance().effect_id_top ) << "\n" <<
            QString::number( CacheAgent::getInstance().audio_id_top ) << "\n" <<
            QString::number( CacheAgent::getInstance().image_id_top ) << "\n" <<

            QString::number( text.size() ) << "\n" <<
            QString::number( stage[0].size() ) << "\n" <<
            QString::number( stage[1].size() ) << "\n" <<

            QString::number( hero.size() ) << "\n" <<
            QString::number( enemy.size() ) << "\n" <<
            QString::number( boss.size() ) << "\n" <<

            QString::number( bullet[0].size() ) << "\n" <<
            QString::number( bullet[1].size() ) << "\n" <<
            QString::number( bullet[2].size() ) << "\n" <<

            QString::number( effect[0].size() ) << "\n" <<
            QString::number( effect[1].size() ) << "\n" <<
            QString::number( effect[2].size() ) << "\n" <<

            QString::number( audio[0].size() ) << "\n" <<
            QString::number( audio[1].size() ) << "\n" <<
            QString::number( audio[2].size() ) << "\n" <<

            QString::number( image[0].size() ) << "\n" <<
            QString::number( image[1].size() ) << "\n" <<
            QString::number( image[2].size() ) << "\n" <<
            QString::number( image[3].size() ) << "\n" <<
            QString::number( image[4].size() ) << "\n";

    file.close();

    file.setFileName(basePath + "/info.txt");
    if(!file.open(QIODevice::WriteOnly)) return 1; fout.setDevice(&file);

    fout << info.projectName << "\n"; /*<<

            QString::number( info.setting_start_with_logo ) << "\n" <<
            QString::number( info.setting_reading_aciton ) << "\n" <<
            QString::number( info.setting_using_cg_collection ) << "\n";*/
    file.close();

    file.setFileName(basePath + "/language.txt");
    if(!file.open(QIODevice::WriteOnly)) return 1; fout.setDevice(&file);
    fout << QString::number( info.language.size() ) << "\n";
    for(int i = 0; i < info.language.size(); i ++) fout << info.language[i] << "\n";
    file.close();


    file.setFileName(basePath + "/ui/index.txt");
    if(!file.open(QIODevice::WriteOnly)) return 1; fout.setDevice(&file);

    file.close();

    file.setFileName(basePath + "/stage/index0.txt");
    if(!file.open(QIODevice::WriteOnly)) return 1; fout.setDevice(&file);
    for(auto i = stage[0].begin(); i != stage[0].end(); i ++) {
        fout << QString::number(i->_stageId) << "\n" << i->name << "\n" << QString::number(i->length) << "\n" <<
                QString::number(i->events.size()) << "\n";
        for(auto j = i->events.begin(); j != i->events.end(); j ++) {
            fout << QString::number(j->id) << "\n" << QString::number(j->time) << "\n" << QString::number(j->type) << "\n" <<
                    QString::number(j->data.size()) << "\n";
            for(auto k = j->data.begin(); k != j->data.end(); k ++) {
                fout << k.key() << "\n" << QString::number(k.value()) << "\n";
            }
            fout << QString::number(j->data_str.size()) << "\n";
            for(auto k = j->data_str.begin(); k != j->data_str.end(); k ++) {
                fout << k.key() << "\n" << k.value().replace("\n", "\\n") << "\n";
            }
        }
    }
    file.close();

    file.setFileName(basePath + "/stage/index1.txt");
    if(!file.open(QIODevice::WriteOnly)) return 1; fout.setDevice(&file);
    for(auto i = stage[1].begin(); i != stage[1].end(); i ++) {
        fout << QString::number(i->_stageId) << "\n" << i->name << "\n" << QString::number(i->length) << "\n" <<
                QString::number(i->events.size()) << "\n";
        for(auto j = i->events.begin(); j != i->events.end(); j ++) {
            fout << QString::number(j->id) << "\n" << QString::number(j->time) << "\n" << QString::number(j->type) << "\n" <<
                    QString::number(j->data.size()) << "\n";
            for(auto k = j->data.begin(); k != j->data.end(); k ++) {
                fout << k.key() << "\n" << QString::number(k.value()) << "\n";
            }
            fout << QString::number(j->data_str.size()) << "\n";
            for(auto k = j->data_str.begin(); k != j->data_str.end(); k ++) {
                fout << k.key() << "\n" << k.value().replace("\n", "\\n") << "\n";
            }
        }
    }
    file.close();

    file.setFileName(basePath + "/hero/index.txt");
    if(!file.open(QIODevice::WriteOnly)) return 1; fout.setDevice(&file);

    file.close();

    file.setFileName(basePath + "/enemy/index.txt");
    if(!file.open(QIODevice::WriteOnly)) return 1; fout.setDevice(&file);
    for(auto i = enemy.begin(); i != enemy.end(); i ++) {
        fout << QString::number(i.key()) << "\n" <<
                // QString::number(i.value().__id) << "\n" << i.value().name << "\n" <<
                QString::number(i.value().image_id) << "\n" <<
                QString::number(i->data.size()) << "\n";
        for(auto k = i->data.begin(); k != i->data.end(); k ++) {
            fout << k.key() << "\n" << QString::number(k.value()) << "\n";
        }
        fout << QString::number(i->data_str.size()) << "\n";
        for(auto j = i->data_str.begin(); j != i->data_str.end(); j ++) {
            fout << j.key() << "\n" << j.value().replace("\n", "\\n") << "\n";
        }
    }

    file.close();

    file.setFileName(basePath + "/boss/index.txt");
    if(!file.open(QIODevice::WriteOnly)) return 1; fout.setDevice(&file);
    for(auto i = boss.begin(); i != boss.end(); i ++) {
        fout << QString::number(i.key()) << "\n" <<
                QString::number(i.value().__id) << "\n" << QString::number(i.value().name) << "\n" <<
                QString::number(i.value().image_id[0]) << "\n" <<
                QString::number(i.value().image_id[1]) << "\n" <<
                QString::number(i.value().image_id[2]) << "\n";
    }

    file.close();

    file.setFileName(basePath + "/bullet/index.txt");
    if(!file.open(QIODevice::WriteOnly)) return 1; fout.setDevice(&file);
    for(int _t = 0; _t < 3; _t ++) {
        for(auto i = bullet[_t].begin(); i != bullet[_t].end(); i ++) {
            fout << QString::number(i.key()) << "\n" <<
                    QString::number(i.value().__id) << "\n" << i.value().name << "\n" <<
                    QString::number(i.value().image_id) << "\n" <<
                    QString::number(i->data.size()) << "\n";
            for(auto k = i->data.begin(); k != i->data.end(); k ++) {
                fout << k.key() << "\n" << QString::number(k.value()) << "\n";
            }
            fout << QString::number(i->data_str.size()) << "\n";
            for(auto j = i->data_str.begin(); j != i->data_str.end(); j ++) {
                fout << j.key() << "\n" << j.value().replace("\n", "\\n") << "\n";
            }
        }
    }
    file.close();

    file.setFileName(basePath + "/effect/index.txt");
    if(!file.open(QIODevice::WriteOnly)) return 1; fout.setDevice(&file);

    file.close();

    file.setFileName(basePath + "/audio/index.txt");
    if(!file.open(QIODevice::WriteOnly)) return 1; fout.setDevice(&file);
    for(int _t = 0; _t < 3; _t ++) {
        for(auto i = audio[_t].begin(); i != audio[_t].end(); i ++) {
            fout << QString::number(i.key()) << "\n" <<
                    QString::number(i.value().__id) << "\n" << i.value().name << "\n" << QString::number(i.value().state) << "\n";
        }
    }
    file.close();

    file.setFileName(basePath + "/image/index.txt");
    if(!file.open(QIODevice::WriteOnly)) return 1; fout.setDevice(&file);
    for(int _t = 0; _t < 5; _t ++) {
        for(auto i = image[_t].begin(); i != image[_t].end(); i ++) {
            fout << QString::number(i.key()) << "\n" <<
                    QString::number(i.value().__id) << "\n" << i.value().name << "\n" << QString::number(i.value().state) << "\n";
        }
    }
    file.close();

    int tmp = info.language.size();
    file.setFileName(basePath + "/text_index.txt");
    if(!file.open(QIODevice::WriteOnly)) return 1; fout.setDevice(&file);
    for(auto i = text.begin(); i != text.end(); i ++) {
        fout << QString::number(i.key()) << "\n" <<
                QString::number(i.value().__id) << "\n";
        for(int j = 0; j < tmp; j ++) {
            fout << i.value().getText(j).replace("\n", "#") << "\n";
        }
    }
    file.close();

    return false;
}

bool Database::pack() {

    QString basePath = info.projectPosition;
    QDir dir(basePath);
    if(!dir.exists()) return true;

    dir.setPath(basePath + "/output");
    if(!dir.exists()) dir.mkdir(dir.path());

    if(QFile::exists(basePath + "/output/image.thmk"))      QFile::remove(basePath + "/output/image.thmk");
    if(QFile::exists(basePath + "/output/audio.thmk"))      QFile::remove(basePath + "/output/audio.thmk");
    if(QFile::exists(basePath + "/output/effect.thmk"))     QFile::remove(basePath + "/output/effect.thmk");

    if(QFile::exists(basePath + "/output/bullet.thmk"))     QFile::remove(basePath + "/output/bullet.thmk");
    if(QFile::exists(basePath + "/output/character.thmk"))  QFile::remove(basePath + "/output/character.thmk");

    if(QFile::exists(basePath + "/output/main.thmk"))       QFile::remove(basePath + "/output/main.thmk");

    QFile resFile;
    QTextStream fout;
    QByteArray buffer;
    QZipWriter *zip;
    QJsonDocument jDoc;
    int num, _tmp_num;

    //QMap<int, int> map_stage;
    QMap<int, int> map_event;

    QMap<int, int> map_text;
    QMap<int, int> map_hero;
    QMap<int, int> map_enemy;
    QMap<int, int> map_boss;
    QMap<int, int> map_bullet[3];
    QMap<int, int> map_effect[3];
    QMap<int, int> map_audio[3];
    QMap<int, int> map_image[5];

    ////////////////////////////////////////////////////////////////////////////
    /// text

    buffer.clear();
    num = 0;

    resFile.setFileName(basePath + "/output/text.json");
    if(!resFile.open(QIODevice::WriteOnly)) return true;

    QJsonObject jObj_text_root;

    jObj_text_root.insert("languageNumber", int(lanSize()));
    jObj_text_root.insert("textNumber", int(text.size()));
    QJsonArray jArr_text_lan;
    for(int i = 0; i < lanSize(); i ++) {
        jArr_text_lan.append(info.language[i]);
    }
    jObj_text_root.insert("languageList", jArr_text_lan);

    QJsonArray jArr_text_root_list;
    for(auto i = text.begin(); i != text.end(); i ++) {
        QJsonArray jArr_text_list;
        for(int j = 0; j < lanSize(); j ++) {
            jArr_text_list.append(i.value().__text[j]);
        }
        jArr_text_root_list.append(jArr_text_list);

        map_text[i.key()] = num;
        num ++;
    }
    jObj_text_root.insert("textList", jArr_text_root_list);
    jDoc.setObject(jObj_text_root);
    resFile.write(jDoc.toJson());
    resFile.close();

    map_text[-1] = -1;
    ////////////////////////////////////////////////////////////////////////////////
    /// pre

    /*num = 0;
    for(int k = 0; k < 2; k ++) {
        for(auto i = stage[k].begin(); i != stage[k].end(); i ++) map_stage[i->id] = num++;
    }
    map_stage[-1] = -1;*/

    num = 0;
    for(int k = 0; k < 2; k ++) {
        for(auto i = stage[k].begin(); i != stage[k].end(); i ++) {
            for(auto j = i->events.begin(); j != i->events.end(); j ++) map_event[j->id] = num++;
        }
    }
    map_event[-1] = -1;

    num = 0;
    for(int k = 0; k < 5; k ++) {
        for(auto i = image[k].begin(); i != image[k].end(); i ++) map_image[k][i.key()] = num++;
        map_image[k][-1] = -1;
    }

    num = 0;
    for(int k = 0; k < 3; k ++) {
        for(auto i = audio[k].begin(); i != audio[k].end(); i ++) map_audio[k][i.key()] = num++;
        map_audio[k][-1] = -1;
    }

    num = 0;
    for(int k = 0; k < 3; k ++) {
        for(auto i = effect[k].begin(); i != effect[k].end(); i ++) map_effect[k][i.key()] = num++;
        map_effect[k][-1] = -1;
    }

    num = 0;
    for(int k = 0; k < 3; k ++) {
        for(auto i = bullet[k].begin(); i != bullet[k].end(); i ++) map_bullet[k][i.key()] = num++;
        map_bullet[k][-1] = -1;
    }

    num = 0;
    for(auto i = hero.begin(); i != hero.end(); i ++) map_hero[i.key()] = num++;
    map_hero[-1] = -1;

    num = 0;
    for(auto i = enemy.begin(); i != enemy.end(); i ++) map_enemy[i.key()] = num++;
    map_enemy[-1] = -1;

    num = 0;
    for(auto i = boss.begin(); i != boss.end(); i ++) map_boss[i.key()] = num++;
    map_boss[-1] = -1;

    ////////////////////////////////////////////////////////////////////////////////
    /// image

    zip = new QZipWriter(basePath + "/output/image.thmk");
    buffer.clear();

    _tmp_num = 0;
    for(int k = 0; k < 5; k ++) _tmp_num += image[k].size();
    buffer += QString::number(_tmp_num) + "\n";

    for(int k = 0; k < 5; k ++) {
        for(auto i = image[k].begin(); i != image[k].end(); i ++) {
            buffer += i.value().name + "\n";
            buffer += QString::number(map_image[k][i.key()]) + "\n";

            buffer += QString::number(i.value().state) + "\n";

            if(i.value().state == 1) {
                resFile.setFileName(basePath + "/image/" + QString::number(i.key()) + ".png");
                if(resFile.exists() && resFile.open(QIODevice::ReadOnly)) {
                    zip->addFile(QString::number(map_image[k][i.key()]) + ".png", resFile.readAll());
                    resFile.close();
                }
            }
            if(i.value().state == 2) {
                //zip->addDirectory(QString::number(map_image[k][i.key()]));
                QMovie *movie = new QMovie(basePath + "/image/" + QString::number(i.key()) + ".gif");
                movie->jumpToFrame(0);
                auto img0 = movie->currentPixmap();
                auto _size = img0.size();
                int _movie_num = movie->frameCount();
                buffer += QString::number(_movie_num) + "\n";
                buffer += QString::number(movie->nextFrameDelay()) + "\n";
                QPixmap pixmap_final = QPixmap(_size.width() * _movie_num, _size.height());
                pixmap_final.fill(Qt::transparent);
                QPainter painter;
                painter.begin(&pixmap_final);
                for(int j = 0; j < _movie_num; j ++) {
                    movie->jumpToFrame(j);
                    auto img = movie->currentPixmap();
                    painter.drawPixmap(QRect(j * _size.width(), 0, _size.width(), _size.width()), img, img.rect());
                }

                painter.end();

                QByteArray bArr;
                QBuffer buff(&bArr);
                buff.open(QIODevice::WriteOnly);
                pixmap_final.save(&buff, "PNG");
                zip->addFile(QString::number(map_image[k][i.key()]) + ".png", bArr);

                delete movie;
            }

        }
    }

    zip->addFile("index", buffer);
    zip->close();
    delete zip;

    ////////////////////////////////////////////////////////////////////////////////
    /// audio

    zip = new QZipWriter(basePath + "/output/audio.thmk");
    buffer.clear();

    _tmp_num = 0;
    for(int k = 0; k < 3; k ++) _tmp_num += audio[k].size();
    buffer += QString::number(_tmp_num) + "\n";

    for(int k = 0; k < 3; k ++) {
        for(auto i = audio[k].begin(); i != audio[k].end(); i ++) {
            buffer += i.value().name + "\n";
            buffer += QString::number(map_audio[k][i.key()]) + "\n";

            buffer += QString::number(i.value().state) + "\n";

            if(i.value().state == 1) {
                resFile.setFileName(basePath + "/audio/" + QString::number(i.key()) + ".ogg");
                if(resFile.exists() && resFile.open(QIODevice::ReadOnly)) {
                    zip->addFile(QString::number(map_audio[k][i.key()]) + ".ogg", resFile.readAll());
                    resFile.close();
                }
            }

        }
    }

    zip->addFile("index", buffer);
    zip->close();
    delete zip;

    ////////////////////////////////////////////////////////////////////////////////
    /// effect

    zip = new QZipWriter(basePath + "/output/effect.thmk");
    buffer.clear();

    _tmp_num = 0;
    for(int k = 0; k < 3; k ++) _tmp_num += effect[k].size();
    buffer += QString::number(_tmp_num) + "\n";

    for(int k = 0; k < 3; k ++) {
        for(auto i = effect[k].begin(); i != effect[k].end(); i ++) {
            buffer += i.value().name + "\n";
            buffer += QString::number(map_effect[k][i.key()]) + "\n";

        }
    }

    zip->addFile("index", buffer);
    zip->close();
    delete zip;

    ////////////////////////////////////////////////////////////////////////////////
    /// bullet

    zip = new QZipWriter(basePath + "/output/bullet.thmk");
    buffer.clear();

    _tmp_num = 0;
    for(int k = 0; k < 3; k ++) _tmp_num += bullet[k].size();
    buffer += QString::number(_tmp_num) + "\n";

    for(int k = 0; k < 3; k ++) {
        for(auto i = bullet[k].begin(); i != bullet[k].end(); i ++) {
            buffer += i.value().name + "\n";
            buffer += QString::number(map_bullet[k][i.key()]) + "\n";

            buffer += QString::number(map_image[3][i.value().image_id]) + "\n";

            QJsonObject jObj_bullet_root;

            i.value().toJson(k, map_text,map_hero,map_enemy,map_boss,map_bullet,map_effect,map_audio,map_image,
                             &jObj_bullet_root);

            jDoc.setObject(jObj_bullet_root);
            zip->addFile(QString::number(map_bullet[k][i.key()]), jDoc.toJson());
        }
    }

    zip->addFile("index", buffer);
    zip->close();
    delete zip;

    ////////////////////////////////////////////////////////////////////////////////
    /// character

    zip = new QZipWriter(basePath + "/output/character.thmk");

    buffer.clear();
    buffer += QString::number(hero.size()) + "\n";
    for(auto i = hero.begin(); i != hero.end(); i ++) {
        buffer += QString::number(map_text[i.value().name]) + "\n";
        buffer += QString::number(map_hero[i.key()]) + "\n";

        for(int j = 0; j < 6; j ++) {
            buffer += QString::number(map_image[4][i.value().image_id[j]]) + "\n";
        }

    }
    zip->addFile("index0", buffer);

    buffer.clear();
    buffer += QString::number(enemy.size()) + "\n";
    for(auto i = enemy.begin(); i != enemy.end(); i ++) {
        buffer += i.value().name + "\n";
        buffer += QString::number(map_enemy[i.key()]) + "\n";

        buffer += QString::number(map_image[4][i.value().image_id]) + "\n";

        QJsonObject jObj_enemy_root;
        i.value().toJson(map_text,map_hero,map_enemy,map_boss,map_bullet,map_effect,map_audio,map_image,
                         &jObj_enemy_root);

        jDoc.setObject(jObj_enemy_root);
        zip->addFile("enemy" + QString::number(map_enemy[i.key()]), jDoc.toJson());

    }
    zip->addFile("index1", buffer);

    buffer.clear();
    buffer += QString::number(boss.size()) + "\n";
    for(auto i = boss.begin(); i != boss.end(); i ++) {
        buffer += QString::number(map_text[i.value().name]) + "\n";
        buffer += QString::number(map_boss[i.key()]) + "\n";

        buffer += QString::number(map_image[4][i.value().image_id[0]]) + "\n";
        buffer += QString::number(map_image[4][i.value().image_id[1]]) + "\n";
        buffer += QString::number(map_image[4][i.value().image_id[2]]) + "\n";

    }
    zip->addFile("index2", buffer);

    zip->close();
    delete zip;

    ////////////////////////////////////////////////////////////////////////////////
    /// main

    zip = new QZipWriter(basePath + "/output/main.thmk");

    buffer.clear();
    buffer += QString::number(stage[0].size()) + "\n";
    buffer += QString::number(stage[1].size()) + "\n";

    int _tmp_event_size = 0;

    for(int k = 0; k < 2; k ++) {
        for(int i = 0; i < stage[k].size(); i ++) {
            auto file = &stage[k][i];
            buffer += file->name + "\n";
//            buffer += QString::number(map_stage[file->id]) + "\n";
//            buffer += QString::number(i) + "\n";

            buffer += QString::number(file->length) + "\n";
            buffer += QString::number(file->events.size()) + "\n";

            for(int j = 0; j < file->events.size(); j ++) {
                buffer += QString::number(map_event[file->events[j].id]) + "\n";
                _tmp_event_size ++;
            }
        }
    }
    zip->addFile("index0", buffer);

    buffer.clear();
    buffer += QString::number(_tmp_event_size) + "\n";

    for(int k = 0; k < 2; k ++) {
        for(int i = 0; i < stage[k].size(); i ++) {
            auto file = &stage[k][i];
            for(int j = 0; j < file->events.size(); j ++) {
                auto event = file->events[j];
                buffer += QString::number(map_event[event.id]) + "\n";

                buffer += QString::number(event.time) + "\n";
                buffer += QString::number(event.type) + "\n";


                QJsonObject jObj_event_root;
                event.toJson(map_text,map_hero,map_enemy,map_boss,map_bullet,map_effect,map_audio,map_image,
                                 &jObj_event_root);

                jDoc.setObject(jObj_event_root);
                zip->addFile(QString::number(map_event[event.id]), jDoc.toJson());
            }
        }
    }
    zip->addFile("index1", buffer);

    zip->close();
    delete zip;

    ////////////////////////////////////////////////////////////////////////////////
    /// setting

    resFile.setFileName(basePath + "/output/setting.txt");
    if(!resFile.open(QIODevice::WriteOnly)) return 1; fout.setDevice(&resFile);
    fout << "\n";
/*
    fout << QString::number(info.setting_start_with_logo) << "\n" <<
            QString::number(info.setting_reading_aciton) << "\n" <<
            QString::number(info.setting_using_cg_collection) << "\n" <<
            QString::number(info.setting_ra.ra_image1) << "\n" <<
            QString::number(info.setting_ra.ra_image2) << "\n" <<
            QString::number(info.setting_ra.ra_image3) << "\n" <<
            QString::number(info.setting_ra.ra_audio1) << "\n" <<
            QString::number(info.setting_ra.ra_audio2) << "\n" <<
            QString::number(info.setting_ra.ra_audio3) << "\n" <<
            QString::number(info.setting_ra.ra_video1) << "\n" <<
            QString::number(info.setting_ra.ra_video2) << "\n" <<
            QString::number(info.setting_ra.ra_video3) << "\n" <<
            QString::number(info.setting_ra.ra_dictionary) << "\n" <<
            QString::number(info.setting_ra.ra_character) << "\n";
*/
    resFile.close();

    ////////////////////////////////////////////////////////////////////////////////
    /// ui





    ///////////////////////////////////

    return false;
}



