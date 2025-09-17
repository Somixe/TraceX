#include "nodeitem.h"
#include "exigence.h"
#include "sss.h"
#include "srs.h"
#include "sdd.h"





/**
 * @brief Constructeur de la classe NodeItem.
 *
 * Initialise un nœud graphique représentant un fichier donné, avec son type
 * (par exemple SSS, SRS, ou SDD). Le nœud est rendu interactif (déplaçable, sélectionnable)
 * et peut clignoter en rouge en fonction de son état.
 *
 * @param file Pointeur vers l'objet File associé au nœud.
 * @param type Le type de fichier (défini par l'énumération TypeFile).
 *
 * Ce constructeur :
 * - Initialise le label avec le nom du fichier.
 * - Configure les flags d'interaction graphique.
 * - Prépare un QTimer pour gérer le clignotement.
 * - Associe une infobulle contenant le nom du fichier.
 *
 * @author malek
 */
NodeItem::NodeItem(File* file, TypeFile type) {
    label = file->getNom();
    this->file = file;
    this->type = type;
    this->isBlinking = false;
    this->isRed = false;  // Le nœud commence avec une couleur normale
    // Créer le timer pour le clignotement
    blinkTimer = new QTimer(this);
    connect(blinkTimer, &QTimer::timeout, this, &NodeItem::updateBlinkingState);
    setToolTip(label);
    setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsScenePositionChanges);  // Activer le déplacement
    setAcceptHoverEvents(true);  // Active les événements au survol

}

/**
 * @brief Gère l'entrée du curseur dans la zone du noeud (PointingHandCursor).
 *
 * @param event L'événement de survol déclenché par Qt.
 *
 * @author Maxime Huang
 *
 * @date 12/04/25
 */
void NodeItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
    setCursor(Qt::PointingHandCursor);  // Curseur en forme de main
}

/**
 * @brief Gère la sortie du curseur en dehors de la zone du nœud. Elle réinitialise le curseur à son état par défaut (Arrow)
 *
 * @param event L'événement de survol déclenché par Qt.
 *
 * @author Maxime Huang
 *
 * @date 12/04/25
 */
void NodeItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
    unsetCursor();  // Réinitialiser le curseur par défaut
}


/**
 * @brief Gère le déplacement du nœud avec la souris.
 *
 * Cette méthode est appelée automatiquement lorsqu'un utilisateur déplace
 * le nœud à la souris. Elle émet un signal "positionChanged()" pour notifier
 * d'autres objets (les aretes) et force la mise à jour des nœuds connectés
 * (parents et fils) afin de redessiner correctement les liens (aretes).
 *
 * @param event Événement de souris déclenché par le déplacement.
 * @author malek
 */
void NodeItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsItem::mouseMoveEvent(event);
    emit positionChanged();  // Émettre un signal lorsque le nœud est déplacé

    // Mettre à jour la position des arêtes connectées (si applicable)
    for (NodeItem* parent : parentNodes) {
        update();  // Redessiner le nœud parent
    }
    for (NodeItem* fils : filsNodes) {
        update();  // Redessiner les fils
    }
}


/**
 * @brief Réagit aux changements d'état de l'élément graphique.
 *
 * Cette méthode est appelée par Qt à chaque changement de propriété important
 * (comme la position, la sélection, etc.). Ici, on intercepte le changement
 * de position ("ItemPositionChange") pour :
 * - émettre le signal "positionChanged()" (utile pour mettre à jour les liens),
 * - redessiner les nœuds parents et fils afin que leurs arêtes soient bien ajustées.
 *
 * @param change Type de changement détecté.
 * @param value Nouvelle valeur associée au changement.
 * @return QVariant La valeur à appliquer (identique à celle reçue ici).
 *
 * @author malek
 */
