#include "classgamequiz.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>

#include <QFile>
#include <QFileDevice>
#include <QTextStream>
#include <QFileInfo>
#include <QDir>
#include <QRandomGenerator>

#include <QDebug>

ClassGameQuiz::ClassGameQuiz(QObject *parent)
    : QObject{parent}
{
    setCapitals(0);
    setCodes(0);
    setFlags( checkFlagsCount() );

    setQuestion("");
    setAnswerA("A");
    setAnswerB("B");
    setAnswerC("C");
    setAnswerD("D");
    setSolution("");
    questionCounter = 0;

    setLanguageKey("DEU");

    bonusMap.insert(1, "50€");
    bonusMap.insert(2, "100€");
    bonusMap.insert(3, "200€");
    bonusMap.insert(4, "300€");
    bonusMap.insert(5, "500€");
    bonusMap.insert(6, "1.000€");
    bonusMap.insert(7, "2.000€");
    bonusMap.insert(8, "4.000€");
    bonusMap.insert(9, "8.000€");
    bonusMap.insert(10, "16.000€");
    bonusMap.insert(11, "32.000€");
    bonusMap.insert(12, "64.000€");
    bonusMap.insert(13, "125.000€");
    bonusMap.insert(14, "500.000€");
    bonusMap.insert(15, "1M €");

}

int ClassGameQuiz::codes() const
{
    return m_codes;
}

void ClassGameQuiz::setCodes(int newCodes)
{
    if(m_codes != newCodes){
        m_codes = newCodes;
        emit codesChanged();
    }
}

int ClassGameQuiz::flags() const
{
    return m_flags;
}

void ClassGameQuiz::setFlags(int newFlags)
{
    if(m_flags != newFlags){
        m_flags = newFlags;
        emit flagsChanged();
    }
}

int ClassGameQuiz::capitals() const
{
    return m_capitals;
}

void ClassGameQuiz::setCapitals(int newCapitals)
{
    if(m_capitals != newCapitals){
        m_capitals = newCapitals;
        emit capitalsChanged();
    }
}

QString ClassGameQuiz::gameType() const
{
    return m_gameType;
}

QString ClassGameQuiz::question() const
{
    return m_question;
}

void ClassGameQuiz::setQuestion(const QString &newQuestion)
{
    if(m_question != newQuestion){
        m_question = newQuestion;
        emit questionChanged();
    }
}

QString ClassGameQuiz::answerA() const
{
    return m_answerA;
}

void ClassGameQuiz::setAnswerA(const QString &newAnswerA)
{
   if(m_answerA != newAnswerA){
        m_answerA = newAnswerA;
        emit answerAChanged();
        answerMap.insert("A", m_answerA);
   }
}

QString ClassGameQuiz::answerB() const
{
    return m_answerB;
}

void ClassGameQuiz::setAnswerB(const QString &newAnswerB)
{
    if(m_answerB != newAnswerB){
         m_answerB = newAnswerB;
         emit answerBChanged();
         answerMap.insert("B", m_answerB);
    }
}

QString ClassGameQuiz::answerC() const
{
    return m_answerC;
}

void ClassGameQuiz::setAnswerC(const QString &newAnswerC)
{
    if(m_answerC != newAnswerC){
         m_answerC = newAnswerC;
         emit answerCChanged();
         answerMap.insert("C", m_answerC);
    };
}

QString ClassGameQuiz::answerD() const
{
    return m_answerD;
}

void ClassGameQuiz::setAnswerD(const QString &newAnswerD)
{
    if(m_answerD != newAnswerD){
         m_answerD = newAnswerD;
         emit answerDChanged();
         answerMap.insert("D", m_answerD);
    }
}

QString ClassGameQuiz::solution() const
{
    return m_solution;
}

void ClassGameQuiz::setSolution(const QString &newSolution)
{
    if(m_solution != newSolution){
        m_solution = newSolution;
        emit solutionChanged();
    }
}

