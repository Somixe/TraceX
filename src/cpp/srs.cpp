#include "srs.h"
#include "xmlparserutils.h"
#include "FileUtils.h"


StyleFile Srs::style = StyleFile();
QStringList Srs::filtres;

/**
 * @brief Constructeur de la classe Srs.
 *
 * Initialise un objet Srs à partir d'un chemin de fichier donné.
 * Ce constructeur appelle le constructeur de la classe de base File
 * avec le chemin fourni, puis instancie dynamiquement un objet Sdd
 * associé à l'attribut "fils".
 *
 * @param path Le chemin vers le fichier source.
 *
 * @author malek
 */
Srs::Srs(const std::string& path) :
    File(path){
    this->fils= new Sdd();
}


/**
 * @brief Définit le style associé au fichier Srs.
 *
 * Cette méthode assigne un objet de type StyleFile à l'attribut statique "style"
 * de la classe Srs.
 *
 * @param style L'objet StyleFile à utiliser pour le style.
 *
 * @author malek
 */
void Srs::setStyle(StyleFile style){
    Srs::style=style;
}


/**
 * @brief Récupère le style associé à la classe Srs.
 *
 * Retourne l'objet StyleFile actuellement utilisé comme style pour les fichiers Srs.
 *
 * @return L'objet StyleFile représentant le style.
 *
 * @author Malek
 */
StyleFile Srs::getStyle() {
    return style;
}


/**
 * @brief Récupère la liste des filtres associés à la classe Srs.
 *
 * Cette méthode retourne la liste de filtres (attribut statique "filtres")
 * utilisée pour le traitement ou l'affichage des exigences dans un fichier Srs.
 *
 * @return Une QStringList contenant les filtres.
 *
 * @author malek
 */
QStringList Srs::getFiltres()
{
    return Srs::filtres;
}

/**
 * @brief Vérifie si un fichier fils est associé à cet objet Srs.
 *
 * Cette méthode retourne true si l'objet "fils" possède un chemin non vide,
 * indiquant qu'un fichier Sdd est bien lié à ce Srs.
 *
 * @return true si un fichier fils est présent, false sinon.
 *
 * @author Malek
 */
bool Srs::hasFils(){
    return !(fils->getPath()=="");
}


/**
 * @brief Définit le fichier fils (Sdd) associé à cet objet Srs.
 *
 * Cette méthode permet d’associer dynamiquement un fichier Sdd en tant que fils
 * de l’objet Srs courant.
 *
 * @param fils Pointeur vers l’objet Sdd à associer.
 *
 * @author Malek
 */
void Srs::setFils(Sdd* fils){
    this->fils=fils;
}



/**
 * @brief Récupère la liste des exigences associées à ce fichier Srs.
 *
 * Cette méthode retourne un vecteur contenant les objets ExigenceSrs
 * extraits ou définis pour ce fichier.
 *
 * @return Un vecteur d'objets ExigenceSrs.
 *
 * @author Malek
 */
std::vector<ExigenceSrs> Srs::getExigence() const{
    return exigences;
}



/**
 * @brief Ajoute une exigence à la liste des exigences du fichier Srs.
 *
 * Cette méthode insère un nouvel objet ExigenceSrs à la fin du vecteur "exigences".
 *
 * @param e L'exigence à ajouter.
 *
 * @author Malek
 */
void Srs::addExigence(ExigenceSrs e){
    exigences.push_back(e);
}


/**
 * @brief Réinitialise la liste des filtres de la classe Srs.
 *
 * Cette méthode vide complètement la liste statique "filtres" utilisée pour filtrer les exigences.
 *
 * @author Malek
 */
void Srs::reinitialiserFiltres()
{
    Srs::filtres.clear();
}


/**
 * @brief Retourne le nombre total d'exigences dans ce fichier Srs.
 *
 * Cette méthode retourne la taille du vecteur "exigences", c’est-à-dire
 * le nombre d’exigences actuellement enregistrées pour ce fichier.
 *
 * @return Le nombre d'exigences.
 *
 * @author Malek
 */
int Srs::totalExigences() const{
    return exigences.size();
}


