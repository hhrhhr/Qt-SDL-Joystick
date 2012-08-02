#ifndef CHANNEL_H
#define CHANNEL_H

#include <QWidget>

namespace Ui {
class Channel;
}

class Channel : public QWidget
{
    Q_OBJECT
    
public:
    explicit Channel(int channelId,
                     QString name,
                     int joyId = -1,
                     int axisId = -1,
                     QWidget *parent = 0);
    ~Channel();
    void setVal(int value);
    
private:
    Ui::Channel *ui;
};

#endif // CHANNEL_H
