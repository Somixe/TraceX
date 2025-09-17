#include "stylefile.h"

/**
 * @brief Constructeur complet de la classe StyleFile.
 *
 * Initialise un style avec tous ses attributs : identifiant, nom, police, taille, couleur et effets (gras, italique, souligné, ombre).
 *
 * @param id Identifiant du style.
 * @param name Nom du style.
 * @param police Police de caractères.
 * @param policeSize Taille de la police.
 * @param color Couleur du texte.
 * @param gras Texte en gras ou non.
 * @param italique Texte en italique ou non.
 * @param souligne Texte souligné ou non.
 * @param shadow Texte avec ombre ou non.
 *
 * @author malek
 */
StyleFile::StyleFile(const std::string& id,const std::string& name,const std::string& police,const int& policeSize,const std::string& color,const bool& gras,
                     const bool& italique,const bool& souligne,const bool& shadow) :
    id(id),name(name), police(police),policeSize(policeSize),color(color), gras(gras), italique(italique), souligne(souligne), shadow(shadow){}

/**
 * @brief Constructeur par défaut de la classe StyleFile.
 *
 * Initialise un style vide avec des valeurs neutres (pas de style particulier).
 *
 *@author malek
 */
StyleFile::StyleFile() :
    id(""), name(""), police(""),policeSize(0), color("black"), gras(false), italique(false), souligne(false), shadow(false){}

/**
 * @brief Récupère l'identifiant du style.
 * @return std::string Identifiant du style.
 *
 * @author malek
 */
std::string StyleFile::getId() const{
    return id;
}

/**
 * @brief Récupère la police utilisée dans le style.
 * @return std::string Nom de la police.
 *
 * @author malek
 */
std::string StyleFile::getPolice()const {
    return police;
}

/**
 * @brief Récupère la taille de police.
 * @return int Taille de la police.
 *
 * @author malek
 */
int StyleFile::getPoliceSize()const{
    return policeSize;
}

/**
 * @brief Récupère la couleur du texte.
 * @return std::string Couleur (en texte ou code hexadécimal).
 *
 * @author malek
 */
std::string StyleFile::getColor()const {
    return color;
}


/**
 * @brief Récupère le nom du style.
 * @return std::string Nom du style.
 *
 * @author malek
 */
std::string StyleFile::getName() const
{
    return name;
}

/**
 * @brief Indique si le style est en gras.
 * @return bool Vrai si gras, faux sinon.
 *
 * @author malek
 */
bool StyleFile::isGras() const {
    return gras;
}

/**
 * @brief Indique si le style est en italique.
 * @return bool Vrai si italique, faux sinon.
 *
 * @author malek
 */
bool StyleFile::isItalique() const{
    return italique;
}

/**
 * @brief Indique si le style est souligné.
 * @return bool Vrai si souligné, faux sinon.
 *
 * @author malek
 */
bool StyleFile::isSouligne() const{
    return souligne;
}

/**
 * @brief Indique si le style contient une ombre.
 * @return bool Vrai si ombre, faux sinon.
 *
 * @author malek
 */
bool StyleFile::isShadow() const {
    return shadow;
}

/**
 * @brief Convertit le style en texte lisible avec les caractéristiques principales.
 *
 * Cette méthode assemble les informations du style (police, taille, couleur, options) en une seule chaîne lisible.
 *
 * @return QString Représentation lisible du style.
 *
 * @author malek
 */
QString StyleFile::toQString()const {
    QString rtr;
    std::string interim = std::to_string(this->getPoliceSize());
    rtr = rtr.append(""+QString::fromStdString(police)+" , "+QString::fromStdString(interim)+" , "+QString::fromStdString(color));
    if(gras){
        rtr.append(" , gras");
    }
    if(italique){
        rtr.append(" , italique");
    }
    if(souligne){
        rtr.append(" , souligné");
    }
    if(shadow){
        rtr.append(" , ombre");
    }
    return rtr;
}
