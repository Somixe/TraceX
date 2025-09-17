#ifndef TESTEXIGENCESRS_H
#define TESTEXIGENCESRS_H

#include <QObject>
#include <QtTest>
#include "../exigencesrs.h"  // Assurez-vous que le fichier d'en-tête ExigenceSrs est inclus

class TestExigenceSrs : public QObject
{
    Q_OBJECT

private slots:
    void testConstructeurs();
    void testGetters();
    void testToString();
    void testHasCibleEtNecessaire();
};

#endif // TESTEXIGENCESRS_H
