#include "CMTL/common/attributes.h"

#include <iostream>

#include <gtest/gtest.h>

TEST(AttributeTest, Test) {
  CMTL::Attributes attr;
  EXPECT_EQ(attr.contains("int"), false);
  EXPECT_EQ(attr.try_get<int>("int"), nullptr);
  EXPECT_THROW(attr.get<int>("int"), std::bad_any_cast);

  attr.set<int>("int") = 1;
  ASSERT_TRUE(attr.contains("int"));
  ASSERT_FALSE(attr.contains("double"));
  EXPECT_EQ(attr.try_get<double>("int"), nullptr);
  EXPECT_EQ(attr.get<int>("int"), 1);
  EXPECT_THROW(attr.get<double>("int"), std::bad_any_cast);
  EXPECT_THROW(attr.set<double>("int") = 3.14, std::bad_any_cast);

  attr.set<int>("int") = 2;
  EXPECT_EQ(attr.get<int>("int"), 2);

  attr.set<double>("double") = 3.14;
  ASSERT_TRUE(attr.contains("double"));
  EXPECT_EQ(attr.try_get<int>("double"), nullptr);
  EXPECT_EQ(attr.get<double>("double"), 3.14);
  EXPECT_THROW(attr.get<int>("double"), std::bad_any_cast);
  EXPECT_THROW(attr.set<int>("double") = 1, std::bad_any_cast);

  const auto& attr2 = attr;
  EXPECT_TRUE(attr2.contains("int"));
  EXPECT_TRUE(attr2.contains("double"));
  EXPECT_NE(attr2.try_get<int>("int"), nullptr);
  EXPECT_EQ(attr2.get<int>("int"), 2);

  CMTL::Attributes attr3 = attr;
  EXPECT_TRUE(attr3.contains("int"));
  EXPECT_TRUE(attr3.contains("double"));
  EXPECT_EQ(attr3.get<int>("int"), 2);
  EXPECT_EQ(attr3.get<double>("double"), 3.14);

  attr3.remove("int");
  EXPECT_FALSE(attr3.contains("int"));
  attr3.remove("double");
  EXPECT_FALSE(attr3.contains("double"));

  attr3.set<double>("int") = 1.1;
  EXPECT_TRUE(attr3.contains("int"));
  EXPECT_EQ(attr3.get<double>("int"), 1.1);

  attr3.clear();
  EXPECT_FALSE(attr3.contains("int"));
}

// int main()
// {
// }