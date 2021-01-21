#include "tabelle001_restcontroller.h"
#include <tabelle001.h>
#include <tabelle002.h>
#include <tabelle002object.h>

void Tabelle001RestController::get() {
    tDebug("Tabelle001RestController::get");

    auto *mapper = new TSqlORMapper<Tabelle001Object>;
    auto propertyMap = Tabelle001::getPropertyIndexMap();

    try {
        HttpCriteria httpCriteria(propertyMap, mapper);
        auto r = httpRequest();
        httpCriteria.add(r);
        return renderJsonSuccess(Tabelle001::getJson(httpCriteria), httpCriteria.getCount());
    }
    catch (std::exception &e) {
        rollbackTransaction();
        this->setStatusCode(Tf::InternalServerError);
        tDebug("Error: %s", e.what());
        renderJsonFail(e.what());
    }
}

void Tabelle001RestController::get(const QString &id) {
    tDebug("Tabelle001RestController::get id");

    auto uuid = QUuid(id);
    if (uuid.isNull()) {
        tDebug("Tf::BadRequest");
        setStatusCode(Tf::BadRequest);
        renderJsonFail("Invalid parameter");
        return;
    }

    auto record = Tabelle001::get(id);
    if (record.isNull()) {
        renderJsonFail("Record not found");
        return;
    }

    renderJsonSuccess(record.toJsonObject());
}

void Tabelle001RestController::post() {
    tDebug("Tabelle001RestController::post");

    QJsonDocument qjd = getDocument();

    QMap<QString, QVariant> qvm = qjd.toVariant().toMap();

    // remove attributes from client
    qvm.remove("id");
    qvm.remove("createdAt");
    qvm.remove("updatedAt");
    qvm.remove("createdById");
    qvm.remove("updatedById");

    const auto record = Tabelle001::create(qvm);

    if (record.isNull()) {
        renderJsonFail("Create record failed");
    } else {
        renderJsonSuccess(record.toJsonObject());
    }
}

void Tabelle001RestController::put() {
    tDebug("Tabelle001RestController::put");

    try {
        QJsonDocument qjd = getDocument();

        Tabelle001 model;
        QMap<int, QUuid> pkMap;

        if (qjd.isObject()) {
            if (!update(qjd.object(), model, pkMap)) {
                QString msg{"Update failed for id: "};
                msg += qjd.object().value("id").toString().toStdString().c_str();
                throw RuntimeException(msg, __FILE__, __LINE__);
            }
            renderJsonSuccess(model.toJsonObject());
        } else if (qjd.isArray()) {
            QJsonArray rArray;

            for (const auto &jo : qjd.array()) {
                if (!update(jo, model, pkMap)) {
                    QString msg{"Update failed for id: "};
                    msg += qjd.object().value("id").toString().toStdString().c_str();
                    throw RuntimeException(msg, __FILE__, __LINE__);
                }
                rArray.append(model.toJsonObject());
            }
            renderJsonSuccess(rArray);
        } else {
            throw RuntimeException("Invalid JSON payload", __FILE__, __LINE__);
        }
    }
    catch (TfException &e) {
        rollbackTransaction();
        this->setStatusCode(Tf::InternalServerError);
        tDebug("Error: %s", e.message().toStdString().c_str());
        renderJsonFail(e.message().toStdString().c_str());
    }
}

bool Tabelle001RestController::update(const QJsonValue &jv, Tabelle001 &model, QMap<int, QUuid> &pkMap) {
    tDebug("Tabelle001RestController::update");
    QMap<QString, QVariant> qvm = jv.toVariant().toMap();
    int createPk = -1;

    const QString &idText = qvm.value("id").toString();
    if (idText.mid(0, 24) == "00000000-0000-0000-0000-") {
        createPk = idText.mid(24, 12).toInt();
        tDebug("id prefix: %d", createPk);
        model = Tabelle001();
    }
    else {
        QUuid id(idText);
        if (id.isNull()) {
            throw RuntimeException("Invalid UUID", __FILE__, __LINE__);
        }
        model = Tabelle001::get(idText);
    }

    // remove attributes from client
    qvm.remove("id");
    qvm.remove("createdAt");
    qvm.remove("updatedAt");
    qvm.remove("createdById");
    qvm.remove("updatedById");

    const QVariant &vParentId = qvm.value("parentId");
    if (!vParentId.isNull() && !vParentId.toUuid().isNull()) {
        const QString &sParentId = vParentId.toString();
        if (sParentId.mid(0, 24) == "00000000-0000-0000-0000-") {
            const QUuid &parentId = pkMap.value(sParentId.mid(24, 12).toInt());
            if (parentId.isNull()) {
                return false;
            }
            qvm["parentId"] = parentId.toString();
        }
    }

    model.setProperties(qvm);
    if (model.isNew()) {
        if (model.create() && createPk != -1) {
            pkMap[createPk] = model.id();
            return true;
        }
        return false;
    }
    return model.update();
}

// --Tabelle002
void Tabelle001RestController::getTabelle002(const QString &parentId, const QString &id) {
    tDebug("Tabelle001RestController::getTabelle002 id");

    auto record = Tabelle002::getByTabelle001(parentId, id);
    if (record.isNull()) {
        renderJsonFail("Record not found");
        return;
    }

    renderJsonSuccess(record.toJsonObject());
}

