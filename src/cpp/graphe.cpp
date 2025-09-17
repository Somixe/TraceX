#include "graphe.h"
#include "xmlparserutils.h"
#include "exigencesrs.h"
#include "tracabilite.h"
#include <QDialog>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QVector>


/**
 * @brief Graphe::Graphe constructeur qui contruit un objet de type graphe
 * @param fichiers : la listes des fichiers importés par l'utilisateur
 * @author malek
 */
Graphe::Graphe(QVector<Sss*> fichiers) {
    this->fichiers=fichiers;
}

/**
 * @brief Graphe::existNode vérifie si un noeud existe dans le graphe
 * @param noeud : un noeud
 * @return vrai si le noeud existe, faux sinon
 * @author malek
 */
bool Graphe::existNode(NodeItem* noeud){
    bool trouve = false;
    for(int i=0; i<nodes.size() && !trouve; i++){
        if(nodes[i]->getFile()->getPath()==noeud->getFile()->getPath()){
            trouve = true;
        }
    }
    return trouve;
}



/**
 * @brief Ajoute des nœuds au graphe à partir de la hiérarchie de fichiers.
 *
 * Cette méthode parcourt une liste de fichiers racines de type "Sss" et crée pour chacun
 * un nœud "NodeItem" associé. Ensuite, elle parcourt leurs enfants de type "Srs", crée les
 * nœuds correspondants, et établit les relations parent-enfant dans le graphe.
 * Si un "Srs" possède un fichier enfant ("Sdd"), un nœud est aussi créé pour celui-ci
 * et ajouté au graphe avec les connexions adéquates.
 * @author malek / Jacques
 */


void Graphe::ajouterNode() {
    const QVector<Sss*>& pere = fichiers;
    for(Sss* fichier : pere){
        NodeItem* node1 = new NodeItem(fichier, TypeFile::sss);

        addItem(node1);
        nodes.append(node1);

        const QVector<Srs*>& fils = fichier->getFils();
        for(Srs* srs : fils){
            NodeItem* node2 = new NodeItem(srs, TypeFile::srs);

            node2->addParent(node1);
            node1->addFils(node2);
            addItem(node2);
            nodes.append(node2);

            if (srs->hasFils()) {
                File* sdd = srs->getFils();
                NodeItem* node3 = new NodeItem(sdd, TypeFile::sdd);

                node3->addParent(node2);
                node2->addFils(node3);
                addItem(node3);
                nodes.append(node3);
            }
        }
    }
}
/**
 * @brief Organise les nœuds du graphe en lignes selon leur type.
 *
 * Cette méthode dispose graphiquement les nœuds (`NodeItem`) selon trois niveaux :
 * - Ligne supérieure : les fichiers de type `SSS`
 * - Ligne centrale : les fichiers de type `SRS`
 * - Ligne inférieure : les fichiers de type `SDD` (si présents)
 *
 * Le positionnement horizontal est géré par un espacement constant (`xSpacing`)
 * à partir d'une position de départ (`xStart`).
 *
 * Fonctionnement :
 * - Les nœuds `SSS` avec enfants sont d'abord placés en haut (`sssY`) et associés
 *   à leurs `SRS`.
 * - Les `SRS` sont ensuite placés au niveau intermédiaire (`srsY`), et leurs enfants
 *   `SDD`, s'ils existent, sont placés juste en dessous (`sddY`).
 * - Une fois tous les `SRS` positionnés, les `SSS` sont recentrés horizontalement
 *   au-dessus de leurs enfants pour assurer un alignement visuel clair.
 * - Enfin, les `SSS` sans enfants sont placés plus bas, à droite, et rendus clignotants
 *   pour les différencier (`makeBlinking()`).
 *
 * @author malek / Maxime
 */
void Graphe::organiserLignes() {
    int sssY = -100;
    int srsY = 00;
    int sddY = 100;
    int xSpacing = 80;
    int xStart = 50;
    const QVector<NodeItem*>& n = nodes;
    QSet<NodeItem*> placedNodes;  // Utilisation d'un QSet pour suivre les nœuds déjà placés
    QVector<QPair<NodeItem*, QVector<NodeItem*>>> sssSrsPairs;  // Pour stocker les relations entre SSS et SRS
    // Placer les SSS
    int sssX = xStart;
    for (NodeItem* node : n) {
        if (node->getType() == TypeFile::sss && !placedNodes.contains(node)) {
            if(node->hasFils()){
                placedNodes.insert(node);   // Marquer le nœud comme placé
                node->setPos(sssX, sssY);   // Placer le SSS
                sssX += xSpacing;            // Avancer pour le placement des SSS
                // Récupérer les fils (SRS) de ce SSS et les associer à ce SSS
                QVector<NodeItem*> srsFils;
                for (NodeItem* srsNode : n) {
                    if (srsNode->getType() == TypeFile::srs) {
                        if (srsNode->getParents().contains(node)){ // Vérifier si ce SRS est enfant de ce SSS
                            srsFils.append(srsNode);

                        }
                    }
                }
                sssSrsPairs.append(qMakePair(node, srsFils));            // Associer ce SSS avec ses SRS
            }
        }
    }
    // Placer les SRS sous les SSS, sans déplacer ceux déjà placés
    int srsX = xStart;
    for (NodeItem* node : n) {
        if (node->getType() == TypeFile::srs && !placedNodes.contains(node)) {
            node->setPos(srsX, srsY);   // Placer le nœud SRS
            placedNodes.insert(node);            // Marquer le nœud comme placé
            if(node->hasFils()){
                const QList<NodeItem*>& fils = node->getFils();
                NodeItem* nodeSdd = fils.first();
                nodeSdd->setPos(srsX, sddY);
                placedNodes.insert(nodeSdd);
            }
            srsX += xSpacing;
        }
    }
    // Placer les SSS au centre de leurs SRS, juste au-dessus
    for (const auto& pair : sssSrsPairs) {
        NodeItem* sssNode = pair.first;
        const QVector<NodeItem*>& srsFils = pair.second;
        // Calculer la position X moyenne des SRS associés
        int totalX = 0;
        for (NodeItem* srsNode : srsFils) {
            totalX += srsNode->pos().x();
        }
        if (!srsFils.isEmpty()) {
            int sssCenterX = totalX / srsFils.size();  // Calculer le centre horizontal des SRS
            sssNode->setPos(sssCenterX - sssNode->boundingRect().width() / 2, sssY);  // Centrer le SSS
            placedNodes.insert(sssNode);  // Marquer le nœud comme placé
        }
    }

    // Placer les SSS sans enfants à droite
    int sssSansFilsX = xStart;  // Placer à droite
    for (NodeItem* node : n) {
        if (node->getType() == TypeFile::sss) {
            if (!node->hasFils() && !placedNodes.contains(node)) {
                node->setPos(sssSansFilsX, sddY+50);
                node->makeBlinking();
                placedNodes.insert(node);  // Marquer le nœud comme placé
                sssSansFilsX += xSpacing;
            }
        }
    }
}
/**
 * @brief Graphe::ajouterLien : permet de créer un lien entre 2 noeuds
 * @param parent : le noeud source
 * @param fils : le noeud de destination
 * @param tauxTracabilite : le taux de tracabilite entre les 2 fichiers que représentent les noeuds
 * @return un lien
 * @author malek
 */
