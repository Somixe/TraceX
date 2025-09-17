/**
 * @file mainwindow.cpp
 * @brief Cette classe permet l'affichage et gestion de l'interface du fichier "mainwindow.ui"
 *
 * @details Cette classe hérité de QMainWindow, au coeur de l'interface graphique, permet en particulier d'afficher
 * et de gérer l'importation et l'affichage des fichiers, que les relations affichés
 * sous forme de graphe, statistiques et rapport.
 *
 * @author Maxime Huang
 * @version 1.0
 * @date Dernière modification : 29/03/2025
 */
#include <QStringList>

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "style.h"
#include "style_exigence.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QHeaderView>
#include "graphe.h"
#include <QThread>
#include "srs.h"
#include "fenetrestatistiques.h"
#include "xmlparserutils.h"
#include "linkitem.h"
#include <QInputDialog>
#include "file.h"
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include "rapport.h"
#include "rapportligne.h"


/**
 *
 * @brief Le constructeur initialise l'interface centrale créés dans Qt Designer.
 *
 * @author Maxime Huang
 * @param parent   Le widget parent.
 *
 * @date 29/03/2025
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Affiche_WidgetFichiers_custom();
    ui->Contenus->setCurrentIndex(PAGE_HOME);
    AnimationFonctions(); //execute et affiche toutes les fonctions d'animations
    ui->TraceX->setText("<span style='color: white;'>Trace</span><span style='color: rgba(159, 75, 75, 1);'>X</span>");
    ui->TraceX->setStyleSheet("font-size: 19px; font-weight: bold;");

}

/**
 * @brief Le destructeur permet de libérer la mémoire de l'interface utilisateur allouée dynamiquement.
 *
 * @date 20/02/2025
 */
MainWindow::~MainWindow()
{
    delete ui;
}

// ==================================================
//              METHODES GET et SET
// ==================================================

/**
 * @brief Renvoie le layout de la barre de navigation (QHBoxLayout) aux autres classes.
 *
 * @return Retourne le layout de la barre de navigation de "mainwindow.ui".
 *
 * @author Maxime Huang
 * @date 29/03/2025
 */
QVBoxLayout *MainWindow::getNav()
{
    return ui->nav;
}

/**
 * @brief Renvoie le bouton d'analyse (QPushButton) aux autres classes.
 *
 * @return Retourne le bouton "Analyse" de "mainwindow.h".
 *
 * @author Maxime Huang
 * @date 29/03/2025
 */
QPushButton *MainWindow::getAnalyse()
{
    return Analyse;
}

/**
 * @brief Renvoie la liste des fichiers importés (QStringList) aux autres classes.
 *
 * @return Retourne la liste "Fichier_upload".
 *
 * @author Maxime Huang
 * @date 12/04/2025
 */
QStringList& MainWindow::getFichierUpload(){
    return Fichier_upload;
}

// ==================================================
//          SLOTS ET METHODES DE NAVIGATION
// ==================================================

/**
 * @brief Force la réactualisation du style (QSS) appliqué à un widget sans avoir à redémarrer l'application.
 *
 * @param widget (QWidget), widget dont le style doit être actualisé.
 *
 * @author Maxime Huang
 * @date 09/03/2025
 */
void MainWindow::ActualiserQSS(QWidget* widget)
{
    if (widget == Analyse || widget == Statistics) {
        widget->setStyleSheet(Style::Style_Button_analyse());
    }
    if (widget == ui->Home || widget == ui->Help || widget == ui->Import){
        widget->setProperty("color", "white");
        widget->setProperty("background-color","rgba(29, 47, 55,1)");
    }
    widget->style()->unpolish(widget);
    widget->style()->polish(widget);
}


/**
 * @brief Réinitialise la couleur de tous les boutons de navigation.
 *
 * @author Maxime Huang
 * @date 09/03/2025
 */
void MainWindow::Reinitialise_bouton()
{

    ActualiserQSS(ui->Help);
    ActualiserQSS(ui->Import);
    ActualiserQSS(ui->Home);

    if (Analyse != nullptr && Statistics != nullptr){
        ActualiserQSS(Analyse);
        ActualiserQSS(Statistics);
    }
}

/**
 * @brief Change la couleur du bouton rentré en paramètre en bleu, change les autres boutons en blanc et
 * redirige l'utilisateur vers la page concernée.
 *
 * @param bouton (QPushButton), bouton concerné pour le changement de style.
 * @param page (int), l'index du contenu à afficher dans le "QStackedWidget".
 *
 * @author Maxime Huang
 * @date 09/03/2025
 */
