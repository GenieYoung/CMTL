#include "CMTL/common/attributes.h"
#include <iostream>
#include <gtest/gtest.h>

TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

// int main()
// {
//     CMTL::Attributes attr;
//     attr.set<int>("number") = 1;
//     attr.set<std::string>("string") = "hello";
//     std::cout << attr.get<int>("number") << " " << attr.get<std::string>("string") << std::endl;
//     attr.set<int>("number") = 2;
//     attr.set<std::string>("string") = "world";
//     std::cout << attr.get<int>("number") << " " << attr.get<std::string>("string") << std::endl;

//     //attr.set<std::string>("number") = "2";
//     return 0;
// }