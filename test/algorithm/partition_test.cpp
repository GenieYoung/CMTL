#include "CMTL/algorithm/partition.h"

#include <gtest/gtest.h>

using namespace CMTL::algorithm;

TEST(PartitionTest, ConnectedManifoldPartition3DTest) {
  // separate two cubes
  std::vector<std::vector<unsigned>> faces1 = {
      {0, 1, 2, 3},    {1, 2, 6, 5},    {5, 6, 7, 4},
      {7, 4, 0, 3},    {0, 1, 5, 4},    {3, 2, 6, 7},

      {8, 9, 10, 11},  {9, 10, 14, 13}, {12, 13, 14, 16},
      {12, 15, 11, 8}, {8, 9, 13, 12},  {11, 10, 14, 15}};
  std::vector<std::vector<unsigned>> res1 =
      connected_manifold_partition_3d(faces1);
  EXPECT_EQ(res1, std::vector<std::vector<unsigned>>(
                      {{0, 4, 5, 1, 3, 2}, {6, 11, 10, 9, 7, 8}}));

  // for(unsigned i = 0; i < res1.size(); ++i) {
  //     for(unsigned j = 0; j < res1[i].size(); ++j) {
  //         std::cout << res1[i][j] << " ";
  //     }
  //     std::cout << std::endl;
  // }
  // std::cout <<std::endl;

  // two cubes sharing a vertex
  std::vector<std::vector<unsigned>> faces2 = {
      {0, 1, 2, 3},    {1, 2, 6, 5},   {5, 6, 7, 4},
      {7, 4, 0, 3},    {0, 1, 5, 4},   {3, 2, 6, 7},

      {6, 8, 9, 10},   {8, 9, 13, 12}, {12, 13, 14, 11},
      {11, 14, 10, 6}, {6, 8, 12, 11}, {10, 9, 13, 14}};
  std::vector<std::vector<unsigned>> res2 =
      connected_manifold_partition_3d(faces2);
  EXPECT_EQ(res2, std::vector<std::vector<unsigned>>(
                      {{0, 4, 5, 1, 3, 2}, {6, 9, 7, 10, 11, 8}}));

  // two cubes sharing an edge
  std::vector<std::vector<unsigned>> faces3 = {
      {0, 1, 2, 3},   {1, 2, 6, 5},   {5, 6, 7, 4},
      {7, 4, 0, 3},   {0, 1, 5, 4},   {3, 2, 6, 7},

      {5, 8, 9, 6},   {8, 9, 12, 11}, {11, 12, 13, 10},
      {10, 13, 6, 5}, {5, 8, 11, 10}, {6, 9, 12, 13}};
  std::vector<std::vector<unsigned>> res3 =
      connected_manifold_partition_3d(faces3);
  EXPECT_EQ(res3, std::vector<std::vector<unsigned>>(
                      {{0, 4, 5, 1, 3, 2}, {6, 11, 7, 10, 9, 8}}));
}