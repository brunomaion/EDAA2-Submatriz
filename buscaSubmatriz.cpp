// g++ -std=c++17 -O2 buscaSubmatriz.cpp -o buscaSubmatriz
// ./buscaSubmatriz 1

#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <ctime>

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

int somasubmatriz(const Matriz& matriz,int linhaInicio,int colunaInicio,int altura,int largura) {
  int soma = 0;
  for (int i = linhaInicio; i < linhaInicio + altura; i++) {
      for (int j = colunaInicio; j < colunaInicio + largura; j++) {
          soma += matriz.dados[i][j];
      }
  }
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
  namespace fs = std::filesystem;
  string pasta = "testes";
  for (const auto& entry : fs::directory_iterator(pasta)) {
    string nomeArquivo = entry.path().string();
    Matriz matriz = atribuirMatriz(nomeArquivo);
    float tempoInicio = clock();
    int linhas = matriz.linhas;
    int colunas = matriz.colunas;
    int submatrizes = 0;
    // Inicializa com a matriz inteira
    int menorSomaGlobal =
        somasubmatriz(matriz, 0, 0, linhas, colunas);

    int indiceI = 0;
    int indiceJ = 0;

    int alturaMenor = linhas;
    int larguraMenor = colunas;

    // Percorre dimensões possíveis
    for (int altura = 1; altura <= linhas; altura++) {
      for (int largura = 1; largura <= colunas; largura++) {
        // Percorre as posições
        for (int linhaInicio = 0; linhaInicio <= linhas - altura; linhaInicio++) {
          for (int colunaInicio = 0; colunaInicio <= colunas - largura; colunaInicio++) {
            int soma =somasubmatriz(matriz,linhaInicio,colunaInicio,altura,largura);
            if (soma < menorSomaGlobal) {
              menorSomaGlobal = soma;
              indiceI = linhaInicio;
              indiceJ = colunaInicio;
              alturaMenor = altura;
              larguraMenor = largura;
            }
            submatrizes++;
            }
          }
      }
    }

    float tempoFim = clock();

    float tempoTotal = (tempoFim - tempoInicio) / CLOCKS_PER_SEC;

    cout << execucao << ","<< linhas << "," << colunas << "," << menorSomaGlobal << ","<< indiceI << "," << indiceJ << ","<< alturaMenor << "x" << larguraMenor << ","<< submatrizes << ","<< tempoTotal<< endl;
  }

  return 0;
}