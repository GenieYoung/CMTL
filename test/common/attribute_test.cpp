#include "CMTL/common/attributes.h"

#include <iostream>

#include <gtest/gtest.h>

TEST(AttributeTest, SetGetTest) {
  CMTL::Attributes attr;

  attr.set<int>("number") = 1;
  ASSERT_TRUE(attr.contain("number"));
  // EXPECT_DEATH({attr.set<char>("number") = '1';}, "attribute with specific
  // type not found"); EXPECT_DEATH({attr.get<int>("Number");}, "attribute with
  // specific name not found"); EXPECT_DEATH({attr.get<char>("number");},
  // "attribute with specific type not found");
  EXPECT_EQ(attr.get<int>("number"), 1);
  attr.set<int>("number") = 2;
  EXPECT_EQ(attr.get<int>("number"), 2);

  attr.set<std::string>("string") = "hello";
  ASSERT_TRUE(attr.contain("string"));
  EXPECT_EQ(attr.get<std::string>("string"), "hello");
  attr.set<std::string>("string") = "world";
  EXPECT_EQ(attr.get<std::string>("string"), "world");

  CMTL::Attributes attr2 = attr;
  EXPECT_TRUE(attr2.contain("number"));
  EXPECT_TRUE(attr2.contain("string"));
  EXPECT_EQ(attr.get<int>("number"), 2);
  EXPECT_EQ(attr.get<std::string>("string"), "world");
  attr2.remove("number");
  EXPECT_FALSE(attr2.contain("number"));
  attr2.remove("string");
  EXPECT_FALSE(attr2.contain("string"));
  attr2.set<char>("number") = '3';
  // EXPECT_DEATH({attr2.get<int>("number");}, "attribute with specific type not
  // found");
  EXPECT_TRUE(attr2.contain("number"));
  EXPECT_EQ(attr2.get<char>("number"), '3');
  attr2.clear();
  EXPECT_FALSE(attr2.contain("number"));
}

// int main()
// {
//     CMTL::Attributes attr;
//     attr.set<int>("number") = 1;
//     attr.set<std::string>("string") = "hello";
//     std::cout << attr.get<int>("number") << " " <<
//     attr.get<std::string>("string") << std::endl; attr.set<int>("number") =
//     2; attr.set<std::string>("string") = "world"; std::cout <<
//     attr.get<int>("number") << " " << attr.get<std::string>("string") <<
//     std::endl;

//     //attr.set<std::string>("number") = "2";
//     return 0;
// }