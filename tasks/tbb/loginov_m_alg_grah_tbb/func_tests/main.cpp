// Copyright 2024 Loginov Maxim

#include <gtest/gtest.h>

#include "tbb/loginov_m_alg_grah_tbb/include/ops_tbb.hpp"

// Points are arranged in a chaotic order (type of x and y is int)
TEST(loginov_m_alg_grah_tbb, Test1) {
  // Create data
  std::vector<LoginovTbb::LoginovPoint> points = {
      LoginovTbb::LoginovPoint(-8, 4),   LoginovTbb::LoginovPoint(-4, 6),   LoginovTbb::LoginovPoint(-12, 2),
      LoginovTbb::LoginovPoint(-6, -2),  LoginovTbb::LoginovPoint(-10, -4), LoginovTbb::LoginovPoint(-4, 2),
      LoginovTbb::LoginovPoint(-6, 6),   LoginovTbb::LoginovPoint(-8, 8),   LoginovTbb::LoginovPoint(-10, 6),
      LoginovTbb::LoginovPoint(-8, 2),   LoginovTbb::LoginovPoint(-6, 2),   LoginovTbb::LoginovPoint(-10, 0),
      LoginovTbb::LoginovPoint(-14, -2), LoginovTbb::LoginovPoint(-16, -4), LoginovTbb::LoginovPoint(-14, -4)};
  std::vector<LoginovTbb::LoginovPoint> mchSeq(7);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> dataGrahamsAlgSeq = std::make_shared<ppc::core::TaskData>();
  dataGrahamsAlgSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(points.data()));
  dataGrahamsAlgSeq->inputs_count.emplace_back(points.size());
  dataGrahamsAlgSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(mchSeq.data()));
  dataGrahamsAlgSeq->outputs_count.emplace_back(mchSeq.size());

  // Create Task
  LoginovTbb::LoginovGrahAlgSequential testGrahamsAlgSeq(dataGrahamsAlgSeq);
  ASSERT_EQ(testGrahamsAlgSeq.validation(), true);
  testGrahamsAlgSeq.pre_processing();
  testGrahamsAlgSeq.run();
  testGrahamsAlgSeq.post_processing();

  // Create data
  std::vector<LoginovTbb::LoginovPoint> mchTbb(7);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> dataGrahamsAlgTbb = std::make_shared<ppc::core::TaskData>();
  dataGrahamsAlgTbb->inputs.emplace_back(reinterpret_cast<uint8_t *>(points.data()));
  dataGrahamsAlgTbb->inputs_count.emplace_back(points.size());
  dataGrahamsAlgTbb->outputs.emplace_back(reinterpret_cast<uint8_t *>(mchTbb.data()));
  dataGrahamsAlgTbb->outputs_count.emplace_back(mchTbb.size());

  // Create Task
  LoginovTbb::LoginovGrahAlgTbbParallel testGrahamsAlgTbb(dataGrahamsAlgTbb);
  ASSERT_EQ(testGrahamsAlgTbb.validation(), true);
  testGrahamsAlgTbb.pre_processing();
  testGrahamsAlgTbb.run();
  testGrahamsAlgTbb.post_processing();

  for (size_t i = 0; i < mchSeq.size(); ++i) {
    ASSERT_EQ(mchSeq[i], mchTbb[i]);
  }
}

