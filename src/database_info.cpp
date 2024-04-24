#include "database_info.h"

Database_info::Database_info()
{
    init();
}

void Database_info::clear()
{
    language.clear();
    projectPosition = "";
    projectName = "";
}

void Database_info::init()
{
    clear();

    language.append("简体中文");
    language.append("繁體中文");
    language.append("English");

    projectPosition = "<empty>";
    projectName = "<empty>";

}





