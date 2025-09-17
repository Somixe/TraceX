/**
 * @file style.cpp
 * @brief Définition des styles personnalisés pour l'interface graphique.
 *
 * @details Ce fichier contient la définition de plusieurs méthodes de la classe Style,
 * qui renvoient des chaînes de caractères représentant les styles en QSS appliqués à différents éléments
 * de l'interface graphique.
 *
 * @author Maxime Huang
 * @version 1.0
 * @date Dernière modification : 28/03/2025
 */

#include "style.h"

/**
 * @brief Retourne le style QSS par défaut du bouton "analyse".
 *
 * @return QString     Chaîne contenant le style CSS.
 *
 * @author Maxime Huang
 * @date 09/03/2025
 */
QString Style::Style_Button_analyse()
{
    return
        "QPushButton:pressed {"
        "background-color: rgba(20, 31, 35, 0.5);"
        "padding: 5px 10px;"
        "width:80px;"
        "}"

        "QPushButton:hover{"
        "font-size: 13px;"
        "background-color: rgba(20, 31, 35, 1);"
        "padding: 5px 10px;"
        "width:80px;"
        "}"

        "QPushButton {"
        "background-color:transparent;"
        "color: white;"
        "font-size: 12px;"
        "font-weight: bold;"
        "border: none;"
        "padding: 5px 10px;"
        "width:80px;"
        "height:30px;"
        "}";
}

/**
 * @brief Retourne le style QSS pour changer la couleur du bouton "analyse" en bleu.
 *
 * @details Ce style change le style du bouton lors de l'appuie, du survol et de la pression.
 *
 * @return QString Chaîne contenant le style CSS.
 *
 * @author Maxime Huang
 * @date 09/03/2025
 */
QString Style::Changer_bleu_bouton_nav()
{
    return
        "QPushButton:pressed {"
        "background-color: rgb(20, 31, 35);"
        "padding: 5px 10px;"
        "width: 80px;"
        "}"

        "QPushButton {"
        "background-color: transparent;"
        "color: rgba(103, 158, 180, 1);"
        "font-size: 12px;"
        "font-weight: bold;"
        "border: none;"
        "padding: 5px 10px;"
        "width: 80px;"
        "height: 30px;"
        "}"

        "QPushButton[color='color_changed'] {"
        "color: rgb(103, 158, 180);"
        "background-color:rgba(27, 56, 69, 0.7);"
        "}"

        "QPushButton:hover {"
        "font-size: 13px;"
        "background-color: rgba(20, 31, 35, 1);"
        "padding: 5px 10px;"
        "width: 80px;"
        "}";
}

/**
 * @brief Retourne le style CSS pour le tableau de fichiers.
 *
 * @details Ce style personnalise l'apparence du widget QListWidget_custom et de ses éléments.
 * Il inclut également le style du conteneur et les effets au survol.
 *
 * @return QString Chaîne contenant le style CSS.
 *
 * @author Maxime Huang
 * @date
 */
QString Style::Style_liste_Fichiers()
{
    return
        "QListWidget_custom {"
        "    border-bottom-left-radius: 5px;"
        "    border-bottom-right-radius: 5px;"
        "    border: 1px solid rgb(227, 227, 227);"
        "    border-top:none;"
        "}"
        "#liste_fichiers{"
        "    background: transparent;"
        "}"
        "#conteneur {"
        "    border: 1px solid rgb(227, 227, 227);"
        "    background-color: rgb(250, 250, 250);"
        "}"
        "QLabel, QString, QPushButton {"
        "    border: none;"
        "    color : black;"
        "    background: transparent;"
        "}"
        "#conteneur:hover {"
        "    background-color: rgb(240, 240, 240);"
        "}"
        "QListWidget_custom::item:selected {"
        "    border-left: none;"
        "}";
}


/**
 * @brief Retourne le style CSS pour l'arbre de données.
 *
 * @details Ce style personnalise l'apparence de l'en-tête de l'arborescence des fichiers.
 *
 * @return QString Chaîne contenant le style CSS.
 *
 * @author Maxime Huang
 * @date 28/03/2025
 */
QString Style::Style_arbre_Fichiers()
{
    return
        "QTreeWidget {"
        "    color: black;"

        "} "
        "QHeaderView::section {"
        "    font-weight: bold;"
        "    font-size: 10px;"
           "color:black;"
        "background-color:rgba(202, 202, 202, 0.8);"
           "border: 1px solid rgba(202, 202, 202, 1);"
        "}"
        "QTreeWidget::item {"
        " color: black;"
        " background-color: rgba(240, 240, 240, 0.9);"
        "}"
        "QTreeWidget::item:selected {"
        " color: black;"
        " background-color: rgba(180, 190, 200, 0.8);"
        "}";

}

/**
 * @brief Retourne le style CSS pour la barre de progression.
 *
 * @details Ce style personnalise l'apparence de la barre de progression.
 *
 * @return QString Chaîne contenant le style CSS.
 *
 * @author Maxime Huang
 * @date 02/03/2025
 */
QString Style::Style_progressBar()
{
    return
        "QProgressDialog {"
        "background-color: #f4f4f4;"
        "color: #333;"
        "font-size: 12px;"
        "border-radius: 10px;"
        "padding: 10px;"
        "min-width: 250px;"
        "}"

        "QLabel {"
        "color: #333;"
        "font-size: 12px;"
        "font-weight: normal;"
        "}"

        "QProgressBar {"
        "border: 1px solid #ccc;"
        "border-radius: 5px;"
        "background: #e4e4e4;"
        "height: 10px;"
        "}"

        "QProgressBar::chunk {"
        "background-color: #4CAF50;"
        "width: 5px;"
        "}"

        "QProgressDialog::close-button {"
        "background-color: #f44336;"
        "border-radius: 6px;"
        "color: white;"
        "font-weight: bold;"
        "}";
}

/**
 * @brief Retourne le style CSS personnalisé pour les QCheckBox des critères de style.
 *
 * Ce style applique une couleur blanche au texte, définit la taille des indicateurs,
 * et personnalise l'apparence des cases cochées et non cochées.
 *
 * @return QString Feuille de style CSS à appliquer aux QCheckBox.
 *
 * @author Maxime Huang
 * @date 02/03/2025
 */
QString Style::Style_CheckBox_Critere_Style(){
    return
        "QCheckBox {"
        " color: white;"
        " }"
        "QCheckBox::indicator {"
        " width: 13px;"
        " height: 13px;"
        " }"
        "QCheckBox::indicator:unchecked {"
        " border: 1px solid white;"
        " background-color: none;"
        " }"
        "QCheckBox::indicator:checked {"
        " border:   1px solid white;"
        " background:   green;"
        " }";
}

