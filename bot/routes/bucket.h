/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef BUCKET_H
#define BUCKET_H

#include <QReadWriteLock>
#include <QObject>
#include <QDateTime>

static const QString GLOBAL_BUCKET = "GLOBAL_BUCKET";


class Bucket
{
    QString _majorId;
    QString _rateLimitBucket;
    int _xRateLimitLimit = 0;
    int _xRateLimitRemaining = 0;
    qint64 _xRateLimitReset = 0;
    QReadWriteLock *_lock = new QReadWriteLock;

public:
    Bucket(const QString &majorId, const QString &rateLimitBucket) {
        _majorId = majorId;

        _rateLimitBucket = rateLimitBucket;
    }

    void setRateLimitLimit(const int rateLimitLimit) {
        _xRateLimitLimit = rateLimitLimit;
    }

    void setRateLimitReset(const qint64 rateLimitReset) {
        _xRateLimitReset = rateLimitReset;
    }

    void setRateLimitRemaining(const int rateLimitRemaining) {
        _xRateLimitRemaining = rateLimitRemaining;
    }

    QString getRateLimitBucket() const {
        return _rateLimitBucket;
    }

    QString getMajorId() const {
        return _majorId;
    }

    int getRateLimitLimit() const {
        return _xRateLimitLimit;
    }

    qint64 getRateLimitReset() const {
        return _xRateLimitReset;
    }

    int getRateLimitRemaining() const {
        return _xRateLimitRemaining;
    }

    QReadWriteLock *getLock() {
        return _lock;
    }

    bool canExecute() {
        // Possible write happening here, but want bucket update to take priority
        QReadLocker locker(_lock);

        bool canExecute = true;

        if ((_xRateLimitRemaining)-- < 1) {
            qint64 currentTime = QDateTime::currentSecsSinceEpoch();

            if (currentTime >= _xRateLimitReset) {
                _xRateLimitRemaining = _xRateLimitLimit - 1;

                canExecute = true;

            } else {
                canExecute = false;
            }
        }

        return canExecute;
    }
};

#endif // BUCKET_H
