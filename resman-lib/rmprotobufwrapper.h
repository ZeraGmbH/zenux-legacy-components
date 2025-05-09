#ifndef PROTOBUFWRAPPER_H
#define PROTOBUFWRAPPER_H

#include <xiqnetwrapper.h>

class RMProtobufWrapper : public XiQNetWrapper
{
public:
    RMProtobufWrapper();

    std::shared_ptr<google::protobuf::Message> byteArrayToProtobuf(const QByteArray &data) override;
};

#endif // PROTOBUFWRAPPER_H
