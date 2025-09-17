#ifndef TESTFILEUTILS_H
#define TESTFILEUTILS_H

#include <QtTest>
#include "../FileUtils.h"
#include <QFile>
#include <QDir>

class TestFileUtils : public QObject {
    Q_OBJECT

private slots:
    void testCreateCopy();
    void testCreateZipFolder();
    void testExtractXmlFolder(); // attention : dépend de fichiers réels
    void testDeleteExtra();      // attention : effets réels sur le système
};

#endif // TESTFILEUTILS_H
