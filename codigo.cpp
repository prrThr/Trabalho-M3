#include <fstream>
#include <iostream>
using namespace std;

typedef struct {
    string nome, cpf, telefone;
} Cliente;

typedef struct {
    string codigo, marca, modelo, placa;
    char situacao;
    int quantidade = 0, categoria;
} Veiculo;

typedef struct {
    string cpf, codigo;
    int dia, mes, diaE, mesE;
    float valor, valorP;
} Locacao;

int funcao_opcao();
int veiculo_ou_cliente();

void incluir_veiculo(); // verifica junto
void excluir_veiculo();

bool verificar_cliente(string);
void inserir_cliente(string);
void excluir_cliente(string);

bool mostrar_categoria(int);
void locacao(string, string, int);

int main() {
    bool existente, existente2;
    int opcao, opcao2, opcao3;
    string placa, nome;
    Veiculo carro;

    do {
        opcao = funcao_opcao();

        switch (opcao) {
        case 1:
            opcao2 = veiculo_ou_cliente(); // fazer do-while quando terminar
            cin.ignore();
            if (opcao2 == 1)
                incluir_veiculo();
            else {
                cout << "Digite o nome do cliente que deseja inserir: ";
                getline(cin, nome);
                existente = verificar_cliente(nome);
                if (!existente)
                    inserir_cliente(nome);
                else
                    cout << "Cliente ja cadastrado!" << endl;
            }
            break;

        case 2:
            opcao2 = veiculo_ou_cliente();
            cin.ignore();
            if (opcao2 == 1) {
                excluir_veiculo();
            } else {
                cout << "Digite o nome do cliente que deseja excluir: ";
                getline(cin, nome);
                existente = verificar_cliente(nome);
                if (existente == true)
                    excluir_cliente(nome);
                else
                    cout << "Cliente inexistente!" << endl;
            }
            // Excluir veiculo ou cliente
            break;

        case 3:
            cout << "Digite o nome do cliente: ";
            cin.ignore();
            getline(cin, nome);
            existente = verificar_cliente(nome);
            if (existente == false) {
                cout << "Cliente inexistente! Retornando" << endl;
                break;
            } else {
                do {
                    cout << "Qual a categoria do veiculo que voce deseja fazer a locacao?" << endl;
                    cout << "Categoria 1: Basica (R$10 por dia)" << endl;
                    cout << "Categoria 2: Intermediaria (R$20 por dia)" << endl;
                    cout << "Categoria 3: Super (R$30 por dia)" << endl;
                    cin >> opcao3;
                } while (opcao3 < 1 or opcao3 > 3);
                existente2 = mostrar_categoria(opcao3);
                if (existente2 == true) {
                    cout << "Informe a placa do veiculo que deseja lotar: ";
                    cin >> placa;
                    locacao(placa, nome, opcao3);
                }
            }
            break;

        case 4:
            // Verificar pelo CPF do cliente e multa caso a data seja posterior a prevista
            // Devolucao de um veiculo
            break;

        case 5:
            do {
                cout << "1.relatorio A: Listagem dos veiculos da frota" << endl;
                cout << "2.Relatorio B: Listagem dos clientes" << endl;
                cout << "3.Relatorio C: listagem das locacoes" << endl;
                cout << "4.Relatorio D: Listagem dos veiculos a serem devolvidos hoje" << endl;
                cin >> opcao2;
            } while (opcao2 < 1 or opcao2 > 4);

            switch (opcao2) {
            case 1:
                // relatorioA();
                break;
            case 2:
                // relatorioB();
                break;
            case 3:
                // relatorioC():
                break;
            case 4:
                // relatorioD();
                break;
            }
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

void incluir_veiculo() {
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
        cout << carro.placa << endl;
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

void excluir_veiculo() { // NÃO ESTÁ 100% CERTO
    int n;
    Veiculo carro;
    ifstream arq("FROTA.DAD", ios::binary | ios::in);
    ofstream temp("temp.DAD", ios::binary | ios::out | ios::app);
    string procurar;

    cout << "Informe a placa do veiculo: ";
    getline(cin, procurar);

    arq.seekg(0, ios::end);
    n = arq.tellg() / sizeof(Veiculo);
    arq.seekg(0, ios::beg);

    for (int i = 0; i < n; i++) {
        arq.read((char *)&carro, sizeof(Veiculo));
        cout << carro.placa << endl;
        if (carro.placa != procurar) {
            temp.write((char *)(&carro), sizeof(Veiculo));
        } else
            cout << "Excluindo veiculo..." << endl;
    }
    arq.close();
    temp.close();

    remove("FROTA.DAD");
    rename("temp.DAD", "FROTA.DAD");
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

void excluir_cliente(string nome) {
    string line;
    ifstream fin;
    fin.open("CLIENTE.TXT");
    ofstream temp;
    temp.open("temp.txt");

    while (getline(fin, line)) {
        if (line == nome) {
            getline(fin, line);
            getline(fin, line);
        } else
            temp << line << endl;
    }

    temp.close();
    fin.close();
    remove("CLIENTE.TXT");
    rename("temp.txt", "CLIENTE.TXT");
}

bool mostrar_categoria(int categoria) {
    ifstream arq("FROTA.DAD", ios::binary);
    Veiculo carro;
    bool mostrar;

    cout << "Mostrando veiculos disponiveis por categoria: " << endl;
    while (arq.read((char *)(&carro), sizeof(Veiculo))) {
        cout << carro.categoria << endl;
        cout << categoria << endl;
        cout << carro.situacao << endl;
        if (carro.categoria == categoria and carro.situacao == 'D') {
            mostrar = true;
            cout << "Codigo: " << carro.codigo << endl;
            cout << "Marca: " << carro.marca << endl;
            cout << "Modelo: " << carro.modelo << endl;
            cout << "Placa: " << carro.placa << endl;
        }
    }
    if (mostrar == false)
        cout << "nenhum veiculo disponivel nessa categoria..." << endl;
    arq.close();
    return mostrar;
}

void locacao(string placa, string nome, int categoria) {
    ofstream gravar;
    fstream arq("FROTA.DAD", ios::ate | ios::binary); // abre e vai pro final !!!
    ifstream arq2;
    string linha;
    Locacao carro;
    Veiculo carro2;
    int dias = 0;

    gravar.open("LOTACAO.DAD");
    arq2.open("CLIENTE.TXT");

    while (!arq2.eof()) {
        getline(arq2, linha);
        if (linha == nome) {
            getline(arq, linha);
            carro.cpf = linha;
            break;
        }
    }
    arq.seekg(0, ios::beg); // vai pro início
    do {
        arq.read((char *)(&carro2), sizeof(Veiculo));
        if (carro2.placa == placa) {
            carro.codigo = carro2.codigo;
            carro2.quantidade++;
            arq.seekp(-sizeof(Veiculo), ios::cur);
            arq.write((char *)(&carro2), sizeof(Veiculo));
            break;
        }
    } while (!arq.eof());

    cout << "Informe o dia e o mes da locacao: ";
    cin >> carro.dia >> carro.mes;
    cout << "Informe o dia e o mes da devolucao: ";
    cin >> carro.diaE >> carro.mesE;

    if (carro.mes == carro.mesE)
        dias = carro.mesE - carro.mes;
    else if (carro.mes < carro.mesE)
        dias = (30 - carro.dia) + carro.diaE;

    carro.valor = (10 * categoria) * dias;
    cout << "Valor a ser pago: R$" << carro.valor << ",00" << endl;

    arq.write((char *)(&carro), sizeof(Locacao));

    gravar.close();
    arq.close();
    arq2.close();
}