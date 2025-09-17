#include "xmlparserutils.h"
#include "FileUtils.h"
#include "exigencesrs.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <QColor>
#include <QString>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <QCheckBox>
#include <QLabel>
#include <QWidget>
#include <QHBoxLayout>
#include <QListWidgetItem>
#include <QString>
#include "mainwindow.h"
#include <QProgressDialog>
#include <QApplication>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QStackedWidget>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>
#include <QElapsedTimer>
#include "style.h"



/**
 * @brief Cette fonction analyse un paragraphe XML pour extraire et filtrer des informations relatives aux exigences, telles que les cibles, les nécessités et le développement (les critères de filtrage).
 *
 * La fonction parcourt un noeud XML contenant des balises "w:r" et "w:t", qui sont des éléments d'un document XML Word (DOCX).
 * Elle concatène le texte de ces balises et analyse les lignes de texte pour extraire des informations en fonction des mots-clés tels que "Cible", "Nécessaire à", et "Développé".
 * En fonction des données extraites, elle met à jour un objet "Exigence_Srs" pour inclure les valeurs correspondantes dans les attributs appropriés.
 *
 * @param[in,out] paragraphe Le noeud XML à analyser. Cette fonction modifie la structure XML en se déplaçant à travers ses frères.
 * @param[in,out] exigences L'objet "Exigence_Srs" qui contient les données extraites. Il est mis à jour avec les informations collectées à partir du texte XML.
 *
 * @note La fonction prend en compte des caractères d'espacement et les caractères spéciaux (comme le "\xC2") pour nettoyer les données extraites.
 *       Elle s'arrête lorsqu'un délimiteur "#" est trouvé.
 *
 *@author malek
 */
void XmlParserUtils::Check_filtres(pugi::xml_node& paragraphe, Exigence_Srs& exigences){
    std::string ligne = "";     //  initialiser ligne pour y stocker la ligne extraite
    bool isDiez = false;        //  le délimiteur #
    std::string key;            //  mot clé de chaque ligne qui permet de filtrer
    std::string element;        //  stocker l'information relative à chaque clé

    size_t pos; //  utiliser pour le nettoyage des lignes
    for(pugi::xml_node r : paragraphe.children("w:r")){ //  1e boucle permet de parcourir les balises w:r qui contiennent le texte ecrit (il pourrait y avoir plusieurs w:r pour un meme paragraphe ==> plusieurs texte)
        for(pugi::xml_node texte : r.child("w:t")){ //  parcourir les balises w:t pour recuperer le texte notamment l'exigence
            ligne = ligne + texte.text().get(); //  concatainer les differents morceau du paragraphe
        }
    }
    if(ligne == "#"){
        isDiez=true;
    }

    while(paragraphe && !isDiez){
        pos = ligne.find_first_of(":");
        if(pos != std::string::npos){
            key = ligne.substr(0,pos);      //nettoyer la ligne en enlevant le mot clé pour n'extraire que les données significatives
            key = key.erase(0, key.find_first_not_of(" "));
            key = key.erase(key.find_last_not_of(" ")+1);
            key.erase(std::remove(key.begin(), key.end(),'\xC2'), key.end()); //prendre en compte les cas où l'espace est interprété comme le caractère \xC2
            std ::string key_alter = key.substr(0,key.length()-1);

            if(key == "Cible" || key_alter == "Cible"){ //extraire les données des cibles
                ligne = ligne.substr(pos+1);
                std::stringstream flux(ligne);
                while(std::getline(flux,element,',')){
                    element=element.erase(0,element.find_first_not_of(" "));
                    element = element.erase(element.find_last_not_of(" ")+1);

                    exigences.cible.push_back(element);
                }
            }else if(key == "Nécessaire à" || key_alter =="Nécessaire à"){     //extraire les données définies dans "necessaire"
                ligne = ligne.substr(pos+1);
                std::stringstream flux(ligne);

                while(std::getline(flux,element,',')){
                    element=element.erase(0,element.find_first_not_of(" "));
                    element = element.erase(element.find_last_not_of(" ")+1);
                    exigences.Necessaire.push_back(element);
                }
            }else if(key == "Traçabilité" || key_alter == "Traçabilité"){
                ligne = ligne.substr(pos+1);
                std::stringstream flux(ligne);
                while(std::getline(flux,element,',')){
                    element=element.erase(0,element.find_first_not_of(" "));
                    element = element.erase(element.find_last_not_of(" ")+1);

                    exigences.tracabilite.push_back(element);
                }
            }

        }else {     //extraire l'information sur le developpement
            std::string ligne_alter = ligne.substr(0,ligne.length()-1);
            if(ligne == "Non développé" || ligne_alter == "Non développé"){
                exigences.dev=false;
            }else if(ligne == "Développé"|| ligne_alter == "Développé"){
                exigences.dev=true;
            }
        }
        paragraphe = paragraphe.next_sibling("w:p");
        ligne = "";
        for(pugi::xml_node r : paragraphe.children("w:r")){ //1e boucle permet de parcourir les balises w:r qui contiennent le texte ecrit (il pourrait y avoir plusieurs w:r pour un meme paragraphe ==> plusieurs texte)
            for(pugi::xml_node texte : r.child("w:t")){ //parcourir les balises w:t pour recuperer le texte notamment l'exigence
                ligne = ligne + texte.text().get(); //concatainer les differents morceau du paragraphe
            }
        }
        if(ligne == "#"){   //verifier si le délimiteur est atteint
            isDiez=true;
        }



    }
}


