#ifndef TU_SRS_H
#define TU_SRS_H

#include <QtTest>
#include "../srs.h"
#include "../exigencesrs.h"
#include "QtCore"

class TU_SRS : public QObject {
    Q_OBJECT

private slots:
    void init();
    void test_addEtGetExigence();
    void test_totalExigences();
    void test_getFilsEtSetFils();
    void test_getIdsExigenceMatchesCriteres();
    void test_toQStringExigence();
    void test_extractExigences_word();
    void test_isMatchesRadical();
    void testGetCriteres();
    void cleanup();
    void test_addFiltres();
    void test_getRadicaux();
};

#endif // TU_SRS_H
