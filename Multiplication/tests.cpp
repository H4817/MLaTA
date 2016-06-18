#define BOOST_TEST_MODULE MyTestModule

#include <boost/test/included/unit_test.hpp>

#include "Multiplication.h"

struct MultiplicationFixture
{
    CMultiplication multiplication;
};

BOOST_FIXTURE_TEST_SUITE(tests_for_multiplication, MultiplicationFixture)
    
    BOOST_AUTO_TEST_SUITE(check_edges)
        BOOST_AUTO_TEST_CASE(lower_edge)
        {
            BOOST_CHECK_NO_THROW(multiplication.ReadFromFile("input0.txt"));
            BOOST_CHECK_EQUAL(multiplication.GetInputNumber(), 1);
            BOOST_CHECK_NO_THROW(multiplication.CalculateMaxMultiplicationSequence());
            BOOST_CHECK_NO_THROW(multiplication.WriteToFile("output0.txt"));
        }

        BOOST_AUTO_TEST_CASE(upper_edge)
        {
            BOOST_CHECK_NO_THROW(multiplication.ReadFromFile("input1.txt"));
            BOOST_CHECK_EQUAL(multiplication.GetInputNumber(), 10000);
            BOOST_CHECK_NO_THROW(multiplication.CalculateMaxMultiplicationSequence());
            BOOST_CHECK_NO_THROW(multiplication.WriteToFile("output1.txt"));
        }
        
        BOOST_AUTO_TEST_CASE(beneath_the_lower_edge)
        {
            BOOST_CHECK_NO_THROW(multiplication.ReadFromFile("input2.txt"));
            BOOST_CHECK_EQUAL(multiplication.GetInputNumber(), -2);
            multiplication.CalculateMaxMultiplicationSequence();
            BOOST_CHECK_NO_THROW(multiplication.WriteToFile("output2.txt"));
        }
        
        BOOST_AUTO_TEST_CASE(above_the_upper_edge)
        {
            BOOST_CHECK_NO_THROW(multiplication.ReadFromFile("input3.txt"));
            BOOST_CHECK_EQUAL(multiplication.GetInputNumber(), 10012);
            multiplication.CalculateMaxMultiplicationSequence();
            BOOST_CHECK_NO_THROW(multiplication.WriteToFile("output3.txt"));
        }
    BOOST_AUTO_TEST_SUITE_END()
    
    BOOST_AUTO_TEST_SUITE(compare_with_example_result)
        BOOST_AUTO_TEST_CASE(first_case)
        {
            BOOST_CHECK_NO_THROW(multiplication.ReadFromFile("input4.txt"));
            BOOST_CHECK_EQUAL(multiplication.GetInputNumber(), 8);
            std::vector<int> expectedResult = {3, 5};
            BOOST_CHECK_NO_THROW(multiplication.CalculateMaxMultiplicationSequence());
            BOOST_CHECK_NO_THROW(multiplication.WriteToFile("output4.txt"));
            BOOST_CHECK(multiplication.GetResult() == expectedResult);
        }
        
        BOOST_AUTO_TEST_CASE(second_case)
        {
            BOOST_CHECK_NO_THROW(multiplication.ReadFromFile("input5.txt"));
            BOOST_CHECK_EQUAL(multiplication.GetInputNumber(), 100);
            std::vector<int> expectedResult = {2, 3, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
            BOOST_CHECK_NO_THROW(multiplication.CalculateMaxMultiplicationSequence());
            BOOST_CHECK_NO_THROW(multiplication.WriteToFile("output5.txt"));
            BOOST_CHECK(multiplication.GetResult() == expectedResult);
        }
    BOOST_AUTO_TEST_SUITE_END()
    
BOOST_AUTO_TEST_SUITE_END()