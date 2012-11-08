#pragma once

#include <exception>

#include <QObject>
#include <QCoreApplication>
#include <QString>

namespace BufferStorage {
class BufferStorageException : public std::exception {
    const QString reason;
public:
    BufferStorageException(const QString &reason) throw() :
        reason(reason)
    {}
    ~BufferStorageException() throw() {}

    const char *what() const throw() {
        return reason.toUtf8().constData();
    }

    QString getReason() const throw() {
        return reason;
    }
};
}
