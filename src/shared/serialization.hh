#ifndef SERIALIZATION_HH
#define SERIALIZATION_HH

#include <cstdint>

#include <vector>
#include <string>

class Serialization{
    public:       
        void writeUInt8(uint8_t);
        void writeUInt32(uint32_t);
        void writeInt32(int32_t);
        void writeFloat(float);
        void writeBool(bool);
        void writeString(const std::string&);

        const std::vector<uint8_t>& data() const;
    private:
        std::vector<uint8_t> buffer;
};

#endif