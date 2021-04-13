#include "shelter.h"

int shelter::getPhoneNumber()
{
    return phoneNumber;
}

QString shelter::getName()
{
    return name;
}

QString shelter::getLocation()
{
    return location;
}

QString shelter::getEmail()
{
    return email;
}

void shelter::setPhoneNumber(int p)
{
    this->phoneNumber = p;
}

void shelter::setName(QString n)
{
    this->name = n;
}

void shelter::setLocation(QString l)
{
    this->location = l;
}

void shelter::setEmail(QString e)
{
    this->email = e;
}

bool shelter::insertIntoDB()
{
    bool result;

    if (!existsInDB()) {
        QSqlQuery query;
        query.prepare("insert into Shelter (shelterID, name, location, email, phoneNumber)"
                      "values (?, ?, ?, ?, ?)");
        query.addBindValue(shelterID);
        query.addBindValue(name);
        query.addBindValue(location);
        query.addBindValue(email);
        query.addBindValue(phoneNumber);

        result = query.exec();

        if (!result)
            std::cerr << query.lastError().text().toStdString() << std::endl;
    } else {
        result = false;
    }

    return result;
}

bool shelter::deleteFromDB()
{
    QSqlQuery query;
    query.prepare("delete from Shelter where shelterID = ?");
    query.addBindValue(shelterID);

    return query.exec();
}
