#ifndef TABELLE001CONTROLLER_H
#define TABELLE001CONTROLLER_H

#include "applicationcontroller.h"


class T_CONTROLLER_EXPORT Tabelle001Controller : public ApplicationController
{
    Q_OBJECT
public:
    Tabelle001Controller() : ApplicationController() {}

public slots:
    void index();
    void show(const QString &id);
    void create();
    void save(const QString &id);
    void remove(const QString &id);
};

#endif // TABELLE001CONTROLLER_H
