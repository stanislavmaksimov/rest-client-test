#ifndef DATA_H
#define DATA_H

#include <QString>
#include <QDateTime>

struct InfoResponseData
{
    QString Name;
    QString Version;
};

struct AuthResponseData
{
    QString Token;
};

struct UserInfoSip
{
    QString Uri;
    QString RegistrationUri;
    QString Login;
    QString Password;
};

struct UserInfoResponseData
{
    int Id;
    QString Login;
    QString FirstName;
    QString MiddleName;
    QString LastName;
    QDateTime CreatedAt;
    QDateTime UpdatedAt;
    UserInfoSip Sip;
};

#endif // DATA_H
