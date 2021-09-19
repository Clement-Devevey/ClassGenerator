#include "fensecondaire.h"

fenSecondaire::fenSecondaire(const QString& codeH, const QString& codeCpp, QString* const nomPageH, QString* const nomPageCpp,QWidget *parent) : QDialog(parent)
{
    pageH = new QTextEdit;
    pageH->setPlainText(codeH);
    pageH->setReadOnly(true);
    pageH->setFont(QFont("Courier"));
    pageH->setLineWrapMode(QTextEdit::NoWrap);

    pageCpp = new QTextEdit;
    pageCpp->setPlainText(codeCpp);
    pageCpp->setReadOnly(true);
    pageCpp->setFont(QFont("Courier"));
    pageCpp->setLineWrapMode(QTextEdit::NoWrap);

    enregistrer = new QPushButton("enregistrer");
    fermer = new QPushButton("fermer");
    setWindowTitle("ClassGenerator");
    QTabWidget* onglets = new QTabWidget;
    onglets->addTab(pageH, *nomPageH);
    onglets->addTab(pageCpp, *nomPageCpp);

    QHBoxLayout* buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(enregistrer);
    buttonsLayout->addWidget(fermer);

    QGridLayout* grid = new QGridLayout(this);
    grid->addWidget(onglets, 0, 0);
    grid->addLayout(buttonsLayout, 1, 0);
    setLayout(grid);
    connect(fermer, SIGNAL(clicked()), this, SLOT(accept()));
    connect(enregistrer, SIGNAL(clicked()), this, SLOT(slot_enregistrer()));
    resize(400,450);

    nomFichierH = new QString;
    *nomFichierH = *nomPageH;
    nomFichierCpp = new QString;
    *nomFichierCpp = *nomPageCpp;
    textH = new QString;
    *textH = codeH;
    textCpp = new QString;
    *textCpp = codeCpp;


}

void fenSecondaire::slot_enregistrer()
{
    QString fileH = QFileDialog::getSaveFileName(this, *nomFichierH, *nomFichierH, "header (*.h)");
    QFile fileh (fileH);
    if ( fileh.open(QIODevice::WriteOnly) )
    {
        QTextStream stream( &fileh );
        stream << *textH << endl;
    }

    QString fileCPP = QFileDialog::getSaveFileName(this, *nomFichierCpp, *nomFichierCpp, "cpp (*.cpp)");
    QFile fileCpp (fileCPP);
    if ( fileCpp.open(QIODevice::WriteOnly) )
    {
        QTextStream stream( &fileCpp );
        stream << *textCpp << endl;
    }

}
