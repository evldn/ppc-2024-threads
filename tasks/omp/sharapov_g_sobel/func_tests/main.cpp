// Copyright 2024 Sharapov Georgiy

#include <gtest/gtest.h>

#include <vector>

#include "omp/sharapov_g_sobel/include/ssobel_omp.hpp"

TEST(sharapov_g_sobel_omp, Test_Seed_1234) {
  int width = 10;
  int height = 10;
  std::vector<SSobelOmp::RGB> ColoredImage = {
      {49, 127, 159},  {209, 112, 156}, {201, 197, 199}, {220, 69, 38},   {70, 50, 205},   {208, 245, 40},
      {224, 29, 91},   {3, 128, 124},   {174, 84, 182},  {205, 94, 25},   {143, 14, 128},  {113, 3, 5},
      {197, 74, 225},  {63, 93, 189},   {157, 227, 19},  {252, 94, 30},   {238, 100, 166}, {115, 101, 137},
      {201, 202, 81},  {119, 145, 111}, {222, 145, 111}, {248, 205, 10},  {36, 140, 180},  {118, 180, 96},
      {56, 83, 236},   {208, 113, 165}, {232, 12, 15},   {254, 47, 176},  {12, 237, 172},  {235, 152, 249},
      {136, 101, 11},  {67, 143, 110},  {84, 195, 128},  {153, 28, 20},   {155, 180, 144}, {41, 1, 8},
      {158, 84, 233},  {121, 202, 17},  {253, 97, 245},  {30, 202, 229},  {73, 195, 159},  {96, 122, 6},
      {50, 232, 97},   {201, 13, 158},  {115, 54, 251},  {74, 31, 169},   {30, 226, 189},  {171, 150, 84},
      {120, 53, 27},   {2, 58, 18},     {230, 186, 106}, {250, 137, 176}, {1, 253, 76},    {176, 111, 242},
      {156, 149, 235}, {136, 160, 43},  {180, 40, 38},   {240, 190, 183}, {212, 121, 162}, {226, 112, 103},
      {39, 43, 145},   {33, 135, 105},  {243, 6, 122},   {144, 128, 200}, {137, 68, 209},  {54, 14, 45},
      {171, 109, 196}, {248, 181, 11},  {203, 234, 142}, {40, 247, 241},  {37, 195, 7},    {13, 152, 65},
      {29, 237, 243},  {214, 83, 40},   {49, 176, 117},  {93, 235, 239},  {225, 157, 64},  {179, 89, 128},
      {46, 182, 230},  {34, 180, 212},  {186, 190, 230}, {117, 199, 20},  {153, 95, 74},   {239, 38, 107},
      {85, 59, 168},   {146, 18, 146},  {14, 106, 82},   {160, 151, 56},  {218, 159, 73},  {122, 44, 249},
      {34, 197, 254},  {6, 45, 56},     {81, 30, 145},   {44, 2, 109},    {230, 168, 250}, {144, 142, 145},
      {21, 167, 85},   {94, 186, 243},  {36, 50, 141},   {217, 69, 245},
  };
  std::vector<SSobelOmp::GrayScale> EdgeImage(ColoredImage.size());
  std::vector<SSobelOmp::GrayScale> EdgeImageExpected = {
      {255}, {0},   {255}, {255}, {255}, {0},   {255}, {0},   {255}, {0},   {255}, {0},   {0},   {0},   {0},
      {0},   {255}, {255}, {255}, {255}, {255}, {255}, {0},   {0},   {0},   {255}, {0},   {255}, {0},   {0},
      {255}, {0},   {0},   {0},   {0},   {0},   {255}, {0},   {255}, {255}, {255}, {255}, {0},   {0},   {255},
      {255}, {255}, {0},   {255}, {0},   {0},   {0},   {0},   {0},   {0},   {0},   {255}, {255}, {255}, {255},
      {255}, {255}, {0},   {0},   {0},   {0},   {255}, {255}, {0},   {0},   {255}, {255}, {0},   {0},   {0},
      {0},   {0},   {255}, {255}, {255}, {0},   {255}, {255}, {255}, {0},   {0},   {0},   {0},   {0},   {0},
      {255}, {255}, {255}, {255}, {255}, {255}, {255}, {0},   {255}, {0},
  };

  // TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataOmp = std::make_shared<ppc::core::TaskData>();
  taskDataOmp->inputs.emplace_back(reinterpret_cast<uint8_t *>(ColoredImage.data()));
  taskDataOmp->inputs_count.emplace_back(width);
  taskDataOmp->inputs_count.emplace_back(height);
  taskDataOmp->outputs.emplace_back(reinterpret_cast<uint8_t *>(EdgeImage.data()));
  taskDataOmp->outputs_count.emplace_back(width);
  taskDataOmp->outputs_count.emplace_back(height);

  // Task
  SSobelOmp SSobelOmp(taskDataOmp);
  ASSERT_EQ(SSobelOmp.validation(), true);
  ASSERT_EQ(SSobelOmp.pre_processing(), true);
  ASSERT_EQ(SSobelOmp.run(), true);
  ASSERT_EQ(SSobelOmp.post_processing(), true);

  for (size_t i = 0; i < ColoredImage.size(); ++i) {
    ASSERT_EQ(EdgeImageExpected[i].value, EdgeImage[i].value);
  }
}

