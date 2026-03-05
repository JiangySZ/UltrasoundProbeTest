#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QLoggingCategory>
#include <QDateTime>
#include <QMessageLogContext>
#include <QMutex>

Q_DECLARE_LOGGING_CATEGORY(LOG_MAIN)
Q_DECLARE_LOGGING_CATEGORY(LOG_CONFIG)
Q_DECLARE_LOGGING_CATEGORY(LOG_HAL)
Q_DECLARE_LOGGING_CATEGORY(LOG_TEST)

class Logger : public QObject
{
    Q_OBJECT

private:
    static Logger* s_instance;
    QString m_logFile;
    QFile m_file;
    QTextStream m_stream;

    explicit Logger(QObject *parent = nullptr);
    ~Logger();

public:
    static Logger* instance();

    void init(const QString& logFile = QString());
    void setLogLevel(QtMsgType level);
    void close();

private:
    static void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);
};

#endif // LOGGER_H
