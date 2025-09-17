/**
 * @file qtreewidget_custom.cpp
 * @brief Cette classe héritant de la classe "QTreeWidget" permet un rendu déposer au widget personnalisé.
 *
 * @author Maxime Huang
 * @version 1.0
 * @date Dernière modification : 29/03/2025
 */

#include "qtreewidget_custom.h"
#include <QFileInfo>

#include "style.h"
#include <QHeaderView>

/**
 * @brief  Autorise l'accès de glisser-déposer les élements du "QListWidget_custom".
 * @param parent    QWidget parent
 *
 * @author Maxime Huang
 * @date 29/03/2025
 */
QTreeWidget_custom::QTreeWidget_custom(QWidget *parent)
    : QTreeWidget(parent){
    setAcceptDrops(true);
    setDropIndicatorShown(true);
    setHeaderLabels({"File", "Type"});
    setStyleSheet(Style::Style_arbre_Fichiers());
    this->setStyleSheet(Style::Style_arbre_Fichiers());
    setHeaderLabels({"Files", "Types"});
    setColumnWidth(0, 250); // Initialise le largeur de "Fichiers"
}

/**
 * @brief Démarre l'opération de glisser d'un élément sélectionné dans le "QTreeWidget_custom".
 *
 * @details Cette méthode est appelée lorsqu'un glisser-déposer est initié. Elle récupère l'élément courant
 * et crée un objet QDrag contenant les données à déplacer.
 *
 * @param Qt::DropActions    Action de glisser possible pour l'élément.
 *
 * @author Maxime Huang
 * @date 08/03/2025
 */
void QTreeWidget_custom::startDrag(Qt::DropActions)
{
    QTreeWidgetItem *item = currentItem();

    if (item == nullptr){
        return;
    }
    else{
        QMimeData *mimeData = new QMimeData();
        mimeData->setText(item->text(0));

        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->exec(Qt::MoveAction);
    }
}

/**
 * @brief Gère l'entrée d'un élément lors d'un glisser-déposer dans le "QTreeWidget_custom".
 *
 * @details Cette méthode est appelée lorsqu'un élément entre dans la zone du QTreeWidget.
 * Si les données du glisser-déposer contiennent du texte, l'action proposée est acceptée.
 *
 * @param evenement     Evenement (QDragEnterEvent) contenant les données du glisser-déposer.
 *
 * @author Maxime Huang
 * @date 08/03/2025
 */
void QTreeWidget_custom::dragEnterEvent(QDragEnterEvent *evenement)
{
    if (evenement->mimeData()->hasText()) {
        evenement->acceptProposedAction();
    }
}

/**
 * @brief Gère le déplacement d'un élément lors d'un glisser-déposer dans le "QTreeWidget_custom".
 *
 * Cette méthode est déclenchée lorsque l'élément est déplacé dans la zone du QTreeWidget.
 * Elle accepte l'action de dépôt si les données contiennent du texte.
 *
 * @param evenement     Evenement (QDragMoveEvent) contenant les données du glisser-déposer.
 *
 * @author Maxime Huang
 * @date 08/03/2025
 */
void QTreeWidget_custom::dragMoveEvent(QDragMoveEvent *evenement)
{
    if (evenement->mimeData()->hasText()) {
        evenement->acceptProposedAction();
    }
}


/**
 * @brief Gère l'opération de dépôt lorsqu'un élément est relâché dans le "QTreeWidget_custom".
 *
 * Cette méthode vérifie les données déposées et crée dynamiquement des éléments "SSS", "SRS", ou "SDD"
 * en fonction de l'endroit où l'élément est relâché dans l'arbre.
 *
 * @param evenement     Evenement (QDropEvent) contenant les données déposées.
 *
 * @author Maxime Huang
 * @date 08/03/2025
 */
void QTreeWidget_custom::dropEvent(QDropEvent *evenement)
{
    if (!evenement->mimeData()->hasText()){
        return;
    }

    //Récupération des données
    QString path = evenement->mimeData()->text();
    QFileInfo fileInfo(path);
    QString NomFichier = fileInfo.baseName() + "." + fileInfo.suffix();

    QTreeWidgetItem *Widget_selectionner = itemAt(evenement->position().toPoint());

    if (!Widget_selectionner) {
        // Crée un "SSS" et le place dans le QTreeWidget
        QTreeWidgetItem *Nv_elem_arbre = new QTreeWidgetItem(this);
        Nv_elem_arbre->setText(0, NomFichier);
        Nv_elem_arbre->setData(0, Qt::UserRole, path);
        Nv_elem_arbre->setText(1, "SSS");
    }
    else if (Widget_selectionner->text(1) == "SSS") {
        QTreeWidgetItem *Nv_elem_arbre = new QTreeWidgetItem(Widget_selectionner);
        Nv_elem_arbre->setText(0, NomFichier);
        Nv_elem_arbre->setData(0, Qt::UserRole, path);
        Nv_elem_arbre->setText(1, "SRS");
    }
    else if (Widget_selectionner->text(1) == "SRS" && Widget_selectionner->childCount() == 0) {
        QTreeWidgetItem *Nv_elem_arbre = new QTreeWidgetItem(Widget_selectionner);
        Nv_elem_arbre->setText(0, NomFichier);
        Nv_elem_arbre->setData(0, Qt::UserRole, path);
        Nv_elem_arbre->setText(1, "SDD");
    }
    evenement->acceptProposedAction();
}

/**
 * @brief Gère la suppression d'un élément du QTreeWidget lorsque la touche "Suppr" est pressée.
 *
 * @param event      Evenement (QKeyEvent) contenant les informations sur la touche pressée.
 *
 * @author Maxime Huang
 * @date 08/03/2025
 */
void QTreeWidget_custom::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete) {  // Si la touche pressée est "Suppr"
        QTreeWidgetItem *delete_elem_tree = currentItem();
        delete(delete_elem_tree);
    }
}
