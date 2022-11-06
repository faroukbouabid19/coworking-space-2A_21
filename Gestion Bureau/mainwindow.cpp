#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <bureaux.h>
#include <QIntValidator>
#include <QMessageBox>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->TabBureau->setModel(B.afficher());

     QPixmap pixBureau("C:/Users/MSI/OneDrive/Documents/Esprit 2/Projet/Icons/Bureau.ico");
     ui->label_pic_Bureau->setPixmap(pixBureau);
     QPixmap pixAcceuil("C:/Users/MSI/OneDrive/Documents/Esprit 2/Projet/Icons/Acceuil.ico");
     ui->label_pic_Acceuil_2->setPixmap(pixAcceuil);
     QPixmap pixPDF("C:/Users/MSI/OneDrive/Documents/Esprit 2/Projet/Icons/PDF.ico");
     ui->label_pic_PDF->setPixmap(pixPDF);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
     QString numbureau=ui->LENum->text();
     QString capacitemax=ui->ComboCapacitemax->currentText();
     QString disponibilite=ui->ComboDispo->currentText();
     QString typebureau=ui->LETypeBureau->text();

    Bureau B(numbureau,capacitemax,disponibilite,typebureau);
bool test=B.ajouter();
QMessageBox msgBox;
 if(test)
 {    ui->TabBureau->setModel(B.afficher());
     QMessageBox::information(nullptr, QObject::tr("ok"),
                                    QObject::tr("ajout effectue.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
}
 else
     QMessageBox::critical(nullptr, QObject::tr("not ok"),
                 QObject::tr("ajout non effectue.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);

}


void MainWindow::on_pb_supp_clicked()
{
    QString numbureau=ui->LENumsupp->text();
     bool test=B.supprimer(numbureau);

     if (test)
     {
         ui->TabBureau->setModel(B.afficher());
     QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("suppression effectué.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
     }
     else
     QMessageBox::critical(nullptr, QObject::tr("not OK"),
                         QObject::tr("suppression failed.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);

}



void MainWindow::on_pb_modif_clicked()
{

    QString numbureau=ui->LENum->text();
    QString capacitemax=ui->ComboCapacitemax->currentText();
    QString disponibilite=ui->ComboDispo->currentText();
    QString typebureau=ui->LETypeBureau->text();


   Bureau B(numbureau,capacitemax,disponibilite,typebureau);



    bool test=B.modifier();

        if(test){
            ui->TabBureau->setModel(B.afficher());
                    QMessageBox::information(nullptr, QObject::tr("OK"),
                                QObject::tr("modification effectué.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("not OK"),
                        QObject::tr("modification failed.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
}


void MainWindow::on_trieNum_clicked()
{
    ui->TabBureau->setModel(B.trieNum());
}

void MainWindow::on_trieType_clicked()
{
    ui->TabBureau->setModel(B.trieType());

}

void MainWindow::on_trieCapacite_clicked()
{
    ui->TabBureau->setModel(B.trieCapacite());

}


void MainWindow::on_trieDisponibilite_clicked()
{
    ui->TabBureau->setModel(B.trieDisponibilite());

}

void MainWindow::on_TabBureau_clicked(const QModelIndex &index)
{

        ui->LENum->setText(ui->TabBureau->model()->data(ui->TabBureau->model()->index(index.row(),0)).toString());
        ui->ComboCapacitemax->setCurrentText(ui->TabBureau->model()->data(ui->TabBureau->model()->index(index.row(),1)).toString());
        ui->ComboDispo->setCurrentText(ui->TabBureau->model()->data(ui->TabBureau->model()->index(index.row(),2)).toString());
        ui->LETypeBureau->setText(ui->TabBureau->model()->data(ui->TabBureau->model()->index(index.row(),3)).toString());


}





void MainWindow::on_BaRecherche_textChanged(const QString &arg1)
{

             QString rech = ui->BaRecherche->text();
                 B.recherche(ui->TabBureau,rech);
                 if (ui->BaRecherche->text().isEmpty())
                 {
                     ui->TabBureau->setModel(B.afficher());
                 }
}
