#include <gtest/gtest.h>

#include <fstream>

#include "../brick_game/snake/model.h"

class ModelTest : public ::testing::Test {
 protected:
  void SetUp() override { model = new s21::Model(); }

  void TearDown() override { delete model; }

  s21::Model* model;
};

TEST_F(ModelTest, InitialGameStatus) {
  EXPECT_EQ(model->getGameStatus(), LIVE);
}

TEST_F(ModelTest, InitialDirection) { EXPECT_EQ(model->getDirection(), RIGHT); }

TEST_F(ModelTest, InitialSnakeSize) { EXPECT_EQ(model->getSnake().size(), 4); }

TEST_F(ModelTest, InitialApplePosition) {
  EXPECT_EQ(model->getApple(), std::make_pair(5, 18));
}

TEST_F(ModelTest, ChangeDirection) {
  model->changeDirection('d');
  EXPECT_EQ(model->getDirection(), RIGHT);

  model->changeDirection('w');
  EXPECT_EQ(model->getDirection(), UP);

  model->changeDirection('a');
  EXPECT_EQ(model->getDirection(), LEFT);

  model->changeDirection('s');
  EXPECT_EQ(model->getDirection(), DOWN);
}

TEST_F(ModelTest, ChangeGameStatus) {
  model->changeDirection('q');
  EXPECT_EQ(model->getStatus(), END);

  model->changeDirection('p');
  EXPECT_EQ(model->getStatus(), STOP);

  model->changeDirection('f');
  model->s21_update();
  // EXPECT_EQ(model->getTimer(), LEFT);
  EXPECT_DOUBLE_EQ(model->getTimer().tv_nsec, (250000000L * 0.65));
}

TEST_F(ModelTest, AppleCollision) {
  // тп перед яблоком яблоко
  model->setSnake({5, 17});

  int initialScore = model->getScore();

  model->s21_update();
  EXPECT_EQ(model->getScore(), initialScore + 1);
}

TEST_F(ModelTest, WallCollision) {
  // тп в стену
  std::pair<int, int> wall = {0, 5};
  model->setSnake(wall);
  model->s21_update();
  EXPECT_EQ(model->getGameStatus(), END);
}

TEST_F(ModelTest, SelfCollision) {
  // тп в себя
  model->setSnake(model->getSnake().back());
  model->s21_update();
  EXPECT_EQ(model->getGameStatus(), END);
}

TEST_F(ModelTest, UpdateSnake) {
  auto initialHead = model->getSnake().front();
  model->setDirection(RIGHT);
  model->updateSnake();
  auto newHead = model->getSnake().front();
  EXPECT_EQ(newHead.second, initialHead.second + 1);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
