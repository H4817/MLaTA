#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int, int>> FindingFirstLineOfTrees(vector<vector<short>> &array, size_t &solution)
{
    vector<pair<int, int>> position;
    bool isFirstTreeFound = false;
    bool isFirstLineOfTreesAlreadyFound = false;
    unsigned long sizeOfArray = array.size();
    unsigned long sizeOfLine = array[0].size();
    for (size_t linesCounter = 0; linesCounter < array.size(); ++linesCounter)
    {
        if (isFirstLineOfTreesAlreadyFound)
        {
            break;
        }
        for (size_t columnCounter = 0; columnCounter < array[linesCounter].size(); ++columnCounter)
        {
            if (!isFirstTreeFound && array[linesCounter][columnCounter] == 1)
            {
                isFirstTreeFound = true;
                if (columnCounter != 0 && position.size() < 1)
                {
                    position.push_back({linesCounter, columnCounter - 1});
                    array[linesCounter][columnCounter - 1] = 4;
                    ++solution;
                }
                else if (position.size() < 1)
                {
                    position.push_back({linesCounter, columnCounter});
                    array[linesCounter][columnCounter] = 4;
                    ++solution;
                }
            }
            else if (isFirstTreeFound)
            {
                if (array[linesCounter][columnCounter] == 1)
                {
                    //++solution;
                    if (columnCounter == sizeOfLine && position.size() < 1)
                    {
                        position.push_back({linesCounter, columnCounter});
                        array[linesCounter][columnCounter] = 4;
                        ++solution;
                    }
                    else if (array[linesCounter][columnCounter + 1] != 1 && position.size() < 1)
                    {
                        position.push_back({linesCounter, columnCounter + 1});
                        array[linesCounter][columnCounter] = 4;
                        ++solution;
                    }
                    if (array[linesCounter][columnCounter - 1] != 1 && position.size() < 1)
                    {
                        position.push_back({linesCounter, columnCounter - 1});
                        array[linesCounter][columnCounter] = 4;
                        ++solution;
                    }
                }
            }
        }
        if (isFirstTreeFound)
        {
            isFirstTreeFound = false;
            isFirstLineOfTreesAlreadyFound = true;
        }
    }
    if (sizeOfArray == 0)
    {
        cout << "Error, the input file without trees" << endl;
        exit(EXIT_FAILURE);
    }
    return position;
}

vector<vector<short>> CreateArray(ifstream &inputFile)
{
    string str;
    pair<size_t, size_t> size;

    inputFile >> size.first;
    inputFile >> size.second;

    getline(inputFile, str);

    vector<vector<short> > area(size.first, vector<short>(size.second));

    for (int lineNo = 0; (getline(inputFile, str) && lineNo < size.first); ++lineNo)
    {
        for (size_t columnNo = 0; columnNo < size.second; ++columnNo)
        {
            area[lineNo][columnNo] = short(str[columnNo] - '0');
        }
    }
    return area;
}

bool PushIfNotFound(vector<pair<int, int>> &position, const pair<int, int> &expectedPoint)
{
    if (find(position.begin(), position.end(), expectedPoint) == position.end())
    {
        position.push_back(expectedPoint);
        return true;
    }
    return false;
}

// TODO: don't pass int, float, double by ref
bool AreAnyOfNeighborsATree(const int &i, const int &j, const int &positionCounter, vector<pair<int, int>> &position,
                            vector<vector<short>> &array)
{
    size_t sizeOfArray = array.size();
    size_t sizeOfLine = array[0].size();
    if (i > 0 && array[i - 1][j] == 1)
    {
        if (PushIfNotFound(position, {i, j}))
        {
            return true;
        }
    }
    else if (i < sizeOfArray && array[i + 1][j] == 1)
    {
        if (PushIfNotFound(position, {i, j}))
        {
            return true;
        }
    }
    else if (j > 0 && array[i][j - 1] == 1)
    {
        if (PushIfNotFound(position, {i, j}))
        {
            return true;
        }
    }
    else if (j < sizeOfLine && array[i][j + 1] == 1)
    {
        if (PushIfNotFound(position, {i, j}))
        {
            return true;
        }
    }
    else if (i < array.size() && j < sizeOfLine && array[i + 1][j + 1] == 1)
    {
        if (PushIfNotFound(position, {i, j}))
        {
            return true;
        }
    }
    else if (i > 0 && j > 0 &&
             array[i - 1][j - 1] == 1)
    {
        if (PushIfNotFound(position, {i, j}))
        {
            return true;
        }
    }
    else if (i < sizeOfArray && j > 0 &&
             array[i + 1][j - 1] == 1)
    {
        if (PushIfNotFound(position, {i, j}))
        {
            return true;
        }
    }
    else if (i > 0 && j < sizeOfLine &&
             array[i - 1][j + 1] == 1)
    {
        if (PushIfNotFound(position, {i, j}))
        {
            return true;
        }
    }
    position.erase(position.begin() + positionCounter);
    return false;
}

void PrintResult(vector<vector<short>> &array, const size_t &solution)
{
    unsigned long sizeOfArray = array.size();
    unsigned long sizeOfLine = array[0].size();
    for (int i = 0; i < sizeOfArray; ++i)
    {
        for (int j = 0; j < sizeOfLine; ++j)
        {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
    cout << solution << endl;
}
//TODO: change vector to unordered map
void WavesAlgorithm(vector<pair<int, int>> &position, vector<vector<short>> &array, size_t &solution)
{
    unsigned long sizeOfArray = array.size();
    unsigned long sizeOfLine = array[0].size();
    for (int i = 0; i < position.size() && position.size() != 0; ++i)
    {
        for (size_t linesCounter = 0; linesCounter < sizeOfArray && position.size() != 0; ++linesCounter)
        {
            for (size_t columnCounter = 0; columnCounter < sizeOfLine && position.size() != 0; ++columnCounter)
            {
                if (position[i].first > 0 && array[position[i].first - 1][position[i].second] == 0 &&
                    AreAnyOfNeighborsATree(position[i].first - 1, position[i].second, i, position, array))
                {
                    array[position.back().first][position.back().second] = 4;
                    ++solution;
                }
                else if (position[i].first < array.size() && array[position[i].first + 1][position[i].second] == 0 &&
                         AreAnyOfNeighborsATree(position[i].first + 1, position[i].second, i, position, array))
                {
                    array[position.back().first][position.back().second] = 4;
                    ++solution;
                }
                else if (position[i].second > 0 && array[position[i].first][position[i].second - 1] == 0 &&
                         AreAnyOfNeighborsATree(position[i].first, position[i].second - 1, i, position, array))
                {
                    array[position.back().first][position.back().second] = 4;
                    ++solution;
                }
                else if (position[i].second < sizeOfLine &&
                         array[position[i].first][position[i].second + 1] == 0 &&
                         AreAnyOfNeighborsATree(position[i].first, position[i].second + 1, i, position, array))
                {
                    array[position.back().first][position.back().second] = 4;
                    ++solution;
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Number parameters is wrong. Please put a file name into command line" << endl;
        return 1;
    }
    ifstream inputFile(argv[1]);
    if (!inputFile)
    {
        cout << "Can't open file " << argv[1] << endl;
        return 1;
    }

    size_t solution = 0;

    vector<vector<short>> array = CreateArray(inputFile);
    vector<pair<int, int>> position = FindingFirstLineOfTrees(array, solution);

    WavesAlgorithm(position, array, solution);
    PrintResult(array, solution);

    return 0;
}
//TODO 1)
//TODO 2) Деполякизация
//TODO 3)
//TODO 4)
//TODO 5)
