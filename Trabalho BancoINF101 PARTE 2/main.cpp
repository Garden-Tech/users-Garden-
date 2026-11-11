#include <cctype>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

// Limites definidos no enunciado da Etapa 2.
const int MAX_CONTAS = 100;
const int MAX_MOVIMENTACOES = 500;

// Vetores paralelos: os dados de uma mesma conta ficam no mesmo indice.
int numeroConta[MAX_CONTAS]{};
string nomeCliente[MAX_CONTAS];
string cpf[MAX_CONTAS];
int tipoConta[MAX_CONTAS]{}; // 1 = Corrente | 2 = Poupanca
double saldo[MAX_CONTAS]{};
bool contaAtiva[MAX_CONTAS]{};
int quantidadeContas = 0;

// Cada posicao representa uma movimentacao de uma conta.
// Deposito = D | Saque = S. Uma transferencia gera um S e um D.
int contaMovimentacao[MAX_MOVIMENTACOES]{};
char tipoMovimentacao[MAX_MOVIMENTACOES]{};
double valorMovimentacao[MAX_MOVIMENTACOES]{};
int quantidadeMovimentacoes = 0;

void limparEntrada() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int lerInteiro(const string& mensagem) {
    int valor;
    while (true) {
        cout << mensagem;
        if (cin >> valor) {
            limparEntrada();
            return valor;
        }

        cout << "Entrada invalida. Digite apenas um numero inteiro.\n";
        limparEntrada();
    }
}

double lerDouble(const string& mensagem) {
    double valor;
    while (true) {
        cout << mensagem;
        if (cin >> valor && std::isfinite(valor)) {
            limparEntrada();
            return valor;
        }

        cout << "Entrada invalida. Digite um valor numerico valido.\n";
        limparEntrada();
    }
}

string lerTextoObrigatorio(const string& mensagem) {
    string texto;
    do {
        cout << mensagem;
        getline(cin, texto);
        if (texto.empty()) {
            cout << "Este campo nao pode ficar vazio.\n";
        }
    } while (texto.empty());

    return texto;
}

string somenteDigitos(const string& texto) {
    string digitos;
    for (char caractere : texto) {
        if (isdigit(static_cast<unsigned char>(caractere))) {
            digitos += caractere;
        }
    }
    return digitos;
}

string lerCpf() {
    string entrada;
    while (true) {
        entrada = lerTextoObrigatorio("CPF (apenas numeros ou formatado): ");
        string cpfLimpo = somenteDigitos(entrada);
        if (cpfLimpo.length() == 11) {
            return cpfLimpo;
        }
        cout << "CPF invalido. Informe exatamente 11 digitos.\n";
    }
}

string descricaoTipo(int tipo) {
    return tipo == 1 ? "Corrente" : "Poupanca";
}

string formatarCpf(const string& cpfSemMascara) {
    return cpfSemMascara.substr(0, 3) + "." + cpfSemMascara.substr(3, 3) + "." +
           cpfSemMascara.substr(6, 3) + "-" + cpfSemMascara.substr(9, 2);
}

// Retorna o indice da conta encontrada ou -1 quando ela nao existe.
int localizarConta(int numero) {
    for (int i = 0; i < quantidadeContas; i++) {
        if (numeroConta[i] == numero) {
            return i;
        }
    }
    return -1;
}

int solicitarContaExistente() {
    if (quantidadeContas == 0) {
        cout << "Nenhuma conta foi cadastrada ainda.\n";
        return -1;
    }

    int numero = lerInteiro("Numero da conta: ");
    int indice = localizarConta(numero);
    if (indice == -1) {
        cout << "Conta nao encontrada.\n";
    }
    return indice;
}

bool contaPodeMovimentar(int indice) {
    if (indice == -1) {
        return false;
    }
    if (!contaAtiva[indice]) {
        cout << "Operacao indisponivel: a conta esta inativa.\n";
        return false;
    }
    return true;
}

