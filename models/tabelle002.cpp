#include <TreeFrogModel>
#include "tabelle002.h"
#include "sqlobjects/tabelle002object.h"

Tabelle002::Tabelle002() :
    TAbstractModel(),
    d(new Tabelle002Object())
{
    // set the initial parameters
}

Tabelle002::Tabelle002(const Tabelle002 &other) :
    TAbstractModel(),
    d(other.d)
{ }

Tabelle002::Tabelle002(const Tabelle002Object &object) :
    TAbstractModel(),
    d(new Tabelle002Object(object))
{ }

Tabelle002::~Tabelle002()
{
    // If the reference count becomes 0,
    // the shared data object 'Tabelle002Object' is deleted.
}

QString Tabelle002::id() const
{
    return d->id;
}

void Tabelle002::setId(const QString &id)
{
    d->id = id;
}

QString Tabelle002::name() const
{
    return d->name;
}

void Tabelle002::setName(const QString &name)
{
    d->name = name;
}

QString Tabelle002::tabelle001Id() const
{
    return d->tabelle_001_id;
}

void Tabelle002::setTabelle001Id(const QString &tabelle001Id)
{
    d->tabelle_001_id = tabelle001Id;
}

Tabelle002 &Tabelle002::operator=(const Tabelle002 &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

Tabelle002 Tabelle002::create(const QString &id, const QString &name, const QString &tabelle001Id)
{
    Tabelle002Object obj;
    obj.id = id;
    obj.name = name;
    obj.tabelle_001_id = tabelle001Id;
    if (!obj.create()) {
        return Tabelle002();
    }
    return Tabelle002(obj);
}

Tabelle002 Tabelle002::create(const QVariantMap &values)
{
    Tabelle002 model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

Tabelle002 Tabelle002::get(const QString &id)
{
    TSqlORMapper<Tabelle002Object> mapper;
    return Tabelle002(mapper.findByPrimaryKey(id));
}

int Tabelle002::count()
{
    TSqlORMapper<Tabelle002Object> mapper;
    return mapper.findCount();
}

QList<Tabelle002> Tabelle002::getAll()
{
    return tfGetModelListByCriteria<Tabelle002, Tabelle002Object>(TCriteria());
}

QJsonArray Tabelle002::getAllJson()
{
    QJsonArray array;
    TSqlORMapper<Tabelle002Object> mapper;

    if (mapper.find() > 0) {
        for (TSqlORMapperIterator<Tabelle002Object> i(mapper); i.hasNext(); ) {
            array.append(QJsonValue(QJsonObject::fromVariantMap(Tabelle002(i.next()).toVariantMap())));
        }
    }
    return array;
}

TModelObject *Tabelle002::modelData()
{
    return d.data();
}

const TModelObject *Tabelle002::modelData() const
{
    return d.data();
}

QDataStream &operator<<(QDataStream &ds, const Tabelle002 &model)
{
    auto varmap = model.toVariantMap();
    ds << varmap;
    return ds;
}

QDataStream &operator>>(QDataStream &ds, Tabelle002 &model)
{
    QVariantMap varmap;
    ds >> varmap;
    model.setProperties(varmap);
    return ds;
}

// Don't remove below this line
T_REGISTER_STREAM_OPERATORS(Tabelle002)
