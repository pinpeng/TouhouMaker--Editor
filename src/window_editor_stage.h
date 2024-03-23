#ifndef WINDOW_EDITOR_STAGE_H
#define WINDOW_EDITOR_STAGE_H

#include <QWidget>
#include <QTimer>

#include "dataSet/database/database.h"
#include "draw.h"

#include "window_editor_stage_tips.h"

#include "window_ask.h"

#include <QProcess>

class Window_editor_stage : public QWidget
{
    Q_OBJECT
public:
    explicit Window_editor_stage(QWidget *parent = nullptr);
    ~Window_editor_stage();
    void paintEvent(QPaintEvent *) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;

    QLabel *label[8];

private:
    QTimer *timer;

    QWidget *runnerWidget = nullptr;

    QProcess *runnerProcess = nullptr;

    enum RUNNER_STATE {
        IDLE,
        TEST_FROM_BEGINING,
        TEST_FROM_POINT
    };

    int runner_state = RUNNER_STATE::IDLE;

    int repaintTimer = 1;

    Window_editor_stage_tips *tips;

    int buff_id3 = -1;

    Database db;
    int file_id;

    float mouse_x = 0.0;
    float mouse_y = 0.0;

    float event_scroll_top = 0;
    float code_scroll_top = 0;

    QList<int> event_list;

    void lb_event(QRectF _rect, float mx, float my, float ss);
    void lb_game(QRectF _rect, float mx, float my, float ss);
    void lb_code(QRectF _rect, float mx, float my, float ss);

    void draw_event(QRectF _rect);
    void draw_game(QRectF _rect);
    void draw_code(QRectF _rect);

    Window_ask_ex *window_ask_ex;

signals:
    void requestUpdate(int _request_id);

private slots:
    void timeoutRepaint();

    void updateFromOutside(int _request_id);

    void codeEditFinished();
    void stageEditFinished();

public slots:

    void codeEditBossAddEventFinished();

    void codeEditBossAddThreadFinished();
};

#endif // WINDOW_EDITOR_STAGE_H