QString ClassGameQuiz::currentFlag() const
{
    return m_currentFlag;
}

void ClassGameQuiz::setCurrentFlag(const QString &newCurrentFlag)
{
    if(m_currentFlag != newCurrentFlag){
        m_currentFlag = newCurrentFlag;
        emit currentFlagChanged();
    }
}

QString ClassGameQuiz::languageKey() const
{
    return m_languageKey;
}

void ClassGameQuiz::setLanguageKey(const QString &newLanguageKey)
{
    m_languageKey = newLanguageKey;
}

bool ClassGameQuiz::isSolution(const QString &key)
{
    bool status = false;

    if(answerMap.value(key) == solution())
        status = true;

    return status;
}

void ClassGameQuiz::nextQuestion()
{

    QString solution = alterGenerateQuestion();

    if(gameType() != "Capitals" && languageKey() != "ENG" )
            solution = translate( solution );

    setSolution(solution);

    generateAnswers();
    questionCounter++;

}

void ClassGameQuiz::startGame(const QString &type)
{
    // clean randomlist
    randomNrList.clear();
    answerMap.clear();
    questionCounter = 0;

    m_gameType = type;
    //nextQuestion();
}

void ClassGameQuiz::setJoker50()
{

    QStringList keyList = answerMap.keys();
    int index = answerMap.values().indexOf( solution() );
    keyList.removeAt(index);

    int nr = getRandomNr(3);
    keyList.removeAt(nr);

    foreach(QString k, keyList)
    {
        if(k == "A"){
            setAnswerA("");
            answerMap.insert("A", "");
        }
        if(k == "B"){
            setAnswerB("");
            answerMap.insert("B", "");
        }
        if(k == "C"){
            setAnswerC("");
            answerMap.insert("C", "");
        }
        if(k == "D"){
            setAnswerD("");
            answerMap.insert("D", "");
        }
    }

}

void ClassGameQuiz::setJokerTel()
{

    int nr = getRandomNr(2);
    if(nr == 1){
        QString key = answerMap.key( solution() );
        emit setJokerTelefon(key);
    }
    if(nr == 0){
        int ac = getRandomNr(4);
        QString key = answerMap.keys().at(ac);
        emit setJokerTelefon(key);
    }

}

void ClassGameQuiz::setJokerPub()
{
    if(questionCounter <= 14){
        QString key = answerMap.key( solution() );
        emit setJokerPublic(key);
    }

    if(questionCounter >= 15){

        int nr = getRandomNr(2);
        if(nr == 1){
            QString key = answerMap.key( solution() );
            emit setJokerPublic(key);
        }
        if(nr == 0){
            int ac = getRandomNr(4);
            QString key = answerMap.keys().at(ac);
            emit setJokerPublic(key);
        }
    }
}

QString ClassGameQuiz::getBonusText(int num)
{
    return bonusMap.value(num);
}

int ClassGameQuiz::checkFlagsCount()
{
    int flagscount = 0;
    QStringList filters;
    filters << "*.svg";
    QDir dir;
    dir.setPath(QDir::currentPath());

    QFileInfoList infoList = dir.entryInfoList(filters);

    return infoList.size();
}

int ClassGameQuiz::getRandomNr(int max)
{
    quint32 n = QRandomGenerator::global()->bounded(max);
    return n;
}

