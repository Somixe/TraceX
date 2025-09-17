#include "sdd.h"

#include "xmlparserutils.h"



StyleFile Sdd::style = StyleFile();

/**
 * @brief Constructeur de la classe Sdd.
 *
 * Ce constructeur initialise un objet "Sdd" en appelant le constructeur par défaut de la classe "File".
 * Il permet de créer un objet de type "Sdd" tout en initialisant les membres hérités de "File".
 * @author malek
 */
Sdd::Sdd(){
    File();
}

/**
 * @brief Constructeur de la classe Sdd avec un chemin de fichier.
 *
 * Ce constructeur initialise un objet "Sdd" en appelant le constructeur de la classe "File"
 * avec un chemin de fichier spécifié. Cela permet de créer un objet "Sdd" en fournissant
 * directement le chemin vers le fichier associé.
 *
 * @param path Le chemin du fichier à associer à l'objet "Sdd".
 * @author malek
 */
Sdd::Sdd(const std::string& path) :
    File(path){}


/**
 * @brief Définit le style pour cet objet Sdd.
 *
 * Cette méthode permet de définir un style spécifique à l'objet "Sdd". Le style est
 * assigné à l'attribut "style" de la classe "Sdd" (le style des exigences définies dans un SDD).
 *
 * @param style Le style à associer à l'objet "Sdd".
 *
 * @author Malek
 */
void Sdd::setStyle(StyleFile style){
    Sdd::style=style;
}

/**
 * @brief Ajoute une exigence à l'objet Sdd.
 *
 * Cette méthode permet d'ajouter une exigence à la liste des exigences de l'objet "Sdd".
 *
 * @param e L'exigence à ajouter à la liste.
 *
 * @author Malek
 */
void Sdd::addExigence(Exigence e){
    exigences.push_back(e);
}


/**
 * @brief Extrait les exigences à partir du fichier SDD et les ajoute à la liste d'exigences.
 *
 * Cette méthode utilise la fonction "extract_exigence_sss" de la calsse XmlParser pour extraire un ensemble d'exigences
 * à partir du fichier SDD actuel, en utilisant le chemin du fichier et le style associé.
 * Les exigences extraites sont ensuite ajoutées à la liste des exigences de l'objet "Sdd".
 *
 * @note La méthode appelle "addExigence" pour chaque exigence extraite.
 *
 * @author Malek
 */
void Sdd::extractExigences(){
    std::vector<std::string> vect = XmlParserUtils::extract_exigence_sss(this->getPath(),style);
    for(std::string& s : vect){
        this->addExigence(Exigence(s));
    }
}

/**
 * @brief Récupère la liste des exigences associées à l'objet Sdd.
 *
 * Cette méthode retourne un vecteur contenant toutes les exigences qui ont été ajoutées à
 * l'objet "Sdd".
 *
 * @return std::vector<Exigence> Le vecteur contenant toutes les exigences de l'objet "Sdd".
 *
 * @author Malek
 */
std::vector<Exigence> Sdd::getExigence() const{
    return exigences;
}

int Sdd::totalExigences() const{
    return exigences.size();
}


/**
 * @brief Extrait tous les styles associés au fichier SDD.
 *
 * Cette méthode utilise la fonction "extract_all_styles" de la classe XmlParser pour extraire tous les styles
 * utilisés dans le fichier SDD en utilisant le chemin du fichier actuel. Elle retourne un vecteur
 * contenant tous les styles extraits.
 *
 * @return std::vector<StyleFile> Un vecteur contenant tous les styles extraits du fichier SDD.
 *
 * @author Malek
 */
std::vector<StyleFile> Sdd::extractStyles() const{
    return XmlParserUtils::extract_all_styles(this->getPath());
}

/**
 * @brief Récupère les identifiants de toutes les exigences.
 *
 * @return std::vector<std::string> Un vecteur contenant les identifiants de toutes les exigences.
 *
 * @author Malek
 */
std::vector<std::string> Sdd::getIdsExigence(const QStringList& liste){
    std::vector<std::string> radicaux_coches;
    std::vector<std::string> rtr;
    if(this->isExcel() && File::getRadical()!=""){
        for(const QString& rad : liste){
            if (Sss::getAttributRadicaux().contains(rad)){
                radicaux_coches.push_back(rad.toStdString());
            }
        }

    }
    if(!radicaux_coches.empty()){
        for(const Exigence& ex : exigences){
            std::string id = ex.getId();
            size_t pos = id.find_last_of('_');
            if (pos != std::string::npos) {
                std::string radical = id.substr(0, pos);
                if (std::find(radicaux_coches.begin(), radicaux_coches.end(), radical) != radicaux_coches.end()){
                    rtr.push_back(ex.getId());
                }
            }

        }
    }else{
        for(const Exigence& e : exigences){
            rtr.push_back(e.getId());
        }
    }
    return rtr;
}

/**
 * @brief Extrait les radicaux des exigences dans le fichier SDD (format Excel uniquement).
 *
 * Si le fichier est au format Excel et qu’un radical est défini, cette méthode identifie les radicaux
 * dans les identifiants des exigences (avant le dernier "_") et les ajoute à la liste des filtres
 * partagée avec la classe Srs.
 *
 * @return void
 * @author Malek
 */
void Sdd::getRadicaux()
{
    if(this->isExcel() && File::getRadical()!=""){
        QString radic;
        for (const Exigence& ex : exigences) {
            std::string id = ex.getId();
            size_t pos = id.find_last_of('_');
            if (pos != std::string::npos) {
                radic = QString::fromStdString(id.substr(0, pos));
            }
        }
        if(!Srs::getFiltres().contains(radic)){
            Srs::getFiltres().append(radic);
        }
    }
}


/**
 * @brief Retourne tous les identifiants d'exigences du fichier SDD sous forme de texte lisible.
 *
 * Chaque identifiant est séparé par un retour à la ligne.
 *
 * @return QString Liste des identifiants d’exigence du SDD.
 * @author Malek
 */
QString Sdd::toQStringExigence()
{
    QString rtr ="";
    for(const Exigence &e : exigences){
        rtr = rtr+"\n"+QString::fromStdString(e.getId());
    }
    return rtr;
}

