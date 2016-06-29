#pragma once

#include <iostream>
#include <fstream>

class CFileManager
{
public:
    virtual ~CFileManager() = default;

    void SetInputFile(const std::string &nameInputFile);

    void SetOutputFile(const std::string &nameOutputFile);

    void OpenFileForReading(std::ifstream &file, const std::string &fileName);

    void OpenFileForWriting(std::ofstream &file, const std::string &fileName);

private:
    std::string m_nameOfInputFile;
    std::string m_nameOfOutputFile;

    std::ifstream m_inputFile;
    std::ofstream m_outputFile;
};