QVariant NodeItem::itemChange(GraphicsItemChange change, const QVariant& value) {
    if (change == ItemPositionChange) {
        emit positionChanged();  // Émettre le signal de changement de position
        for (NodeItem* fils : filsNodes) {
            fils->update();
        }
        for (NodeItem* parent : parentNodes) {
            parent->update();
        }
    }
    return QGraphicsItem::itemChange(change, value);
}
/**
 * @brief Met à jour l'état de clignotement du nœud.
 *
 * Cette méthode est appelée périodiquement par un "QTimer" pour créer un effet
 * de clignotement visuel. Elle inverse la couleur du nœud entre rouge et sa
 * couleur d'origine (en fonction de son type) puis demande un redessin en appelant "update()".
 *
 * Utiliser pour signaler les documents SSS sans fils
 *
 * @author malek
 */
void NodeItem::updateBlinkingState() {

    isRed = !isRed;  // Inverser l'état (rouge ou pas)

    update();
}

/**
 * @brief Active le clignotement du nœud.
 *
 * Si le nœud ne clignote pas encore, cette méthode :
 * - active l'état de clignotement ("isBlinking"),
 * - force la couleur initiale à rouge ("isRed = true"),
 * - démarre un "QTimer" avec un intervalle de 500 ms pour alterner la couleur.
 *
 *@author malek
 */
void NodeItem::makeBlinking() {
    if (!isBlinking) {
        isBlinking = true;
        isRed = true;  // Commencer le clignotement en rouge
        blinkTimer->start(500);  // Intervalle de 500 ms pour alterner la couleur
    }
}

/**
 * @brief Retourne la zone occupée par le nœud dans la scène.
 *
 * Cette méthode définit une zone fixe autour du centre de l'élément,
 * ici un petit rectangle de 20x20 pixels positionné à (-50, -30) par rapport au centre.
 *
 * @return QRectF La zone rectangulaire de l'élément.
 * @author malek
 */
QRectF NodeItem::boundingRect() const {
    return QRectF(-50, -30, 20, 20);  // Dimension du nœud
}

/**
 * @brief Dessine le nœud graphique sur la scène.
 *
 * Cette méthode est responsable du dessin du nœud sur la scène. Elle définit d'abord la couleur du
 * nœud en fonction de son état de clignotement et de son type de fichier. Ensuite, elle dessine un cercle
 * représentant le nœud à la position et la taille spécifiées par "boundingRect()".
 *
 * - Si le nœud clignote, il est dessiné en rouge.
 * - Si le nœud ne clignote pas, il est dessiné dans une couleur spécifique en fonction de son type :
 *   - "TypeFile::sss" : bleu
 *   - "TypeFile::srs" : vert
 *   - "TypeFile::sdd" : jaune
 *
 * @param painter L'objet utilisé pour dessiner sur la scène.
 * @param option Les options de style pour dessiner l'élément.
 * @param widget Le widget qui contient cet élément graphique (si applicable).
 * @author malek
 */
void NodeItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    QPen pen;
    pen.setColor(Qt::black);
    painter->setPen(pen);
    // Définir la couleur du nœud : rouge si clignotant, sinon selon le type de fichier
    QColor nodeColor;
    if (isBlinking && isRed) {
        nodeColor = Qt::red;  // Si clignotant, rouge
    } else {
        // Sinon, selon le type de fichier
        switch (type) {
        case TypeFile::sss:
            nodeColor = Qt::blue;
            break;
        case TypeFile::srs:
            nodeColor = Qt::green;
            break;
        case TypeFile::sdd:
            nodeColor = Qt::yellow;
            break;
        default:
            nodeColor = Qt::lightGray;  // Couleur par défaut
            break;
        }
    }
    painter->setBrush(QBrush(nodeColor));  // Appliquer la couleur
    // Dessiner le nœud (cercle)
    painter->drawEllipse(boundingRect());
}

/**
 * @brief Retourne le pointeur vers le fichier associé au nœud.
 * @return File* Le pointeur vers l'objet "File" associé au nœud.
 * @author malek
 */
