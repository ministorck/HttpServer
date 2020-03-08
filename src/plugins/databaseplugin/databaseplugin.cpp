#include "databaseplugin.h"
#include <QDebug>

static QString replyTextFormat(
        "HTTP/1.1 %1 OK\r\n"
        "Content-Type: %2\r\n"
        "Content-Length: %3\r\n"
        "Access-Control-Allow-Origin: *\r\n"
        "Access-Control-Allow-Headers: Content-Type,X-Requested-With\r\n"
        "\r\n"
        "%4"
    );

static QString replyRedirectsFormat(
        "HTTP/1.1 %1 OK\r\n"
        "Content-Type: %2\r\n"
        "Content-Length: %3\r\n"
        "Access-Control-Allow-Origin: *\r\n"
        "Access-Control-Allow-Headers: Content-Type,X-Requested-With\r\n"
        "\r\n"
        "%4"
    );

static QString replyFileFormat(
        "HTTP/1.1 %1 OK\r\n"
        "Content-Disposition: attachment;filename=%2\r\n"
        "Content-Length: %3\r\n"
        "Access-Control-Allow-Origin: *\r\n"
        "Access-Control-Allow-Headers: Content-Type,X-Requested-With\r\n"
        "\r\n"
    );

static QString replyImageFormat(
        "HTTP/1.1 %1\r\n"
        "Content-Type: image\r\n"
        "Content-Length: %2\r\n"
        "Access-Control-Allow-Origin: *\r\n"
        "Access-Control-Allow-Headers: Content-Type,X-Requested-With\r\n"
        "\r\n"
    );

static QString replyBytesFormat(
        "HTTP/1.1 %1 OK\r\n"
        "Content-Type: application/octet-stream\r\n"
        "Content-Length: %2\r\n"
        "Access-Control-Allow-Origin: *\r\n"
        "Access-Control-Allow-Headers: Content-Type,X-Requested-With\r\n"
        "\r\n"
    );

static QString replyOptionsFormat(
        "HTTP/1.1 200 OK\r\n"
        "Allow: OPTIONS, GET, POST, PUT, HEAD\r\n"
        "Access-Control-Allow-Methods: OPTIONS, GET, POST, PUT, HEAD\r\n"
        "Content-Length: 0\r\n"
        "Access-Control-Allow-Origin: *\r\n"
        "Access-Control-Allow-Headers: Content-Type,X-Requested-With\r\n"
        "\r\n"
    );



DatabasePlugin::DatabasePlugin(QObject *parent) :
    QObject(parent)
{
}

void DatabasePlugin::insert(QString str)
{
    qDebug() << "DatabasePlugin::insert" << str;
}

QByteArray DatabasePlugin::responseData(QByteArray byte)
{
    buffer_ = byte;
    return inspectionBufferSetup();
}

