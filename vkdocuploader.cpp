#include "vkdocuploader.h"

VKDocUploader::VKDocUploader(const QString &token, const QString &path,
                             const QString &title, QObject *parent)
    : QObject(parent), m_accessToken(token), m_filePath(path)
{
    m_docTitle = QString(title + ".png").toUtf8();
}

void VKDocUploader::uploadGraffiti()
{
    QString graffitiServer(getUploadServer(true));
    if (graffitiServer.isEmpty()) {
        emit errorOccurred("Critical Error", "Couldn't get graffiti server URL");
        return;
    }

    QString docServer(getUploadServer());
    if (docServer.isEmpty()) {
        emit errorOccurred("Critical Error", "Couldn't get document server URL");
        return;
    }

    QString fileString(docUpload(graffitiServer));
    if (fileString.isEmpty()) {
        emit errorOccurred("Critical Error", "Couldn't upload graffiti to server");
        return;
    }

    QString saveReply(docSave(fileString));
    if (!saveReply.contains("response")) {
        emit errorOccurred("Unknown Error", saveReply);
        return;
    }

    fileString = docUpload(docServer);
    if (fileString.isEmpty()) {
        emit errorOccurred("Critical Error", "Couldn't upload graffiti to server");
        return;
    }

    saveReply = docSave(fileString);
    if (!saveReply.contains("response")) {
        emit errorOccurred("Unknown Error", saveReply);
        return;
    }

    emit uploadFinished();
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
    QJsonDocument jsonDocument;
    jsonDocument = QJsonDocument::fromJson(replyString.toUtf8());
    QJsonObject jsonObject = jsonDocument.object();
    jsonObject = jsonObject["response"].toObject();

    return jsonObject["upload_url"].toString();
}

QString VKDocUploader::docUpload(const QString &server)
{
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    multiPart->deleteLater();

    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                        QVariant("form-data; name=\"file\"; filename=\"" +
                                 m_docTitle + "\""));
    QFile *file = new QFile(m_filePath);
    file->open(QIODevice::ReadOnly);
    imagePart.setBodyDevice(file);

    multiPart->append(imagePart);

    QNetworkReply *reply;
    reply = m_accessManager.post(QNetworkRequest(server), multiPart);
    reply->deleteLater();

    QEventLoop loop;
    connect(reply, SIGNAL(readyRead()), &loop, SLOT(quit()));
    loop.exec();

    QString replyString(reply->readAll());
    QJsonDocument jsonDocument;
    jsonDocument = QJsonDocument::fromJson(replyString.toUtf8());
    QJsonObject jsonObject = jsonDocument.object();

    return jsonObject["file"].toString();
}

QString VKDocUploader::docSave(const QString &fileString)
{
    QUrl url("https://api.vk.com/method/docs.save");

    QUrlQuery query;
    query.addQueryItem("access_token", m_accessToken);
    query.addQueryItem("file", fileString);
    query.addQueryItem("title", m_docTitle);
    url.setQuery(query);

    QNetworkReply *reply;
    reply = m_accessManager.get(QNetworkRequest(url));
    reply->deleteLater();

    QEventLoop loop;
    connect(reply, SIGNAL(readyRead()), &loop, SLOT(quit()));
    loop.exec();

    QString replyString(reply->readAll());
    return replyString;
}
