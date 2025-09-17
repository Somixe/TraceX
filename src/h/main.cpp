/**
 * @file main.cpp
 * @brief Point d'entrée de l'application.
 *
 * @details Ce fichier contient la fonction main(), qui initialise l'application Qt
 * et affiche la fenêtre principale définie dans la classe MainWindow.
 *
 * @version 1.0
 * @date Dernière modification : 20/02/2025
 */

#include "mainwindow.h"

#include <QApplication>


/**
 * @brief Fonction principale de l'application.
 *
 * @param argc       Nombre d'arguments passés en ligne de commande.
 * @param argv       Tableau contenant les arguments en ligne de commande.
 *
 * @return int      Code de retour du programme.
 *
 * @date
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();


}
