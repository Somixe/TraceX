#ifndef TU_STYLEFILE_H
#define TU_STYLEFILE_H

#include <QtTest>
#include "../stylefile.h"

class TU_STYLEFILE : public QObject {
    Q_OBJECT

private slots:
    void test_constructeurParDefaut();
    void test_constructeurCompletEtAccesseurs();
    void test_toQString();
};

#endif // TU_STYLEFILE_H
