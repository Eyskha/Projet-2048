#ifndef GRILLE_H
#define GRILLE_H
#include <iostream>
#include <QColor>
using namespace std;

#include <QObject>

class Grille : public QObject
{
    Q_OBJECT
public:
    explicit Grille(int l, int c, int i, QObject *parent = nullptr);
    Q_INVOKABLE void mouvUp();
    Q_INVOKABLE void mouvDown();
    Q_INVOKABLE void mouvLeft();
    Q_INVOKABLE void mouvRight();
    Q_INVOKABLE void newgame();
    void newTile();
    void initGrid();
    void majListeCases();
    void majListeCouleurs();
    bool testfinpartie();
    void partietermine();

    Q_PROPERTY(QList<QString> cases MEMBER listeCases NOTIFY caseChanged)
    Q_PROPERTY(QList<QColor> couleurs MEMBER listeCouleurs NOTIFY caseChanged)
    Q_PROPERTY(qint32 score MEMBER Score NOTIFY caseChanged)
    Q_PROPERTY(QString fin MEMBER Fingame NOTIFY caseChanged)
    Q_PROPERTY(qint32 opacite MEMBER opacite NOTIFY caseChanged)

    Q_PROPERTY(qint32 largeur MEMBER L NOTIFY sizeChanged)
    Q_PROPERTY(qint32 hauteur MEMBER C NOTIFY sizeChanged)

signals:
    void caseChanged();
    void sizeChanged();

private:
    int L;
    int C;
    int ** contenu;
    QList<QString> listeCases;
    QList<QColor> listeCouleurs;
    QList<QColor> paletteCouleurs;
    qint32 Score = 0;
    QString Fingame;
    int initiatedTiles;
    bool test;
    bool findepartie;
    int opacite = 0;
};

#endif // GRILLE_H
