#include"fenprincipal.h"
#include"fensecondaire.h"

fenPrincipal::fenPrincipal() : QWidget()
{

    /* Partie 1 : définition de la classe*/

    QGroupBox* defClasse = new QGroupBox("Définition de la classe");
    nom = new QLineEdit("nom");
    classeMere = new QLineEdit("classe mère");

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("nom", nom);
    formLayout->addRow("classe mère", classeMere);

    defClasse->setLayout(formLayout);

    /* Partie 2 : options */

    headerName = new QLineEdit("");
    headerName->setText("HEADER_"+nom->text());

    QGridLayout* grid = new QGridLayout;

    QGroupBox* options = new QGroupBox("Options");
    proteger_inclu_multipes = new QCheckBox("Protéger le header contre les inclusions multiples :");
    proteger_inclu_multipes->setChecked(true);
    generer_constructeur = new QCheckBox("Générer le constructeur");
    generer_constructeur->setChecked(true);
    generer_destructeur = new QCheckBox("Générer le destructeur");
    generer_destructeur->setChecked(true);
    ajouter_header = new QCheckBox("Inclure des headers");
    ajouter_attribut = new QCheckBox("Ajouter des attributs");

    // Quatre éléments qui servent si on veut ajouter des headers.
    nameAddHeader = new QLineEdit();
    buttonAddHeader = new QPushButton("Add");
    listHeaderToAdd = new QListWidget();
    buttonRemoveHeader = new QPushButton("Remove");

    nameAddHeader->setVisible(false);
    buttonAddHeader->setVisible(false);
    listHeaderToAdd->setVisible(false);
    buttonRemoveHeader->setVisible(false);

    // Quatre éléments qui servent si on veut ajouter des attributs.
    nameAddAttribut = new QLineEdit();
    buttonAddAttribut = new QPushButton("Add");
    listAttributToAdd = new QListWidget();
    buttonRemoveAttribut = new QPushButton("Remove");

    nameAddAttribut->setVisible(false);
    buttonAddAttribut->setVisible(false);
    listAttributToAdd->setVisible(false);
    buttonRemoveAttribut->setVisible(false);

    // Mise en place de la grille pour placer les éléments
    grid->addWidget(proteger_inclu_multipes,0,0);
    grid->addWidget(headerName, 0,1);
    grid->addWidget(generer_constructeur,1,0);
    grid->addWidget(generer_destructeur,2,0);

    grid->addWidget(ajouter_header,3,0);
    grid->addWidget(nameAddHeader,4,0);
    grid->addWidget(buttonAddHeader,5,0);
    grid->addWidget(listHeaderToAdd,4,1);
    grid->addWidget(buttonRemoveHeader,5,1);

    grid->addWidget(ajouter_attribut,6,0);
    grid->addWidget(nameAddAttribut,7,0);
    grid->addWidget(buttonAddAttribut,8,0);
    grid->addWidget(listAttributToAdd,7,1);
    grid->addWidget(buttonRemoveAttribut,8,1);

    options->setLayout(grid);


    /* Partie 3 : commentaires */

    commentaires = new QGroupBox("commentaires");
    commentaires->setCheckable(true);
    commentaires->setChecked(false);

    auteur = new QLineEdit("auteur");
    date = new QDateEdit();
    date->setDate(QDate::currentDate());
    date->setDisplayFormat("MMMM d yy");
    role = new QTextEdit("role");
    QFormLayout *formLayout2 = new QFormLayout;
    formLayout2->addRow("auteur", auteur);
    formLayout2->addRow("date", date);
    formLayout2->addRow("role", role);

    commentaires->setLayout(formLayout2);


    /* Boutons */
    generer = new QPushButton("Génerer");
    quitter = new QPushButton("Quitter");

     /* Partie 4 : layout de toute la fenetre */
    QVBoxLayout *vbox4 = new QVBoxLayout(this);
    vbox4->addWidget(defClasse);
    vbox4->addWidget(options);
    vbox4->addWidget(commentaires);
    vbox4->addWidget(generer);
    vbox4->addWidget(quitter);

    resize(750, 750);
    QWidget::connect(quitter, SIGNAL(pressed()), this, SLOT(close()));
    QWidget::connect(generer, SIGNAL(pressed()), this, SLOT(slot_generer()));
    QWidget::connect(proteger_inclu_multipes, SIGNAL(stateChanged(int)), this, SLOT(slot_header(int)));
    QWidget::connect(nom, SIGNAL(textChanged(QString)), this, SLOT(slot_headerName(QString)));

    /* ajouter HEADER */
    QWidget::connect(ajouter_header, SIGNAL(stateChanged(int)), this, SLOT(slot_addHeader(int)));
    QWidget::connect(buttonAddHeader, SIGNAL(pressed()), this, SLOT(slot_addHeader()));
    QWidget::connect(nameAddHeader, SIGNAL(returnPressed()), this, SLOT(slot_addHeader()));
    QWidget::connect(buttonRemoveHeader, SIGNAL(pressed()), this, SLOT(slot_removeHeader()));
    QWidget::connect(listHeaderToAdd, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(slot_removeHeader(QListWidgetItem*)));

    /* ajouter Attributs */
    QWidget::connect(ajouter_attribut, SIGNAL(stateChanged(int)), this, SLOT(slot_addAttribut(int)));
    QWidget::connect(buttonAddAttribut, SIGNAL(pressed()), this, SLOT(slot_addAttribut()));
    QWidget::connect(nameAddAttribut, SIGNAL(returnPressed()), this, SLOT(slot_addAttribut()));
    QWidget::connect(buttonRemoveAttribut, SIGNAL(pressed()), this, SLOT(slot_removeAttribut()));
    QWidget::connect(listAttributToAdd, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(slot_removeAttribut(QListWidgetItem*)));

}

