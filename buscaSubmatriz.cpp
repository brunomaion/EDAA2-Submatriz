// g++ -std=c++17 -O2 buscaSubmatriz.cpp -o buscaSubmatriz
// ./buscaSubmatriz

#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

using namespace std;

struct Matriz {
    int linhas;
    int colunas;
    vector<vector<int>> dados;
};

void printarArqSubPasta(string nomePasta) {
    namespace fs = std::filesystem;
    for (const auto& entry : fs::directory_iterator(nomePasta)) {
      if (entry.is_regular_file()) {
          cout << entry.path().filename().string() << endl;
      }
    }
}

void printarMatriz(const Matriz& matriz) {

    for (int i = 0; i < matriz.linhas; i++) {
        for (int j = 0; j < matriz.colunas; j++) {
            cout << matriz.dados[i][j] << " ";
        }
        cout << endl;
    }
}

int somasubmatriz(const Matriz& matriz, int linhaInicio, int colunaInicio, int dimensao) {
    int soma = 0;
    int linhaFim = linhaInicio + dimensao;
    int colunaFim = colunaInicio + dimensao;
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

int lerQuantosTestes(string pasta) {
  namespace fs = std::filesystem;
  int contador = 0;
  for (const auto& entry : fs::directory_iterator(pasta)) {
      if (entry.is_regular_file()) {
          contador++;
      }
  }
  return contador;
}

Matriz atribuirMatriz(string nomeArquivo) {
  Matriz matriz;
  ifstream arquivo(nomeArquivo);
  arquivo >> matriz.linhas >> matriz.colunas;
  matriz.dados.resize(matriz.linhas, vector<int>(matriz.colunas));
  for (int i = 0; i < matriz.linhas; i++) {
      for (int j = 0; j < matriz.colunas; j++) {
          arquivo >> matriz.dados[i][j];
      }
    }
  arquivo.close();
  return matriz;
}


int main() {

    //string nome = ("testes/5.txt");
    //Matriz matriz = atribuirMatriz(nome);
    //printarMatriz(matriz);
    string pasta = "testes";
    int numeroTestes = lerQuantosTestes(pasta);
    //cout << "Número de testes " << numeroTestes << endl;

    for (int i = 0; i < numeroTestes; i++) {
      string nomeArquivo = pasta + "/" + to_string(i+2) + ".txt";
      cout << "\nTestes do arquivo " << nomeArquivo << endl;
      Matriz matriz = atribuirMatriz(nomeArquivo);
      //printarMatriz(matriz);
      int m=matriz.linhas;
      int submatrizes = 0;
      int menorSomaGlobal = somasubmatriz(matriz, 0, 0, m);
      int indiceI, indiceJ = m;
      int dimensaoMenorSoma = m;
      cout << "Menor soma global incial: " << menorSomaGlobal << endl;

      for (int dimensao=2; dimensao<=m; dimensao++) { //ESSE FOR VAI ATE O MAX DE MxN
        for (int linhaInicio=0; linhaInicio<=m-dimensao; linhaInicio++) {
          for (int colunaInicio=0; colunaInicio<=m-dimensao; colunaInicio++) {
            int somaSubmatriz = somasubmatriz(matriz, linhaInicio, colunaInicio, dimensao);
            if (somaSubmatriz <= menorSomaGlobal) {
              menorSomaGlobal = somaSubmatriz;
              indiceI = linhaInicio;
              indiceJ = colunaInicio;
              dimensaoMenorSoma = dimensao;
            }
            submatrizes++;
          }
        }
      }
      cout << "Menor soma global final: " << menorSomaGlobal << endl;
      cout << "Número de submatrizes percorridas: " << submatrizes << endl;
    }

    return 0;
}