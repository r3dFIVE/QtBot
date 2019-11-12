#ifndef LOCKINGQQUEUE_H
#define LOCKINGQQUEUE_H

#include <QQueue>
#include <QReadWriteLock>


template<typename T>
class LockingDeque {
    QQueue<T> queue_;
    QReadWriteLock lock_;

public:
    T dequeue() {
        lock_.lockForRead();
        T& t = std::move(queue_.head());
        queue_.dequeue();
        lock_.unlock();
        return t;
    }

    void enqueue(const T& t) {
        lock_.lockForWrite();
        queue_.enqueue(std::move(t));
        lock_.unlock();
    }

    void enqueue_front(const T& t) {
        lock_.lockForWrite();
        queue_.insert(0, t);
        lock_.unlock();
    }

    T& head() {
        lock_.lockForRead();
        T& t = queue_.head();
        lock_.unlock();
        return t;
    }

    const T& head() const {
        lock_.lockForRead();
        T& t = queue_.head();
        lock_.unlock();
        return t;
    }

    void swap(QQueue<T> &other) {
        lock_.lockForWrite();
        queue_.swap(other);
        lock_.unlock();
    }

    void swap(int i, int j) {
        lock_.lockForWrite();
        queue_.swap(i, j);
        lock_.unlock();
    }
};

#endif // LOCKINGQQUEUE_H