/**
 * @brief Extrait tous les styles associés à ce fichier Srs.
 *
 * Cette méthode utilise un parseur XML pour extraire tous les styles
 * associés au fichier Srs à partir du chemin spécifié. Elle retourne
 * un vecteur contenant les objets StyleFile extraits.
 *
 * @return Un vecteur de StyleFile représentant tous les styles extraits.
 *
 * @author Malek
 */
std::vector<StyleFile> Srs::extractStyles() const{
    return XmlParserUtils::extract_all_styles(this->getPath());
}

/**
 * @brief Récupère le fichier fils associé à cet objet Srs.
 *
 * Cette méthode retourne le pointeur vers l'objet Sdd qui est actuellement
 * associé à cet objet Srs. Si aucun fichier fils n'est défini, le pointeur
 * sera nul.
 *
 * @return Pointeur vers le fichier fils (Sdd), ou nullptr si aucun fils n'est défini.
 *
 * @author Malek
 */
Sdd* Srs::getFils(){
    return fils;
};



/**
 * @brief Vérifie si la cible de l'exigence correspond à l'un des critères sélectionnés.
 *
 * Cette méthode vérifie si l'une des cibles de l'objet ExigenceSrs correspond
 * à l'un des critères présents dans le vecteur "criteres_selectionnes".
 * Si une correspondance est trouvée, la méthode retourne true, sinon false.
 *
 * @param e L'exigence à vérifier.
 * @param criteres_selectionnes Un vecteur de chaînes de caractères représentant les critères sélectionnés.
 *
 * @return true si la cible de l'exigence correspond à l'un des critères sélectionnés, false sinon.
 *
 * @author Malek
 */
bool Srs::isCibleMatchesCriteres(const ExigenceSrs& e, const std::vector<std::string>& criteres_selectionnes){
    bool trouve = false;
    for(int i=0; i< e.getCible().size() && !trouve; i++){
        if(std::find(criteres_selectionnes.begin(), criteres_selectionnes.end(), e.getCible()[i]) != criteres_selectionnes.end()){
            trouve = true;
        }
    }
    return trouve;
}


/**
 * @brief Vérifie si la nécessité de l'exigence correspond à l'un des critères sélectionnés.
 *
 * Cette méthode vérifie si l'une des nécessités de l'objet ExigenceSrs correspond
 * à l'un des critères présents dans le vecteur "criteres_selectionnes".
 * Si une correspondance est trouvée, la méthode retourne true, sinon false.
 *
 * @param e L'exigence à vérifier.
 * @param criteres_selectionnes Un vecteur de chaînes de caractères représentant les critères sélectionnés.
 *
 * @return true si la nécessité de l'exigence correspond à l'un des critères sélectionnés, false sinon.
 *
 * @author Malek
 */
bool Srs::isNecessaireMatchesCriteres(const ExigenceSrs& e, const std::vector<std::string>& criteres_selectionnes){
    bool trouve = false;
    for(int i=0; i< e.getNecessaire().size() && !trouve; i++){
        if(std::find(criteres_selectionnes.begin(), criteres_selectionnes.end(), e.getNecessaire()[i]) != criteres_selectionnes.end()){
            trouve = true;
        }
    }
    return trouve;
}



/**
 * @brief Vérifie si l'état de développement de l'exigence correspond à l'un des critères sélectionnés.
 *
 * Cette méthode vérifie si l'état de développement de l'objet ExigenceSrs (développé ou non développé)
 * correspond à l'un des critères présents dans le vecteur "criteres_selectionnes".
 * Si une correspondance est trouvée, la méthode retourne true, sinon false.
 *
 * @param e L'exigence à vérifier.
 * @param criteres_selectionnes Un vecteur de chaînes de caractères représentant les critères sélectionnés.
 *
 * @return true si l'état de développement de l'exigence correspond à l'un des critères sélectionnés, false sinon.
 *
 * @author Malek
 */
