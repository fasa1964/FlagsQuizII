#ifndef CLASSGAMEQUIZ_H
#define CLASSGAMEQUIZ_H

#include <QObject>
#include <QMap>
#include <QQmlProperties>

//#include <classsetupflags.h>

class ClassGameQuiz : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(int codes READ codes WRITE setCodes NOTIFY codesChanged)
    Q_PROPERTY(int flags READ flags WRITE setFlags NOTIFY flagsChanged)
    Q_PROPERTY(int capitals READ capitals WRITE setCapitals NOTIFY capitalsChanged)


    Q_PROPERTY(QString question READ question WRITE setQuestion NOTIFY questionChanged)
    Q_PROPERTY(QString answerA READ answerA WRITE setAnswerA NOTIFY answerAChanged)
    Q_PROPERTY(QString answerB READ answerB WRITE setAnswerB NOTIFY answerBChanged)
    Q_PROPERTY(QString answerC READ answerC WRITE setAnswerC NOTIFY answerCChanged)
    Q_PROPERTY(QString answerD READ answerD WRITE setAnswerD NOTIFY answerDChanged)
    Q_PROPERTY(QString solution READ solution WRITE setSolution NOTIFY solutionChanged)

    Q_PROPERTY(QString currentFlag READ currentFlag WRITE setCurrentFlag NOTIFY currentFlagChanged)


public:
    explicit ClassGameQuiz(QObject *parent = nullptr);

    Q_INVOKABLE void createGameData();
    Q_INVOKABLE void nextQuestion();
    Q_INVOKABLE void startGame(const QString &type);

    Q_INVOKABLE void setJoker50();
    Q_INVOKABLE void setJokerTel();
    Q_INVOKABLE void setJokerPub();


    int codes() const;
    void setCodes(int newCodes);

    int flags() const;
    void setFlags(int newFlags);

    int capitals() const;
    void setCapitals(int newCapitals);

    QString gameType() const;


    QString question() const;
    void setQuestion(const QString &newQuestion);

    QString answerA() const;
    void setAnswerA(const QString &newAnswerA);

    QString answerB() const;
    void setAnswerB(const QString &newAnswerB);

    QString answerC() const;
    void setAnswerC(const QString &newAnswerC);

    QString answerD() const;
    void setAnswerD(const QString &newAnswerD);

    QString solution() const;
    void setSolution(const QString &newSolution);

    QString currentFlag() const;
    void setCurrentFlag(const QString &newCurrentFlag);

    QString languageKey() const;
    void setLanguageKey(const QString &newLanguageKey);

signals:
    void codesChanged();
    void flagsChanged();
    void capitalsChanged();


    void questionChanged();
    void answerAChanged();
    void answerBChanged();
    void answerCChanged();
    void answerDChanged();
    void solutionChanged();
    void currentFlagChanged();


    void errorOccurred(const QString &error);

    void setJokerTelefon(const QString &key);
    void setJokerPublic(const QString &key);

private:

    int m_codes;
    int m_flags;
    int m_capitals;
    int questionCounter;



    QString m_gameType;

    QString m_languageKey;
    QString m_question;
    QString m_answerA;
    QString m_answerB;
    QString m_answerC;
    QString m_answerD;
    QString m_solution;

    QMap<QString, QString> answerMap;
    bool isSolution(const QString &key);
    QList<int> randomNrList;
    QString m_currentFlag;

    QMap<QString, QString> alphaMap;
    QMap<QString, QString> codesMap;
    QMap<QString, QString> flagsMap;
    QMap<QString, QString> capitalsMap;
    QMap<QString, QString> continentMap;
    QMap<QString, QString> continentCodeMap;
    QMap<QString, QVariant> bordersMap;
    QMap<QString, QMap<QString, QVariant>> translationMap;

    int checkFlagsCount();

    // For questions and answer's
    int getRandomNr(int max);
    QString generateQuestion();
    void generateAnswers();


    QString getSolutionContinent();
    QStringList getCountriesWidthBorders();
    QStringList getIslands();
    QString getCountrieCode(const QString &countrie);
    QString getCountrie(const QString &key);
    QString getCapital(const QString &key);
    QStringList getBorders(const QString &key);
    QStringList getCountriesContinent(const QString &continent);
    QString translate(const QString &source, const QString &key);

    QString createKey(const QString &c);
    QString getKeyAtPos(const QMap<QString, QString>&map, int pos);

    void createFlagsMap();
    bool fileExist(const QString &filename);
};

#endif // CLASSGAMEQUIZ_H