void Tabelle001RestController::getTabelle002(const QString &parentId) {
    tDebug("Tabelle001RestController::get");

    auto *mapper = new TSqlORMapper<Tabelle002Object>;
    auto propertyMap = Tabelle002::getPropertyIndexMap();

    try {
        HttpCriteria httpCriteria(propertyMap, mapper);

        httpCriteria.add(Tabelle002Object::PropertyIndex::Tabelle001Id, parentId);
        httpCriteria.add(httpRequest());
        return renderJsonSuccess(Tabelle002::getJson(httpCriteria), httpCriteria.getCount());
    }
    catch (std::exception &e) {
        rollbackTransaction();
        this->setStatusCode(Tf::InternalServerError);
        tDebug("Error: %s", e.what());
        renderJsonFail(e.what());
    }
}

void Tabelle001RestController::postTabelle002(const QString &parentId) {
    tDebug("Tabelle001RestController::postTabelle002");

    QJsonDocument qjd = getDocument();

    QMap<QString, QVariant> qvm = qjd.toVariant().toMap();

    // remove attributes from client
    qvm.remove("id");
    qvm.remove("createdAt");
    qvm.remove("updatedAt");
    qvm.remove("createdById");
    qvm.remove("updatedById");

    const auto payloadParentId = qvm.value("tabelle001Id").toString();
    if (payloadParentId != parentId) {
        renderJsonFail("Parent ID mismatch");
    }

    const auto record = Tabelle002::create(qvm);

    if (record.isNull()) {
        QString msg = "Create record failed: ";
        msg += __FILE__;
        msg += " ";
        msg += QString::number(__LINE__);
        renderJsonFail(msg);
    } else {
        renderJsonSuccess(record.toJsonObject());
    }
}

void Tabelle001RestController::putTabelle002(const QString &parentId) {
        tDebug("Tabelle001RestController::putTabelle002");

        QPair<QString, QString> parent{"tabelle001Id", parentId};

        try {
            QJsonDocument qjd = getDocument();

            Tabelle002 model;
            QMap<int, QUuid> pkMap;

            if (qjd.isObject()) {
                if (!updateTabelle002(qjd.object(), model, pkMap, parent)) {
                    QString msg{"Update failed for id: "};
                    msg += qjd.object().value("id").toString().toStdString().c_str();
                    throw RuntimeException(msg, __FILE__, __LINE__);
                }
                renderJsonSuccess(model.toJsonObject());
            } else if (qjd.isArray()) {
                QJsonArray rArray;

                for (const auto &jo : qjd.array()) {
                    if (!updateTabelle002(jo, model, pkMap, parent)) {
                        QString msg{"Update failed for id: "};
                        msg += qjd.object().value("id").toString().toStdString().c_str();
                        throw RuntimeException(msg, __FILE__, __LINE__);
                    }
                    rArray.append(model.toJsonObject());
                }
                renderJsonSuccess(rArray);
            } else {
                throw RuntimeException("Invalid JSON payload", __FILE__, __LINE__);
            }
        }
        catch (TfException &e) {
            rollbackTransaction();
            this->setStatusCode(Tf::InternalServerError);
            tDebug("Error: %s", e.message().toStdString().c_str());
            renderJsonFail(e.message().toStdString().c_str());
        }
    }

    bool Tabelle001RestController::updateTabelle002(const QJsonValue &jv, Tabelle002 &model, QMap<int, QUuid> &pkMap, const QPair<QString, QString> &parent) {
        tDebug("Tabelle001RestController::updateTabelle002");
        QMap<QString, QVariant> qvm = jv.toVariant().toMap();
        int createPk = -1;

        const QString &idText = qvm.value("id").toString();
        if (idText.mid(0, 24) == "00000000-0000-0000-0000-") {
            createPk = idText.mid(24, 12).toInt();
            tDebug("id prefix: %d", createPk);
            model = Tabelle002();
        }
        else {
            QUuid id(idText);
            if (id.isNull()) {
                throw RuntimeException("Invalid UUID", __FILE__, __LINE__);
            }
            model = Tabelle002::getByTabelle001(parent.second, idText);
        }

        // remove attributes from client
        qvm.remove("id");
        qvm.remove("createdAt");
        qvm.remove("updatedAt");
        qvm.remove("createdById");
        qvm.remove("updatedById");

        const auto payloadParentId = qvm.value(parent.second).toString();
        if (payloadParentId != parent.second) {
            renderJsonFail("Parent ID mismatch");
        }

        const QVariant &vParentId = qvm.value("parentId");
        if (!vParentId.isNull() && !vParentId.toUuid().isNull()) {
            const QString &sParentId = vParentId.toString();
            if (sParentId.mid(0, 24) == "00000000-0000-0000-0000-") {
                const QUuid &parentId = pkMap.value(sParentId.mid(24, 12).toInt());
                if (parentId.isNull()) {
                    return false;
                }
                qvm["parentId"] = parentId.toString();
            }
        }

        model.setProperties(qvm);
        if (model.isNew()) {
            if (model.create() && createPk != -1) {
                pkMap[createPk] = model.id();
                return true;
            }
            return false;
        }
        return model.update();
    }

// Don't remove below this line
T_DEFINE_CONTROLLER(Tabelle001RestController)

