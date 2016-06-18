#include <iostream>
#include <fstream>
#include <vector>

class CMultiplication
{
public:
    CMultiplication() = default;

    void ReadFromFile(const std::string &nameOfFile);

    void WriteToFile(const std::string &nameOfFile = "output.txt");

    int GetInputNumber() const;

    int GetDifference();

    void CalculateMaxMultiplicationSequence();

    const std::vector<int> &GetResult() const;

private:
    int m_inputNumber;
    std::vector<int> m_result;
};

