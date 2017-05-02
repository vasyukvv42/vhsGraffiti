#include "vkdocuploader.h"

VKDocUploader::VKDocUploader(const QString &token, const QString &path,
                             const QString &title, QObject *parent)
    : QObject(parent), m_accessToken(token), m_filePath(path), m_docTitle(title)
{

}

void VKDocUploader::uploadGraffiti()
{

}

QString VKDocUploader::getUploadServer(bool graffiti)
{
    QUrl url("https://api.vk.com/method/docs.getUploadServer");

    QUrlQuery query;
    query.addQueryItem("access_token", m_accessToken);
    if (graffiti)
        query.addQueryItem("type", "graffiti");
    url.setQuery(query);

    QNetworkReply *reply;
    reply = m_accessManager.get(QNetworkRequest(url));
    reply->deleteLater();

    QEventLoop loop;
    connect(reply, SIGNAL(readyRead()), &loop, SLOT(quit()));
    loop.exec();

    QString replyString(reply->readAll());
    if (!replyString.contains("upload_url"))
        QMessageBox::critical(new QWidget(), "Unknown error", replyString);

    QJsonDocument jsonDocument;
    jsonDocument = QJsonDocument::fromJson(replyString.toUtf8());
    QJsonObject jsonObject = jsonDocument.object();
    jsonObject = jsonObject["response"].toObject();

    return jsonObject["upload_url"].toString();
}
