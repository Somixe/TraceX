
/*#include "evenement.h"
#include <QFileInfo>
#include <QDebug>
#include "mainwindow.h"


QListWidget_custom::QListWidget_custom(QWidget *parent)
    : QListWidget(parent) {
    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);        // Affiche un indicateur visuel
}

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


QTreeWidget_custom::QTreeWidget_custom(QWidget *parent)
    : QTreeWidget(parent){
    setAcceptDrops(true);
    setDropIndicatorShown(true);
}

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


void QTreeWidget_custom::dragEnterEvent(QDragEnterEvent *evenement)
{
    if (evenement->mimeData()->hasText()) {
        evenement->acceptProposedAction();
    }
}

void QTreeWidget_custom::dragMoveEvent(QDragMoveEvent *evenement)
{
    if (evenement->mimeData()->hasText()) {
        evenement->acceptProposedAction();
    }
}

void QTreeWidget_custom::dropEvent(QDropEvent *evenement)
{
    if (!evenement->mimeData()->hasText()){
        return;
    }

    QString path = evenement->mimeData()->text();

    QFileInfo fileInfo(path);
    QString NomFichier = fileInfo.baseName() + "." + fileInfo.suffix();


    //Renvoie un pointeur d'un point contenant les coordonées de l'elem selectionne
    QTreeWidgetItem *Widget_selectionner = itemAt(evenement->position().toPoint());

    if (!Widget_selectionner) {
        //Crée un "SSS" et le place dans le QTreeWidget
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

void QTreeWidget_custom::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete) {  // Si la touche pressée est "Suppr"
        QTreeWidgetItem *delete_elem_tree = currentItem();
        delete(delete_elem_tree);
    }
}*/
