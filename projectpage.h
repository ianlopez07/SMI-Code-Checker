#ifndef PROJECTPAGE_H
#define PROJECTPAGE_H

#include <QWidget>

namespace Ui {
class Projectpage;
}

class Projectpage : public QWidget
{
    Q_OBJECT

public:
    explicit Projectpage(QWidget *parent = nullptr);
    ~Projectpage();

public:
    Ui::Projectpage *ui;
};

#endif // PROJECTPAGE_H
