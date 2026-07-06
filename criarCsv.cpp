// g++ criarCsv.cpp -o criarCsv
// ./criarCsv

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main() {
  string nomeCsv = "resultados.csv";
  string nomeCsv2 = "resultados2.csv";

  vector<string> colunas = {
    "Execucao",
    "Linha",
    "Coluna",
    "Menor Soma Global",
    "IndiceI",
    "IndiceJ",
    "alturaMenorXlarguraMenor",
    "Submatrizes Percorridas",
    "Tempo Total (s)"
  };
  ofstream arquivo(nomeCsv);
  ofstream arquivo2(nomeCsv2);
  for (size_t i = 0; i < colunas.size(); i++) {
      arquivo << colunas[i];
      arquivo2 << colunas[i];
      if (i < colunas.size() - 1)
          arquivo << ",";
          arquivo2 << ",";
  }
  arquivo << "\n";
  arquivo.close();
  arquivo2 << "\n";
  arquivo2.close();
  cout << "Arquivo '" << nomeCsv << "' criado." << endl;
  cout << "Arquivo '" << nomeCsv2 << "' criado." << endl;
  return 0;
}