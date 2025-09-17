#ifndef XMLPARSERUTILS_H
#define XMLPARSERUTILS_H

#include "pugixml-1.15/pugixml-1.15/src/pugixml.hpp"

#include "StyleCharacteristics.h"
#include "exigencesrs.h"
#include <QString>
#include <QListWidget>
#include "mainwindow.h"
#include "stylefile.h"
#include <vector>
#include "srs.h"
#include "style_exigence.h"
#include <functional>
#include <set>


class XmlParserUtils
{
public:
    struct Exigence_Srs {
        std::vector<std::string> cible;
        std::vector<std::string> Necessaire;
        bool dev;
        std::list<std::string> liste_exigences;
        std::vector<std::string> tracabilite;
    };
public :
    // Méthodes statiques (utilitaires)

    static void Check_filtres(pugi::xml_node& paragraphe, Exigence_Srs& exigences); // extrait les filtres

    static std::vector<StyleFile> extract_all_styles(const std::string& path); // extrait tous les styles utilisés dans un fichier
    static std::list<std::string> nettoyage_exigence_srs(const std::string& line_exigence_srs); // nettoie les exigences (private)



    static std::vector<std::string> ExtractExigenceExcel(const std::string& PathExcelDoc); // extrait les exigences d'un fichier excel

    static std::vector<std::string> Search_Sss_Exigence(const std::string& path,const StyleFile& userStyle);

    

    static void afficherStyles(QDialog* styleExigence, const QVector<Sss*>& sss_files, MainWindow* mainwindow); // affiche les style dans une fenetre

    static std::vector<std::string> get_used_styleIds(const std::string& path_doc_xml); // retourne les id styles utilisés


    static std::vector<std::string> extract_exigence_sss(const std::string& path, const StyleFile& userStyle);
    static void ajouterStyleAListe(QListWidget* listWidget, const StyleFile& style);
    static int getCheckedIndex(QListWidget* listWidget);


    static std::vector<std::string> extractFromCsv(const std::string& path);
    static void remplirCriteres(QFrame* frame, const QStringList& liste_criteres, QObject* receiver, std::function<void()> updateCallback);
    static QStringList getCriteresCoches(QFrame* frame);
    static std::string RGB_to_Color(const std::string &rgb);
    static void extraireExigencesApresSelection(const QVector<Sss*>& sss_files, QListWidget* listWidgetSSS, QListWidget* listWidgetSRS, QListWidget* listWidgetSDD,
                                                const std::vector<StyleFile>& styles_sss, const std::vector<StyleFile>& styles_srs, const std::vector<StyleFile>& styles_sdd, MainWindow *mainwindow);

};

#endif // XMLPARSERUTILS_H