TEST(sharapov_g_sobel_omp, Test_Seed_2451) {
  int width = 10;
  int height = 10;
  std::vector<SSobelOmp::RGB> ColoredImage = {
      {165, 211, 100}, {224, 104, 130}, {136, 101, 44},  {211, 188, 234}, {190, 165, 221}, {201, 96, 100},
      {200, 199, 192}, {216, 98, 94},   {176, 159, 98},  {90, 247, 230},  {92, 47, 123},   {219, 208, 223},
      {216, 134, 178}, {192, 254, 253}, {20, 37, 41},    {215, 173, 35},  {105, 144, 67},  {56, 229, 39},
      {254, 235, 71},  {127, 134, 35},  {186, 131, 119}, {91, 75, 18},    {238, 243, 2},   {77, 76, 179},
      {13, 24, 10},    {38, 207, 0},    {31, 175, 203},  {192, 93, 66},   {27, 207, 113},  {89, 184, 73},
      {182, 72, 215},  {71, 236, 177},  {12, 10, 134},   {88, 69, 95},    {110, 84, 197},  {22, 254, 101},
      {175, 62, 176},  {88, 0, 89},     {30, 124, 171},  {4, 162, 2},     {70, 226, 24},   {112, 124, 20},
      {177, 146, 101}, {184, 144, 227}, {243, 12, 219},  {179, 186, 41},  {245, 142, 15},  {190, 199, 60},
      {22, 66, 184},   {245, 24, 121},  {218, 21, 94},   {66, 242, 95},   {237, 237, 99},  {82, 86, 145},
      {169, 114, 97},  {130, 198, 72},  {163, 245, 215}, {177, 187, 76},  {155, 88, 96},   {212, 180, 230},
      {51, 62, 149},   {224, 44, 147},  {223, 92, 5},    {12, 247, 119},  {190, 25, 137},  {245, 217, 17},
      {139, 220, 240}, {221, 191, 114}, {16, 1, 199},    {20, 15, 6},     {60, 255, 104},  {69, 243, 150},
      {119, 47, 56},   {105, 92, 186},  {66, 173, 238},  {153, 229, 161}, {104, 41, 110},  {222, 27, 212},
      {92, 94, 180},   {238, 137, 47},  {24, 197, 99},   {45, 200, 152},  {108, 246, 238}, {180, 138, 155},
      {71, 64, 6},     {51, 103, 208},  {180, 224, 33},  {201, 26, 5},    {92, 87, 114},   {228, 202, 243},
      {25, 97, 20},    {177, 63, 194},  {148, 72, 120},  {214, 77, 230},  {7, 167, 6},     {165, 17, 149},
      {1, 251, 31},    {167, 216, 178}, {12, 190, 185},  {124, 97, 237},
  };
  std::vector<SSobelOmp::GrayScale> EdgeImage(ColoredImage.size());
  std::vector<SSobelOmp::GrayScale> EdgeImageExpected = {
      {0},   {255}, {255}, {0},   {255}, {255}, {0},   {0},   {0},   {0},   {255}, {0},   {0},   {255}, {255},
      {255}, {0},   {0},   {0},   {255}, {0},   {255}, {255}, {255}, {0},   {255}, {255}, {255}, {255}, {255},
      {0},   {0},   {0},   {0},   {255}, {255}, {255}, {0},   {0},   {255}, {0},   {0},   {255}, {255}, {0},
      {255}, {255}, {255}, {255}, {255}, {255}, {255}, {0},   {255}, {0},   {255}, {0},   {255}, {255}, {255},
      {255}, {0},   {255}, {0},   {255}, {255}, {255}, {255}, {255}, {0},   {255}, {255}, {255}, {0},   {255},
      {255}, {255}, {255}, {255}, {255}, {255}, {255}, {0},   {255}, {255}, {255}, {0},   {255}, {255}, {255},
      {255}, {255}, {255}, {0},   {255}, {255}, {255}, {255}, {0},   {255},
  };

  // TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataOmp = std::make_shared<ppc::core::TaskData>();
  taskDataOmp->inputs.emplace_back(reinterpret_cast<uint8_t *>(ColoredImage.data()));
  taskDataOmp->inputs_count.emplace_back(width);
  taskDataOmp->inputs_count.emplace_back(height);
  taskDataOmp->outputs.emplace_back(reinterpret_cast<uint8_t *>(EdgeImage.data()));
  taskDataOmp->outputs_count.emplace_back(width);
  taskDataOmp->outputs_count.emplace_back(height);

  // Task
  SSobelOmp SSobelOmp(taskDataOmp);
  ASSERT_EQ(SSobelOmp.validation(), true);
  ASSERT_EQ(SSobelOmp.pre_processing(), true);
  ASSERT_EQ(SSobelOmp.run(), true);
  ASSERT_EQ(SSobelOmp.post_processing(), true);

  for (size_t i = 0; i < ColoredImage.size(); ++i) {
    ASSERT_EQ(EdgeImageExpected[i].value, EdgeImage[i].value);
  }
}

