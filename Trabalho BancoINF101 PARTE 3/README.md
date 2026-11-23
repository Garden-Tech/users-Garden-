# Banco INF101 — Etapa 3

Sistema de registro e gestão de contas bancárias em C++, com persistência em arquivos de texto.

## Arquivos do programa

- `main.cpp`: código-fonte do sistema.
- `contas.txt`: criado automaticamente para armazenar os dados das contas.
- `movimentacoes.txt`: criado automaticamente para armazenar o histórico de depósitos, saques e transferências.

Os dois arquivos de dados devem ficar na mesma pasta de execução do programa. Na primeira execução, caso ainda não existam, o sistema inicia sem contas e sem movimentações.

## Compilar

Com um compilador C++17:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o banco
```

No Windows, execute o programa gerado na mesma pasta em que deseja manter os arquivos `contas.txt` e `movimentacoes.txt`.

## Formato dos dados

Cada linha de `contas.txt` contém:

```
numeroConta;nomeCliente;cpf;tipoConta;saldo;contaAtiva
```

Cada linha de `movimentacoes.txt` contém:

```
numeroConta;tipoMovimentacao;valor
```

Códigos de movimentação: `D` = depósito/entrada; `S` = saque/saída. Uma transferência gera dois registros: saída na conta de origem e entrada na conta de destino.

## Persistência

Ao iniciar, o sistema carrega os registros dos arquivos para os arrays. Quando há alterações, grava novamente o conteúdo completo dos arrays nos arquivos, preservando também o histórico carregado de execuções anteriores.
