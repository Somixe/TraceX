#include <QtTest>
#include "../FileUtils.h"
#include <QFile>
#include <QDir>
#include "tst_fileutils.h"

void TestFileUtils::testCreateCopy() {
    std::string input = "document.docx";
    std::string expected = "documentCopy.docx";
    QCOMPARE(FileUtils::CreateCopy(input), expected);

    input = "data.backup.csv";
    expected = "data.backupCopy.csv";
    QCOMPARE(FileUtils::CreateCopy(input), expected);
}

void TestFileUtils::testCreateZipFolder() {
    std::string input = "documentCopy.docx";
    std::string expected = "documentCopy.zip";
    QCOMPARE(FileUtils::CreateZipFolder(input), expected);

    input = "data.backupCopy.csv";
    expected = "data.backupCopy.zip";
    QCOMPARE(FileUtils::CreateZipFolder(input), expected);
}



void TestFileUtils::testExtractXmlFolder() {
    // Préparation : copier un fichier DOCX valide dans le dossier de test
    std::string path = "test_data/sample.docx";
    if (!QFile::exists(QString::fromStdString(path))) {
        QSKIP("Fichier test_data/sample.docx manquant pour testExtractXmlFolder");
    }

    std::string folder = FileUtils::ExtractXmlFolder(path);
    QVERIFY(!folder.empty());
    QVERIFY(QDir(QString::fromStdString(folder)).exists());

    // Nettoyage
    FileUtils::delete_extra(folder);
    QVERIFY(!QFile::exists(QString::fromStdString(folder)));
    QVERIFY(!QFile::exists(QString::fromStdString(folder.substr(0, folder.size() - 6) + ".zip")));
}

void TestFileUtils::testDeleteExtra() {
    // Créer un faux dossier et fichier zip pour tester
    QString base = "test_data/testToDelete";
    QDir().mkpath(base);
    QString zipPath = base + ".zip";

    QFile dummy(zipPath);
    dummy.open(QIODevice::WriteOnly);
    dummy.write("zip");
    dummy.close();

    std::string path = base.toStdString() + "Folder";
    QDir().rename(base, QString::fromStdString(path));

    FileUtils::delete_extra(path);
    QVERIFY(!QFile::exists(QString::fromStdString(path)));
    QVERIFY(!QFile::exists(zipPath));
}


