#include "restcontroller.h"

bool RestController::preFilter()
{
    tDebug("RestController::preFilter");  // TODO: fix this
    httpResponse().header().addRawHeader(QByteArrayLiteral("Access-Control-Allow-Origin"), QByteArrayLiteral("*"));
    httpResponse().header().addRawHeader(QByteArrayLiteral("Access-Control-Allow-Methods"), QByteArrayLiteral("GET, PUT, DELETE, OPTIONS, POST"));
    httpResponse().header().addRawHeader(QByteArrayLiteral("Access-Control-Allow-Headers"),
                                         QByteArrayLiteral("Shib-commonName, Shib-userCertificate, Content-Type"));

    return true;
}

QMap<QJsonParseError::ParseError, QString> RestController::jsonParseErrorMap{
        {QJsonParseError::NoError,               "No error occurred"},
        {QJsonParseError::UnterminatedObject,    "An object is not correctly terminated with a closing curly bracket"},
        {QJsonParseError::MissingNameSeparator,  "A comma separating different items is missing"},
        {QJsonParseError::UnterminatedArray,     "The array is not correctly terminated with a closing square bracket"},
        {QJsonParseError::MissingValueSeparator, "A colon separating keys from values inside objects is missing"},
        {QJsonParseError::IllegalValue,          "The value is illegal"},
        {QJsonParseError::TerminationByNumber,   "The input stream ended while parsing a number"},
        {QJsonParseError::IllegalNumber,         "The number is not well formed"},
        {QJsonParseError::IllegalEscapeSequence, "An illegal escape sequence occurred in the input"},
        {QJsonParseError::IllegalUTF8String,     "An illegal UTF8 sequence occurred in the input"},
        {QJsonParseError::UnterminatedString,    "A string wasn't terminated with a quote"},
        {QJsonParseError::MissingObject,         "An object was expected but couldn't be found"},
        {QJsonParseError::DeepNesting,           "The JSON document is too deeply nested for the parser to parse it"},
        {QJsonParseError::DocumentTooLarge,      "The JSON document is too large for the parser to parse it"},
        {QJsonParseError::GarbageAtEnd,          "The parsed document contains additional garbage characters at the end"}
};

void RestController::options() {
    tDebug("RestController::options 0");
    renderText(nullptr);
}

void RestController::options(const QString &arg1 __attribute__((unused))) {
    tDebug("RestController::options 1");
    options();
}

void RestController::options(const QString &arg1 __attribute__((unused)), const QString &arg2 __attribute__((unused))) {
    tDebug("RestController::options 2");
    options();
}

void RestController::options(const QString &arg1 __attribute__((unused)), const QString &arg2 __attribute__((unused)), const QString &arg3 __attribute__((unused))) {
    tDebug("RestController::options 3");
    options();
}

void RestController::options(const QString &arg1 __attribute__((unused)), const QString &arg2 __attribute__((unused)), const QString &arg3 __attribute__((unused)), const QString &arg4 __attribute__((unused))) {
    tDebug("RestController::options 4");
    options();
}

void RestController::renderJsonSuccess(const QJsonValue &data, int count) {
    QJsonObject result{
            {"success", true},
            {"msg", QJsonValue::Null}
    };

    if (data.isArray()) {
        result.insert("total", count);
    }
    else {
        result.insert("total", QJsonValue::Null);
    }
    result.insert("data", data);

    renderJson(result);
}

void RestController::renderJsonFail(const QString &msg) {
    QJsonObject result{
            {"success", false},
            {"msg", msg},
            {"total", QJsonValue::Null},
            {"data", QJsonValue::Null}
    };

    renderJson(result);
}

QJsonDocument RestController::getDocument() {
    QIODevice *qioDevice = this->httpRequest().rawBody();

    if (!qioDevice->isOpen()) {
        if (!qioDevice->open(QIODevice::ReadOnly)) {
            throw RuntimeException("Could not open QIODevice", __FILE__, __LINE__);
        }
    }

    QJsonParseError e{};
    const QJsonDocument &qjd = QJsonDocument::fromJson(qioDevice->readAll(), &e);
    if (e.error != QJsonParseError::NoError) {
        throw RuntimeException(e.errorString(), __FILE__, __LINE__);
    }
    return qjd;
}

// Don't remove below this line
T_DEFINE_CONTROLLER(RestController)
