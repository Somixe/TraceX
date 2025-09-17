#ifndef SDD_H
#define SDD_H

#include "stylefile.h"
#include "exigence.h"
#include "file.h"
#include <vector>

class Sdd : public File
{
private:
    static StyleFile style;
    std::vector<Exigence> exigences;
public:
    Sdd();
    Sdd(const std::string& path);
    /**
     * @brief setStyle : attribue un style aux exigences des Sdd
     * @param style : le style à attribuer aux exigences des Sdd
     */
    static void setStyle(StyleFile style);

    /**
     * @brief addExigence : ajouter une exigence à l'attribut exigences
     * @param e : l'exigence à ajouter
     */
    void addExigence(Exigence e);

    /**
     * @brief getExigence : récupérer l'attribut 'exigences'
     * @return un vecteur des exigences d'un Sdd
     */
    std::vector<Exigence> getExigence() const;
    /**
     * @brief extractExigences : extraire les exigences d'un fichier Sdd
     * @details la fonction récupère d'abord les fichiers xml
     *          ensuite elle parcourt le fichier xml balise par balise avec pugixml
     *          récupère le texte de l'exigence et le stocke dans exigences
     */
    void extractExigences();

    /**
     * @brief extractStyles : extrait les styles utilisés dans le fichier word
     * @return un vecteur qui contient les styles utilisés dans un fichier
     */
    std::vector<StyleFile> extractStyles() const;

    /**
     * @brief totalExigences : calcul le nombre d'exigence dans un fichier
     * @return la taille de l'attribut exigences
     */
    int totalExigences() const;

    std::vector<std::string> getIdsExigence(const QStringList& liste);

    void getRadicaux();
    QString toQStringExigence();
};

#endif // SDD_H