// Points are arranged in a chaotic order (type of x and y is double)
TEST(loginov_m_alg_grah_tbb, Test2) {
  // Create data
  std::vector<LoginovTbb::LoginovPoint> points = {
      LoginovTbb::LoginovPoint(-0.5, 2.2),  LoginovTbb::LoginovPoint(1.6, 1.3),   LoginovTbb::LoginovPoint(0.3, -0.6),
      LoginovTbb::LoginovPoint(0.1, 1.3),   LoginovTbb::LoginovPoint(-1.8, 1.42), LoginovTbb::LoginovPoint(-0.3, 0.6),
      LoginovTbb::LoginovPoint(-0.5, -1.2), LoginovTbb::LoginovPoint(1.2, -0.8),  LoginovTbb::LoginovPoint(0.7, 0.4),
      LoginovTbb::LoginovPoint(1.1, 1.9),   LoginovTbb::LoginovPoint(0.4, -1.2),  LoginovTbb::LoginovPoint(-1.9, 0.4),
      LoginovTbb::LoginovPoint(-0.6, -0.3), LoginovTbb::LoginovPoint(1.8, 0.5),   LoginovTbb::LoginovPoint(-1.4, -0.7),
      LoginovTbb::LoginovPoint(-0.9, 1.1),  LoginovTbb::LoginovPoint(-1.2, 1.9),  LoginovTbb::LoginovPoint(0.4, 2.2),
      LoginovTbb::LoginovPoint(1.7, -0.1)};

  std::vector<LoginovTbb::LoginovPoint> mchSeq(13);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> dataGrahamsAlgSeq = std::make_shared<ppc::core::TaskData>();
  dataGrahamsAlgSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(points.data()));
  dataGrahamsAlgSeq->inputs_count.emplace_back(points.size());
  dataGrahamsAlgSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(mchSeq.data()));
  dataGrahamsAlgSeq->outputs_count.emplace_back(mchSeq.size());

  // Create Task
  LoginovTbb::LoginovGrahAlgSequential testGrahamsAlgSeq(dataGrahamsAlgSeq);
  ASSERT_EQ(testGrahamsAlgSeq.validation(), true);
  testGrahamsAlgSeq.pre_processing();
  testGrahamsAlgSeq.run();
  testGrahamsAlgSeq.post_processing();

  // Create data
  std::vector<LoginovTbb::LoginovPoint> mchTbb(13);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> dataGrahamsAlgTbb = std::make_shared<ppc::core::TaskData>();
  dataGrahamsAlgTbb->inputs.emplace_back(reinterpret_cast<uint8_t *>(points.data()));
  dataGrahamsAlgTbb->inputs_count.emplace_back(points.size());
  dataGrahamsAlgTbb->outputs.emplace_back(reinterpret_cast<uint8_t *>(mchTbb.data()));
  dataGrahamsAlgTbb->outputs_count.emplace_back(mchTbb.size());

  // Create Task
  LoginovTbb::LoginovGrahAlgTbbParallel testGrahamsAlgTbb(dataGrahamsAlgTbb);
  ASSERT_EQ(testGrahamsAlgTbb.validation(), true);
  testGrahamsAlgTbb.pre_processing();
  testGrahamsAlgTbb.run();
  testGrahamsAlgTbb.post_processing();

  for (size_t i = 0; i < mchSeq.size(); ++i) {
    ASSERT_EQ(mchSeq[i], mchTbb[i]);
  }
}

// Points are located on the same straight line
TEST(loginov_m_alg_grah_tbb, Test3) {
  // Create data
  std::vector<LoginovTbb::LoginovPoint> points = {
      LoginovTbb::LoginovPoint(-1.4, 2.2), LoginovTbb::LoginovPoint(2.2, 2.2),  LoginovTbb::LoginovPoint(-0.6, 2.2),
      LoginovTbb::LoginovPoint(-2.3, 2.2), LoginovTbb::LoginovPoint(2.7, 2.2),  LoginovTbb::LoginovPoint(0.6, 2.2),
      LoginovTbb::LoginovPoint(1.7, 2.2),  LoginovTbb::LoginovPoint(-3.4, 2.2), LoginovTbb::LoginovPoint(5.3, 2.2),
      LoginovTbb::LoginovPoint(4.4, 2.2),  LoginovTbb::LoginovPoint(3.4, 2.2)};
  std::vector<LoginovTbb::LoginovPoint> mchSeq(2);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> dataGrahamsAlgSeq = std::make_shared<ppc::core::TaskData>();
  dataGrahamsAlgSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(points.data()));
  dataGrahamsAlgSeq->inputs_count.emplace_back(points.size());
  dataGrahamsAlgSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(mchSeq.data()));
  dataGrahamsAlgSeq->outputs_count.emplace_back(mchSeq.size());

  // Create Task
  LoginovTbb::LoginovGrahAlgSequential testGrahamsAlgSeq(dataGrahamsAlgSeq);
  ASSERT_EQ(testGrahamsAlgSeq.validation(), true);
  testGrahamsAlgSeq.pre_processing();
  testGrahamsAlgSeq.run();
  testGrahamsAlgSeq.post_processing();

  // Create data
  std::vector<LoginovTbb::LoginovPoint> mchTbb(2);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> dataGrahamsAlgTbb = std::make_shared<ppc::core::TaskData>();
  dataGrahamsAlgTbb->inputs.emplace_back(reinterpret_cast<uint8_t *>(points.data()));
  dataGrahamsAlgTbb->inputs_count.emplace_back(points.size());
  dataGrahamsAlgTbb->outputs.emplace_back(reinterpret_cast<uint8_t *>(mchTbb.data()));
  dataGrahamsAlgTbb->outputs_count.emplace_back(mchTbb.size());

  // Create Task
  LoginovTbb::LoginovGrahAlgTbbParallel testGrahamsAlgTbb(dataGrahamsAlgTbb);
  ASSERT_EQ(testGrahamsAlgTbb.validation(), true);
  testGrahamsAlgTbb.pre_processing();
  testGrahamsAlgTbb.run();
  testGrahamsAlgTbb.post_processing();

  for (size_t i = 0; i < mchSeq.size(); ++i) {
    ASSERT_EQ(mchSeq[i], mchTbb[i]);
  }
}

