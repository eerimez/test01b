#ifndef TABELLE001OBJECT_H
#define TABELLE001OBJECT_H

#include <TSqlObject>
#include <QSharedData>


class T_MODEL_EXPORT Tabelle001Object : public TSqlObject, public QSharedData
{
public:
    QString id;
    QString name;

    enum PropertyIndex {
        Id = 0,
        Name,
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
};

#endif // TABELLE001OBJECT_H