/**
 * @brief Convertit une couleur en format RGB en son nom de couleur correspondant.
 *
 * Cette fonction prend une chaîne de caractères représentant une couleur en format RGB (par exemple "#FF5733"),
 * la convertit en un objet "QColor", puis cherche le nom de cette couleur dans la liste des couleurs.
 * Si la couleur existe dans cette liste, le nom est retourné sous forme de chaîne. Si elle n'est pas trouvée,
 * le code hexadécimal de la couleur est retourné.
 *
 * @param rgb La chaîne représentant la couleur en format RGB (par exemple "#FF5733").
 * @return Le nom de la couleur correspondant à la valeur RGB, ou le code hexadécimal de la couleur si aucun nom n'est trouvé.
 *
 * @author Malek
 */
std::string XmlParserUtils::RGB_to_Color(const std::string &rgb) {
    QString qrgb = QString::fromStdString(rgb); // Conversion std::string -> QString
    QColor color("#" + qrgb);

    if (!color.isValid()) {
        return "";
    }

    QStringList colorNames = QColor::colorNames();
    for (QStringList::const_iterator it = colorNames.constBegin(); it != colorNames.constEnd(); ++it) {
        if (QColor(*it) == color) {
            return it->toStdString(); // Conversion QString -> std::string
        }
    }

    return color.name(QColor::HexRgb).toStdString(); // Retourne le code hex normalisé si pas de nom
}

/**
 * @brief Récupère les identifiants de style utilisés dans un document XML Word.
 *
 * Cette fonction charge un document XML Word spécifié par le chemin "path_doc_xml" et parcourt tous les paragraphes du corps du document.
 * Pour chaque paragraphe, elle recherche la balise "<w:pStyle>" et en extrait l'attribut "w:val", qui représente l'identifiant du style appliqué au paragraphe.
 * Les identifiants de style extraits sont ajoutés à un vecteur, qui est retourné à la fin de la fonction.
 *
 * @param path_doc_xml Le chemin du fichier XML Word à analyser.
 * @return Un vecteur de chaînes contenant les identifiants des styles utilisés dans le document.
 *
 * @note La fonction utilise la bibliothèque pugixml pour le parsing XML.
 *
 * @author Malek
 */
std::vector<std::string> XmlParserUtils::get_used_styleIds(const std::string& path_doc_xml){
    std::vector<std::string> v;

    pugi::xml_document doc;
    std::string Exigence; //Chaine de caractere permet de stocker les parties de l'exigence
    if (!doc.load_file(path_doc_xml.c_str())) {//transformer en un tableau de type char

        exit(EXIT_FAILURE);
    }
    for(pugi::xml_node paragraphe : doc.child("w:document").child("w:body").children("w:p")){ //1e boucle permet de parcourir tout les paragraphes
        pugi::xml_node pProperties = paragraphe.child("w:pPr");
        if(pProperties){
            if(pProperties.child("w:pStyle").attribute("w:val")){ //accéder à la balise pStyle pour verifier le StyleId
                v.push_back(pProperties.child("w:pStyle").attribute("w:val").value());
            }

        }
    }
    return v;
}


/**
 * @brief Extrait tous les styles utilisés dans un document Word à partir du fichier XML des styles.
 *
 * Cette fonction analyse le fichier XML "styles.xml" associé au document Word pour en extraire les informations relatives aux styles utilisés dans le document.
 * Pour chaque style utilisé, elle récupère ses caractéristiques telles que l'identifiant, la police, la taille de la police, la couleur, ainsi que les propriétés telles que gras, italique, souligné et ombré.
 * Ces informations sont stockées dans un vecteur de structures "StyleFile" et renvoyées à la fin de la fonction.
 *
 * @param[in] path Le chemin du fichier XML principal du document (utilisé pour extraire le dossier contenant les fichiers associés).
 * @return Un vecteur de structures "StyleFile" représentant les styles extraits du fichier "styles.xml".
 *
 * @note La fonction utilise la bibliothèque pugixml pour le parsing XML et la fonction "get_used_styleIds" pour récupérer les identifiants des styles utilisés.
 *
 * @author Malek
 */
