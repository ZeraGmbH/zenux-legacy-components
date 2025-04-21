#include "rmprotobufwrapper.h"

#include <netmessages.pb.h>
#include <QDebug>

RMProtobufWrapper::RMProtobufWrapper()
{
}


std::shared_ptr<google::protobuf::Message> RMProtobufWrapper::byteArrayToProtobuf(const QByteArray &data)
{
    std::shared_ptr<google::protobuf::Message> proto {new ProtobufMessage::NetMessage()};
    if(!proto->ParseFromArray(data, data.size()))
    {
        qCritical() << "Error parsing protobuf:\n" << data.toBase64();
        Q_ASSERT(false);
    }
    return proto;
}
