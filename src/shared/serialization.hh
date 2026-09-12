#ifndef SERIALIZATION_HH
#define SERIALIZATION_HH

#include <cstdint>
#include <cstring>

#include <vector>
#include <string>

class Serialization{
    public:       
        void writeUInt8(uint8_t);
        void writeInt8(int8_t);
        void writeUInt32(uint32_t);
        void writeInt32(int32_t);
        void writeFloat(float);
        void writeBool(bool);

        const std::vector<uint8_t>& getSerializedData() const;
    private:
        std::vector<uint8_t> buffer;
};

#endif