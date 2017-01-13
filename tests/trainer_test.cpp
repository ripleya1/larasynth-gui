#include <string>

#include "trainer.hpp"

#include "gtest/gtest.h"

using namespace std;
using namespace larasynth;

TEST( LstmTrainerTest, SimpleSequence ) {
  string directory = "test_files/trainer_test";
  volatile sig_atomic_t shutdown_flag = false;

  Trainer trainer( directory, &shutdown_flag );
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
