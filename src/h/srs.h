#ifndef SRS_H
#define SRS_H
#include "file.h"
#include "stylefile.h"
#include <vector>
#include "exigencesrs.h"
#include "sdd.h"
#include <QVector>
class Srs : public File
{
private:
    static StyleFile style;
    static QStringList filtres;
    std::vector<ExigenceSrs> exigences;
    Sdd* fils;
public:
    Srs();
    Srs(const std::string& path);
    static void setStyle(StyleFile style);
    static StyleFile getStyle();
    static QStringList getFiltres();
    void setFils(Sdd* fils);
    Sdd* getFils();
    bool hasFils();
    void addExigence(ExigenceSrs e);
    void static reinitialiserFiltres();
    std::vector<ExigenceSrs> getExigence() const;
    void extractExigences();
    std::vector<StyleFile> extractStyles() const;
    int totalExigences() const;
    void afficherExigence();
    std::vector<std::string> getIdsExigenceMatchesCriteres(const QStringList& criteres_selectionnes );
    std::vector<std::string> getIdsExigenceMatchesCriteresWithSdd(const QStringList& criteres_selectionnes );
    void getCriteres();
    std::vector<std::string> getMatchedCriteresExigences(const QStringList& liste);
    bool isDevMatchesCriteres(const ExigenceSrs& e, const std::vector<std::string>& criteres_selectionnes);
    bool isNecessaireMatchesCriteres(const ExigenceSrs& e, const std::vector<std::string>& criteres_selectionnes);
    bool isCibleMatchesCriteres(const ExigenceSrs& e, const std::vector<std::string>& criteres_selectionnes);
    bool isMatchesRadical(const ExigenceSrs& e, const std::vector<std::string>& criteres_selectionnes);
    void getRadicaux();
    static void addFiltres(QString filtre);
    QString toQStringExigence();
};

#endif // SRS_H
