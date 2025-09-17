#include "exigence.h"

/**
 * @brief Constructeur pour initialiser une exigence avec un identifiant.
 *
 * Ce constructeur initialise une instance de la classe "Exigence" avec un identifiant spécifique.
 *
 * @param id L'identifiant de l'exigence.
 * @author malek
 */
Exigence::Exigence(const std::string& id)
    : id(id) {}


/**
 * @brief Récupère l'identifiant de l'exigence.
 *
 * Cette méthode retourne l'identifiant de l'exigence sous forme de chaîne de caractères.
 *
 * @return std::string L'identifiant de l'exigence.
 * @author Malek
 */
std::string Exigence::getId()const{
    return id;
}

/**
 * @brief Retourne une représentation textuelle de l’exigence.
 *
 * Cette méthode retourne une chaîne de caractères du type "Id : <identifiant>".
 * Si l’attribut "id" est vide, elle retourne une chaîne vide afin d’éviter
 * d'afficher des exigences sans identifiant.
 *
 * @return Une chaîne de caractères décrivant l’exigence, ou une chaîne vide si l’id est vide.
 *
 * @author Jacques Zheng
 * @date 02/05/2025
 */

std::string Exigence::toString() const {
    if (id.empty()) return "" ;
    return "Id : " + id;
}
