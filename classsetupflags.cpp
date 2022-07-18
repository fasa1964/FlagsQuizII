#include "classsetupflags.h"


#include <QFile>
#include <QFileDevice>
#include <QFileInfo>

#include <QDebug>


ClassSetupFlags::ClassSetupFlags(QObject *parent)
    : QObject{parent}
{
    setCountriesFile(  fileExist("countries.json")  );

    setDownloadFilename("");
    setUnit("");
    setDownloadSpeed(0);
    setTotalBytes(0);
    setReceivedBytes(0);



}

void ClassSetupFlags::startDownloadGamesData(const QString &type)
{

    // https://sourceforge.net/projects/world-countries.mirror/files/latest/download // countries.json
    // <script src="https://gist.github.com/ssskip/5a94bfcd2835bf1dea52.js"></script>
    // <script src="https://gist.github.com/chankok/6b085b08e29ccafc60c34542afc10acc.js"></script>
    // https://gist.github.com/jmmalaca/c39ba20f30388bbf8c28cc2dad3d27a4

    if(type == "Flags"){
        //qDebug() << "Start downloading flag";
        prepareDownloadFlags();
        QUrl url = downloadQueue.dequeue();
        startDownload(url);
    }

}

void ClassSetupFlags::startDownload(const QUrl &url)
{
    QString filename = getDownloadBasename(url);
    stream.setFileName(filename);
    setDownloadFilename(filename);

    if(!stream.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        emit errorOccurred(stream.errorString());
        return;
    }

    QNetworkRequest request(url);
//    request.setSslConfiguration(config);
    reply = manager.get( request );

    connect(reply, &QNetworkReply::downloadProgress, this, &ClassSetupFlags::downloadProgress );
    connect(reply, &QNetworkReply::finished, this, &ClassSetupFlags::downloadFinished );
    connect(reply, &QNetworkReply::readyRead, this, &ClassSetupFlags::downloadReadyToRead );

}

QString ClassSetupFlags::getDownloadBasename(const QUrl &url)
{
    QString path = url.path();
    QString basename = QFileInfo(path).fileName();

    if(basename.isEmpty()){
        basename = "Unknown";
    }

    return basename;
}

bool ClassSetupFlags::countriesFile() const
{
    return m_countriesFile;
}

void ClassSetupFlags::setCountriesFile(bool newCountriesFile)
{
    m_countriesFile = newCountriesFile;
}

void ClassSetupFlags::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    // calculate the download speed
     double s = bytesReceived * 1000.0 / timer.elapsed();
     QString u;

     if(s < 1024.0){
         u = "bytes/sec";
     }else if(s < 1024 * 1024){
         s /= 1024;
         u = "kB/s";
     } else {
         s  /= 1024 * 1024;
         u = "MB/s";
     }

     setDownloadSpeed( s );
     setTotalBytes( bytesTotal );
     setReceivedBytes( bytesReceived );
     setUnit( u );
}

void ClassSetupFlags::downloadFinished()
{
    stream.close();

    if(reply->error() == QNetworkReply::NoError)
    {
        ;
    }
    else
    {
        emit errorOccurred( reply->errorString() );
    }

    if(!downloadQueue.isEmpty())
    {
        QUrl url = downloadQueue.dequeue();
        startDownload(url);
    }
    else
        emit finishedDownloadFlags();

}

void ClassSetupFlags::downloadReadyToRead()
{
    stream.write( reply->readAll() );
}

void ClassSetupFlags::prepareDownloadFlags()
{
    if(codesMap.isEmpty())
        createCodesMap();

    QMapIterator<QString, QString> it(codesMap);
    QString s = "https://flagcdn.com/";
    QString e = ".svg";

    while (it.hasNext())
    {
        it.next();

        QString filename = it.key()+e;

        if(!fileExist(filename))
        {
            QUrl url( s+it.key()+e  );
            downloadQueue.enqueue(url);
        }
    }

}

void ClassSetupFlags::createCodesMap()
{
    QString fname = "countries.json";
    QFile file(fname);

    if(!file.exists()){
        QString errorMessage = "Sorry, " + fname + " not exist";
        emit errorOccurred(errorMessage);
        return;
    }


    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QString errorMessage = "Open " + fname + " failed.\nPlease check app permission!";
        emit errorOccurred(errorMessage);
        return;
    }


    QByteArray array = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument docJson = QJsonDocument::fromJson(array, &parseError);

    if(parseError.error != QJsonParseError::NoError)
    {
        QString errorMessage = "Error: " + parseError.errorString();
        emit errorOccurred(errorMessage);
        return;
    }

    if(!docJson.isArray()){
        QString errorMessage = "Error: " + fname + " wrong fileversion!";
        emit errorOccurred(errorMessage);
        return;
    }

    QVariant variant = docJson.toVariant();

    if(!variant.isValid()){
        QString errorMessage = "Error: " + fname + " wrong fileversion!";
        emit errorOccurred(errorMessage);
        return;
    }


    QVariantList vList = variant.toList();
    for(auto &v : vList)
    {

        QJsonObject obj = v.toJsonObject();

        QString name = obj.value("name").toObject().value("common").toString();             // Name of countrie
        QString alpha2 = obj.value("cca2").toString().toLower();                            // alpha2 of countrie

        codesMap.insert(alpha2, name);
    }
}


QString ClassSetupFlags::unit() const
{
    return m_unit;
}

void ClassSetupFlags::setUnit(const QString &newUnit)
{
    m_unit = newUnit;
}

qint64 ClassSetupFlags::receivedBytes() const
{
    return m_receivedBytes;
}

void ClassSetupFlags::setReceivedBytes(qint64 newReceivedBytes)
{
    m_receivedBytes = newReceivedBytes;
}

qint64 ClassSetupFlags::totalBytes() const
{
    return m_totalBytes;
}

void ClassSetupFlags::setTotalBytes(qint64 newTotalBytes)
{
    m_totalBytes = newTotalBytes;
}

double ClassSetupFlags::downloadSpeed() const
{
    return m_downloadSpeed;
}

void ClassSetupFlags::setDownloadSpeed(double newDownloadSpeed)
{
    m_downloadSpeed = newDownloadSpeed;
}

QString ClassSetupFlags::downloadFilename() const
{
    return m_downloadFilename;
}

void ClassSetupFlags::setDownloadFilename(const QString &newDownloadFilename)
{
    m_downloadFilename = newDownloadFilename;
}

bool ClassSetupFlags::fileExist(const QString &filename)
{
    QFileInfo file(filename);

    if(file.size() <= 0)
        return false;

    return file.exists();
}