void MainWindow::Bouton_nav(QPushButton* bouton, int page){
    Reinitialise_bouton();
    if (bouton == ui->Home || bouton == ui->Help || bouton == ui->Import) {
        bouton->setProperty("color", "color_changed");
        bouton->style()->unpolish(bouton);
        bouton->style()->polish(bouton);
    }
    ui->Contenus->setCurrentIndex(page);
}

/**
 * @brief Ce slot est appelé après avoir cliqué sur le bouton Home. Elle dirige l'utilisateur
 * vers la page "Home".
 *
 * @author Maxime Huang
 * @date 20/02/2025
 */
void MainWindow::on_Home_clicked()
{
    Bouton_nav(ui->Home, PAGE_HOME);
}

/**
 * @brief Ce slot est appelé après avoir cliqué sur le bouton Import. Elle dirige l'utilisateur
 * vers la page "Import".
 *
 * @author Maxime Huang
 * @date 20/02/2025
 */
void MainWindow::on_Import_clicked()
{
    Bouton_nav(ui->Import, PAGE_IMPORT);
}

/**
 * @brief Ce slot est appelé après avoir cliqué sur le bouton Help. Elle dirige l'utilisateur
 * vers la page "Help".
 *
 * @author Maxime Huang
 * @date 20/02/2025
 */
void MainWindow::on_Help_clicked()
{
    Bouton_nav(ui->Help, PAGE_HELP);
}

/**
 * @brief Ajoute le bouton "Analyse" dans la barre de navigation .
 *
 * @author Maxime Huang
 * @date 26/03/2025
 */
void MainWindow::Ajout_Analyse_bouton(){

    if (ui->OptionMenu->count() == 2){
        Analyse = new QPushButton("GRAPH");

        //Ajout du bouton
        ui->OptionMenu->insertWidget(2, Analyse);
        Analyse->setStyleSheet(Style::Style_Button_analyse());
        Analyse->setCursor(Qt::PointingHandCursor);
        onAnalyseClicked();

        //Ajout de l'icon
        QPixmap iconGraphe(":/Icons/images/analyse_icon.png");
        QPixmap scaledGraphe = iconGraphe.scaled(28, 28, Qt::KeepAspectRatio);

        QLabel *iconLabel = new QLabel;
        iconLabel->setPixmap(scaledGraphe);
        iconLabel->setFixedSize(32, 32);
        iconLabel->setStyleSheet("margin-left:8px;margin-bottom:5px;");

        Analyse->setIcon(iconGraphe);

        connect(Analyse, &QPushButton::clicked, this, [=](){
            Bouton_nav(Analyse,PAGE_ANALYSE);
            Analyse->setStyleSheet(Style::Changer_bleu_bouton_nav());
            ui->Stacked_Analyse->setCurrentIndex(PAGE_GRAPHE);
        });

        Statistics = new QPushButton("STATISTICS");

        //Ajout du bouton
        ui->OptionMenu->insertWidget(3, Statistics);
        Statistics->setStyleSheet(Style::Style_Button_analyse());
        Statistics->setCursor(Qt::PointingHandCursor);

        QLabel *iconStat = new QLabel;
        iconStat->setPixmap(scaledGraphe);
        iconStat->setFixedSize(32, 32);
        iconStat->setStyleSheet("margin-left:8px;margin-bottom:5px;");

        Statistics->setIcon(iconGraphe);

        connect(Statistics, &QPushButton::clicked, this, [=](){
            Bouton_nav(Statistics,PAGE_ANALYSE);
            Statistics->setStyleSheet(Style::Changer_bleu_bouton_nav()); // bouton actif en bleu
            ui->Stacked_Analyse->setCurrentIndex(PAGE_STATISTIQUE);

            std::vector<double> listeDesTaux = extraireTousLesTauxDesLiens();
            FenetreStatistiques::afficherHistogramme(ui->widget_2, listeDesTaux);
        });
    }
}

/**
 * @brief Ce méthode dirige l'utilisateur vers la page "Analyse".
 *
 * @author Maxime Huang
 * @date 28/03/2025
 */
void MainWindow::onAnalyseClicked(){
    Bouton_nav(Analyse, PAGE_ANALYSE);
}

// ===================================================================
//      SLOTS ET METHODES DE GESTION/AFFICHAGE DE FICHIERS
// ===================================================================

/**
 * @brief Vide le contenu des fichiers importés
 *
 * @author Maxime Huang
 * @date 14/04/25
 */
