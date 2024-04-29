#include "database_character.h"

#include "memoryCache/cacheAgent.h"

DB_Character_Face_File::DB_Character_Face_File(int _fa, int _id, float _x, float _y, QString _name)
{
    fa = _fa; id = _id; state = 0;
    name = _name;
    x = _x; y = _y;
}

DB_Character_Face_Folder::DB_Character_Face_Folder(int _fa, int _id, QString _name)
{
    fa = _fa; id = _id; state = 0;
    name = _name;
}

DB_Character_Voice_File::DB_Character_Voice_File(int _fa, int _id, QString _name)
{
    fa = _fa; id = _id;
    name = _name;
    __state.append(0);
}

int DB_Character_Voice_File::state(int _lan)
{
    int tmp = CacheAgent::getInstance().databaseInfo().language.size();
    while(__state.size() < tmp) __state.append(0);
    while(__state.size() > tmp) __state.pop_back();
    return __state[_lan];
}

void DB_Character_Voice_File::setState(int _lan, int _state)
{
    int tmp = CacheAgent::getInstance().databaseInfo().language.size();
    while(__state.size() < tmp) __state.append(0);
    while(__state.size() > tmp) __state.pop_back();
    __state[_lan] = _state;
}

DB_Character_Voice_Folder::DB_Character_Voice_Folder(int _fa, int _id, QString _name)
{
    fa = _fa; id = _id;
    name = _name;
}


DB_Character_File::DB_Character_File(int _fa, int _id, QString _name)
{
    fa = _fa; id = _id;
    __name.append(_name);
//    __text.append("啊这");
//    __voiceState.append(0);
}

QString DB_Character_File::name(int _lan)
{
    int tmp = CacheAgent::getInstance().databaseInfo().language.size();
    while(__name.size() < tmp) __name.append("");
    while(__name.size() > tmp) __name.pop_back();
    return __name[_lan];
}

QString DB_Character_File::text(int _lan)
{
    int tmp = CacheAgent::getInstance().databaseInfo().language.size();
    while(__text.size() < tmp) __text.append("");
    while(__text.size() > tmp) __text.pop_back();
    return __text[_lan];
}

void DB_Character_File::setName(int _lan, QString _name)
{
    int tmp = CacheAgent::getInstance().databaseInfo().language.size();
    while(__name.size() < tmp) __name.append("");
    while(__name.size() > tmp) __name.pop_back();
    __name[_lan] = _name;
}

void DB_Character_File::setText(int _lan, QString _text)
{
    int tmp = CacheAgent::getInstance().databaseInfo().language.size();
    while(__text.size() < tmp) __text.append("");
    while(__text.size() > tmp) __text.pop_back();
    __text[_lan] = _text;
}

bool DB_Character_File::read(QFile &file, QTextStream &fin, QString _fileName, int _lan_number)
{
    file.setFileName(_fileName + "/index.txt");
    if(!file.open(QIODevice::ReadOnly)) return 1; fin.setDevice(&file);
    id = fin.readLine().toInt();
    fa = fin.readLine().toInt();
    int tmp_face_size = fin.readLine().toInt();
    for(int i = 0; i < tmp_face_size; i ++) faceGroup.append(fin.readLine().toInt());
    int tmp_voice_size = fin.readLine().toInt();
    for(int i = 0; i < tmp_voice_size; i ++) voiceGroup.append(fin.readLine().toInt());

    for(int i = 0; i < _lan_number; i ++) {
        __name.append(fin.readLine());
        __text.append(fin.readLine());
        __voiceState.append(fin.readLine().toInt());
    }

    file.close();

    return false;

}

bool DB_Character_File::save(QFile &file, QTextStream &fout, QString _fileName)
{
    int tmp = CacheAgent::getInstance().databaseInfo().language.size();
    file.setFileName(_fileName + "/index.txt");
    if(!file.open(QIODevice::WriteOnly)) return 1; fout.setDevice(&file);
    fout << QString::number( id ) << "\n" <<
            QString::number( fa ) << "\n";

    fout << QString::number( faceGroup.size() ) << "\n";
    for(int i = 0; i < faceGroup.size(); i ++) fout << QString::number( faceGroup[i] ) << "\n";
    fout << QString::number( voiceGroup.size() ) << "\n";
    for(int i = 0; i < voiceGroup.size(); i ++) fout << QString::number( voiceGroup[i] ) << "\n";

    for(int i = 0; i < tmp; i ++) fout << name(i) << "\n" << text(i) << "\n" << QString::number( voiceState(i) ) << "\n";

    file.close();

    return false;
}

int DB_Character_File::voiceState(int _lan)
{
    int tmp = CacheAgent::getInstance().databaseInfo().language.size();
    while(__voiceState.size() < tmp) __voiceState.append(0);
    while(__voiceState.size() > tmp) __voiceState.pop_back();
    for(int i = 0; i < tmp; i ++) __voiceState[i] = qMax(0, qMin(__voiceState[i], tmp - 1));
    return __voiceState[_lan];
}

void DB_Character_File::setVoiceState(int _lan, int _state)
{

    int tmp = CacheAgent::getInstance().databaseInfo().language.size();
    while(__voiceState.size() < tmp) __voiceState.append(0);
    while(__voiceState.size() > tmp) __voiceState.pop_back();
    for(int i = 0; i < tmp; i ++) __voiceState[i] = qMax(0, qMin(__voiceState[i], tmp - 1));
    __voiceState[_lan] = _state;
}


DB_Character_Folder::DB_Character_Folder(QString _name, int _state)
{
    name = _name;
    state = _state;
}




