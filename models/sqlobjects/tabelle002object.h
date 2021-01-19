#ifndef TABELLE002OBJECT_H
#define TABELLE002OBJECT_H

#include <TSqlObject>
#include <QSharedData>


class T_MODEL_EXPORT Tabelle002Object : public TSqlObject, public QSharedData
{
public:
    QString id;
    QString name;
    QString tabelle_001_id;

    enum PropertyIndex {
        Id = 0,
        Name,
        Tabelle001Id,
    };

    int primaryKeyIndex() const override { return Id; }
    int autoValueIndex() const override { return -1; }
    QString tableName() const override { return QStringLiteral("tabelle_002"); }

private:    /*** Don't modify below this line ***/
    Q_OBJECT
    Q_PROPERTY(QString id READ getid WRITE setid)
    T_DEFINE_PROPERTY(QString, id)
    Q_PROPERTY(QString name READ getname WRITE setname)
    T_DEFINE_PROPERTY(QString, name)
    Q_PROPERTY(QString tabelle_001_id READ gettabelle_001_id WRITE settabelle_001_id)
    T_DEFINE_PROPERTY(QString, tabelle_001_id)
};

#endif // TABELLE002OBJECT_H
