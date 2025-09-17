#include <algorithm>
#include <vector>
#include <string>
#include <list>

#include <fstream>
#include <sstream>

#include <QVector>
#include <QString>

#include "rapport.h"

using namespace std;

/**
 * @brief Constructeur pour initialiser un rapport avec une liste de documents SSS.
 *
 * Ce constructeur initialise une instance de la classe "Rapport" en lui associant une liste de documents
 * SSS (de type "QVector<Sss*>").
 *
 * @param listeDocSss La liste des documents SSS associés au rapport.
 * @author Léa
 */
Rapport::Rapport(QVector<Sss*> listeDocSss) {
    this->listeDocSss = listeDocSss;
    this->lignesRapport = list<Rapportligne>();
}

/**
 * @brief Récupère la liste des lignes de rapport.
 *
 * Cette méthode retourne la liste des lignes de rapport générées, chacune contenant des informations
 * relatives à l'association entre les documents SSS, SRS et SDD.
 *
 * @return list<Rapportligne> La liste des lignes de rapport.
 * @author Léa
 */
list<Rapportligne> Rapport::getLignesRapport() {
    return this->lignesRapport;
}

/**
 * @brief Génère le rapport en fonction des documents SSS et de leurs relations avec les documents SRS et SDD.
 *
 * Cette méthode parcourt les documents SSS et leurs exigences, puis cherche les documents SRS et SDD
 * associés en fonction de la traçabilité des exigences, et les ajoute aux lignes de rapport.
 *
 * @param listeDocSss La liste des documents SSS à analyser pour générer le rapport.
 * @return void
 * @author Léa
 */
void Rapport::generation(QVector<Sss*> listeDocSss) {
    for (Sss* docSss : this->listeDocSss) {
        vector<Exigence> listeExigencesSss = docSss->getExigence();
        QVector<Srs*> listeDocSrs = docSss->getFils();

        for (Exigence exi : listeExigencesSss) {
            int i = 0;
            Rapportligne rl;
            rl.setNameSSS(docSss->getNom());
            rl.setExigenceSSS(exi.toString());
            bool found = false;
            while (!found && i < listeDocSrs.size()) {
                ExigenceSrs rtr = ExigenceSrs("",false);
                if (rl.isInSrs(&exi,*listeDocSrs[i], rtr)) {
                    rl.setNameSRS(listeDocSrs[i]->getNom());
                    rl.setExigenceSRS(rtr.getId());
                    Sdd* docSdd = listeDocSrs[i]->getFils();
                    if (rl.isInSdd(&rtr,*docSdd)) {
                        rl.setNameSDD(docSdd->getNom());
                        rl.setExigenceSDD(rtr.getId());
                    }

                    found = true;
                }
                i++;
            }
            this->lignesRapport.push_back(rl);

        }
    }
}
