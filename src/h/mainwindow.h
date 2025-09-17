/**
 * @file mainwindow.h
 * @brief Affichage et gestion de l'interface "mainwindow.ui"
 *
 * @details Ce fichier contient la définition de la classe MainWindow, qui gère l'interface graphique,
 * l'importation et l'affichage des fichiers, ainsi que l'affichage des relations sous forme de graphe/statisque/rapport.
 *
 * @author Maxime Huang
 * @version 1.0
 * @date 29/03/2025
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QList>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QStringList>
#include <QGraphicsRectItem>
#include <QHBoxLayout>
#include <QVector>
#include "qtreewidget_custom.h"
#include "qlistwidget_custom.h"
#include "fenetregraphe.h"
#include "sss.h"
#include <QLabel>
#include <QPropertyAnimation>
#include "fenetreexigences.h"
#include "nodeitem.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    // Constructeur et destructeur
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Méthodes publiques pour l'interface et la navigation
    void Ajout_Analyse_bouton();
    void Debug_extraction_fichier();
    void Afficher_fichier_upload();
    void onAnalyseClicked();
    void Reinitialise_bouton();
    void newGraphWindow();
    QPushButton* getAnalyse();
    QVBoxLayout* getNav();
    QVBoxLayout* getConteneurExigenceLayout();
    void resetFichierUpload();
    QStringList& getFichierUpload();
    void ActualiserQSS(QWidget *widget);
    void afficherStats();
    void Affiche_WidgetFichiers_custom();
    void AnimationFonctions();
    void updateGraphWithCriteres();
    void Animation_afficherProchaineLettre(QString texteComplet, QLabel* WidgetTexte);
    void fadeIn_Widget(QWidget* widget, int delai = 0, int duree = 925);




public slots:
    void Bouton_graphe();

private slots:
    // Slots liés aux boutons de l'interface utilisateur
    void on_Home_clicked();
    void on_Help_clicked();
    void on_upload_fichier_clicked();
    void on_Import_clicked();
    void on_Filtrage_fichiers_clicked();
    void Lancer_filtre_style(); // Applique le filtre sur les styles
    void Bouton_nav(QPushButton* bouton, int page);  // Change la couleur du bouton et la page visible
    void on_DeleteAll_clicked();
    void on_BarreLateraleMenu_clicked();
    void afficherExigencesPourNoeud(NodeItem *noeud);
    void on_BoutonTelechargementCSV_clicked();

private:
    // Variables membres pour l'interface
    Ui::MainWindow *ui;
    QPushButton* Analyse = nullptr;
    QPushButton* Statistics = nullptr;

    enum Pages {
        PAGE_HOME = 0,
        PAGE_IMPORT,
        PAGE_HELP,
        PAGE_ANALYSE,
        PAGE_GRAPHE = 0,
        PAGE_STATISTIQUE
    };
    // Variables pour les fichiers et l'analyse
    QStringList Fichier_upload;
    int nb_fichier_upload = 0;
    QVector<Sss*> Fichier_extrait;
    QListWidget_custom* liste_fichiers;
    QTreeWidget_custom* arbre_fichiers;

    // Variables pour la gestion du graphe
    FenetreGraphe *maVue = new FenetreGraphe();
    QGraphicsScene maScene = new QGraphicsScene();

    // Méthode utilitaire
    QString Convertisseur_bit(qint64 bit);

    // Méthode pour extraire tous les liens de traçabilité du graphe
    std::vector<double> extraireTousLesTauxDesLiens();

    //Variables pour l'animation des textes dynamiques
    int i = 0;
    QTimer* timer = nullptr;
    QString texteActuel;
    bool menuOpen = true;

    FenetreExigences *fenetreExigences = nullptr;
    void resizeEvent(QResizeEvent* event) override;


};

#endif // MAINWINDOW_H
