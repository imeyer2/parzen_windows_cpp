/**
 * Description: Unit tests for `BasePDFGenerator` class
 */


#include <gtest/gtest.h>
#include <parzen_windows/base_pdf_generator.hpp> // Question: How is intellisense able to autocomplete this? Due to CMake?
#include <iostream>

TEST(TestIntantiation, BasicAssertions) {
    BasePDFGenerator<double> bpg( { {0, 1, 2} } );

    EXPECT_TRUE(bpg.trainingDatapoints.size() > 0);
};