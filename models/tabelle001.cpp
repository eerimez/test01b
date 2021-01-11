#include <TreeFrogModel>
#include "tabelle001.h"
#include "sqlobjects/tabelle001object.h"

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
