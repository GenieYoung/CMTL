#include "CMTL/common/vectorT.h"

#include <gtest/gtest.h>

using namespace CMTL;

TEST(VectorTest, ConstructTest) {
  // default constructor
  Vec1i v1i_from_default_construct;
  Vec2i v2i_from_default_construct;
  Vec3i v3i_from_default_construct;
  EXPECT_EQ(v1i_from_default_construct[0], 0);
  EXPECT_EQ(v2i_from_default_construct[0], 0);
  EXPECT_EQ(v2i_from_default_construct[1], 0);
  EXPECT_EQ(v3i_from_default_construct[0], 0);
  EXPECT_EQ(v3i_from_default_construct[1], 0);
  EXPECT_EQ(v3i_from_default_construct[2], 0);
#ifdef USE_GMP
  Vec3r v3r_from_default_construct;
  EXPECT_EQ(v3r_from_default_construct[0], 0);
  EXPECT_EQ(v3r_from_default_construct[1], 0);
  EXPECT_EQ(v3r_from_default_construct[2], 0);
#endif

  // filled constructor
  Vec2f v2f_from_filled_construct(2);
  Vec3f v3f_from_filled_construct(3);
  EXPECT_EQ(v2f_from_filled_construct[0], 2);
  EXPECT_EQ(v2f_from_filled_construct[1], 2);
  EXPECT_EQ(v3f_from_filled_construct[0], 3);
  EXPECT_EQ(v3f_from_filled_construct[1], 3);
  EXPECT_EQ(v3f_from_filled_construct[2], 3);
#ifdef USE_GMP
  Vec3r v3r_from_filled_construct(mpq_class(1, 2));
  EXPECT_EQ(v3r_from_filled_construct[0], mpq_class(1, 2));
  EXPECT_EQ(v3r_from_filled_construct[1], mpq_class(1, 2));
  EXPECT_EQ(v3r_from_filled_construct[2], mpq_class(1, 2));
  EXPECT_FALSE((std::is_constructible_v<Vec3f, mpq_class>));
#endif

  // multi values constructor
  Vec1d v1d_from_multivalue_construct(1);
  Vec2d v2d_from_multivalue_construct(2, 3.0);
  Vec3d v3d_from_multivalue_construct(4, 5.0, 6);
  EXPECT_EQ(v1d_from_multivalue_construct[0], 1);
  EXPECT_EQ(v2d_from_multivalue_construct[0], 2);
  EXPECT_EQ(v2d_from_multivalue_construct[1], 3);
  EXPECT_EQ(v3d_from_multivalue_construct[0], 4);
  EXPECT_EQ(v3d_from_multivalue_construct[1], 5);
  EXPECT_EQ(v3d_from_multivalue_construct[2], 6);
  EXPECT_FALSE((std::is_constructible_v<Vec3d, double, double>));
#ifdef USE_GMP
  Vec1d v1d_from_multivalue_construct_2(mpq_class(1, 2));
  Vec3r v3r_from_multivalue_construct(0.5, 5, mpq_class(1, 2));
  Vec3d v3d_from_multivalue_construct_2(mpq_class(1, 2), 5, 0.5);
  EXPECT_EQ(v1d_from_multivalue_construct_2[0], 0.5);
  EXPECT_EQ(v3r_from_multivalue_construct[0], 0.5);
  EXPECT_EQ(v3r_from_multivalue_construct[1], 5);
  EXPECT_EQ(v3r_from_multivalue_construct[2], mpq_class(1, 2));
  EXPECT_EQ(v3d_from_multivalue_construct_2[0], 0.5);
  EXPECT_EQ(v3d_from_multivalue_construct_2[1], 5);
  EXPECT_EQ(v3d_from_multivalue_construct_2[2], 0.5);
#endif

  // construct from initializer list
  Vec1d v1d_from_initializer_list{1};
  Vec2d v2d_from_initializer_list{2, 3.0};
  Vec3d v3d_from_initializer_list{4, 5, 6.0};
  EXPECT_EQ(v1d_from_initializer_list[0], 1);
  EXPECT_EQ(v2d_from_initializer_list[0], 2);
  EXPECT_EQ(v2d_from_initializer_list[1], 3);
  EXPECT_EQ(v3d_from_initializer_list[0], 4);
  EXPECT_EQ(v3d_from_initializer_list[1], 5);
  EXPECT_EQ(v3d_from_initializer_list[2], 6);
  EXPECT_FALSE((std::is_convertible_v<double, Vec1d>));
  EXPECT_FALSE((std::is_convertible_v<std::initializer_list<double>, Vec3d>));
#ifdef USE_GMP
  Vec3r v3r_from_initializer_list{mpq_class(1, 2), 0, 0.5};
  EXPECT_EQ(v3r_from_initializer_list[0], 0.5);
  EXPECT_EQ(v3r_from_initializer_list[1], 0);
  EXPECT_EQ(v3r_from_initializer_list[2], 0.5);
#endif

  // construct from build-in array
  double v3d_builtin_array[3] = {1.1, 2.2, 3.3};
  Vec3d v3d_from_builtin_array(v3d_builtin_array);
  EXPECT_EQ(v3d_from_builtin_array[0], 1.1);
  EXPECT_EQ(v3d_from_builtin_array[1], 2.2);
  EXPECT_EQ(v3d_from_builtin_array[2], 3.3);
  EXPECT_FALSE((std::is_convertible_v<double[3], Vec3d>));
#ifdef USE_GMP
  mpq_class v3r_builtin_array[3] = {mpq_class(1, 2), mpq_class(2, 4),
                                    mpq_class(3, 6)};
  Vec3d v3d_from_builtin_array_2(v3r_builtin_array);
  EXPECT_EQ(v3d_from_builtin_array_2[0], 0.5);
  EXPECT_EQ(v3d_from_builtin_array_2[1], 0.5);
  EXPECT_EQ(v3d_from_builtin_array_2[2], 0.5);
#endif

  // construct from array
  std::array<double, 3> v3d_array = {1.1, 2.2, 3.3};
  Vec3d v3d_from_array(v3d_array);
  EXPECT_EQ(v3d_from_array[0], 1.1);
  EXPECT_EQ(v3d_from_array[1], 2.2);
  EXPECT_EQ(v3d_from_array[2], 3.3);
  EXPECT_FALSE((std::is_convertible_v<std::array<double, 3>, Vec3d>));
#ifdef USE_GMP
  std::array<mpq_class, 3> v3r_array = {mpq_class(1, 2), mpq_class(2, 4),
                                        mpq_class(3, 6)};
  Vec3d v3d_from_array_2(v3r_array);
  EXPECT_EQ(v3d_from_array_2[0], 0.5);
  EXPECT_EQ(v3d_from_array_2[1], 0.5);
  EXPECT_EQ(v3d_from_array_2[2], 0.5);
#endif

  // cast constructor
  Vec3d v3d_from_cast_construct(Vec2d(1.1, 2.2));
  EXPECT_EQ(v3d_from_cast_construct[0], 1.1);
  EXPECT_EQ(v3d_from_cast_construct[1], 2.2);
  EXPECT_EQ(v3d_from_cast_construct[2], 0);
  Vec2d v2d_from_cast_construct(Vec3d(1.1, 2, 3.3));
  EXPECT_EQ(v2d_from_cast_construct[0], 1.1);
  EXPECT_EQ(v2d_from_cast_construct[1], 2);
  Vec3i v3i_from_cast_construct(Vec2d(1.1, 2.2));
  EXPECT_EQ(v3i_from_cast_construct[0], 1);
  EXPECT_EQ(v3i_from_cast_construct[1], 2);
  EXPECT_EQ(v3i_from_cast_construct[2], 0);
  EXPECT_FALSE((std::is_convertible_v<Vec2d, Vec3d>));
  EXPECT_FALSE((std::is_convertible_v<Vec3d, Vec2d>));
  EXPECT_FALSE((std::is_convertible_v<Vec2d, Vec3i>));
#ifdef USE_GMP
  Vec3d v3d_from_cast_construct_2(Vec2r(mpq_class(1, 2), mpq_class(1, 4)));
  EXPECT_EQ(v3d_from_cast_construct_2[0], 0.5);
  EXPECT_EQ(v3d_from_cast_construct_2[1], 0.25);
  EXPECT_EQ(v3d_from_cast_construct_2[2], 0);
  Vec2d v2d_from_cast_construct_2(
      Vec3r(mpq_class(1, 2), mpq_class(1, 4), mpq_class(1, 8)));
  EXPECT_EQ(v2d_from_cast_construct_2[0], 0.5);
  EXPECT_EQ(v2d_from_cast_construct_2[1], 0.25);
#endif

  // assign operator
  Vec2d v2d_assign_operator_from(1.1, 2.2);
  Vec2d v2d_assign_operator_to;
  v2d_assign_operator_to = v2d_assign_operator_from;
  EXPECT_EQ(v2d_assign_operator_to, v2d_assign_operator_from);

  // cast operator
  Vec2d v2d_from_cast_operator;
  v2d_from_cast_operator = Vec3d(-1.1, -2.2, -3.3);
  EXPECT_EQ(v2d_from_cast_operator[0], -1.1);
  EXPECT_EQ(v2d_from_cast_operator[1], -2.2);
  Vec3d v3d_from_cast_operator;
  v3d_from_cast_operator = Vec2d(-1.1, -2.2);
  EXPECT_EQ(v3d_from_cast_operator[0], -1.1);
  EXPECT_EQ(v3d_from_cast_operator[1], -2.2);
  EXPECT_EQ(v3d_from_cast_operator[2], 0);
  v3i_from_cast_construct = Vec2d(-1.1, -2.2);
  EXPECT_EQ(v3i_from_cast_construct[0], -1);
  EXPECT_EQ(v3i_from_cast_construct[1], -2);
  EXPECT_EQ(v3i_from_cast_construct[2], 0);
  Vec2i v2i_from_cast_operator;
  v2i_from_cast_operator = Vec3d(-1.1, -2.2, -3.3);
  EXPECT_EQ(v2i_from_cast_operator[0], -1);
  EXPECT_EQ(v2i_from_cast_operator[1], -2);
#ifdef USE_GMP
  Vec2d v2d_from_cast_operator_2;
  v2d_from_cast_operator_2 =
      Vec3r(mpq_class(-1, 2), mpq_class(-1, 4), mpq_class(-1, 8));
  EXPECT_EQ(v2d_from_cast_operator_2[0], -0.5);
  EXPECT_EQ(v2d_from_cast_operator_2[1], -0.25);
  Vec3d v3d_from_cast_operator_2;
  v3d_from_cast_operator_2 = Vec2r(mpq_class(-1, 2), mpq_class(-1, 4));
  EXPECT_EQ(v3d_from_cast_operator_2[0], -0.5);
  EXPECT_EQ(v3d_from_cast_operator_2[1], -0.25);
  EXPECT_EQ(v3d_from_cast_operator_2[2], 0);
#endif
}

