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

int somasubmatriz(const Matriz& matriz, int linhaInicio, int linhaFim, int colunaInicio, int colunaFim) {
    int soma = 0;
    for (int i = linhaInicio; i < linhaFim; i++) {
        for (int j = colunaInicio; j < colunaFim; j++) {
          int elemento = matriz.dados[i][j];
          //printf("Elemento [%d][%d] = %d\n", i, j, elemento);
          soma += elemento;
        }
    }
    //printf("Soma da submatriz: %d\n", soma);
    return soma;
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

    
    int intervalo = 2;
    int linhaInicio = 0;
    int linhaFim = linhaInicio + intervalo;
    int colunaInicio = 0;
    int colunaFim = colunaInicio + intervalo;
    int soma = somasubmatriz(matriz, linhaInicio, linhaFim, colunaInicio, colunaFim);

    cout << "Soma da submatriz de tamanho " << intervalo << "x" << intervalo << " = " << soma << "\n";

    return 0;
}