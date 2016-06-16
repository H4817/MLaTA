#include <sstream>
#include "Multiplication.h"

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
            auto tmp = m_inputNumber;
            while (tmp % 3 != 0)
            {
                --tmp;
            }
            auto amountOfTreys = tmp / 3;
            size_t amountOfDeuces = 0;
            if ((m_inputNumber - tmp) % 2 == 0)
            {
                amountOfDeuces = (m_inputNumber - tmp) / 2;
            }

            for (int i = 0; i < amountOfTreys; ++i)
            {
                m_result.push_back(3);
            }
            if (amountOfDeuces == 1)
            {
                m_result.push_back(2);
            }
            else
            {
                for (int i = 0; i < amountOfDeuces; ++i)
                {
                    m_result.push_back(2);
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
        for (auto const & it : m_result)
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
