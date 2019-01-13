#ifndef FORMCOMMANDASSIST_H
#define FORMCOMMANDASSIST_H

#include <QWidget>

namespace Ui {
class FormCommandAssist;
}

class FormCommandAssist : public QWidget
{
    Q_OBJECT

public:
    explicit FormCommandAssist(QWidget *parent = nullptr);
    ~FormCommandAssist();

private:
    Ui::FormCommandAssist *ui;
};

#endif // FORMCOMMANDASSIST_H