bool Srs::isDevMatchesCriteres(const ExigenceSrs& e, const std::vector<std::string>& criteres_selectionnes){
    bool trouve = false;

        std::string rechercher;
        if(e.isDev()){
            rechercher = "Développé";
        }else{
            rechercher = "Non développé";
        }
        if(std::find(criteres_selectionnes.begin(), criteres_selectionnes.end(), rechercher) != criteres_selectionnes.end()){
            trouve = true;
        }

    return trouve;
}





/**
 * @brief Vérifie si l'ID de l'exigence correspond à l'un des radicaux sélectionnés.
 *
 * Cette méthode vérifie si l'ID de l'objet ExigenceSrs commence par l'un des radicaux
 * sélectionnés dans le vecteur "criteres_selectionnes". Si l'ID de l'exigence a un préfixe
 * correspondant à l'un des radicaux, la méthode retourne true. Sinon, elle retourne false.
 *
 * @param e L'exigence à vérifier.
 * @param criteres_selectionnes Un vecteur de chaînes de caractères représentant les radicaux sélectionnés.
 *
 * @return true si l'ID de l'exigence correspond à l'un des radicaux sélectionnés, false sinon.
 *
 * @author Malek
 */
bool Srs::isMatchesRadical(const ExigenceSrs& e, const std::vector<std::string>& criteres_selectionnes){
    bool trouve = false;
    std::vector<std::string> radicaux_coches;
    std::vector<std::string> rtr;
     //extraire les radicaux sélectionnés
    if(this->isExcel() && File::getRadical()!=""){
        for(const std::string& rad : criteres_selectionnes){
            if (Sss::getAttributRadicaux().contains(QString::fromStdString(rad))){
                radicaux_coches.push_back(rad);
            }
        }

    //vérifier si l'id de l'exigence a comme préfixe le radical
    if(!radicaux_coches.empty()){
    std::string id = e.getId();
    size_t pos = id.find_last_of('_');
    if (pos != std::string::npos) {
        std::string radical = id.substr(0, pos);
        if (std::find(radicaux_coches.begin(), radicaux_coches.end(), radical) != radicaux_coches.end()){
            trouve = true;
        }
    }
    }else{
        trouve = false;
    }
}
    return trouve;
}


/**
 * @brief Récupère les identifiants des exigences qui correspondent aux critères sélectionnés.
 *
 * Cette méthode parcourt les exigences associées à l'objet Srs et vérifie, pour chaque exigence,
 * si elle correspond à l'un des critères sélectionnés (cible, nécessaire, développement, radical).
 * Si une exigence correspond à l'un de ces critères, ses identifiants de traçabilité sont ajoutés
 * à la liste résultante.
 *
 * @param criteres_selectionnes Liste des critères sélectionnés sous forme de QStringList.
 *
 * @return Un vecteur de chaînes de caractères représentant les identifiants de traçabilité des exigences
 *         qui correspondent aux critères sélectionnés.
 *
 * @author Malek
 */
std::vector<std::string> Srs::getIdsExigenceMatchesCriteres(const QStringList& criteres_selectionnes)
{
    std::vector<std::string> rtr;
    std::vector<ExigenceSrs> exigences = this->exigences;

    // Conversion de QStringList vers std::vector<std::string>
    std::vector<std::string> criteres_std;
    for (const QString& critere : criteres_selectionnes) {
        criteres_std.push_back(critere.toStdString());
    }



    // Parcours des exigences et filtrage
    for (const ExigenceSrs& e : exigences) {
        if (isCibleMatchesCriteres(e, criteres_std) ||
            isNecessaireMatchesCriteres(e, criteres_std) ||
            isDevMatchesCriteres(e, criteres_std) || isMatchesRadical(e,criteres_std)) {
            for(const std::string& traca : e.getTracabilite()){
                rtr.push_back(traca);
            }
        }
    }

    return rtr;
}
/**
 * @brief Récupère les identifiants des exigences SRS qui correspondent à au moins un des critères sélectionnés.
 *
 * Cette fonction parcourt toutes les exigences du SRS et sélectionne celles qui correspondent
 * à l’un des critères donnés selon plusieurs types de correspondance :
 * - correspondance avec la cible ("isCibleMatchesCriteres")
 * - correspondance avec la nécessité ("isNecessaireMatchesCriteres")
 * - correspondance avec le développement ("isDevMatchesCriteres")
 * - correspondance avec un radical commun ("isMatchesRadical")
 *
 * @param criteres_selectionnes Une liste de critères sélectionnés sous forme de "QStringList".
 * Chaque critère sera converti en "std::string" pour la comparaison.
 *
 * @return std::vector<std::string> Un vecteur contenant les identifiants ("id") des exigences qui correspondent
 * à au moins un des critères donnés.
 */
