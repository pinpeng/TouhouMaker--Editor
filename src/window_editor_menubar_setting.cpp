#include "window_editor_menubar_setting.h"

Window_editor_menubar_setting::Window_editor_menubar_setting(QWidget *parent) : SmallWindow(parent)
{
    setFixedSize(1200, 800);
    setWindowTitle("游戏设置（请参照帮助文档）");

    db = Global::database();

    button_accept = new GradientButton(this);
    button_accept->setGeometry(580, 704, 240, 80);
    button_accept->setText("确定");
    // button_accept->setTimer(_timer);

    button_cancel = new GradientButton(this);
    button_cancel->setGeometry(836, 704, 240, 80);
    button_cancel->setText("取消");
    // button_cancel->setTimer(_timer);

    connect(button_accept, SIGNAL(pressed()), this, SLOT(accept()));
    connect(button_cancel, SIGNAL(pressed()), this, SLOT(end()));

    /*buttonBox_start_with_logo = new QButtonGroup(this);
    roundButton_swl_yes = new Widget_RoundButton(this);
    roundButton_swl_yes->setTimer(_timer);
    roundButton_swl_yes->setText("使用");
    roundButton_swl_yes->setGeometry(480, 128, 160, 48);
    roundButton_swl_no = new Widget_RoundButton(this);
    roundButton_swl_no->setTimer(_timer);
    roundButton_swl_no->setText("不使用");
    roundButton_swl_no->setGeometry(720, 128, 160, 48);

    buttonBox_start_with_logo->addButton(roundButton_swl_yes);
    buttonBox_start_with_logo->addButton(roundButton_swl_no);
    if(db.info.setting_start_with_logo == 0) roundButton_swl_yes->setChecked(true);
    if(db.info.setting_start_with_logo == 1) roundButton_swl_no->setChecked(true);

    buttonBox_reading_action= new QButtonGroup(this);
    roundButton_ra_default = new Widget_RoundButton(this);
    roundButton_ra_default->setTimer(_timer);
    roundButton_ra_default->setText("不管（推荐）");
    roundButton_ra_default->setGeometry(480, 240, 200, 48);
    roundButton_ra_static = new Widget_RoundButton(this);
    roundButton_ra_static->setTimer(_timer);
    roundButton_ra_static->setText("强制静态");
    roundButton_ra_static->setGeometry(720, 240, 200, 48);
    roundButton_ra_dynamic = new Widget_RoundButton(this);
    roundButton_ra_dynamic->setTimer(_timer);
    roundButton_ra_dynamic->setText("强制动态");
    roundButton_ra_dynamic->setGeometry(960, 240, 200, 48);
    roundButton_ra_custom = new Widget_RoundButton(this);
    roundButton_ra_custom->setTimer(_timer);
    roundButton_ra_custom->setText("对每一项进行自定义");
    roundButton_ra_custom->setGeometry(480, 300, 320, 48);
    buttonBox_reading_action->addButton(roundButton_ra_default);
    buttonBox_reading_action->addButton(roundButton_ra_static);
    buttonBox_reading_action->addButton(roundButton_ra_dynamic);
    buttonBox_reading_action->addButton(roundButton_ra_custom);
    if(db.info.setting_reading_aciton == 0) roundButton_ra_default->setChecked(true);
    if(db.info.setting_reading_aciton == 1) roundButton_ra_static->setChecked(true);
    if(db.info.setting_reading_aciton == 2) roundButton_ra_dynamic->setChecked(true);
    if(db.info.setting_reading_aciton == 3) roundButton_ra_custom->setChecked(true);

    button_ra_custom = new GradientButton(this);
    button_ra_custom->setTimer(_timer);
    button_ra_custom->setText("自定义行为...");
    button_ra_custom->setGeometry(850, 280, 320, 80);
    connect(button_ra_custom, SIGNAL(pressed()), this, SLOT(ra_custom()));

    buttonBox_using_cg_collection = new QButtonGroup(this);
    roundButton_ucc_yes = new Widget_RoundButton(this);
    roundButton_ucc_yes->setTimer(_timer);
    roundButton_ucc_yes->setText("使用");
    roundButton_ucc_yes->setGeometry(480, 410, 160, 48);
    roundButton_ucc_no = new Widget_RoundButton(this);
    roundButton_ucc_no->setTimer(_timer);
    roundButton_ucc_no->setText("不使用");
    roundButton_ucc_no->setGeometry(720, 410, 160, 48);

    buttonBox_using_cg_collection->addButton(roundButton_ucc_yes);
    buttonBox_using_cg_collection->addButton(roundButton_ucc_no);
    if(db.info.setting_using_cg_collection == 0) roundButton_ucc_yes->setChecked(true);
    if(db.info.setting_using_cg_collection == 1) roundButton_ucc_no->setChecked(true);*/

    lineEdit_name = new EllipticalLineEdit(this);
    lineEdit_name->setGeometry(480, 510, 480, 80);
    lineEdit_name->setText(db.info.projectName);

    button_reset_name = new GradientButton(this);
    // button_reset_name->setTimer(_timer);
    button_reset_name->setText("重置");
    button_reset_name->setGeometry(964, 510, 205, 80);
    connect(button_reset_name, SIGNAL(pressed()), this, SLOT(reset_projectName()));

    itemList_lan = new Widget_ItemList(this);
    QList<QString> tmp_list;
    tmp_list << "顺序" << "名称";
    itemList_lan->setHeadTextList(tmp_list);
    itemList_lan->setHeadWidthList({64, 64});
    itemList_lan->setGeometry(16, 124, 440, 580);

    button_lan_add = new GradientButton(this);
    // button_lan_add->setTimer(_timer);
    button_lan_add->setText("添加");
    button_lan_add->setGeometry(16, 704, 220, 80);
    button_lan_del = new GradientButton(this);
    // button_lan_del->setTimer(_timer);
    button_lan_del->setText("删除");
    button_lan_del->setGeometry(16 + 220, 704, 220, 80);

    connect(button_lan_add, SIGNAL(pressed()), this, SLOT(lan_add()));
    connect(button_lan_del, SIGNAL(pressed()), this, SLOT(lan_del()));
    connect(itemList_lan, SIGNAL(doubleClicked(int)), this, SLOT(lan_edit(int)));

    updateList();

}

