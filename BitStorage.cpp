//
// Created by topau on 15/03/2025.
// Código gerado por Gemini 2.0
// Classe para ler e escrever os bits de uma variável de 64 bits
//os primeiros 50 são para guardar um jogo de 7x7. Do 51 ao 56 para o tamanho do tabuleiro.
// O bit 57 servirá para registar o jogador a jogar (apesar de poder ser inferido pelo número de jogadas, mas é mais rápido consultar o bit)
// Os últimos 6 bits registam a posição da peça:"caracol"


#include "BitStorage.h"

BitStorage::BitStorage(uint64_t value) : data_(value) {}

void BitStorage::setBit(int bitIndex) {
    if (bitIndex >= 0 && bitIndex < 64) {
        data_ |= (1ULL << bitIndex);
    }
}

bool BitStorage::operator==(const BitStorage &rhs) const {
    return data_ == rhs.data_;
}

bool BitStorage::operator!=(const BitStorage &rhs) const {
    return !(rhs == *this);
}

void BitStorage::clearBit(int bitIndex) {
    if (bitIndex >= 0 && bitIndex < 64) {
        data_ &= ~(1ULL << bitIndex);
    }
}

void BitStorage::toggleBit(int bitIndex) {
    if (bitIndex >= 0 && bitIndex < 64) {
        data_ ^= (1ULL << bitIndex);
    }
}

bool BitStorage::isBitSet(int bitIndex) const {
    if (bitIndex >= 0 && bitIndex < 64) {
        return (data_ & (1ULL << bitIndex)) != 0;
    }
    return false; // Or throw an exception for invalid index
}

uint64_t BitStorage::getValue() const {
    return data_;
}

void BitStorage::setValue(uint64_t value) {
    data_ = value;
}

// Set the most significant 6 bits (positions 58-63)
void BitStorage::setMostSignificant6Bits(uint8_t value) {
    if (value >= 0 && value <= 63) {
        // Clear the most significant 6 bits
        data_ &= ~(0x3FULL << 58); // Shift the mask to the correct position

        // Set the most significant 6 bits
        data_ |= (static_cast<uint64_t>(value) << 58);
    }
}

// Get the most significant 6 bits as a decimal number
int BitStorage::getMostSignificant6Bits() const {
    return static_cast<int>((data_ >> 58) & 0x3FULL); // Shift and mask
}

void BitStorage::setTamanho(int a, int l) {
    // Store 'a' in bits 51-54
    data_ |= (static_cast<uint64_t>(a) << 51);

    // Store 'l' in bits 53-55
    data_ |= (static_cast<uint64_t>(l) << 54);
}

//Get the a value
int BitStorage::getTamanhoA() const {
    return static_cast<int>((data_ >> 51) & 0x7ULL);
}
//Get the l value.
int BitStorage::getTamanhoL() const {
    return static_cast<int>((data_ >> 54) & 0x7ULL);
}



