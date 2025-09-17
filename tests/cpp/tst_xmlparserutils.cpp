#include <QtTest>
#include "../xmlparserutils.h"
#include "tst_xmlparserutils.h"

void TU_XMLPARSERUTILS::test_nettoyage_exigence_srs() {
    std::string ligne = "ID: EX1, EX2 , EX3";
    auto list = XmlParserUtils::nettoyage_exigence_srs(ligne);
    QCOMPARE(list.size(), static_cast<size_t>(3));
    QVERIFY(std::find(list.begin(), list.end(), "EX1") != list.end());
    QVERIFY(std::find(list.begin(), list.end(), "EX2") != list.end());
}

void TU_XMLPARSERUTILS::test_RGB_to_Color() {
    std::string hex = "FF0000";  // rouge
    std::string nom = XmlParserUtils::RGB_to_Color(hex);
    QVERIFY(!nom.empty());
    QVERIFY(nom == "red" || nom == "#ff0000");
}


