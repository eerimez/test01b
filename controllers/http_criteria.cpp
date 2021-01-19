#include "http_criteria.h"
#include "treefrog/tsqlormapper.h"

const QMap<QString, TSql::ComparisonOperator> HttpCriteria::tSqlComparisonOperatorMap{
        {"nl", TSql::ComparisonOperator::IsNull},       // IS NULL
        {"nn", TSql::ComparisonOperator::IsNotNull},       // IS NULL
        {"lt", TSql::ComparisonOperator::LessThan},     // < val
        {"le", TSql::ComparisonOperator::LessEqual},    // <= val
        {"eq", TSql::ComparisonOperator::Equal},        // = val
        {"ge", TSql::ComparisonOperator::GreaterEqual}, // >= val
        {"gt", TSql::ComparisonOperator::GreaterThan},  // > val
        {"ne", TSql::ComparisonOperator::NotEqual},     // <> val
        {"in", TSql::ComparisonOperator::Contains},           // LIKE val%
        {"ni", TSql::ComparisonOperator::NotContains},           // LIKE val%
        {"bw", TSql::ComparisonOperator::BeginsWith},           // LIKE val%
        {"ew", TSql::ComparisonOperator::EndsWith}           // LIKE val%
};

const QMap<int, Tf::SortOrder> HttpCriteria::tfSortOrderMap{
        {2, Tf::SortOrder::DescendingOrder},
        {1, Tf::SortOrder::AscendingOrder}
};

HttpCriteria::HttpCriteria(const QMap<QString, int> &propertyIndexMap, TSqlORMapperBase *mapper) {
    this->propertyIndexMap = propertyIndexMap;
    this->mapper = mapper;
}

const TCriteria &HttpCriteria::getCriteria() const {
    return criteria;
}

TCriteria &HttpCriteria::add(int property, TSql::ComparisonOperator op) {
    return criteria.add(property, op);
}

TCriteria &HttpCriteria::add(int property, const QVariant &val) {
    return criteria.add(property, val);
}

TCriteria &HttpCriteria::add(int property, TSql::ComparisonOperator op, const QVariant &val) {
    return criteria.add(property, op, val);
}

TCriteria &HttpCriteria::add(int property, TSql::ComparisonOperator op, const QVariant &val1, const QVariant &val2) {
    return criteria.add(property, op, val1, val2);
}

TCriteria &HttpCriteria::add(int property, TSql::ComparisonOperator op1, TSql::ComparisonOperator op2, const QVariant &val) {
    return criteria.add(property, op1, op2, val);
}

TCriteria &HttpCriteria::add(const THttpRequest &httpRequest) {

    QJsonParseError e{};

    start = httpRequest.queryItemValue("s").toInt();
    limit = httpRequest.queryItemValue("l").toInt();

    tDebug("Sort:");
    const auto sortText = httpRequest.queryItemValue("o").toUtf8();
    if (!sortText.isNull() && sortText.length() > 0) {
        QJsonArray jsonSorters = QJsonDocument::fromJson(sortText, &e).array();
        if (e.error != QJsonParseError::NoError) {
            throw RuntimeException(e.errorString(), __FILE__, __LINE__);
        }

        for (auto const &j : jsonSorters) {
            const QJsonObject &sortObject = j.toObject();
            if (sortObject.isEmpty()) {
                throw RuntimeException("Invalid sorter element", __FILE__, __LINE__);
            }

            const QString key(sortObject.keys()[0]);
            if (key.isNull()) {
                throw RuntimeException("Invalid sorter key", __FILE__, __LINE__);
            }

            auto propertyIndex = propertyIndexMap.value(key, -1);
            if (propertyIndex == -1) {
                throw RuntimeException("Invalid property name", __FILE__, __LINE__);
            }

            int sortDirection = sortObject.value(key).toInt();
            auto sortOrder = tfSortOrderMap.value(sortDirection, (Tf::SortOrder) -1);
            if (sortOrder == (Tf::SortOrder) -1) {
                throw RuntimeException("Invalid sort order", __FILE__, __LINE__);
            }

            mapper->setSortOrder(propertyIndex, sortOrder);
        }
    }

    tDebug("Filters:");
    const auto filterText = httpRequest.queryItemValue("f").toUtf8();
    if (!filterText.isNull() && filterText.length() > 0) {
        QJsonArray jsonFilters = QJsonDocument::fromJson(filterText, &e).array();
        if (e.error != QJsonParseError::NoError) {
            throw RuntimeException(e.errorString(), __FILE__, __LINE__);
        }

        for (auto const &j : jsonFilters) {
            const QJsonObject &filterObject = j.toObject();
            if (filterObject.isEmpty()) {
                throw RuntimeException("Invalid filter object", __FILE__, __LINE__);
            }

            const QString key(filterObject.keys()[0]);
            if (key.isNull()) {
                throw RuntimeException("Invalid filter key", __FILE__, __LINE__);
            }

            auto propertyIndex = propertyIndexMap.value(key, -1);
            if (propertyIndex == -1) {
                throw RuntimeException("Invalid property name", __FILE__, __LINE__);
            }

            const auto filterArgs = filterObject.value(key).toArray();
            if (filterArgs.isEmpty() || filterArgs.count() != 2) {
                throw RuntimeException("Invalid filter arguments", __FILE__, __LINE__);
            }

            const auto filterOp = tSqlComparisonOperatorMap.value(filterArgs[0].toString(), TSql::ComparisonOperator::Invalid);
            if (filterOp == TSql::ComparisonOperator::Invalid) {
                throw RuntimeException("Invalid comparison operator", __FILE__, __LINE__);
            }

            const QJsonValue &jsonValue = filterArgs[1];
            QString value;

            switch (jsonValue.type()) {
                case QJsonValue::Double:
                    value = QVariant(jsonValue.toDouble()).toString();
                    break;
                case QJsonValue::String:
                    value = jsonValue.toString();
                    break;
                case QJsonValue::Bool:
                    value = QVariant(jsonValue.toBool()).toString();
                    break;
                case QJsonValue::Null:
                    break;
                default:
                    QString msg = "Unsupported filter type: ";
                    msg += jsonValue.type();
                    throw RuntimeException(msg, __FILE__, __LINE__);
            }

            criteria.add(propertyIndex, filterOp, value);
        }
    }

    count = mapper->findCount(criteria);

    if (start > 0) {
        mapper->setOffset(start);
    }

    if (limit > 0) {
        mapper->setLimit(limit);
    }

    return criteria;
}

int HttpCriteria::getCount() const {
    return count;
}

TSqlORMapperBase *HttpCriteria::getMapper() const {
    return mapper;
}
