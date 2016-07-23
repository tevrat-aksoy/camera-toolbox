#ifndef CAMERASERVER_H
#define CAMERASERVER_H

#include <QObject>

#include "camerathread.h"

#include <qhttpserver.hpp>
#include <qhttpserverrequest.hpp>
#include <qhttpserverresponse.hpp>

#include <QList>
#include <QMutex>

namespace hpis {

class CameraServer : public QObject
{
    Q_OBJECT
public:
    explicit CameraServer(CameraThread* cameraThread, QObject *parent = 0);
    
    
protected:
    void processRequest(qhttp::server::QHttpRequest* req, qhttp::server::QHttpResponse* res);

    void ctrlSet(QMap<QString, QString> params);
    QJsonDocument ctrlMode(QMap<QString, QString> params);
    void ctrlRec(QMap<QString, QString> params);
    void ctrlShutdown();

private:
    CameraThread* m_cameraThread;
    qhttp::server::QHttpServer m_httpServer;

    QMutex m_LiveViewListMutex;
    QList<qhttp::server::QHttpResponse*> m_liveViewList;
signals:

public slots:
    void responseDestroyed(QObject* resp);
    void previewAvailable(CameraPreview::Format format, QByteArray bytes);
};

}

#endif // CAMERASERVER_H
