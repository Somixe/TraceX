#include <QtTest>
#include "../exigence.h"
#include "tst_exigence.h"



void TestExigence::testConstructeur() {
    Exigence e("123");
    QCOMPARE(e.getId(), std::string("123"));
}

void TestExigence::testGetId() {
    Exigence e("abc");
    QCOMPARE(e.getId(), std::string("abc"));
}

void TestExigence::testToString() {
    Exigence e("999");
    QCOMPARE(e.toString(), std::string("Id : 999"));

    Exigence empty("");
    QCOMPARE(empty.toString(), std::string(""));
}
