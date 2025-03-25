#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QObject>

class QTcpSocket;
class QNetworkSession;

class Client : public QObject
{
    Q_OBJECT

public:
    Client();
    QString getTexte();

private slots:
    void lireTexte();
    void afficherErreur(QAbstractSocket::SocketError socketError);

public slots:
    void envoiTexte( const std::string& s);

private:
    QTcpSocket *m_tcpSocket;
    quint16 m_blockSize;
    QNetworkSession *m_networkSession;
    QString m_texte;
};

#endif

