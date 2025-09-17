
#ifndef EXIGENCESRS_H
#define EXIGENCESRS_H
#include "exigence.h"
#include <vector>

class ExigenceSrs : public Exigence
{
private:
    std::vector<std::string> cible;
    std::vector<std::string> tracabilite;
    std::vector<std::string> Necessaire;
    bool dev;

public:
    ExigenceSrs(const std::string& id, const std::vector<std::string>& cible,
                const std::vector<std::string>& Necessaire, bool dev, const std::vector<std::string>& tracabilite);

    ExigenceSrs(const std::string& id,
                const std::vector<std::string>& Necessaire, bool dev, const std::vector<std::string>& tracabilite);

    ExigenceSrs(const std::string& id,
                 bool dev, const std::vector<std::string>& tracabilite);

    ExigenceSrs(const std::string& id,
                bool dev);

    std::vector<std::string> getCible() const;

    std::vector<std::string> getNecessaire() const;

    std::vector<std::string> getTracabilite() const;

    std::vector<std::string> setTracabilite() const;

    bool isDev() const;

    bool hasCible() const;

    bool hasNecessaire() const;

    std::string toString();
};

#endif // EXIGENCESRS_H
