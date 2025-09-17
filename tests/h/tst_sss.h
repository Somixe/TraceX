#ifndef TU_SSS_H
#define TU_SSS_H

#include <QtTest>
#include "../sss.h"
#include "../exigence.h"
#include "../srs.h"

class TU_SSS : public QObject {
    Q_OBJECT

private slots:
    void test_addEtGetExigence();
    void test_totalExigences();
    void test_addEtGetFils();
    void test_getIdsExigence_sansFiltre();
    void test_toQStringExigence();
};

#endif // TU_SSS_H
