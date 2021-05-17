#include "shelterhelp.h"
#include "ui_shelterhelp.h"
#include "shelterprofile.h"
#include "shelterupload.h"
#include "createaccount.h"
#include "mainwindow.h"

shelterhelp::shelterhelp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::shelterhelp)
{
    ui->setupUi(this);
}

shelterhelp::~shelterhelp()
{
    delete ui;
}

void shelterhelp::on_actionProfile_triggered()
{
    hide();
    shelterProfile *profileUI = new shelterProfile(this);
    profileUI->setAttribute(Qt::WA_DeleteOnClose);
    profileUI->show();
}

void shelterhelp::on_actionUpload_triggered()
{
    hide();
    shelterUpload *uploadUI = new shelterUpload(this);
    uploadUI->setAttribute(Qt::WA_DeleteOnClose);
    uploadUI->show();
}

void shelterhelp::on_actionLog_out_triggered()
{
    hide();
    MainWindow *login = new MainWindow(this);
    login->setAttribute(Qt::WA_DeleteOnClose);
    login->show();
}

void shelterhelp::on_actionQuit_triggered()
{
   QApplication::quit();
}

void shelterhelp::on_actionAbout_BreadnButter_triggered()
{
    QMessageBox::about(this, "About BreadnButter", "Welcome to BreadnButter!\n "
           "This applications allows quick, efficient and effective services for those looking for pets!\n"
           "If you are looking for people to adopt your pets, please don't hesistate to make a shelter account!");
}
