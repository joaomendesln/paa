# Heurístia E1 de Johnson

A heurística de E1 Johnson para o clique máximo pode ser encontrada no arquivo `mcp_greedy.cpp`. A sua saída apresenta o tamanho e configuração do clique máximo encontrado, e o tempo para execução em microssegundos.

A fim de checar se o clique resultado do algoritmo é realmente um subgrafo completo, foi implementado o código `mcp_greedy_checker.cpp`, cuja saída é "S" se o clique é um subgrafo completo e "N" caso contrário.

## Compilação
```sh
gpp mcp_greedy.cpp -o mcp_greedy
```

## Execução
Para a execução, considere `<` e `>` como os operadores, respectivamente, de recebimento e envio de fluxo para um arquivo:

``` sh
./mcp_greedy < instances/instance > result.txt
``` 

`instance` representa o nome de um dos arquivos das instâncias de teste os quais podem ser encontrandos no diretório `instances` e `result.txt`, o nome do arquivo em que ficarão armazenados os resultados do teste.
