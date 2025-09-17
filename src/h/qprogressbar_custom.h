#ifndef QPROGRESSBAR_CUSTOM_H
#define QPROGRESSBAR_CUSTOM_H

#include <QProgressBar>
#include <QLabel>
#include <QVBoxLayout>

class QProgressBar_custom : public QProgressBar
{
    Q_OBJECT

public:
    explicit QProgressBar_custom(QWidget *parent = nullptr);
    void updateProgress(int pourcentage, const QString &taskName);

private:
    QProgressBar* progressBar;
    QLabel* nomTache;
};

#endif // QPROGRESSBAR_CUSTOM_H
