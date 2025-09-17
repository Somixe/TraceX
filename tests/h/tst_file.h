#ifndef TU_FILE_H
#define TU_FILE_H

#include <QtTest>
#include "../file.h"

class TU_FILE : public QObject {
    Q_OBJECT

private slots:
    // TU_FILE_01 : Vérifie la construction sans chemin
    void test_constructeurParDefaut();

    // TU_FILE_02 : Vérifie la construction avec chemin
    void test_constructeurAvecChemin();

    // TU_FILE_03 : Vérifie getNom() retourne bien le nom du fichier
    void test_getNom();

    // TU_FILE_04 : Vérifie les fonctions isWord, isExcel, isCsv
    void test_extensions();

    // TU_FILE_05 : Vérifie setRadical et getRadical
    void test_radical();
};

#endif // TU_FILE_H