QString ClassGameQuiz::generateQuestion()
{
    QString solution;
    int size = 0;

    if(gameType() == "Flags")
        size = codesMap.size();

    if(gameType() == "Capitals")
        size = capitalsMap.size();

    if(gameType() == "Borders")
        size = codesMap.size();


    int nr = getRandomNr( size );
    while(randomNrList.contains(nr)){
        nr = getRandomNr( size );
    }

    randomNrList << nr;
    QString key;
    QString value;


    if(gameType() == "Flags")
    {

        key = codesMap.keys().at(nr);
        value = codesMap.value(key);

        //value = translate(value, languageKey()); //

        solution = value;
        setQuestion( flagsMap.value(key) );
    }

    if(gameType() == "Capitals")
    {
        value = capitalsMap.keys().at(nr);
        key = getCountrieCode(value);
        solution = capitalsMap.value(value);

        //value = translate(value, languageKey());

        setQuestion( value );
        QString cflag = flagsMap.value( key );
        setCurrentFlag( cflag );
        //qDebug() << "cflag" << cflag;
    }

    if(gameType() == "Borders")
    {

        key = codesMap.keys().at(nr);
        value = codesMap.value(key);

        QStringList borderList =  bordersMap.value(value).toStringList();
        if(borderList.isEmpty()) // looks like island
            solution = "None";
        else{

            int nr = getRandomNr(borderList.size());
            solution =  getCountrie( borderList.at(nr) );

//            foreach(QString k, borderList){
//                qDebug() << getCountrie(k);
//            }
        }


        value = translate( value );
        setQuestion( value );
    }

    return solution;
}


// Returns the solution of questions
QString ClassGameQuiz::alterGenerateQuestion()
{
    QString solution;

    int size = 0;

    if(gameType() == "Flags" || gameType() == "Borders")
        size = codesMap.count();

    if(gameType() == "Capitals")
        size = capitalsMap.count();

    int nr = getRandomNr( size );
    while(randomNrList.contains(nr)){
        nr = getRandomNr( size );
    }

    randomNrList << nr;

    QString key = "";
    QString countrie = "";

    if(gameType() == "Flags")
    {
        key = codesMap.keys().at(nr);
        countrie =  codesMap.value(key);
        QString flagPath = flagsMap.value(key);

        solution = countrie;
        setQuestion( flagPath );

    }

    if(gameType() == "Borders")
    {
        key = codesMap.keys().at(nr);
        countrie =  codesMap.value(key);
        QStringList borders = getBorders(key);
        if(borders.isEmpty())
            solution = "None";
        else{

            int pos = getRandomNr(borders.size());
            solution = borders.at(pos);
        }

        QString flagPath = flagsMap.value(key);
        setCurrentFlag(flagPath);

        // Test
        if(languageKey() != "ENG")
            countrie = translate( countrie );


        setQuestion(countrie);

    }

    if(gameType() == "Capitals")
    {
        countrie = capitalsMap.keys().at(nr);
        key = codesMap.key(countrie);
        QString capital =  capitalsMap.value(countrie);
        solution = capital;

        QString flagPath = flagsMap.value(key);
        setCurrentFlag(flagPath);

        setQuestion(countrie);

    }

    return solution;
}

