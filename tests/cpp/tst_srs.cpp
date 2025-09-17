#include <QtTest>
#include "../srs.h"
#include "../exigencesrs.h"
#include "QtCore"
#include "tst_srs.h"
#include "../sss.h"

void TU_SRS::init()
{

    Srs::reinitialiserFiltres();
}

void TU_SRS::test_addEtGetExigence() {
    Srs srs("file.docx");
    ExigenceSrs e("E1", {}, {}, true, {"T1"});
    srs.addExigence(e);

    auto exigences = srs.getExigence();
    QCOMPARE(exigences.size(), 1);
    QCOMPARE(exigences[0].getId(), std::string("E1"));
}

void TU_SRS::test_isMatchesRadical()
{

    Srs srs("fichier.xlsx");
    Sss sss("sss.xlsx");

    // On simule le radical
    File::setRadical(".*");
    QVERIFY(File::getRadical() == ".*");



    // On simule une exigence avec un id de forme "ABC_001"
    Exigence ex("RAD1_001");
    Exigence ex2("RAD2_001");
    Exigence ex3("RAD3_001");
    sss.addExigence(ex);
    sss.addExigence(ex2);
    sss.addExigence(ex3);
    sss.getRadicaux();




    // Simule un ExigenceSrs avec un id RAD2_123
    ExigenceSrs exigence("RAD2_123", true);

    // Critères sélectionnés contenant "RAD2" → match attendu
    std::vector<std::string> criteres = {"RAD2"};

    bool resultat = srs.isMatchesRadical(exigence, criteres);
    QVERIFY(resultat); // Le test doit passer (true attendu)

    // Test avec un radical non contenu dans les attributs → pas de match
    std::vector<std::string> criteres_invalides = {"RADX"};
    bool resultat2 = srs.isMatchesRadical(exigence, criteres_invalides);
    QVERIFY(!resultat2); // false attendu
}


void TU_SRS::test_totalExigences() {
    Srs srs("fichier.docx");
    QVERIFY(srs.totalExigences() == 0);
    srs.addExigence(ExigenceSrs("X", {}, {}, false, {}));
    QCOMPARE(srs.totalExigences(), 1);
}

void TU_SRS::test_getFilsEtSetFils() {
    Srs srs("srs.docx");
    Sdd* sdd = new Sdd("sdd.docx");
    srs.setFils(sdd);
    QVERIFY(srs.hasFils());
    QCOMPARE(srs.getFils()->getPath(), std::string("sdd.docx"));
    delete sdd;
}

void TU_SRS::test_getIdsExigenceMatchesCriteres() {
    Srs srs("srs.xlsx");
    ExigenceSrs e("E123", {"UI"}, {"RAM"}, true, {"REQ-1", "REQ-2"});
    srs.addExigence(e);

    QStringList criteres;
    criteres << "UI";

    auto ids = srs.getIdsExigenceMatchesCriteres(criteres);
    QCOMPARE(ids.size(), 2);
    QCOMPARE(ids[0], "REQ-1");
    QCOMPARE(ids[1], "REQ-2");
}

void TU_SRS::test_toQStringExigence() {
    Srs srs("fichier.xlsx");
    srs.addExigence(ExigenceSrs("X1", {}, {}, false, {}));
    QString texte = srs.toQStringExigence();
    QVERIFY(texte.contains("X1"));
}


void TU_SRS::test_addFiltres()
{

    Srs::reinitialiserFiltres();
    Srs srs("");

    Srs::addFiltres("Critère1");

    QCOMPARE(Srs::getFiltres().size(), 1);
    QCOMPARE(Srs::getFiltres().at(0), QString("Critère1"));



    // Ajout d’un autre filtre
    Srs::addFiltres("Critère2");
    QCOMPARE(Srs::getFiltres().size(), 2);
    QCOMPARE(Srs::getFiltres().at(1), QString("Critère2"));

}



void TU_SRS::test_getRadicaux()
{

    Srs::reinitialiserFiltres();
    Srs srs = Srs("srs.xlsx");



    // On simule le radical
    File::setRadical(".*");
    QVERIFY(File::getRadical() == ".*");



    // On simule une exigence avec un id de forme "ABC_001"
    ExigenceSrs ex("ABC_001", true);



    srs.addExigence(ex);



    srs.getRadicaux();


    QVERIFY(Srs::getFiltres().contains("ABC"));
    QCOMPARE(Srs::getFiltres().size(), 1);
    // Vérification : "ABC" doit apparaître dans les filtres



}


void TU_SRS::testGetCriteres()
{
    Srs::reinitialiserFiltres();
    Srs srs = Srs("");

    ExigenceSrs ex1 = ExigenceSrs("id1", {"c1", "c2"}, {"n1"}, true, {"t1"});


    ExigenceSrs ex2 = ExigenceSrs("id2", {"c3", "c4"}, {"n2"}, true, {"t2"});


    srs.addExigence(ex1);
    srs.addExigence(ex2);

    srs.getCriteres();

    QStringList attendu = {
        "c1", "c2", "n1",
        "c3", "c4", "n2",
        "Développé"
    };

    for (const QString& critere : attendu) {
        QVERIFY2(Srs::getFiltres().contains(critere), qPrintable("Critère manquant : " + critere));
    }

    QCOMPARE(srs.getFiltres().size(), attendu.size());

}

void TU_SRS::test_extractExigences_word()
{
    QString basePath = QFileInfo(__FILE__).absolutePath(); // dossier du fichier source .cpp
    qDebug() << "basePath : "<<basePath;
    QString cheminTest = basePath + "/fichiers_test/SRS.docx";

    qDebug() << "chemin de test :" <<cheminTest;
    QVERIFY(QFile::exists(cheminTest)); // Assure que le fichier existe

    // 2. Créer l'objet Srs
    Srs srs = Srs(cheminTest.toStdString());


    // 3. Définir un style attendu dans le document
    StyleFile style = StyleFile("Exigence0", "", "", 0, "", false, false, false, false);

    srs.setStyle(style);

    // 4. Appel de la méthode à tester
    srs.extractExigences();

    // 5. Vérifier que les exigences ont bien été extraites
    int nbExigences = srs.totalExigences();
    QVERIFY(nbExigences >0); // On s'attend à au moins une exigence


    ExigenceSrs e = srs.getExigence()[0];
    QVERIFY(!e.getId().empty());
    QVERIFY(e.getTracabilite().size() > 0);
}

void TU_SRS::cleanup()
{
    Srs::reinitialiserFiltres(); // Nettoyage après chaque test
}
