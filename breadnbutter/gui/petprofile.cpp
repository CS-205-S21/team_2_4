#include "petprofile.h"
#include "ui_petprofile.h"

PetProfile::PetProfile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PetProfile)
{
    ui->setupUi(this);

    srand(time(0));

    catImageList = QDir(":/cats/Cats").entryList();
    dogImageList = QDir(":/dogs/Dogs").entryList();

    if (pDisplay.getIs_cat()) {
        int imageIndex = rand() % catImageList.size();

        QString imageName = catImageList.at(imageIndex);
        QString dirName = ":/cats/Cats/";
        dirName.append(imageName);

        qDebug() << "Loading" << dirName;
        petPic.load(dirName);
        ui->animalDisplay->setPixmap(petPic.scaled(ui->animalDisplay->width(), ui->animalDisplay->height(), Qt::KeepAspectRatio));
    } else {
        int imageIndex = rand() % dogImageList.size();

        QString imageName = dogImageList.at(imageIndex);
        QString dirName = ":/dogs/Dogs/";
        dirName.append(imageName);

        qDebug() << "Loading" << dirName;
        petPic.load(dirName);
        ui->animalDisplay->setPixmap(petPic.scaled(ui->animalDisplay->width(), ui->animalDisplay->height(), Qt::KeepAspectRatio));
    }

    // adding icons to the page
    QPixmap icon;

    QString iconName(":/icons/icons/Name.png");
    icon.load(iconName);
    ui->icon_name->setPixmap(icon.scaled(ui->icon_name->width(), ui->icon_name->height(), Qt::KeepAspectRatio));

    QString iconType(":/icons/icons/Type.png");
    icon.load(iconType);
    ui->icon_type->setPixmap(icon.scaled(ui->icon_type->width(), ui->icon_type->height(), Qt::KeepAspectRatio));

    QString iconBreed(":/icons/icons/Breed.png");
    icon.load(iconBreed);
    ui->icon_breed->setPixmap(icon.scaled(ui->icon_breed->width(), ui->icon_breed->height(), Qt::KeepAspectRatio));

    QString iconAge(":/icons/icons/Age.png");
    icon.load(iconAge);
    ui->icon_age->setPixmap(icon.scaled(ui->icon_age->width(), ui->icon_age->height(), Qt::KeepAspectRatio));

    QString iconColor(":/icons/icons/Color.png");
    icon.load(iconColor);
    ui->icon_color->setPixmap(icon.scaled(ui->icon_color->width(), ui->icon_color->height(), Qt::KeepAspectRatio));

    QString iconHair(":/icons/icons/Hair.png");
    icon.load(iconHair);
    ui->icon_hair->setPixmap(icon.scaled(ui->icon_hair->width(), ui->icon_hair->height(), Qt::KeepAspectRatio));

    QString iconWeight(":/icons/icons/Weight.png");
    icon.load(iconWeight);
    ui->icon_weight->setPixmap(icon.scaled(ui->icon_weight->width(), ui->icon_weight->height(), Qt::KeepAspectRatio));

    QString iconHypo(":/icons/icons/Hypoallergenic.png");
    icon.load(iconHypo);
    ui->icon_hypoallergenic->setPixmap(icon.scaled(ui->icon_hypoallergenic->width(), ui->icon_hypoallergenic->height(), Qt::KeepAspectRatio));

    QString iconOrigin(":/icons/icons/Origin.png");
    icon.load(iconOrigin);
    ui->icon_origin->setPixmap(icon.scaled(ui->icon_origin->width(), ui->icon_origin->height(), Qt::KeepAspectRatio));

    QString iconLocation(":/icons/icons/Location.png");
    icon.load(iconLocation);
    ui->icon_location->setPixmap(icon.scaled(ui->icon_location->width(), ui->icon_location->height(), Qt::KeepAspectRatio));

    QString iconShelter(":/icons/icons/Shelter.png");
    icon.load(iconShelter);
    ui->icon_shelter->setPixmap(icon.scaled(ui->icon_shelter->width(), ui->icon_shelter->height(), Qt::KeepAspectRatio));

    QString iconPhone(":/icons/icons/Phone.png");
    icon.load(iconPhone);
    ui->icon_phone->setPixmap(icon.scaled(ui->icon_phone->width(), ui->icon_phone->height(), Qt::KeepAspectRatio));

    QString iconEmail(":/icons/icons/Email.png");
    icon.load(iconEmail);
    ui->icon_email->setPixmap(icon.scaled(ui->icon_email->width(), ui->icon_email->height(), Qt::KeepAspectRatio));
}

PetProfile::~PetProfile()
{
    delete ui;
}


void PetProfile::setPDisplay(const Pet &value)
{
    pDisplay = value;

    fetchPet();
}

void PetProfile::fetchPet()
{
    ui->label_name->setText(pDisplay.getName());
    ui->label_breed->setText(pDisplay.getBreed());
    ui->label_age->setText(QString::number(pDisplay.getAge()));
    ui->label_color->setText(pDisplay.getColor());
    ui->label_weight->setText(QString::number(pDisplay.getWeight()));
    ui->label_origin->setText(pDisplay.getOrigin());
    ui->label_hair->setText(pDisplay.getHairLength());
    ui->descriptionBox->setPlainText(pDisplay.getDescription());

    if (pDisplay.getIs_cat())
        ui->label_type->setText("Cat");
    else
        ui->label_type->setText("Dog");

    if (pDisplay.getHypoallergenic())
        ui->label_hypo->setText("Yes");
    else
        ui->label_hypo->setText("No");

    QSqlQuery query;
    query.prepare("select shelter.owner_id, shelter.location "
                  "from pet "
                  "inner join shelter on shelter.shelter_id = pet.shelter_id "
                  "where pet.pet_id = ?");
    query.addBindValue(pDisplay.getPet_id());

    if (query.exec()) {
        if (query.next()) {
            int ownerIndex = query.record().indexOf("owner_id");
            int ownerID = query.value(ownerIndex).toInt();

            int locIndex = query.record().indexOf("location");
            QString loc = query.value(locIndex).toString();
            ui->label_location->setText(loc);

            ShelterOwner owner(ownerID);
            ui->label_shelter->setText(owner.getFirstName() + " " + owner.getLastName());
            ui->label_email->setText(owner.getEmail());
            ui->label_phone->setText(owner.getPhoneNumber());
        }
    }
}

void PetProfile::on_backToSearchButton_clicked()
{
    close();
}
