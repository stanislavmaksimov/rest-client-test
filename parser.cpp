#include "parser.h"
#include "data.h"

template <> int fromJsonValue(const QJsonValue& value)
{
    return value.toInt();
}

template <> QString fromJsonValue(const QJsonValue& value)
{
    return value.toString();
}

template <> QDateTime fromJsonValue(const QJsonValue& value)
{
    return QDateTime::fromString(value.toString(), "yyyy-MM-dd hh:mm:ss");
}

template <> InfoResponseData fromJsonValue(const QJsonValue& value)
{
    InfoResponseData result;
    if (value.isObject()) {
        const QJsonObject object = value.toObject();
        if (!object.isEmpty()) {
            if (object.contains("nameserver"))
                result.Name = fromJsonValue<QString>(object["nameserver"]);
            if (object.contains("version"))
                result.Version = fromJsonValue<QString>(object["version"]);
        }
    }
    return result;
}

template <> AuthResponseData fromJsonValue(const QJsonValue& value)
{
    AuthResponseData result;
    if (value.isObject()) {
        const QJsonObject object = value.toObject();
        if (!object.isEmpty()) {
            if (object.contains("token"))
                result.Token = fromJsonValue<QString>(object["token"]);
        }
    }
    return result;
}

template <> UserInfoSip fromJsonValue(const QJsonValue& value)
{
    UserInfoSip result;
    if (value.isObject()) {
        const QJsonObject object = value.toObject();
        if (!object.isEmpty()) {
            if (object.contains("uri"))
                result.Uri = fromJsonValue<QString>(object["uri"]);
            if (object.contains("registration_uri"))
                result.RegistrationUri = fromJsonValue<QString>(object["registration_uri"]);
            if (object.contains("username"))
                result.Login = fromJsonValue<QString>(object["username"]);
            if (object.contains("password"))
                result.Password = fromJsonValue<QString>(object["password"]);
        }
    }
    return result;
}

template <> UserInfoResponseData fromJsonValue(const QJsonValue& value)
{
    UserInfoResponseData result;
    if (value.isObject()) {
        const QJsonObject object = value.toObject();
        if (!object.isEmpty()) {
            if (object.contains("id"))
                result.Id = fromJsonValue<int>(object["id"]);
            if (object.contains("email"))
                result.Login = fromJsonValue<QString>(object["email"]);
            if (object.contains("first_name"))
                result.FirstName = fromJsonValue<QString>(object["first_name"]);
            if (object.contains("last_name"))
                result.LastName = fromJsonValue<QString>(object["last_name"]);
            if (object.contains("middle_name"))
                result.MiddleName = fromJsonValue<QString>(object["middle_name"]);
            if (object.contains("created_at"))
                result.CreatedAt = fromJsonValue<QDateTime>(object["created_at"]);
            if (object.contains("updated_at"))
                result.UpdatedAt = fromJsonValue<QDateTime>(object["updated_at"]);
            if (object.contains("sip"))
                result.Sip = fromJsonValue<UserInfoSip>(object["sip"]);
        }
    }
    return result;
}