bool haEspacoMovimentacoes(int quantidadeNecessaria) {
    if (quantidadeMovimentacoes + quantidadeNecessaria > MAX_MOVIMENTACOES) {
        cout << "Limite de " << MAX_MOVIMENTACOES
             << " movimentacoes atingido. Operacao nao realizada.\n";
        return false;
    }
    return true;
}

// Registra uma movimentacao. A capacidade deve ser verificada antes da chamada.
void registrarMovimentacao(int numero, char tipo, double valor) {
    contaMovimentacao[quantidadeMovimentacoes] = numero;
    tipoMovimentacao[quantidadeMovimentacoes] = tipo;
    valorMovimentacao[quantidadeMovimentacoes] = valor;
    quantidadeMovimentacoes++;
}

void exibirCabecalho() {
    cout << "\n========================================\n";
    cout << "          BANCO INF101 - P2\n";
    cout << "========================================\n";
}

void cadastrarConta() {
    if (quantidadeContas == MAX_CONTAS) {
        cout << "Limite de " << MAX_CONTAS << " contas atingido.\n";
        return;
    }

    cout << "\n--- Cadastro de conta ---\n";
    int novoNumero;
    do {
        novoNumero = lerInteiro("Numero da conta: ");
        if (novoNumero <= 0) {
            cout << "O numero da conta deve ser maior que zero.\n";
        } else if (localizarConta(novoNumero) != -1) {
            cout << "Ja existe uma conta com esse numero.\n";
            novoNumero = 0;
        }
    } while (novoNumero <= 0);

    string novoNome = lerTextoObrigatorio("Nome do titular: ");
    string novoCpf = lerCpf();

    int novoTipo;
    do {
        novoTipo = lerInteiro("Tipo (1 - Corrente | 2 - Poupanca): ");
        if (novoTipo != 1 && novoTipo != 2) {
            cout << "Tipo invalido. Escolha 1 ou 2.\n";
        }
    } while (novoTipo != 1 && novoTipo != 2);

    double saldoInicial;
    do {
        saldoInicial = lerDouble("Saldo inicial: R$ ");
        if (saldoInicial < 0) {
            cout << "O saldo inicial nao pode ser negativo.\n";
        }
    } while (saldoInicial < 0);

    numeroConta[quantidadeContas] = novoNumero;
    nomeCliente[quantidadeContas] = novoNome;
    cpf[quantidadeContas] = novoCpf;
    tipoConta[quantidadeContas] = novoTipo;
    saldo[quantidadeContas] = saldoInicial;
    contaAtiva[quantidadeContas] = true;
    quantidadeContas++;

    cout << "Conta cadastrada e ativada com sucesso.\n";
}

void listarContas() {
    cout << "\n--- Contas cadastradas ---\n";
    if (quantidadeContas == 0) {
        cout << "Nenhuma conta foi cadastrada ainda.\n";
        return;
    }

    cout << fixed << setprecision(2);
    for (int i = 0; i < quantidadeContas; i++) {
        cout << "\nConta: " << numeroConta[i] << "\n";
        cout << "Titular: " << nomeCliente[i] << "\n";
        cout << "Tipo: " << descricaoTipo(tipoConta[i]) << "\n";
        cout << "Saldo: R$ " << saldo[i] << "\n";
        cout << "Situacao: " << (contaAtiva[i] ? "Ativa" : "Inativa") << "\n";
    }
}

void consultarConta() {
    cout << "\n--- Consulta de conta ---\n";
    int indice = solicitarContaExistente();
    if (indice == -1) return;

    cout << fixed << setprecision(2);
    cout << "Numero: " << numeroConta[indice] << "\n";
    cout << "Titular: " << nomeCliente[indice] << "\n";
    cout << "CPF: " << formatarCpf(cpf[indice]) << "\n";
    cout << "Tipo: " << descricaoTipo(tipoConta[indice]) << "\n";
    cout << "Saldo: R$ " << saldo[indice] << "\n";
    cout << "Situacao: " << (contaAtiva[indice] ? "Ativa" : "Inativa") << "\n";
}

