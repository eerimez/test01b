#ifndef RESTCONTROLLER_H
#define RESTCONTROLLER_H

#include "applicationcontroller.h"

class T_CONTROLLER_EXPORT RestController : public ApplicationController
{
    Q_OBJECT
public:
    RestController() : ApplicationController() {}

    static void renderJsonSuccess(const QJsonValue &data, int count = 0);
    static void renderJsonFail(const QString &msg);
    static QMap<QJsonParseError::ParseError, QString> jsonParseErrorMap;

    bool preFilter();

public slots:
    void options();
    void options(const QString &arg1);
    void options(const QString &arg1, const QString &arg2);
    void options(const QString &arg1, const QString &arg2, const QString &arg3);
    void options(const QString &arg1, const QString &arg2, const QString &arg3, const QString &arg4);

protected:
    QJsonDocument getDocument();
};

#endif // RESTCONTROLLER_H