void ClassGameQuiz::generateAnswers()
{
    QList<int> answerNrList;
    int size = 0;

    if(gameType() == "Flags")
        size = codesMap.size();

    if(gameType() == "Capitals")
        size = capitalsMap.size();

    if(gameType() == "Borders"){
        size =  codesMap.size();
        //qDebug() << "Solution: " << solution();
    }


    // Other way
    // Get the current countrie key wich stores in function question
    QString questionKey = getCountrieCode( question() );
    QStringList bordersList = getBorders( questionKey );

//    qDebug() << "Lösung : "  << solution();
//    qDebug() << "Lösung : "  << translate( solution(), languageKey() );
//    qDebug() << "Borders of : "  << question();

//    foreach(QString k, bordersList){
//        qDebug() << "Borders:"  << translate( k , languageKey()) ;
//    }


    QStringList possibleAnswerList;
    while (answerNrList.size() <= 2) {
        int nr = getRandomNr( size );


        if(!randomNrList.contains(nr)){
            answerNrList << nr;

            QString c = codesMap.value(  codesMap.keys().at(nr) );
            if(!bordersList.contains(c))
               possibleAnswerList << translate( c )  ;
            else
              answerNrList.removeLast();

            QString ct =  translate( c );
            //qDebug() << translate( c , languageKey() );

        }






        // possible answers



//        QString currentCountrie = getCountrie( codesMap.keys().at(nr) );
//        QString currentKey = codesMap.keys().at(nr);
//        QStringList borders = getBorders( currentKey );

        //qDebug()<< borders;
        //qDebug()<< question();
        //qDebug()<< answerNrList.count() << ":" << nr << ":" << getCountrie( codesMap.keys().at(nr)  );


//        if(randomNrList.contains(nr))
//            answerNrList.removeLast();

    }


    qDebug() << "---------------------------";
    qDebug() << "Possible answers:";
    foreach(QString k, possibleAnswerList){
        qDebug() << k ;
    }
    qDebug() << "Lösung: " << solution();
    qDebug() << "---------------------------";

    // Is working accept for gametype capitals
    for(int i = 0; i < 3; i++){
        int nr = getRandomNr( size );
        while(randomNrList.contains(nr)){
            nr = getRandomNr( size );
        }
        //qDebug() << i;
        randomNrList << nr; // it's a global list
        answerNrList << nr;
    }

    //qDebug() << answerNrList;

    QStringList answers;
    for(int l = 0; l < answerNrList.size(); l++)
    {
        QString key = codesMap.keys().at(answerNrList.at(l));

        if(gameType() == "Flags")
            answers <<  translate( codesMap.value( key ) );

        if(gameType() == "Borders")
            answers <<  translate( codesMap.value( key ) );

        if(gameType() == "Capitals")
            answers << capitalsMap.value( codesMap.value( key )  );

    }

    // Set the solution in random pos
    int pos = getRandomNr(3);

    // Translate the answers
    QString s = solution();
    QString a =  answers.at(0);
    QString b =  answers.at(1);
    QString c =  answers.at(2);


    if(pos == 0)
    {
        setAnswerA( s );
        setAnswerB( a );
        setAnswerC( b );
        setAnswerD( c );
    }

    if(pos == 1)
    {
        setAnswerA( a );
        setAnswerB( s );
        setAnswerC( b );
        setAnswerD( c );
    }

    if(pos == 2)
    {
        setAnswerA( a );
        setAnswerB( b );
        setAnswerC( s );
        setAnswerD( c );
    }

    if(pos == 3)
    {
        setAnswerA( a );
        setAnswerB( b );
        setAnswerC( c );
        setAnswerD( s );
    }

}

QString ClassGameQuiz::getSolutionContinent()
{
    QString co;
    QString s = solution();

    if(gameType() == "Flags")
        co = continentMap.value(s);

    if(gameType() == "Capitals"){
        QString sk = capitalsMap.key(s);
        co = continentMap.value(sk);
    }

    return co;
}

QStringList ClassGameQuiz::getCountriesWidthBorders()
{
    QStringList cList;

    QMapIterator<QString, QString> it(codesMap);
    while(it.hasNext()){
        it.next();

        if( getBorders(it.key()).size() > 0)
            cList << it.value();
    }

    return cList;
}

QStringList ClassGameQuiz::getIslands()
{
    QStringList cList;

    QMapIterator<QString, QString> it(codesMap);
    while(it.hasNext()){
        it.next();

        if( getBorders(it.key()).size() >= 0)
            cList << it.value();
    }

    return cList;
}

QString ClassGameQuiz::getCountrieCode(const QString &countrie)
{

    QString c = countrie;
    if(languageKey() != "ENG"){

      //QMap<QString, QMap<QString, QVariant>> translationMap;

      // qDebug() << "Searching for:" << c;

       // key = countrie in englisch, map = key, translated string
       QMapIterator<QString, QMap<QString, QVariant>> it(translationMap);
       while (it.hasNext()) {
           it.next();

           //
           QMapIterator<QString, QVariant> i( it.value() );
           while (i.hasNext()) {
               i.next();

               // compare the countries name
               if(i.value().toString() == c && i.key() == languageKey() ) {

//                   qDebug() << "Countrie in english: " << it.key();
//                   qDebug() << "Countrie key: " <<  codesMap.key( it.key() );
                   return codesMap.key( it.key() );
                }

           }

       }

    }


    QString key = codesMap.key(c);
    return key;
}

