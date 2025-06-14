//
// Created by topau on 15/03/2025.
//

#ifndef RASTROS_BITSTORAGE_H
#define RASTROS_BITSTORAGE_H

#include <cstdint>


class BitStorage {
public:

    explicit BitStorage(uint64_t value = 0);

    //explicit BitStorage(uint64_t data);

    // Set a specific bit
    void setBit(int bitIndex);

    // Clear a specific bit
    void clearBit(int bitIndex);

    // Toggle a specific bit
    void toggleBit(int bitIndex);

    // Check if a specific bit is set
    [[nodiscard]] bool isBitSet(int bitIndex) const;

    // Get the full 64-bit number
    [[nodiscard]] uint64_t getValue() const;

    // Set the full 64-bit number.
    void setValue(uint64_t value);

    void setMostSignificant6Bits(uint8_t value);

    [[nodiscard]] int getMostSignificant6Bits() const;

    int getTamanhoA() const;

    int getTamanhoL() const;

    void setTamanho(int a, int l);

    bool operator==(const BitStorage &rhs) const;

    bool operator!=(const BitStorage &rhs) const;


private:
    uint64_t data_;


};



#endif //RASTROS_BITSTORAGE_H
