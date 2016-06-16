#include <iostream>
#include <fstream>
#include <vector>

class CMultiplication
{
public:
    CMultiplication() = default;

    void ReadFromFile(const std::string &nameOfFile);

    void WriteToFile(const std::string &nameOfFile = "output.txt");

    size_t GetInputNumber() const;

    void CalculateMaxMultiplicationSequence();

    const std::vector<size_t> &GetResult() const;

private:
    size_t m_inputNumber;
    std::vector<size_t> m_result;
};

