#ifndef NODEITEM_H
#define NODEITEM_H

#include "file.h"
#include <QGraphicsObject>
#include <QPen>
#include <QPainter>
#include "TypeFile.h"
#include <QTimer>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QCursor>

class NodeItem : public QGraphicsObject{
    Q_OBJECT
private:
    File* file;
    QString label;
    TypeFile type;
    QList<NodeItem*> parentNodes;    // Liste des parents
    QList<NodeItem*> filsNodes;      // Liste des fils
    bool isRed;
    bool isBlinking;
    QTimer* blinkTimer;

public:

    void addParent(NodeItem* parent);


    QList<NodeItem*> getFils() const;


    void addFils(NodeItem* fils);


    bool hasFils() const;


    QList<NodeItem*> getParents() const;

    NodeItem(File* file, TypeFile type);


    TypeFile getType();

    QRectF boundingRect() const override;


    void makeBlinking();

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;


    void updateBlinkingState();


    File* getFile();



    QStringList getExigences() const;

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;


signals:
    void positionChanged();
    void nodeClicked(NodeItem* self);
};

#endif // NODEITEM_H
