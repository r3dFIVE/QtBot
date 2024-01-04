#include "logfactory.h"
#include "logutils.h"


void
LogUtils::logConstructor(QObject *obj, const QString &appendString) {
    doLogging("Creating", obj, appendString);
}

void
LogUtils::logDestructor(QObject *obj, const QString &appendString) {
    doLogging("Destorying", obj, appendString);
}

void
LogUtils::doLogging(const QString &verb, QObject *obj, const QString &appendValue) {
    Logger *logger = LogFactory::getLogger(obj);

    QString ptrStr = QString("0x%1").arg((quintptr) obj,
                        QT_POINTER_SIZE * 2, 16, QChar('0'));

    QString className = obj->metaObject()->className();

    QObject *parent = obj->parent();

    QString outputString;

    if (parent) {
        QString parentClassName = parent->metaObject()->className();

        QString parentPtrStr = QString("0x%1").arg((quintptr) parent,
                            QT_POINTER_SIZE * 2, 16, QChar('0'));


        outputString = QString("%1 %2(%3) | Parent: %4(%5)")
                      .arg(verb)
                      .arg(className)
                      .arg(ptrStr)
                      .arg(parentClassName)
                      .arg(parentPtrStr);
    } else {
        outputString = QString("%1 %2(%3)")
                      .arg(verb)
                      .arg(className)
                      .arg(ptrStr);
    }

    if (!appendValue.isEmpty()) {
        outputString = QString("%1 | %2").arg(outputString).arg(appendValue);
    }

    logger->debug(outputString);
}
