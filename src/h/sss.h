#ifndef SSS_H
#define SSS_H
#include "stylefile.h"
#include "exigence.h"
#include "file.h"
#include <vector>
#include "srs.h"
#include <QVector>

class Sss : public File
{
private:
    static StyleFile style;
    std::vector<Exigence> exigences;
    QVector<Srs*> fils;
    static QStringList radicaux;

public:
    Sss();
    Sss(std::string path);
    QVector<Srs*> getFils();
    void setFils(QVector<Srs*> fils);
    static void setStyle(StyleFile style);
    std::vector<Exigence> getExigence() const;
    void addExigence(Exigence e);
    void extractExigences();
    std::vector<StyleFile> extractStyles() const;
    int totalExigences() const;
    void addFils(Srs* srs);
    static QStringList getAttributRadicaux();
    std::vector<std::string> getIdsExigence(const QStringList& liste);
    static void reinitialiserRadicaux();
    void getRadicaux();
    QString toQStringExigence();

};

#endif // SSS_H
