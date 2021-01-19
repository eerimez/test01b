#pragma once

#include "tsqlormapper.h"
#include <THttpRequest>

class HttpCriteria {

public:
    HttpCriteria(const QMap<QString, int> &propertyIndexMap, TSqlORMapperBase *mapper);

    // TODO: Inline these:
    TCriteria &add(const THttpRequest &httpRequest);
    TCriteria &add(int property, const QVariant &val);
    TCriteria &add(int property, TSql::ComparisonOperator op);
    TCriteria &add(int property, TSql::ComparisonOperator op, const QVariant &val);
    TCriteria &add(int property, TSql::ComparisonOperator op, const QVariant &val1, const QVariant &val2);
    TCriteria &add(int property, TSql::ComparisonOperator op1, TSql::ComparisonOperator op2, const QVariant &val);

    int getCount() const;
    const TCriteria &getCriteria() const;
    TSqlORMapperBase *getMapper() const;

private:
    TCriteria criteria;

    int start = 0;
    int limit = 0;

    int count = 0;

    QMap<QString, int> propertyIndexMap;
    TSqlORMapperBase *mapper;

    const static QMap<QString, TSql::ComparisonOperator> tSqlComparisonOperatorMap;
    const static QMap<int, Tf::SortOrder> tfSortOrderMap;
};
