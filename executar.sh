#!/bin/bash

# Compilar
echo "Compilando"
g++ buscaSubmatriz.cpp -o buscaSubmatriz
g++ buscaSubmatriz2.cpp -o buscaSubmatriz2
g++ gerarMatrizTeste.cpp -o gerarMatrizTeste
g++ criarCsv.cpp -o criarCsv

n=80
echo "Gerando $n matrizes de teste"
./gerarMatrizTeste $n

echo "Criando CSV"
./criarCsv

execucao=10
echo "Executando buscaSubmatriz"
for i in $(seq 1 $execucao); do
    echo "Execução $i"
    ./buscaSubmatriz $i >> resultados.csv
    ./buscaSubmatriz2 $i >> resultados2.csv
done


