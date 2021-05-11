# Projeto 2 de Análise e Síntese de Algoritmos

## Descrição do problema
Em computação distribuída, o problema de atribuição de um conjunto de processos a um conjunto de processadores é um problema complexo, mesmo quando considerados apenas dois processadores, devido a overheads computacionais, como por exemplo: custos de execução de cada processo em cada processador (este pode ter diferentes capacidades - velocidade, cache, etc); e custos de comunicação entre vários processos.

Considere que pretende correr um programa P = {p1, ..., pn}, constituído por um conjunto de n processos. Considere ainda que é conhecido o custo Xi de correr cada processo pi no processador X, e o custo Yi, de correr cada processo pi no processador Y.

Considere adicionalmente o custo de comunicação cij entre dois processos pi e pj, sempre que pi != pj. Assuma que não há custo de comunicação (cij = 0) entre processos que corram num mesmo processador.

Seja Px contido em P o conjunto de processos que correm no processador X, e Py contido em P o conjunto de processos que correm no processador Y, tal que Px interseção com Py seja igual a conjunto vazio, proponha e implemente um algoritmo eficiene que minimize o custo total de execução do programa P, sem testar todas as combinações de atribuições possíveis.

min(sum(Xi) + sum(Yi) + sum(cij))

## Links
https://stackoverflow.com/questions/67039746/dynamic-programming-assigning-tasks-to-different-computers
