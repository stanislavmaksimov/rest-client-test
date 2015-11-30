#ifndef PARSER_H
#define PARSER_H

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

template <typename T> T fromJsonValue(const QJsonValue& value);

template <typename T> T fromJson(const QByteArray& value)
{
    QJsonDocument document = QJsonDocument::fromJson(value);
    if (document.isArray()) {
        return fromJsonValue<T>(document.array());
    }
    return fromJsonValue<T>(document.object());
}

#endif // PARSER_H
