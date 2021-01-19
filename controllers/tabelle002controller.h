#ifndef TABELLE002CONTROLLER_H
#define TABELLE002CONTROLLER_H

#include "applicationcontroller.h"


class T_CONTROLLER_EXPORT Tabelle002Controller : public ApplicationController
{
    Q_OBJECT
public:
    Tabelle002Controller() : ApplicationController() {}

public slots:
    void index();
    void show(const QString &id);
    void create();
    void save(const QString &id);
    void remove(const QString &id);
};

#endif // TABELLE002CONTROLLER_H
