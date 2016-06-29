#include "FileManager.h"

void CFileManager::SetInputFile(const std::string & nameInputFile)
{
    if (m_nameOfInputFile.size() == 0)
    {
        m_nameOfInputFile = nameInputFile;
        OpenFileForReading(m_inputFile, m_nameOfInputFile);
    }
    else
    {
        throw logic_error("cannot open the file: " + nameInputFile);
    }
}

void CFileManager::SetOutputFile(const std::string & nameOutputFile)
{
    if (m_nameOfOutputFile.size() == 0)
    {
        m_nameOfOutputFile = nameOutputFile;
        OpenFileForWriting(m_outputFile, m_nameOfOutputFile);
    }
    else
    {
        throw logic_error("cannot open the file: " + nameOutputFile);
    }
}

void CFileManager::OpenFileForReading(std::ifstream &file, const std::string &fileName)
{
    file.open(fileName);
    file.exceptions(std::ifstream::badbit);
    if (!file.is_open())
    {
        throw std::ifstream::failure("cannot open the file: " + fileName);
    }
}

void CFileManager::OpenFileForWriting(std::ofstream &file, const std::string &fileName)
{
    file.open(fileName);
    file.exceptions(std::ofstream::badbit);
    if (!file.is_open())
    {
        throw std::ofstream::failure("cannot open the file: " + fileName);
    }
}
