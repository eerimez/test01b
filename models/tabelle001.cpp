#include <TreeFrogModel>
#include "tabelle001.h"
#include "sqlobjects/tabelle001object.h"
#include "../controllers/http_criteria.h"

const QMap<QString, int> Tabelle001::propertyIndexMap{
        {"id", Tabelle001Object::PropertyIndex::Id},
        {"name", Tabelle001Object::PropertyIndex::Name},
        {"lockRevision", Tabelle001Object::PropertyIndex::LockRevision},
        {"createdAt", Tabelle001Object::PropertyIndex::CreatedAt},
        {"updatedAt", Tabelle001Object::PropertyIndex::UpdatedAt},
//        {"createdById", Tabelle001Object::PropertyIndex::CreatedById},
//        {"updatedById", Tabelle001Object::PropertyIndex::UpdatedById}
};

const QMap<QString, int> &Tabelle001::getPropertyIndexMap() {
    return propertyIndexMap;
}

QJsonArray Tabelle001::getJson(const HttpCriteria &criteria)
{
    QJsonArray jsonArray;
    auto *mapper = dynamic_cast<TSqlORMapper<Tabelle001Object> *>(criteria.getMapper());

    if (mapper->find(criteria.getCriteria()) > 0) {
        for (TSqlORMapperIterator<Tabelle001Object> i(*mapper); i.hasNext(); ) {
            jsonArray.append(Tabelle001(i.next()).toJsonObject());
        }
    }
    return jsonArray;
}


Tabelle001::Tabelle001() :
    TAbstractModel(),
    d(new Tabelle001Object())
{
    // set the initial parameters
}

Tabelle001::Tabelle001(const Tabelle001 &other) :
    TAbstractModel(),
    d(other.d)
{ }

Tabelle001::Tabelle001(const Tabelle001Object &object) :
    TAbstractModel(),
    d(new Tabelle001Object(object))
{ }

Tabelle001::~Tabelle001()
{
    // If the reference count becomes 0,
    // the shared data object 'Tabelle001Object' is deleted.
}

QString Tabelle001::id() const
{
    return d->id;
}

void Tabelle001::setId(const QString &id)
{
    d->id = id;
}

QString Tabelle001::name() const
{
    return d->name;
}

void Tabelle001::setName(const QString &name)
{
    d->name = name;
}

QString Tabelle001::lockRevision() const
{
    return d->lock_revision;
}

QDateTime Tabelle001::createdAt() const
{
    return d->created_at;
}

QDateTime Tabelle001::updatedAt() const
{
    return d->updated_at;
}

Tabelle001 &Tabelle001::operator=(const Tabelle001 &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

Tabelle001 Tabelle001::create(const QString &id, const QString &name)
{
    Tabelle001Object obj;
    obj.id = id;
    obj.name = name;
    if (!obj.create()) {
        return Tabelle001();
    }
    return Tabelle001(obj);
}

Tabelle001 Tabelle001::create(const QVariantMap &values)
{
    Tabelle001 model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

Tabelle001 Tabelle001::get(const QString &id)
{
    TSqlORMapper<Tabelle001Object> mapper;
    return Tabelle001(mapper.findByPrimaryKey(id));
}

Tabelle001 Tabelle001::get(const QString &id, int lockRevision)
{
    TSqlORMapper<Tabelle001Object> mapper;
    TCriteria cri;
    cri.add(Tabelle001Object::Id, id);
    cri.add(Tabelle001Object::LockRevision, lockRevision);
    return Tabelle001(mapper.findFirst(cri));
}

int Tabelle001::count()
{
    TSqlORMapper<Tabelle001Object> mapper;
    return mapper.findCount();
}

QList<Tabelle001> Tabelle001::getAll()
{
    return tfGetModelListByCriteria<Tabelle001, Tabelle001Object>(TCriteria());
}

QJsonArray Tabelle001::getAllJson()
{
    QJsonArray array;
    TSqlORMapper<Tabelle001Object> mapper;

    if (mapper.find() > 0) {
        for (TSqlORMapperIterator<Tabelle001Object> i(mapper); i.hasNext(); ) {
            array.append(QJsonValue(QJsonObject::fromVariantMap(Tabelle001(i.next()).toVariantMap())));
        }
    }
    return array;
}

TModelObject *Tabelle001::modelData()
{
    return d.data();
}

const TModelObject *Tabelle001::modelData() const
{
    return d.data();
}

QDataStream &operator<<(QDataStream &ds, const Tabelle001 &model)
{
    auto varmap = model.toVariantMap();
    ds << varmap;
    return ds;
}

QDataStream &operator>>(QDataStream &ds, Tabelle001 &model)
{
    QVariantMap varmap;
    ds >> varmap;
    model.setProperties(varmap);
    return ds;
}

// Don't remove below this line
T_REGISTER_STREAM_OPERATORS(Tabelle001)
