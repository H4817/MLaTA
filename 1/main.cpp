#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct SizeOfMap {
    pair <size_t, size_t> size;
};

vector<pair<int, int>> FindingFirstLineOfTrees(short **array, size_t &solution, SizeOfMap & sizeOfMap) {
    vector<pair<int, int>> position;
    bool isFirstTreeFound = false;
    bool isFirstLineOfTreesAlreadyFound = false;
    for (size_t linesCounter = 0; linesCounter < sizeOfMap.size.first; ++linesCounter) {
        if (isFirstLineOfTreesAlreadyFound) {
            break;
        }
        for (size_t columnCounter = 0; columnCounter < sizeOfMap.size.second; ++columnCounter) {
            if (!isFirstTreeFound && array[linesCounter][columnCounter] == 1) {
                isFirstTreeFound = true;
                if (columnCounter != 0) {
                    position.push_back({linesCounter, columnCounter - 1});
                    array[linesCounter][columnCounter - 1] = 4;
                    ++solution;
                }
                else {
                    position.push_back({linesCounter, columnCounter});
                    array[linesCounter][columnCounter] = 4;
                    ++solution;
                }
            }
            else if (isFirstTreeFound) {
                if (array[linesCounter][columnCounter] == 1) {
                    ++solution;
                    if (columnCounter == sizeOfMap.size.second) {
                        position.push_back({linesCounter, columnCounter});
                        array[linesCounter][columnCounter] = 4;
                        ++solution;
                    }
                    else if (array[linesCounter][columnCounter + 1] != 1) {
                        position.push_back({linesCounter, columnCounter + 1});
                        array[linesCounter][columnCounter] = 4;
                        ++solution;
                    }
                    if (array[linesCounter][columnCounter - 1] != 1) {
                        position.push_back({linesCounter, columnCounter - 1});
                        array[linesCounter][columnCounter] = 4;
                        ++solution;
                    }
                }
            }
        }
        if (isFirstTreeFound) {
            isFirstTreeFound = false;
            isFirstLineOfTreesAlreadyFound = true;
        }
    }
    if (position.size() == 0) {
        cout << "Error, the input file without trees" << endl;
        exit(EXIT_FAILURE);
    }
    return position;
}

short **CreateArray(ifstream &inputFile, SizeOfMap & sizeOfMap) {
    short **array;
    string str;

    inputFile >> sizeOfMap.size.first;
    inputFile >> sizeOfMap.size.second;

    getline(inputFile, str);

    array = new short *[sizeOfMap.size.first];
    for (int i = 0; i < sizeOfMap.size.first; ++i) {
        array[i] = new short[sizeOfMap.size.first];
    }

    for (int linesCounter = 0; (getline(inputFile, str) && linesCounter < sizeOfMap.size.first); ++linesCounter) {
        const char *ch = str.c_str();
        for (size_t columnCounter = 0; columnCounter < sizeOfMap.size.first; ++columnCounter) {
            array[linesCounter][columnCounter] = short(ch[columnCounter] - '0');
        }
    }
    return array;
}

bool itsTheSamePoint(const vector<pair<int, int>> &position, const pair<int, int> &expectedPoint) {
    return (find(position.begin(), position.end(), expectedPoint) != position.end());
}

