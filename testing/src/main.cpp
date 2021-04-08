#include <gtest/gtest.h>
#include "utils.h"

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    if (argc < 3) {
        std::cout << "Please specify test seed, array size and shared lib path in arguments.." << std::endl;
        return -1;
    }
    TestConfig::testSeed = std::stoul(argv[1]);
    TestConfig::arraySize = std::stoul(argv[2]);
    TestConfig::sharedLibraryPath = argv[3];
    return RUN_ALL_TESTS();
}