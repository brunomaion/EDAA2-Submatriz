// g++ -std=c++17 -O2 buscaSubmatriz2.cpp -o buscaSubmatriz2
// ./buscaSubmatriz2 1

#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <ctime>
#include <climits>

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

vector<vector<int>> construirPrefixos(const Matriz& matriz) {

    vector<vector<int>> pre(
        matriz.linhas + 1,
        vector<int>(matriz.colunas + 1, 0)
    );

    for (int i = 1; i <= matriz.linhas; i++) {
        for (int j = 1; j <= matriz.colunas; j++) {

            pre[i][j] =
                matriz.dados[i - 1][j - 1]
                + pre[i - 1][j]
                + pre[i][j - 1]
                - pre[i - 1][j - 1];
        }
    }

    return pre;
}

int somaSubmatriz(
    const vector<vector<int>>& pre,
    int linhaInicio,
    int colunaInicio,
    int altura,
    int largura) {

    int r1 = linhaInicio;
    int c1 = colunaInicio;
    int r2 = linhaInicio + altura - 1;
    int c2 = colunaInicio + largura - 1;

    return pre[r2 + 1][c2 + 1]
         - pre[r1][c2 + 1]
         - pre[r2 + 1][c1]
         + pre[r1][c1];
}

int main(int argc, char* argv[]) {

    int execucao = atoi(argv[1]);

    namespace fs = std::filesystem;

    string pasta = "testes";

  for (const auto& entry : fs::directory_iterator(pasta)) {

      string nomeArquivo = entry.path().string();

      Matriz matriz = atribuirMatriz(nomeArquivo);

      float tempoInicio = clock();

      vector<vector<int>> prefixos = construirPrefixos(matriz);

      int linhas = matriz.linhas;
      int colunas = matriz.colunas;

      int submatrizes = 0;

      int menorSomaGlobal =
          somaSubmatriz(prefixos, 0, 0, linhas, colunas);

      int indiceI = 0;
      int indiceJ = 0;

      int alturaMenor = linhas;
      int larguraMenor = colunas;

      for (int altura = 1; altura <= linhas; altura++) {

          for (int largura = 1; largura <= colunas; largura++) {

              // Percorre todas as posições possíveis
              for (int linhaInicio = 0;
                    linhaInicio <= linhas - altura;
                    linhaInicio++) {

                  for (int colunaInicio = 0;
                        colunaInicio <= colunas - largura;
                        colunaInicio++) {

                      int soma = somaSubmatriz(
                          prefixos,
                          linhaInicio,
                          colunaInicio,
                          altura,
                          largura
                      );

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

      float tempoTotal =
          (tempoFim - tempoInicio) / CLOCKS_PER_SEC;

  cout
      << execucao << ","
      << linhas << ","
      << colunas << ","
      << menorSomaGlobal << ","
      << indiceI << ","
      << indiceJ << ","
      << alturaMenor << "x" << larguraMenor << ","
      << submatrizes << ","
      << tempoTotal
      << endl;
  }

  return 0;
}