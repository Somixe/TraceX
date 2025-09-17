#ifndef TRACABILITE_H
#define TRACABILITE_H

#include "exigencesrs.h"
#include "exigence.h"

using namespace std;

class Tracabilite {    
    public :
    static int taux_traca_sss_srs(vector<Exigence> exigences_pere, vector<ExigenceSrs> exigences_fils);
    static int taux_traca_srs_sdd(vector<ExigenceSrs> exigences_pere, vector<Exigence> exigences_fils);
    static float taux_traca(const vector<std::string> pere, const std::vector<std::string>& fils);
};

#endif
