#ifndef QLISTWIDGET_CUSTOM_H
#define QLISTWIDGET_CUSTOM_H

#include <QListWidget>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QDrag>

class QListWidget_custom : public QListWidget
{
    Q_OBJECT
public:
    QListWidget_custom(QWidget *parent = nullptr);
    void FichierVideImage();


protected:
    void startDrag(Qt::DropActions);

};

#endif // QLISTWIDGET_CUSTOM_H