void verificarSaldo() {
    cout << "\n--- Verificacao de saldo ---\n";
    int indice = solicitarContaExistente();
    if (!contaPodeMovimentar(indice)) return;

    cout << fixed << setprecision(2);
    cout << "Saldo da conta " << numeroConta[indice] << ": R$ " << saldo[indice] << "\n";
}

void depositar() {
    cout << "\n--- Deposito ---\n";
    int indice = solicitarContaExistente();
    if (!contaPodeMovimentar(indice)) return;
    if (!haEspacoMovimentacoes(1)) return;

    double valor;
    do {
        valor = lerDouble("Valor do deposito: R$ ");
        if (valor <= 0) {
            cout << "O valor do deposito deve ser maior que zero.\n";
        }
    } while (valor <= 0);

    saldo[indice] += valor;
    registrarMovimentacao(numeroConta[indice], 'D', valor);

    cout << fixed << setprecision(2);
    cout << "Deposito realizado com sucesso. Novo saldo: R$ " << saldo[indice] << "\n";
}

void sacar() {
    cout << "\n--- Saque ---\n";
    int indice = solicitarContaExistente();
    if (!contaPodeMovimentar(indice)) return;

    double valor;
    do {
        valor = lerDouble("Valor do saque: R$ ");
        if (valor <= 0) {
            cout << "O valor do saque deve ser maior que zero.\n";
        }
    } while (valor <= 0);

    if (valor > saldo[indice]) {
        cout << "Saldo insuficiente. Saque nao realizado.\n";
        return;
    }
    if (!haEspacoMovimentacoes(1)) return;

    saldo[indice] -= valor;
    registrarMovimentacao(numeroConta[indice], 'S', valor);

    cout << fixed << setprecision(2);
    cout << "Saque realizado com sucesso. Novo saldo: R$ " << saldo[indice] << "\n";
}

void transferir() {
    cout << "\n--- Transferencia ---\n";
    if (quantidadeContas < 2) {
        cout << "E necessario ter pelo menos duas contas cadastradas.\n";
        return;
    }

    cout << "Conta de origem:\n";
    int indiceOrigem = solicitarContaExistente();
    if (!contaPodeMovimentar(indiceOrigem)) return;

    cout << "Conta de destino:\n";
    int indiceDestino = solicitarContaExistente();
    if (!contaPodeMovimentar(indiceDestino)) return;

    if (indiceOrigem == indiceDestino) {
        cout << "A conta de origem e a de destino devem ser diferentes.\n";
        return;
    }

    double valor;
    do {
        valor = lerDouble("Valor da transferencia: R$ ");
        if (valor <= 0) {
            cout << "O valor da transferencia deve ser maior que zero.\n";
        }
    } while (valor <= 0);

    if (valor > saldo[indiceOrigem]) {
        cout << "Saldo insuficiente na conta de origem. Transferencia nao realizada.\n";
        return;
    }

    // A transferencia precisa de dois espacos: uma saida e uma entrada.
    // A capacidade e verificada antes de alterar qualquer saldo.
    if (!haEspacoMovimentacoes(2)) return;

    saldo[indiceOrigem] -= valor;
    saldo[indiceDestino] += valor;

    registrarMovimentacao(numeroConta[indiceOrigem], 'S', valor);
    registrarMovimentacao(numeroConta[indiceDestino], 'D', valor);

    cout << fixed << setprecision(2);
    cout << "Transferencia realizada com sucesso.\n";
    cout << "Novo saldo da conta " << numeroConta[indiceOrigem]
         << ": R$ " << saldo[indiceOrigem] << "\n";
    cout << "Novo saldo da conta " << numeroConta[indiceDestino]
         << ": R$ " << saldo[indiceDestino] << "\n";
}

