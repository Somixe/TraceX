#include "linkitem.h"

/**
 * @brief Constructeur de la classe LinkItem.
 *
 * Crée un lien graphique entre deux éléments (noeuds) (source et cible),
 * avec un taux de traçabilité spécifié.
 *
 * @param source Pointeur vers l'élément (noeud) source du lien.
 * @param target Pointeur vers l'élément cible du lien.
 * @param tauxTracabilite Entier représentant le taux de traçabilité associé à ce lien.
 *
 * @details Ce constructeur initialise les membres "sourceItem", "targetItem" et "tauxTracabilite",
 * puis appelle "updateLink()" pour calculer(nouvel emplacement en cas de déplacement des neouds par l'user)
 *  et afficher le lien entre les deux items.
 *  @author malek
 */
LinkItem::LinkItem(QGraphicsItem* source, QGraphicsItem* target, int tauxTracabilite)
    : QGraphicsObject(nullptr), sourceItem(source), targetItem(target), tauxTracabilite(tauxTracabilite)
{
    updateLink();
}

/**
 * @brief Met à jour la position du lien graphique entre les deux items.
 *
 * Cette méthode recalcule et met à jour la ligne reliant l'item (noeud) source à l'item (noeud) cible,
 * en prenant en compte leurs positions et tailles actuelles dans la scène.
 *
 * Le lien est dessiné depuis le bas du cercle source jusqu'au haut du cercle cible,
 *
 * - Si l’un des deux items n’est pas défini ("nullptr"), la fonction quitte immédiatement.
 * - "prepareGeometryChange()" est appelé pour informer Qt que la géométrie de l’objet va changer,
 *   évitant ainsi les artefacts visuels (les résidus du taux de tracabilité).
 * - La ligne ("line") est mise à jour avec les nouveaux points calculés.
 * - Un appel à "update()" permet de redessiner le lien avec les nouvelles coordonnées.
 * @author malek
 */
void LinkItem::updateLink() {
    if (!sourceItem || !targetItem) return;

    // Forcer Qt à recalculer la zone (évite les traces)
    prepareGeometryChange();

    QRectF sourceRect = sourceItem->boundingRect();
    QRectF targetRect = targetItem->boundingRect();

    // Rayon du cercle (on suppose que c'est un QGraphicsEllipseItem)
    qreal sourceRadius = sourceRect.width() / 2.0;
    qreal targetRadius = targetRect.width() / 2.0;

    // Calcul du bas du nœud source
    QPointF sourceBottom = sourceItem->mapToScene(sourceRect.center().x(), sourceRect.bottom());

    //  Calcul du haut du nœud destination**
    QPointF targetTop = targetItem->mapToScene(targetRect.center().x(), targetRect.top());

    // Mettre à jour la ligne
    line.setP1(sourceBottom);
    line.setP2(targetTop);

    update();  // Redessiner proprement**
}

/**
 * @brief Retourne le rectangle englobant de l'élément graphique. (tout élément graphique est englobé par un rectangle)
 *
 * lorsque l'élément change. Le rectangle retourné correspond à la
 * ligne tracée entre les deux items (source et cible)
 *
 * @return QRectF Le rectangle englobant normalisé et ajusté autour de la ligne.
 * @author malek
 */
QRectF LinkItem::boundingRect() const {
    return QRectF(line.p1(), line.p2()).normalized().adjusted(-15, -15, 15, 15);
}


/**
 * @brief Dessine le lien entre les deux items avec le taux de traçabilité.
 *
 * Elle effectue les actions suivantes :
 * - Trace une ligne noire entre l'item source et l'item cible.
 * - Calcule le milieu de la ligne pour y afficher le taux de traçabilité.
 * - Efface proprement la zone du texte pour éviter les superpositions.(résidu du taux de tracabilite)
 * - Affiche le taux de traçabilité (en pourcentage) centré sur la ligne.
 *
 * @param painter Pointeur vers le QPainter utilisé pour dessiner.
 * @param option Options de style fournies par Qt (non utilisées ici).
 * @param widget Widget parent du dessin (non utilisé ici).
 *
 * @author malek
 */
void LinkItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    // **Tracer l'arête**
    QPen pen(Qt::black);
    pen.setWidth(2);
    if (tauxTracabilite == 0) {
        pen.setStyle(Qt::DashLine);   // ← Trait pointillé
        pen.setColor(Qt::gray);       // ← Couleur plus douce
    } else {
        pen.setStyle(Qt::SolidLine);  // ← Trait plein
        pen.setColor(Qt::black);
    }

    painter->setPen(pen);
    painter->drawLine(line);

    // **Effacer proprement l'ancien texte**
    if(tauxTracabilite!=0){
    QPointF middle = (line.p1() + line.p2()) / 2;
    QRect textRect(middle.x() - 15, middle.y() - 10, 30, 20); //  Zone du texte bien définie
    painter->fillRect(textRect, Qt::white); //  Efface les anciens dessins

    // **Affichage propre du taux**

        QString tauxText = QString::number(tauxTracabilite) + "%";
        painter->setPen(Qt::black);
        painter->drawText(textRect, Qt::AlignCenter, tauxText);
    }

}

/**
 * @brief Renvoie le taux de traçabilité associé à ce lien.
 *
 * @details Ce taux est exprimé en pourcentage (entier de 0 à 100) et reflète la couverture ou la force du lien entre deux exigences.
 *
 * @return Un entier représentant le pourcentage de traçabilité du lien.
 * @author Jacques Zheng
 * @date 12/04/2025
 *
 */
int LinkItem::getTauxTracabilite() const {
    return tauxTracabilite;
}

