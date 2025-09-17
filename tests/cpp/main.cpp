#include <QCoreApplication>
#include <QtTest>

// Inclure les fichiers des classes de tests unitaires
#include "tst_exigence.h"
#include "tst_exigencesrs.h"
#include "tst_file.h"
#include "tst_fileutils.h"
#include "tst_stylefile.h"
#include "tst_rapport.h"
#include "tst_sdd.h"
#include "tst_sss.h"
#include "tst_srs.h"
#include "tst_tracabilite.h"
#include "tst_style.h"
#include "tst_tracabilite.h"
#include "tst_xmlparserutils.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    int statut = 0;

    TU_XMLPARSERUTILS testXmlParserUtils;
    statut |= QTest::qExec(&testXmlParserUtils, argc, argv);

   TestExigence testExigence;
    statut |= QTest::qExec(&testExigence, argc, argv);

    TestExigenceSrs testExigenceSrs;
    statut |= QTest::qExec(&testExigenceSrs, argc, argv);

    TU_SRS testSrs;
    statut |= QTest::qExec(&testSrs, argc, argv);






    return statut;
}