TEST(sharapov_g_sobel_omp, Test_Seed_2423) {
  int width = 10;
  int height = 10;
  std::vector<SSobelOmp::RGB> ColoredImage = {
      {228, 176, 206}, {62, 172, 252},  {227, 163, 82},  {135, 233, 63},  {196, 51, 11},   {77, 236, 82},
      {104, 99, 138},  {172, 61, 211},  {193, 128, 101}, {52, 135, 222},  {147, 96, 177},  {63, 127, 55},
      {3, 33, 84},     {30, 236, 154},  {99, 198, 31},   {41, 54, 195},   {43, 94, 164},   {130, 58, 140},
      {75, 121, 84},   {9, 191, 43},    {234, 234, 89},  {238, 180, 148}, {54, 178, 150},  {138, 118, 99},
      {112, 40, 121},  {102, 145, 114}, {19, 186, 135},  {232, 187, 20},  {97, 134, 38},   {154, 189, 74},
      {229, 67, 18},   {219, 49, 50},   {250, 141, 69},  {115, 219, 130}, {115, 95, 100},  {180, 98, 151},
      {221, 146, 254}, {77, 47, 171},   {202, 190, 172}, {81, 188, 33},   {161, 167, 67},  {71, 110, 91},
      {253, 61, 43},   {141, 214, 52},  {188, 110, 43},  {31, 32, 30},    {91, 155, 1},    {216, 163, 169},
      {55, 192, 67},   {206, 11, 9},    {67, 127, 217},  {57, 237, 129},  {190, 184, 92},  {43, 96, 206},
      {238, 83, 173},  {105, 210, 232}, {39, 183, 158},  {57, 61, 106},   {246, 63, 6},    {210, 34, 128},
      {23, 50, 61},    {239, 174, 93},  {131, 227, 15},  {179, 89, 157},  {80, 63, 68},    {210, 220, 171},
      {225, 91, 82},   {159, 228, 125}, {253, 66, 86},   {141, 132, 181}, {148, 41, 243},  {28, 74, 215},
      {97, 176, 34},   {17, 184, 197},  {190, 129, 103}, {138, 209, 186}, {30, 233, 190},  {83, 225, 120},
      {167, 113, 218}, {5, 63, 190},    {43, 69, 30},    {101, 78, 147},  {204, 144, 103}, {38, 214, 6},
      {142, 14, 197},  {149, 254, 188}, {129, 139, 76},  {181, 236, 180}, {225, 144, 214}, {179, 155, 90},
      {157, 200, 233}, {152, 213, 136}, {157, 28, 74},   {250, 236, 114}, {191, 55, 90},   {162, 243, 76},
      {22, 93, 85},    {49, 213, 172},  {132, 136, 42},  {57, 192, 78},
  };
  std::vector<SSobelOmp::GrayScale> EdgeImage(ColoredImage.size());
  std::vector<SSobelOmp::GrayScale> EdgeImageExpected = {
      {255}, {255}, {255}, {0},   {0},   {255}, {255}, {255}, {0},   {0},   {0},   {255}, {0}, {255}, {255},
      {0},   {0},   {0},   {0},   {0},   {0},   {255}, {255}, {0},   {0},   {255}, {255}, {0}, {0},   {0},
      {255}, {255}, {0},   {255}, {255}, {255}, {0},   {0},   {0},   {255}, {0},   {0},   {0}, {0},   {255},
      {0},   {0},   {0},   {255}, {255}, {255}, {255}, {255}, {0},   {0},   {255}, {255}, {0}, {0},   {255},
      {255}, {255}, {0},   {255}, {255}, {0},   {255}, {255}, {255}, {0},   {0},   {255}, {0}, {0},   {255},
      {0},   {0},   {0},   {255}, {0},   {255}, {255}, {255}, {0},   {0},   {0},   {0},   {0}, {255}, {255},
      {255}, {255}, {0},   {0},   {0},   {0},   {255}, {255}, {255}, {0},
  };

  // TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataOmp = std::make_shared<ppc::core::TaskData>();
  taskDataOmp->inputs.emplace_back(reinterpret_cast<uint8_t *>(ColoredImage.data()));
  taskDataOmp->inputs_count.emplace_back(width);
  taskDataOmp->inputs_count.emplace_back(height);
  taskDataOmp->outputs.emplace_back(reinterpret_cast<uint8_t *>(EdgeImage.data()));
  taskDataOmp->outputs_count.emplace_back(width);
  taskDataOmp->outputs_count.emplace_back(height);

  // Task
  SSobelOmp SSobelOmp(taskDataOmp);
  ASSERT_EQ(SSobelOmp.validation(), true);
  ASSERT_EQ(SSobelOmp.pre_processing(), true);
  ASSERT_EQ(SSobelOmp.run(), true);
  ASSERT_EQ(SSobelOmp.post_processing(), true);

  for (size_t i = 0; i < ColoredImage.size(); ++i) {
    ASSERT_EQ(EdgeImageExpected[i].value, EdgeImage[i].value);
  }
}

