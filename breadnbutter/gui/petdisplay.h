#ifndef PETDISPLAY_H
#define PETDISPLAY_H

#include <QMainWindow>
#include <QDebug>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <QMessageBox>
#include <QColor>
#include <QColorDialog>
#include <QtSql>
#include "../backend/globals.h"
#include "../backend/petowner.h"
#include "../backend/pet.h"
#include "petprofile.h"

namespace Ui {
class PetDisplay;
}

class PetDisplay : public QMainWindow
{
    Q_OBJECT

public:
    explicit PetDisplay(QWidget *parent = nullptr);
    ~PetDisplay();

private slots:
    void on_actionQuit_triggered();

    void on_typeBox_activated(const QString &arg1);

    void on_breedBox_activated(const QString &arg1);

    void on_pushButton_clicked();

    void on_profileButton_clicked();

    void on_button_like_clicked();

    void on_button_dislike_clicked();

    void on_actionLogout_triggered();

private:
    Ui::PetDisplay *ui;
    PetProfile *profileUI;
    QPixmap petPic;
    std::vector<Pet> pets;
    int currentPos;

    void fetchPets();
    void displayPet(Pet p);
    void getCurrentUser();
};

#endif // PETDISPLAY_H
