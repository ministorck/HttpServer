#include "http.h"
#include <QHttpMultiPart>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QFileInfo>
#include <QDebug>
#include "globaldata.h"
QString Http::m_dest;
QString Http::m_addr;
Http::Http()
{

}
QByteArray Http::Post(QByteArray data,
                      bool isAsync)
{
    QNetworkAccessManager manager;
    QEventLoop eventLoop;
    QObject::connect(&manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkRequest request;
    request.setUrl(QUrl(m_dest));
    s_printLog->writeLog(QString(__FUNCTION__).append("() - ") + QString("Url: %1, Request: %2").arg(m_dest).arg(QString(data)));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");

    QNetworkReply *reply = manager.post(request, data);
    if(!isAsync)
        eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
    else
        eventLoop.exec();
    QByteArray response;
    if (reply->error() == QNetworkReply::NoError) {
        response = reply->readAll();
        s_printLog->writeLog(QString(__FUNCTION__).append("() - ") + QString("Response: %1").arg(QString(response)));
    } else {
        //failure
        s_printLog->writeLog(QString(__FUNCTION__).append("() - ") + QString("Network Ex: %1").arg(reply->errorString()));
    }
    reply->deleteLater();
    return response;
}
QByteArray Http::Get(QByteArray data,
                     bool isAsync)
{
    QNetworkAccessManager manager;
    QEventLoop eventLoop;
    QObject::connect(&manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkRequest request;
    if(data.isEmpty())
        request.setUrl(QUrl(m_dest));
    else
        request.setUrl(QUrl(m_dest + "?" + data));
    s_printLog->writeLog(QString(__FUNCTION__).append("() - ") + QString("Url: %1, Request: %2").arg(m_dest).arg(QString(data)));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded; charset=utf-8");
    QNetworkReply *reply = manager.get(request);
    if(!isAsync)
        eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
    else
        eventLoop.exec();
    QByteArray response;
    if (reply->error() == QNetworkReply::NoError) {
        response = reply->readAll();
        s_printLog->writeLog(QString(__FUNCTION__).append("() - ") + \
            QString("Response: %1").arg(QString(response)));
    } else {
        //failure
        s_printLog->writeLog(QString(__FUNCTION__).append("() - ") + \
            QString("Network Ex: %1").arg(reply->errorString()));
    }
    reply->deleteLater();
    return response;
}

bool Http::DownloadFile(QByteArray data,
                        QObject *receiver)
{
    QNetworkAccessManager manager;
    QEventLoop eventLoop;
    QObject::connect(&manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkRequest request;
    if(data.isEmpty())
        request.setUrl(QUrl(m_dest));
    else
        request.setUrl(QUrl(m_dest + "?" + data));
    s_printLog->writeLog(QString(__FUNCTION__).append("() - ") + QString("Url: %1, Request: %2").arg(m_dest).arg(QString(data)));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded; charset=utf-8");
    QNetworkReply *reply = manager.get(request);
//    DownloadFileDialog *dialog = qobject_cast<DownloadFileDialog *>(receiver);
//    if(dialog != NULL)
//    {
//        dialog->setNetworkReply(reply);
//        QObject::connect(reply, SIGNAL(downloadProgress(qint64,qint64)), dialog, SLOT(downloadProgress(qint64,qint64)));
//        QObject::connect(reply, SIGNAL(readyRead()), dialog, SLOT(downloadRead()));
//    }
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
    bool bRet = false;
    if (reply->error() == QNetworkReply::NoError) {
        bRet = true;
    } else {
        //failure
        s_printLog->writeLog(QString(__FUNCTION__).append("() - ") + \
            QString("Network Ex (download fail): %1").arg(reply->errorString()));
    }
    reply->deleteLater();
    return bRet;
}

QByteArray Http::UploadFile(const QString &filePath,
                            QByteArray data,
                            QObject *sender)
{
    QByteArray response;
    QNetworkAccessManager manager;
    QEventLoop eventLoop;
    QObject::connect(&manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart filePart;
    QFileInfo file_info(filePath);
    QString suffix = file_info.suffix();
    if(suffix.compare("png", Qt::CaseInsensitive) == 0)
    {
        filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/png; charset=utf-8"));
    }
    else if(suffix.compare("jpg", Qt::CaseInsensitive) == 0 || suffix.compare("jpeg", Qt::CaseInsensitive) == 0)
    {
        filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg; charset=utf-8"));
    }
    else if(suffix.compare("gif", Qt::CaseInsensitive) == 0)
    {
        filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/gif; charset=utf-8"));
    }
    else if(suffix.compare("apk", Qt::CaseInsensitive) == 0)
    {
        filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/vnd.android.package-archive; charset=utf-8"));
    }
    else if(suffix.compare("mp3", Qt::CaseInsensitive) == 0)
    {
        filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("audio/mp3; charset=utf-8"));
    }
    else if(suffix.compare("mp4", Qt::CaseInsensitive) == 0)
    {
        filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("video/mpeg4; charset=utf-8"));
    }
    else if(suffix.compare("avi", Qt::CaseInsensitive) == 0)
    {
        filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("video/avi; charset=utf-8"));
    }
    else
    {
        s_printLog->writeLog(QString(__FUNCTION__).append("() - ") + \
            QString("File(%1) format unknown").arg(filePath));
        return response;
    }
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"" + file_info.fileName() + "\"; filename=\"" + file_info.fileName() + "\""));
    QFile *file = new QFile(filePath);
    file->open(QIODevice::ReadOnly);
    filePart.setBodyDevice(file);
    file->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart
    multiPart->append(filePart);
    QNetworkRequest request;
    request.setUrl(QUrl(m_dest + "?" + data));
    s_printLog->writeLog(QString(__FUNCTION__).append("() - ") + \
        QString("Url: %1, Request: %2").arg(m_dest).arg(QString(data)));
    QNetworkReply *reply = manager.post(request, multiPart);
