#include "CMTL/common/numeric_utils.h"

#include <gtest/gtest.h>

TEST(NumberUtilsTest, ComparatorTest) {
  float float_tol = CMTL::default_float_tolerance;
  double double_tol = CMTL::default_double_tolerance;

  ASSERT_TRUE(CMTL::is_equal(float(0.0), float_tol));
  ASSERT_TRUE(CMTL::is_equal(float(0.0), float_tol * 0.9f));
  ASSERT_FALSE(CMTL::is_equal(float(0.0), float_tol * 1.1f));

  ASSERT_TRUE(CMTL::is_equal(0.0, double_tol));
  ASSERT_TRUE(CMTL::is_equal(0.0, double_tol * (double)0.9));
  ASSERT_FALSE(CMTL::is_equal(0.0, double_tol * (double)1.1));

  // ASSERT_TRUE(CMTL::is_equal(mpq_class(1, 2), mpq_class(2, 4))); // 2/4 is
  // not in canonical form, it is dangerous
  ASSERT_TRUE(CMTL::is_not_equal(mpq_class(0), mpq_class(1, 1e100)));

  ASSERT_TRUE(CMTL::is_zero(float_tol));
  ASSERT_TRUE(CMTL::is_zero(double_tol));
  ASSERT_FALSE(CMTL::is_zero(float_tol * 1.1f));
  ASSERT_FALSE(CMTL::is_zero(double_tol * 1.1));

  ASSERT_TRUE(CMTL::is_less(float(0.0), float_tol * 2));
  ASSERT_FALSE(CMTL::is_less(float(0.0), float_tol));
  ASSERT_TRUE(CMTL::is_less_equal(float(0.0), float_tol));

  ASSERT_TRUE(CMTL::is_less(0.0, double_tol * 2));
  ASSERT_FALSE(CMTL::is_less(0.0, double_tol));
  ASSERT_TRUE(CMTL::is_less_equal(0.0, double_tol));

  ASSERT_TRUE(CMTL::is_less(mpq_class(0), mpq_class(1, 1e100)));
  ASSERT_TRUE(CMTL::is_less_equal(mpq_class(0), mpq_class(0)));

  ASSERT_TRUE(CMTL::is_greater(float(0.0), -float_tol * 2));
  ASSERT_FALSE(CMTL::is_greater(float(0.0), -float_tol));
  ASSERT_TRUE(CMTL::is_greater_equal(float(0.0), -float_tol));

  ASSERT_TRUE(CMTL::is_greater(0.0, -double_tol * 2));
  ASSERT_FALSE(CMTL::is_greater(0.0, -double_tol));
  ASSERT_TRUE(CMTL::is_greater_equal(0.0, -double_tol));

  ASSERT_TRUE(CMTL::is_greater(mpq_class(1, 1e100), mpq_class(0)));
  ASSERT_TRUE(CMTL::is_greater_equal(mpq_class(0), mpq_class(0)));
}