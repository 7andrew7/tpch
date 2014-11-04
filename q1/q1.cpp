
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

using identifier_t = uint32_t;
using date_t = uint32_t; // XXX replace with boost gregorian

struct LINEITEM_Record {
    identifier_t L_ORDERKEY;
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
    uint8_t l_returnflag;
    uint8_t l_linestatus;
    double sum_qty;
    double sum_base_price;
    double sum_disc_price;
    double sum_charge;
    double avg_qty;
    double avg_price;
    double avg_disc;
    int32_t count_order;
};

using InputType = std::vector<struct LINEITEM_Record>;
using InputRecord = InputType::value_type;
using OutputType = std::vector<struct OutputRecord>;
using OutputRecord = OutputType::value_type;

OutputType q1(const InputType &input) {
    OutputType output{};

    for (const InputRecord &record : input) {
        (void)record;
    }

    return output;
}