std::vector<std::string> Srs::getIdsExigenceMatchesCriteresWithSdd(const QStringList &criteres_selectionnes)
{
    std::vector<std::string> rtr;
    std::vector<ExigenceSrs> exigences = this->exigences;

    // Conversion de QStringList vers std::vector<std::string>
    std::vector<std::string> criteres_std;
    for (const QString& critere : criteres_selectionnes) {
        criteres_std.push_back(critere.toStdString());
    }



    // Parcours des exigences et filtrage
    for (const ExigenceSrs& e : exigences) {
        if (isCibleMatchesCriteres(e, criteres_std) ||
            isNecessaireMatchesCriteres(e, criteres_std) ||
            isDevMatchesCriteres(e, criteres_std) || isMatchesRadical(e,criteres_std)) {
            rtr.push_back(e.getId());
        }
    }

    return rtr;
}



/**
 * @brief Extrait et ajoute les radicaux à la liste des filtres si nécessaire.
 *
 * Cette méthode vérifie si le fichier actuel est un fichier Excel et si un radical est défini.
 * Elle parcourt ensuite les exigences et extrait le radical de l'ID de chaque exigence. Si le radical
 * n'est pas déjà présent dans la liste des filtres et s'il correspond à une expression régulière,
 * il est ajouté à la liste des filtres.
 *
 * @author Malek
 */
void Srs::getRadicaux()
{
    if(this->isExcel() && File::getRadical()!="" ){
        QString radic;
        QRegularExpression regex(File::getRadical());


        for (const ExigenceSrs& ex : exigences) {
            std::string id = ex.getId();
            size_t pos = id.find('_');
            if (pos != std::string::npos) {
                radic = QString::fromStdString(id.substr(0, pos));
            }
        }
        if(!filtres.contains(radic) && regex.match(radic).hasMatch()){
            filtres.append(radic);
        }
    }
}



/**
 * @brief Ajoute un filtre à la liste des filtres.
 *
 * Cette méthode ajoute le filtre spécifié à la liste des filtres de la classe Srs.
 *
 * @param filtre Le filtre à ajouter, sous forme de chaîne de caractères (QString).
 *
 * @author Malek
 */
void Srs::addFiltres(QString filtre)
{
    Srs::filtres.append(filtre);
}



/**
 * @brief Convertit les identifiants des exigences en une chaîne QString.
 *
 * Cette méthode parcourt les exigences associées à l'objet Srs et génère une chaîne de caractères
 * contenant les identifiants de toutes les exigences. Chaque identifiant est séparé par un saut de ligne.
 *
 * @return Une chaîne QString contenant les identifiants des exigences.
 *
 * @author Malek
 */
QString Srs::toQStringExigence()
{
    QString rtr ="";
    for(const ExigenceSrs &e : exigences){
        rtr = rtr+"\n"+QString::fromStdString(e.getId());
    }
    return rtr;
}

/**
 * @brief Extrait et ajoute les critères de filtres à la liste des filtres.
 *
 * Cette méthode parcourt toutes les exigences et, pour chaque exigence, elle extrait les critères
 * associés à la cible, à la nécessité, et au développement. Si ces critères ne sont pas déjà présents
 * dans la liste des filtres, ils sont ajoutés. Les critères incluent les valeurs de la cible, de la nécessité
 * et l'état de développement ("Développé" ou "Non développé").
 *
 * @author Malek
 */
