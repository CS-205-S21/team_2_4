#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <QtSql>

#include "gtest/gtest.h"
#include "../backend/petowner.h"
#include "../backend/shelter.h"
#include "../backend/pet.h"
#include "../backend/user.h"
#include "../gui/shelterprofilesqlmodel.h"

using namespace std;

class AdopterTest : public ::testing::Test {
protected:
    PetOwner *owner;

public:
    AdopterTest() {
        owner = new PetOwner("hello", "jonny", "appleseed", "themapples@gmail.com", "4845427676", "Seattle");
    }

    void TearDown() {
        owner->deleteFromDB();
    }
};

class PetTest : public ::testing::Test {
protected:
    Pet *pet;

public:
    PetTest() {
        pet = new Pet(true, "Fuzzy Wuzzy", 4, "Turkish Van", "brown", "medium", 8, "Shelter", true, "Lorem Ipsum");
    }

    void TearDown() {
        pet->deleteFromDB();
    }
};

class ShelterTest : public ::testing::Test {
protected:
    Shelter *shelter;

public:
    ShelterTest() {
        shelter = new Shelter("Who Let the Paws Out?", "Pittsburgh", "paws@paws.com");
    }

    void TearDown() {
        shelter->deleteFromDB();
    }
};

TEST_F(AdopterTest, TestNewAdopter) {
    if (!owner->existsInDB())
        EXPECT_EQ(owner->insertInDB(), true);
    else
        EXPECT_EQ(owner->insertInDB(), false);
}

TEST_F(AdopterTest, DISABLED_TestLogin) {
    ASSERT_EQ(owner->attemptLogin(), true);
}

TEST_F(AdopterTest, TestDeleteAdopter) {
    ASSERT_EQ(owner->deleteFromDB(), true);
}

TEST_F(PetTest, TestInsertPet) {
    ASSERT_EQ(pet->insertIntoDB(100), true);
}

TEST_F(PetTest, TestUpdatePet) {
    QSqlQuery query;
    query.prepare("update pet set age = ? where pet_id = ?");
    query.addBindValue(13);
    query.addBindValue(pet->getPet_id());

    ASSERT_EQ(query.exec(), true);
}

TEST_F(PetTest, TestLikePet) {
    PetOwner owner(201);
    ASSERT_EQ(owner.likePet(*pet), true);
}

TEST_F(ShelterTest, TestInsertShelter) {
    if (shelter->existsInDB())
        ASSERT_EQ(shelter->insertIntoDB(), false);
    else
        ASSERT_EQ(shelter->insertIntoDB(), true);
}

TEST(TestRead, TestReadShelter) {
    QSqlQuery query("select max(shelter_id) from Shelter");

    if (query.next()) {
        int maxID = query.value(0).toInt();

        srand(time(0));
        int id = rand() % maxID + 1;

        query.prepare("select * from Shelter where shelter_id = ?");
        query.addBindValue(id);

        if (query.exec()) {
            while (query.next()) {
                int nameIndex = query.record().indexOf("name");
                QString name = query.value(nameIndex).toString();
                ASSERT_EQ(name.isEmpty(), false);
            }
        }
    }
}

TEST(TestRead,TestReadPet) {
    QSqlQuery query("select max(pet_id) from Pet");

    if (query.next()) {
        int maxID = query.value(0).toInt();

        srand(time(0));
        int id = rand() % maxID + 1;

        query.prepare("select * from Pet where pet_id = ?");
        query.addBindValue(id);

        if (query.exec()) {
            while (query.next()) {
                int nameIndex = query.record().indexOf("name");
                QString name = query.value(nameIndex).toString();
                ASSERT_EQ(name.isEmpty(), false);
            }
        }
    }
}

TEST (TestRead, TestReadDogsOnly) {
    QSqlQuery query;
    if (query.exec("select * from Pet where is_cat = 0")) {
        ASSERT_EQ(query.next(), true);
    } else {
        qDebug() << "Error querying dogs:" << query.lastError().text();
    }
}

TEST(TestRead, GetPetsFromShelter) {
    QSqlQuery query("select max(shelter_id) from Shelter");

    if (query.next()) {
        int maxID = query.value(0).toInt();

        srand(time(0));
        int id = rand() % maxID + 1;

        Shelter s(id);

        ASSERT_EQ(s.getPets().size() > 0, true);
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("test_db.sqlite");

    if (!db.open())
        qFatal("Error opening database.");

    return RUN_ALL_TESTS();
}
