#include <QtTest>
#include "../file.h"
#include "tst_file.h"



void TU_FILE::test_constructeurParDefaut() {
    File f;
    QCOMPARE(f.getPath(), std::string(""));
}

void TU_FILE::test_constructeurAvecChemin() {
    File f("docs/example.docx");
    QCOMPARE(f.getPath(), std::string("docs/example.docx"));
}

void TU_FILE::test_getNom() {
    File f("folder/testfile.csv");
    QCOMPARE(f.getNom(), QString("testfile.csv"));
}

void TU_FILE::test_extensions() {
    File word("doc.docx");
    File excel("sheet.xlsx");
    File csv("data.csv");
    File none("image.png");

    QVERIFY(word.isWord());
    QVERIFY(!word.isExcel());
    QVERIFY(!word.isCsv());

    QVERIFY(excel.isExcel());
    QVERIFY(!excel.isWord());
    QVERIFY(!excel.isCsv());

    QVERIFY(csv.isCsv());
    QVERIFY(!csv.isWord());
    QVERIFY(!csv.isExcel());

    QVERIFY(!none.isWord());
    QVERIFY(!none.isExcel());
    QVERIFY(!none.isCsv());
}

void TU_FILE::test_radical() {
    //a enlever
    File f = File("dummy");
    File::setRadical("base");
    QCOMPARE(f.getRadical(), QString("base"));
}