void exibirExtrato() {
    cout << "\n--- Extrato da conta ---\n";
    int indice = solicitarContaExistente();
    if (indice == -1) return;

    cout << "Extrato - Conta " << numeroConta[indice]
         << " | Titular: " << nomeCliente[indice] << "\n";
    cout << fixed << setprecision(2);

    bool encontrouMovimentacao = false;
    double totalEntradas = 0.0;
    double totalSaidas = 0.0;

    for (int i = 0; i < quantidadeMovimentacoes; i++) {
        if (contaMovimentacao[i] == numeroConta[indice]) {
            encontrouMovimentacao = true;
            if (tipoMovimentacao[i] == 'D') {
                cout << "Deposito/Entrada: + R$ " << valorMovimentacao[i] << "\n";
                totalEntradas += valorMovimentacao[i];
            } else if (tipoMovimentacao[i] == 'S') {
                cout << "Saque/Saida: - R$ " << valorMovimentacao[i] << "\n";
                totalSaidas += valorMovimentacao[i];
            }
        }
    }

    if (!encontrouMovimentacao) {
        cout << "Nenhuma movimentacao registrada para esta conta.\n";
    }

    cout << "Total de entradas: R$ " << totalEntradas << "\n";
    cout << "Total de saidas: R$ " << totalSaidas << "\n";
    cout << "Saldo atual: R$ " << saldo[indice] << "\n";
}

void alterarTipoConta() {
    cout << "\n--- Alteracao de tipo de conta ---\n";
    int indice = solicitarContaExistente();
    if (!contaPodeMovimentar(indice)) return;

    int novoTipo;
    do {
        novoTipo = lerInteiro("Novo tipo (1 - Corrente | 2 - Poupanca): ");
        if (novoTipo != 1 && novoTipo != 2) {
            cout << "Tipo invalido. Escolha 1 ou 2.\n";
        }
    } while (novoTipo != 1 && novoTipo != 2);

    tipoConta[indice] = novoTipo;
    cout << "Tipo da conta alterado para " << descricaoTipo(novoTipo) << ".\n";
}

void alternarStatusConta() {
    cout << "\n--- Ativacao/Desativacao de conta ---\n";
    int indice = solicitarContaExistente();
    if (indice == -1) return;

    contaAtiva[indice] = !contaAtiva[indice];
    cout << "Conta " << (contaAtiva[indice] ? "ativada" : "desativada")
         << " com sucesso.\n";
}

void exibirMenu() {
    exibirCabecalho();
    cout << "1  - Cadastrar conta\n";
    cout << "2  - Listar contas\n";
    cout << "3  - Consultar conta\n";
    cout << "4  - Verificar saldo\n";
    cout << "5  - Realizar deposito\n";
    cout << "6  - Realizar saque\n";
    cout << "7  - Realizar transferencia\n";
    cout << "8  - Exibir extrato\n";
    cout << "9  - Alterar tipo da conta\n";
    cout << "10 - Ativar/Desativar conta\n";
    cout << "11 - Sair\n";
}

int main() {
    int opcao;

    do {
        exibirMenu();
        opcao = lerInteiro("Escolha uma opcao: ");

        switch (opcao) {
            case 1: cadastrarConta(); break;
            case 2: listarContas(); break;
            case 3: consultarConta(); break;
            case 4: verificarSaldo(); break;
            case 5: depositar(); break;
            case 6: sacar(); break;
            case 7: transferir(); break;
            case 8: exibirExtrato(); break;
            case 9: alterarTipoConta(); break;
            case 10: alternarStatusConta(); break;
            case 11: cout << "Obrigado por utilizar o Banco INF101. Ate logo!\n"; break;
            default: cout << "Opcao invalida. Escolha uma opcao de 1 a 11.\n";
        }
    } while (opcao != 11);

    return 0;
}
