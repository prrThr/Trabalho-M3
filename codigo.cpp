#include <fstream>
#include <iostream>
using namespace std;

typedef struct {
    string codigo, marca, modelo, placa, situacao;
    int quantidade = 0, categoria;
} Veiculo;

typedef struct {
    string nome, cpf, telefone;
} Cliente;

typedef struct {
    string cpf, data, dataE, codigo;
    float valor, valorP;
} Locacao;

int funcao_opcao();
int veiculo_ou_cliente();
bool verificar_veiculo(string);
void inserir_veiculo(string);
bool verificar_cliente(string);
void inserir_cliente(string);

int main() {
    bool existente;
    int opcao, opcao2;
    string placa, nome;

    do {
        opcao = funcao_opcao();

        switch (opcao) {
        case 1:
            opcao2 = veiculo_ou_cliente();
            cin.ignore();
            if (opcao2 == 1) {
                cout << "Digite a placa do veiculo que deseja inserir: ";
                getline(cin, placa);
                existente = verificar_veiculo(placa);
                if (existente == false)
                    inserir_veiculo(placa);
                else
                    cout << "veiculo ja cadastrado!" << endl;
            } else {
                cout << "Digite o nome do cliente que deseja inserir: ";
                getline(cin, nome);
                existente = verificar_cliente(nome);
                if (existente == false)
                    inserir_cliente(nome);
                else
                    cout << "Cliente ja cadastrado!" << endl;
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
    ifstream arq("FROTA.DAD", ios::in | ios::binary);
    Veiculo carro;

    while (arq.read((char *)(&carro), sizeof(Veiculo))) {
        if (carro.placa == placa)
            arq.close();
        return true;
    }
    arq.close();
    return false;
}

void inserir_veiculo(string placa) {
    ofstream gravar;
    Veiculo carro;

    gravar.open("FROTA.DAT", ios::out | ios::binary);

    cout << "Informe o codigo do veiculo: ";
    getline(cin, carro.codigo);
    cout << "Informe a marca do veiculo: ";
    getline(cin, carro.marca);
    cout << "Informe o modelo do veiculo: ";
    getline(cin, carro.modelo);
    carro.placa = placa;
    do {
        cout << "Informe a categoria do veiculo: " << endl;
        cout << "1. Basico" << endl;
        cout << "2. Intermediario" << endl;
        cout << "3. Super" << endl;
        cin >> carro.categoria;
    } while (carro.categoria < 1 or carro.categoria > 3);
    carro.situacao = "disponivel";

    gravar.write((char *)(&carro), sizeof(Veiculo));
    gravar.close();
}

bool verificar_cliente(string nome) {
    ifstream arq("cliente.txt");
    string linha;

    while (getline(arq, linha)) {
        cout << linha << endl;
        if (linha == nome) {
            arq.close();
            return true;
        }
    }

    arq.close();
    return false;
}

void inserir_cliente(string nome) {
    Cliente pessoa;
    ofstream gravar("CLIENTE.TXT");

    gravar << nome << endl;
    cout << "Informe o CPF do cliente: ";
    getline(cin, pessoa.cpf);
    gravar << pessoa.cpf << endl;
    cout << "Informe o telefone do cliente: ";
    getline(cin, pessoa.telefone);
    gravar << pessoa.telefone << endl;

    gravar.close();
}
