#ifndef QTREEWIDGET_CUSTOM_H
#define QTREEWIDGET_CUSTOM_H

#include <QTreeWidget>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QDrag>
#include <QKeyEvent>

class QTreeWidget_custom : public QTreeWidget
{
    Q_OBJECT
public:
    QTreeWidget_custom(QWidget *parent = nullptr);

protected:
    void startDrag(Qt::DropActions);
    void dragEnterEvent(QDragEnterEvent *evenement);
    void dragMoveEvent(QDragMoveEvent *evenement);
    void dropEvent(QDropEvent *evenement);
    void keyPressEvent(QKeyEvent *event);
};

#endif // QTREEWIDGET_CUSTOM_H
