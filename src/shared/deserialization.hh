#ifndef DESERIALIZATION_HH
#define DESERIALIZATION_HH

#include <cstdint>

#include <vector>
#include <string>

class Deserialization{
    public:
        Deserialization(const uint8_t*, size_t);
        ~Deserialization();

        uint8_t readUInt8();
        uint32_t readUInt32();
        int32_t readInt32();
        float readFloat();
        bool readBool();
        std::string readString();

        bool hasBytes(size_t count) const;

        uint8_t readMessageType();

    private:
        const uint8_t* data;
        size_t size;
        size_t position;
};

#endif