//    UploadFileDialog *dialog = qobject_cast<UploadFileDialog *>(sender);
//    if(dialog != NULL)
//    {
//        QObject::connect(reply, SIGNAL(uploadProgress(qint64,qint64)), dialog, SLOT(uploadProgress(qint64,qint64)));
//    }
    multiPart->setParent(reply); // delete the multiPart with the reply
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
    if (reply->error() == QNetworkReply::NoError) {
        response = reply->readAll();
        s_printLog->writeLog(QString(__FUNCTION__).append("() - ") + \
            QString("Response: %1").arg(QString(response)));
    } else {
        //failure
        s_printLog->writeLog(QString(__FUNCTION__).append("() - ") + \
            QString("Network Ex: %1").arg(reply->errorString()));
    }
    reply->deleteLater();
    return response;
}
int Http::GetBookInfo(const QString &barcode,
                      const QString &tag,
                      const QString &keyword,
                      QList<BookInfo>& books,
                      int &code)
{
    code = ErrorCode::NetworkException;
    QString url = "/Api/Book/Info";
    m_dest = m_addr + url;
    int ret = NetworkError;
    QJsonObject json;
    json.insert("barcode", barcode);
    json.insert("tag", tag);
    json.insert("keyword", keyword);
    QJsonDocument document;
    document.setObject(json);
    QByteArray response = Post(document.toJson(QJsonDocument::Compact), false);
    if(!response.isEmpty())
    {
        ret = NoError;
        QJsonParseError jsonError;
        QJsonDocument parseDoc = QJsonDocument::fromJson(response, &jsonError);  // 转化为 JSON 文档
        if (!parseDoc.isNull() && (jsonError.error == QJsonParseError::NoError)) {  // 解析未发生错误
            /// JSON 文档为对象
            if (parseDoc.isObject()) {
                QJsonObject object = parseDoc.object();
                if (object.contains("code")) {
                    QJsonValue value = object.value("code");
                    if (value.isDouble()) {
                        code = value.toVariant().toInt();
                    }
                }
                if (object.contains("info")) {
                    QJsonValue value = object.value("info");
                    if(value.isArray()){
                        QJsonArray array = value.toArray();
                        int size = array.size();
                        for(int i = 0; i < size; i++){
                            BookInfo book;
                            QJsonValue value = array.at(i);
                            if (value.isObject()) {
                                QJsonObject object= value.toObject();
                                if (object.contains("keyid")) {
                                    QJsonValue value = object.value("keyid");
                                    if (value.isDouble()) {
                                        book.keyid = value.toVariant().toInt();
                                    }
                                }
                                if (object.contains("type")) {
                                    QJsonValue value = object.value("type");
                                    if(value.isString()){
                                        book.type = value.toString();
                                    }
                                }
                                books.append(book);
                            }
                        }
                    }
                }
            }
        }
    }
    return ret;
}
int Http::DoubanBookInfo(const QString &par1,
                         const QString &par2,
                         int &code)
{
    code = ErrorCode::NetworkException;
    int ret = NetworkError;
    QString url = "/Api/Book/Info/Douban";
    m_dest = m_addr + url;
    QByteArray form;
    form.append("par1=" + par1 + "&");
    form.append("par2=" + par2);
    QByteArray response = Get(form, false);
    if(!response.isEmpty())
    {
        ret = NoError;
        QJsonParseError jsonError;
        QJsonDocument parseDoc = QJsonDocument::fromJson(response, &jsonError);  // 转化为 JSON 文档
        if (!parseDoc.isNull() && (jsonError.error == QJsonParseError::NoError)) {  // 解析未发生错误
            /// JSON 文档为对象
            if (parseDoc.isObject()) {
                QJsonObject object = parseDoc.object();
                if (object.contains("code")) {
                    QJsonValue value = object.value("code");
                    if (value.isDouble()) {
                        code = value.toVariant().toInt();
                    }
                }
            }
        }
    }
    return ret;
}
int Http::StartDownloadFile(const QString &uid,
                            const QString &token,
                            const int &keyid,
                            QObject* receiver,
                            int &code)
{
    //code = ErrorCode::NetworkException;
    int ret = NetworkError;
    QString url = "/Api/User/File/Download/Media";
    m_dest = m_addr + url;
    QByteArray form;
    form.append("keyid=" + QString::number(keyid) + "&");
    form.append("uid=" + uid + "&");
    form.append("token=" + token);
    bool bRet = DownloadFile(form, receiver);
    if(bRet)
    {
        code = ErrorCode::Success;
        ret = NoError;
    }
    return ret;
}