TEST(sharapov_g_sobel_omp, Test_Seed_2354) {
  int width = 10;
  int height = 10;
  std::vector<SSobelOmp::RGB> ColoredImage = {
      {89, 163, 39},   {242, 105, 46},  {244, 222, 207}, {74, 144, 140},  {37, 81, 108},   {76, 94, 229},
      {241, 190, 52},  {18, 186, 142},  {208, 145, 121}, {101, 217, 13},  {183, 42, 151},  {122, 51, 28},
      {213, 21, 233},  {87, 118, 200},  {1, 111, 111},   {4, 220, 229},   {29, 2, 247},    {254, 16, 238},
      {83, 204, 98},   {190, 165, 131}, {122, 110, 18},  {43, 21, 221},   {149, 28, 137},  {253, 101, 59},
      {33, 48, 207},   {206, 107, 130}, {251, 224, 193}, {49, 188, 19},   {27, 176, 37},   {167, 200, 28},
      {158, 221, 200}, {42, 151, 126},  {5, 96, 249},    {105, 34, 158},  {30, 37, 69},    {143, 246, 19},
      {145, 168, 226}, {122, 40, 31},   {142, 133, 201}, {83, 208, 136},  {223, 130, 219}, {143, 177, 1},
      {183, 62, 90},   {212, 37, 242},  {166, 76, 161},  {6, 246, 188},   {115, 38, 213},  {107, 141, 235},
      {245, 59, 9},    {203, 166, 219}, {15, 3, 56},     {128, 65, 76},   {167, 17, 52},   {147, 129, 214},
      {83, 122, 167},  {135, 151, 77},  {228, 192, 178}, {102, 67, 240},  {91, 202, 34},   {96, 38, 132},
      {61, 55, 254},   {196, 250, 153}, {28, 255, 254},  {8, 129, 215},   {2, 20, 253},    {24, 190, 204},
      {238, 246, 215}, {253, 74, 212},  {183, 59, 66},   {31, 170, 169},  {111, 130, 40},  {242, 50, 139},
      {239, 186, 28},  {163, 109, 40},  {35, 76, 254},   {187, 96, 46},   {10, 134, 104},  {175, 211, 116},
      {199, 230, 163}, {164, 119, 198}, {124, 240, 215}, {44, 34, 152},   {241, 247, 226}, {226, 108, 155},
      {70, 109, 119},  {59, 43, 108},   {60, 60, 155},   {138, 142, 179}, {3, 168, 209},   {149, 225, 19},
      {10, 247, 170},  {14, 202, 237},  {91, 59, 40},    {11, 176, 218},  {243, 134, 205}, {218, 6, 240},
      {221, 8, 114},   {117, 118, 233}, {147, 198, 126}, {63, 170, 186},
  };
  std::vector<SSobelOmp::GrayScale> EdgeImage(ColoredImage.size());
  std::vector<SSobelOmp::GrayScale> EdgeImageExpected = {
      {255}, {255}, {0},   {255}, {0},   {0},   {0},   {0},   {0},   {0},   {255}, {255}, {255}, {255}, {0},
      {255}, {0},   {0},   {255}, {0},   {255}, {255}, {0},   {0},   {0},   {255}, {255}, {0},   {255}, {0},
      {255}, {255}, {0},   {0},   {255}, {255}, {255}, {0},   {255}, {0},   {255}, {255}, {0},   {255}, {255},
      {0},   {255}, {0},   {0},   {255}, {0},   {255}, {255}, {0},   {0},   {255}, {255}, {255}, {0},   {0},
      {255}, {255}, {255}, {255}, {0},   {255}, {0},   {255}, {255}, {255}, {0},   {255}, {0},   {255}, {0},
      {255}, {255}, {255}, {0},   {0},   {255}, {0},   {255}, {255}, {255}, {0},   {255}, {255}, {0},   {0},
      {0},   {255}, {255}, {255}, {255}, {255}, {0},   {255}, {0},   {0},
  };

  // TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataOmp = std::make_shared<ppc::core::TaskData>();
  taskDataOmp->inputs.emplace_back(reinterpret_cast<uint8_t *>(ColoredImage.data()));
  taskDataOmp->inputs_count.emplace_back(width);
  taskDataOmp->inputs_count.emplace_back(height);
  taskDataOmp->outputs.emplace_back(reinterpret_cast<uint8_t *>(EdgeImage.data()));
  taskDataOmp->outputs_count.emplace_back(width);
  taskDataOmp->outputs_count.emplace_back(height);

  // Task
  SSobelOmp SSobelOmp(taskDataOmp);
  ASSERT_EQ(SSobelOmp.validation(), true);
  ASSERT_EQ(SSobelOmp.pre_processing(), true);
  ASSERT_EQ(SSobelOmp.run(), true);
  ASSERT_EQ(SSobelOmp.post_processing(), true);

  for (size_t i = 0; i < ColoredImage.size(); ++i) {
    ASSERT_EQ(EdgeImageExpected[i].value, EdgeImage[i].value);
  }
}

