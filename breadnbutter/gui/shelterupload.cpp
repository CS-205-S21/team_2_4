#include "shelterupload.h"
#include "ui_shelterupload.h"

shelterUpload::shelterUpload(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::shelterUpload)
{
    ui->setupUi(this);
}

shelterUpload::~shelterUpload()
{
    delete ui;
}

void shelterUpload::on_pushButton_clicked()
{
    this->name = ui->nameField->text();
    this->age = ui->ageField->text().toInt();
    this->weight = ui->weightField->text().toFloat();
    this->origin = ui->originField->text();
    this->description = ui->descriptionTextEdit->toPlainText();


    /* bool check = newPet.insertIntoDB();

    if(check){
        QMessageBox::information(this, "Successful!", "Yay! You've added a new pet!");
    } */
}

void shelterUpload::on_typeBox_currentTextChanged(const QString &arg1)
{
    if(arg1 == "Dog"){
        ui->breedBox->clear();
        ui->breedBox->addItem("German Shepherd");
        ui->breedBox->addItem("Golden Retriever");
        ui->breedBox->addItem("Bulldog");
        ui->breedBox->addItem("Poodle");
        ui->breedBox->addItem("Chihuahua");
    }
    else if(arg1 == "Cat"){
        ui->breedBox->clear();
        ui->breedBox->addItem("Persian cat");
        ui->breedBox->addItem("Bengal cat");
        ui->breedBox->addItem("Siamese cat");
        ui->breedBox->addItem("Sphynx cat");
        ui->breedBox->addItem("Siberian cat");
    }
    else if(arg1 == "Snake"){
        ui->breedBox->clear();
        ui->breedBox->addItem("Cobra");
        ui->breedBox->addItem("Python");
        ui->breedBox->addItem("Copperhead");
    }
    else if(arg1 == "Hamster"){
        ui->breedBox->clear();
        ui->breedBox->addItem("Syrian hamster");
        ui->breedBox->addItem("Winter White hamster");
        ui->breedBox->addItem("Chinese hamster");
        ui->breedBox->addItem("Roborowski hamster");
        ui->breedBox->addItem("Campbell's Dwarf hamster");
    }
}

void shelterUpload::on_colorBox_activated(const QString &arg1)
{
    this->color = arg1;
}

void shelterUpload::on_hypoBox_activated(const QString &arg1)
{

}

void shelterUpload::on_hairLenBox_activated(const QString &arg1)
{
    this->hairLength = arg1;
}

void shelterUpload::on_breedBox_activated(const QString &arg1)
{
<<<<<<< HEAD
    this->name = ui->lineEdit_4->text();
    this->age = ui->lineEdit->text().toInt();
    this->weight = ui->lineEdit_2->text().toFloat();
    this->origin = ui->lineEdit_3->text();
    this->description = ui->lineEdit_5->text();

    Pet newPet(name, age, breed, color, hairLength, weight, origin, allergy, description);
    bool check = newPet.insertIntoDB();

    if(check){
        QMessageBox::information(this, "Successful!", "Yay! You've added a new pet!");
    }
=======
    this->breed = arg1;
>>>>>>> origin/main
}
