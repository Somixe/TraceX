#include <QtTest>
#include "../style.h"
#include "tst_style.h"

void TU_STYLE::test_Style_Button_analyse() {
    QString style = Style::Style_Button_analyse();
    QVERIFY(style.contains("QPushButton"));
    QVERIFY(style.contains("font-size"));
}

void TU_STYLE::test_Changer_bleu_bouton_nav() {
    QString style = Style::Changer_bleu_bouton_nav();
    QVERIFY(style.contains("color"));
    QVERIFY(style.contains("background-color"));
}

void TU_STYLE::test_Style_liste_Fichiers() {
    QString style = Style::Style_liste_Fichiers();
    QVERIFY(style.contains("QListWidget_custom"));
    QVERIFY(style.contains("background"));
}

void TU_STYLE::test_Style_arbre_Fichiers() {
    QString style = Style::Style_arbre_Fichiers();
    QVERIFY(style.contains("QTreeWidget"));
    QVERIFY(style.contains("background-color"));
}

void TU_STYLE::test_Style_progressBar() {
    QString style = Style::Style_progressBar();
    QVERIFY(style.contains("QProgressBar"));
    QVERIFY(style.contains("QProgressDialog"));
}

void TU_STYLE::test_Style_CheckBox_Critere_Style() {
    QString style = Style::Style_CheckBox_Critere_Style();
    QVERIFY(style.contains("QCheckBox"));
    QVERIFY(style.contains("indicator"));
}

