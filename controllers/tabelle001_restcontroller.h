#ifndef TABELE001_RESTCONTROLLER_H
#define TABELE001_RESTCONTROLLER_H

#include <tabelle001.h>
#include <tabelle002.h>
#include "restcontroller.h"

class T_CONTROLLER_EXPORT Tabelle001RestController : public RestController
{
    Q_OBJECT
public:
    Tabelle001RestController() : RestController() {}

private:
    bool update(const QJsonValue &jv, Tabelle001 &model, QMap<int, QUuid> &pkMap);
    static bool updateTabelle002(const QJsonValue &jv, Tabelle002 &model, QMap<int, QUuid> &pkMap, const QPair<QString, QString> &parent);

public slots:
    void get();
    void get(const QString &id);
    void post();
    void put();

    void getTabelle002(const QString &parentId, const QString &parent_id);
    void getTabelle002(const QString &s1);
    void postTabelle002(const QString &s1);
    void putTabelle002(const QString &s1);
};

#endif //TABELE001_RESTCONTROLLER_H

