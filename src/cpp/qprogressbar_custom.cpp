#include "QProgressBar_custom.h"
#include "style.h"
#include <QVBoxLayout>

QProgressBar_custom::QProgressBar_custom(QWidget *parent)
    : QProgressBar(parent)
{
    setWindowModality(Qt::ApplicationModal);
    this->setCancelButton(nullptr);
    progress->setWindowTitle("Veuillez patienter");
    progress->setMinimumDuration(0);
    progress->setRange(0, 0);  // Plage de 0 à 0 pour indiquer une barre indéterminée
    progress->setValue(0);  // Placer la barre à 0
    progress->setStyleSheet(Style::Style_progressBar());
}


void QProgressBar_custom::updateProgress(int pourcentage, const QString &taskName)
{
    progressBar->setValue(pourcentage);
    nomTache->setText(taskName);
}
