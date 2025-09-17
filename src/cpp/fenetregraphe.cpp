/**
 * @file fenetregraphe.cpp
 * @brief Gestion de la fenêtre de visualisation du graphe.
 *
 * @details Cette classe héritant de la classe "QGraphicsView" permet d'afficher et de manipuler un graphe
 * avec diverses fonctionnalités.
 *
 * @author Maxime Huang
 * @version 1.0
 * @date Dernière modification : 29/03/2025
 */

#include "fenetregraphe.h"


/**
 * @brief Constructeur de la classe "FenetreGraphe.cpp".
 *
 * @param parent    Pointeur vers le widget parent.
 *
 *@author Maxime Huang
 *@date 23/03/2025
 */
FenetreGraphe::FenetreGraphe(QWidget* parent)
    : QGraphicsView(parent)

{
    setDragMode(QGraphicsView::ScrollHandDrag);
}

/**
 * @brief Gestion du zoom avec le boutont '+'.
 *
 *@author Jacques Zheng
 *@date
 */
void FenetreGraphe::zoomAvant() {
    if (limiteZoom < MAX_ZOOM) {
        this->scale(1.2, 1.2);
        limiteZoom++;

    }
}

/**
 * @brief Gestion du dézoom avec le boutont '-'.
 *
 *@author Jacques Zheng
 *@date
 */
void FenetreGraphe::zoomArriere() {
    if (limiteZoom > MIN_ZOOM) {
        this->scale(1.0 / 1.2, 1.0 / 1.2);
        limiteZoom--;
    }
}

/**
 * @brief Gestion du zoom et dézoom avec la molette de la souris.
 * @param event     Pointeur vers l'événement de molette (QWheelEvent).
 *
 *@author Maxime Huang
 *@date 26/03/2025
 */
void FenetreGraphe::Zoom_dezoom(QWheelEvent *event)
{
    double facteurZoom = 1.2;  // Facteur constant de zoom
    double facteurDezoom = 1.0 / facteurZoom;

    if (event->angleDelta().y() > 0) {
        if (limiteZoom < MAX_ZOOM) {  // Limite maximale du zoom
            this->scale(facteurZoom, facteurZoom);
            limiteZoom++;
        }
    } else {
        if (limiteZoom > MIN_ZOOM) {
            this->scale(facteurDezoom, facteurDezoom);
            limiteZoom--;
        }
    }
}

/**
 * @brief Gère l'événement lorsque l'utilisateur utilise la molette de la souris.
 * @param event     Pointeur vers l'événement de molette de type (QWheelEvent).
 *
 * Cette méthode redirige l'événement de molette vers la méthode "Zoom_dezoom()", qui se charge
 * d'agrandir ou de rétrécir l'affichage en fonction de l'orientation de la molette.
 *
 * @author Maxime Huang
 * @date 28/03/2025
 */
void FenetreGraphe::wheelEvent(QWheelEvent *event)
{
    Zoom_dezoom(event);
}


