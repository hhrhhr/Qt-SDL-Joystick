#ifndef HAT_H
#define HAT_H

#include <QWidget>

namespace Ui {
class Hat;
}

class Hat : public QWidget
{
    Q_OBJECT
    
public:
    explicit Hat(QWidget *parent = 0);
    ~Hat();
    void setHat(qint8 pos);
    
private:
    Ui::Hat *ui;
};

#endif // HAT_H
