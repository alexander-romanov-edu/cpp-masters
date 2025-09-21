#include <stwine/string_twine.hpp>

#include <gtest/gtest.h>

#include <array>
#include <string>

using namespace std::string_literals;
TEST(string_twine, single_string) {
  std::string str = "my very very very long string number";
  std::string_view strview = "my very very very long string number";
  const char cstr[] = "my very very very long string number";
  EXPECT_STREQ(str.c_str(), mcpp::string_twine(str).str().c_str());
  EXPECT_STREQ(strview.data(), mcpp::string_twine(strview).str().c_str());
  EXPECT_STREQ(cstr, mcpp::string_twine(cstr).str().c_str());
}

TEST(string_twine, concat_2) {
  std::string str1 = "my very very very long string number1";
  std::string str2 = "my very very very long string number2";
  auto sum1 = str1 + str2;
  auto sum2 = mcpp::string_twine(str1).concat(str2).str();
  EXPECT_STREQ(sum1.c_str(), sum2.c_str());
}

TEST(string_twine, concat_3) {
  std::string str1 = "my very very very long string number1";
  std::string str2 = "my very very very long string number2";
  std::string str3 = "my very very very long string number3";
  auto sum1 = str1 + str2 + str3;
  auto sum2 = mcpp::string_twine(str1).concat(str2).concat(str3).str();
  EXPECT_STREQ(sum1.c_str(), sum2.c_str());
}

TEST(string_twine, operator_plus_string_view_2) {
  std::string str1 = "my very very very long string number1";
  std::string str2 = "my very very very long string number2";
  auto sum1 = str1 + str2;
  auto sum2 = (mcpp::string_twine(str1) + std::string_view(str2)).str();
  EXPECT_STREQ(sum1.c_str(), sum2.c_str());
}

TEST(string_twine, operator_plus_string_view_lhs_2) {
  std::string str1 = "my very very very long string number1";
  std::string str2 = "my very very very long string number2";
  auto sum1 = str1 + str2;
  auto sum2 = (std::string_view(str1) + mcpp::string_twine(str2)).str();
  EXPECT_STREQ(sum1.c_str(), sum2.c_str());
}

TEST(string_twine, operator_plus_string_view_3) {
  std::string str1 = "my very very very long string number1";
  std::string str2 = "my very very very long string number2";
  auto sum1 = str1 + str2 + str2;
  auto sum2 = (std::string_view(str1) + mcpp::string_twine(str2) +
               mcpp::string_twine(str2))
                  .str();
  EXPECT_STREQ(sum1.c_str(), sum2.c_str());
}

TEST(string_twine, operator_plus_cstr_2) {
  std::string str1 = "my very very very long string number1";
  auto sum1 = str1 + "my very very very long string number2";
  auto sum2 =
      (mcpp::string_twine(str1) + "my very very very long string number2")
          .str();
  EXPECT_STREQ(sum1.c_str(), sum2.c_str());
}

TEST(string_twine, operator_plus_many_cstr) {
  auto sum1 = "I "s + "append " + "strings " + "pretty " + "often";
  auto sum2 =
      (mcpp::string_twine("I ") + "append " + "strings " + "pretty " + "often")
          .str();
  EXPECT_STREQ(sum1.c_str(), sum2.c_str());
}

TEST(string_twine, operator_plus_many_cstr_2) {
  auto sum1 = "I "s + "append " + "strings " + "pretty " + "often";
  auto sum2 =
      (mcpp::string_twine("I ") + "append " + (mcpp::string_twine("strings ") + "pretty " + "often"))
          .str();
  EXPECT_STREQ(sum1.c_str(), sum2.c_str());
}

TEST(string_twine, operator_concat_many_strings) {
  std::array<std::string, 5> strs = {"I "s, "append ", "strings ", "pretty ",
                                     "often"};
  auto sum1 = strs[0] + strs[1] + strs[2] + strs[3] + strs[4];
  auto sum2 =
      (mcpp::string_twine(strs[0]).concat(strs[1]).concat(mcpp::string_twine(strs[2]).concat(strs[3]).concat(strs[4])))
          .str();
  EXPECT_STREQ(sum1.c_str(), sum2.c_str());
}
