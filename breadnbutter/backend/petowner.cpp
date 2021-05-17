#include "petowner.h"

bool PetOwner::existsInDB()
{
    QSqlQuery query;
    query.prepare("select email from User where email = ?");
    query.addBindValue(email);

    if (query.exec()) {
        return query.next();
    } else {
        qDebug() << "Error searching for adopter in DB:" << query.lastError().text();
    }

    return false;
}

void PetOwner::setLocation(QString loc)
{
    location = loc;
}

void PetOwner::setPhone(QString phone)
{
    phoneNumber = phone;
}

QString PetOwner::getLocation()
{
    return location;
}

QString PetOwner::getPhone()
{
    return phoneNumber;
}

PetOwner::~PetOwner()
{

}

PetOwner::PetOwner(QString email, QString password)
{
    this->email = email;
    this->password = password;
}

PetOwner::PetOwner(int id)
{
    this->id = id;
    this->is_adopter = true;

    QSqlQuery query;
    query.prepare("select * from User where user_id = ?");
    query.addBindValue(id);

    if (query.exec()) {
        if (query.next()) {
            QString aName = query.value(1).toString();
            QString aEmail = query.value(3).toString();
            QString aPhone = query.value(4).toString();
            QString aPassword = query.value(5).toString();

            QStringList pieces = aName.split(" ");
            for (int i = 0; i < pieces.size(); i++) {
                if (i == 0)
                    this->firstName = pieces.at(i);
                else if (i == 1)
                    this->lastName = pieces.at(i);
            }

            this->email = aEmail;
            this->phoneNumber = aPhone;
            this->password = aPassword;
        }
    } else {
        qDebug() << "Error creating adopter:" << query.lastError().text();
    }
}

PetOwner::PetOwner(QString p, QString fn, QString ln, QString e, QString ph, QString loc)
{
    this->password = p;
    this->firstName = fn;
    this->lastName = ln;
    this->email = e;
    this->phoneNumber = ph;
    this->location = loc;
    this->is_adopter = true;
}

QString PetOwner::getPassword()
{
    return password;
}

QString PetOwner::getLastName()
{
    return lastName;
}

QString PetOwner::getEmail()
{
    return email;
}

int PetOwner::getAge()
{
    return this->p_age;
}

QString PetOwner::getBreed()
{
    return this->p_breed;
}

QString PetOwner::getColor()
{
    return this->p_color;
}

QString PetOwner::getHair()
{
    return this->p_hair_type;
}

int PetOwner::getWeight()
{
    return this->p_weight;
}

QString PetOwner::getOrigin()
{
    return this->p_origin;
}

bool PetOwner::getAllergy()
{
    return this->p_allergy;
}

void PetOwner::setPassword(QString p)
{
    this->password = p;
}

void PetOwner::setFirstName(QString fn)
{
    this->firstName = fn;
}

void PetOwner::setLastName(QString ln)
{
    this->lastName = ln;
}

void PetOwner::setEmail(QString e)
{
    this->email = e;
}

void PetOwner::setAge(int age)
{
    this->p_age = age;
}

void PetOwner::setBreed(QString breed)
{
    this->p_breed = breed;
}

void PetOwner::setColor(QString color)
{
    this->p_color = color;
}

void PetOwner::setHair(QString hair)
{
    this->p_hair_type = hair;
}

void PetOwner::setWeight(int weight)
{
    this->p_weight = weight;
}

void PetOwner::setOrigin(QString origin)
{
    this->p_origin = origin;
}

void PetOwner::setAllergy(bool a)
{
    this->p_allergy = a;
}

bool PetOwner::hasLikedPet(Pet p)
{
    QSqlQuery query;
    query.prepare("select * from Liked_By where adopter_id = ? and pet_id = ?");
    query.addBindValue(id);
    query.addBindValue(p.getPet_id());

    bool ok = query.exec();

    if (ok) {
        return query.next();
    } else {
        qDebug() << "Error determining if pet was already liked:" << query.lastError().text();
    }

    return ok;
}

bool PetOwner::likePet(Pet p)
{
    if (!hasLikedPet(p)) {
        QSqlQuery query;
        query.prepare("insert into Liked_By (adopter_id, pet_id)"
                      "values (?, ?)");
        query.addBindValue(id);
        query.addBindValue(p.getPet_id());

        bool ok = query.exec();

        if (!ok)
            qDebug() << "Error liking pet:" << query.lastError().text();

        return ok;
    }

    return false;
}

bool PetOwner::insertInDB()
{
    bool result;

    if (!existsInDB()) {
        QSqlQuery query;
        query.prepare("insert into User (name, location, email, phone, password, is_adopter)"
                      "values (?, ?, ?, ?, ?, ?)");
        query.addBindValue(firstName + " " + lastName);
        query.addBindValue(location);
        query.addBindValue(email);
        query.addBindValue(phoneNumber);
        query.addBindValue(password);
        query.addBindValue(1);

        result = query.exec();

        if (!result)
            qDebug() << "Error inserting adopter:" << query.lastError().text();

        id = query.lastInsertId().toInt();
    }

    return result;
}

bool PetOwner::deleteFromDB()
{
    bool result;

    QSqlQuery query;
    query.prepare("delete from User where user_id = ?");
    query.addBindValue(id);

    result = query.exec();

    if (!result)
        std::cerr << query.lastError().text().toStdString() << std::endl;

    return result;
}
