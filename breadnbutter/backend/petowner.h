#ifndef PETOWNER_H
#define PETOWNER_H
#include <QString>
#include <QStringList>
#include <QtSql>
#include <iostream>
#include "pet.h"
#include "user.h"

class PetOwner : public User
{
public:
    ~PetOwner();
    PetOwner(QString email, QString password);
    PetOwner(int id);
    PetOwner(QString p, QString fn, QString ln, QString e, QString ph, QString city);

    // accessor methods
    QString getPassword();
    QString getLastName();
    QString getEmail();
    QString getPhone();

    int getAgeMin();
    int getAgeMax();
    QString getBreed();
    QString getColor();
    QString getHair();
    int getWeightMin();
    int getWeightMax();
    QString getOrigin();
    bool getAllergy();
    bool getWantsCat();

    // mutator methods
    void setPassword(QString p);
    void setFirstName(QString fn);
    void setLastName(QString ln);
    void setEmail(QString e);
    void setPhone(QString phone);

    void setAgeMin(int age);
    void setAgeMax(int age);
    void setBreed(QString breed);
    void setColor(QString color);
    void setHair(QString hair);
    void setWeightMin(int weight);
    void setWeightMax(int weight);
    void setOrigin(QString origin);
    void setAllergy(bool a);
    void setWantsCat(bool w);

    bool likePet(Pet p);

    // database methods
    bool insertInDB();
    bool deleteFromDB();
    bool existsInDB();
private:
    // preferences
    int p_age_min, p_age_max;
    QString p_breed;
    QString p_color;
    QString p_hair_type;
    int p_weight_min, p_weight_max;
    QString p_origin;
    bool p_allergy;
    bool wants_cat;

    bool hasLikedPet(Pet p);
};

#endif // PETOWNER_H