QString ClassGameQuiz::getCountrie(const QString &key)
{
    QString nk = key;
    if(key.size() >= 3)
        nk = alphaMap.key(key);
    return codesMap.value(nk, "");
}

QString ClassGameQuiz::getCapital(const QString &key)
{
    QString nk = key;
    if(key.size() >= 3)
        nk = alphaMap.key(key);
    QString c = codesMap.value(key);
    return capitalsMap.value(c, "");
}

QStringList ClassGameQuiz::getBorders(const QString &key)
{
    QStringList list;
    QString c = getCountrie(key);

    // check if key is a key or a 
    
    
    QStringList vlk = bordersMap.value(c).toStringList();

    QStringList keyList;
    foreach(auto &s, vlk){
        keyList << s;
    }

    foreach(auto &s, keyList){
        list << getCountrie(s);
    }

    return list;
}

QStringList ClassGameQuiz::getCountriesContinent(const QString &continent)
{
    QStringList cList;

    QMapIterator<QString, QString> it(continentMap);
    while(it.hasNext()){
        it.next();

        if(it.value() == continent)
            cList << it.key();
    }

    return cList;
}

QString ClassGameQuiz::translate(const QString &source)
{
    QString translationString = "";

    if(source == "None")
        return source;

    if(!codesMap.values().contains(source))
        qDebug() << "Source already translated: " << source;


    QMap<QString, QVariant> vmap = translationMap.value(source);
    translationString = vmap.value(languageKey()).toString().toUtf8();

    if(translationString.isEmpty())
        return "No translation";

    return translationString;
}

QString ClassGameQuiz::createKey(const QString &c)
{
    QString key;
    int nr = 0;
    foreach(QChar s, c){
        if(nr >= 2)
            break;
        key.append( s.toLower() );
        nr++;
    }

    return key;
}


void ClassGameQuiz::createFlagsMap()
{
    QMapIterator<QString, QString> it(codesMap);

    while(it.hasNext()){
        it.next();

        QString key = it.key();
        QString filename = key+".svg";
        QString path = QDir::currentPath() + "/";
        if(fileExist(filename)){
            flagsMap.insert(key, path + filename);
        }
    }

    setFlags(flagsMap.count());

}

bool ClassGameQuiz::fileExist(const QString &filename)
{
    QFileInfo file(filename);

    if(file.size() <= 0)
        return false;

    return file.exists();
}

void ClassGameQuiz::createGameData()
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
        QString alpha3 = obj.value("cca3").toString();                                      // alpha3 of countrie
        QString capital = obj.value("capital").toArray().toVariantList().first().toString();// capital of countrie
        QString continent = obj.value("region").toString();                                 // continent of countrie
        QVariantList borders = obj.value("borders").toArray().toVariantList();              // borders of countrie


        alphaMap.insert(alpha2, alpha3);
        codesMap.insert(alpha2, name);
        if(!capital.isEmpty())
            capitalsMap.insert(name, capital);
//        else
//            qDebug() << name;

        continentMap.insert(name, continent);
        bordersMap.insert(name, borders);
        continentCodeMap.insert( createKey(continent), continent );



        // For translation in another language
        QStringList keyList = obj.value("translations").toObject().keys();      // get all keys for translation
        //qDebug() << keyList;

        QMap<QString, QVariant> tmap;
        foreach(auto &k, keyList){
            // translated string
            QString trans = obj.value("translations").toObject().value(k).toObject().value("common").toString().toUtf8();
            tmap.insert(k.toUpper(), trans);
        }

        // insert the englisch key witdt translated countrie name
        tmap.insert("ENG", name);

        translationMap.insert(name, tmap);


    }

    setCapitals( capitalsMap.size() );
    setCodes( codesMap.size() );


    if(checkFlagsCount() >= 0 && codesMap.size() > 0)
        createFlagsMap();



}

