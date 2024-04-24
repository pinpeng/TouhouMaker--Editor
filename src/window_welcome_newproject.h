    #ifndef WINDOW_WELCOME_NEWPROJECT_H
#define WINDOW_WELCOME_NEWPROJECT_H

#include "window_small.h"

#include "widget_lineEdit.h"
#include "widget_button.h"
#include "widget_roundbutton.h"


class Window_welcome_newProject : public Window_small
{

    Q_OBJECT

public:
    explicit Window_welcome_newProject(QWidget *parent = nullptr);
    ~Window_welcome_newProject();

    void paintEvent(QPaintEvent *);

private:

    Widget_LineEdit *lineEdit_projectName;
    Widget_LineEdit *lineEdit_projectPosition;

    Widget_Button *button_changePostion;

    QButtonGroup *buttonBox_type;

    Widget_RoundButton * round_base;
    Widget_RoundButton * round_empty;
    Widget_RoundButton * round_example;

    Widget_Button *button_accept;
    Widget_Button *button_cancel;


signals:
    void requestClose();

public slots:
    void findDir();
    void createProject();
};

#endif // WINDOW_WELCOME_NEWPROJECT_H
