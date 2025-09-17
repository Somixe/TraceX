#include "fenetreexigences.h"
#include "mainwindow.h"
#include <QVBoxLayout>

/**
 * @brief Constructeur de la fenêtre d'exigences intégrée dans MainWindow
 * @param mw Pointeur vers la fenêtre principale
 * @param parent Widget parent (optionnel)
 */
FenetreExigences::FenetreExigences(MainWindow *mw, QWidget *parent)
    : QWidget(parent), mainwindow(mw)
{
    // Création du contenu interne
    listeExigences = new QListWidget(this);
    listeExigences->setMaximumHeight(175); // Limite de hauteur

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(listeExigences);

    mainwindow->getConteneurExigenceLayout()->addWidget(listeExigences);
}


/**
 * @brief Met à jour la liste des exigences affichées.
 *
 * Cette méthode efface les éléments actuels de la liste et y insère ceux
 * passés en paramètre. Elle est appelée lorsqu’un nœud est cliqué dans le graphe.
 *
 * @param exigences Une "QStringList" contenant les exigences à afficher.
 *
 * @author Jacques Zheng
 * @date 02/05/2025
 */


void FenetreExigences::setExigences(const QStringList &exigences)
{
    listeExigences->clear();
    listeExigences->addItems(exigences);
}


