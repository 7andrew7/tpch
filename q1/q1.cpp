
#include <cstdint>
#include <ctime>
#include <iostream>
#include <string>

using identifier_t = uint32_t;

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

    std::time_t L_SHIPDATE;
    std::time_t L_COMMITDATE;
    std::time_t L_RECEIPTDATE;

    std::string L_SHIPINSTRUCT;
    std::string L_SHIPMODE;
    std::string L_COMMENT;
};