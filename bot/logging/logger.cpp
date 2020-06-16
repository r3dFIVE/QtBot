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
Logger::trace(QString event) {
    logEvent(LogContext::LogLevel::TRACE, event);
}

void
Logger::info(QString event) {
    logEvent(LogContext::LogLevel::INFO, event);
}

void
Logger::debug(QString event) {
    logEvent(LogContext::LogLevel::DEBUG, event);
}

void
Logger::warning(QString event) {
    logEvent(LogContext::LogLevel::WARNING, event);
}

void
Logger::critical(QString event) {
    logEvent(LogContext::LogLevel::CRITICAL, event);
}

void
Logger::fatal(QString event) {
    logEvent(LogContext::LogLevel::FATAL, event);
}
