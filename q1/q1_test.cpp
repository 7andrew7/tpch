#include "gtest/gtest.h"
#include "q1.h"

TEST(q1, basic) {
    EXPECT_EQ(1 + 2, 3);
}


TEST(q1, small_input) {
    InputType input{
        {1, 2, 3, 4.0, 5.0, 6.0, 7.0, 'A', 'B', 90, 100, 110, "however", "now", "comment"},
        {1, 2, 3, 4.0, 5.0, 6.0, 7.0, 'D', 'E', 90, 100, 110, "however", "now", "comment"},
        {1, 2, 3, 4.0, 5.0, 6.0, 7.0, 'A', 'B', 90, 100, 110, "however", "now", "comment"}
    };

    OutputType expected_output{};

    OutputType output = q1(input);
    EXPECT_EQ(output, expected_output);
}
