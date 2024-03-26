#ifndef AS_H
#define AS_H

#include <cstdint>
#include <cassert>
#include <iostream>

#define REPEAT(n) for (int repeat_index = 0; repeat_index < n; repeat_index++)

uint8_t as_get_first_bit(uint8_t x);
uint8_t as_get_last_bit(uint8_t x);
uint8_t as_right_shift_one(uint8_t x);
uint8_t as_left_shift_one(uint8_t x);
uint8_t as_set_last_bit(uint8_t x, uint8_t one_bit);
uint8_t as_xor_bits(uint8_t one_a, uint8_t one_b);
uint8_t as_and_bits(uint8_t one_a, uint8_t one_b);
uint8_t as_or_bits(uint8_t one_a, uint8_t one_b);
uint8_t as_not_bits(uint8_t one_a);
uint8_t as_xor(uint8_t a, uint8_t b);
uint8_t as_add(uint8_t a, uint8_t b);
uint8_t as_greater_than(uint8_t a, uint8_t b);

#endif