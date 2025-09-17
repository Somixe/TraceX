#ifndef RAPPORTLIGNE_H
#define RAPPORTLIGNE_H
#include <algorithm>
#include <vector>
#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <QString>
#include "exigencesrs.h"
#include "exigence.h"
#include "sss.h"
#include "srs.h"
#include "sdd.h"
using namespace std;
/**
 * @class Rapportligne
 * @brief Contient les informations sur une ligne du rapport
 *
 * @author Lea KIM
 */
class Rapportligne {
private :
    QString nameSSS;
    QString nameSRS;
    QString nameSDD;
    string exigenceSSS;
    string exigenceSRS;
    string exigenceSDD;
public :
    /**
     * @brief constructeur
     * @param nameSSS nom du fichier SSS tracé
     * @param nameSRS nom du fichier SRS si tracé
     * @param nameSDD nom du fichier SDD si tracé
     * @param exigenceSSS exigence du SSS tracé
     * @param exigenceSRS exigence du SRS si tracé
     * @param exigenceSDD exigence du SDD si tracé
     *
     * @author Lea KIM
     */
    Rapportligne(QString nameSSS,QString nameSRS,QString nameSDD,string exigenceSSS,string exigenceSRS,string exigenceSDD);
    Rapportligne();
    /**
     * @brief setter du nom du fichier SSS
     * @param nameSSS nouveau nom du fichier
     *
     * @author Lea KIM
     */
    void setNameSSS(QString nameSSS) ;
    /**
     * @brief setter du nom du fichier SRS
     * @param nameSRS nouveau nom du fichier
     *
     * @author Lea KIM
     */
    void setNameSRS(QString nameSRS) ;
    /**
     * @brief setter du nom du fichier SDD
     * @param nameSDD nouveau nom du fichier
     *
     * @author Lea KIM
     */
    void setNameSDD(QString nameSDD) ;
    /**
     * @brief setter du nom de l'exigence dans le SSS
     * @param exigenceSSS nouveau nom d'exigence
     *
     * @author Lea KIM
     */
    void setExigenceSSS(string exigenceSSS) ;
    /**
     * @brief setter du nom de l'exigence dans le SRS
     * @param exigenceSRS nouveau nom d'exigence
     *
     * @author Lea KIM
     */
    void setExigenceSRS(string exigenceSRS) ;
    /**
     * @brief setter du nom de l'exigence dans le SDD
     * @param exigenceSDD nouveau nom d'exigence
     *
     * @author Lea KIM
     */
    void setExigenceSDD(string exigenceSDD) ;
    /**
     * @brief vérifie si l'exigence exi est dans le document docSrs
     * @param exi exigence que l'on cherche dans le document
     * @param docSrs document où l'on cherche l'exigence
     * @param rtr exigence trouvée et retournée
     *
     * @author Lea KIM
     */
    bool isInSrs(Exigence* exi, Srs docSrs, ExigenceSrs& rtr);
    /**
     * @brief vérifie si l'exigence exi est dans le document docSdd
     * @param exi exigence que l'on cherche dans le document
     * @param docSdd document où l'on cherche l'exigence
     *
     * @author Lea KIM
     */
    bool isInSdd(Exigence* exi,Sdd docSdd);
    /**
     * @brief retourne un string correspondant à une ligne de fichier csv
     *
     * @author Lea KIM
     */
    string toString() ;
};
#endif //RAPPORTLIGNE_H
