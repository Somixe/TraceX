#ifndef TESTEXIGENCE_H
#define TESTEXIGENCE_H

#include <QObject>
#include <QtTest>
#include "../exigence.h"  // Assurez-vous que le fichier d'en-tête Exigence est inclus

class TestExigence : public QObject
{
    Q_OBJECT

private slots:
    void testConstructeur();
    void testGetId();
    void testToString();
};

#endif // TESTEXIGENCE_H
