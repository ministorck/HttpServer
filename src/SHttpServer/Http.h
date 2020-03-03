#ifndef HTTP_H
#define HTTP_H

#include <QObject>
#include <QString>
#include "globaldata.h"
#define HTTP_COMMAND_LOGIN 0
#define HTTP_COMMAND_BOOKINFO 1
#define HTTP_COMMAND_CONVERTTAG 2
#define HTTP_COMMAND_GETACCOUNTS 3
#define HTTP_COMMAND_GETWORKLOAD 4
#define HTTP_COMMAND_REGACCOUNT 5
#define HTTP_COMMAND_BORROWERINFO 8
#define HTTP_COMMAND_REGBORROWER 9

class Http
{
public:
    enum ErrorType
    {
        NoError = 0,
        ResponseError,
        NetworkError
    };

    Http();

    static void setAddr(QString addr)
    { m_addr = addr; }
    static QByteArray Post(QByteArray,bool isAsync = true);
    static QByteArray Get(QByteArray,bool isAsync = true);
    static bool DownloadFile(QByteArray,QObject* receiver);
    static QByteArray UploadFile(const QString &filePath,
                                 QByteArray,
                                 QObject *sender);
    static int DoubanBookInfo(const QString& par1,
                              const QString& par2,
                              int& code);
    static int GetBookInfo(const QString& barcode,
                           const QString& tag,
                           const QString& keyword,
                           QList<BookInfo>& books,
                           int& code);
    static int StartDownloadFile(const QString& uid,
                                 const QString& token,
                                 const int& keyid,
                                 QObject* receiver,
                                 int& code);
    static int StartUploadFile(const QString& uid,
                               const QString& token,
                               const QString& filePath,
                               const int& index,
                               const int& total,
                               const QString& filetype,
                               const QString& desc,
                               QObject *sender,
                               int& code);
private:
    static QString m_addr;
    static QString m_dest;
};

#endif // HTTP_H