File* NodeItem::getFile() {
    if (!file) {
        qWarning() << "[NodeItem] getFile() retourne nullptr !";
    }
    return file;
}




/**
 * @brief Retourne le type de fichier associé au nœud.
 * @return TypeFile Le type de fichier associé au nœud.
 * @author malek
 */
TypeFile NodeItem::getType() {
    return type;
}

/**
 * @brief Retourne la liste des nœuds parents associés à ce nœud.
 * @return QList<NodeItem*> La liste des nœuds parents associés à ce nœud.
 * @author malek
 */
QList<NodeItem*> NodeItem::getParents() const {
    return parentNodes;
}


/**
 * @brief Ajoute un nœud parent à ce nœud.
 * @param parent Le nœud à ajouter comme parent.
 * @author malek
 */
void NodeItem::addParent(NodeItem* parent) {
    parentNodes.append(parent);
}


/**
 * @brief Retourne la liste des nœuds fils associés à ce nœud.
 * @return QList<NodeItem*> La liste des nœuds fils associés à ce nœud.
 * @author malek
 */
QList<NodeItem*> NodeItem::getFils() const {
    return filsNodes;
}

/**
 * @brief Ajoute un nœud fils à ce nœud.
 * @param fils Le nœud à ajouter comme fils.
 * @author malek
 */
void NodeItem::addFils(NodeItem* fils) {
    filsNodes.append(fils);
}
/**
 * @brief Vérifie si ce nœud a des nœuds fils.
 * @return true Si ce nœud a des nœuds fils, false sinon
 * @author malek
 */
bool NodeItem::hasFils() const {
    return (!filsNodes.isEmpty());
}

/**
 * @brief Gère le clic souris sur le nœud graphique.
 *
 * Cette méthode est appelée automatiquement lorsqu’un utilisateur clique
 * sur un objet "NodeItem" dans la scène graphique. Elle émet un signal
 * "nodeClicked(this)" pour permettre à l’interface (MainWindow)
 * d’afficher les exigences associées au nœud.
 *
 * @param event L’événement de clic détecté par Qt.
 *
 * @author Jacques Zheng
 * @date 02/05/2025
 */


void NodeItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsObject::mousePressEvent(event);  // Important : QGraphicsObject
    emit nodeClicked(this);  //  Une seule fois
}

/**
 * @brief Retourne les exigences associées au fichier de ce nœud sous forme de texte.
 *
 * Cette méthode effectue un "dynamic_cast" du fichier ("File*") vers son type réel
 * ("Sss", "Srs", ou "Sdd") afin d’accéder à la méthode "getExigence()" de la classe dérivée.
 * Chaque exigence est convertie en "QString" à partir de son "toString()".
 * Si le fichier est nul, ou que le type est inconnu, des messages par défaut sont renvoyés.
 *
 * @return Une "QStringList" contenant les descriptions des exigences.
 *
 * @author Jacques Zheng
 * @date 02/05/2025
 */

QStringList NodeItem::getExigences() const {
    if (!file) return {"Erreur : fichier null"};

    QStringList liste;

    if (Sss* sss = dynamic_cast<Sss*>(file)) {
        for (const Exigence& ex : sss->getExigence()) {
            liste << QString::fromStdString(ex.toString());
        }
    } else if (Srs* srs = dynamic_cast<Srs*>(file)) {
        for (const Exigence& ex : srs->getExigence()) {
            liste << QString::fromStdString(ex.toString());
        }
    } else if (Sdd* sdd = dynamic_cast<Sdd*>(file)) {
        for (const Exigence& ex : sdd->getExigence()) {
            liste << QString::fromStdString(ex.toString());
        }
    } else {
        liste << "Type de fichier inconnu.";
    }

    return liste.isEmpty() ? QStringList{"Aucune exigence trouvée"} : liste;
}
