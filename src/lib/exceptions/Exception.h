#pragma once

#include <exception>

#include <QObject>
#include <QString>

class Exception : public std::exception {
    QString reason;
public:
    Exception(const QString &reason) throw() :
        reason(reason)
    {}

    ~Exception() throw() {}

    const char *what() const throw() {
        return reason.toUtf8();
    }

    QString getReason() const throw() {
        return reason;
    }
};

