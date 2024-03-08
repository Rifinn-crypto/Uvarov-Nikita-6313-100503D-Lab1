#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;

vector<vector<int>> multiplyMatrices(vector<vector<int>>& matrix1, vector<vector<int>>& matrix2) {
    int rows1 = matrix1.size();
    int cols1 = matrix1[0].size();
    int rows2 = matrix2.size();
    int cols2 = matrix2[0].size();

    if (cols1 != rows2) {
        throw std::length_error("Incompatible matrix sizes for multiplication.");
    }

    vector<vector<int>> result(rows1, vector<int>(cols2, 0));

    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            for (int k = 0; k < cols1; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return result;
}

int main() {
    try {
        // Чтение матриц из файлов
        ifstream file1("C:\\Users\\esh20\\OneDrive\\Рабочий стол\\HTML+MATH\\TS\\ParallProg\\matrix1.txt");
        ifstream file2("C:\\Users\\esh20\\OneDrive\\Рабочий стол\\HTML+MATH\\TS\\ParallProg\\matrix2.txt");

        int rows1, cols1, rows2, cols2;
        file1 >> rows1 >> cols1;
        file2 >> rows2 >> cols2;

        vector<vector<int>> matrix1(rows1, vector<int>(cols1));
        vector<vector<int>> matrix2(rows2, vector<int>(cols2));

        for (int i = 0; i < rows1; i++) {
            for (int j = 0; j < cols1; j++) {
                file1 >> matrix1[i][j];
            }
        }

        for (int i = 0; i < rows2; i++) {
            for (int j = 0; j < cols2; j++) {
                file2 >> matrix2[i][j];
            }
        }

        // Умножение матриц
        auto start = chrono::high_resolution_clock::now();
        vector<vector<int>> result = multiplyMatrices(matrix1, matrix2);
        auto end = chrono::high_resolution_clock::now();

        // Замер времени выполнения
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

        // Сохранение результатов в файл
        ofstream outputFile("C:\\Users\\esh20\\OneDrive\\Рабочий стол\\HTML+MATH\\TS\\ParallProg\\result.txt");
        for (int i = 0; i < rows1; i++) {
            for (int j = 0; j < cols2; j++) {
                outputFile << result[i][j] << " ";
            }
            outputFile << endl;
        }

        // Отображение времени выполнения
        cout << "Execution time: " << duration.count() << " mcs" << endl;

        // Вывод об объеме задачи
        cout << "The scope of the task: " << rows1 * cols1 * cols2 << endl;

    }
    catch (const std::length_error& e) {
        cerr << "ERROR: " << e.what() << endl;
    }

    return 0;
}

