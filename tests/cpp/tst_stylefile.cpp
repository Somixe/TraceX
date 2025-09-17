#include <QtTest>
#include "../stylefile.h"
#include "tst_stylefile.h"

void TU_STYLEFILE::test_constructeurParDefaut() {
    StyleFile s;
    QCOMPARE(s.getId(), std::string(""));
    QCOMPARE(s.getName(), std::string(""));
    QCOMPARE(s.getPolice(), std::string(""));
    QCOMPARE(s.getPoliceSize(), 0);
    QCOMPARE(s.getColor(), std::string("black"));
    QVERIFY(!s.isGras());
    QVERIFY(!s.isItalique());
    QVERIFY(!s.isSouligne());
    QVERIFY(!s.isShadow());
}

void TU_STYLEFILE::test_constructeurCompletEtAccesseurs() {
    StyleFile s("id1", "Titre", "Arial", 12, "blue", true, false, true, true);

    QCOMPARE(s.getId(), std::string("id1"));
    QCOMPARE(s.getName(), std::string("Titre"));
    QCOMPARE(s.getPolice(), std::string("Arial"));
    QCOMPARE(s.getPoliceSize(), 12);
    QCOMPARE(s.getColor(), std::string("blue"));
    QVERIFY(s.isGras());
    QVERIFY(!s.isItalique());
    QVERIFY(s.isSouligne());
    QVERIFY(s.isShadow());
}

void TU_STYLEFILE::test_toQString() {
    StyleFile s("id1", "Titre", "Arial", 14, "red", true, true, false, false);
    QString qstr = s.toQString();

    QVERIFY(qstr.contains("Arial"));
    QVERIFY(qstr.contains("14"));
    QVERIFY(qstr.contains("red"));
    QVERIFY(qstr.contains("gras"));
    QVERIFY(qstr.contains("italique"));
    QVERIFY(!qstr.contains("souligné"));  // false
    QVERIFY(!qstr.contains("ombre"));     // false
}

