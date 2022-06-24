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
void incluiV();
void excluir_veiculo(string);
bool verificar_cliente(string);
void inserir_cliente(string);
void excluir_cliente(string);

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
            if (opcao2 == 1)
                incluiV();
            else {
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
            opcao2 = veiculo_ou_cliente();
            cin.ignore();
            if (opcao2 == 1) {
                /* cout << "Digite a placa do veiculo que deseja excluir: ";
                getline(cin, placa);
                existente = verificar_veiculo(placa);
                if (existente == false)
                    excluir_veiculo(placa);
                else
                    cout << "Veiculo ja inexistente!" << endl; */
            } /* else {
                cout << "Digite o nome do cliente que deseja excluir: ";
                getline(cin, nome);
                existente = verificar_cliente(nome);
                if (existente == true)
                    excluir_cliente(nome);
                else
                    cout << "Cliente inexistente!" << endl; */
            //}
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
    cout << "1 - Veiculo" << endl;
    cout << "2 - Cliente" << endl;
    cin >> escolher;
    return escolher;
}

bool verificar_cliente(string nome) {
    ifstream arq("cliente.txt");
    string linha;

    while (getline(arq, linha)) {
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
    ofstream gravar("CLIENTE.TXT", ios::app);

    gravar << nome << endl;
    cout << "Informe o CPF do cliente: ";
    getline(cin, pessoa.cpf);
    gravar << pessoa.cpf << endl;
    cout << "Informe o telefone do cliente: ";
    getline(cin, pessoa.telefone);
    gravar << pessoa.telefone << endl;

    gravar.close();
}

/* void excluir_cliente(string nome) {
    fstream arq("CLIENTE.TXT");
    string linha;

    while (getline(arq, linha)) {
        if (linha == nome) {
            arq.seekp(arq.tellp() - linha.size());
            arq << '\n';
            break;
        }
    }
    arq.close();
} */

void incluiV() { // Quebrar para fazer um verificarVeiculo separado
    int n;
    Veiculo carro;
    fstream arq("FROTA.DAD", ios::binary | ios::in | ios::out | ios::app);
    string procurar;

    cout << "Informe a placa do veiculo: ";
    getline(cin, procurar);

    arq.seekg(0, ios::end);
    n = arq.tellg() / sizeof(Veiculo);
    arq.seekg(0, ios::beg);

    for (int i = 0; i < n; i++) {
        arq.read((char *)&carro, sizeof(Veiculo));
        if (carro.placa == procurar) {
            cout << "Veiculo ja cadastrado!" << endl;
            system("pause");
            return;
        }
    }
    carro.placa = procurar;
    cout << "Informe a marca: ";
    getline(cin, carro.marca);
    cout << "Informe o modelo: ";
    getline(cin, carro.modelo);
    cout << "Informe a categoria (1 - Basico / 2 - Intermediario / 3 - Super): ";
    cin >> carro.categoria;
    cout << "Informe a situacao ((L) Locado / (D) Disponivel): ";
    cin >> carro.situacao;
    carro.quantidade = 0;

    arq.write((char *)(&carro), sizeof(Veiculo));
    arq.close();
}
