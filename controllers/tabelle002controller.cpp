#include "tabelle002controller.h"
#include "tabelle002.h"


void Tabelle002Controller::index()
{
    auto tabelle002List = Tabelle002::getAll();
    texport(tabelle002List);
    render();
}

void Tabelle002Controller::show(const QString &id)
{
    auto tabelle002 = Tabelle002::get(id);
    texport(tabelle002);
    render();
}

void Tabelle002Controller::create()
{
    switch (httpRequest().method()) {
    case Tf::Get:
        render();
        break;

    case Tf::Post: {
        auto tabelle002 = httpRequest().formItems("tabelle002");
        auto model = Tabelle002::create(tabelle002);

        if (!model.isNull()) {
            QString notice = "Created successfully.";
            tflash(notice);
            redirect(urla("show", model.id()));
        } else {
            QString error = "Failed to create.";
            texport(error);
            texport(tabelle002);
            render();
        }
        break; }

    default:
        renderErrorResponse(Tf::NotFound);
        break;
    }
}

void Tabelle002Controller::save(const QString &id)
{
    switch (httpRequest().method()) {
    case Tf::Get: {
        auto model = Tabelle002::get(id);
        if (!model.isNull()) {
            session().insert("tabelle002_lockRevision", model.lockRevision());
            auto tabelle002 = model.toVariantMap();
            texport(tabelle002);
            render();
        }
        break; }

    case Tf::Post: {
        QString error;
        int rev = session().value("tabelle002_lockRevision").toInt();
        auto model = Tabelle002::get(id, rev);
        
        if (model.isNull()) {
            error = "Original data not found. It may have been updated/removed by another transaction.";
            tflash(error);
            redirect(urla("save", id));
            break;
        }

        auto tabelle002 = httpRequest().formItems("tabelle002");
        model.setProperties(tabelle002);
        if (model.save()) {
            QString notice = "Updated successfully.";
            tflash(notice);
            redirect(urla("show", model.id()));
        } else {
            error = "Failed to update.";
            texport(error);
            texport(tabelle002);
            render();
        }
        break; }

    default:
        renderErrorResponse(Tf::NotFound);
        break;
    }
}

void Tabelle002Controller::remove(const QString &id)
{
    if (httpRequest().method() != Tf::Post) {
        renderErrorResponse(Tf::NotFound);
        return;
    }

    auto tabelle002 = Tabelle002::get(id);
    tabelle002.remove();
    redirect(urla("index"));
}


// Don't remove below this line
T_DEFINE_CONTROLLER(Tabelle002Controller)
