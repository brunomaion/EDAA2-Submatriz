// g++ -std=c++17 -O2 gerarMatrizTeste.cpp -o gerarMatrizTeste
// ./gerarMatrizTeste 5

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {

    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " <n>" << endl;
        return 1;
    }

    int n = stoi(argv[1]);

    if (n <= 0) {
        cerr << "Erro: n deve ser maior que 0." << endl;
        return 1;
    }

    vector<int> numeros;
    numeros.reserve(n * n);

    for (int i = 1; i <= n * n; i++) {
        numeros.push_back(i);
    }

    random_device rd;
    mt19937 gen(rd());

    shuffle(numeros.begin(), numeros.end(), gen);

    ofstream arquivo("matriz_teste.txt");

    if (!arquivo) {
        cerr << "Erro ao criar matriz_teste.txt" << endl;
        return 1;
    }

    int idx = 0;

    arquivo << n << " " << n << "\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            arquivo << numeros[idx++];
            if (j != n - 1)
                arquivo << " ";
        }
        arquivo << '\n';
    }

    cout << "Matriz " << n << "x" << n << " gerada em matriz_teste.txt" << endl;

    return 0;
}