LinkItem* Graphe::ajouterLien(NodeItem* parent, NodeItem* fils, float tauxTracabilite) {
    LinkItem* link = new LinkItem(parent, fils, tauxTracabilite);
    links.append(link);
    connectNodeAndLink(parent, link);  // Connecter le nœud parent à l'arête
    connectNodeAndLink(fils, link);    // Connecter le nœud fils à l'arête
    return link;
}

/**
 * @brief Graphe::connectNodeAndLink : connecter un noeud à un lien pour synchroniser les coordonnées des noeuds avec celles du lien pour dynamiser le graphe
 * @param node : le node à connecter
 * @param link : le lien du noeud
 * @author malek
 */
void Graphe::connectNodeAndLink(NodeItem* node, LinkItem* link) {

    connect(node, &NodeItem::positionChanged, link, &LinkItem::updateLink);
}

/**
 * @brief Graphe::afficherGraphe : permet l'affichage du noeud dans la scene
 * @param scene : la scene sur laquelle le graphe sera afficher
 * @author malek / Jacques / Maxime
 */


void Graphe::afficherGraphe(QGraphicsScene* scene , const QStringList& criteres) {
    scene->setBackgroundBrush(Qt::white);

    this->ajouterNode();
    this->organiserLignes();

    int i = 0;
    int nbSss = -1;

    while (i < nodes.size()) {
        nbSss++;
        NodeItem* nodeSss = nodes[i];
        File* sssFile = nodeSss->getFile();
        Sss* sssPtr = dynamic_cast<Sss*>(sssFile);

        if (!sssPtr) {
            qWarning() << "[afficherGraphe] Impossible de caster en Sss* à l'indice" << i;
            i++;
            continue;
        }
        scene->addItem(nodeSss);

        int j = i + 1;
        int nbSrs = -1;

        while (j < nodes.size() && nodes[j]->getType() == TypeFile::srs) {
            NodeItem* nodeSrs = nodes[j];
            File* srsFile = nodeSrs->getFile();
            Srs* srsPtr = dynamic_cast<Srs*>(srsFile);
            nbSrs++;

            if (!srsPtr) {
                qWarning() << "[afficherGraphe] Impossible de caster en Srs* à l'indice" << j;
                j++;
                continue;
            }

            scene->addItem(nodeSrs);

            int taux = criteres.isEmpty()
                           ? Tracabilite::taux_traca_sss_srs(sssPtr->getExigence(), srsPtr->getExigence())
                           : Tracabilite::taux_traca(sssPtr->getIdsExigence(criteres), srsPtr->getIdsExigenceMatchesCriteres(criteres));


                scene->addItem(ajouterLien(nodeSss, nodeSrs, taux));


            // SDD
            if (j + 1 < nodes.size() && nodes[j + 1]->getType() == TypeFile::sdd) {
                NodeItem* nodeSdd = nodes[j + 1];
                File* sddFile = nodeSdd->getFile();
                Sdd* sddPtr = dynamic_cast<Sdd*>(sddFile);

                if (!sddPtr || !srsPtr->hasFils()) {
                    qWarning() << "[afficherGraphe] SDD invalide ou manquant à l'indice" << j + 1;
                    j += 2;
                    continue;
                }

                scene->addItem(nodeSdd);

                int tauxSDD = criteres.isEmpty()
                                  ? Tracabilite::taux_traca_srs_sdd(srsPtr->getExigence(), sddPtr->getExigence())
                                  : Tracabilite::taux_traca(srsPtr->getIdsExigenceMatchesCriteresWithSdd(criteres), sddPtr->getIdsExigence(criteres));


                    scene->addItem(ajouterLien(nodeSrs, nodeSdd, tauxSDD));


                j++;
            }

            j++;
        }

        i = j;
    }
}

/**
 * @brief Récupère la liste des fichiers associés au graphe.
 *
 * Cette méthode retourne la liste des fichiers associés au graphe sous forme de "QVector<Sss*>".
 *
 * @return QVector<Sss*> La liste des fichiers associés au graphe.
 * @author Maxime
 */
QVector<Sss*> Graphe::getFichiers() {
    return fichiers;
}
