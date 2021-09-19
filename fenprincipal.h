#ifndef FENPRINCIPAL_H
#define FENPRINCIPAL_H

#include "fenprincipal.h"
#include<QWidget>
#include<QGroupBox>
#include<QLineEdit>
#include<QCheckBox>
#include<QPushButton>
#include<QDateEdit>
#include<QTextEdit>
#include<QVBoxLayout>
#include<QColor>
#include<QFormLayout>
#include<QMessageBox>
#include<QGridLayout>
#include<QListWidget>
#include<QStringList>




class fenPrincipal : public QWidget
{
    Q_OBJECT
public:
    fenPrincipal();
protected:

    /* création classe */
    QLineEdit* nom;
    QLineEdit* classeMere;

    /* OPTIONS */
    QCheckBox* proteger_inclu_multipes;
    QCheckBox* generer_constructeur;
    QCheckBox* generer_destructeur;
    QLineEdit* headerName;

    /* commentaires */
    QGroupBox* commentaires;
    QLineEdit* auteur;
    QDateEdit* date;
    QTextEdit* role;


    /* Boutons */
    QPushButton* generer;
    QPushButton* quitter;


    /* ajouter HEADER */
    QCheckBox* ajouter_header;
    QLineEdit* nameAddHeader;
    QPushButton* buttonAddHeader;
    QListWidget* listHeaderToAdd;
    QPushButton* buttonRemoveHeader;

    /* ajouter ATTRIBUTS */
    QCheckBox* ajouter_attribut;
    QLineEdit* nameAddAttribut;
    QPushButton* buttonAddAttribut;
    QListWidget* listAttributToAdd;
    QPushButton* buttonRemoveAttribut;
    QStringList* listAttribut;

    /* Gestion nom fichiers */
    QString* nomH;
    QString* nomCpp;


public slots:
    void slot_generer();
    void slot_header(int state);
    void slot_headerName(QString newText);

    /* ajouter HEADER */
    void slot_addHeader(int state);
    void slot_addHeader();
    void slot_removeHeader();
    void slot_removeHeader(QListWidgetItem* item);

    /* ATTRIBUT */
    void slot_addAttribut(int state);
    void slot_addAttribut();
    void slot_removeAttribut();
    void slot_removeAttribut(QListWidgetItem* item);


};

#endif