std::vector<StyleFile> XmlParserUtils::extract_all_styles(const std::string& path){
    struct StyleCharacteristics {
        std::string id;
        std::string name;
        std::string police;
        int policesz;
        std::string color;
        bool gras;
        bool italique;
        bool souligne;
        bool shadow;
    };


    std::vector<StyleFile> styles;
    std::string rgb;
    pugi::xml_document doc;
    StyleCharacteristics carac ;
    std::string folder = FileUtils::ExtractXmlFolder(path);
    std::string style_path = folder+"/word/styles.xml";
    std::string doc_xml = folder+"/word/document.xml";
    std::vector<std::string> styleIds = get_used_styleIds(doc_xml);
    if (!doc.load_file(style_path.c_str())) {//transformer en const char

        exit(EXIT_FAILURE);

    }

    for(pugi::xml_node styleBalise : doc.child("w:styles").children("w:style")){
        if(std::string(styleBalise.attribute("w:type").value()) != "paragraph" || styleBalise.attribute("w:default")){
            continue;
        }
        //id du style
        if(std::find(styleIds.begin(), styleIds.end(), styleBalise.attribute("w:styleId").value()) != styleIds.end()){
            carac.id = styleBalise.attribute("w:styleId").value();
            bool exist = false;
            if(styleBalise.child("w:name").attribute("w:val")){
            carac.name = styleBalise.child("w:name").attribute("w:val").value();
            }else{
                carac.name="";
            }
            pugi::xml_node ProprieteBalise = styleBalise.child("w:rPr");
            //Police
            if(!ProprieteBalise.child("w:rFonts")){
                carac.police = "Calibri";
            }else{
                if(ProprieteBalise.child("w:rFonts").attribute("w:ascii")){
                    carac.police = ProprieteBalise.child("w:rFonts").attribute("w:ascii").value();
                }else if(ProprieteBalise.child("w:rFonts").attribute("w:cstheme")){
                    carac.police = ProprieteBalise.child("w:rFonts").attribute("w:cstheme").value();
                }
            }

            //police size
            if(ProprieteBalise.child("w:sz")){
                int sz = ProprieteBalise.child("w:sz").attribute("w:val").as_int();
                sz = sz/2;
                carac.policesz = sz;
            }else if(ProprieteBalise.child("w:szCs")){
                int sz = ProprieteBalise.child("w:szCs").attribute("w:val").as_int();
                sz = sz/2;
                carac.policesz = sz;
            }else if(!ProprieteBalise.child("w:sz") && !ProprieteBalise.child("w:szCs")){
                carac.policesz = 11;
            }

            //couleur
            if(!ProprieteBalise.child("w:color")){
                carac.color= "Noire";
            }else{

                rgb = ProprieteBalise.child("w:color").attribute("w:val").value();
                carac.color = XmlParserUtils::RGB_to_Color(rgb);
            }

            //gras
            if(!ProprieteBalise.child("w:b")){
                carac.gras=false ;
            }else{
                carac.gras = true;
            }

            //italique
            if(!ProprieteBalise.child("w:i")){
                carac.italique=false ;
            }else{
                carac.italique = true;
            }

            //shadow
            if(!ProprieteBalise.child("w:shadow")){
                carac.shadow=false ;
            }else{
                carac.shadow = true;
            }

            //souligné
            if(!ProprieteBalise.child("w:u")){
                carac.souligne=false ;
            }else{
                carac.souligne = true;
            }

            styles.push_back(StyleFile(carac.id,carac.name,carac.police,carac.policesz, carac.color, carac.gras, carac.italique,
                                       carac.souligne, carac.shadow));

        }
    }


    FileUtils::delete_extra(folder);

    return styles ;

}


/**
 * @brief Nettoie une ligne d'exigences SRS et extrait chaque exigence sous forme de liste.
 *
 * Cette fonction prend une ligne de texte représentant une ou plusieurs exigences SRS,
 * supprime le préfixe avant le premier caractère ":", puis extrait chaque exigence
 * séparée par des virgules. Elle supprime également les espaces en début et fin
 * de chaque exigence avant de l'ajouter à la liste retournée.
 *
 * Exemple d'entrée : "ID: EX1, EX2, EX3"
 * Résultat : {"EX1", "EX2", "EX3"}
 *
 * @param line_exigence_srs La ligne brute contenant les exigences SRS.
 * @return std::list<std::string> Une liste contenant chaque exigence nettoyée.
 *
 * @author Malek
 */
std::list<std::string> XmlParserUtils::nettoyage_exigence_srs(const std::string& line_exigence_srs){
    std::string chaine_copie = line_exigence_srs;   //  créer une copie de la chaine pour pouvoir la manipuler
    size_t pos = chaine_copie.find_first_of(":");   //  recupérer la position du premier ":"
    if(pos!= std::string::npos){
        chaine_copie = chaine_copie.substr(pos + 1);
    }
    std::stringstream flux(chaine_copie);   //  manipuler la chaine comme étant un flux pour faciliter le nettoyage
    std::string exigence ;
    std::list<std::string> exigences;
    //  recupérer exigence par exigence et les stocker dans une list
    while(std::getline(flux, exigence, ',')){
        exigence=exigence.erase(0,exigence.find_first_not_of(" "));
        exigence = exigence.erase(exigence.find_last_not_of(" ")+1);
        exigences.push_back(exigence);
    }

    return exigences;


}


