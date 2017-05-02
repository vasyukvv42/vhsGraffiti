#ifndef VKDOCUPLOADER_H
#define VKDOCUPLOADER_H

#include <QObject>
#include <QUrlQuery>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QMessageBox>

class VKDocUploader : public QObject
{
    Q_OBJECT
public:
    explicit VKDocUploader(const QString &token, const QString &path,
                           const QString &title, QObject *parent = 0);
    void uploadGraffiti();
    QString getUploadServer(bool graffiti = false);
    QString uploadDoc(const QString &server);
    void docSave(const QString &fileString);
private:
    QString m_accessToken;
    QString m_filePath;
    QString m_docTitle;
    QNetworkAccessManager m_accessManager;
};

#endif // VKDOCUPLOADER_H