// Only one point
TEST(loginov_m_alg_grah_tbb, Test4) {
  // Create data
  std::vector<LoginovTbb::LoginovPoint> points = {LoginovTbb::LoginovPoint(3.5, 4.7)};
  std::vector<LoginovTbb::LoginovPoint> mchSeq(1);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> dataGrahamsAlgSeq = std::make_shared<ppc::core::TaskData>();
  dataGrahamsAlgSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(points.data()));
  dataGrahamsAlgSeq->inputs_count.emplace_back(points.size());
  dataGrahamsAlgSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(mchSeq.data()));
  dataGrahamsAlgSeq->outputs_count.emplace_back(mchSeq.size());

  // Create Task
  LoginovTbb::LoginovGrahAlgSequential testGrahamsAlgSeq(dataGrahamsAlgSeq);
  ASSERT_EQ(testGrahamsAlgSeq.validation(), true);
  testGrahamsAlgSeq.pre_processing();
  testGrahamsAlgSeq.run();
  testGrahamsAlgSeq.post_processing();

  // Create data
  std::vector<LoginovTbb::LoginovPoint> mchTbb(1);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> dataGrahamsAlgTbb = std::make_shared<ppc::core::TaskData>();
  dataGrahamsAlgTbb->inputs.emplace_back(reinterpret_cast<uint8_t *>(points.data()));
  dataGrahamsAlgTbb->inputs_count.emplace_back(points.size());
  dataGrahamsAlgTbb->outputs.emplace_back(reinterpret_cast<uint8_t *>(mchTbb.data()));
  dataGrahamsAlgTbb->outputs_count.emplace_back(mchTbb.size());

  // Create Task
  LoginovTbb::LoginovGrahAlgTbbParallel testGrahamsAlgTbb(dataGrahamsAlgTbb);
  ASSERT_EQ(testGrahamsAlgTbb.validation(), true);
  testGrahamsAlgTbb.pre_processing();
  testGrahamsAlgTbb.run();
  testGrahamsAlgTbb.post_processing();

  for (size_t i = 0; i < mchSeq.size(); ++i) {
    ASSERT_EQ(mchSeq[i], mchTbb[i]);
  }
}

// Only two points
TEST(loginov_m_alg_grah_tbb, Test5) {
  // Create data
  std::vector<LoginovTbb::LoginovPoint> points = {LoginovTbb::LoginovPoint(2.4, -2.9),
                                                  LoginovTbb::LoginovPoint(-1.8, 4.2)};
  std::vector<LoginovTbb::LoginovPoint> mchSeq(2);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> dataGrahamsAlgSeq = std::make_shared<ppc::core::TaskData>();
  dataGrahamsAlgSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(points.data()));
  dataGrahamsAlgSeq->inputs_count.emplace_back(points.size());
  dataGrahamsAlgSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(mchSeq.data()));
  dataGrahamsAlgSeq->outputs_count.emplace_back(mchSeq.size());

  // Create Task
  LoginovTbb::LoginovGrahAlgSequential testGrahamsAlgSeq(dataGrahamsAlgSeq);
  ASSERT_EQ(testGrahamsAlgSeq.validation(), true);
  testGrahamsAlgSeq.pre_processing();
  testGrahamsAlgSeq.run();
  testGrahamsAlgSeq.post_processing();

  // Create data
  std::vector<LoginovTbb::LoginovPoint> mchTbb(2);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> dataGrahamsAlgTbb = std::make_shared<ppc::core::TaskData>();
  dataGrahamsAlgTbb->inputs.emplace_back(reinterpret_cast<uint8_t *>(points.data()));
  dataGrahamsAlgTbb->inputs_count.emplace_back(points.size());
  dataGrahamsAlgTbb->outputs.emplace_back(reinterpret_cast<uint8_t *>(mchTbb.data()));
  dataGrahamsAlgTbb->outputs_count.emplace_back(mchTbb.size());

  // Create Task
  LoginovTbb::LoginovGrahAlgTbbParallel testGrahamsAlgTbb(dataGrahamsAlgTbb);
  ASSERT_EQ(testGrahamsAlgTbb.validation(), true);
  testGrahamsAlgTbb.pre_processing();
  testGrahamsAlgTbb.run();
  testGrahamsAlgTbb.post_processing();

  for (size_t i = 0; i < mchSeq.size(); ++i) {
    ASSERT_EQ(mchSeq[i], mchTbb[i]);
  }
}