/**
 * @brief Extrait les exigences d'un document Excel de type SSS.
 *
 * Cette fonction ouvre un fichier Excel spécifié par le chemin "PathExcelDoc", en extrait les chaînes
 * de texte depuis le fichier "sharedStrings.xml" généré par Excel dans le dossier temporaire décompressé,
 * et retourne la liste des exigences trouvées.
 *
 * Elle utilise la bibliothèque PugiXML pour analyser le contenu XML, et une fonction auxiliaire
 * "FileUtils::ExtractXmlFolder()" pour décompresser temporairement le fichier Excel (ZIP).
 * Une fois les données extraites, les fichiers temporaires sont supprimés par "FileUtils::delete_extra()".
 *
 * @param PathExcelDoc Le chemin vers le fichier Excel (.xlsx) à analyser.
 * @return std::vector<std::string> Un vecteur contenant toutes les exigences extraites.
 *
 * @author Malek
 */
std::vector<std::string> XmlParserUtils::ExtractExigenceExcel(const std::string& PathExcelDoc ){
    std::vector<std::string> vect_exigence;
    std::string XmlFolder = FileUtils::ExtractXmlFolder(PathExcelDoc);
    std::string contenueCell = XmlFolder+"/xl/sharedStrings.xml";
    std::string Exigence;
    pugi::xml_document doc;

    if(!doc.load_file(contenueCell.c_str())){
        std::cerr << "Erreur lors de la lecture du fichier XML." << std::endl;
    }
    //  boucle permettant de parcourir tous les cellules afin d'extraire
    for(pugi::xml_node siBalise : doc.child("sst").children("si")){
        pugi::xml_node texte = siBalise.child("t");
        Exigence = "";
        Exigence = Exigence + texte.text().get();
        vect_exigence.push_back(Exigence);
    }

    FileUtils::delete_extra(XmlFolder);//  supprimer les dossiers extra qu'on a créer
    return vect_exigence;
}


/**
 * @brief Recherche et extrait les exigences dans un document SSS Word en fonction d'un style utilisateur.
 *
 * Cette fonction ouvre un fichier ".docx" (au format Word), extrait son contenu XML,
 * puis parcourt chaque paragraphe pour détecter ceux ayant le style spécifié par l'utilisateur.
 * Si le style correspond, le texte du paragraphe est considéré comme une exigence et est ajouté à la liste.
 *
 * @param path Le chemin vers le fichier Word (.docx) contenant les exigences.
 * @param userStyle Le style (ID de style) défini par l'utilisateur pour identifier les exigences.
 * @return std::vector<std::string> Un vecteur contenant les exigences extraites du fichier Word.
 *
 * @note Le fichier ".docx" est traité comme une archive ZIP. Le contenu est extrait
 * temporairement pour accéder au fichier "document.xml".
 *
 * @author Malek
 */
std::vector<std::string> XmlParserUtils::Search_Sss_Exigence(const std::string& path,const StyleFile& userStyle){
    std::vector<std::string> vect_exigence;

    std::string xmlFolder = FileUtils::ExtractXmlFolder(path);

    std::string xml_doc_file = xmlFolder + "/word/document.xml";
    pugi::xml_document doc;
    std::string Exigence; //  Chaine de caractere permet de stocker les parties de l'exigence
    if (!doc.load_file(xml_doc_file.c_str())) {//  transformer en un tableau de type char

        exit(EXIT_FAILURE);
    }

    for(pugi::xml_node paragraphe : doc.child("w:document").child("w:body").children("w:p")){ //  1e boucle permet de parcourir tout les paragraphes
        pugi::xml_node pProperties = paragraphe.child("w:pPr");
        if(pProperties){
            if(pProperties.child("w:pStyle").attribute("w:val").value() != userStyle.getId()){ //  accéder à la balise pStyle pour verifier le StyleId
                continue; //  si different continue
            }else{
                Exigence = ""; //initialiser la chaine à "" pour former l'exigence
                for(pugi::xml_node r : paragraphe.children("w:r")){ //  1e boucle permet de parcourir les balises w:r qui contiennent le texte ecrit (il pourrait y avoir plusieurs w:r pour un meme paragraphe ==> plusieurs texte)
                    for(pugi::xml_node texte : r.child("w:t")){ //  parcourir les balises w:t pour recuperer le texte notamment l'exigence
                        Exigence = Exigence + texte.text().get(); //  concatainer les differents morceau du paragraphe
                    }
                }
                vect_exigence.push_back(Exigence);
            }
        }
    }

    FileUtils::delete_extra(xmlFolder);


    return vect_exigence;
}

