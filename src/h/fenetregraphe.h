#ifndef FENETREGRAPHE_H
#define FENETREGRAPHE_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QDebug>


class FenetreGraphe : public QGraphicsView
{
public:
     FenetreGraphe(QWidget* parent = nullptr);

public slots:
    void zoomAvant();
    void zoomArriere();


protected:
    void wheelEvent(QWheelEvent *event);  // Pour capter les événements de la molette

private:
    void Zoom_dezoom(QWheelEvent *event);  // Méthode de zoom/dézoom
    int limiteZoom = 0;
    const int MAX_ZOOM = 4;
    const int MIN_ZOOM = -4;
};

#endif // FENETREGRAPHE_H
