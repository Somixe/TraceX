#include <QtTest>
#include "../sss.h"
#include "../exigence.h"
#include "../srs.h"
#include "tst_sss.h"

void TU_SSS::test_addEtGetExigence() {
    Sss sss("sss.docx");
    sss.addExigence(Exigence("A1"));
    sss.addExigence(Exigence("A2"));

    auto exigences = sss.getExigence();
    QCOMPARE(exigences.size(), 2);
    QCOMPARE(exigences[0].getId(), std::string("A1"));
}

void TU_SSS::test_totalExigences() {
    Sss sss("path.docx");
    QCOMPARE(sss.totalExigences(), 0);
    sss.addExigence(Exigence("X"));
    QCOMPARE(sss.totalExigences(), 1);
}

void TU_SSS::test_addEtGetFils() {
    Sss sss("sss1.docx");
    Srs* srs = new Srs("srs.docx");
    sss.addFils(srs);

    auto fils = sss.getFils();
    QCOMPARE(fils.size(), 1);
    QCOMPARE(fils.first()->getPath(), std::string("srs.docx"));
    delete srs;
}

void TU_SSS::test_getIdsExigence_sansFiltre() {
    Sss sss("sss.xlsx");  // peu importe le type ici
    sss.addExigence(Exigence("REQ_001"));
    sss.addExigence(Exigence("REQ_002"));

    QStringList criteresVides;
    auto ids = sss.getIdsExigence(criteresVides);

    QCOMPARE(ids.size(), 2);
    QCOMPARE(ids[0], "REQ_001");
    QCOMPARE(ids[1], "REQ_002");
}

void TU_SSS::test_toQStringExigence() {
    Sss sss("sss.csv");
    sss.addExigence(Exigence("E1"));
    QString texte = sss.toQStringExigence();
    QVERIFY(texte.contains("E1"));
}

