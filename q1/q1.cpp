
#include <array>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "q1.h"

struct AggEntry {
    double sum_qty;
    double sum_disc;
    double sum_base_price;
    double sum_disc_price;
    double sum_charge;
    int32_t count;
};

constexpr int num_values(int num_bytes) {
    return 2 << (num_bytes * 8);
}

OutputType q1(const InputType &input) {
    OutputType output{};

    struct std::array<AggEntry, num_values(sizeof(uint8_t) * 2)> entry_map;

    for (const InputRecord &record : input) {
        uint16_t idx = record.L_RETURNFLAG +
            (static_cast<uint16_t>(record.L_LINESTATUS) << 8);
        struct AggEntry *entry = &entry_map[idx];
        entry->sum_qty += record.L_QUANTITY;
        entry->sum_disc += record.L_DISCOUNT;

        double ext_price = record.L_EXTENDEDPRICE;
        entry->sum_base_price += ext_price;

        ext_price *= (1 - record.L_DISCOUNT);
        entry->sum_disc_price += ext_price;

        ext_price *= (1 + record.L_TAX);
        entry->sum_charge += ext_price;

        entry->count++;
    }

    for (std::size_t i = 0; i < entry_map.size(); ++i) {
        if (entry_map[i].count == 0)
            continue;
        AggEntry *entry = &entry_map[i];
        uint8_t l_return_flag = i & 0xFF;
        uint8_t l_line_status = (i >> 8) & 0xFF;

        output.emplace_back(l_return_flag, l_line_status, entry->sum_qty,
            entry->sum_base_price, entry->sum_disc_price, entry->sum_charge,
            entry->sum_qty / entry->count, entry->sum_base_price / entry->count,
            entry->sum_disc / entry->count, entry->count);
    }

    return output;
}
