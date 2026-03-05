#include "Config/Logger.h"

#include <QDir>
#include <QMutexLocker>

Q_LOGGING_CATEGORY(LOG_MAIN, "main")
Q_LOGGING_CATEGORY(LOG_CONFIG, "config")
Q_LOGGING_CATEGORY(LOG_HAL, "hal")
Q_LOGGING_CATEGORY(LOG_TEST, "test")

Logger* Logger::s_instance = nullptr;

Logger::Logger(QObject *parent)
    : QObject(parent)
{
}

Logger::~Logger()
{
    close();
}

Logger* Logger::instance()
{
    if (!s_instance) {
        s_instance = new Logger();
    }
    return s_instance;
}

void Logger::init(const QString& logFile)
{
    m_logFile = logFile;
    if (m_logFile.isEmpty()) {
        m_logFile = "app.log";
    }

    m_file.setFileName(m_logFile);
    if (m_file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        m_stream.setDevice(&m_file);
    }

    qInstallMessageHandler(messageHandler);
}

void Logger::setLogLevel(QtMsgType level)
{
    QLoggingCategory::setFilterRules(QStringLiteral("*.debug=%1\n"
                                                     "*.info=%2\n"
                                                     "*.warning=%3\n"
                                                     "*.critical=%4")
                                      .arg(level == QtDebugMsg ? "true" : "false")
                                      .arg(level <= QtInfoMsg ? "true" : "false")
                                      .arg(level <= QtWarningMsg ? "true" : "false")
                                      .arg(level <= QtCriticalMsg ? "true" : "false"));
}

void Logger::close()
{
    if (m_file.isOpen()) {
        m_file.close();
    }
}

void Logger::messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    QString level;

    switch (type) {
    case QtDebugMsg:    level = "DEBUG"; break;
    case QtInfoMsg:     level = "INFO "; break;
    case QtWarningMsg:  level = "WARN "; break;
    case QtCriticalMsg: level = "CRIT "; break;
    case QtFatalMsg:   level = "FATAL"; break;
    }

    QString category = context.category ? QString(context.category) : "default";
    QString logMsg = QString("[%1] [%2] [%3] %4")
                         .arg(timestamp)
                         .arg(level)
                         .arg(category)
                         .arg(msg);

    Logger* logger = Logger::instance();
    if (logger && logger->m_stream.device()) {
        QMutexLocker locker(nullptr);
        logger->m_stream << logMsg << "\n";
        logger->m_stream.flush();
    }

    fprintf(stderr, "%s\n", qUtf8Printable(logMsg));

    if (type == QtFatalMsg) {
        abort();
    }
}
