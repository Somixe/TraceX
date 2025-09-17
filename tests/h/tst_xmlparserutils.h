#ifndef TU_XMLPARSERUTILS_H
#define TU_XMLPARSERUTILS_H

#include <QtTest>
#include "../xmlparserutils.h"

class TU_XMLPARSERUTILS : public QObject {
    Q_OBJECT

private slots:
    void test_nettoyage_exigence_srs();
    void test_RGB_to_Color();

};

#endif // TU_XMLPARSERUTILS_H
