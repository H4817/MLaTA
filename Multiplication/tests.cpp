#define BOOST_TEST_MODULE MyTestModule

#include <boost/test/included/unit_test.hpp>

#include "Multiplication.h"

struct MultiplicationFixture
{
    CMultiplication multiplication;
};

BOOST_FIXTURE_TEST_SUITE(tests_for_multiplication, MultiplicationFixture)
    BOOST_AUTO_TEST_CASE(read_from_file)
    {
        BOOST_CHECK_NO_THROW(multiplication.ReadFromFile("input.txt"));
        BOOST_CHECK_EQUAL(multiplication.GetInputNumber(), 100);
    }
    
    BOOST_AUTO_TEST_CASE(main_algorithm)
    {
        BOOST_CHECK_NO_THROW(multiplication.ReadFromFile("input.txt"));
        BOOST_CHECK_EQUAL(multiplication.GetInputNumber(), 100);
        std::vector<size_t> expectedResult = {2, 3, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
        BOOST_CHECK_NO_THROW(multiplication.CalculateMaxMultiplicationSequence());
        BOOST_CHECK(multiplication.GetResult() == expectedResult);
    }
    
/*    BOOST_AUTO_TEST_CASE(write_to_file)
    {
        BOOST_CHECK_NO_THROW(multiplication.ReadFromFile("input.txt"));
        BOOST_CHECK_EQUAL(multiplication.GetInputNumber(), 8);
//        std::vector<size_t> expectedResult = {3, 3, 2};
        BOOST_CHECK_NO_THROW(multiplication.WriteToFile("output.txt"));
//        BOOST_CHECK_NO_THROW(multiplication.ReadFromFile("output.txt"));
//        BOOST_CHECK_EQUAL(multiplication.GetInputNumber(), 3);
    }*/
BOOST_AUTO_TEST_SUITE_END()