// No points
TEST(loginov_m_alg_grah_tbb, Test6) {
  // Create data
  std::vector<LoginovTbb::LoginovPoint> points = {};
  std::vector<LoginovTbb::LoginovPoint> mchSeq(points.size());

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> dataGrahamsAlgSeq = std::make_shared<ppc::core::TaskData>();
  dataGrahamsAlgSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(points.data()));
  dataGrahamsAlgSeq->inputs_count.emplace_back(points.size());
  dataGrahamsAlgSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(mchSeq.data()));
  dataGrahamsAlgSeq->outputs_count.emplace_back(mchSeq.size());

  // Create Task
  LoginovTbb::LoginovGrahAlgSequential testGrahamsAlgSeq(dataGrahamsAlgSeq);
  ASSERT_EQ(testGrahamsAlgSeq.validation(), true);
  testGrahamsAlgSeq.pre_processing();
  testGrahamsAlgSeq.run();
  testGrahamsAlgSeq.post_processing();

  // Create data
  std::vector<LoginovTbb::LoginovPoint> mchTbb(points.size());

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> dataGrahamsAlgTbb = std::make_shared<ppc::core::TaskData>();
  dataGrahamsAlgTbb->inputs.emplace_back(reinterpret_cast<uint8_t *>(points.data()));
  dataGrahamsAlgTbb->inputs_count.emplace_back(points.size());
  dataGrahamsAlgTbb->outputs.emplace_back(reinterpret_cast<uint8_t *>(mchTbb.data()));
  dataGrahamsAlgTbb->outputs_count.emplace_back(mchTbb.size());

  // Create Task
  LoginovTbb::LoginovGrahAlgTbbParallel testGrahamsAlgTbb(dataGrahamsAlgTbb);
  ASSERT_EQ(testGrahamsAlgTbb.validation(), true);
  testGrahamsAlgTbb.pre_processing();
  testGrahamsAlgTbb.run();
  testGrahamsAlgTbb.post_processing();

  for (size_t i = 0; i < mchSeq.size(); ++i) {
    ASSERT_EQ(mchSeq[i], mchTbb[i]);
  }
}

TEST(loginov_m_alg_grah_tbb, Test7) {
  // Create data
  std::vector<LoginovTbb::LoginovPoint> points = {
      LoginovTbb::LoginovPoint(4.4, 1.7), LoginovTbb::LoginovPoint(4.4, 1.7), LoginovTbb::LoginovPoint(4.4, 1.7),
      LoginovTbb::LoginovPoint(4.4, 1.7), LoginovTbb::LoginovPoint(4.4, 1.7), LoginovTbb::LoginovPoint(4.4, 1.7),
      LoginovTbb::LoginovPoint(4.4, 1.7), LoginovTbb::LoginovPoint(4.4, 1.7), LoginovTbb::LoginovPoint(4.4, 1.7),
      LoginovTbb::LoginovPoint(4.4, 1.7)};
  std::vector<LoginovTbb::LoginovPoint> mchSeq(1);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> dataGrahamsAlgSeq = std::make_shared<ppc::core::TaskData>();
  dataGrahamsAlgSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(points.data()));
  dataGrahamsAlgSeq->inputs_count.emplace_back(points.size());
  dataGrahamsAlgSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(mchSeq.data()));
  dataGrahamsAlgSeq->outputs_count.emplace_back(mchSeq.size());

  // Create Task
  LoginovTbb::LoginovGrahAlgSequential testGrahamsAlgSeq(dataGrahamsAlgSeq);
  ASSERT_EQ(testGrahamsAlgSeq.validation(), true);
  testGrahamsAlgSeq.pre_processing();
  testGrahamsAlgSeq.run();
  testGrahamsAlgSeq.post_processing();

  // Create data
  std::vector<LoginovTbb::LoginovPoint> mchTbb(1);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> dataGrahamsAlgTbb = std::make_shared<ppc::core::TaskData>();
  dataGrahamsAlgTbb->inputs.emplace_back(reinterpret_cast<uint8_t *>(points.data()));
  dataGrahamsAlgTbb->inputs_count.emplace_back(points.size());
  dataGrahamsAlgTbb->outputs.emplace_back(reinterpret_cast<uint8_t *>(mchTbb.data()));
  dataGrahamsAlgTbb->outputs_count.emplace_back(mchTbb.size());

  // Create Task
  LoginovTbb::LoginovGrahAlgTbbParallel testGrahamsAlgTbb(dataGrahamsAlgTbb);
  ASSERT_EQ(testGrahamsAlgTbb.validation(), true);
  testGrahamsAlgTbb.pre_processing();
  testGrahamsAlgTbb.run();
  testGrahamsAlgTbb.post_processing();

  for (size_t i = 0; i < mchSeq.size(); ++i) {
    ASSERT_EQ(mchSeq[i], mchTbb[i]);
  }
}