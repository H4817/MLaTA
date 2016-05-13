#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

size_t N;
size_t K;

vector<pair<int, int>> FindingFirstLineOfTrees(short **array, size_t &solution) {
    vector<pair<int, int>> position;
    bool isFirstTreeFound = false;
    bool isFirstLineOfTreesAlreadyFound = false;
    for (size_t linesCounter = 0; linesCounter < N; ++linesCounter) {
        if (isFirstLineOfTreesAlreadyFound) {
            break;
        }
        for (size_t columnCounter = 0; columnCounter < K; ++columnCounter) {
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
                    if (columnCounter == K) {
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

short **CreateArray(ifstream &inputFile) {
    short **array;
    string str;

    inputFile >> N;
    inputFile >> K;

    getline(inputFile, str);

    array = new short *[N];
    for (int i = 0; i < N; ++i) {
        array[i] = new short[K];
    }

    for (int linesCounter = 0; (getline(inputFile, str) && linesCounter < N); ++linesCounter) {
        const char *ch = str.c_str();
        for (size_t columnCounter = 0; columnCounter < K; ++columnCounter) {
            array[linesCounter][columnCounter] = short(ch[columnCounter] - '0');
        }
    }
    return array;
}

bool itsTheSamePoint(const vector<pair<int, int>> &position, const pair<int, int> &expectedPoint) {
    return (find(position.begin(), position.end(), expectedPoint) != position.end());
}

bool AreAnyOfNeighborsATree(const int &i, const int &j, const int &positionCounter, vector<pair<int, int>> &position,
                            short **array) {
    if (i > 0 && array[i - 1][j] == 1) {
        if (!itsTheSamePoint(position, {i, j})) {
            position.push_back(make_pair(i, j));
            return true;
        }
    }
    else if (i < N && array[i + 1][j] == 1) {
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
    else if (j < K && array[i][j + 1] == 1) {
        if (!itsTheSamePoint(position, {i, j})) {
            position.push_back(make_pair(i, j));
            return true;
        }
    }
    else if (i < N && j < K && array[i + 1][j + 1] == 1) {
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
    else if (i < N && j > 0 &&
             array[i + 1][j - 1] == 1) {
        if (!itsTheSamePoint(position, {i, j})) {
            position.push_back(make_pair(i, j));
            return true;
        }
    }
    else if (i > 0 && j < K &&
             array[i - 1][j + 1] == 1) {
        if (!itsTheSamePoint(position, {i, j})) {
            position.push_back(make_pair(i, j));
            return true;
        }
    }
    position.erase(position.begin() + positionCounter);
    return false;
}


void PrintResult(short **array, const size_t &solution) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < K; ++j) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
    cout << solution << endl;
}

void WavesAlgorithm(vector<pair<int, int>> &position, short **array, size_t &solution) {
    for (int i = 0; i < position.size() && position.size() != 0; ++i) {
        for (size_t linesCounter = 0; linesCounter < N && position.size() != 0; ++linesCounter) {
            for (size_t columnCounter = 0; columnCounter < K && position.size() != 0; ++columnCounter) {
                if (position[i].first > 0 && array[position[i].first - 1][position[i].second] == 0 &&
                        AreAnyOfNeighborsATree(position[i].first - 1, position[i].second, i, position, array)) {
                    array[position.back().first][position.back().second] = 4;
                    ++solution;
                }
                else if (position[i].first < N && array[position[i].first + 1][position[i].second] == 0 &&
                        AreAnyOfNeighborsATree(position[i].first + 1, position[i].second, i, position, array)) {
                    array[position.back().first][position.back().second] = 4;
                    ++solution;
                }
                else if (position[i].second > 0 && array[position[i].first][position[i].second - 1] == 0 &&
                        AreAnyOfNeighborsATree(position[i].first, position[i].second - 1, i, position, array)) {
                    array[position.back().first][position.back().second] = 4;
                    ++solution;
                }
                else if (position[i].second < K && array[position[i].first][position[i].second + 1] == 0 &&
                        AreAnyOfNeighborsATree(position[i].first, position[i].second + 1, i, position, array)) {
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

    short **array = CreateArray(inputFile);
    vector<pair<int, int>> position = FindingFirstLineOfTrees(array, solution);

    WavesAlgorithm(position, array, solution);
    PrintResult(array, solution);

    return 0;
}