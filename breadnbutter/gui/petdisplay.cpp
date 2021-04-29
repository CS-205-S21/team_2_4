#include "petdisplay.h"
#include "ui_petdisplay.h"

PetDisplay::PetDisplay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PetDisplay)
{
    ui->setupUi(this);
    ui->statusbar->showMessage("number of pets liked or number of pets viewed here");

    QString photoFilePath(":/resources/imgs/petPhoto0.jpg");
    petPic.load(photoFilePath);
    int width = ui->animalDisplay->width();
    int height = ui->animalDisplay->height();
    ui->animalDisplay->setPixmap(petPic.scaled(width, height, Qt::KeepAspectRatio));

    currentPos = 0;
    fetchPets();
    getCurrentUser();

    if (pets.size() > 0)
        displayPet(pets.front());
}

PetDisplay::~PetDisplay()
{
    delete ui;
}

void PetDisplay::on_actionQuit_triggered()
{
   QApplication::quit();
}

// changes available breeds based on pet type
void PetDisplay::on_typeBox_activated(const QString &arg1)
{
    std::vector<std::string> dogBreedList = {"Any", "Affenpinscher", "Curly-Coated Retriever",
                               "Foxhound", "Lakeland Terrier"};
    if (arg1 == "Dog") {

        // clearing all of the drop down menus
        ui->breedBox->clear();
        ui->colorBox->clear();
        ui->hairLenBox->clear();
//        ui->hypoBox->clear();

        for (unsigned long i = 0; i < dogBreedList.size(); i++) {
            ui->breedBox->addItem(dogBreedList[i].data());
        }
    }


    std::vector<std::string> catBreedList = {"Any", "Abyssinian", "Manx",
                               "Russian Blue", "Sphynx"};
    if (arg1 == "Cat") {

        // clearing all of the drop down menus
        ui->breedBox->clear();
        ui->colorBox->clear();
        ui->hairLenBox->clear();
//        ui->hypoBox->clear();

        for (unsigned long j = 0; j < catBreedList.size(); j++) {
            ui->breedBox->addItem(catBreedList[j].data());
        }
    }
}

void PetDisplay::on_breedBox_activated(const QString &arg1)
{
    std::vector<std::string> affenpinscherColors = {"Any", "Black", "Grey", "Red", "Tan",
                                                   "Silver", "Beige"};

    // handle dog breeds colors and hair length -- maybe use a map with key val pairs
    // loaded from the database?
    if (arg1 == "Affenpinscher") {
        ui->colorBox->clear();
        ui->hairLenBox->clear();
        for (unsigned long k = 0; k < affenpinscherColors.size(); k++) {
            ui->colorBox->addItem(affenpinscherColors[k].data());
        }
        ui->hairLenBox->addItem("Any");
        ui->hairLenBox->addItem("Long");
        ui->hairLenBox->addItem("Short");
    }

    std::vector<std::string> curlyCoatedRetrieverColors = {"Any", "Black", "Liver"};
    if (arg1 == "Curly-Coated Retriever") {
        ui->colorBox->clear();
        ui->hairLenBox->clear();
        for (unsigned long i = 0; i < curlyCoatedRetrieverColors.size(); i++) {
            ui->colorBox->addItem(curlyCoatedRetrieverColors[i].data());
        }
        ui->hairLenBox->addItem("Any");
        ui->hairLenBox->addItem("Medium");
        ui->hairLenBox->addItem("Short");
    }

    std::vector<std::string> foxhoundColors = {"Any", "White", "Tan", "Blue", "Tri-color",
                                              "White & Cream", "Red"};
    if (arg1 == "Foxhound") {
        ui->colorBox->clear();
        ui->hairLenBox->clear();
        for (unsigned long i = 0; i < foxhoundColors.size(); i++) {
            ui->colorBox->addItem(foxhoundColors[i].data());
        }
        ui->hairLenBox->addItem("Any");
        ui->hairLenBox->addItem("Medium");
        ui->hairLenBox->addItem("Short");
    }

    std::vector<std::string> lakelandTerrierColors = {"Any", "Black", "Wheaten", "Black and Tan",
                                                      "Blue", "Grizzle & Tan", "Red"};
    if (arg1 == "Lakeland Terrier") {
        ui->colorBox->clear();
        ui->hairLenBox->clear();
        for (unsigned long i = 0; i < lakelandTerrierColors.size(); i++) {
            ui->colorBox->addItem(lakelandTerrierColors[i].data());
        }
        ui->hairLenBox->addItem("Any");
        ui->hairLenBox->addItem("Long");
        ui->hairLenBox->addItem("Medium");
    }



    std::vector<std::string> abyssinianColors = {"Any", "Ruddy", "Sorrel", "Blue", "Fawn",
                                                "Chocolate", "Silver", "Lilac"};
    // handle cat breeds colors and hair length -- maybe use a map with key val pairs
    // loaded from the database?
    if (arg1 == "Abyssinian") {
        ui->colorBox->clear();
        ui->hairLenBox->clear();
        for (unsigned int i = 0; i < abyssinianColors.size(); i++) {
            ui->colorBox->addItem(abyssinianColors[i].data());
        }
        ui->hairLenBox->addItem("Short");
    }

    std::vector<std::string> manxColors = {"Any", "White", "Blue", "Black", "Red",
                                                "Cream", "Silver", "Tortoiseshell",
                                          "Bluecream", "Brown"};
    if (arg1 == "Manx") {
        ui->colorBox->clear();
        ui->hairLenBox->clear();
        for (unsigned int i = 0; i < manxColors.size(); i++) {
            ui->colorBox->addItem(manxColors[i].data());
        }
        ui->hairLenBox->addItem("Any");
        ui->hairLenBox->addItem("Long");
        ui->hairLenBox->addItem("Medium");
    }

    std::vector<std::string> russianBlueColors = {"Any", "Silver", "Dark Grey"};
    if (arg1 == "Russian Blue") {
        ui->colorBox->clear();
        ui->hairLenBox->clear();
        for (unsigned int i = 0; i < russianBlueColors.size(); i++) {
            ui->colorBox->addItem(russianBlueColors[i].data());
        }
        ui->hairLenBox->addItem("Short");
    }

    std::vector<std::string> sphynxColors = {"Any", "White", "Black", "Red", "Brown",
                                            "Lavender"};
    if (arg1 == "Sphynx") {
        ui->colorBox->clear();
        ui->hairLenBox->clear();
        for (unsigned int i = 0; i < sphynxColors.size(); i++) {
            ui->colorBox->addItem(sphynxColors[i].data());
        }
        ui->hairLenBox->addItem("Hairless");
    }
}

