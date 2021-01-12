#ifndef RESTCONTROLLER_H
#define RESTCONTROLLER_H

#include <TActionController>
#include "applicationhelper.h"


class T_CONTROLLER_EXPORT RestController : public TActionController
{
    Q_OBJECT
public:
    RestController();
    virtual ~RestController();

    void renderJsonSuccess(const QJsonValue &data, int count = 0);
    void renderJsonFail(const QString &msg);
    static QMap<QJsonParseError::ParseError, QString> jsonParseErrorMap;

public slots:
    void staticInitialize();
    void staticRelease();

    void options();
    void options(const QString &arg1);
    void options(const QString &arg1, const QString &arg2);
    void options(const QString &arg1, const QString &arg2, const QString &arg3);
    void options(const QString &arg1, const QString &arg2, const QString &arg3, const QString &arg4);

protected:
    virtual bool preFilter();
};

#endif // RESTCONTROLLER_H
