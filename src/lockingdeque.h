#ifndef LOCKINGQQUEUE_H
#define LOCKINGQQUEUE_H

#include <QQueue>
#include <QReadWriteLock>


template<typename T>
class LockingDeque {
    QQueue<T> _queue;
    QReadWriteLock _lock;

public:
    T dequeue() {
        _lock.lockForRead();
        T& t = std::move(_queue.head());
        _queue.dequeue();
        _lock.unlock();
        return t;
    }

    void enqueue(const T& t) {
        _lock.lockForWrite();
        _queue.enqueue(std::move(t));
        _lock.unlock();
    }

    void enqueue_front(const T& t) {
        _lock.lockForWrite();
        _queue.insert(0, t);
        _lock.unlock();
    }

    T& head() {
        _lock.lockForRead();
        T& t = _queue.head();
        _lock.unlock();
        return t;
    }

    const T& head() const {
        _lock.lockForRead();
        T& t = _queue.head();
        _lock.unlock();
        return t;
    }

    void swap(QQueue<T> &other) {
        _lock.lockForWrite();
        _queue.swap(other);
        _lock.unlock();
    }

    void swap(int i, int j) {
        _lock.lockForWrite();
        _queue.swap(i, j);
        _lock.unlock();
    }
};

#endif // LOCKINGQQUEUE_H
