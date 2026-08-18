#include "CMTL/common/numeric_utils.h"

#include <type_traits>

#include <gtest/gtest.h>

TEST(NumberUtilsTest, CastTest) {
  EXPECT_DOUBLE_EQ(CMTL::to_double(2), 2.0);
  static_assert(std::is_same<decltype(CMTL::sqrt(4)), double>::value,
                "sqrt(int) should return double");
  EXPECT_EQ(CMTL::to_string(42), "42");

#ifdef USE_GMP
  EXPECT_DOUBLE_EQ(CMTL::to_double(mpq_class(1, 3)), 1 / 3.0);
  EXPECT_DOUBLE_EQ(CMTL::to_double(mpq_class(1, 6) + mpq_class(1, 6)), 1 / 3.0);
  EXPECT_EQ(CMTL::to_string(mpq_class(1, 2)), "1/2");
  EXPECT_EQ(CMTL::to_string(mpq_class(1, 3) + mpq_class(1, 6)), "1/2");
#endif

#ifdef USE_CORE
  EXPECT_DOUBLE_EQ(CMTL::to_double(CORE::Expr("1/3")), 1 / 3.0);
  EXPECT_EQ(CMTL::to_string(CORE::BigRat("1/2")), "1/2");
#endif

#if defined(USE_GMP) && defined(USE_CORE)
  EXPECT_TRUE(CMTL::to_core_expr(mpq_class(1, 3)) == CORE::Expr("1/3"));
  EXPECT_TRUE(CMTL::to_core_expr(mpq_class(1, 3) + mpq_class(1, 6)) ==
              CORE::Expr("1/2"));
#endif
}

TEST(NumberUtilsTest, MathTest) {
  EXPECT_DOUBLE_EQ(CMTL::sqrt(4.0), 2.0);
  EXPECT_EQ(CMTL::abs(-2), 2);

#ifdef USE_GMP
  EXPECT_TRUE(CMTL::abs(mpq_class(-1, 3)) == mpq_class(1, 3));
  EXPECT_TRUE(CMTL::abs(mpq_class(-1, 3) + mpq_class(-1, 6)) ==
              mpq_class(1, 2));
  EXPECT_TRUE(CMTL::min(mpq_class(1, 3), mpq_class(1, 6)) == mpq_class(1, 6));
  EXPECT_TRUE(CMTL::min(mpq_class(1, 3) + mpq_class(1, 3), mpq_class(1, 2)) ==
              mpq_class(1, 2));
  EXPECT_TRUE(CMTL::min(mpq_class(1, 3) + mpq_class(1, 6),
                        mpq_class(1, 2) * mpq_class(2, 3)) == mpq_class(1, 3));
  EXPECT_TRUE(CMTL::max(mpq_class(1, 3), mpq_class(1, 6)) == mpq_class(1, 3));
  EXPECT_TRUE(CMTL::max(mpq_class(1, 3) + mpq_class(1, 3), mpq_class(1, 2)) ==
              mpq_class(2, 3));
  EXPECT_TRUE(CMTL::max(mpq_class(1, 3) + mpq_class(1, 6),
                        mpq_class(1, 2) * mpq_class(2, 3)) == mpq_class(1, 2));
#endif

#ifdef USE_CORE
  EXPECT_TRUE(CMTL::abs(CORE::Expr("-1/3")) == CORE::Expr("1/3"));
  EXPECT_TRUE(CMTL::abs(CORE::Expr("-1/3") + CORE::Expr("-1/6")) ==
              CORE::Expr("1/2"));
  EXPECT_TRUE(CMTL::min(CORE::Expr("1/3"), CORE::Expr("1/6")) ==
              CORE::Expr("1/6"));
  EXPECT_TRUE(CMTL::max(CORE::Expr("1/3"), CORE::Expr("1/6")) ==
              CORE::Expr("1/3"));

  CORE::Expr sqrt2 = CMTL::sqrt(CORE::Expr(2));
  CORE::Expr sqrt3 = CMTL::sqrt(CORE::Expr(3));
  CORE::Expr sqrt6 = CMTL::sqrt(CORE::Expr(6));
  EXPECT_TRUE(sqrt2 * sqrt2 == 2);
  EXPECT_TRUE((sqrt2 + sqrt3) * (sqrt2 + sqrt3) == 5 + 2 * sqrt6);
#endif

#if defined(USE_GMP) && defined(USE_CORE)
  CORE::Expr sqrt2_gmp = CMTL::sqrt(mpq_class(2));
  EXPECT_TRUE(sqrt2_gmp * sqrt2_gmp == 2);
  CORE::Expr sqrt_1_2_gmp = CMTL::sqrt(mpq_class(1, 3) + mpq_class(1, 6));
  EXPECT_TRUE(sqrt_1_2_gmp * sqrt_1_2_gmp == CORE::Expr("1/2"));
  CORE::Expr sqrt_4_9 = CMTL::sqrt(mpq_class(4, 9));
  EXPECT_TRUE(sqrt_4_9 == CORE::Expr("2/3"));
#endif
}
