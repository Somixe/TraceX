/**
 * @file style_exigence.cpp
 * @brief Affichage et gestion de la boîte de dialogue du fichier "style_exigence.ui"
 *
 * @details Cette classe hérité de "QDialog" permet d'afficher et de gérer les styles d'exigences des fichiers en format ".Wordx".
 *
 * @author Maxime Huang
 * @version 1.0
 * @date Dernière modification : 29/03/2025
 */

#include "style_exigence.h"
#include "ui_style_exigence.h"
#include "style.h"
#include "xmlparserutils.h"
#include <QCheckBox>
#include <QLabel>
#include <QWidget>
#include <QHBoxLayout>
#include <QListWidgetItem>
#include "sss.h"

/**
 * @brief Le constructeur initialise l'interface de styles d'exigences créés dans Qt Designer
 *
 * @param mainWindow    Pointeur vers l'objet MainWindow pour interagir avec l'interface principale.
 * @param parent        Pointeur vers le widget parent.
 * @param fichiers      Un vecteur(QVector<Sss*>) contenant les fichiers sous forme d'arborescent.
 *
 * @author Maxime Huang / Malek Allahoum
 * @date 18/03/2025
 */
style_exigence::style_exigence( QWidget *parent, QVector<Sss*> fichiers)
    : QDialog(parent)
    , ui(new Ui::style_exigence), fichiers_extraits(fichiers)
{
    ui->setupUi(this);
    ui->Styles_stacked->setCurrentIndex(0);

}

/**
 * @brief Le destructeur permet de libérer la mémoire de l'interface de styles allouée dynamiquement.
 *
 * @author Maxime Huang
 * @date 18/03/2025
 */
style_exigence::~style_exigence()
{
    delete ui;
}

/**
 * @brief Affiche la page de style des exigences SRS (bouton 2).
 * @return void
 */
void style_exigence::on_pushButton_2_clicked()
{
    ui->Styles_stacked->setCurrentIndex(PAGE_SRS);
}


/**
 * @brief Affiche la page de style des exigences SRS (bouton 3).
 * @return void
 */
void style_exigence::on_pushButton_3_clicked()
{
    ui->Styles_stacked->setCurrentIndex(PAGE_SRS);
}

/**
 * @brief Affiche la page de style des exigences SSS.
 * @return void
 */
void style_exigence::on_pushButton_4_clicked()
{
    ui->Styles_stacked->setCurrentIndex(PAGE_SSS);
}

/**
 * @brief Affiche la page de style des exigences SDD.
 * @return void
 */
void style_exigence::on_pushButton_6_clicked()
{
    ui->Styles_stacked->setCurrentIndex(PAGE_SDD);
}