void MainWindow::resetFichierUpload()
{
    Fichier_upload.clear();
}

/**
 * @brief Affiche une fenêtre de dialogue pour importer les fichiers.
 *
 * @details Ce slot est appelé après avoir cliqué sur le bouton "upload manually". Il ouvre une boîte
 * de dialogue pour permettre à l'utilisateur de sélectionner un ou plusieurs fichiers
 * avec des formats spécifiques (.docx, .xlsx, .csv), puis appelle la fonction "Afficher_fichier_upload()"
 * pour affiche les fichiers importés dans le tableau.
 *
 * @authors Maxime Huang / Jacques Zheng
 * @date 26/03/2025
 */
void MainWindow::on_upload_fichier_clicked()
{
    resetFichierUpload();
    Fichier_upload = QFileDialog::getOpenFileNames(this, "Gestionnaire de fichiers", QDir::homePath(), "Documents (*.docx *.xlsx *.csv *.doc)");
    if (!Fichier_upload.isEmpty()) {
        Afficher_fichier_upload();
    }
}


/**
 * @brief Affiche sur le tableau les fichiers importés.
 *
 * @details Cette méthode affiche dans le tableau "QListWidget_custom" les fichiers importés
 * (icône du format correspondante, taille, bouton de supression) et actualise le compteur
 * de fichiers téléchargés (nb_fichier_upload)
 *
 * @author Maxime Huang
 * @date 26/03/2025
 */
void MainWindow::Afficher_fichier_upload()
{
    qDebug() << "Affichage des fichiers : " << Fichier_upload;

    nb_fichier_upload += Fichier_upload.count();
    ui->nb_fichier_upload->setText("(" + QString::number(nb_fichier_upload) + ")");

    // Déclaration d'icônes
    static QPixmap docxIcon(":/Icons/images/docx.png");
    static QPixmap xlsxIcon(":/Icons/images/xlsx.png");
    static QPixmap csvIcon(":/Icons/images/csv.png");
    static QPixmap docIcon(":/Icons/images/doc.png");
    static QPixmap deleteIcon(":/Icons/images/delete.png");

    for (int i = 0; i < Fichier_upload.size(); i++) {
        QString chemin = Fichier_upload[i];
        QFileInfo Info_fichier(chemin);
        QString nomFichier = Info_fichier.baseName() + "." + Info_fichier.suffix();
        QLabel* Nom_Fichier = new QLabel(nomFichier);
        QLabel* Taille_fichier = new QLabel(Convertisseur_bit(Info_fichier.size()));
        QLabel* Icone_Fichier = new QLabel();

        if (Info_fichier.suffix() == "docx") {
            Icone_Fichier->setPixmap(docxIcon.scaled(24, 24, Qt::KeepAspectRatio));
        } else if (Info_fichier.suffix() == "xlsx") {
            Icone_Fichier->setPixmap(xlsxIcon.scaled(24, 24, Qt::KeepAspectRatio));
        } else if (Info_fichier.suffix() == "csv") {
            Icone_Fichier->setPixmap(csvIcon.scaled(24, 24, Qt::KeepAspectRatio));
        } else if (Info_fichier.suffix() == "doc") {
            Icone_Fichier->setPixmap(docIcon.scaled(24, 24, Qt::KeepAspectRatio));
        }

        QPushButton* Poubelle = new QPushButton();
        Poubelle->setIcon(QIcon(deleteIcon));
        Poubelle->setIconSize(QSize(20, 20));
        Poubelle->setCursor(Qt::PointingHandCursor);

        QHBoxLayout *layout_horizontal = new QHBoxLayout();
        layout_horizontal->addWidget(Icone_Fichier);
        layout_horizontal->addWidget(Nom_Fichier);
        layout_horizontal->addStretch();
        layout_horizontal->addWidget(Taille_fichier);
        layout_horizontal->addStretch();
        layout_horizontal->addWidget(Poubelle);

        QWidget *conteneur = new QWidget();
        conteneur->setObjectName("conteneur");
        conteneur->setLayout(layout_horizontal);
        conteneur->setToolTip(Fichier_upload[i]); //chemin du fichier


        QListWidgetItem *contenu = new QListWidgetItem();
        contenu->setText(chemin);
        contenu->setTextAlignment(Qt::AlignLeft);
        contenu->setSizeHint(conteneur->sizeHint());

        liste_fichiers->addItem(contenu);
        liste_fichiers->setItemWidget(contenu, conteneur);

        // Slot suppression
        connect(Poubelle, &QPushButton::clicked, this, [=]() {
            int ligne = liste_fichiers->row(contenu);
            if (ligne >= 0) {
                delete liste_fichiers->takeItem(ligne);
                nb_fichier_upload--;
                ui->nb_fichier_upload->setText("(" + QString::number(nb_fichier_upload) + ")");
            }
            delete conteneur;
        });
    }

    liste_fichiers->setSpacing(3);
}


