#include <fstream>
#include <iostream>
using namespace std;

// Veículo: código, marca, modelo, placa, categoria, situação, Quantidade de locações
// Cliente: Nome, CPF, telefone
// Locação: Data, CPF, código, data entrega, valor, valor pago
// Verificar se é um carro por locação

typedef struct {
    string codigo, marca, modelo, placa, situacao;
    int qntd_locacoes = 0, categoria;
} Veiculo;

typedef struct {
    string nome, cpf, telefone;
} Cliente;

typedef struct {
    string data, cpf, cod, data_entrega;
    float valor, valor_pago;
} Locacao;

int funcao_opcao();
int veiculo_ou_cliente();
bool verificar_veiculo(string);
bool verificar_cliente(string);
void inserir_veiculo();
void inserir_cliente();

int main() {
    int opcao, escolha;
    bool existente;
    string placa, nomeCliente;

    do {
        opcao = funcao_opcao();

        switch (opcao) {
        case 1:
            escolha = veiculo_ou_cliente();
            if (escolha == 1) {
                cout << "Digite a placa do veiculo que deseja: ";
                getline(cin, placa);
                existente = verificar_veiculo(placa);
                // Incluir veiculo
            } else {
                cout << "Digite o nome do cliente que deseja: ";
                getline(cin, nomeCliente);
                existente = verificar_cliente(nomeCliente);
                // Incluir um veiculo ou cliente
            }
            break;

        case 2:
            // Verificar se veículo existe (placa)
            // Verificar se cliente existe (nome)
            // Excluir veiculo ou cliente
            break;

        case 3:
            // Verificar se cliente existe (nome)
            // Listar veículos disponíveis. Emitir mensagem de erro caso não existir nenhum veículo
            // Locacao de um veiculo
            break;

        case 4:
            // Verificar pelo CPF do cliente e multa caso a data seja posterior a prevista
            // Devolucao de um veiculo
            break;

        case 5:
            // Relatorios
            break;

        case 6:
            cout << "Saindo..." << endl;
            break;
        }
    } while (opcao != 6);

    return 0;
}

int funcao_opcao() {
    int escolha;
    do {
        cout << "Digite a opcao desejada: " << endl;
        cout << "1 - Incluir um veiculo ou cliente" << endl;
        cout << "2 - Excluir veiculo ou cliente" << endl;
        cout << "3 - Locacao de um veiculo" << endl;
        cout << "4 - Devolucao de um veiculo" << endl;
        cout << "5 - Relatorios" << endl;
        cout << "6 - Sair" << endl;
        cin >> escolha;
    } while (escolha < 1 or escolha > 6);
    return escolha;
}

int veiculo_ou_cliente() {
    int escolher;
    cout << "1 - Incluir veiculo" << endl;
    cout << "2 - Incluir cliente" << endl;
    cin >> escolher;
    return escolher;
}

bool verificar_veiculo(string placa) {

}

void inserir_veiculo() {
    ofstream gravar;
    Veiculo carro;

    gravar.open("FROTA.DAT", ios::out | ios::binary);

    cout << "Informe o codigo do veiculo: ";
    getline(cin, carro.codigo);
    cout << "Informe a marca do veiculo: ";
    getline(cin, carro.marca);
    cout << "Informe o modelo do veiculo: ";
    getline(cin, carro.modelo);
    cout << "Informe a placa do veiculo: ";
    getline(cin, carro.placa);
    cin.ignore();
    do {
        cout << "Informe a categoria do veiculo: ";
        cout << "1. Basico" << endl;
        cout << "2. Intermediario" << endl;
        cout << "3. Super" << endl;
        cin >> carro.categoria;
    } while (carro.categoria < 1 or carro.categoria > 3);
    carro.situacao = "disponivel";

    gravar.write((char *)(&carro), sizeof(Veiculo));

    gravar.close();
}

void inserir_cliente() {
    Cliente pessoa;
    ofstream gravar("CLIENTE.TXT");

    cout << "Informe o nome do cliente: ";
    getline(cin, pessoa.nome);
    gravar << pessoa.nome << endl;
    cout << "Informe o CPF do cliente: ";
    getline(cin, pessoa.cpf);
    gravar << pessoa.cpf << endl;
    cout << "Informe o telefone do cliente: ";
    getline(cin, pessoa.telefone);
    gravar << pessoa.telefone << endl;

    gravar.close();
}