/**
 * @brief Extrait les exigences à partir d'un fichier CSV.
 *
 * Cette fonction lit un fichier CSV ligne par ligne, supprime les guillemets (""") de chaque ligne,
 * puis découpe la ligne en éléments en utilisant ";" comme séparateur. Chaque élément est ajouté
 * à un vecteur de chaînes représentant les exigences.
 *
 * @param path Le chemin vers le fichier CSV à analyser.
 * @return std::vector<std::string> Un vecteur contenant les exigences extraites.
 *
 * @note Cette fonction suppose que les exigences sont séparées par des points-virgules (";")
 * et qu'elles peuvent être entourées de guillemets (qui seront supprimés).
 *
 * @author Malek
 */
std::vector<std::string> XmlParserUtils::extractFromCsv(const std::string& path){
    std::fstream file(path, std::ios::in);
    std::string ligne;
    std::vector<std::string> v;
    while(getline(file,ligne)){
        ligne.erase(std::remove(ligne.begin(),ligne.end(),'\"'), ligne.end());
        std::stringstream s(ligne);
        std::string exigence;
        while(getline(s, exigence, ';')){
            v.push_back(exigence);
        }
    }
    return v;
}

/**
 * @brief Extrait les exigences d’un fichier SSS, quel que soit son format (.docx, .xlsx, .csv).
 *
 * Cette fonction détecte automatiquement le type de fichier (Word, Excel ou CSV) en se basant sur son extension,
 * puis appelle la fonction d'extraction appropriée.
 *
 * @param path Le chemin vers le fichier contenant les exigences.
 * @param userStyle Le style à utiliser dans le cas d'un document Word (.docx/.doc).
 * @return std::vector<std::string> Un vecteur contenant les exigences extraites.
 *
 * @note Cette fonction agit comme un point d'entrée unique pour l’extraction d’exigences
 * à partir de différents formats de fichiers.
 *
 * @author Malek
 */
std::vector<std::string> XmlParserUtils::extract_exigence_sss(const std::string& path, const StyleFile& userStyle){
    std::vector<std::string> v;
    std::filesystem::path p = path;
    std::string extension = p.extension().string();
    if(extension == ".docx" || extension == ".doc"){
        v = XmlParserUtils::Search_Sss_Exigence(path, userStyle);
    }else if(extension == ".xlsx" || extension == ".xls"){
        v = XmlParserUtils::ExtractExigenceExcel(path);
    }else if(extension == ".csv"){
        v= XmlParserUtils::extractFromCsv(path);
    }
    return v;
}







/**
 * @brief Ajoute un style à une QListWidget sous forme d’un item contenant une case à cocher et un label.
 *
 * Cette fonction crée dynamiquement un widget personnalisé avec :
 * - une QCheckBox affichant le nom du style,
 * - un QLabel décrivant le style,
 * puis l’ajoute comme nouvel item dans la QListWidget fournie.
 *
 * @param listWidget Pointeur vers la QListWidget où l’item sera ajouté.
 * @param style L’objet StyleFile représentant le style à afficher.
 *
 * @author Malek
 */
void XmlParserUtils::ajouterStyleAListe(QListWidget* listWidget, const StyleFile& style) {
    QWidget *itemWidget = new QWidget();
    QString qstr = "";
    if(style.getName()!=""){
        qstr = QString::fromStdString(style.getName());
    }else{
        qstr = QString::fromStdString(style.getName());
    }
    QCheckBox* checkBox = new QCheckBox(qstr);
    QLabel* label = new QLabel(style.toQString());

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(checkBox);
    layout->addWidget(label);
    itemWidget->setLayout(layout);

    QListWidgetItem *item = new QListWidgetItem();
    item->setSizeHint(itemWidget->sizeHint());
    listWidget->addItem(item);
    listWidget->setItemWidget(item, itemWidget);
}


/**
 * @brief Retourne l'index du premier élément coché dans un QListWidget contenant des QCheckBox.
 *
 * Cette fonction parcourt les éléments du QListWidget et cherche la première case à cocher cochée.
 * Chaque élément du QListWidget doit contenir un QCheckBox en tant que widget associé.
 *
 * @param listWidget Pointeur vers le QListWidget à analyser.
 * @return L'index du premier QCheckBox coché, ou -1 si aucun n'est coché.
 *
 * @author Malek
 */
int XmlParserUtils::getCheckedIndex(QListWidget* listWidget) {

    for (int i = 0; i < listWidget->count(); ++i) {
        QListWidgetItem* item = listWidget->item(i);
        QWidget* widget = listWidget->itemWidget(item);
        if (widget) {
            QCheckBox* checkBox = widget->findChild<QCheckBox*>();
            if (checkBox && checkBox->isChecked()) {
                return i; // Retourne l'index de la case cochée
            }
        }
    }
    return -1; // Aucun élément coché
}

