#include "shelterowner.h"

ShelterOwner::~ShelterOwner()
{

}

ShelterOwner::ShelterOwner(QString email, QString password)
{
    this->email = email;
    this->password = password;
}

ShelterOwner::ShelterOwner(int id)
{
    this->id = id;

    QSqlQuery query;
    query.prepare("select * from User where user_id = ?");
    query.addBindValue(id);

    if (query.exec()) {
        if (query.next()) {
            int nameIndex = query.record().indexOf("name");
            int emailIndex = query.record().indexOf("email");
            int passwordIndex = query.record().indexOf("password");
            int phoneIndex = query.record().indexOf("phone");

            QString aName = query.value(nameIndex).toString();
            QString aEmail = query.value(emailIndex).toString();
            QString aPassword = query.value(passwordIndex).toString();
            QString aPhoneNum = query.value(phoneIndex).toString();

            QStringList pieces = aName.split(" ");
            for (int i = 0; i < pieces.size(); i++) {
                if (i == 0)
                    this->firstName = pieces.at(i);
                else if (i == 1)
                    this->lastName = pieces.at(i);
            }

            this->email = aEmail;
            this->password = aPassword;
            this->phoneNumber = aPhoneNum;
        }
    } else {
        qDebug() << "Error creating adopter:" << query.lastError().text();
    }
}

ShelterOwner::ShelterOwner(QString fn, QString ln, QString loc, QString e, QString p)
{
    this->firstName = fn;
    this->lastName = ln;
    this->location = loc;
    this->email = e;
    this->password = p;
}

bool ShelterOwner::insertInDB()
{
    bool result;

    if (!existsInDB()) {
        QSqlQuery query;
        query.prepare("insert into User (name, location, email, password, is_adopter)"
                      "values (?, ?, ?, ?, ?)");
        query.addBindValue(firstName + " " + lastName);
        query.addBindValue(location);
        query.addBindValue(email);
        query.addBindValue(password);
        query.addBindValue(0);

        result = query.exec();

        if (!result)
            qDebug() << "Error inserting shelter owner:" << query.lastError().text();

        id = query.lastInsertId().toInt();
    }

    return result;
}

bool ShelterOwner::deleteFromDB()
{
    bool result;

    QSqlQuery query;
    query.prepare("delete from User where user_id = ?");
    query.addBindValue(id);

    result = query.exec();

    if (!result)
        qDebug() << "Error deleting shelter owner:" << query.lastError().text();

    return result;
}

bool ShelterOwner::existsInDB()
{
    QSqlQuery query;
    query.prepare("select email from User where email = ?");
    query.addBindValue(email);

    if (query.exec()) {
        while (query.next()) {
            QString dbEmail = query.value(0).toString();

            int compare = QString::compare(email, dbEmail, Qt::CaseInsensitive);
            if (compare == 0)
                return true;
        }
    } else {
        qDebug() << "Error searching for adopter in DB:" << query.lastError().text();
    }

    return false;
}
