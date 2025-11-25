#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>

class Message
{
public:

    Message(QString* name, QString& text);

    void setText();

    QString getText();
    QString getName();

private:

    QString* NameOfSender;
    QString Text;

};

#endif // MESSAGE_H