TEST(sharapov_g_sobel_omp, Test_Seed_3453) {
  int width = 10;
  int height = 10;
  std::vector<SSobelOmp::RGB> ColoredImage = {
      {17, 24, 49},    {175, 112, 198}, {84, 156, 62},   {46, 84, 186},   {152, 71, 37},   {95, 152, 45},
      {189, 187, 219}, {123, 85, 107},  {151, 60, 86},   {198, 86, 248},  {127, 31, 131},  {166, 23, 243},
      {134, 195, 132}, {126, 135, 157}, {237, 87, 126},  {42, 46, 219},   {232, 169, 146}, {158, 220, 95},
      {100, 105, 151}, {248, 175, 21},  {160, 90, 143},  {30, 247, 234},  {232, 13, 30},   {28, 169, 105},
      {40, 122, 72},   {55, 255, 82},   {184, 224, 147}, {201, 12, 46},   {30, 147, 52},   {111, 91, 203},
      {210, 5, 244},   {2, 210, 46},    {207, 40, 230},  {186, 195, 12},  {162, 250, 84},  {93, 30, 207},
      {207, 26, 149},  {68, 188, 201},  {16, 254, 111},  {223, 179, 142}, {17, 215, 213},  {47, 255, 92},
      {112, 33, 64},   {159, 178, 251}, {67, 122, 173},  {21, 171, 234},  {46, 238, 75},   {242, 51, 157},
      {149, 241, 101}, {239, 61, 136},  {9, 71, 32},     {253, 3, 13},    {22, 40, 48},    {92, 124, 218},
      {21, 113, 218},  {17, 55, 184},   {58, 216, 17},   {101, 227, 1},   {64, 224, 171},  {242, 158, 115},
      {252, 250, 122}, {94, 200, 206},  {28, 24, 107},   {71, 89, 40},    {156, 87, 120},  {231, 225, 225},
      {209, 152, 12},  {87, 253, 120},  {89, 153, 240},  {44, 232, 192},  {100, 61, 170},  {201, 130, 147},
      {222, 39, 74},   {250, 225, 234}, {205, 233, 252}, {53, 192, 106},  {107, 218, 59},  {236, 45, 133},
      {98, 237, 103},  {82, 255, 231},  {242, 236, 183}, {125, 104, 123}, {213, 20, 190},  {150, 212, 56},
      {220, 119, 234}, {196, 202, 116}, {162, 95, 150},  {138, 202, 31},  {130, 67, 248},  {114, 159, 76},
      {144, 39, 90},   {178, 47, 156},  {67, 219, 61},   {146, 57, 203},  {229, 53, 154},  {180, 64, 189},
      {190, 141, 205}, {244, 192, 214}, {141, 238, 130}, {103, 101, 46},
  };
  std::vector<SSobelOmp::GrayScale> EdgeImage(ColoredImage.size());
  std::vector<SSobelOmp::GrayScale> EdgeImageExpected = {
      {0},   {255}, {0},   {0},   {0},   {255}, {0},   {255}, {0},   {0},   {255}, {255}, {0},   {0},   {0},
      {255}, {0},   {255}, {0},   {255}, {0},   {0},   {0},   {0},   {0},   {0},   {255}, {255}, {0},   {0},
      {0},   {0},   {0},   {255}, {255}, {0},   {0},   {0},   {255}, {0},   {0},   {255}, {255}, {255}, {255},
      {0},   {0},   {0},   {0},   {0},   {255}, {255}, {0},   {255}, {0},   {255}, {255}, {0},   {0},   {0},
      {255}, {255}, {255}, {255}, {255}, {255}, {0},   {0},   {0},   {0},   {0},   {255}, {255}, {255}, {0},
      {0},   {0},   {0},   {0},   {0},   {255}, {0},   {255}, {255}, {255}, {0},   {0},   {255}, {0},   {255},
      {255}, {0},   {0},   {0},   {255}, {0},   {255}, {255}, {255}, {255},
  };

  // TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataOmp = std::make_shared<ppc::core::TaskData>();
  taskDataOmp->inputs.emplace_back(reinterpret_cast<uint8_t *>(ColoredImage.data()));
  taskDataOmp->inputs_count.emplace_back(width);
  taskDataOmp->inputs_count.emplace_back(height);
  taskDataOmp->outputs.emplace_back(reinterpret_cast<uint8_t *>(EdgeImage.data()));
  taskDataOmp->outputs_count.emplace_back(width);
  taskDataOmp->outputs_count.emplace_back(height);

  // Task
  SSobelOmp SSobelOmp(taskDataOmp);
  ASSERT_EQ(SSobelOmp.validation(), true);
  ASSERT_EQ(SSobelOmp.pre_processing(), true);
  ASSERT_EQ(SSobelOmp.run(), true);
  ASSERT_EQ(SSobelOmp.post_processing(), true);

  for (size_t i = 0; i < ColoredImage.size(); ++i) {
    ASSERT_EQ(EdgeImageExpected[i].value, EdgeImage[i].value);
  }
}
