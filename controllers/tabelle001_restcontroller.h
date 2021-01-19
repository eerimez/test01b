#ifndef TABELE001_RESTCONTROLLER_H
#define TABELE001_RESTCONTROLLER_H

#include <tabelle001.h>
#include "restcontroller.h"

class T_CONTROLLER_EXPORT Tabelle001RestController : public RestController
{
    Q_OBJECT
public:
    Tabelle001RestController() : RestController() {}

private:
    bool update(const QJsonValue &jv, Tabelle001 &model, QMap<int, QUuid> &pkMap);

public slots:
    void get();
    void get(const QString &id);
    void post();
    void put();
};

#endif //TABELE001_RESTCONTROLLER_H

