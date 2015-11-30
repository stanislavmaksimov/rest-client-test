#include <QCoreApplication>
#include "client.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Client client(QUrl("http://stas.pubsandbox.eterhost.ru/rest-test/public/api/"), &app);

    QObject::connect(&client, SIGNAL(received(InfoResponseData)),
                     &client, SLOT(requestAuth()));
    QObject::connect(&client, SIGNAL(received(AuthResponseData)),
                     &client, SLOT(requestUserInfo(AuthResponseData)));
    QObject::connect(&client, SIGNAL(received(UserInfoResponseData)),
                     &app, SLOT(quit()));
    QObject::connect(&client, SIGNAL(error(int,QString)),
                     &app, SLOT(quit()));

    if (client.requestInfo()) {
        return app.exec();
    }

    return -1;
}
