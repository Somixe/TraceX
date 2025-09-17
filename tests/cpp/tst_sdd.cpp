#include <QtTest>
#include "../sdd.h"
#include "../exigence.h"
#include "tst_sdd.h"

void TU_SDD::test_addEtGetExigence() {
    Sdd s;
    Exigence e1("REQ_001");
    Exigence e2("REQ_002");
    s.addExigence(e1);
    s.addExigence(e2);

    auto exigences = s.getExigence();
    QCOMPARE(exigences.size(), 2);
    QCOMPARE(exigences[0].getId(), std::string("REQ_001"));
    QCOMPARE(exigences[1].getId(), std::string("REQ_002"));
}

void TU_SDD::test_totalExigences() {
    Sdd s;
    QVERIFY(s.totalExigences() == 0);
    s.addExigence(Exigence("E1"));
    QCOMPARE(s.totalExigences(), 1);
}

void TU_SDD::test_toQStringExigence() {
    Sdd s;
    s.addExigence(Exigence("E1"));
    s.addExigence(Exigence("E2"));

    QString texte = s.toQStringExigence();
    QVERIFY(texte.contains("E1"));
    QVERIFY(texte.contains("E2"));
}

void TU_SDD::test_getIdsExigence_sansRadical() {
    Sdd s;
    s.addExigence(Exigence("E1"));
    s.addExigence(Exigence("E2"));

    QStringList vide;
    auto ids = s.getIdsExigence(vide);
    QCOMPARE(ids.size(), 2);
    QCOMPARE(ids[0], "E1");
    QCOMPARE(ids[1], "E2");
}

