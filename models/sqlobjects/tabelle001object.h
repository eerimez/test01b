#ifndef TABELLE001OBJECT_H
#define TABELLE001OBJECT_H

#include <TSqlObject>
#include <QSharedData>


class T_MODEL_EXPORT Tabelle001Object : public TSqlObject, public QSharedData
{
public:
    QString id;
    QString name;
    QString lock_revision;
    QDateTime created_at;
    QDateTime updated_at;

    enum PropertyIndex {
        Id = 0,
        Name,
        LockRevision,
        CreatedAt,
        UpdatedAt,
    };

    int primaryKeyIndex() const override { return Id; }
    int autoValueIndex() const override { return -1; }
    QString tableName() const override { return QStringLiteral("tabelle_001"); }

private:    /*** Don't modify below this line ***/
    Q_OBJECT
    Q_PROPERTY(QString id READ getid WRITE setid)
    T_DEFINE_PROPERTY(QString, id)
    Q_PROPERTY(QString name READ getname WRITE setname)
    T_DEFINE_PROPERTY(QString, name)
    Q_PROPERTY(QString lock_revision READ getlock_revision WRITE setlock_revision)
    T_DEFINE_PROPERTY(QString, lock_revision)
    Q_PROPERTY(QDateTime created_at READ getcreated_at WRITE setcreated_at)
    T_DEFINE_PROPERTY(QDateTime, created_at)
    Q_PROPERTY(QDateTime updated_at READ getupdated_at WRITE setupdated_at)
    T_DEFINE_PROPERTY(QDateTime, updated_at)
};

#endif // TABELLE001OBJECT_H
