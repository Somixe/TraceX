#include "sss.h"
#include "xmlparserutils.h"

StyleFile Sss::style = StyleFile();
QStringList Sss::radicaux = QStringList();

/**
 * @brief Constructeur de la classe Sss à partir du chemin du fichier.
 * @param path Le chemin du fichier SSS.
 * @author Malek
 */
Sss::Sss(std::string path) :
    File(path){}


/**
 * @brief Définit le style utilisé pour identifier les exigences.
 * @param style L'objet StyleFile à utiliser.
 * @return void
 * @author Malek
 */
void Sss::setStyle(StyleFile style){
    Sss::style=style;
}

/**
 * @brief Ajoute une exigence à la liste.
 * @param e L'exigence à ajouter.
 * @return void
 * @author Malek
 */
void Sss::addExigence(Exigence e){
    exigences.push_back(e);
}

/**
 * @brief Extrait les exigences depuis le fichier SSS en fonction du style défini.
 * @return void
 * @author Malek
 */
void Sss::extractExigences(){
    std::vector<std::string> vect = XmlParserUtils::extract_exigence_sss(this->getPath(),style);
    for(std::string& s : vect){
        this->addExigence(Exigence(s));
    }
}
/**
 * @brief Définit les fichiers SRS enfants associés à ce SSS.
 * @param fils Vecteur de pointeurs vers les objets SRS.
 * @return void
 * @author Malek
 */
void Sss::setFils(QVector<Srs*> fils){
    this->fils=fils;
}


/**
 * @brief Retourne la liste des exigences extraites.
 * @return std::vector<Exigence> Liste des exigences.
 * @author Malek
 */
std::vector<Exigence> Sss::getExigence() const{
    return exigences;
}

/**
 * @brief Retourne le nombre total d’exigences du fichier SSS.
 * @return int Nombre d’exigences.
 * @author Malek
 */
int Sss::totalExigences() const{
    return exigences.size();
}

/**
 * @brief Ajoute un SRS comme enfant du SSS.
 * @param srs Pointeur vers un objet SRS.
 * @return void
 * @author Malek
 */
void Sss::addFils(Srs *srs)
{
    fils.append(srs);
}

/**
 * @brief Récupère la liste des radicaux sélectionnables dans une vue utilisateur.
 * @return QStringList Liste des radicaux disponibles.
 * @author Malek
 */
QStringList Sss::getAttributRadicaux()
{
    return radicaux;
}

/**
 * @brief Extrait tous les styles disponibles depuis le fichier SSS.
 * @return std::vector<StyleFile> Liste des styles détectés.
 * @author Malek
 */
std::vector<StyleFile> Sss::extractStyles() const{
    return XmlParserUtils::extract_all_styles(this->getPath());
}


/**
 * @brief Récupère les identifiants des exigences filtrés par radicaux cochés.
 * @param liste Liste des radicaux sélectionnés dans l'interface.
 * @return std::vector<std::string> Identifiants des exigences correspondantes.
 * @author Malek, Maxime
 */
std::vector<std::string> Sss::getIdsExigence(const QStringList& liste){
    std::vector<std::string> radicaux_coches;
    std::vector<std::string> rtr;
    //extraire les radicaux sélectionnés
    if(this->isExcel() && File::getRadical()!=""){
        for(const QString& rad : liste){
            if (radicaux.contains(rad)){
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
 * @brief Vide la liste statique des radicaux enregistrés.
 * @return void
 * @author Malek
 */
void Sss::reinitialiserRadicaux()
{
    Sss::radicaux.clear();
}

/**
 * @brief Extrait les radicaux à partir des identifiants d’exigence, et les enregistre.
 * @return void
 * @author Malek, Maxime
 * @date 09/05/2025
 */
void Sss::getRadicaux()
{
    if(this->isExcel() && File::getRadical()!=""){
        QString radic;
        QRegularExpression regex(File::getRadical());

        for (const Exigence& ex : exigences) {
            std::string id = ex.getId();
            size_t pos = id.find_last_of('_');

            if (pos != std::string::npos) {
                radic = QString::fromStdString(id.substr(0, pos)); //radic contient la chaine de caractère avant le dernier delimiteur
            }
            if(!Srs::getFiltres().contains(radic) && regex.match(radic).hasMatch()){
                Srs::addFiltres(radic);
            }
            if(!Sss::radicaux.contains(radic)){
                Sss::radicaux.append(radic);

            }
        }
    }
}

/**
 * @brief Retourne tous les identifiants d'exigences sous forme de texte.
 * @return QString Texte contenant les identifiants, séparés par des sauts de ligne.
 * @author Malek
 */
QString Sss::toQStringExigence()
{
    QString rtr ="";
    for(const Exigence &e : exigences){
        rtr = rtr+"\n"+QString::fromStdString(e.getId());
    }
    return rtr;
}

/**
 * @brief Récupère la liste des fichiers SRS enfants associés à ce SSS.
 * @return QVector<Srs*> Vecteur des enfants SRS.
 * @author Malek
 */
QVector<Srs*> Sss::getFils(){
    return fils;
};