void Window_editor_menubar_setting::paintEvent(QPaintEvent *)
{
    Draw::smallWindow(this, this);
    Draw::begin(this);
    Draw::setAntialising(true);

    setPenColor_c(c_symbol);
    Draw::line(464, 80, 464, 770, 2);

    Draw::setTextDefault();
    setPenColor_c(c_textMain);
    Draw::text(232, 96, "语言设置");

    Draw::text(480, 96, "游戏启动时播放logo", Qt::AlignLeft | Qt::AlignVCenter);
    Draw::text(480, 208, "资源读取行为的全局设定", Qt::AlignLeft | Qt::AlignVCenter);
    Draw::text(480, 378, "启用CG收集功能", Qt::AlignLeft | Qt::AlignVCenter);
    Draw::text(480, 488, "重命名项目", Qt::AlignLeft | Qt::AlignVCenter);

    Draw::end();
}

void Window_editor_menubar_setting::updateList()
{
    QList<itemSTR> tmpList;
    for(int i = 0; i < db.info.language.size(); i ++) {
        itemSTR tmp;
        tmp.text << QString::number(i + 1) << db.info.language[i];
    }
    itemList_lan->setItemList(tmpList);
}

void Window_editor_menubar_setting::accept()
{

    /*if(roundButton_swl_yes->isChecked()) db.info.setting_start_with_logo = 0;
    if(roundButton_swl_no->isChecked()) db.info.setting_start_with_logo = 1;

    if(roundButton_ra_default->isChecked()) db.info.setting_reading_aciton = 0;
    if(roundButton_ra_static->isChecked()) db.info.setting_reading_aciton = 1;
    if(roundButton_ra_dynamic->isChecked()) db.info.setting_reading_aciton = 2;
    if(roundButton_ra_custom->isChecked()) db.info.setting_reading_aciton = 3;

    if(roundButton_ucc_yes->isChecked()) db.info.setting_using_cg_collection = 0;
    if(roundButton_ucc_no->isChecked()) db.info.setting_using_cg_collection = 1;*/

    db.info.projectName = lineEdit_name->text();

    Global::databaseUpdate(db);
    end();
}

void Window_editor_menubar_setting::lan_add()
{
    db.info.language.append("新语言");
    updateList();
}

void Window_editor_menubar_setting::lan_del()
{
    int tmp = itemList_lan->index();
    if(tmp < 0) {
        TransparentDialog::play("没选怎么删除呀");
        return;
    }
    if(tmp == 0) {
        TransparentDialog::play("必须保留一项");
        return;
    }
    if(tmp != itemList_lan->getItemSize() - 1) {
        TransparentDialog::play("只能删最后一项");
        return;
    }
    db.info.language.removeAt(tmp);
    TransparentDialog::play("删除成功");
    updateList();
}

void Window_editor_menubar_setting::lan_edit(int pos)
{
    window_language = new Window_editor_menubar_setting_language(&db.info.language[pos]);
    connect(window_language, SIGNAL(changed()), this, SLOT(lan_edit_finished()));
    window_language->setWindowModality(Qt::ApplicationModal);
    window_language->setAttribute(Qt::WA_DeleteOnClose);
    window_language->show();
}

void Window_editor_menubar_setting::lan_edit_finished()
{
    updateList();
}

void Window_editor_menubar_setting::reset_projectName()
{
    lineEdit_name->setText(db.info.projectName);
}

/*void Window_editor_menubar_setting::ra_custom()
{
    window_ra_custom = new Window_editor_menubar_setting_ra(&db);
    window_ra_custom->setWindowModality(Qt::ApplicationModal);
    window_ra_custom->setAttribute(Qt::WA_DeleteOnClose);
    window_ra_custom->show();

}*/




