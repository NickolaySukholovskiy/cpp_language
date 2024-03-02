
#include <gtest/gtest.h>

#include "back/s21_calc.h"

TEST(check_function, test_plus)
{
    S21Calc test;
    test.set_string("1+1");
    EXPECT_DOUBLE_EQ(test.GetExpressionResult(), 2);
}

TEST(check_function, test_minus)
{
    S21Calc test;
    test.set_string("2-3");
    EXPECT_DOUBLE_EQ(test.GetExpressionResult(), -1);
}

TEST(check_function, test_mul)
{
    S21Calc test;
    test.set_string("3*4");
    EXPECT_DOUBLE_EQ(test.GetExpressionResult(), 12);
}

TEST(check_function, test_div)
{
    S21Calc test;
    test.set_string("63/9");
    EXPECT_DOUBLE_EQ(test.GetExpressionResult(), 7);
}

TEST(check_function, test_mod)
{
    S21Calc test;
    test.set_string("9mod2");
    EXPECT_DOUBLE_EQ(test.GetExpressionResult(), fmod(9, 2));
}

TEST(check_function, test_pow)
{
    S21Calc test;
    test.set_string("5^2");
    EXPECT_DOUBLE_EQ(test.GetExpressionResult(), 25);
}

TEST(check_function, test_uminus)
{
    S21Calc test;
    test.set_string("-2");
    EXPECT_DOUBLE_EQ(test.GetExpressionResult(), -2);
}

TEST(check_function, test_sqrt)
{
    S21Calc test;
    test.set_string("sqrt(9)");
    EXPECT_DOUBLE_EQ(test.GetExpressionResult(), 3);
}

TEST(check_function, test_sin)
{
    S21Calc test;
    test.set_string("sin(1.2)");
    EXPECT_DOUBLE_EQ(test.GetExpressionResult(), sin(1.2));
}

TEST(check_function, test_cos)
{
    S21Calc test;
    test.set_string("cos(1.2)");
    EXPECT_DOUBLE_EQ(test.GetExpressionResult(), cos(1.2));
}

TEST(check_function, test_tg)
{
    S21Calc test;
    test.set_string("tan(1.2)");
    EXPECT_DOUBLE_EQ(test.GetExpressionResult(), tan(1.2));
}

TEST(check_function, test_asin)
{
    S21Calc test;
    test.set_string("asin(1.2)");
    EXPECT_DOUBLE_EQ(isnan(test.GetExpressionResult()), isnan(asin(1.2)));
}

TEST(check_function, test_acos)
{
    S21Calc test;
    test.set_string("acos(1.2)");
    EXPECT_EQ(isnan(test.GetExpressionResult()), isnan(acos(1.2)));
}

TEST(check_function, test_atan)
{
    S21Calc test;
    test.set_string("atan(1.2)");
    EXPECT_DOUBLE_EQ(test.GetExpressionResult(), atan(1.2));
}

TEST(check_function, test_ln)
{
    S21Calc test;
    test.set_string("ln(1.2)");
    EXPECT_DOUBLE_EQ(test.GetExpressionResult(), log(1.2));
}

TEST(check_function, test_log)
{
    S21Calc test;
    test.set_string("log(1.2)");
    EXPECT_DOUBLE_EQ(test.GetExpressionResult(), log10(1.2));
}

TEST(check_errors, invalid_input_1)
{
    S21Calc test;
    EXPECT_ANY_THROW(test.set_string(""));
}

TEST(check_errors, invalid_input_2)
{
    S21Calc test;
    EXPECT_ANY_THROW(test.set_string("r"));
}

TEST(check_errors, invalid_input_3)
{
    S21Calc test;
    EXPECT_ANY_THROW(test.set_string("())"));
}

TEST(check_errors, invalid_input_4)
{
    S21Calc test;
    test.set_string("()");
    EXPECT_ANY_THROW(test.GetExpressionResult());
}

TEST(check_errors, invalid_input_5)
{
    S21Calc test;
    test.set_string("-");
    EXPECT_ANY_THROW(test.GetExpressionResult());
}

TEST(check_errors, invalid_input_6)
{
    S21Calc test;
    EXPECT_ANY_THROW(test.set_string("sin"));
}

TEST(check_errors, invalid_input_7)
{
    S21Calc test;
    test.set_string("cos()");
    EXPECT_ANY_THROW(test.GetExpressionResult());
}

TEST(check_errors, invalid_input_8)
{
    S21Calc test;
    test.set_string("2-");
    EXPECT_ANY_THROW(test.GetExpressionResult());
}

TEST(check_errors, invalid_input_9)
{
    S21Calc test;
    EXPECT_ANY_THROW(test.set_string("1."));
}

TEST(check_errors, invalid_input_10)
{
    S21Calc test;
    EXPECT_ANY_THROW(test.set_string("."));
}

TEST(check_errors, invalid_input_11)
{
    S21Calc test;
    EXPECT_ANY_THROW(test.set_string(".0"));
}

TEST(check_errors, invalid_input_12)
{
    S21Calc test;
    EXPECT_ANY_THROW(test.set_string("1x"));
}

TEST(check_errors, invalid_input_13)
{
    S21Calc test;
    test.set_string("1^-2");
    EXPECT_ANY_THROW(test.GetExpressionResult());
}

TEST(check_errors, invalid_input_14)
{
    S21Calc test;
    test.set_string("*2");
    EXPECT_ANY_THROW(test.GetExpressionResult());
}

TEST(check_errors, invalid_input_15)
{
    S21Calc test;
    test.set_string("2(1+2)");
    EXPECT_ANY_THROW(test.GetExpressionResult());
}

TEST(check_errors, invalid_arithmetic_1)
{
    S21Calc test;
    test.set_string("2/0");
    EXPECT_ANY_THROW(test.GetExpressionResult());
}

TEST(check_errors, invalid_arithmetic_2)
{
    S21Calc test;
    test.set_string("9mod0");
    EXPECT_ANY_THROW(test.GetExpressionResult());
}

TEST(check_errors, invalid_arithmetic_3)
{
    S21Calc test;
    test.set_string("sqrt(-1)");
    EXPECT_ANY_THROW(test.GetExpressionResult());
}

TEST(check_errors, invalid_arithmetic_4)
{
    S21Calc test;
    test.set_string("ln(-34)");
    EXPECT_ANY_THROW(test.GetExpressionResult());
}

TEST(check_errors, invalid_arithmetic_5)
{
    S21Calc test;
    test.set_string("log(-123)");
    EXPECT_ANY_THROW(test.GetExpressionResult());
}

TEST(check_something, test_all_1)
{
    S21Calc test;
    test.set_string("sqrt(3^2)");
    EXPECT_DOUBLE_EQ(test.GetExpressionResult(), 3);
}

TEST(check_something, test_all_2)
{
    S21Calc test;
    test.set_string("sqrt(9)^2");
    EXPECT_DOUBLE_EQ(test.GetExpressionResult(), 9);
}

TEST(check_something, test_all_3)
{
    S21Calc test;
    test.set_string("(cos(9))^(-1)");
    EXPECT_DOUBLE_EQ(test.GetExpressionResult(), pow(cos(9), -1));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}