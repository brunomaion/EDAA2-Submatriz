// g++ -std=c++17 -O2 buscaSubmatriz.cpp -o buscaSubmatriz
// ./buscaSubmatriz

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Matriz {
    int linhas;
    int colunas;
    vector<vector<int>> dados;
};

void printarMatriz(const Matriz& matriz) {

    for (int i = 0; i < matriz.linhas; i++) {
        for (int j = 0; j < matriz.colunas; j++) {
            cout << matriz.dados[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {

    ifstream arquivo("matriz_teste.txt");
    // LE MATRIZ DO ARQUIVO
    Matriz matriz;
    arquivo >> matriz.linhas >> matriz.colunas;
    matriz.dados.resize(matriz.linhas, vector<int>(matriz.colunas));
    for (int i = 0; i < matriz.linhas; i++) {
        for (int j = 0; j < matriz.colunas; j++) {
            arquivo >> matriz.dados[i][j];
        }
    }
    arquivo.close();
    cout << "Matriz lida:\n";
    printarMatriz(matriz);

    return 0;
}