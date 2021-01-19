#ifndef TABELLE001_H
#define TABELLE001_H

#include <QStringList>
#include <QDateTime>
#include <QJsonArray>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

#include "sqlobjects/tabelle001object.h"
#include "../controllers/http_criteria.h"

class T_MODEL_EXPORT Tabelle001 : public TAbstractModel
{
public:
    Tabelle001();
    Tabelle001(const Tabelle001 &other);
    Tabelle001(const Tabelle001Object &object);
    ~Tabelle001();

    QString id() const;
    void setId(const QString &id);
    QString name() const;
    void setName(const QString &name);
    QString lockRevision() const;
    QDateTime createdAt() const;
    QDateTime updatedAt() const;
    Tabelle001 &operator=(const Tabelle001 &other);

    bool create() override { return TAbstractModel::create(); }
    bool update() override { return TAbstractModel::update(); }
    bool save()   override { return TAbstractModel::save(); }
    bool remove() override { return TAbstractModel::remove(); }

    static Tabelle001 create(const QString &id, const QString &name);
    static Tabelle001 create(const QVariantMap &values);
    static Tabelle001 get(const QString &id);
    static Tabelle001 get(const QString &id, int lockRevision);
    static QJsonArray getJson(const HttpCriteria &criteria);

    static int count();
    static QList<Tabelle001> getAll();
    static QJsonArray getAllJson();

    static const QMap<QString, int> &getPropertyIndexMap();

private:
    const static QMap<QString, int> propertyIndexMap;
    QSharedDataPointer<Tabelle001Object> d;

    TModelObject *modelData() override;
    const TModelObject *modelData() const override;
    friend QDataStream &operator<<(QDataStream &ds, const Tabelle001 &model);
    friend QDataStream &operator>>(QDataStream &ds, Tabelle001 &model);

};

Q_DECLARE_METATYPE(Tabelle001)
Q_DECLARE_METATYPE(QList<Tabelle001>)

#endif // TABELLE001_H
