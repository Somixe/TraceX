#ifndef TESTRAPPORT_H
#define TESTRAPPORT_H

#include <QtTest>
#include "../rapport.h"
#include "../rapportligne.h"
#include "../sss.h"  // Inclure vos en-têtes pour Sss, Srs, Exigence, etc.
#include "../exigencesrs.h"
#include "../srs.h"
#include "../exigence.h"

class TestRapport : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testGeneration();
    void testLignesRapport();
    void cleanupTestCase();
    void testIsInSrs();
};

#endif // TESTRAPPORT_H
