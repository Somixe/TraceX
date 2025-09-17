#include <QtTest>
#include "../exigencesrs.h"
#include "tst_exigencesrs.h"



void TestExigenceSrs::testConstructeurs() {
    ExigenceSrs e1("id1", {"c1", "c2"}, {"n1"}, true, {"t1"});
    QCOMPARE(e1.getId(), std::string("id1"));
    QVERIFY(e1.isDev());
}

void TestExigenceSrs::testGetters() {
    std::vector<std::string> cible = {"client"};
    std::vector<std::string> necessaire = {"n1", "n2"};
    std::vector<std::string> tracabilite = {"t1"};

    ExigenceSrs e("id42", cible, necessaire, false, tracabilite);
    QCOMPARE(e.getCible(), cible);
    QCOMPARE(e.getNecessaire(), necessaire);
    QCOMPARE(e.getTracabilite(), tracabilite);
    QVERIFY(!e.isDev());
}

void TestExigenceSrs::testToString() {
    ExigenceSrs e("X1", {"UI"}, {"moduleX"}, true, {});
    std::string result = e.toString();
    QVERIFY(result.find("Id : X1") != std::string::npos);
    QVERIFY(result.find("Cible : UI") != std::string::npos);
    QVERIFY(result.find("Necessaire : moduleX") != std::string::npos);
    QVERIFY(result.find("dev") != std::string::npos);
}

void TestExigenceSrs::testHasCibleEtNecessaire() {
    ExigenceSrs e1("idA", {"A"}, {"B"}, false, {});
    QVERIFY(e1.hasCible());
    QVERIFY(e1.hasNecessaire());

    ExigenceSrs e2("idB", false, {});
    QVERIFY(!e2.hasCible());
    QVERIFY(!e2.hasNecessaire());
}