/**
 * @brief Extrait les exigences à partir des fichiers SSS/SRS/SDD en fonction des criteres sélectionnés.
 *
 * Cette fonction est déclenchée après la sélection de criteres de filtrage par l'utilisateur dans l'interface graphique.
 * Elle applique les filtres sélectionnés aux classes Sss, Srs et Sdd, réinitialise les filtres,
 * puis extrait les exigences de manière asynchrone à l'aide de QtConcurrent, tout en affichant une boîte de progression.
 *
 * À la fin de l'extraction, elle déclenche le traitement du graphe dans la fenêtre principale ("MainWindow::Bouton_graphe").
 *
 * @param sss_files Pointeur vers un vecteur de fichiers SSS.
 * @param listWidgetSSS Pointeur vers le QListWidget contenant les styles disponibles pour SSS.
 * @param listWidgetSRS Pointeur vers le QListWidget contenant les styles disponibles pour SRS.
 * @param listWidgetSDD Pointeur vers le QListWidget contenant les styles disponibles pour SDD.
 * @param styles_sss Vecteur contenant les styles extraits du fichier SSS.
 * @param styles_srs Vecteur contenant les styles extraits du fichier SRS.
 * @param styles_sdd Vecteur contenant les styles extraits du fichier SDD.
 * @param mainwindow Pointeur vers la fenêtre principale, utilisé pour déclencher l'affichage du graphe.
 *
 * @author Malek
 */
void XmlParserUtils::extraireExigencesApresSelection(const QVector<Sss*>& sss_files, QListWidget* listWidgetSSS, QListWidget* listWidgetSRS, QListWidget* listWidgetSDD,
                                     const std::vector<StyleFile>& styles_sss, const std::vector<StyleFile>& styles_srs, const std::vector<StyleFile>& styles_sdd, MainWindow *mainwindow) {
    // Créer une boîte de progression esthétique
    QProgressDialog* progress = new QProgressDialog("Requirement extraction in progress...", QString(), 0, 0);
    progress->setWindowModality(Qt::ApplicationModal);
    progress->setCancelButton(nullptr);
    progress->setWindowTitle("Please wait");
    progress->setMinimumDuration(0);
    progress->setRange(0, 0);  // Plage de 0 à 0 pour indiquer une barre indéterminée
    progress->setValue(0);  // Placer la barre à 0
    progress->setStyleSheet(Style::Style_progressBar());
    progress->show();

    QApplication::processEvents(); // Assurer l'affichage immédiat de la boîte de progression

    QElapsedTimer timerTotal, timer;
    timerTotal.start();  // Démarrer le chronomètre global

    // Récupérer les indices cochés et appliquer les styles
    timer.start();
    listWidgetSSS->setFocus();
    int selectedIndexSSS = getCheckedIndex(listWidgetSSS);
    listWidgetSRS->setFocus();
    int selectedIndexSRS = getCheckedIndex(listWidgetSRS);
    listWidgetSDD->setFocus();
    int selectedIndexSDD = getCheckedIndex(listWidgetSDD);


    timer.start();
    if (selectedIndexSSS != -1) {
        Sss::setStyle(styles_sss.at(selectedIndexSSS));
    }
    if (selectedIndexSRS != -1) {
        Srs::setStyle(styles_srs.at(selectedIndexSRS));
    }
    if (selectedIndexSDD != -1) {
        Sdd::setStyle(styles_sdd.at(selectedIndexSDD));
    }

    Srs::reinitialiserFiltres();
    Sss::reinitialiserRadicaux();
    // Créer un thread pour l'extraction des exigences
    QtConcurrent::run([=]() {
        for (Sss* file : sss_files) {
            progress->setLabelText(QString("Requirement extraction in progress..."));

            // Extraction des exigences
            file->extractExigences();
            file->getRadicaux();

            for (Srs* srsFile : file->getFils()) {
                srsFile->extractExigences();
                if(srsFile->isWord()){
                    srsFile->getCriteres();
                }
                if (srsFile->hasFils()) {
                    srsFile->getFils()->extractExigences();
                }
            }

            // Attendre un peu avant de mettre à jour la barre (pour ne pas bloquer l'interface)
            QThread::msleep(50);  // Cette pause permet à l'interface de se mettre à jour entre chaque fichier
        }

        // Fermer la boîte de progression une fois l'extraction terminée
        QMetaObject::invokeMethod(progress, "close", Qt::QueuedConnection);
        QMetaObject::invokeMethod(mainwindow, "Bouton_graphe", Qt::QueuedConnection);

    });


}



/**
 * @brief Remplit dynamiquement un QFrame avec une liste de critères sous forme de cases à cocher (QCheckBox).
 *
 * Cette fonction remplace l'ancien layout du QFrame donné par un nouveau contenant une QListWidget.
 * Chaque élément de la QStringList passée est ajouté sous forme de QCheckBox dans la liste.
 * Une connexion est faite entre chaque QCheckBox et un callback fourni pour réagir aux changements d'état.
 *
 * @param frame Pointeur vers le QFrame à remplir. S'il contient déjà un layout, celui-ci est supprimé.
 * @param liste_criteres Liste de critères à afficher sous forme de QCheckBox.
 * @param receiver Pointeur vers l'objet receveur pour les connexions de signaux/slots.
 * @param updateCallback Fonction appelée à chaque fois qu'une case est cochée/décochée.
 *
 * @author Malek
 */
