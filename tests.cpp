#include <gtest/gtest.h>
#include "twelve.hpp"

using namespace std;

// Тесты конструкторов
TEST(TwelveTest, DefaultConstructor) {
    Twelve num;
    EXPECT_EQ(num.toString(), "0");
    EXPECT_EQ(num.getSize(), 1);
}

TEST(TwelveTest, InitializerListConstructor) {
    Twelve num{'1', '0', 'A'};
    EXPECT_EQ(num.toString(), "10A");
    
    Twelve num2{'0', '0', '5', 'B'};
    EXPECT_EQ(num2.toString(), "5B");
}

TEST(TwelveTest, InitializerListConstructorThrowsOnEmpty) {
    EXPECT_THROW(Twelve({}), invalid_argument);
}

TEST(TwelveTest, InitializerListConstructorThrowsOnInvalidDigit) {
    EXPECT_THROW(Twelve({'1', 'C', '2'}), invalid_argument); // 'C' недопустимая цифра
}

TEST(TwelveTest, StringConstructor) {
    Twelve num("2B4");
    EXPECT_EQ(num.toString(), "2B4");
    
    Twelve num2("000A5");
    EXPECT_EQ(num2.toString(), "A5");
}

TEST(TwelveTest, StringConstructorThrowsOnEmpty) {
    EXPECT_THROW(Twelve(""), invalid_argument);
}

TEST(TwelveTest, StringConstructorThrowsOnInvalidDigit) {
    EXPECT_THROW(Twelve("12G3"), invalid_argument); // 'G' недопустимая цифра
}

// Тесты копирования и перемещения
TEST(TwelveTest, CopyConstructor) {
    Twelve original("1A3");
    Twelve copy(original);
    
    EXPECT_EQ(copy.toString(), "1A3");
    EXPECT_TRUE(original.equals(copy));
}

TEST(TwelveTest, MoveConstructor) {
    Twelve original("1A3");
    Twelve moved(move(original));
    
    EXPECT_EQ(moved.toString(), "1A3");
}

TEST(TwelveTest, CopyAssignment) {
    Twelve original("1A3");
    Twelve assigned;
    assigned = original;
    
    EXPECT_EQ(assigned.toString(), "1A3");
    EXPECT_TRUE(original.equals(assigned));
}

TEST(TwelveTest, MoveAssignment) {
    Twelve original("1A3");
    Twelve assigned;
    assigned = move(original);
    
    EXPECT_EQ(assigned.toString(), "1A3");
}

// Тесты арифметических операций
TEST(TwelveTest, Addition) {
    Twelve num1("123");
    Twelve num2("45");
    Twelve sum = num1.add(num2);
    EXPECT_EQ(sum.toString(), "168");
    
    Twelve num3("A");
    Twelve num4("2");
    Twelve sum2 = num3.add(num4);
    EXPECT_EQ(sum2.toString(), "10");
    
    // Проверка сложения с нулем
    Twelve zero;
    Twelve sum3 = num1.add(zero);
    EXPECT_EQ(sum3.toString(), "123");
}

TEST(TwelveTest, AdditionWithCarry) {
    Twelve num1("B");  // 11
    Twelve num2("1");  // 1
    Twelve sum = num1.add(num2);
    EXPECT_EQ(sum.toString(), "10"); // 11 + 1 = 12 (10 в 12-ричной)
    
    Twelve num3("BB"); // 11*12 + 11 = 143
    Twelve num4("1");  // 1
    Twelve sum2 = num3.add(num4);
    EXPECT_EQ(sum2.toString(), "100"); // 143 + 1 = 144 (100 в 12-ричной)
}

TEST(TwelveTest, Subtraction) {
    Twelve num1("100");
    Twelve num2("1");
    Twelve diff = num1.subtract(num2);
    EXPECT_EQ(diff.toString(), "BB");
    
    Twelve num3("50");
    Twelve num4("10");
    Twelve diff2 = num3.subtract(num4);
    EXPECT_EQ(diff2.toString(), "40");
    
    // Вычитание нуля
    Twelve zero;
    Twelve diff3 = num1.subtract(zero);
    EXPECT_EQ(diff3.toString(), "100");
}

TEST(TwelveTest, SubtractionThrowsWhenLarger) {
    Twelve small("10");
    Twelve large("100");
    
    EXPECT_THROW(small.subtract(large), invalid_argument);
}

TEST(TwelveTest, SubtractionEqualNumbers) {
    Twelve num1("123");
    Twelve num2("123");
    Twelve diff = num1.subtract(num2);
    
    EXPECT_EQ(diff.toString(), "0");
}

// Тесты сравнения
TEST(TwelveTest, Equality) {
    Twelve num1("123");
    Twelve num2("123");
    Twelve num3("124");
    
    EXPECT_TRUE(num1.equals(num2));
    EXPECT_FALSE(num1.equals(num3));
}

TEST(TwelveTest, LessThan) {
    Twelve num1("12");
    Twelve num2("13");
    Twelve num3("100");
    Twelve num4("12");
    
    EXPECT_TRUE(num1.lessThan(num2));
    EXPECT_TRUE(num1.lessThan(num3));
    EXPECT_FALSE(num1.lessThan(num4));
    EXPECT_FALSE(num2.lessThan(num1));
}

TEST(TwelveTest, GreaterThan) {
    Twelve num1("13");
    Twelve num2("12");
    Twelve num3("100");
    Twelve num4("13");
    
    EXPECT_TRUE(num1.greaterThan(num2));
    EXPECT_FALSE(num1.greaterThan(num3));
    EXPECT_FALSE(num1.greaterThan(num4));
    EXPECT_FALSE(num2.greaterThan(num1));
}

// Тесты валидации цифр
TEST(TwelveTest, IsValidDigit) {
    EXPECT_TRUE(Twelve::isValidDigit('0'));
    EXPECT_TRUE(Twelve::isValidDigit('9'));
    EXPECT_TRUE(Twelve::isValidDigit('A'));
    EXPECT_TRUE(Twelve::isValidDigit('a'));
    EXPECT_TRUE(Twelve::isValidDigit('B'));
    EXPECT_TRUE(Twelve::isValidDigit('b'));
    
    EXPECT_FALSE(Twelve::isValidDigit('C'));
    EXPECT_FALSE(Twelve::isValidDigit(' '));
    EXPECT_FALSE(Twelve::isValidDigit('-'));
}

// Тесты граничных случаев
TEST(TwelveTest, LargeNumbers) {
    Twelve num1("BBB"); // 11*144 + 11*12 + 11 = 1727
    Twelve num2("1");   // 1
    Twelve sum = num1.add(num2);
    EXPECT_EQ(sum.toString(), "1000"); // 1728 в 12-ричной
    
    Twelve diff = sum.subtract(num2);
    EXPECT_EQ(diff.toString(), "BBB");
}

TEST(TwelveTest, SingleDigitOperations) {
    Twelve num1("B");
    Twelve num2("3");
    Twelve sum = num1.add(num2);
    EXPECT_EQ(sum.toString(), "12"); // 11 + 3 = 14 (12 в 12-ричной)
    
    Twelve diff = sum.subtract(num2);
    EXPECT_EQ(diff.toString(), "B");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}