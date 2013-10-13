#include <QtCore>
#include <QtNetwork>
#include "client.h"

Client::Client() {

}

void Client::startRequest(QUrl url) {
  QFileInfo fileInfo(url.path());
  QString fileName = fileInfo.fileName();
  if (fileName.isEmpty())
    fileName = "index.html";
  file = new QFile(fileName);
  if (!file->open(QIODevice::WriteOnly)) {
    delete file;
    file = nullptr;
    return;
  }

  reply = nam.get(QNetworkRequest(url));
  connect(reply, SIGNAL(readyRead()), SLOT(httpReadyRead()));
  connect(reply, SIGNAL(finished()), SLOT(httpFinished()));
}

void Client::httpReadyRead() {
  file->write(reply->readAll());
}

void Client::httpFinished() {
  file->flush();
  file->close();
  reply->deleteLater();
  reply = nullptr;
  qApp->exit();
}
