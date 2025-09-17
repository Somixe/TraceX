#ifndef GRAPHE_H
#define GRAPHE_H
#include "sss.h"
#include <QVector>
#include <QGraphicsScene>
#include "nodeitem.h"
#include "linkitem.h"




class Graphe :public QGraphicsScene
{
private:
    QVector<Sss*> fichiers;
    QVector<NodeItem*> nodes;
    QVector<LinkItem*> links;

public:
    Graphe(QVector<Sss*> fichiers);

    bool existNode(NodeItem* node);


    void ajouterNode();


    void organiserLignes();


    LinkItem* ajouterLien(NodeItem* parent, NodeItem* fils, float tauxTracabilite);

    void connectNodeAndLink(NodeItem* node, LinkItem* link);

    void afficherGraphe(QGraphicsScene* scene,const QStringList& criteres);
    QVector<Sss*> getFichiers();

};

#endif // GRAPHE_H
