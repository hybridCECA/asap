#include <limits>
#include <cassert>
#include <iostream>

#include "as.h"

int main (int argc, char** argv) {
    for (uint16_t i = 0; i < std::numeric_limits<uint8_t>::max(); i++) {
        assert ((i & 1) == as_get_first_bit(i));
    }

    for (uint16_t i = 0; i < std::numeric_limits<uint8_t>::max(); i++) {
        assert (((i >> 7) & 1) == as_get_last_bit(i));
    }

    for (uint16_t i = 0; i < std::numeric_limits<uint8_t>::max(); i++) {
        assert ((i >> 1) == as_right_shift_one(i));
    }

    for (uint16_t i = 0; i < std::numeric_limits<uint8_t>::max(); i++) {
        assert (static_cast<uint8_t>(i << 1) == as_left_shift_one(i));
    }

    for (uint16_t i = 0; i < std::numeric_limits<uint8_t>::max(); i++) {
        assert ((i & ~(1 << 7)) == as_set_last_bit(i, 0));
        assert ((i | (1 << 7)) == as_set_last_bit(i, 1));
    }

    assert (0 == as_xor_bits(0, 0));
    assert (1 == as_xor_bits(0, 1));
    assert (1 == as_xor_bits(1, 0));
    assert (0 == as_xor_bits(1, 1));

    assert (0 == as_and_bits(0, 0));
    assert (0 == as_and_bits(0, 1));
    assert (0 == as_and_bits(1, 0));
    assert (1 == as_and_bits(1, 1));

    assert (0 == as_or_bits(0, 0));
    assert (1 == as_or_bits(0, 1));
    assert (1 == as_or_bits(1, 0));
    assert (1 == as_or_bits(1, 1));

    for (uint16_t i = 0; i < std::numeric_limits<uint8_t>::max(); i++) {
        for (uint16_t j = 0; j < std::numeric_limits<uint8_t>::max(); j++) {
            assert ((i ^ j) == as_xor(i, j));
        }
    }

    for (uint16_t i = 0; i < std::numeric_limits<uint8_t>::max(); i++) {
        for (uint16_t j = 0; j < std::numeric_limits<uint8_t>::max(); j++) {
            assert (static_cast<uint8_t>(i + j) == as_add(i, j));
        }
    }

    for (uint16_t i = 0; i < std::numeric_limits<uint8_t>::max(); i++) {
        for (uint16_t j = 0; j < std::numeric_limits<uint8_t>::max(); j++) {
            assert ((i > j ? 1 : 0) == as_greater_than(i, j));
        }
    }
}