QByteArray DatabasePlugin::inspectionBufferSetup()
{
    QByteArray ret = "";
    forever
    {
        static QByteArray splitFlag( "\r\n" );

        auto splitFlagIndex = buffer_.indexOf( splitFlag );
        // 没有获取到分割标记，意味着数据不全
        if ( splitFlagIndex == -1 )
        {
            // 没有获取到 method 但是缓冲区内已经有了数据，这可能是一个无效的连接
            if ( requestMethod_.isEmpty() && ( buffer_.size() > 4 ) )
            {
                this->deleteLater();
                return ret;
            }

            return ret;
        }

        // 如果未获取到 method 并且已经定位到了分割标记符，那么直接放弃这个连接
        if ( requestMethod_.isEmpty() && ( splitFlagIndex == 0 ) )
        {
            this->deleteLater();
            return ret;
        }

        // 如果没有获取到 method 则先尝试分析 method
        if ( requestMethod_.isEmpty() )
        {
            auto requestLineDatas = buffer_.mid( 0, splitFlagIndex ).split( ' ' );
            buffer_.remove( 0, splitFlagIndex + 2 );
            if ( requestLineDatas.size() != 3 )
            {
                this->deleteLater();
                return ret;
            }

            // 获取请求
            requestMethod_ = requestLineDatas.at( 0 );
            requestUrl_ = requestLineDatas.at( 1 );
            requestCrlf_ = requestLineDatas.at( 2 );

            if ( ( requestMethod_ != "GET" ) &&
                 ( requestMethod_ != "OPTIONS" ) &&
                 ( requestMethod_ != "POST" ) &&
                 ( requestMethod_ != "PUT" ) )
            {
                this->deleteLater();
                return ret;
            }
        }
        else if ( splitFlagIndex == 0 )
        {
            buffer_.remove( 0, 2 );
            if ( ( requestMethod_.toUpper() == "GET" ) ||
                 ( requestMethod_.toUpper() == "OPTIONS" ) ||
                 ( ( requestMethod_.toUpper() == "POST" ) && ( ( contentLength_ > 0 ) ? ( !buffer_.isEmpty() ) : ( true ) ) ) ||
                 ( ( requestMethod_.toUpper() == "PUT" ) && ( ( contentLength_ > 0 ) ? ( !buffer_.isEmpty() ) : ( true ) ) ) )
            {
                if(requestMethod_.toUpper() == "GET")
                {
                    return get_();
                }
                else if(requestMethod_.toUpper() == "PUT")
                {
                    return put_();
                }
                else if(requestMethod_.toUpper() == "POST")
                {
                    return post_();
                }
                else if(requestMethod_.toUpper() == "PATCH")
                {
                    return patch_();
                }
                else if(requestMethod_.toUpper() == "DELETE")
                {
                    return delete_();
                }
            }
        }
        else
        {
            auto index = buffer_.indexOf( ':' );

            if ( index <= 0 )
            {
                this->deleteLater();
                return ret;
            }

            auto headerData = buffer_.mid( 0, splitFlagIndex );

            buffer_.remove( 0, splitFlagIndex + 2 );

            const auto &&key = headerData.mid( 0, index );
            auto value = headerData.mid( index + 1 );
            if ( value.startsWith( ' ' ) )
            {
                value.remove( 0, 1 );
            }

            requestHeader_[ key ] = value;

            if ( key.toLower() == "content-length" )
            {
                contentLength_ = value.toLongLong();
            }
        }
    }
}

QByteArray DatabasePlugin::get_()
{
    QString data = "get code!!!";

    QByteArray data2 = replyTextFormat.arg(QString::number(200),
                                           QString("text;charset=UTF-8"),
                                           QString::number(data.toUtf8().size()),
                                           data).toUtf8();
    return data2;
}

QByteArray DatabasePlugin::put_()
{
    QString data = "put_ code!!!";
    QByteArray data2 = replyTextFormat.arg(QString::number(200),
                                           QString("application/json;charset=UTF-8"),
                                           QString::number(data.toUtf8().size()),
                                           data).toUtf8();
    return data2;
}

QByteArray DatabasePlugin::post_()
{
    QString data = "";
    QByteArray data2 = replyTextFormat.arg(QString::number(200),
                                           QString("application/json;charset=UTF-8"),
                                           QString::number(data.toUtf8().size()),
                                           data).toUtf8();
    return data2;
}

QByteArray DatabasePlugin::patch_()
{
    QString data = "";
    QByteArray data2 = replyTextFormat.arg(QString::number(200),
                                           QString("application/json;charset=UTF-8"),
                                           QString::number(data.toUtf8().size()),
                                           data).toUtf8();
    return data2;
}

QByteArray DatabasePlugin::delete_()
{
    QString data = "";
    QByteArray data2 = replyTextFormat.arg(QString::number(200),
                                           QString("application/json;charset=UTF-8"),
                                           QString::number(data.toUtf8().size()),
                                           data).toUtf8();
    return data2;
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(databaseplugin, DatabasePlugin)
#endif // QT_VERSION < 0x050000