bool AreAnyOfNeighborsATree(const int &i, const int &j, const int &positionCounter, vector<pair<int, int>> &position,
                            short **array, SizeOfMap & sizeOfMap) {
    if (i > 0 && array[i - 1][j] == 1) {
        if (!itsTheSamePoint(position, {i, j})) {
            position.push_back(make_pair(i, j));
            return true;
        }
    }
    else if (i < sizeOfMap.size.first && array[i + 1][j] == 1) {
        if (!itsTheSamePoint(position, {i, j})) {
            position.push_back(make_pair(i, j));
            return true;
        }
    }
    else if (j > 0 && array[i][j - 1] == 1) {
        if (!itsTheSamePoint(position, {i, j})) {
            position.push_back(make_pair(i, j));
            return true;
        }
    }
    else if (j < sizeOfMap.size.second && array[i][j + 1] == 1) {
        if (!itsTheSamePoint(position, {i, j})) {
            position.push_back(make_pair(i, j));
            return true;
        }
    }
    else if (i < sizeOfMap.size.first && j < sizeOfMap.size.second && array[i + 1][j + 1] == 1) {
        if (!itsTheSamePoint(position, {i, j})) {
            position.push_back(make_pair(i, j));
            return true;
        }
    }
    else if (i > 0 && j > 0 &&
             array[i - 1][j - 1] == 1) {
        if (!itsTheSamePoint(position, {i, j})) {
            position.push_back(make_pair(i, j));
            return true;
        }
    }
    else if (i < sizeOfMap.size.first && j > 0 &&
             array[i + 1][j - 1] == 1) {
        if (!itsTheSamePoint(position, {i, j})) {
            position.push_back(make_pair(i, j));
            return true;
        }
    }
    else if (i > 0 && j < sizeOfMap.size.second &&
             array[i - 1][j + 1] == 1) {
        if (!itsTheSamePoint(position, {i, j})) {
            position.push_back(make_pair(i, j));
            return true;
        }
    }
    position.erase(position.begin() + positionCounter);
    return false;
}


void PrintResult(short **array, const size_t &solution, SizeOfMap & sizeOfMap) {
    for (int i = 0; i < sizeOfMap.size.first; ++i) {
        for (int j = 0; j < sizeOfMap.size.first; ++j) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
    cout << solution << endl;
}

void WavesAlgorithm(vector<pair<int, int>> &position, short **array, size_t &solution, SizeOfMap & sizeOfMap) {
    for (int i = 0; i < position.size() && position.size() != 0; ++i) {
        for (size_t linesCounter = 0; linesCounter < sizeOfMap.size.first && position.size() != 0; ++linesCounter) {
            for (size_t columnCounter = 0; columnCounter < sizeOfMap.size.second && position.size() != 0; ++columnCounter) {
                if (position[i].first > 0 && array[position[i].first - 1][position[i].second] == 0 &&
                        AreAnyOfNeighborsATree(position[i].first - 1, position[i].second, i, position, array, sizeOfMap)) {
                    array[position.back().first][position.back().second] = 4;
                    ++solution;
                }
                else if (position[i].first < sizeOfMap.size.first && array[position[i].first + 1][position[i].second] == 0 &&
                        AreAnyOfNeighborsATree(position[i].first + 1, position[i].second, i, position, array, sizeOfMap)) {
                    array[position.back().first][position.back().second] = 4;
                    ++solution;
                }
                else if (position[i].second > 0 && array[position[i].first][position[i].second - 1] == 0 &&
                        AreAnyOfNeighborsATree(position[i].first, position[i].second - 1, i, position, array, sizeOfMap)) {
                    array[position.back().first][position.back().second] = 4;
                    ++solution;
                }
                else if (position[i].second < sizeOfMap.size.second && array[position[i].first][position[i].second + 1] == 0 &&
                        AreAnyOfNeighborsATree(position[i].first, position[i].second + 1, i, position, array, sizeOfMap)) {
                    array[position.back().first][position.back().second] = 4;
                    ++solution;
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Number parameters is wrong. Please put a file name into command line" << endl;
        return 1;
    }
    ifstream inputFile(argv[1]);
    if (!inputFile) {
        cout << "Can't open file " << argv[1] << endl;
        return 1;
    }

    size_t solution = 0;
    SizeOfMap sizeOfMap;

    short **array = CreateArray(inputFile, sizeOfMap);
    vector<pair<int, int>> position = FindingFirstLineOfTrees(array, solution, sizeOfMap);

    WavesAlgorithm(position, array, solution, sizeOfMap);
    PrintResult(array, solution, sizeOfMap);

    return 0;
}
