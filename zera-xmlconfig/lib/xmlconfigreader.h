#ifndef XMLCONFIGREADER_H
#define XMLCONFIGREADER_H

#include "zera-xmlconfig_export.h"
#include <QObject>
#include <QXmlStreamWriter>
#include <QIODevice>

namespace Zera
{
namespace XMLConfig
{

class cReaderPrivate;

class ZERA_XMLCONFIG_EXPORT cReader : public QObject
{
    Q_OBJECT
public:
    explicit cReader(QObject *parent = 0);
    ~cReader();

    bool loadXMLFile(const QString &path);
    bool loadXMLFromString(const QString &xmlString);
    QString getValue(const QString &key);
    bool setValue(const QString &key, const QString &value);
    QString getXMLConfig();
signals:
    void valueChanged(QString key);
    void finishedParsingXML(bool ok);

protected:
    Zera::XMLConfig::cReaderPrivate *d_ptr;
private:
    bool loadXMLFromStringWithoutSchema(const QString &xmlString);
    bool xml2Config(QIODevice* xmlData);
    void parseLists(QList<QString> oldList, QList<QString> newList, QXmlStreamWriter &writer);

    Q_DISABLE_COPY(cReader)
    Q_DECLARE_PRIVATE(cReader)
};
}
}

#endif // XMLCONFIGREADER_H
