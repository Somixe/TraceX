#ifndef TU_SDD_H
#define TU_SDD_H

#include <QtTest>
#include "../sdd.h"
#include "../exigence.h"

class TU_SDD : public QObject {
    Q_OBJECT

private slots:
    void test_addEtGetExigence();
    void test_totalExigences();
    void test_toQStringExigence();
    void test_getIdsExigence_sansRadical();
};

#endif // TU_SDD_H
