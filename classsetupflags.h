#ifndef CLASSSETUPFLAGS_H
#define CLASSSETUPFLAGS_H

#include <QObject>
#include <QQmlProperties>

#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QElapsedTimer>
#include <QUrl>

class ClassSetupFlags : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(bool countriesFile READ countriesFile WRITE setCountriesFile NOTIFY countriesFileChanged)

    Q_PROPERTY(QString downloadFilename READ downloadFilename WRITE setDownloadFilename NOTIFY downloadFilenameChanged)
    Q_PROPERTY(double downloadSpeed READ downloadSpeed WRITE setDownloadSpeed NOTIFY downloadSpeedChanged)
    Q_PROPERTY(qint64 totalBytes READ totalBytes WRITE setTotalBytes NOTIFY totalBytesChanged)
    Q_PROPERTY(qint64 receivedBytes READ receivedBytes WRITE setReceivedBytes NOTIFY receivedBytesChanged)
    Q_PROPERTY(QString unit READ unit WRITE setUnit NOTIFY unitChanged)


public:
    explicit ClassSetupFlags(QObject *parent = nullptr);

    Q_INVOKABLE void startDownloadGamesData(const QString &type);
    //Q_INVOKABLE void startDownloadFlags();

    void startDownload(const QUrl &url);
    static QString getDownloadBasename(const QUrl &url);

    bool countriesFile() const;
    void setCountriesFile(bool newCountriesFile);

    QString downloadFilename() const;
    void setDownloadFilename(const QString &newDownloadFilename);

    double downloadSpeed() const;
    void setDownloadSpeed(double newDownloadSpeed);

    qint64 totalBytes() const;
    void setTotalBytes(qint64 newTotalBytes);

    qint64 receivedBytes() const;
    void setReceivedBytes(qint64 newReceivedBytes);

    QString unit() const;
    void setUnit(const QString &newUnit);


signals:
    void countriesFileChanged();

    // Download information
    void downloadFilenameChanged();
    void downloadSpeedChanged();
    void totalBytesChanged();
    void receivedBytesChanged();
    void unitChanged();

    void errorOccurred(const QString &error);
    void finishedDownloadFlags();


private slots:
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void downloadFinished();
    void downloadReadyToRead();



private:

    bool m_countriesFile;
    QMap<QString, QString> codesMap;

    // Download information
    QString m_downloadFilename;
    double m_downloadSpeed;
    qint64 m_totalBytes;
    qint64 m_receivedBytes;
    QString m_unit;

    // Download progress
    QFile stream;
    QElapsedTimer timer;
    QNetworkAccessManager manager;
    QNetworkReply *reply;

    QQueue<QUrl> downloadQueue;
    void prepareDownloadFlags();
    void createCodesMap();
    bool fileExist(const QString &filename);

};

#endif // CLASSSETUPFLAGS_H
