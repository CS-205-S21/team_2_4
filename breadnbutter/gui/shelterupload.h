#ifndef SHELTERUPLOAD_H
#define SHELTERUPLOAD_H

#include <QMainWindow>
#include <QMessageBox>
#include "../backend/pet.h"

namespace Ui {
class shelterUpload;
}

class shelterUpload : public QMainWindow
{
    Q_OBJECT

public:
    explicit shelterUpload(QWidget *parent = 0);
    ~shelterUpload();

private slots:
    void on_pushButton_clicked();

    void on_typeBox_currentTextChanged(const QString &arg1);

    void on_colorBox_activated(const QString &arg1);

    void on_hypoBox_activated(const QString &arg1);

    void on_hairLenBox_activated(const QString &arg1);

    void on_breedBox_activated(const QString &arg1);

private:
    Ui::shelterUpload *ui;
    QString type;
    QString breed;
    float weight;
    int age;
    QString hairLength;
    QString color;
    bool hypoallergenic;
    QString origin;
    QString description;
    QString name;

    bool upload;
};

#endif // SHELTERUPLOAD_H
