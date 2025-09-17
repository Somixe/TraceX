/**
 * @file fenetrestatistiques.cpp
 * @brief Affichage et animation de l'histogramme des taux de traçabilité.
 *
 * @details Cette classe permet d'afficher dynamiquement un histogramme
 * représentant les taux de traçabilité entre exigences SSS → SRS et SRS → SDD,
 * sous forme graphique avec axes, barres animées et fond fixe.
 *
 * @author Jacques Zheng
 * @version 1.2
 * @date Dernière modification : 21/04/2025
 */
#include "fenetrestatistiques.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QVBoxLayout>
#include <QPen>
#include <QBrush>
#include <QTimeLine>
#include <QStringList>
#include <QObject>
#include <algorithm>
/**
 * @brief Affiche un histogramme animé représentant les taux de traçabilité.
 *
 * @details Cette méthode principale orchestre l'affichage du graphique dans un widget Qt donné.
 * Elle initialise les données, prépare la scène graphique, trace les axes, ajoute
 * les barres animées et insère le graphique dans le conteneur.
 *
 * @param conteneur Le widget Qt (QWidget*) dans lequel insérer l'histogramme.
 * @param listeTaux Liste des taux de traçabilité (entre 0 et 100 %).
 *
 * @author Jacques Zheng
 * @date 22/04/2025
 */
void FenetreStatistiques::afficherHistogramme(QWidget* conteneur, const std::vector<double>& listeTaux) {
    int tranches[11] = {0};
    initialiserTranches(listeTaux, tranches);
    QStringList etiquettes = {
        "0–9%", "10–19%", "20–29%", "30–39%", "40–49%",
        "50–59%", "60–69%", "70–79%", "80–89%", "90–99%", "100%"
    };
    QGraphicsScene* scene = new QGraphicsScene();
    int largeurBarre = 40;
    int espacementBarres = 15;
    int hauteurMaximale = 250;
    int origineX = 60;
    int origineY = hauteurMaximale;
    int valeurMax = *std::max_element(tranches, tranches + 11);
    if (valeurMax == 0)
        valeurMax = 1;
    else
        valeurMax += 1;
    int hauteurParGraduation = hauteurMaximale / valeurMax;
    int largeurTotale = 11 * (largeurBarre + espacementBarres);
    dessinerAxes(scene, origineX, origineY, valeurMax, hauteurParGraduation, largeurTotale);
    ajouterTitresAxes(scene, origineX, origineY, largeurTotale);
    ajouterBarres(scene, tranches, etiquettes, origineX, origineY, largeurBarre, espacementBarres, hauteurMaximale, valeurMax);
    afficherVue(conteneur, scene, largeurTotale, hauteurMaximale);
}
/**
 * @brief Répartit les taux de traçabilité dans 11 tranches de 10 %.
 *
 * @details Cette méthode convertit chaque taux en un indice de tranche compris entre 0 et 10,
 * pour regrouper les valeurs dans des catégories de 10 %.
 *
 * @param listeTaux Vecteur des taux de traçabilité.
 * @param tranches Tableau de 11 entiers à remplir avec les comptes par tranche.
 *
 * @author Jacques Zheng
 * @date 22/04/2025
 */
void FenetreStatistiques::initialiserTranches(const std::vector<double>& listeTaux, int tranches[11]) {
    for (double taux : listeTaux) {
        int indice = static_cast<int>(taux / 10);
        if (indice >= 10) indice = 10;
        tranches[indice]++;
    }
}
/**
 * @brief Dessine les axes X et Y de l’histogramme.
 *
 * @details Trace les lignes des axes avec graduations et ajoute une flèche au bout de l’axe des abscisses.
 * L’axe des ordonnées est affiché sans flèche.
 *
 * @param scene La scène graphique dans laquelle tracer les axes.
 * @param origineX Position horizontale de l'origine des axes.
 * @param origineY Position verticale de l'origine des axes.
 * @param valeurMaximale Valeur maximale pour l’axe Y (nombre de fichiers max dans une tranche).
 * @param hauteurParGraduation Hauteur entre deux graduations de l’axe Y.
 * @param largeurTotale Largeur totale prévue de l’histogramme (barres + espacement).
 *
 * @author Jacques Zheng
 * @date 22/04/2025
 */
void FenetreStatistiques::dessinerAxes(QGraphicsScene* scene, int origineX, int origineY, int valeurMaximale, int hauteurParGraduation, int largeurTotale) {
    // Axe Y (sans flèche)
    scene->addLine(origineX, 0, origineX, origineY, QPen(Qt::black));
    for (int i = 0; i <= valeurMaximale; ++i) {
        int y = origineY - i * hauteurParGraduation;
        // Supprimer le petit trait gauche pour la graduation 0
        if (i != 0) {
            scene->addLine(origineX - 5, y, origineX, y, QPen(Qt::black));
        }
        QGraphicsTextItem* etiquetteY = scene->addText(QString::number(i));
        etiquetteY->setPos(origineX - 25, y - 8);
    }
    // Axe X (avec flèche)
    scene->addLine(origineX, origineY, origineX + largeurTotale + 20, origineY, QPen(Qt::black));
    scene->addLine(origineX + largeurTotale + 10, origineY - 5, origineX + largeurTotale + 20, origineY, QPen(Qt::black));
    scene->addLine(origineX + largeurTotale + 10, origineY + 5, origineX + largeurTotale + 20, origineY, QPen(Qt::black));
}
/**
 * @brief Ajoute les titres des axes X et Y à la scène.
 *
 * Le texte est positionné dynamiquement selon la taille de la scène et orienté verticalement pour Y.
 *
 * @param scene Scène graphique dans laquelle ajouter les titres.
 * @param origineX Position de départ en X des axes.
 * @param origineY Position de départ en Y des axes.
 * @param largeurTotale Largeur totale occupée par les barres.
 *
 * @author Jacques Zheng
 * @date 22/04/2025
 */
