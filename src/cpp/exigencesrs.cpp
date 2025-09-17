#include "exigencesrs.h"



/**
 * @brief Constructeur de la classe ExigenceSrs.
 *
 * Ce constructeur permet d'initialiser un objet ExigenceSrs avec les paramètres fournis.
 * Il initialise les membres de l'objet ExigenceSrs à partir de l'ID, de la cible, des nécessités, de l'état de développement et de la tracabilité.
 *
 * @param id L'identifiant de l'exigence.
 * @param cible Liste des cibles associées à l'exigence.
 * @param Necessaire Liste des clients.
 * @param dev Indicateur de développement (true si développé, false sinon).
 * @param tracabilite liste des exigences tracées.
 *
 * @author Malek
 */
ExigenceSrs::ExigenceSrs(const std::string& id, const std::vector<std::string>& cible,
                         const std::vector<std::string>& Necessaire, bool dev, const std::vector<std::string>& tracabilite) :
    Exigence(id), cible(cible), Necessaire(Necessaire), dev(dev), tracabilite(tracabilite){}



/**
 * @brief Constructeur de la classe ExigenceSrs.
 *
 * Ce constructeur permet d'initialiser un objet ExigenceSrs avec les paramètres fournis.
 * Il initialise les membres de l'objet ExigenceSrs à partir de l'ID, des éléments nécessaires, de l'état de développement et de la tracabilité.
 * Il ne prend pas en compte les cibles, contrairement à l'autre constructeur.
 *
 * @param id L'identifiant de l'exigence.
 * @param Necessaire Liste des éléments nécessaires à l'exigence.
 * @param dev Indicateur de développement (true si développé, false sinon).
 * @param tracabilite Liste des éléments de tracabilité associés à l'exigence.
 *
 * @author Malek
 */
ExigenceSrs::ExigenceSrs(const std::string& id, const std::vector<std::string>& Necessaire, bool dev, const std::vector<std::string>& tracabilite):
    Exigence(id), Necessaire(Necessaire), dev(dev), tracabilite(tracabilite){}



/**
 * @brief Constructeur de la classe ExigenceSrs.
 *
 * Ce constructeur permet d'initialiser un objet ExigenceSrs avec les paramètres fournis.
 * Il initialise les membres de l'objet ExigenceSrs à partir de l'ID, de l'état de développement et de la tracabilité.
 * Ce constructeur ne prend en compte ni les cibles ni les éléments nécessaires.
 *
 * @param id L'identifiant de l'exigence.
 * @param dev Indicateur de développement (true si développé, false sinon).
 * @param tracabilite Liste des éléments de tracabilité associés à l'exigence.
 *
 * @author Malek
 */
ExigenceSrs::ExigenceSrs(const std::string& id,bool dev, const std::vector<std::string>& tracabilite) :
    Exigence(id), dev(dev), tracabilite(tracabilite){}



/**
 * @brief Constructeur de la classe ExigenceSrs.
 *
 * Ce constructeur permet d'initialiser un objet ExigenceSrs avec l'identifiant de l'exigence et l'état de développement.
 * Ce constructeur ne prend en compte ni les cibles, ni les éléments nécessaires, ni la tracabilité.
 *
 * @param id L'identifiant de l'exigence.
 * @param dev Indicateur de développement (true si développé, false sinon).
 *
 * @author Malek
 */
ExigenceSrs::ExigenceSrs(const std::string &id, bool dev) :
    Exigence(id), dev(dev){}



/**
 * @brief Récupère la liste des cibles de l'exigence.
 *
 * Cette méthode retourne un vecteur contenant toutes les cibles associées à l'exigence.
 *
 * @return std::vector<std::string> Liste des cibles de l'exigence.
 *
 * @author Malek
 */
std::vector<std::string> ExigenceSrs::getCible() const{
    return cible;
}



/**
 * @brief Récupère la liste des éléments nécessaires de l'exigence.
 *
 * Cette méthode retourne un vecteur contenant tous les éléments nécessaires associés à l'exigence.
 *
 * @return std::vector<std::string> Liste des éléments nécessaires de l'exigence.
 *
 * @author Malek
 */
std::vector<std::string> ExigenceSrs::getNecessaire() const {
    return Necessaire;
}



/**
 * @brief Récupère la liste des éléments de tracabilité de l'exigence.
 *
 * Cette méthode retourne un vecteur contenant tous les éléments de tracabilité associés à l'exigence.
 *
 * @return std::vector<std::string> Liste des éléments de tracabilité de l'exigence.
 *
 * @author Malek
 */
std::vector<std::string> ExigenceSrs::getTracabilite() const
{
    return tracabilite;
}


/**
 * @brief Vérifie si l'exigence est développée.
 *
 * Cette méthode retourne un indicateur qui permet de savoir si l'exigence est considérée comme développée.
 *
 * @return true Si l'exigence est développée.
 * @return false Si l'exigence n'est pas développée.
 *
 * @author Malek
 */
bool ExigenceSrs::isDev()const{
    return dev;
}


/**
 * @brief Vérifie si l'exigence a des cibles définies.
 *
 * Cette méthode permet de vérifier si l'exigence contient des cibles. Elle retourne true si la liste des cibles n'est pas vide, sinon false.
 *
 * @return true Si l'exigence possède des cibles.
 * @return false Si l'exigence n'a pas de cibles.
 *
 * @author Malek
 */
bool ExigenceSrs::hasCible() const {
    return (!cible.empty());
}


/**
 * @brief Vérifie si l'exigence a des éléments nécessaires définis.
 *
 * Cette méthode permet de vérifier si la liste "nécessaire" n'est pas vide. Elle retourne true si la liste des éléments nécessaires n'est pas vide, sinon false.
 *
 * @return true Si l'exigence possède des éléments nécessaires.
 * @return false Si l'exigence n'a pas d'éléments nécessaires.
 *
 * @author Malek
 */
bool ExigenceSrs::hasNecessaire() const{
    return (!Necessaire.empty());
}


/**
 * @brief Génère une représentation sous forme de chaîne de caractères de l'exigence.
 *
 * Cette méthode retourne une chaîne de caractères contenant l'ID, les cibles, les éléments nécessaires et l'état de développement (dev ou non dev) de l'exigence.
 * Elle permet de visualiser facilement les informations principales d'une exigence sous un format lisible.
 *
 * @return std::string Représentation sous forme de chaîne de caractères de l'exigence.
 *
 * @author Malek
 */
std::string ExigenceSrs::toString(){
    std::string rtr = "Id : "+this->getId()+"\n";
    rtr+= "Cible : ";
    for(std::string& s : this->cible){
        rtr+=s+" , ";
    }
    rtr+="\nNecessaire : ";
    for(std::string& s : this->Necessaire){
        rtr+=s+" , ";
    }
    if(this->dev == true){
        rtr += "\ndev";
    }else{
        rtr+="\nndev";
    }
    return rtr;
}
