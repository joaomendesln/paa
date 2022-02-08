# Metaheurística GRASP adaptada para problema do Clique Máximo - Barbosa (2006)

O algoritmo em questão pode ser encontro arquivo `mcp_grasp.cpp`. A sua saída apresenta o tamanho e configuração do clique máximo encontrado, e o tempo para execução em microssegundos.

## Compilação
```sh
gpp mcp_grasp.cpp -o mcp_grasp
```

## Execução
Para a execução, considere `<` e `>` como os operadores, respectivamente, de recebimento e envio de fluxo para um arquivo e `cat file1.txt file2.txt > file3.txt` o comando que concatenará o conteúdo do arquivo `file1.txt` com o do `file2.txt` e armazená-lo no arquivo `file3.txt`:

``` sh
cat instances/instance parameter.txt > test
``` 

``` sh
./mcp_exact < test > result.txt
``` 

`instance` representa o nome de um dos arquivos das instâncias de teste os quais podem ser encontrandos no diretório `instances` e `result.txt`, o nome do arquivo em que ficarão armazenados os resultados do teste.
