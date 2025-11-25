#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    User(QString& name);

    void setName();
    void getName();

private:
    QString Name;

};

#endif // USER_H
