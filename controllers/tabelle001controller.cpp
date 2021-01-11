#include "tabelle001controller.h"
#include "tabelle001.h"


void Tabelle001Controller::index()
{
    auto tabelle001List = Tabelle001::getAll();
    texport(tabelle001List);
    render();
}

void Tabelle001Controller::show(const QString &id)
{
    auto tabelle001 = Tabelle001::get(id);
    texport(tabelle001);
    render();
}

void Tabelle001Controller::create()
{
    switch (httpRequest().method()) {
    case Tf::Get:
        render();
        break;

    case Tf::Post: {
        auto tabelle001 = httpRequest().formItems("tabelle001");
        auto model = Tabelle001::create(tabelle001);

        if (!model.isNull()) {
            QString notice = "Created successfully.";
            tflash(notice);
            redirect(urla("show", model.id()));
        } else {
            QString error = "Failed to create.";
            texport(error);
            texport(tabelle001);
            render();
        }
        break; }

    default:
        renderErrorResponse(Tf::NotFound);
        break;
    }
}

void Tabelle001Controller::save(const QString &id)
{
    switch (httpRequest().method()) {
    case Tf::Get: {
        auto model = Tabelle001::get(id);
        if (!model.isNull()) {
            auto tabelle001 = model.toVariantMap();
            texport(tabelle001);
            render();
        }
        break; }

    case Tf::Post: {
        QString error;
        auto model = Tabelle001::get(id);
        
        if (model.isNull()) {
            error = "Original data not found. It may have been updated/removed by another transaction.";
            tflash(error);
            redirect(urla("save", id));
            break;
        }

        auto tabelle001 = httpRequest().formItems("tabelle001");
        model.setProperties(tabelle001);
        if (model.save()) {
            QString notice = "Updated successfully.";
            tflash(notice);
            redirect(urla("show", model.id()));
        } else {
            error = "Failed to update.";
            texport(error);
            texport(tabelle001);
            render();
        }
        break; }

    default:
        renderErrorResponse(Tf::NotFound);
        break;
    }
}

void Tabelle001Controller::remove(const QString &id)
{
    if (httpRequest().method() != Tf::Post) {
        renderErrorResponse(Tf::NotFound);
        return;
    }

    auto tabelle001 = Tabelle001::get(id);
    tabelle001.remove();
    redirect(urla("index"));
}


// Don't remove below this line
T_DEFINE_CONTROLLER(Tabelle001Controller)
