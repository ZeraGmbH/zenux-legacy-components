#include "xmlconfigreader.h"
#include "xmlconfigreaderprivate.h"
#include <QStringList>
#include <QByteArray>
#include <QFile>
#include <QBuffer>
#include <QDebug>

namespace Zera
{
namespace XMLConfig
{

cReader::cReader(QObject *parent) :
    QObject(parent), d_ptr(new cReaderPrivate(this))
{
}

cReader::~cReader()
{
    delete d_ptr;
}

bool cReader::loadXMLFile(const QString &path)
{
    QFile xmlFile(path);
    if(xmlFile.open(QFile::ReadOnly)) {
        QString xml = xmlFile.readAll();
        return loadXMLFromString(xml);
    }
    return false;
}

bool cReader::loadXMLFromString(const QString &xmlString)
{
    bool retVal = false;
    QByteArray baXmlData = xmlString.toUtf8();
    QBuffer xmlDevice(&baXmlData);

    xmlDevice.open(QBuffer::ReadOnly);
    if(xml2Config(&xmlDevice))
        retVal = true;
    else
        qWarning("[zera-xml-config] %s is invalid", qPrintable(xmlString));

    xmlDevice.close();
    emit finishedParsingXML(retVal);
    return retVal;
}

QString cReader::getValue(const QString &key)
{
    Q_D(cReader);
    return d->data.getValue(key);
}

bool cReader::setValue(const QString &key, const QString &value)
{
    Q_D(cReader);
    return d->data.modifyExisting(key, value);
}

QString cReader::getXMLConfig()
{
    Q_D(cReader);
    QString retVal = QString();
    QStringList parents, oldParents;
    QXmlStreamWriter stream(&retVal);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();

    const QStringList sortedKeys = d->data.getKeysSortedByCreationSequence();
    for(const QString &key : sortedKeys) {
        QString elementName;
        parents = key.split(":");
        elementName = parents.takeLast();

        parseLists(oldParents, parents, stream);
        oldParents = parents;
        stream.writeTextElement(elementName, d->data.getValue(key));
    }
    stream.writeEndDocument();
    return retVal;
}

bool cReader::xml2Config(QIODevice *xmlData)
{
    QStringList parents;
    QXmlStreamReader xmlReader;
    xmlReader.setDevice(xmlData);
    bool retVal = true;

    for(QXmlStreamReader::TokenType token; (!xmlReader.atEnd() && !xmlReader.hasError()); token = xmlReader.readNext()) {
        switch(token) {
        // we read the actual data that stands between a start and an end node
        case QXmlStreamReader::Characters: {
            // ignore whitespaces
            if(!xmlReader.text().isEmpty()&&!xmlReader.isWhitespace()) {
                Q_D(cReader);
                QString fullPath = parents.join(":");
                d->data.insert(fullPath, xmlReader.text().toString());
                emit valueChanged(fullPath);
            }
            break;
        }
        // add the node name as parent if it is a start node: <text>
        case QXmlStreamReader::StartElement: {
            parents.append(xmlReader.name().toString());
            break;
        }
        // remove the last node from the parents if it is and end node: </text>
        case QXmlStreamReader::EndElement: {
            parents.removeLast();
            break;
        }
        default:
            break;
        }
    }

    /* Error handling. */
    if(xmlReader.hasError()) {
        retVal = false;
        qWarning("[zera-xml-config] Error parsing XML: %s", qPrintable(xmlReader.errorString()));
    }
    return retVal;
}


void cReader::parseLists(QList<QString> oldList, QList<QString> newList, QXmlStreamWriter &writer)
{
    if(oldList.count() > newList.count()) {
        oldList.removeLast();
        writer.writeEndElement();
        parseLists(oldList, newList, writer);
    }
    else if(oldList.isEmpty() == false) {
        if(oldList.at(0) == newList.at(0)) {
            oldList.removeFirst();
            newList.removeFirst();
            parseLists(oldList, newList, writer);
        }
        else
        {
            for(int i=0; i<oldList.count(); ++i) {
                writer.writeEndElement();
            }
            for(int i=0; i<newList.count(); ++i) {
                writer.writeStartElement(newList.at(i));
            }
        }
    }
    else
    {
        for(int i=0; i<newList.count(); ++i) {
            writer.writeStartElement(newList.at(i));
        }
    }
}

}
}