void PetDisplay::on_pushButton_clicked()
{
    QString noticeString = "Search button clicked! Your pet type is ";
    noticeString.append(ui->typeBox->currentText());
    QMessageBox::information(this, "Hurray!", noticeString);
    //QMessageBox searchBox;
    //searchBox.setText("Hurray!\nSearch button clicked!");
    //searchBox.exec();
}

void PetDisplay::displayPet(Pet p)
{
    int numberOfPhotos = 8;

    srand(time(0));
    int photoNum = rand() % numberOfPhotos;

    QString photoString = QString::number(photoNum);

    QString tempPath(":/resources/imgs/petPhoto");
    tempPath.append(photoString);
    QString filePath = tempPath.append(".jpg");
    qDebug() << filePath;

    petPic.load(filePath);
    int width = ui->animalDisplay->width();
    int height = ui->animalDisplay->height();
    ui->animalDisplay->setPixmap(petPic.scaled(width, height, Qt::KeepAspectRatio));

    ui->label_name->setText(p.getName());
    ui->label_breed->setText(p.getBreed());

    if (!p.getIs_cat())
        ui->label_type->setText("Dog");
    else
        ui->label_type->setText("Cat");

    QSqlQuery query;
    query.prepare("select shelter_id from pet where pet_id = ?");
    query.addBindValue(p.getPet_id());

    // This does not update the label text when the dislike button is selected.
    if (query.exec()) {
        if (query.next()) {
            int shelterID = query.value(0).toInt();

            Shelter s(shelterID);
            ui->label_shelter_name->setText(s.getName());
            ui->label_location->setText(s.getLocation());
        }
    } else {
        qDebug() << "Error getting pet's shelter:" << query.lastError().text();
    }
}

void PetDisplay::getCurrentUser()
{
    QString name = currentUser.getFirstName();
    ui->label_user_name->setText("<b><FONT COLOR=red>Welcome " + name + "!<FONT></b>");
}

void PetDisplay::on_profileButton_clicked()
{
   profileUI = new PetProfile(this);
   profileUI->setPDisplay(pets.at(currentPos));
   profileUI->setModal(true);
   profileUI->exec();
}

void PetDisplay::on_button_like_clicked()
{
    Pet currPet = pets.at(currentPos);

    QSqlQuery query;
    query.prepare("insert into Liked_By (adopter_id, pet_id)"
                  "values (?, ?)");
    query.addBindValue(currentUser.getID());
    query.addBindValue(currPet.getPet_id());

    if (query.exec()) {
        currentPos++;
        displayPet(pets.at(currentPos));
    } else {
        qDebug() << "Error liking pet:" << query.lastError().text();
    }
}

void PetDisplay::on_button_dislike_clicked()
{
    currentPos++;
    displayPet(pets.at(currentPos));
}

void PetDisplay::fetchPets()
{
    QSqlQuery query;
    if (query.exec("select pet_id from Pet")) {
        while (query.next()) {
            int pID = query.value(0).toInt();

            Pet p(pID);
            pets.push_back(p);
        }
    } else {
        qDebug() << "Error fetching pets:" << query.lastError().text();
    }
}

void PetDisplay::on_actionLogout_triggered()
{
    hide();

    currentUser.logOut();
    parentWidget()->show();
}

void PetDisplay::on_actionLiked_triggered()
{
    hide();
    likedUI = new PetLiked(this);
    likedUI->show();
}
