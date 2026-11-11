# Trabalho BancoINF101 PARTE 2

Projeto desenvolvido para a disciplina INF101 – Programação de Computadores I, referente à Etapa 2 do sistema de registro e gestão de contas bancárias.

## Conteúdo

- `main.cpp`: implementação em C++ do sistema bancário.
- `BancoINF101-Etapa2.zip`: pacote do projeto com o código-fonte e este README.
- `Enunciado_Etapa2.pdf`: documento com os requisitos da atividade.

## Funcionalidades

- Cadastro e listagem de até 100 contas.
- Consulta de conta pelo número.
- Depósitos e saques com registro no histórico.
- Transferências entre contas, registradas como saída e entrada.
- Extrato individual com movimentações, entradas, saídas e saldo atual.
- Histórico limitado a 500 registros, mantido em memória.

## Compilação

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o banco
```

Os dados permanecem apenas na memória durante a execução, conforme o escopo da Etapa 2.
