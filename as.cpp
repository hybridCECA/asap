#include "as.h"

uint8_t as_scrub_non_first_bits(uint8_t x) {
    asm (
        "shr $8, %%al;"
        "add %0, %%al;"
        "shr $1, %%al;"
        "add %%al, %%al;"
        "add %%al, %0;"
        : "=r" ( x )
        : "0" ( x )
        : "%al"
    );

    return x;
}

uint8_t as_get_first_bit(uint8_t x) {
    REPEAT (7)
        x = as_scrub_non_first_bits(x);

    return x;
}

uint8_t as_get_last_bit(uint8_t x) {
    asm (
        "shr $7, %0;"
        : "=r" ( x )
        : "0" ( x )
        :
    );

    assert(x <= 1);

    return x;
}

uint8_t as_right_shift_one(uint8_t x) {
    asm (
        "shr $1, %0;"
        : "=r" ( x )
        : "0" ( x )
        :
    );

    return x;
}


uint8_t as_left_shift_one(uint8_t x) {
    asm (
        "add %0, %0;"
        : "=r" ( x )
        : "0" ( x )
        :
    );

    return x;
}

uint8_t as_set_last_bit(uint8_t x, uint8_t one_bit) {
    assert(one_bit <= 1);

    REPEAT (7)
        one_bit = as_left_shift_one(one_bit);

    x = as_left_shift_one(x);
    x = as_right_shift_one(x);

    asm (
        "add %2, %0;"
        : "=r" ( x )
        : "0" ( x ), "r" ( one_bit )
        :
    );

    return x;
}


uint8_t as_xor_bits(uint8_t one_a, uint8_t one_b) {
    assert(one_a <= 1);
    assert(one_b <= 1);

    asm (
        "add %2, %0;"
        : "=r" ( one_a )
        : "0" ( one_a ), "r" ( one_b )
        :
    );

    return as_get_first_bit(one_a);
}

uint8_t as_and_bits(uint8_t one_a, uint8_t one_b) {
    assert(one_a <= 1);
    assert(one_b <= 1);

    asm (
        "add %2, %0;"
        "shr $1, %0;"
        : "=r" ( one_a )
        : "0" ( one_a ), "r" ( one_b )
        :
    );

    return one_a;
}

uint8_t as_or_bits(uint8_t one_a, uint8_t one_b) {
    assert(one_a <= 1);
    assert(one_b <= 1);

    one_a = as_not_bits(one_a);
    one_b = as_not_bits(one_b);

    return as_not_bits(as_and_bits(one_a, one_b));
}

uint8_t as_not_bits(uint8_t one_a) {
    assert(one_a <= 1);

    return as_xor_bits(one_a, 1);
}

uint8_t as_xor(uint8_t a, uint8_t b) {
    uint8_t one_a, one_b, one_out;
    uint8_t out = 0;

    REPEAT (8)
    {
        one_a = as_get_first_bit(a);
        one_b = as_get_first_bit(b);
        one_out = as_xor_bits(one_a, one_b);

        a = as_right_shift_one(a);
        b = as_right_shift_one(b);
        out = as_right_shift_one(out);

        out = as_set_last_bit(out, one_out);
    }

    return out;
}

uint8_t as_add(uint8_t a, uint8_t b) {
    asm (
        "add %2, %0;"
        : "=r" ( a )
        : "0" ( a ), "r" ( b )
        :
    );

    return a;
}



uint8_t as_greater_than(uint8_t a, uint8_t b) {
    uint8_t one_a, one_b;
    uint8_t one_b_gt = 0;
    uint8_t out = 0;

    REPEAT (8)
    {
        one_a = as_get_last_bit(a);
        one_b = as_get_last_bit(b);

        one_b_gt = as_or_bits(one_b_gt, as_and_bits(as_not_bits(one_a), one_b));
        out = as_or_bits(out, as_and_bits(as_and_bits(one_a, as_not_bits(one_b)), as_not_bits(one_b_gt)));

        a = as_left_shift_one(a);
        b = as_left_shift_one(b);
    }

    return out;
}

uint8_t as_not(uint8_t a) {
    uint8_t out = 0;

    REPEAT (8) {
        out = as_right_shift_one(out);

        uint8_t not_bit = as_not_bits(as_get_first_bit(a));
        out = as_set_last_bit(out, not_bit);
        a = as_right_shift_one(a);
    }

    return out;
}

uint8_t as_and(uint8_t a, uint8_t b) {
    uint8_t one_a, one_b, one_out;
    uint8_t out = 0;

    REPEAT (8)
    {
        one_a = as_get_first_bit(a);
        one_b = as_get_first_bit(b);
        one_out = as_and_bits(one_a, one_b);

        a = as_right_shift_one(a);
        b = as_right_shift_one(b);
        out = as_right_shift_one(out);

        out = as_set_last_bit(out, one_out);
    }

    return out;
}

uint8_t as_or(uint8_t a, uint8_t b) {
    uint8_t one_a, one_b, one_out;
    uint8_t out = 0;

    REPEAT (8)
    {
        one_a = as_get_first_bit(a);
        one_b = as_get_first_bit(b);
        one_out = as_or_bits(one_a, one_b);

        a = as_right_shift_one(a);
        b = as_right_shift_one(b);
        out = as_right_shift_one(out);

        out = as_set_last_bit(out, one_out);
    }

    return out;
}

uint8_t as_ternary(uint8_t cond, uint8_t a, uint8_t b) {
    assert(cond <= 1);

    uint8_t mask = 0;

    REPEAT (8) {
        mask = as_right_shift_one(mask);
        mask = as_set_last_bit(mask, cond);
    }

    a = as_and(a, mask);
    b = as_and(b, as_not(mask));

    return as_or(a, b);
}

uint8_t as_left_shift(uint8_t a, uint8_t amount) {
    REPEAT (8) {
        uint8_t should_shift = as_greater_than(amount, 0);
        a = as_ternary(should_shift, as_left_shift_one(a), a);
        amount = as_ternary(should_shift, as_add(amount, -1), amount);
    }

    return a;

}