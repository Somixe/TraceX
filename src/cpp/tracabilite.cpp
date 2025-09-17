#include <algorithm>
#include <vector>
#include <string>
#include <list>
#include <set>
#include "tracabilite.h"

using namespace std;

/**
 * @brief Calcul du taux de traçabilité entre un fichier SSS et un fichier SRS
 * @param exigences_pere exigences du SSS
 * @param exigences_fils exigences du SRS
 * @return int pourcentage (sur 100) du taux de traçabilité
 * 
 */
int Tracabilite::taux_traca_sss_srs(std::vector<Exigence> exigences_pere, std::vector<ExigenceSrs> exigences_fils){
    int total = static_cast<int> (exigences_pere.size());

    std::set<std::string> set_tracabilites;

    for (const ExigenceSrs& e : exigences_fils) {
        for (const std::string& id : e.getTracabilite()) {
            set_tracabilites.insert(id);  // Les doublons sont ignorés automatiquement
        }
    }

    std::vector<std::string> toutes_tracabilites(set_tracabilites.begin(), set_tracabilites.end());


    double nb = 0;
    if(total!=0){
        for(const std::string& traca : toutes_tracabilites){
            bool trouve = false;
            for(int i=0; i<exigences_pere.size() && !trouve; i++){
                if(traca==exigences_pere[i].getId()){
                    trouve = true;
                    nb++;
                }
            }
        }
    }else{
        total=1;
    }
    return (nb/total)*100;
}

/**
 * @brief Calcul du taux de traçabilité entre un fichier SRS et un fichier SDD
 * @param exigences_pere exigences du SRS
 * @param exigences_fils exigences du SDD
 * @return int pourcentage (sur 100) du taux de traçabilité
 * 
 */
int Tracabilite::taux_traca_srs_sdd(std::vector<ExigenceSrs> exigences_pere, std::vector<Exigence> exigences_fils){
    int total = static_cast<int> (exigences_pere.size());


    double nb = 0;
    if(total!=0){
        for(const Exigence &e : exigences_fils){
            bool trouve = false;
            for(int i=0; i<total && !trouve; i++){

                if(e.getId()==exigences_pere[i].getId()){
                    trouve = true;
                    nb++;

                }
            }
        }
    }else{
        total = 1;
    }
    return (nb/total)*100;
}

/**
 * @brief Calcule le taux de traçabilité entre deux ensembles d'identifiants d'exigences.
 *
 * @param pere Vecteur contenant les identifiants des exigences "père".
 * @param fils Vecteur contenant les identifiants des exigences "fils".
 * @return float Pourcentage d’exigences fils qui sont tracées vers les exigences père.
 *
 */
float Tracabilite::taux_traca(const std::vector<std::string> pere, const std::vector<std::string>& fils){
    int total = static_cast<int> (pere.size());
    double nb = 0;
    if(total!=0){
    for(const std::string &idFils : fils){
        bool trouve = false;
        for(int i=0; i< pere.size() && !trouve; i++){
            if(idFils ==pere[i]){
                trouve = true;
                nb++;
            }
        }
    }
    }else{
        total = 1;
    }

    return (nb/total)*100;
}
