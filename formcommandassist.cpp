#include "formcommandassist.h"
#include "ui_formcommandassist.h"

FormCommandAssist::FormCommandAssist(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormCommandAssist)
{
    ui->setupUi(this);
}

FormCommandAssist::~FormCommandAssist()
{
    delete ui;
}
