#ifndef LINKITEM_H
#define LINKITEM_H

#include <QGraphicsObject>
#include <QPen>
#include <QPainter>

class LinkItem : public QGraphicsObject
{
    Q_OBJECT  // Ajout de la macro obligatoire pour signals/slots

private:
    QGraphicsItem* sourceItem;
    QGraphicsItem* targetItem;
    float tauxTracabilite;
    QLineF line;  //  Stocker la ligne tracée

public:
    LinkItem(QGraphicsItem* source, QGraphicsItem* target, int tauxTracabilite);

    QRectF boundingRect() const override;  //  Ajout obligatoire
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    int getTauxTracabilite() const;


public slots:
    void updateLink();
};

#endif // LINKITEM_H
