#ifndef FENETRESTATISTIQUES_H
#define FENETRESTATISTIQUES_H
#include <QWidget>
#include <QGraphicsScene>
#include <vector>
class FenetreStatistiques {
public:
    static void afficherHistogramme(QWidget* conteneur, const std::vector<double>& listeTaux);
private:
    static void initialiserTranches(const std::vector<double>& listeTaux, int tranches[11]);
    static void dessinerAxes(QGraphicsScene* scene, int origineX, int origineY, int valeurMaximale, int hauteurParGraduation, int largeurTotale);
    static void ajouterTitresAxes(QGraphicsScene* scene, int origineX, int origineY, int largeurTotale);
    static void ajouterBarres(QGraphicsScene* scene, const int tranches[11], const QStringList& etiquettesTranches, int origineX, int origineY, int largeurBarre, int espacementBarres, int hauteurMaximaleBarre, int valeurMaximale);
    static void afficherVue(QWidget* conteneur, QGraphicsScene* scene, int largeurTotale, int hauteurMaximaleBarre);
};
#endif // FENETRESTATISTIQUES_H
