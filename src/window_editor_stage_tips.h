// #ifndef WINDOW_EDITOR_STAGE_TIPS_H
// #define WINDOW_EDITOR_STAGE_TIPS_H

// #include <QWidget>
// #include <QTimer>
// #include "draw.h"

// #include <QEvent>

// #include "basethread.h"

// /**
//  * @brief 神秘的提示文本，现在没有用上
// */
// class Window_editor_stage_tips : public QWidget
// {
//     Q_OBJECT

// public:
//     explicit Window_editor_stage_tips(QWidget *parent = nullptr);
//     ~Window_editor_stage_tips();
//     void paintEvent(QPaintEvent *);

//     void mousePressEvent(QMouseEvent *event);

// #define send_tips(_id) Window_editor_stage_tips::important=_id
//     static int important;

// private:
//     BaseThread *timer;

//     int speakTimer;
//     int action; // 0 = waiting, 1 = auto speaking, 2 = interaction, 3 = important info
//     int action_timer;
//     int face; // 0 = happy, 1 = sleep, 2 = angry, 3 = worry, 4 = shy

//     QList<QPixmap> faces;
//     QString text;

//     QList<QString> tips_auto;
//     QList<QString> tips_interaciton;
//     QList<QString> tips_important;


// private slots:
//     void timeoutRepaint();


// };

// #endif // WINDOW_EDITOR_STAGE_TIPS_H
