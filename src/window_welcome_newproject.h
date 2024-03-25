    #ifndef WINDOW_WELCOME_NEWPROJECT_H
#define WINDOW_WELCOME_NEWPROJECT_H

#include "window/smallWindow.h"

#include "widget/widget_lineEdit.h"
#include "widget/gradientButton.h"
#include "widget/widget_roundbutton.h"


class Window_welcome_newProject : public SmallWindow
{

    Q_OBJECT

public:
    explicit Window_welcome_newProject(QWidget *parent = nullptr);
    ~Window_welcome_newProject();

    void paintEvent(QPaintEvent *);

private:

    Widget_LineEdit *lineEdit_projectName;
    Widget_LineEdit *lineEdit_projectPosition;

    GradientButton *button_changePostion;

    QButtonGroup *buttonBox_type;

    Widget_RoundButton * round_base;
    Widget_RoundButton * round_empty;
    Widget_RoundButton * round_example;

    GradientButton *button_accept;
    GradientButton *button_cancel;


signals:
    void requestClose();

public slots:
    void findDir();
    void createProject();
};

#endif // WINDOW_WELCOME_NEWPROJECT_H
