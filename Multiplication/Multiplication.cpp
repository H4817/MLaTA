#include <sstream>
#include "Multiplication.h"
#include <algorithm>

int CMultiplication::GetInputNumber() const
{
    return m_inputNumber;
}

const std::vector<int> &CMultiplication::GetResult() const
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

int CMultiplication::GetDifference()
{
    int sumOfElements = 0;
    for (auto const & n : m_result)
        sumOfElements += n;
    return m_inputNumber - sumOfElements;
}

void CMultiplication::CalculateMaxMultiplicationSequence()
{
    if (m_inputNumber >= 1 && m_inputNumber <= 10000)
    {
        if (m_inputNumber == 1 || m_inputNumber == 2 || m_inputNumber == 3 || m_inputNumber == 4)
        {
            m_result.push_back(m_inputNumber);
        }
        else
        {
            int counter = 2;
            for (; ;)
            {
                auto difference = GetDifference();
                if (difference == 0)
                    break;
                else if (difference > 0)
                {
                    m_result.push_back(counter);
                    ++counter;
                }
                else
                {
                    difference *= -1;
                    if (std::find(m_result.begin(), m_result.end(), difference) != m_result.end())
                    {
                        for (size_t i = 0; i < m_result.size(); ++i)
                        {
                            if (m_result[i] == difference)
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
                            auto number = m_result[i] - difference;
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
