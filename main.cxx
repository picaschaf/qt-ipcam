#include <QtCore>
#include <QtNetwork>


int main(int argc, char** argv)
{
    QCoreApplication app { argc, argv };

    QString username = "admin";
    QString password = "";
    QString concatenated = username + ":" + password;
    QByteArray data = concatenated.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;

    QNetworkAccessManager qnam { &app };
    QNetworkRequest req { QUrl { "http://192.168.1.93/image.jpg" } };
    req.setRawHeader("Authorization", headerData.toLocal8Bit());

    auto resp = qnam.get(req);
    while (!resp->isFinished())
        app.processEvents();

    auto result = resp->readAll();

    QFile f { "/home/picaschaf/image.jpg" };
    f.open(QIODevice::WriteOnly);
    f.write(result);
    f.close();

    qDebug() << "Finished";

    return app.exec();
}