int Http::StartUploadFile(const QString &uid,
                          const QString &token,
                          const QString &filePath,
                          const int &index,
                          const int &total,
                          const QString &filetype,
                          const QString &desc,
                          QObject *sender,
                          int &code)
{
    code = ErrorCode::NetworkException;
    int ret = NetworkError;
    QString url = "/Api/User/File/Upload";
    m_dest = m_addr + url;
    QFileInfo file_info(filePath);
    QByteArray form;
    form.append("uid=" + uid + "&");
    form.append("token=" + token + "&");
    form.append("fileName=" + file_info.fileName() + "&");
    form.append("index=" + QString::number(index) + "&");
    form.append("total=" + QString::number(total) + "&");
    form.append("filetype=" + filetype + "&");
    form.append("desc=" + desc);
    QByteArray response = UploadFile(filePath, form, sender);
    if(!response.isEmpty())
    {
        ret = NoError;
        QJsonParseError jsonError;
        QJsonDocument parseDoc = QJsonDocument::fromJson(response, &jsonError);  // 转化为 JSON 文档
        if (!parseDoc.isNull() && (jsonError.error == QJsonParseError::NoError)) {  // 解析未发生错误
            /// JSON 文档为对象
            if (parseDoc.isObject()) {
                QJsonObject object = parseDoc.object();
                if (object.contains("code")) {
                    QJsonValue value = object.value("code");
                    if (value.isDouble()) {
                        code = value.toVariant().toInt();
                    }
                }
            }
        }
    }
    return ret;
}
