#include <iostream>
#include <fstream>

using namespace std;

size_t N;
size_t M;

void WasError(int ErrorCode) {
    cout << "Program executed with error: " << ErrorCode << '\n';
    exit(EXIT_FAILURE);
}

void FillMatrix(ifstream &ifs) {
    ifs >> N >> M;
    char matrix[N][N];
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            ifs >> matrix[i][j];
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    for (size_t i = 0; i < M; i++) {
        for (size_t j = 0; j < M; j++) {
            if (matrix[i][j] != '.') {
                cout << "Error, there is no place for raft" << '\n';
                WasError(2);
            }
        }
    }
}

void OpenFile(string inputFile) {
    ifstream ifs;
    ifs.open(inputFile);
    if (!ifs.is_open()) {
        cout << "Error, cant open file: " << inputFile << "\n";
        WasError(1);
    }
    FillMatrix(ifs);
}


void CalculateSteps(char &matrix[N][N]) {
    enum direction {
        RIGHT, LEFT, BOTTOM, TOP
    };
    direction dir;
    switch (dir) {
        case RIGHT: {
            for (size_t i = 0; ((matrix[i][N - 1] != '@') && (i < N - 1)); ++i) {
                if (matrix[i][N - 1] == '@') {
                    dir = BOTTOM;
                    break;
                }
            }
        }
        case LEFT: {
            for (size_t i = 0; ((matrix[i][0] != '@') && (i < N - 1)); ++i) {
                if (matrix[i][0] == '@') {
                   dir =
                   break;
                }
            }
        }
        case BOTTOM: {
            for (size_t i = 0; ((matrix[N - 1][i] != '@') && (i < N - 1)); ++i) {

            }
        }
        case TOP: {
            for (size_t i = 0; ((matrix[0][i] != '@') && (i < N - 1)); ++i) {

            }
        }
        default:
            break;
    }
}

void OutputResult() {

}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "You forgot to pass some name of file into the command line" << endl;
        return -1;
    }
    string inputFile = argv[1];
    OpenFile(inputFile);
    return 0;
}