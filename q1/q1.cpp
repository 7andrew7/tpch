
#include <array>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

using identifier_t = uint32_t;
using date_t = uint32_t; // XXX replace with boost gregorian

struct InputRecord {
    identifier_t L_PARTKEY;
    identifier_t L_SUPPKEY;
    int32_t L_LINENUMBER;
    double L_QUANTITY;
    double L_EXTENDEDPRICE;
    double L_DISCOUNT;
    double L_TAX;

    uint8_t L_RETURNFLAG;
    uint8_t L_LINESTATUS;

    date_t L_SHIPDATE;
    date_t L_COMMITDATE;
    date_t L_RECEIPTDATE;

    std::string L_SHIPINSTRUCT;
    std::string L_SHIPMODE;
    std::string L_COMMENT;
};

struct OutputRecord {
    uint8_t l_return_flag;
    uint8_t l_line_status;
    double sum_qty;
    double sum_base_price;
    double sum_disc_price;
    double sum_charge;
    double avg_qty;
    double avg_price;
    double avg_disc;
    int32_t count_order;
};

using InputType = std::vector<struct InputRecord>;
using OutputType = std::vector<struct OutputRecord>;

struct AggEntry {
    double sum_qty;
    double sum_disc;
    double sum_base_price;
    double sum_disc_price;
    double sum_charge;
    int32_t count;
};

OutputType q1(const InputType &input) {
    OutputType output{};

    struct std::array<AggEntry, sizeof(uint8_t) + sizeof(uint8_t)> entry_map{};

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

        OutputRecord _or{l_return_flag, l_line_status, entry->sum_qty,
            entry->sum_base_price, entry->sum_disc_price, entry->sum_charge,
            entry->sum_qty / entry->count, entry->sum_base_price / entry->count,
            entry->sum_disc / entry->count, entry->count};
        output.push_back(_or);
    }

    return output;
}
