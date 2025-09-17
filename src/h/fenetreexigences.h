#ifndef FENETREEXIGENCES_H
#define FENETREEXIGENCES_H

#include <QWidget>
#include <QListWidget>

class MainWindow; // déclaration anticipée pour éviter les inclusions circulaires

class FenetreExigences : public QWidget {
    Q_OBJECT

public:
    explicit FenetreExigences(MainWindow *mw, QWidget *parent = nullptr);
    void setExigences(const QStringList &exigences);

private:
    QListWidget *listeExigences;
    MainWindow *mainwindow;
};

#endif // FENETREEXIGENCES_H
