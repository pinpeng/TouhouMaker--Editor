#include "window_editor_stage_tips.h"

#include <complex>
#include "global.h"
#include <QApplication>

#include <QFile>
#include <QTextStream>
#include <QMouseEvent>


int Window_editor_stage_tips::important = -1;

Window_editor_stage_tips::Window_editor_stage_tips(QWidget *parent) : QWidget(parent)
{
    timer = new BaseThread();
    connect(timer, SIGNAL(timeout()), this, SLOT(timeoutRepaint()));
    timer->start();


    setFixedSize(640, 480);
    setGeometry(0, 0, 640, 360);

    setWindowFlag(Qt::WindowStaysOnTopHint, true);

    important = -1;

    speakTimer = 300;
    action = 2;
    action_timer = 0;
    face = 0; // 0 = happy, 1 = sleep, 2 = angry, 3 = worry, 4 = shy
    faces << Sprite(tips_happy)
          << Sprite(tips_sleep)
          << Sprite(tips_dark_face)
          << Sprite(tips_worry)
          << Sprite(tips_shy);

    QFile *file = new QFile(QApplication::applicationDirPath() + "/tips/tips.txt");
    if(file->open(QIODevice::ReadOnly)) {
        QString str;
        QTextStream fin;
        fin.setDevice(file);

        str = fin.readLine().replace("#", "\n");
        text = str;

        int num;
        num = fin.readLine().toInt();
        for(int i = 0; i < num; i ++) {
            str = fin.readLine().replace("#", "\n");
            tips_auto.append(str);
        }
        num = fin.readLine().toInt();
        for(int i = 0; i < num; i ++) {
            str = fin.readLine().replace("#", "\n");
            tips_interaciton.append(str);
        }
        num = fin.readLine().toInt();
        for(int i = 0; i < num; i ++) {
            str = fin.readLine().replace("#", "\n");
            tips_important.append(str);
        }

        file->close();

    } else {
        text = "你好呀！我是凯特丽丝，叫我小凯就行啦！\n如果有什么问题的话，我会帮助你的哦！";
        tips_auto <<
                     "0据说更改程序设置必须先退出到开始界面……\n为什么要做的这么麻烦呢！" <<
                     "0很多事情都写在了说明书上，\n点击上方的“帮助”按钮就可以看到啦！" <<
                     "0对话树管理器是不是不太好找东西呢？\n其实只要用搜索功能就行啦！" <<
                     "0搜索框里如果不填东西，默认会搜索全部哦！" <<
                     "0箭头状态下可以连线和拖动单个节点哦！" <<
                     "0那个长得像剪刀的东西其实是橡皮擦啦！\n用它点击节点就可以删除哦！" <<
                     "0如果想要一次性移动很多节点，\n框选住再用十字箭头移动就行啦！" <<
                     "0如果想要收回拉出去的连线，\n用箭头点一下连线的起点就行啦！" <<
                     "0今天你保存了吗？快快保存哦！" <<
                     "0听说有些很神奇的功能还没有做？\n敬请期待新版本吧！";
        tips_interaciton <<
                            "0怎么样，我很可爱吧！" <<
                            "0快去在B站上关注E17bits吧！" <<
                            "0喜欢的甜点是……香草冰淇淋！" <<
                            "0喜欢的水果是……西瓜和苹果！" <<
                            "2再这么用力地戳我，我可要报警了！" <<
                            "0？有什么事情吗？" <<
                            "2你是不是有什么奇怪的想法啊……" <<
                            "3等等，你在干嘛！" <<
                            "4呜呜，好痛！" <<
                     "0你知道武汉大学的布谷工作室吗？\n快来加入我们吧！" <<
                     "1ZZZZZZZZZZZZZZZZZZZZZ……\n呼啊……好困……" <<
                     "1我是谁，我在哪儿，我要去哪里……";
        tips_important <<
                          "0看起来帮助文档失踪了呢……\n快去找别人要一个新的吧！" << // 0 help.pdf lost
                          "0保存成功啦！\n这下就算崩溃了也不用担心！" << // 1 save finished
                          "3保存失败！？\n项目文件夹是不是搞丢了？" << // 2 save failed
                          "0打包完成！都是我的功劳哦！" << // 3 pack finished
                          "3打包失败！？\n项目文件夹是不是搞丢了？"; // 4 pack failed
    }

    delete file;

}

Window_editor_stage_tips::~Window_editor_stage_tips()
{
    timer->quit();
    timer->wait();
    delete timer;
}