TEST(VectorTest, OperationTest) {
  // equality
  Vec3d v3d_equality_0(1.1, 2, 3.3);
  Vec3d v3d_equality_1(1.1, 2, 3.3);
  EXPECT_TRUE(v3d_equality_0 == v3d_equality_1);
  EXPECT_FALSE(v3d_equality_0 != v3d_equality_1);

  // less
  Vec3d v3d_less_0(1.1, 2, 3.3);
  Vec3d v3d_less_1(1.1, 1.9, 3.3);
  Vec3d v3d_less_2(1.1, 2, 3.2);
  EXPECT_TRUE(v3d_less_1 < v3d_less_0);
  EXPECT_TRUE(v3d_less_2 < v3d_less_0);

  // add
  Vec3d v3d_selfadd_0(1.5, 2, 3.5);
  v3d_selfadd_0 += Vec3d(0.5, 0, -1.5);
  EXPECT_EQ(v3d_selfadd_0, Vec3d(2, 2, 2));
  Vec3i v3i_selfadd_0(1, 2, 3);
  v3i_selfadd_0 += Vec3d(1.5, 0, -1.5);
  EXPECT_EQ(v3i_selfadd_0, Vec3i(2, 2, 2));
  Vec3d v3d_add_0 = Vec3d(1.5, 2, 3.5) + Vec3d(0.5, 0, -1.5);
  EXPECT_EQ(v3d_add_0, Vec3d(2, 2, 2));
  Vec3i v3i_add_0 = Vec3i(1, 2, 3) + Vec3d(1.5, 0, -1.5);
  EXPECT_EQ(v3i_add_0, Vec3i(2, 2, 2));
#ifdef USE_GMP
  Vec3d v3d_selfadd_1(1.5, 2, 3.5);
  v3d_selfadd_1 += Vec3r(mpq_class(1, 2), 0, mpq_class(-3, 2));
  EXPECT_EQ(v3d_selfadd_1, Vec3d(2, 2, 2));
  Vec3r v3r_selfadd_0(mpq_class(1, 2), mpq_class(2, 3), mpq_class(5, 4));
  v3r_selfadd_0 += Vec3r(mpq_class(1, 2), mpq_class(1, 3), mpq_class(-1, 4));
  EXPECT_EQ(v3r_selfadd_0, Vec3r(1, 1, 1));
  Vec3d v3d_add_1 =
      Vec3d(1.5, 2, 3.5) + Vec3r(mpq_class(1, 2), 0, mpq_class(-3, 2));
  EXPECT_EQ(v3d_add_1, Vec3d(2, 2, 2));
  Vec3r v3r_add_0 = Vec3r(mpq_class(1, 2), mpq_class(2, 3), mpq_class(5, 4)) +
                    Vec3r(mpq_class(1, 2), mpq_class(1, 3), mpq_class(-1, 4));
  EXPECT_EQ(v3r_add_0, Vec3r(1, 1, 1));
#endif

  // substract
  Vec3d v3d_selfsubtract_0(1.5, 2, 3.5);
  v3d_selfsubtract_0 -= Vec3d(-0.5, 0, 1.5);
  EXPECT_EQ(v3d_selfsubtract_0, Vec3d(2, 2, 2));
  Vec3i v3i_selfsubtract_0(1, 2, 3);
  v3i_selfsubtract_0 -= Vec3d(-1.5, 0, 1.5);
  EXPECT_EQ(v3i_selfsubtract_0, Vec3i(2, 2, 2));
  Vec3d v3d_substract_0 = Vec3d(1.5, 2, 3.5) - Vec3d(-0.5, 0, 1.5);
  EXPECT_EQ(v3d_substract_0, Vec3d(2, 2, 2));
  Vec3i v3i_subtract_0 = Vec3i(1, 2, 3) - Vec3d(-1.5, 0, 1.5);
  EXPECT_EQ(v3i_subtract_0, Vec3i(2, 2, 2));
#ifdef USE_GMP
  Vec3d v3d_selfsubtract_1(1.5, 2, 3.5);
  v3d_selfsubtract_1 -= Vec3r(-mpq_class(1, 2), 0, mpq_class(3, 2));
  EXPECT_EQ(v3d_selfsubtract_1, Vec3d(2, 2, 2));
  Vec3r v3r_selfsubtract_0(mpq_class(1, 2), mpq_class(2, 3), mpq_class(5, 4));
  v3r_selfsubtract_0 -=
      Vec3r(mpq_class(-1, 2), mpq_class(-1, 3), mpq_class(1, 4));
  EXPECT_EQ(v3r_selfsubtract_0, Vec3r(1, 1, 1));
  Vec3d v3d_substract_1 =
      Vec3d(1.5, 2, 3.5) - Vec3r(mpq_class(-1, 2), 0, mpq_class(3, 2));
  EXPECT_EQ(v3d_substract_1, Vec3d(2, 2, 2));
  Vec3r v3r_subtract_0 =
      Vec3r(mpq_class(1, 2), mpq_class(2, 3), mpq_class(5, 4)) -
      Vec3r(mpq_class(-1, 2), mpq_class(-1, 3), mpq_class(1, 4));
  EXPECT_EQ(v3r_subtract_0, Vec3r(1, 1, 1));
#endif

  // negative
  Vec3d v3d_negative(1.5, 0, -1.5);
  EXPECT_EQ(-v3d_negative, Vec3d(-1.5, 0, 1.5));
#ifdef USE_GMP
  Vec3r v3r_negative(mpq_class(1, 2), 0, mpq_class(-1, 2));
  EXPECT_EQ(-v3r_negative, Vec3r(mpq_class(-1, 2), 0, mpq_class(1, 2)));
#endif

  // scalar product
  Vec3d v3d_scalar_product_0(1.5, 0, 2);
  Vec3d v3d_scalar_product_1(2, 0, 1.5);
  Vec3i v3i_scalar_product_0(1, 0, 2);
  EXPECT_EQ(v3d_scalar_product_0 * v3d_scalar_product_1, 6);
  EXPECT_EQ(v3i_scalar_product_0 * v3d_scalar_product_0, 5);
  EXPECT_EQ(v3d_scalar_product_0.dot(v3d_scalar_product_1), 6);
  EXPECT_EQ(v3i_scalar_product_0.dot(v3d_scalar_product_0), 5);
#ifdef USE_GMP
  Vec3r v3r_scalar_product_0(mpq_class(2, 1), 0, mpq_class(3, 2));
  EXPECT_EQ(v3d_scalar_product_0 * v3r_scalar_product_0, 6);
#endif

  // multiply
  Vec3d v3d_multiply(1.5, 0, -1.5);
  EXPECT_EQ(v3d_multiply * 2, Vec3d(3, 0, -3));

  // divide
  Vec3d v3d_divide(1.5, 0, -3);
  EXPECT_EQ(v3d_divide / 2, Vec3d(0.75, 0, -1.5));

  // data
  EXPECT_EQ(*Vec3d(1.1, 2.2, 3.3).data(), 1.1);
  VecXT<double, 5> v5d_sort(0.2, 0.1, -0.1, 0.3, 0.1);
  std::sort(v5d_sort.data(), v5d_sort.data() + v5d_sort.size());
  EXPECT_EQ(v5d_sort, (VecXT<double, 5>(-0.1, 0.1, 0.1, 0.2, 0.3)));
#ifdef USE_GMP
  VecXT<mpq_class, 5> v5r_sort(mpq_class(1, 5), mpq_class(1, 10),
                               mpq_class(-1, 10), mpq_class(3, 10),
                               mpq_class(1, 10));
  std::sort(v5r_sort.data(), v5r_sort.data() + v5r_sort.size());
  EXPECT_EQ(v5r_sort, (VecXT<mpq_class, 5>(mpq_class(-1, 10), mpq_class(1, 10),
                                           mpq_class(1, 10), mpq_class(1, 5),
                                           mpq_class(3, 10))));
#endif

  // min max
  VecXT<double, 10> v10d_min_max(0.2, 0.1, -0.4, 0.3, 0.4, 0.3, 0, 0.1, -0.4,
                                 0);
  EXPECT_EQ(v10d_min_max.max(), 4);
  EXPECT_EQ(v10d_min_max.min(), 2);
  EXPECT_EQ(v10d_min_max.max_abs(), 2);
  EXPECT_EQ(v10d_min_max.min_abs(), 6);
#ifdef USE_GMP
  VecXT<mpq_class, 10> v10r_min_max(
      mpq_class(1, 5), mpq_class(1, 10), mpq_class(-4, 10), mpq_class(-3, 10),
      mpq_class(4, 10), mpq_class(3, 10), mpq_class(0), mpq_class(1, 10),
      mpq_class(-4, 10), mpq_class(0));
  EXPECT_EQ(v10r_min_max.max(), 4);
  EXPECT_EQ(v10r_min_max.min(), 2);
  EXPECT_EQ(v10r_min_max.max_abs(), 2);
  EXPECT_EQ(v10r_min_max.min_abs(), 6);
#endif

  // measure
  Vec3d v3d_measure(1, 0, -2);
  EXPECT_EQ(v3d_measure.norm_square(), 5);
#ifdef USE_GMP
  Vec3r v3r_measure(mpq_class(1, 3), mpq_class(0), mpq_class(-2, 5));
  EXPECT_EQ(v3r_measure.norm_square(), mpq_class(61, 225));
#endif
}

