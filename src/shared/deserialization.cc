#include "deserialization.hh"
#include <stdexcept>

Deserialization::Deserialization(const uint8_t* data, size_t data_size)
    : data(data),
      size(data_size),
      position(0)
{

}

bool Deserialization::hasBytes(size_t count) const{
    return position + count <= size;
}

uint8_t Deserialization::readUInt8(){
    if(!hasBytes(1)){
        throw std::runtime_error("Packet does not contain enough data");
    }
    return data[position++];
}

int8_t Deserialization::readInt8(){
    return static_cast<uint8_t>(readUInt8());
}

uint32_t Deserialization::readUInt32(){
    if(!hasBytes(4)){
        throw std::runtime_error("Packet does not contain enough data");
    }

    uint32_t value =
        static_cast<uint32_t>(data[position + 0]) |
        (static_cast<uint32_t>(data[position + 1]) << 8) |
        (static_cast<uint32_t>(data[position + 2]) << 16) |
        (static_cast<uint32_t>(data[position + 3]) << 24);

    position += 4;

    return value;
}

int32_t Deserialization::readInt32(){
    return static_cast<int32_t>(readUInt32());
}

float Deserialization::readFloat(){
    uint32_t bits = readUInt32();

    float value;

    static_assert(sizeof(float) == sizeof(uint32_t));

    std::memcpy(&value, &bits, sizeof(float));

    return value;
}

bool Deserialization::readBool(){
    return true ? readUInt8() : false;
}

std::string Deserialization::readString(){

}