void fenPrincipal::slot_generer()
{
    // On vérifie que le nom de la classe n'est pas vide, sinon on arrête
    if (nom->text().isEmpty() || headerName->text().isEmpty())
    {
        QMessageBox::critical(this, "Erreur", "Veuillez entrer au moins un nom de classe, ainsi qu'un nom de header si la case est cochée.");
        return; // Arrêt de la méthode
    }

    // Si tout va bien, on génère le code
    QString code = "";
    QString codeCpp = "#include ";
    codeCpp += '"' + nom->text() + ".h" + '"' + "\n";


    if(commentaires->isChecked())
    {
        code += "/*\nAuteur : " + auteur->text() + "\n";
        code += "Date de création : " + date->date().toString() + "\n"+ "\n";
        code += "Role : \n" + role->toPlainText() + "\n*/ \n";
    }

    if(proteger_inclu_multipes->isChecked())
    {
        code += "#ifndef " + headerName->text() + "\n";
        code += "#define " + headerName->text() + "\n";
    }

    if (ajouter_header->isChecked())
    {
        for (int i = 0 ; i<listHeaderToAdd->count() ; i++)
        {
            code += "#include <" +listHeaderToAdd->item(i)->text() + ">\n";
        }

    }

    if(classeMere->text().isEmpty())
    {
        code += "class " + nom->text() + "\n";
    }

    else
    {
        code += "class " + nom->text() +" : public " + classeMere->text() + "\n";
    }

    code += "{ \n   public:\n";

    if(generer_constructeur->isChecked())
    {
        code += "       " + nom->text() + "();";
        codeCpp += nom->text() + "::" + nom->text() + "()";

        if(!(classeMere->text().isEmpty()))
        {
            codeCpp += " : " + classeMere->text() + "()";
        }
        codeCpp += "\n{\n";
        codeCpp += "   \n";
        codeCpp += "}\n";
    }

    if (ajouter_attribut->isChecked())
    {
        bool* espacePasse = new bool;
        *espacePasse = false;
        QString *type = new QString();
        QString *s_nom = new QString();
        for (int i = 0 ; i<listAttributToAdd->count() ; i++)
        {
            *type = "";
            *s_nom = "";
            *espacePasse = false;
            for (int j = 0 ; j<listAttributToAdd->item(i)->text().size() ; j++)
            {
                if (listAttributToAdd->item(i)->text()[j] == " ")
                {
                    *espacePasse = true;
                    j++;
                }
                if (*espacePasse)
                {
                    *s_nom += listAttributToAdd->item(i)->text()[j];
                }
                else
                {
                    *type += listAttributToAdd->item(i)->text()[j];
                }
            }

            QString *s_nom_upper = new QString();
            *s_nom_upper = *s_nom;
            s_nom_upper->replace(0, 1, s_nom->toUpper().remove(1, s_nom->size()));

            code += "\n       "  + *type + " get" + *s_nom_upper + "() { return this." + *s_nom + "; }";
            code += "\n       void set" + *s_nom_upper + "(" + *type + " " + *s_nom + ") { this." + *s_nom + " = " + *s_nom + "; }";

            delete s_nom_upper;
        }
        delete espacePasse;
        delete s_nom;
        delete type;

    }

    if(generer_destructeur->isChecked())
    {
        code += "\n       ~" + nom->text() + "();";
        codeCpp += "\n" + nom->text() + "::" + "~" + nom->text() + "()\n{  \n\n}";
    }
    code += "\n\n\n   protected:";

    if (ajouter_attribut->isChecked())
    {
        for (int i = 0 ; i<listAttributToAdd->count() ; i++)
        {
            code += "\n       " +listAttributToAdd->item(i)->text() + ";";
        }

    }
    code += "\n\n\n   private:\n";
    code += "};\n\n";

    if(proteger_inclu_multipes->isChecked())
    {
        code += "#endif";
    }

    // Génération du code à l'aide des informations de la fenêtre
    // …

    // On crée puis affiche la fenêtre qui affichera le code généré, qu'on lui envoie en paramètre
    nomH = new QString;
    *nomH = nom->text()+".h";
    nomCpp = new QString;
    *nomCpp = nom->text()+".cpp";
    fenSecondaire* fenetreCode = new fenSecondaire(code, codeCpp, nomH, nomCpp, this);
    delete nomH;
    delete nomCpp;
    fenetreCode->exec();
}