void Srs::getCriteres()
{

    for(const ExigenceSrs& e : this->exigences){
        if(e.hasCible()){
            for(std::string& e : e.getCible()){
                QString qe = QString::fromStdString(e);
                if(!Srs::filtres.contains(qe)){
                    Srs::filtres.append(qe);
                }
            }
        }

        if(e.hasNecessaire()){
            for(std::string& e : e.getNecessaire()){
                QString qe = QString::fromStdString(e);
                if(!Srs::filtres.contains(qe)){
                    Srs::filtres.append(qe);
                }
            }
        }

        if(e.hasNecessaire()){
            for(std::string& e : e.getNecessaire()){
                QString qe = QString::fromStdString(e);
                if(!Srs::filtres.contains(qe)){
                    Srs::filtres.append(qe);
                }
            }
        }

        if(e.isDev()){
            if(!Srs::filtres.contains("Développé")){
                Srs::filtres.append("Développé");
            }
        }else{

            if(!filtres.contains("Non développé")){
                Srs::filtres.append("Non développé");
            }
        }


    }


}


/**
 * @brief Extrait les exigences depuis un fichier, selon le format du fichier (Word, Excel, CSV).
 *
 * Cette méthode extrait les exigences à partir de différents types de fichiers :
 * - Pour un fichier Word : elle parcourt le fichier XML associé au document Word et récupère les exigences en fonction du style défini.
 * - Pour un fichier Excel : elle utilise une fonction d'extraction spécifique pour récupérer les exigences.
 * - Pour un fichier CSV : elle utilise une fonction d'extraction spécifique pour récupérer les exigences.
 *
 * Les exigences extraites sont ensuite ajoutées à la liste des exigences de l'objet Srs.
 *
 * @author Malek
 */
void Srs::extractExigences(){
    if(this->isWord()){
    std::vector<XmlParserUtils::Exigence_Srs> exigences_vect;
    std::string filtres ;
    XmlParserUtils::Exigence_Srs exigences;

    std::string xmlFolder = FileUtils::ExtractXmlFolder(this->getPath());

    std::string xml_doc_file = xmlFolder + "/word/document.xml";
    pugi::xml_document doc;
    std::string Exigence; //pour enregistrer la chaine de caractère de l'exigence.
    if(!doc.load_file(xml_doc_file.c_str())){
        exit(EXIT_FAILURE);
    }
    for(pugi::xml_node paragraphe : doc.child("w:document").child("w:body").children("w:p")){ //1e boucle permet de parcourir tout les paragraphes
        pugi::xml_node pProperties = paragraphe.child("w:pPr");
        if(pProperties){
            if(pProperties.child("w:pStyle").attribute("w:val").value() !=Srs::style.getId()){ //accéder à la balise pStyle pour verifier le StyleId
                continue; //si different continue
            }else{

                Exigence = "";
                for(pugi::xml_node r : paragraphe.children("w:r")){
                    for(pugi::xml_node texte : r.child("w:t")){
                        Exigence = Exigence + texte.text().get(); //concatainer les differents morceaux du paragraphe
                    }
                }

                exigences = XmlParserUtils::Exigence_Srs();
                exigences.liste_exigences = XmlParserUtils::nettoyage_exigence_srs(Exigence);//affecter au champ liste_exigence la liste des exigences extraites
                paragraphe = paragraphe.next_sibling("w:p");

                XmlParserUtils::Check_filtres(paragraphe, exigences);
                for(std::string& e : exigences.liste_exigences){

                    this->addExigence(ExigenceSrs(e, exigences.cible, exigences.Necessaire, exigences.dev, exigences.tracabilite));
                }


            }
        }
    }
    FileUtils::delete_extra(xmlFolder);
    }else if(this->isExcel()){
        std::vector<std::string> vect = XmlParserUtils::ExtractExigenceExcel(this->getPath());
        for(const std::string& s : vect){
            std::vector<std::string> traca;
            traca.clear();
            traca.push_back(s);
            this->addExigence(ExigenceSrs(s,false, traca));
        }
    }else if(this->isCsv()){
        std::vector<std::string> vect = XmlParserUtils::extractFromCsv(this->getPath());
        for(const std::string& s : vect){
            std::vector<std::string> traca;
            traca.clear();
            traca.push_back(s);
            this->addExigence(ExigenceSrs(s,false, traca));
        }
    }


}






