#include <sstream>
#include "Multiplication.h"
#include <algorithm>

size_t CMultiplication::GetInputNumber() const
{
    return m_inputNumber;
}

const std::vector<size_t> &CMultiplication::GetResult() const
{
    return m_result;
}

void CMultiplication::ReadFromFile(const std::string &nameOfFile)
{
    std::ifstream input(nameOfFile);
    if (input.is_open())
    {
        std::string str;
        getline(input, str);
        std::stringstream sstream(str);
        sstream >> m_inputNumber;
    }
    else
    {
        std::cout << "Error, cannot open the file: " << nameOfFile << std::endl;
        throw;
    }
}

size_t CMultiplication::GetDifference()
{
    size_t sum = 0;
    for (auto const &it : m_result)
    {
        sum += it;
    }
    return m_inputNumber - sum;
}

void CMultiplication::CalculateMaxMultiplicationSequence()
{
    if (m_inputNumber >= 1 && m_inputNumber <= 10000)
    {
        if (m_inputNumber == 1 || m_inputNumber == 2 || m_inputNumber == 3 || m_inputNumber == 4) //fix it
        {
            m_result.push_back(m_inputNumber);
        }
        else //and it
        {
            size_t counter = 0;
            counter = 2;
            while ( GetDifference() != 0 || m_result.size() == 0)
            {
                auto diff = GetDifference();
                if (diff > 0)
                {
                    m_result.push_back(counter);
                }
                else
                {
                    diff *= -1;
                    if (std::find(m_result.begin(), m_result.end(), diff) != m_result.end())
                    {
                        for (size_t i = 0; i < m_result.size(); ++i)
                        {
                            if (m_result[i] == diff)
                            {
                                m_result.erase(m_result.begin() + i);
                                break;
                            }
                        }
                    }
                    else
                    {
                        for (size_t i = 0; i < m_result.size(); ++i)
                        {
                            auto number = m_result[i] - diff;
                            if (std::find(m_result.begin(), m_result.end(), number) == m_result.end())
                            {
                                if (number != 1)
                                    m_result[i] = number;
                                else
                                    m_result.erase(m_result.begin() + i);
                            }
                        }
                    }
                }
                ++counter;
            }
        }
    }
    else
    {
        std::cout << "Error, the input number: " << m_inputNumber << " should belong [1, 10000] edges" << std::endl;
        throw;
    }
}

void CMultiplication::WriteToFile(const std::string &nameOfFile)
{
    std::ofstream output;
    output.open(nameOfFile);
    if (output.is_open())
    {
        for (auto const &it : m_result)
        {
            output << it << " ";
        }
        output.close();
    }
    else
    {
        std::cout << "Error, cannot open the file: " << nameOfFile << std::endl;
        throw;
    }
}