#include <QtTest>
#include "../rapport.h"
#include "../rapportligne.h"
#include "../sss.h"  // Inclure vos en-têtes pour Sss, Srs, Exigence, etc.
#include "../exigencesrs.h"
#include "../srs.h"
#include "../exigence.h"
#include "tst_rapport.h"

// Initialisation avant les tests
void TestRapport::initTestCase() {
    // Vous pouvez initialiser vos objets ici si nécessaire
}

// Test pour la méthode generation()
void TestRapport::testGeneration() {
    // Créez des objets factices (mock) pour les classes Sss, Srs, Exigence, etc.
    QVector<Sss*> listeDocSss;  // Liste simulée de documents SSS
    // Ajouter des objets Sss à la liste (vous pouvez les créer manuellement ou les mocker)

    Rapport rapport(listeDocSss);  // Créez un objet Rapport avec la liste simulée
    rapport.generation(listeDocSss);  // Exécutez la génération

    // Vérifiez si le rapport a bien généré les lignes
    QVERIFY(rapport.getLignesRapport().size() > 0);
}

// Test pour vérifier l'ajout de lignes au rapport
void TestRapport::testLignesRapport() {
    QVector<Sss*> listeDocSss;
    Rapport rapport(listeDocSss);

    // Création de données factices pour la ligne de rapport
    Rapportligne ligne=Rapportligne("SSS1", "SRS1", "SDD1", "exigence1", "exigence2", "exigence3");
    // Ajouter cette ligne à la liste
    rapport.getLignesRapport().push_back(ligne);

    // Vérifiez si la ligne a bien été ajoutée
    QCOMPARE(rapport.getLignesRapport().size(), 1);
    QCOMPARE(rapport.getLignesRapport().front().toString(), "SSS1;SRS1;SDD1;exigence1;exigence2;exigence3");
}

// Nettoyage après les tests
void TestRapport::cleanupTestCase() {
    // Libérez la mémoire ou effectuez toute autre opération nécessaire après les tests
}

void TestRapport::testIsInSrs() {
    // Créer une exigence factice
    ExigenceSrs exi = ExigenceSrs("exigence1",false);


    // Créer un document SRS factice
    Srs docSrs= Srs("");
    docSrs.addExigence(exi);


    Rapportligne rl;
    ExigenceSrs rtr = ExigenceSrs("", false);
    bool found = rl.isInSrs(&exi, docSrs, rtr);

    QVERIFY(found);  // Vérifiez si l'exigence a été trouvée dans le SRS
}


