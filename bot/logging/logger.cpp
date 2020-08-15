#include "logger.h"

#include <QThread>

Logger::Logger(LogContext ctx, QObject *parent) : QObject (parent) {
    _thread = new QThread(this);

    _worker = new LogWorker(ctx);

    _worker->moveToThread(_thread);

    connect(this, &Logger::logEvent, _worker, &LogWorker::logEvent);

    connect(_thread, &QThread::finished, _worker, &QObject::deleteLater);

    _thread->start();
}

Logger::~Logger() {
    _thread->quit();

    _thread->wait();
}

void
Logger::trace(QString message) {
    logEvent(LogContext::LogLevel::TRACE, message);
}

void
Logger::info(QString message) {
    logEvent(LogContext::LogLevel::INFO, message);
}

void
Logger::debug(QString message) {
    logEvent(LogContext::LogLevel::DEBUG, message);
}

void
Logger::warning(QString message) {
    logEvent(LogContext::LogLevel::WARNING, message);
}

void
Logger::critical(QString message) {
    logEvent(LogContext::LogLevel::CRITICAL, message);
}

void
Logger::fatal(QString message) {
    logEvent(LogContext::LogLevel::FATAL, message);
}
