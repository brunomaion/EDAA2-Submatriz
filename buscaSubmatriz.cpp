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

int somasubmatriz(const Matriz& matriz, int linhaInicio, int colunaInicio, int ordem) {
    int soma = 0;
    int linhaFim = linhaInicio + ordem;
    int colunaFim = colunaInicio + ordem;
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


int main(int argc, char* argv[]) {
    int execucao = atoi(argv[1]);

    string pasta = "testes";
    int numeroTestes = lerQuantosTestes(pasta);
    for (int i = 0; i < numeroTestes; i++) {
      float tempoInicio = clock();

      string nomeArquivo = pasta + "/" + to_string(i+2) + ".txt";
      //cout << "\nTestes do arquivo " << nomeArquivo << endl;
      Matriz matriz = atribuirMatriz(nomeArquivo);
      //printarMatriz(matriz);
      int m=matriz.linhas;
      int submatrizes = 0;
      int menorSomaGlobal = somasubmatriz(matriz, 0, 0, m);
      int indiceI, indiceJ = m;
      int ordemMenorSoma = m;
      //cout << "Menor soma global incial: " << menorSomaGlobal << endl;

      for (int ordem=2; ordem<=m; ordem++) { //ESSE FOR VAI ATE O MAX DE MxN
        for (int linhaInicio=0; linhaInicio<=m-ordem; linhaInicio++) {
          for (int colunaInicio=0; colunaInicio<=m-ordem; colunaInicio++) {
            int somaSubmatriz = somasubmatriz(matriz, linhaInicio, colunaInicio, ordem);
            if (somaSubmatriz <= menorSomaGlobal) {
              menorSomaGlobal = somaSubmatriz;
              indiceI = linhaInicio;
              indiceJ = colunaInicio;
              ordemMenorSoma = ordem;
            }
            submatrizes++;
          }
        }
      }
      float tempoFim = clock();
      float tempoTotal = (tempoFim - tempoInicio) / CLOCKS_PER_SEC;

      cout << execucao << "," << m << "," << menorSomaGlobal << "," << indiceI << "," << indiceJ << "," << ordemMenorSoma << "," << submatrizes << "," << tempoTotal << endl;
    }

    return 0;
}