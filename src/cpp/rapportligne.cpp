#include <algorithm>
#include <vector>
#include <string>
#include <list>

#include <fstream>
#include <sstream>
#include <QString>
#include "rapportligne.h"
using namespace std;

/**
 * @brief Constructeur avec paramètres pour initialiser une ligne de rapport avec des valeurs spécifiques.
 *
 * Ce constructeur initialise une instance de la classe "Rapportligne" avec des valeurs définies pour
 * les noms des fichiers SSS, SRS, et SDD, ainsi que les exigences associées.
 *
 * @param nameSSS Le nom du fichier SSS.
 * @param nameSRS Le nom du fichier SRS.
 * @param nameSDD Le nom du fichier SDD.
 * @param exigenceSSS L'exigence associée au fichier SSS.
 * @param exigenceSRS L'exigence associée au fichier SRS.
 * @param exigenceSDD L'exigence associée au fichier SDD.
 * @author Léa
 */
Rapportligne::Rapportligne(QString nameSSS,QString nameSRS,QString nameSDD,string exigenceSSS,string exigenceSRS,string exigenceSDD) {
    this->nameSSS = nameSSS;
    this->nameSRS = nameSRS;
    this->nameSDD = nameSDD;
    this->exigenceSSS = exigenceSSS;
    this->exigenceSRS = exigenceSRS;
    this->exigenceSDD = exigenceSDD;
}

/**
 * @brief Constructeur par défaut pour initialiser une ligne de rapport avec des valeurs vides.
 *
 * Ce constructeur initialise une instance de la classe "Rapportligne" avec des chaînes vides pour tous
 * les attributs de la ligne de rapport.
 *
 * @author Léa
 */
Rapportligne::Rapportligne() {
    this->nameSSS = "";
    this->nameSRS = "";
    this->nameSDD = "";
    this->exigenceSSS = "";
    this->exigenceSRS = "";
    this->exigenceSDD = "";
}

/**
 * @brief Définit le nom du fichier SSS.
 *
 * Cette méthode permet de définir le nom du fichier SSS associé à la ligne de rapport.
 *
 * @param nameSSS Le nom du fichier SSS à attribuer à la ligne de rapport.
 * @return void
 * @author Léa
 */
void Rapportligne::setNameSSS(QString nameSSS) {
    this->nameSSS = nameSSS;
}

/**
 * @brief Définit le nom du fichier SRS.
 *
 * Cette méthode permet de définir le nom du fichier SRS associé à la ligne de rapport.
 *
 * @param nameSRS Le nom du fichier SRS à attribuer à la ligne de rapport.
 * @return void
 * @author Léa
 */
void Rapportligne::setNameSRS(QString nameSRS) {
    this->nameSRS = nameSRS;
}

/**
 * @brief Définit le nom du fichier SDD.
 *
 * Cette méthode permet de définir le nom du fichier SDD associé à la ligne de rapport.
 *
 * @param nameSDD Le nom du fichier SDD à attribuer à la ligne de rapport.
 * @return void
 * @author Léa
 */
void Rapportligne::setNameSDD(QString nameSDD) {
    this->nameSDD = nameSDD;
}

/**
 * @brief Définit l'exigence associée au fichier SSS.
 *
 * Cette méthode permet de définir l'exigence associée au fichier SSS dans la ligne de rapport.
 *
 * @param exigenceSSS L'exigence à associer au fichier SSS.
 * @return void
 * @author Léa
 */
void Rapportligne::setExigenceSSS(string exigenceSSS) {
    this->exigenceSSS = exigenceSSS;
}

/**
 * @brief Définit l'exigence associée au fichier SRS.
 *
 * Cette méthode permet de définir l'exigence associée au fichier SRS dans la ligne de rapport.
 *
 * @param exigenceSRS L'exigence à associer au fichier SRS.
 * @return void
 * @author Léa
 */
void Rapportligne::setExigenceSRS(string exigenceSRS) {
    this->exigenceSRS = exigenceSRS;
}

/**
 * @brief Définit l'exigence associée au fichier SDD.
 *
 * Cette méthode permet de définir l'exigence associée au fichier SDD dans la ligne de rapport.
 *
 * @param exigenceSDD L'exigence à associer au fichier SDD.
 * @return void
 * @author Léa
 */
void Rapportligne::setExigenceSDD(string exigenceSDD) {
    this->exigenceSDD = exigenceSDD;
}

/**
 * @brief Vérifie si une exigence existe dans le fichier SRS.
 *
 * Cette méthode parcourt les exigences du fichier SRS et vérifie si l'exigence avec l'identifiant
 * correspondant à celui de l'exigence passée en paramètre est présente dans le fichier.
 *
 * @param exi L'exigence à rechercher dans le fichier SRS.
 * @param docSrs Le document SRS dans lequel effectuer la recherche.
 * @param rtr L'exigence SRS trouvée, si elle existe.
 * @return bool "true" si l'exigence est trouvée, "false" sinon.
 * @author Léa
 */
bool Rapportligne::isInSrs(Exigence* exi, Srs docSrs, ExigenceSrs& rtr) {
    vector<ExigenceSrs> v = docSrs.getExigence();
    bool res = false;
    for(const ExigenceSrs& e : v){
        for(string str : e.getTracabilite()){
            if (str.compare(exi->getId())==0){
                res = true;
                rtr = e;
            }
        }
    }
    return res;
}

/**
 * @brief Vérifie si une exigence existe dans le fichier SDD.
 *
 * Cette méthode parcourt les exigences du fichier SDD et vérifie si l'exigence avec l'identifiant
 * correspondant à celui de l'exigence passée en paramètre est présente dans le fichier.
 *
 * @param exi L'exigence à rechercher dans le fichier SDD.
 * @param docSdd Le document SDD dans lequel effectuer la recherche.
 * @return bool "true" si l'exigence est trouvée, "false" sinon.
 * @author Léa
 */
bool Rapportligne::isInSdd(Exigence* exi, Sdd docSdd) {
    vector<Exigence> v = docSdd.getExigence();
    bool res = false;
    for (Exigence e : v) {
        if (e.getId().compare(exi->getId())==0){
            res = true;
        }
    }
    return res;
}

/**
 * @brief Convertit les données de la ligne de rapport en une chaîne de caractères lisible.
 *
 * Cette méthode permet de convertir les informations contenues dans une ligne de rapport en une chaîne
 * de caractères qui peut être utilisée pour l'affichage ou l'écriture dans un fichier.
 *
 * @return string La chaîne de caractères représentant la ligne de rapport.
 * @author Léa
 */
string Rapportligne::toString() {
    stringstream buf;
    buf << nameSSS.toStdString();
    buf << ";";
    buf << nameSRS.toStdString();
    buf << ";";
    buf << nameSDD.toStdString();
    buf << ";";
    buf << this->exigenceSSS;
    buf << ";";
    buf << this->exigenceSRS;
    buf << ";";
    buf << this->exigenceSDD;
    return buf.str();
}
