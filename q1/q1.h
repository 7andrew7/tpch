#include <cstdint>

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

    OutputRecord(uint8_t l_return_flag, uint8_t l_line_status, double sum_qty,
        double sum_base_price, double sum_disc_price,  double sum_charge,
        double avg_qty, double avg_price, double avg_disc,
        int32_t count_order):
        l_return_flag{l_return_flag},
        l_line_status{l_line_status},
        sum_qty{sum_qty},
        sum_base_price{sum_base_price},
        sum_disc_price{sum_disc_price},
        sum_charge{sum_charge},
        avg_qty{avg_qty},
        avg_price{avg_price},
        avg_disc{avg_disc},
        count_order{count_order} {}

    bool operator==(const OutputRecord &other) const {
        return
            sum_disc_price == other.sum_base_price &&
            sum_disc_price == other.sum_disc_price;

    }
};

using InputType = std::vector<struct InputRecord>;
using OutputType = std::vector<struct OutputRecord>;

OutputType q1(const InputType &input);
