// #ifndef DATABASE_CHARACTER_H
// #define DATABASE_CHARACTER_H

// #include <QList>
// #include <QString>
// #include <QTextStream>

// struct DB_Character_Face_File {
//     int id, fa;
//     QString name;
//     int state; // only png
//     float x, y;

//     DB_Character_Face_File(int _fa, int _id, float _x, float _y, QString _name = "新建差分");
//     DB_Character_Face_File() {}
// };

// struct DB_Character_Face_Folder {
//     int id, fa;
//     QString name;
//     QList<int> next;
//     int state; // only png

//     inline int size() { return next.size(); }

//     DB_Character_Face_Folder(int _fa, int _id, QString _name = "新建文件夹");
//     DB_Character_Face_Folder() {}
// };

// struct DB_Character_Voice_File {
//     int id, fa;
//     QString name;
//     QList<int> __state; // .ogg, .mp3, .wav

//     DB_Character_Voice_File(int _fa, int _id, QString _name = "新建配音");
//     DB_Character_Voice_File() {}

//     int state(int _lan);
//     void setState(int _lan, int _state);
// };

// struct DB_Character_Voice_Folder {
//     int id, fa;
//     QString name;
//     QList<int> next;

//     inline int size() { return next.size(); }

//     DB_Character_Voice_Folder(int _fa, int _id, QString _name = "新建文件夹");
//     DB_Character_Voice_Folder() {}
// };

// struct DB_Character_info {
//     QString aaa;
// // use in future
//     DB_Character_info() {}
// };

// struct DB_Character_File {
//     int id, fa;
//     QList<QString> __name;
//     QList<QString> __text;
//     QList<int> faceGroup;
//     QList<int> voiceGroup;
//     QList<int> __voiceState; // in each language

//     DB_Character_info info;

//     DB_Character_File(int _fa, int _id, QString _name = "新建角色");
//     DB_Character_File() {}

//     QString name(int _lan);
//     QString text(int _lan);
//     void setName(int _lan, QString _name);
//     void setText(int _lan, QString _text);

//     bool read(QFile &file, QTextStream &fin, QString _fileName, int _lan_number);
//     bool save(QFile &file, QTextStream &fout, QString _fileName);

//     int voiceState(int _lan);
//     void setVoiceState(int _lan, int _state);

// };

// struct DB_Character_Folder {
//     QString name;
//     QList<int> next;
//     int state; // 0 = default, 1 = static, 2 = dynamic

//     inline int size() { return next.size(); }

//     DB_Character_Folder(QString _name = "新建文件夹", int _state = 0);
//     //DB_Character_Folder();
// };

// #endif // DATABASE_CHARACTER_H