void XmlParserUtils::remplirCriteres(QFrame* frame, const QStringList& liste_criteres, QObject* receiver, std::function<void()> updateCallback) {
    if (!frame) return;

    // Supprimer l'ancien layout
    QLayout* ancienLayout = frame->layout();
    if (ancienLayout) {
        QLayoutItem* item;
        while ((item = ancienLayout->takeAt(0)) != nullptr) {
            if (item->widget()) delete item->widget();
            delete item;
        }
        delete ancienLayout;
    }

    QVBoxLayout* layout = new QVBoxLayout(frame);

    if (liste_criteres.isEmpty()) {
        QLabel* labelVide = new QLabel("<<vide>>");
        layout->addWidget(labelVide);
    } else {
        QListWidget* listWidget = new QListWidget();
        listWidget->setSpacing(20);
        listWidget->setStyleSheet("border:none");

        for (const QString& critere : liste_criteres) {
            QListWidgetItem* item = new QListWidgetItem(listWidget);
            QCheckBox* checkBox = new QCheckBox(critere);
            checkBox->setStyleSheet(Style::Style_CheckBox_Critere_Style());
            item->setSizeHint(checkBox->sizeHint());
            listWidget->addItem(item);
            listWidget->setItemWidget(item, checkBox);

            // Connexion avec une lambda qui appelle le callback
            QObject::connect(checkBox, &QCheckBox::stateChanged, receiver, [=](int){ updateCallback(); });
        }

        layout->addWidget(listWidget);
    }

    frame->setLayout(layout);
}

/**
 * @brief Récupère la liste des critères sélectionnés (cases cochées) dans les QListWidget.
 *
 * Cette fonction parcourt récursivement tous les QListWidget présents dans le QFrame donné en paramètre,
 * et extrait les textes des QCheckBox qui sont cochées. Elle retourne la liste de ces textes comme une QStringList.
 *
 * @param frame Pointeur vers le QFrame contenant plusieurs Widget.
 * @return QStringList contenant les textes de toutes les QCheckBox cochées trouvées dans les QListWidget.
 *
 * @author Malek
 */
QStringList XmlParserUtils::getCriteresCoches(QFrame* frame) {
    QStringList criteresCoches;

    // On parcourt tous les QListWidget présents dans le frame
    QList<QListWidget*> listWidgets = frame->findChildren<QListWidget*>();
    for (QListWidget* listWidget : listWidgets) {
        for (int i = 0; i < listWidget->count(); ++i) {
            QListWidgetItem* item = listWidget->item(i);
            QWidget* widget = listWidget->itemWidget(item);
            QCheckBox* checkBox = qobject_cast<QCheckBox*>(widget);
            if (checkBox && checkBox->isChecked()) {
                criteresCoches << checkBox->text();
            }
        }
    }

    return criteresCoches;
}

/**
 * @brief Affiche les styles détectés dans les documents SSS, SRS et SDD dans une boite de dialogue.
 *
 * Cette fonction est utilisée pour extraire les styles de formatage à partir des fichiers Word (SSS, SRS, SDD),
 * puis les afficher dans une fenêtre contenant trois listes (une pour chaque type de document). À la fin du traitement, l’utilisateur peut valider
 * sa sélection de styles, ce qui déclenche une extraction des exigences correspondantes.
 *
 * @param styleExigence Pointeur vers la QDialog utilisée pour afficher les styles.
 * @param sss_files Vecteur contenant les fichiers SSS avec leurs éventuels liens vers des fichiers SRS et SDD.
 * @param mainwindow Pointeur vers la fenêtre principale de l'application, utilisé pour relancer l'extraction après sélection.
 *
 * @note Les styles sont extraits uniquement des fichiers Word détectés.
 * @note Si aucun style n’est trouvé pour un type de fichier, un message est affiché dans la liste concernée.
 *
 * @author Malek
 */
