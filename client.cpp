#include "client.h"
#include "logging.h"
#include "data.h"
#include "parser.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

const QUrl API_PATH_INFO("info");
const QUrl API_PATH_AUTH("authenticate");
const QUrl API_PATH_USERINFO("userinfo");

Client::Client(const QUrl& apiEndpoint, QObject *parent)
    : QObject(parent)
    , mApiEndpoint(apiEndpoint)
    , mNetworkAccessManager(new QNetworkAccessManager(this))
{
    LOG;
}

Client::~Client()
{
    LOG;
}

bool Client::requestInfo()
{
    if (this->mNetworkAccessManager->networkAccessible() == QNetworkAccessManager::Accessible) {
        const QNetworkRequest request(this->mApiEndpoint.resolved(API_PATH_INFO));
        if (QNetworkReply* reply = this->mNetworkAccessManager->get(request)) {
            connect(reply, SIGNAL(finished()), this, SLOT(onFinishedInfo()));
            return true;
        }
    }
    return false;
}

bool Client::requestAuth(const QString& login, const QString& password)
{
    if (this->mNetworkAccessManager->networkAccessible() == QNetworkAccessManager::Accessible) {
        QNetworkRequest request(this->mApiEndpoint.resolved(API_PATH_AUTH));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        if (QNetworkReply* reply = this->mNetworkAccessManager->post(request, QString("email=%1&password=%2").arg(login, password).toUtf8())) {
            connect(reply, SIGNAL(finished()), this, SLOT(onFinishedAuth()));
            return true;
        }
    }
    return false;
}

bool Client::requestUserInfo(const QString& token)
{
    if (this->mNetworkAccessManager->networkAccessible() == QNetworkAccessManager::Accessible) {
        QNetworkRequest request(this->mApiEndpoint.resolved(API_PATH_USERINFO));
        request.setRawHeader("Authorization", QString("Bearer %1").arg(token).toUtf8());
        if (QNetworkReply* reply = this->mNetworkAccessManager->get(request)) {
            connect(reply, SIGNAL(finished()), this, SLOT(onFinishedUserInfo()));
            return true;
        }
    }
    return false;
}

bool Client::requestUserInfo(const AuthResponseData& value)
{
    return this->requestUserInfo(value.Token);
}

void Client::onFinishedInfo()
{
    if (QNetworkReply* reply = qobject_cast<QNetworkReply*>(this->sender())) {
        if (reply->error() == QNetworkReply::NoError) {
            const InfoResponseData result = fromJson<InfoResponseData>(reply->readAll());
            LOG << reply << result.Name << result.Version;
            emit this->received(result);
        } else {
            LOG << reply->error() << reply->errorString();
            emit this->error(reply->error(), reply->errorString());
        }
    }
}

void Client::onFinishedAuth()
{
    if (QNetworkReply* reply = qobject_cast<QNetworkReply*>(this->sender())) {
        if (reply->error() == QNetworkReply::NoError) {
            const AuthResponseData result = fromJson<AuthResponseData>(reply->readAll());
            LOG << reply << result.Token;
            emit this->received(result);
        } else {
            LOG << reply->error() << reply->errorString();
            emit this->error(reply->error(), reply->errorString());
        }
    }
}

void Client::onFinishedUserInfo()
{
    if (QNetworkReply* reply = qobject_cast<QNetworkReply*>(this->sender())) {
        if (reply->error() == QNetworkReply::NoError) {
            const UserInfoResponseData result = fromJson<UserInfoResponseData>(reply->readAll());
            LOG << reply << result.Id << result.Login
                << result.FirstName << result.LastName << result.MiddleName
                << result.CreatedAt << result.UpdatedAt
                << result.Sip.Uri << result.Sip.RegistrationUri
                << result.Sip.Login << result.Sip.Password;
            emit this->received(result);
        } else {
            LOG << reply->error() << reply->errorString();
            emit this->error(reply->error(), reply->errorString());
        }
    }
}