void fenPrincipal::slot_header(int state)
{
    if (state == Qt::Checked)
    {
        headerName->setVisible(true);
        headerName->setText("HEADER_"+nom->text());

    }
    else if (state == Qt::Unchecked)
    {
        headerName->setVisible(false);
    }
}

void fenPrincipal::slot_headerName(QString newText)
{
    headerName->setText("HEADER_"+newText);
}

void fenPrincipal::slot_addHeader(int state)
{
    if(state == Qt::Unchecked)
    {
        nameAddHeader->setVisible(false);
        buttonAddHeader->setVisible(false);
        listHeaderToAdd->setVisible(false);
        buttonRemoveHeader->setVisible(false);
    }
    else if (state == Qt::Checked)
    {
        nameAddHeader->setVisible(true);
        buttonAddHeader->setVisible(true);
        listHeaderToAdd->setVisible(true);
        buttonRemoveHeader->setVisible(true);
    }
}

void fenPrincipal::slot_addHeader()
{
    if (nameAddHeader->text().isEmpty())
    {
        QMessageBox::critical(this, "Erreur", "Veuillez entrer le nom du header.");
        return;
    }

    listHeaderToAdd->addItem(nameAddHeader->text());
    nameAddHeader->clear();
}

void fenPrincipal::slot_removeHeader()
{
    if(listHeaderToAdd->currentRow() == -1)
    {
        QMessageBox::critical(this, "Erreur", "Veuillez sélectionner un header à supprimer.");
        return;
    }
    listHeaderToAdd->takeItem(listHeaderToAdd->currentRow());
}

void fenPrincipal::slot_removeHeader(QListWidgetItem* item)
{
    listHeaderToAdd->takeItem(listHeaderToAdd->row(item));
}

void fenPrincipal::slot_addAttribut()
{
    if (nameAddAttribut->text().isEmpty() || nameAddAttribut->text().count(" ") != 1 || nameAddAttribut->text()[0] == " ")
    {
        QMessageBox::critical(this, "Erreur", "Veuillez entrer le nom de l'attribut sous la forme 'type nom'.");
        return;
    }

    listAttributToAdd->addItem(nameAddAttribut->text());
    nameAddAttribut->clear();

}
void fenPrincipal::slot_removeAttribut()
{
    if(listAttributToAdd->currentRow() == -1)
    {
        QMessageBox::critical(this, "Erreur", "Veuillez sélectionner un attribut à supprimer.");
        return;
    }
    listAttributToAdd->takeItem(listAttributToAdd->currentRow());

}
void fenPrincipal::slot_removeAttribut(QListWidgetItem* item)
{
    listAttributToAdd->takeItem(listAttributToAdd->row(item));
}

void fenPrincipal::slot_addAttribut(int state)
{
    if(state == Qt::Unchecked)
    {
        nameAddAttribut->setVisible(false);
        buttonAddAttribut->setVisible(false);
        listAttributToAdd->setVisible(false);
        buttonRemoveAttribut->setVisible(false);
    }
    else if (state == Qt::Checked)
    {
        nameAddAttribut->setVisible(true);
        buttonAddAttribut->setVisible(true);
        listAttributToAdd->setVisible(true);
        buttonRemoveAttribut->setVisible(true);
    }

}
