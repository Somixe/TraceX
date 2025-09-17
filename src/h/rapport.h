#ifndef RAPPORT_H
#define RAPPORT_H

#include <algorithm>
#include <vector>
#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>

#include "exigencesrs.h"
#include "exigence.h"
#include "sss.h"
#include "srs.h"
#include "sdd.h"
#include "rapportligne.h"

using namespace std;

/**
 * @class Rapport
 * @brief Génère le rapport
 *
 * @author Lea KIM
 *
 * Cette classe s'occupe de la création du rapport
 * Elle contient un vecteur de Rapportligne et une liste de documents SSS
 */
class Rapport {
private :
    list<Rapportligne> lignesRapport;
    QVector<Sss*> listeDocSss;

public :
    /**
     * @brief constructeur
     * @param listeDocSSS liste des documents SSS du graphe
     *
     * @author Lea KIM
     */
    Rapport(QVector<Sss*> listeDocSss);

    list<Rapportligne> getLignesRapport();

    /**
     * @brief rempli lignesRapport en traitant les exigences de chaque SSS
     * @param listeDocSSS liste des documents SSS du graphe
     *
     * @author Lea KIM
     */
    void generation(QVector<Sss*> listeDocSss);
};

#endif //RAPPORT_H
