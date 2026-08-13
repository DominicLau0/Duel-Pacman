#include "serialization.hh"

void Serialization::writeUInt8(uint8_t value){
    buffer.push_back(value);
}

void Serialization::writeUInt32(uint32_t value){
    buffer.push_back(static_cast<uint8_t>((value >> 0) & 0xFF));
    buffer.push_back(static_cast<uint8_t>((value >> 8) & 0xFF));
    buffer.push_back(static_cast<uint8_t>((value >> 16) & 0xFF));
    buffer.push_back(static_cast<uint8_t>((value >> 24) & 0xFF));
}

void Serialization::writeInt32(int32_t value){
    writeUInt32(static_cast<uint32_t>(value));
}

void Serialization::writeFloat(float value){
    uint32_t bits;

    static_assert(sizeof(float) == sizeof(uint32_t));

    std::memcpy(&bits, &value, sizeof(float));

    writeUInt32(bits);
}

void Serialization::writeBool(bool value){
    writeUInt8(value ? 1:0);
}

void Serialization::writeString(const std::string& value){
}

const std::vector<uint8_t>& Serialization::data() const{
    return buffer;
}