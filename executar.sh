#!/bin/bash

# Compilar
echo "Compilando"
g++ buscaSubmatriz.cpp -o buscaSubmatriz
g++ gerarMatrizTeste.cpp -o gerarMatrizTeste
g++ criarCsv.cpp -o criarCsv

n=5
echo "Gerando $n matrizes de teste"
./gerarMatrizTeste $n

echo "Criando CSV"
./criarCsv

execucao=2
echo "Executando buscaSubmatriz"
for i in $(seq 1 $execucao); do
    echo "Execução $i"
    ./buscaSubmatriz $i >> resultados.csv
done