/**
 * @brief Convertit un nombre de bits en une chaîne de caractères
 * représentant sa taille en octets (Ko,Mo ou Go).
 *
 * @param bit, la valeur en bits à convertir (type entier signé de 64 bits).
 *
 * @return Une chaîne de caractères représentant la conversion des bits la plus appropriée (octets, Ko, Mo, Go).
 *
 * @author Maxime Huang
 * @date 06/03/2025
 */
QString MainWindow::Convertisseur_bit(qint64 bit){ // valeur numérique
    QString nb_octet;

    if (bit < 1024){
        nb_octet = QString::number(bit) + " octets";
    }
    else if (bit < 1024 * 1024){
        nb_octet = QString::number(bit / 1024, 'f', 1) + " Ko";
    }
    else if (bit < 1024 * 1024 * 1024){
        nb_octet = QString::number(bit / (1024 * 1024), 'f', 1) + " Mo";
    }
    else if (bit > 1024 * 1024 * 1024){
        nb_octet = QString::number(bit / (1024.0 * 1024 * 1024), 'f', 1) + " Go";
    }
    else{
        nb_octet = "Ne contient pas d'octects";
    }

    return nb_octet;
}

/**
 * @brief Extrait les fichiers importés, les affichent sur la console et ouvre la fenêtre de style.
 *
 * @details Ce slot est appelé après avoir cliqué sur le bouton "filtrer les styles". Il permet de
 * vider la liste des élements (Fichier_extrait), d'extraire les SSS,SRS et SDD depuis l'arbre
 * (QTreeWidget) de manière hiérarchique et de les ajouter dans "Fichier_extrait", d'afficher sur
 * la console les fichiers extraits et d'afficher la fenête de dialogue sur les styles de fichiers Wordx.
 *
 * @author Maxime Huang / Malek Allahoum
 * @date 26/03/2025
 */
void MainWindow::on_Filtrage_fichiers_clicked()
{
    Fichier_extrait.clear();

    int nb_sss = arbre_fichiers->topLevelItemCount();

    //Ajoute dans "Fichiers_extrait", les fichiers rangés de manière arborescent.
    for (int i = 0; i < nb_sss; i++) {
        QTreeWidgetItem* sss_arbre = arbre_fichiers->topLevelItem(i);
        QString sss_chemin = sss_arbre->data(0, Qt::UserRole).toString();
        Sss* sss = new Sss(sss_chemin.toStdString());

        int nb_srs = sss_arbre->childCount();
        for (int j = 0; j < nb_srs; j++) {
            QTreeWidgetItem* srs_arbre = sss_arbre->child(j);
            QString srs_chemin = srs_arbre->data(0, Qt::UserRole).toString();

            Srs* srs = new Srs(srs_chemin.toStdString());
            sss->addFils(srs);

            if (srs_arbre->childCount() > 0) {
                QTreeWidgetItem* sdd_arbre = srs_arbre->child(0);
                QString sdd_chemin = sdd_arbre->data(0, Qt::UserRole).toString();
                Sdd* sdd = new Sdd(sdd_chemin.toStdString());
                srs->setFils(sdd);
            }
        }
        Fichier_extrait.append(sss);
    }

    Lancer_filtre_style();
}

/**
 * @brief Affiche de manière arborescente sur la console, les fichiers de l'arbre de données.
 *
 * @author Maxime Huang
 * @date 26/03/2025
 */
void MainWindow::Debug_extraction_fichier(){

    qDebug() << "\n------------ Vérification des fichiers extraits ----------------\n";

    if (Fichier_extrait.isEmpty()){
        qDebug() << "Aucun fichier n'a été trouvé";
    }
    for (int i = 0; i < Fichier_extrait.count(); i++) {
        qDebug() << "SSS :" << Fichier_extrait[i]->getPath();

        // Vérifier les SRS dans chaque SSS
        for (int j = 0; j < Fichier_extrait[i]->getFils().count(); j++) {
            qDebug() << "  |-- SRS :" << Fichier_extrait[i]->getFils()[j]->getPath();

            if (!Fichier_extrait[i]->getFils()[j]->hasFils()) {
                qDebug() << "  |   |-- SDD :" << Fichier_extrait[i]->getFils()[j]->getFils()->getPath();
            }
        }
    }
}