void FenetreStatistiques::ajouterTitresAxes(QGraphicsScene* scene, int origineX, int origineY, int largeurTotale) {
    QGraphicsTextItem* titreY = scene->addText("Liens de traçabilité SSS → SRS et SRS → SDD");
    titreY->setDefaultTextColor(Qt::black);
    titreY->setRotation(-90);
    titreY->setPos(origineX - 50, origineY - 5);
    QGraphicsTextItem* titreX = scene->addText("% de taux traçabilité");
    titreX->setPos(origineX + largeurTotale / 2 - 60, origineY + 25);
    titreX->setDefaultTextColor(Qt::black);
}
/**
 * @brief Ajoute les barres de l’histogramme ainsi que leur animation.
 *
 * @details Chaque barre est animée depuis une hauteur de 0 jusqu’à sa hauteur cible,
 * proportionnelle au nombre d’éléments dans la tranche.
 *
 * @param scene Scène graphique sur laquelle ajouter les barres.
 * @param tranches Tableau contenant les comptages par tranche.
 * @param etiquettesTranches Libellés pour les tranches (0-9 %, 10-19 %, etc.).
 * @param origineX Position X de départ.
 * @param origineY Position Y de base (axe horizontal).
 * @param largeurBarre Largeur de chaque barre.
 * @param espacementBarres Espacement entre les barres.
 * @param hauteurMaximaleBarre Hauteur maximale que peut atteindre une barre.
 * @param valeurMaximale Valeur maximale utilisée pour normaliser les hauteurs.
 * @author Jacques Zheng
 * @date 22/04/2025
 */
void FenetreStatistiques::ajouterBarres(QGraphicsScene* scene, const int tranches[11], const QStringList& etiquettesTranches, int origineX, int origineY, int largeurBarre, int espacementBarres, int hauteurMaximaleBarre, int valeurMaximale) {
    int positionX = origineX + 10;
    for (int i = 0; i < 11; ++i) {
        int hauteur = (tranches[i] * hauteurMaximaleBarre) / valeurMaximale;
        if (tranches[i] > 0) {
            QGraphicsRectItem* barre = scene->addRect(positionX, origineY, largeurBarre, 0,
                                                      QPen(Qt::black), QBrush(QColor(66, 133, 244)));
            QTimeLine* timeline = new QTimeLine(600);
            timeline->setFrameRange(0, hauteur);
            QObject::connect(timeline, &QTimeLine::frameChanged, [=](int val) {
                barre->setRect(positionX, origineY - val, largeurBarre, val);
            });
            timeline->start();
            QGraphicsTextItem* valeur = scene->addText(QString::number(tranches[i]));
            valeur->setPos(positionX + largeurBarre / 4, origineY - hauteur - 20);
            valeur->setDefaultTextColor(Qt::black);
        }
        QGraphicsTextItem* etiquetteX = scene->addText(etiquettesTranches[i]);
        etiquetteX->setPos(positionX, origineY + 5);
        positionX += largeurBarre + espacementBarres;
       etiquetteX ->setDefaultTextColor(Qt::black);
    }
}
/**
 * @brief Crée et insère la vue graphique dans le widget cible.
 *
 * @details Nettoie le layout existant dans le widget conteneur (si présent), puis y insère
 * une QGraphicsView configurée avec la scène et les paramètres visuels.
 *
 * @param conteneur Le widget parent dans lequel insérer l'histogramme.
 * @param scene La scène graphique complète contenant l'histogramme.
 * @param largeurTotale Largeur totale de la scène.
 * @param hauteurMaximaleBarre Hauteur maximale de la scène.
 *
 * @author Jacques Zheng
 * @date 22/04/2025
 */
void FenetreStatistiques::afficherVue(QWidget* conteneur, QGraphicsScene* scene, int largeurTotale, int hauteurMaximaleBarre) {
    scene->setSceneRect(0, 0, largeurTotale + 80, hauteurMaximaleBarre + 40);
    QGraphicsView* vue = new QGraphicsView(scene);
    vue->setMinimumHeight(400);
    vue->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    vue->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vue->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vue->setBackgroundBrush(Qt::white);
    if (conteneur->layout()) {
        QLayoutItem* item;
        while ((item = conteneur->layout()->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete conteneur->layout();
    }
    QVBoxLayout* layout = new QVBoxLayout(conteneur);
    layout->addWidget(vue);
    conteneur->setLayout(layout);
}
