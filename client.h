#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QUrl>

class QNetworkAccessManager;
struct InfoResponseData;
struct AuthResponseData;
struct UserInfoResponseData;

class Client : public QObject
{
    Q_OBJECT

signals:
    void received(const InfoResponseData&);
    void received(const AuthResponseData&);
    void received(const UserInfoResponseData&);
    void error(int code, const QString& description);

public:
    explicit Client(const QUrl& apiEndpoint = QUrl("http://stas.pubsandbox.eterhost.ru/rest-test/public/api/"),
                    QObject *parent = 0);
    virtual ~Client();

public slots:
    bool requestInfo();
    bool requestAuth(const QString& login = "testuser", const QString& password = "testuser");
    bool requestUserInfo(const QString& token);
    bool requestUserInfo(const AuthResponseData&);

private slots:
    void onFinishedInfo();
    void onFinishedAuth();
    void onFinishedUserInfo();

private:
    const QUrl mApiEndpoint;
    QNetworkAccessManager* mNetworkAccessManager;
};

#endif // CLIENT_H