/**
 * @brief Lance la fenêtre de dialogue "style_exigence.ui".
 *
 * @author Maxime Huang
 * @date 09/03/2025
 */
void MainWindow::Lancer_filtre_style()
{
    if(arbre_fichiers->topLevelItemCount() == 0){
        QMessageBox::warning(this, "Erreur", "Veuillez importer les fichiers");
    }
    else{
        bool ok;
        QString radical = QInputDialog::getText(this,"Filtering by regular expression", "Radical (optional). Enter .* to select all:",QLineEdit::Normal,"", &ok);
        if (radical.endsWith('\n')) {
            radical.chop(1); // supprime le dernier caractère
        }
        QRegularExpression regex(radical);
        qDebug() << "File::getRadical() brut : [" << radical << "]";

        if (ok && !radical.isEmpty() && regex.isValid()){
            qDebug()<< "regex valide";
            File::setRadical("");
            File::setRadical(radical);
        }

        // "this" pour que MainWindow soit le parent
        QDialog *styleExigence = new style_exigence(this, Fichier_extrait);
        XmlParserUtils::afficherStyles(styleExigence, Fichier_extrait, this);
    }
}

/**
 * @brief Affiche les différents widgets customisés (QListWidget_custom, QTreeWidget_custom..).
 *
 * @author Maxime Huang
 * @date 29/03/2025
 */


void MainWindow::Affiche_WidgetFichiers_custom()
{
    //Affichage du tableau de fichiers importés
    liste_fichiers = new QListWidget_custom();
    ui->conteneur_liste->addWidget(liste_fichiers);

    //Affichage de l'arbre de données
    arbre_fichiers = new QTreeWidget_custom();
    ui->conteneur_arbre->insertWidget(1, arbre_fichiers);
}

/**
 * @brief Créer et configure une nouvelle fenêtre de graphe_affiche avec des boutons de zoom (+ et –).
 *
 * @details Cette méthode initialise une instance de la classe "FenetreGraphe", configure la scène
 * graphique "maScene" et crée un graphe_affiche à partir de "Fichier_extrait".
 *
 * @authors Maxime Huang / Jacques Zheng / Malek Allahoum
 * @date 28/03/2025
 */
void MainWindow::newGraphWindow()
{
    maScene.clear();
    maScene.setBackgroundBrush(Qt::white);
    maScene.setSceneRect(maScene.sceneRect().adjusted(-2000, -2000, 2000, 2000));

    // Créer et afficher le graphe
    Graphe* graphe = new Graphe(Fichier_extrait);
    QStringList liste_vide = {};
    graphe->afficherGraphe(&maScene, liste_vide);

    // Vue graphique principale
    maVue = new FenetreGraphe(this);
    maVue->setScene(&maScene);
    maVue->setRenderHint(QPainter::Antialiasing);
    maVue->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);


    // Boutons de zoom
    QPushButton* boutonPlus = new QPushButton("+", this);
    QPushButton* boutonMoins = new QPushButton("–", this);
    boutonPlus->setFixedSize(30, 30);
    boutonMoins->setFixedSize(30, 30);

    connect(boutonPlus, &QPushButton::clicked, this, [=]() {
        maVue->zoomAvant();
    });
    connect(boutonMoins, &QPushButton::clicked, this, [=]() {
        maVue->zoomArriere();
    });

    QHBoxLayout* boutonsLayout = new QHBoxLayout();
    boutonsLayout->addStretch();
    boutonsLayout->addWidget(boutonPlus);
    boutonsLayout->addWidget(boutonMoins);
    boutonsLayout->setSpacing(0);

    // Partie gauche : graphe + boutons
    QVBoxLayout* zoneGraphe = new QVBoxLayout();
    zoneGraphe->addWidget(maVue);
    zoneGraphe->addLayout(boutonsLayout);
    zoneGraphe->setStretch(0, 1);
    zoneGraphe->setContentsMargins(0, 0, 0, 0);

    // Créer ou réutiliser fenetreExigences
    if (!fenetreExigences) {
        fenetreExigences = new FenetreExigences(this);
        fenetreExigences->setFixedSize(200, 250);
    }

    // Layout horizontal principal : graphe à gauche, exigences à droite
    QHBoxLayout* grapheLayout = new QHBoxLayout();
    grapheLayout->addLayout(zoneGraphe);
    //grapheLayout->addWidget(fenetreExigences);
    grapheLayout->setStretch(0, 1);
    grapheLayout->setStretch(1, 0);
    grapheLayout->setContentsMargins(0, 0, 0, 0);

    // Nettoyer et insérer dans ui->graphe_affiche
    QWidget* conteneur = new QWidget();
    conteneur->setLayout(grapheLayout);

    if (ui->graphe_affiche->layout()) {
        //delete ui->graphe_affiche->layout(); // supprimer ancien layout si présent
    }
    QVBoxLayout* layoutGlobal = new QVBoxLayout();
    layoutGlobal->addWidget(conteneur);
    layoutGlobal->setContentsMargins(0, 0, 0, 0);
    ui->graphe_affiche->setLayout(layoutGlobal);

    // Connecter les clics sur les noeuds à l'affichage des exigences
    for (QGraphicsItem* item : maScene.items()) {
        NodeItem* node = dynamic_cast<NodeItem*>(item);
        if (node) {
            connect(node, &NodeItem::nodeClicked, this, &MainWindow::afficherExigencesPourNoeud);
        }
    }
}

