#include <QtTest>
#include "../tracabilite.h"
#include "../exigence.h"
#include "../exigencesrs.h"
#include "../srs.h"
#include "../sss.h"
#include "tst_tracabilite.h"

void TU_TRACABILITE::test_taux_traca_sss_srs() {
    Exigence A=Exigence("A"); Exigence B = Exigence("B"); Exigence C = Exigence("C");Exigence D = Exigence("D");
    Sss docSss = Sss("");
    docSss.addExigence(A);
     docSss.addExigence(B);
     docSss.addExigence(C);
      docSss.addExigence(D);
    ExigenceSrs e1("A", {}, {}, false, {});
    ExigenceSrs e2("B", {}, {}, false, {});
    Srs docSrs = Srs("");
    docSrs.addExigence(e1);
    docSrs.addExigence(e2);

    int taux = Tracabilite::taux_traca_sss_srs(docSss.getExigence(), docSrs.getExigence());  // 2/3 = 66%
    QCOMPARE(taux, 50);
}

void TU_TRACABILITE::test_taux_traca_srs_sdd() {
    Srs docSrs = Srs("");
    ExigenceSrs srs1("X", {}, {}, false, {});

    ExigenceSrs srs2("Y", {}, {}, false, {});
    docSrs.addExigence(srs1);
    docSrs.addExigence(srs2);

    std::vector<ExigenceSrs> srs = {srs1, srs2};

    std::vector<Exigence> sdd = {Exigence("X"), Exigence("A")};

    int taux = Tracabilite::taux_traca_srs_sdd(docSrs.getExigence(), sdd);
    QCOMPARE(taux, 50);
}

void TU_TRACABILITE::test_taux_traca_ids() {
    std::vector<std::string> pere = {"A", "B", "C"};
    std::vector<std::string> fils = {"B", "C", "D"};

    float taux = Tracabilite::taux_traca(pere, fils);  // 2/3
    QCOMPARE(static_cast<int>(taux), 66);  // float mais on compare en %
}

