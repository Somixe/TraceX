#ifndef TU_STYLE_H
#define TU_STYLE_H

#include <QtTest>
#include "../style.h"

class TU_STYLE : public QObject {
    Q_OBJECT

private slots:
    void test_Style_Button_analyse();
    void test_Changer_bleu_bouton_nav();
    void test_Style_liste_Fichiers();
    void test_Style_arbre_Fichiers();
    void test_Style_progressBar();
    void test_Style_CheckBox_Critere_Style();
};

#endif // TU_STYLE_H