/**
 * @brief Affiche les statistiques sous forme d'histogramme.
 *
 * Cette méthode extrait les taux des liens à l'aide de la fonction "extraireTousLesTauxDesLiens()", puis
 * passe ces données à la méthode "afficherHistogramme" de la classe "FenetreStatistiques" pour afficher
 * un histogramme sur le widget spécifié.
 *
 * @return void
 * @author Jacques
 */
void MainWindow::afficherStats(){
    std::vector<double> listeDesTaux = extraireTousLesTauxDesLiens();

    FenetreStatistiques::afficherHistogramme(ui->widget_2, listeDesTaux);
}

/**
 * @brief Gère l'action du bouton pour afficher un graphe.
 *
 *
 * @return void
 * @author Léa
 */
void MainWindow::Bouton_graphe(){
    int verif = getNav()->count();
    if (verif < 4) {
        Ajout_Analyse_bouton();  // Appeler la fonction de la fenêtre principale
    }
    onAnalyseClicked();
    getAnalyse()->setStyleSheet(Style::Changer_bleu_bouton_nav());
    newGraphWindow();
    XmlParserUtils::remplirCriteres(ui->frame_9, Srs::getFiltres(), this, [=]() {
        updateGraphWithCriteres();  // appel à la fonction qui va mettre à jour le graphe
    });
}

/**
 * @brief Met à jour dynamiquement le graphe en fonction des filtres cochés.
 *
 * Cette méthode récupère les critères sélectionnés par l’utilisateur dans l’interface,
 * efface la scène graphique actuelle, génère un nouveau graphe en fonction des critères,
 * puis le réaffiche dans "maVue". Enfin, elle reconnecte les signaux de chaque nouveau
 * "NodeItem" pour que les clics sur les nœuds continuent d'afficher les exigences.
 *
 * @author Jacques Zheng
 * @date 02/05/2025
 */

void MainWindow::updateGraphWithCriteres() {
    //Récupérer les critères cochés
    QStringList criteres = XmlParserUtils::getCriteresCoches(ui->frame_9);

    //Nettoyer la scène
    maScene.clear();
    maScene.setBackgroundBrush(Qt::white);


    //Créer un nouveau graphe avec critères
    Graphe* graphe = new Graphe(Fichier_extrait);
    graphe->afficherGraphe(&maScene, criteres);

    //Réassocier la scène à la vue

    maVue->setScene(&maScene);
    maVue->update();  // Forcer le redessin

    //Reconnecter les clics sur les nouveaux nœuds
    for (QGraphicsItem* item : maScene.items()) {
        NodeItem* node = dynamic_cast<NodeItem*>(item);
        if (node) {
            connect(node, &NodeItem::nodeClicked, this, &MainWindow::afficherExigencesPourNoeud);
        }
    }
}

/**
 * @brief Gère la suppression de tous les fichiers de la liste.
 *
 * Cette méthode vérifie d'abord s'il y a des fichiers dans la liste. Si la liste est vide,
 * elle affiche un message d'information. Ensuite, elle demande à l'utilisateur de confirmer
 * la suppression via une boîte de dialogue. Si l'utilisateur confirme, tous les fichiers
 * sont supprimés de la liste et le compteur de fichiers téléchargés est réinitialisé à zéro.
 * Enfin, un message de confirmation est affiché.
 *
 * @return void
 * @author Jacques
 */