// int main()
// {
//     Vec2d vd0;
//     std::cout << vd0 << std::endl;

//     Vec2d vd1(0, 1);     // specific constructor
//     Vec2d vd2 = vd1;     // default constructor
//     vd2.fill(10);
//     std::cout << vd2 << std::endl;
//     std::cout << Vec2d::Origin << std::endl;
//     vd2 = vd1;    // assign operator

//     Vec2f vf1(0);
//     //Vec2f vf2 = vd1;    // call the copy constructor, but can not implicit
//     convert from vec2d to vef2d Vec2f vf3(vd1);     // specific copy
//     constructor vf3 = vd1;      // specific assign operator

//     Vec1d v1d1(0);
//     std::cout << vd0 << std::endl;
//     Vec1d v1d2 = v1d1;  // specific constructor
//     //Vec1f v1f1 = v1d1;    // call the specific constructor, wrong

//     VecXT<double, 10> v10d(10);
//     std::cout << v10d << std::endl;

//     Vec3d v3d0(5, 9, 4);
//     std::cout << v3d0.max().first << " " << v3d0.max().second << std::endl;
//     Vec3d v3d1(5, -9, 4);
//     std::cout << v3d1.max_abs().first << " " << v3d1.max_abs().second <<
//     std::endl; Vec3d v3d2(5, -9, 4); std::cout << v3d2.min_abs().first << " "
//     << v3d2.min_abs().second << std::endl;

//     Vec3d v3d3(Vec2d(1,2));
//     std::cout << v3d3 << std::endl;
// }