/**
 * @file qlistwidget_custom.cpp
 * @brief Cette classe héritant de la classe "QListWidget" permet un rendu de glisser déposer au widget personnalisé.
 *
 * @author Maxime Huang
 * @version 1.0
 * @date Dernière modification : 29/03/2025
 */

#include "qlistwidget_custom.h"
#include "style.h"
#include <QFileInfo>


/**
 * @brief Autorise l'accès de glisser glisser déposer les élements du "QListWidget_custom".
 *
 * @param parent    QWidget parent
 *
 * @author Maxime Huang
 * @date 29/03/2025
 */
QListWidget_custom::QListWidget_custom(QWidget *parent)
    : QListWidget(parent) {
    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);        // Affiche un indicateur visuel
    setStyleSheet(Style::Style_liste_Fichiers());

}

/**
 * @brief Démarre l'opération de glisser-déposer pour l'élément sélectionné dans le "QListWidget_custom".
 *
 * @details Cette fonction est appelée lorsque l'utilisateur commence à faire glisser un élément du QListWidget. Elle crée
 * un objet QDrag avec les données MIME correspondantes et une image de l'élément à faire glisser. L'opération de glisser-déposer
 * est ensuite exécutée avec une action de déplacement.
 *
 * @param Qt::DropActions Action de dépôt possible pour l'élément..
 *
 * @author Maxime Huang
 * @date 08/03/2025
 */
void QListWidget_custom::startDrag(Qt::DropActions)
{
    QListWidgetItem *item = currentItem();

    if (item == nullptr){
        return;
    }
    else{
        QMimeData *mimeData = new QMimeData();
        mimeData->setText(item->text());
        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);

        QWidget *itemWidget = this->itemWidget(item);
        QPixmap pixmap = itemWidget->grab();
        drag->setPixmap(pixmap);

        drag->exec(Qt::MoveAction);
    }
}

