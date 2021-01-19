#ifndef TABELLE002_H
#define TABELLE002_H

#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class Tabelle002Object;
class QJsonArray;


class T_MODEL_EXPORT Tabelle002 : public TAbstractModel
{
public:
    Tabelle002();
    Tabelle002(const Tabelle002 &other);
    Tabelle002(const Tabelle002Object &object);
    ~Tabelle002();

    QString id() const;
    void setId(const QString &id);
    QString name() const;
    void setName(const QString &name);
    QString tabelle001Id() const;
    void setTabelle001Id(const QString &tabelle001Id);
    Tabelle002 &operator=(const Tabelle002 &other);

    bool create() override { return TAbstractModel::create(); }
    bool update() override { return TAbstractModel::update(); }
    bool save()   override { return TAbstractModel::save(); }
    bool remove() override { return TAbstractModel::remove(); }

    static Tabelle002 create(const QString &id, const QString &name, const QString &tabelle001Id);
    static Tabelle002 create(const QVariantMap &values);
    static Tabelle002 get(const QString &id);
    static int count();
    static QList<Tabelle002> getAll();
    static QJsonArray getAllJson();

private:
    QSharedDataPointer<Tabelle002Object> d;

    TModelObject *modelData() override;
    const TModelObject *modelData() const override;
    friend QDataStream &operator<<(QDataStream &ds, const Tabelle002 &model);
    friend QDataStream &operator>>(QDataStream &ds, Tabelle002 &model);
};

Q_DECLARE_METATYPE(Tabelle002)
Q_DECLARE_METATYPE(QList<Tabelle002>)

#endif // TABELLE002_H
