#ifndef PETOWNER_H
#define PETOWNER_H
#include <QString>
#include <QStringList>
#include <QtSql>
#include <iostream>
#include <vector>
#include "pet.h"

class PetOwner
{
public:
    PetOwner();
    PetOwner(int id);
    PetOwner(QString email, QString password);
    PetOwner(QString p, QString fn, QString ln, QString e, QString loc);

    // accessor methods
    QString getPassword();
    QString getFirstName();
    QString getLastName();
    QString getEmail();
    QString getLocation();

    int getID();
    int getAge();
    QString getBreed();
    QString getColor();
    QString getHair();
    int getWeight();
    QString getOrigin();
    bool getAllergy();

    // mutator methods
    void setPassword(QString p);
    void setFirstName(QString fn);
    void setLastName(QString ln);
    void setEmail(QString e);
    void setLocation(QString loc);

    void setAge(int age);
    void setBreed(QString breed);
    void setColor(QString color);
    void setHair(QString hair);
    void setWeight(int weight);
    void setOrigin(QString origin);
    void setAllergy(bool a);

    // database methods
    bool insertIntoDB();
    bool deleteFromDB();
    bool existsInDB();
    bool attemptLogin();

    std::vector<Pet> getLikedPets();





private:
    int petOwnerID;
    QString password;
    QString firstName;
    QString lastName;
    QString email;
    QString location;

    // preferences
    int p_age;
    QString p_breed;
    QString p_color;
    QString p_hair_type;
    int p_weight;
    QString p_origin;
    bool p_allergy;
    void chooseID();
    std::vector<Pet> likedPets;
};

#endif // PETOWNER_H