void XmlParserUtils::afficherStyles(QDialog *styleExigence, const QVector<Sss*>& sss_files, MainWindow* mainwindow) {
    if (sss_files.isEmpty()) {
        QMessageBox::information(nullptr, "Information", "Rien à tracer.");
        return;
    }

    // Créer une boîte de progression esthétique
    QProgressDialog* progress = new QProgressDialog("Loading styles in progres...", QString(), 0, 0);
    progress->setWindowModality(Qt::ApplicationModal);
    progress->setCancelButton(nullptr);
    progress->setWindowTitle("Please wait");
    progress->setMinimumDuration(0);
    progress->setStyleSheet(Style::Style_progressBar());
    progress->setAutoClose(false);  // fermeture manuelle
    progress->show();
    QApplication::processEvents(); // assure que la boîte de progression s'affiche immédiatement

    // Lancer le traitement dans un thread séparé
    QtConcurrent::run([=]() {
        std::string path, pathSrs, pathSdd;
        bool trouveSss = false;
        bool trouveSrs = false;
        bool trouveSdd = false;
        for (Sss* one_file : sss_files) {
            if (!one_file->getFils().isEmpty()) {
                if(!trouveSss && one_file->isWord()){
                    path = one_file->getPath();
                    trouveSss = true;
                }
                int i=0;
                const QVector<Srs*>& fichierSrs = one_file->getFils();
                while(i<fichierSrs.size() && (!trouveSrs || !trouveSdd)){
                    if(!trouveSrs && fichierSrs[i]->isWord()){
                        pathSrs = fichierSrs[i]->getPath();
                        trouveSrs=true;
                    }
                    if(!trouveSdd && fichierSrs[i]->hasFils() && fichierSrs[i]->getFils()->isWord()){
                        pathSdd = fichierSrs[i]->getFils()->getPath();
                        trouveSdd=true;
                    }
                    i++;
                }


            }
        }

        auto styles_sss = path.empty() ? std::vector<StyleFile>() : XmlParserUtils::extract_all_styles(path);
        auto styles_srs = pathSrs.empty() ? std::vector<StyleFile>() : XmlParserUtils::extract_all_styles(pathSrs);
        auto styles_sdd = pathSdd.empty() ? std::vector<StyleFile>() : XmlParserUtils::extract_all_styles(pathSdd);

        // Mise à jour de l’interface dans le thread principal
        QMetaObject::invokeMethod(styleExigence, [=]() {
            QStackedWidget* stackedWidget = styleExigence->findChild<QStackedWidget*>("Styles_stacked");
            QWidget *pageSss = stackedWidget->widget(0);
            QWidget *pageSrs = stackedWidget->widget(1);
            QWidget *pageSdd = stackedWidget->widget(2);

            QListWidget *listWidgetSSS = pageSss->findChild<QFrame *>("frame")->findChild<QFrame*>("frame_3")->findChild<QListWidget *>("style_liste");
            QListWidget *listWidgetSRS = pageSrs->findChild<QFrame *>("frame_4")->findChild<QFrame*>("frame_5")->findChild<QListWidget *>("style_liste_2");
            QListWidget *listWidgetSDD = pageSdd->findChild<QFrame *>("frame_7")->findChild<QFrame*>("frame_8")->findChild<QListWidget *>("style_liste_3");

            listWidgetSSS->clear();
            listWidgetSRS->clear();
            listWidgetSDD->clear();

            if (styles_sss.empty()) {
                listWidgetSSS->addItem("Style not found");
                listWidgetSSS->setEnabled(false);
            } else {
                for (const StyleFile& style : styles_sss)
                    ajouterStyleAListe(listWidgetSSS, style);
                listWidgetSSS->setEnabled(true);
            }

            // Affichage pour SRS
            if (styles_srs.empty()) {
                listWidgetSRS->addItem("Style not found");
                listWidgetSRS->setEnabled(false);
            } else {
                for (const StyleFile& style : styles_srs)
                    ajouterStyleAListe(listWidgetSRS, style);
                listWidgetSRS->setEnabled(true);
            }

            // Affichage pour SDD
            if (styles_sdd.empty()) {
                listWidgetSDD->addItem("Style not found");
                listWidgetSDD->setEnabled(false);
            } else {
                for (const StyleFile& style : styles_sdd)
                    ajouterStyleAListe(listWidgetSDD, style);
                listWidgetSDD->setEnabled(true);
            }
            listWidgetSSS->setSelectionMode(QAbstractItemView::SingleSelection);
            listWidgetSRS->setSelectionMode(QAbstractItemView::SingleSelection);
            listWidgetSDD->setSelectionMode(QAbstractItemView::SingleSelection);

            QPushButton* validerButton = pageSdd->findChild<QFrame *>("frame_7")->findChild<QFrame *>("frame_9")->findChild<QPushButton *>("pushButton_5");
            QObject::connect(validerButton, &QPushButton::clicked, [styleExigence, sss_files, listWidgetSSS, listWidgetSRS, listWidgetSDD, styles_sss, styles_srs, styles_sdd, mainwindow]() {
                styleExigence->close();
                extraireExigencesApresSelection(sss_files, listWidgetSSS, listWidgetSRS, listWidgetSDD, styles_sss, styles_srs, styles_sdd, mainwindow);
            });

            QMetaObject::invokeMethod(progress, "close", Qt::QueuedConnection);
            progress->deleteLater();           // fermer la boîte de progression
            styleExigence->show();       // ensuite afficher la fenêtre
        }, Qt::QueuedConnection);
    });
}



