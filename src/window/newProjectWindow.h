#ifndef WINDOW_WELCOME_NEWPROJECT_H
#define WINDOW_WELCOME_NEWPROJECT_H

#include "window/smallWindow.h"

#include "widget/ellipticalLineEdit.h"
#include "widget/gradientButton.h"
#include "widget/roundButton.h"


class NewProjectWindow : public SmallWindow
{

    Q_OBJECT

public:
    explicit NewProjectWindow(QWidget *parent = nullptr);
    ~NewProjectWindow();

    void paintEvent(QPaintEvent *);

private:

    EllipticalLineEdit * _projectNameLineEdit;
    EllipticalLineEdit * _projectDirLineEdit;

    GradientButton * _findProjectButton;

    QButtonGroup *buttonBox_type;

    RoundButton * round_base;
    RoundButton * round_empty;
    RoundButton * round_example;

    GradientButton *_acceptButton;
    GradientButton *_cancelButton;


signals:
    void requestClose();

public slots:
    void findOldProjectSlot();
    void createProjectSlot();
    void buttonPressSlot(int id);
};

#endif // WINDOW_WELCOME_NEWPROJECT_H
