#include <QApplication>

#include "global.h"
#include "sprite.h"
#include "draw.h"

#include "window/interduceWindow.h"

#include <qt_windows.h>
#include <QDesktopWidget>
#include <QFontDatabase>
#include "logModule/logmodule.h"
#include "globalSource/sourceAgent.h"

float getWindowsScale() {
    HDC screen = GetDC(0);
    FLOAT dpiX = static_cast<FLOAT>(GetDeviceCaps(screen, LOGPIXELSX));
    ReleaseDC(0, screen);
    return dpiX / 96.0 / 1.25;
}


int main(int argc, char *argv[])
{
    qInstallMessageHandler(LogModule::StaticLogHandler);
    QApplication a(argc, argv);

    QRect rect = QApplication::desktop()->screenGeometry();
    if(rect.width() < 1918 || rect.height() < 1078) {
        QMessageBox::critical(nullptr, "警告", "屏幕分辨率不足1920x1080，程序可能会出现显示不全的问题。");
    }

    if(!QFile::exists(QApplication::applicationDirPath() + "/agreed20240129")) {
        QString str = "";

str += "        总则 - 《车万没课儿》是美博犇工作室（Meboxen Studio）开发的开源软件。美博犇工作室保留对本协议拥有修改，增补，删除，更新等权利。\n\n";
str += "        1 – 用户在使用本软件时，必须完全知情并同意本协议。此外，用户使用时需遵守所在地区的相关法律法规，如因违反法律法规造成的任何问题将由用户承担。当本协议内容与相关法律法规冲突时，以法律法规规定的内容为准。\n\n";
str += "        2 - 用户可以使用《车万没课儿》从事包括但不限于使用、修改、复制、软件销售等任何盈利或非盈利活动，但在进行上述活动时，需在产品显著位置著名“原作：美博犇工作室”或表达相关含义的字样。\n\n";
str += "        3 – 本软件具有内容生成功能，使用本软件生成内容的个人或团体称为生成者。在进行内容生成时，使用的资产应当为生成者自行生产，或得到资产生产者授权予以使用，如果因资产的使用权问题而产生纠纷，将由生成者自行承担责任。（注：此处的资产指图像、音频、字体等具有明确使用许可范围的文件。）\n\n";
str += "        4 - 使用本软件，或者使用本软件所生成的内容可能会泄露用户的个人信息或者对财产造成损失，此类损害将由用户自行承担。恶意使用本软件造成上述后果的，应当追究恶意使用者的法律责任。\n\n";
str += "        5 – 无论是否知情或同意本协议，用户均可使用本软件所生成的内容。如果因此而造成损害，应由生成者承担相应责任。\n\n";
str += "        6 - 在涉及东方Project原作内容时，需严格遵守东方Project使用协议。\n\n";
str += "        7 - 若用户不同意本协议，应当点击下方“No”按钮退出程序，并从计算机中完全删除《车万没课儿》及其相关组件。一旦用户点击下方“Yes”按钮，并开始使用本软件，即视为同意本协议。在此之后，用户不得以未阅读或者未同意上述内容的理由进行任何形式的抗辩。\n\n";
str += "2024年1月29日";
        int tmp = QMessageBox::question(nullptr, "用户使用协议", str);
        if(tmp == QMessageBox::No) return 0;
        QSettings *file = new QSettings(QApplication::applicationDirPath() + "/agreed20240129", QSettings::IniFormat);
        file->setValue("a", "a");
        delete file;
    }
    Spr::init();
    Col::init();
    Draw::font_scale = getWindowsScale();
    //Draw::font_id = QFontDatabase::addApplicationFont(QStringLiteral("SourceHanSansCN-Medium.ttf"));
    Draw::font_id = QFontDatabase::addApplicationFont(QStringLiteral("jcyt500W.ttf"));

    auto tmp = QFontDatabase::applicationFontFamilies(Draw::font_id);
    //a.setFont(QFont(tmp[0]));
    a.setFont(SourceAgent::GetInstance().GetFont(GlobalSource::FONT_JCYT_500W));
    InterduceWindow w;
    w.show();
    int ret = a.exec();
    // Shd::release();
    Spr::release();
    return ret;
}
