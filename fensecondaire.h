#ifndef FENSECONDAIRE_H
#define FENSECONDAIRE_H
#include<QDialog>
#include<QTextEdit>
#include<QPushButton>
#include<QLayout>
#include<QTabWidget>
#include<QFileDialog>
#include<QTextStream>

class fenSecondaire : public QDialog
{
    Q_OBJECT
public:
    fenSecondaire(const QString&  codeH, const QString& codeCpp, QString* const nomPageH, QString* const nomPageCpp, QWidget *parent = 0);
protected:
    QTextEdit* pageH;
    QTextEdit* pageCpp;
    QString* nomFichierH;
    QString* nomFichierCpp;
    QString* textH;
    QString* textCpp;
    QPushButton* fermer;
    QPushButton* enregistrer;

public slots:
    void slot_enregistrer();


};

#endif // FENSECONDAIRE_H
