#ifndef STYLE_EXIGENCE_H
#define STYLE_EXIGENCE_H

#include <QDialog>
#include "mainwindow.h"

#include "StyleCharacteristics.h"
#include "sss.h"


namespace Ui {
class style_exigence;
}

class style_exigence : public QDialog
{
    Q_OBJECT

public:
    style_exigence(QWidget *parent, QVector<Sss*> fichiers);
    ~style_exigence();



private slots:

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();


private:
    Ui::style_exigence *ui;
    QList<StyleFile> All_style_fichier;
    QVector<Sss*> fichiers_extraits;
    MainWindow* mainwindow;
    const int PAGE_SRS = 1;
    const int PAGE_SDD = 2;
    const int PAGE_SSS = 0;
};

#endif // STYLE_EXIGENCE_H