void Window_editor_stage_tips::paintEvent(QPaintEvent *)
{
    Draw::smallWindow(this, this);

    float ss = Global::setting.editor_scale;

    if(Global::setting.tips_action == 2) return;
    Draw::begin(this);
    Draw::setAntialising(true);

    float mid_x = 282 * ss;
    float mid_y = 200 * ss;

    if(speakTimer >= 285) {
        Draw::sprite_size(faces[face].transformed(QMatrix().scale(ss, ss)),
                          416 * ss, sin((15.0 - speakTimer) / 15.0 * M_PI) * 30.0 * ss + 30 * ss, 384 * ss, 384 * ss);
        setPenColor_false();
        setBrushColor_ca(c_theme, 255.0 * (300.0 - speakTimer) / 15.0);
        Draw::roundRect(mid_x - 250 * ss, mid_y - 40 * ss, mid_x + 250 * ss, mid_y + 40 * ss, 10);
        //Draw::triangle(390, 200, 450, 200, 500, 140);
        setPenColor_ca(c_backgroundMain, 255.0 * (300.0 - speakTimer) / 15.0);
        Draw::setTextDefault();
        Draw::setTextSize(14 * ss);
        Draw::text(mid_x, mid_y, text);
    } else if(speakTimer <= 15) {
        Draw::sprite_size(faces[face].transformed(QMatrix().scale(ss, ss)), 416 * ss, 30 * ss, 384 * ss, 384 * ss);
        setPenColor_false();
        setBrushColor_ca(c_theme, 255.0 * (speakTimer / 15.0));
        Draw::roundRect(mid_x - 250 * ss, mid_y - 40 * ss, mid_x + 250 * ss, mid_y + 40 * ss, 10);
        //Draw::triangle(390, 200, 450, 200, 500, 140);
        setPenColor_ca(c_backgroundMain, 255.0 * (speakTimer / 15.0));
        Draw::setTextDefault();
        Draw::setTextSize(14 * ss);
        Draw::text(mid_x, mid_y, text);

    } else {
        Draw::sprite_size(faces[face].transformed(QMatrix().scale(ss, ss)), 416 * ss, 30 * ss, 384 * ss, 384 * ss);
        if(speakTimer) {
            setPenColor_false();
            setBrushColor_c(c_theme);
            Draw::roundRect(mid_x - 250 * ss, mid_y - 40 * ss, mid_x + 250 * ss, mid_y + 40 * ss, 10);
            //Draw::triangle(390, 200, 450, 200, 500, 140);
            setPenColor_c(c_backgroundMain);
            Draw::setTextDefault();
            Draw::setTextSize(14 * ss);
            Draw::text(mid_x, mid_y, text);
        }
    }
//    Draw::painter->drawPixmap(400, 0, 384, 384, faces[face].transformed(QMatrix().scale(
//                              384.0 / faces[face].width(), 384.0 / faces[face].height()), Qt::SmoothTransformation));

    Draw::end();
}

void Window_editor_stage_tips::mousePressEvent(QMouseEvent *event)
{
    float ss = Global::setting.editor_scale;

    if(event->button() != Qt::LeftButton) { event->ignore(); return; }
    if(Global::setting.tips_action != 0) { event->ignore(); return; }
    if(event->pos().x() > rect().left() + 416 * ss &&
       event->pos().y() > rect().top() + 46 * ss) {
        if(speakTimer >= 30 && speakTimer <= 270) speakTimer = 30;
        if(action == 0) {
            action = 2;
            action_timer += 800;
            text = tips_interaciton[rand() % tips_interaciton.size()];
            speakTimer = 300;
            face = text.leftRef(1).toInt();
            text = text.right(text.size() - 1);
            repaint();
        }
    } else { event->ignore(); return; }
}

void Window_editor_stage_tips::timeoutRepaint()
{
    if(!isActiveWindow()) return;
    if(Global::setting.tips_action == 2) return;

    if(important != -1) {
        action = 3;
        text = tips_important[important];
        important = -1;
        speakTimer = 300;
        face = text.leftRef(1).toInt();
        text = text.right(text.size() - 1);
        repaint();
        return;
    }

    if(speakTimer) speakTimer --;
    switch(action) {
    case 1: case 2: case 3: {
        if(!speakTimer) {
            action = 0;
            repaint();
        } else if(speakTimer >= 285 || speakTimer <= 15) repaint();
    } break;

    default: case 0: {
        action_timer += rand() % 2;
        if(Global::setting.tips_action == 0) {
            if(action_timer >= 1200) {
                action = 1;
                text = tips_auto[rand() % tips_auto.size()];
                action_timer = 0;
                speakTimer = 300;
                face = text.leftRef(1).toInt();
                text = text.right(text.size() - 1);
                repaint();
            }
        }
    } break;
    } // switch end

}

