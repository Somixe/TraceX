#ifndef TU_TRACABILITE_H
#define TU_TRACABILITE_H

#include <QtTest>
#include "../tracabilite.h"
#include "../exigence.h"
#include "../exigencesrs.h"
#include "../srs.h"
#include "../sss.h"

class TU_TRACABILITE : public QObject {
    Q_OBJECT

private slots:
    void test_taux_traca_sss_srs();
    void test_taux_traca_srs_sdd();
    void test_taux_traca_ids();
};

#endif // TU_TRACABILITE_H