void MainWindow::on_DeleteAll_clicked()
{
    // Vérifier s'il y a des fichiers à supprimer
    if (liste_fichiers->count() == 0) {
        QMessageBox::information(this, "Suppression", "Aucun fichier à supprimer.");
        return;
    }

    // Demander confirmation
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation","Voulez-vous vraiment supprimer tous les fichiers de la liste ?", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::No)
        return;

    // Supprimer tous les fichiers de la liste
    while (liste_fichiers->count() > 0) {
        QListWidgetItem* item = liste_fichiers->takeItem(0);
        delete item;
    }

    // Réinitialiser le compteur
    nb_fichier_upload = 0;
    ui->nb_fichier_upload->setText("(0)");

    // Message de confirmation
    QMessageBox::information(this, "Suppression", "Tous les fichiers ont été retirés de la liste.");
}

/**
 * @brief Extrait tous les taux de traçabilité présents dans la scène graphique.
 *
 * @details Cette fonction parcourt tous les éléments de la scène graphique principale ("maScene")
 * et récupère les objets de type LinkItem. Pour chaque lien détecté, elle extrait le taux
 * de traçabilité associé et le stocke dans un vecteur de valeurs numériques.
 *
 * @return Un vecteur de doubles contenant les taux de traçabilité de tous les liens présents dans le graphe.
 *
 * @author Jacques Zheng
 * @date 12/04/2025
 */

//Extrait tous les taux de traçabilité des noeuds
std::vector<double> MainWindow::extraireTousLesTauxDesLiens() {
    std::vector<double> tauxList;

    QList<QGraphicsItem*> items = maScene.items();
    for (QGraphicsItem* item : items) {
        LinkItem* lien = dynamic_cast<LinkItem*>(item);
        if (lien) {
            tauxList.push_back(static_cast<double>(lien->getTauxTracabilite()));
        }
    }

    return tauxList;
}

// ===================================================================
//                 METHODES ANIMATION DYNAMTIQUE
// ===================================================================

/**
 * @brief MainWindow::AnimationFonctions
 *
 * @author Maxime Huang
 * @date 20/04/25
 */
void MainWindow::AnimationFonctions()
{
    Animation_afficherProchaineLettre("The traceability tool loved by engineers", ui->subtitles);


    fadeIn_Widget(ui->BarreLateraleMenu,500,770);
    fadeIn_Widget(ui->Widget_help,530,770);
    fadeIn_Widget(ui->WidgetHelpTexte,600,770);
    fadeIn_Widget(ui->WidgetTexteOption,600,770);
    fadeIn_Widget(ui->JustPlotIt,300);
    fadeIn_Widget(ui->WithTraceX,350);

}

/**
 * @brief fadeIn_Widget
 * @param widget
 *
 * @author Maxime Huang
 * @date 21/04/25
 */
void MainWindow::fadeIn_Widget(QWidget* widget, int delai, int duree) {

    widget->setVisible(false);

    QTimer::singleShot(delai, [=]() {
        QGraphicsOpacityEffect* effet = new QGraphicsOpacityEffect(widget);
        widget->setGraphicsEffect(effet);

        widget->setVisible(true);
        QPropertyAnimation* animation = new QPropertyAnimation(effet, "opacity");
        animation->setDuration(duree);   // Durée de l'animation
        animation->setStartValue(0);
        animation->setEndValue(1);



        animation->start(QAbstractAnimation::DeleteWhenStopped);
    });
}



/**
 * @brief MainWindow::Animation_afficherProchaineLettre
 * @param texteComplet
 * @param WidgetTexte
 *
 * @author Maxime Huang
 * @date 20/04/25
 */
void MainWindow::Animation_afficherProchaineLettre(QString texteComplet, QLabel* WidgetTexte) {
    i = 0;
    texteActuel = "";

    //Attend 880ms avant de s'executer
    QTimer::singleShot(950, this, [=]() {
        timer = new QTimer(this);

        QString newStyle = ui->subtitles->styleSheet() + "border-top: 1px solid rgba(22, 55, 68,0.8)";
        ui->subtitles->setStyleSheet(newStyle);

        // Connexion du signal timeout() du timer à un lambda qui va afficher les lettres
        connect(timer, &QTimer::timeout, this, [=]() {
            if (i < texteComplet.length()) {
                texteActuel += texteComplet[i];  // Ajoute une lettre à chaque fois
                WidgetTexte->setText(texteActuel);

                i++;
            } else {
                timer->stop();
                delete timer;
            }
        });

        //intervalle entre chaque lettres
        timer->start(30);
    });
}

