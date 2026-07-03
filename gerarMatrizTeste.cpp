// g++ -std=c++17 -O2 gerarMatrizTeste.cpp -o gerarMatrizTeste
// ./gerarMatrizTeste 5

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

void criarMatrizTxt(int n) {

  vector<int> numeros;
  for (int i = 1; i <= n * n; i++)
      numeros.push_back(i);

  random_device rd;
  mt19937 gen(rd());
  shuffle(numeros.begin(), numeros.end(), gen);
    string nomeArquivo = "testes/" + to_string(n) + ".txt";
  ofstream arquivo(nomeArquivo);

  arquivo << n << " " << n << "\n";
  int k = 0;
  for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {

          int boolean = rand() % 2;
          if (boolean == 0)
              arquivo << numeros[k++];
          else
              arquivo << -numeros[k++];
          if (j != n - 1)
              arquivo << " ";
      }
      arquivo << "\n";
  }
  arquivo.close();
  cout << nomeArquivo << " criado com sucesso." << endl;
}

int main(int argc, char* argv[]) {
  int numeroTestes = atoi(argv[1]);
  for (int i = 2; i <= numeroTestes; i++) {
    criarMatrizTxt(i);
  }
  return 0;
}