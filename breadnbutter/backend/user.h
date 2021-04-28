#ifndef USER_H
#define USER_H

#include <QString>
#include <QtSql>
#include <iostream>

class User
{
public:
    User();
    User(QString email, QString password);
    virtual ~User();

    virtual bool insertInDB();
    virtual bool deleteFromDB();
    virtual bool existsInDB();

    bool attemptLogin();

    int getID();

    QString getFirstName();

    bool getIs_adopter() const;

    QString getLastName() const;

protected:
    int id;
    QString firstName;
    QString lastName;
    QString location;
    QString email;
    QString password;

    bool is_adopter;

    virtual void chooseID();
};

#endif // USER_H