/**
 * @brief MainWindow::on_BarreLateraleMenu_clicked
 *
 * @author Maxime Huang
 * @date 20/04/25
 */
void MainWindow::on_BarreLateraleMenu_clicked()
{
    QWidget* contenu = ui->WidgetAnime; // le widget à animer
    QPropertyAnimation *menuAnimation = new QPropertyAnimation(contenu, "maximumWidth");

    menuAnimation->setDuration(330);

    if (menuOpen) {
        menuAnimation->setStartValue(180);
        menuAnimation->setEndValue(0);
        menuOpen = false;
    } else {
        menuAnimation->setStartValue(0);
        menuAnimation->setEndValue(180);
        menuOpen = true;
    }

    menuAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}



// 02/05 Jacques

/**
 * @brief Affiche les exigences associées à un nœud lorsqu’il est cliqué.
 *
 * Cette méthode est appelée lorsqu’un objet NodeItem est cliqué dans le graphe.
 * Elle vérifie si le nœud et son fichier sont valides, puis extrait les exigences
 * et les affiche dans la fenêtre dédiée (fenetreExigences).
 *
 * La méthode ne fait rien si :
 * - le nœud est nul,
 * - le fichier associé est nul,
 * - l’utilisateur n’est pas sur la page "Analyse > Graphe".
 *
 * @param noeud Pointeur vers le NodeItem cliqué.
 *
 * @author Jacques Zheng
 * @date 02/05/2025
 */


void MainWindow::afficherExigencesPourNoeud(NodeItem *noeud)
{
    if (!noeud) {
        qWarning() << "[ERREUR] NodeItem nul.";
        return;
    }

    File* file = noeud->getFile();
    if (!file) {
        qWarning() << "[ERREUR] Le fichier du noeud est nullptr.";
        if (fenetreExigences)
            fenetreExigences->setExigences(QStringList() << "Erreur : fichier manquant");
        return;
    }

    QStringList exigences = noeud->getExigences();

    if (fenetreExigences) {
        fenetreExigences->setExigences(exigences);
    } else {
        qWarning() << "fenetreExigences est nullptr !";
    }

    if (ui->Contenus->currentIndex() != PAGE_ANALYSE || ui->Stacked_Analyse->currentIndex() != PAGE_GRAPHE) {
        return;
    }
}

/**
 * @brief Repositionne dynamiquement la fenêtre des exigences lors du redimensionnement de la fenêtre principale.
 *
 * Cette surcharge de resizeEvent déplace la "fenetreExigences" en bas à droite
 * de la fenêtre principale, en maintenant un décalage fixe. Elle appelle ensuite
 * l'implémentation parente ("QMainWindow::resizeEvent").
 *
 * @param event Pointeur vers l’événement de redimensionnement.
 *
 * @author Jacques Zheng
 * @date 02/05/2025
 */
void MainWindow::resizeEvent(QResizeEvent *event)
{
    if (fenetreExigences)
        fenetreExigences->move(this->width() - 220, this->height() - 320);
    QMainWindow::resizeEvent(event);
}

/**
 * @brief Retourne le widget qui contient les filtres d'exigence
 *
 * @author Maxime Huang
 * @date 04/05/25
 */
QVBoxLayout* MainWindow::getConteneurExigenceLayout() {
    return qobject_cast<QVBoxLayout*>(ui->frame_11->layout());
}

/**
 * @brief MainWindow::on_BoutonTelechargementCSV_clicked
 * @author Jacques Zheng
 * @date
 */
void MainWindow::on_BoutonTelechargementCSV_clicked()
{
    QString cheminFichier = QFileDialog::getSaveFileName(this, "Enregistrer le fichier CSV", "", "Fichiers CSV (*.csv)");
    if (cheminFichier.isEmpty())
        return; // L'utilisateur a annulé
    QFile fichier(cheminFichier);
    if (!fichier.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier !");
        return;
    }
    // Générer le rapport à partir des fichiers de Graphe
    Graphe* graphe = new Graphe(Fichier_extrait);
    Rapport rapport(graphe->getFichiers());
    rapport.generation(graphe->getFichiers());
    QTextStream out(&fichier);
    out << "NameSSS;NameSRS;NameSDD;exigenceSSS;exigenceSRS;exigenceSDD\n";

    for (Rapportligne rl : rapport.getLignesRapport()) {
        out << QString::fromStdString(rl.toString()) << "\n";
    }

    fichier.close();
    QMessageBox::information(this, "Succès", "Fichier CSV généré avec succès !");
}

