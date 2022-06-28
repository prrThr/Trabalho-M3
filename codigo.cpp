#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

typedef struct {
    string nome, telefone, cpf;
} Cliente;

typedef struct {
    string marca, modelo, placa, situacao, categoria, codigo;
    int quantidade;
} Veiculo;

typedef struct {
    string cpf, codigo;
    int dia, mes, diaE, mesE;
    float valor, valorP;
} Locacao;

int funcao_opcao(int, int, int);
int veiculo_ou_cliente();

void inserir_veiculo(string);
void excluir_veiculo(string);

bool verificar_existente(string, string);
void inserir_cliente(string);
void excluir_cliente(string);

int escolher_categoria();
bool mostrar_categoria(int);
void locacao(string, string, int);
void devolucao(string, int, int);

void relatorioA();
void relatorioB();
void relatorioC();
void relatorioD(int, int);

// TODO Agora: conta para os valores na locação, relatório D, devolução e ordenação
// TODO Ao terminar: zerar variáveis, cin.ignore, testes de entrada, reduzir aonde for possível

int main() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int dia = ltm->tm_mday, mes = 1 + ltm->tm_mon, ano = 1900 + ltm->tm_year;
    int opcao, opcao2, opcao_categoria;
    bool existente, existente_categoria = false;
    string nome_ou_placa, aux, escolha, placa;

    do {
        opcao = funcao_opcao(dia, mes, ano);
        switch (opcao) {
        case 1:
            system("cls");
            opcao2 = veiculo_ou_cliente();
            cin.ignore();

            if (opcao2 == 1) {
                cout << "Digite a placa: ";
                getline(cin, nome_ou_placa);
                existente = verificar_existente(nome_ou_placa, "frota.txt");
                if (!existente)
                    inserir_veiculo(nome_ou_placa);
                else
                    cout << "Veiculo ja cadastrado!" << endl;

            } else {
                cout << "Digite o nome do cliente que deseja inserir: ";
                getline(cin, nome_ou_placa);
                existente = verificar_existente(nome_ou_placa, "cliente.txt");
                if (!existente)
                    inserir_cliente(nome_ou_placa);
                else
                    cout << "Cliente ja cadastrado!" << endl;
            }
            break;

        case 2:
            system("cls");
            opcao2 = veiculo_ou_cliente();
            cin.ignore();

            if (opcao2 == 1) {
                cout << "Digite a placa do veiculo que deseja excluir: ";
                getline(cin, nome_ou_placa);
                existente = verificar_existente(nome_ou_placa, "frota.txt");
                if (existente)
                    excluir_veiculo(nome_ou_placa);
                else
                    cout << "Veiculo inexistente!" << endl;

            } else {
                cout << "Digite o nome do cliente que deseja excluir: ";
                getline(cin, nome_ou_placa);
                existente = verificar_existente(nome_ou_placa, "cliente.txt");
                if (existente)
                    excluir_cliente(nome_ou_placa);
                else
                    cout << "Cliente inexistente!" << endl;
            }
            break;

        case 3:
            system("cls");
            cout << "Digite o nome do cliente: ";
            cin.ignore();
            getline(cin, nome_ou_placa);
            existente = verificar_existente(nome_ou_placa, "cliente.txt");
            if (!existente) {
                cout << "Cliente inexistente! Retornando..." << endl;
                break;
            } else {
                opcao_categoria = escolher_categoria();
                existente_categoria = mostrar_categoria(opcao_categoria);
                if (existente_categoria) {
                    cout << "Informe a placa do veiculo que deseja lotar: ";
                    getline(cin, placa);
                    locacao(placa, nome_ou_placa, opcao_categoria);
                } else
                    cout << "Nenhum veiculo disponivel nesta categoria!" << endl;
            }
            break;

            /*case 4:
                cout << "Digite o cpf do cliente que deseja fazer a devolucao: ";
                cin.ignore();
                getline(cin, aux);
                existente = verificar_existente(aux);
                if (existente == true) {
                    devolucao(aux, dia, mes);
                    cout << "Devolucao realizada!" << endl;
                } else
                    cout << "Cliente nao cadastrado!" << endl;
                break;*/

        case 5:
            do {
                system("cls");
                cout << "1.Relatorio Listagem dos veiculos da frota" << endl;
                cout << "2.Relatorio Listagem dos clientes" << endl;
                cout << "3.Relatorio Listagem das locacoes" << endl;
                cout << "4.Relatorio Listagem dos veiculos a serem devolvidos hoje" << endl;
                cin >> opcao2;
            } while (opcao2 < 1 or opcao2 > 4);

            switch (opcao2) {
            case 1:
                relatorioA();
                break;
            case 2:
                relatorioB();
                break;
            case 3:
                relatorioC();
                break;
            case 4:
                relatorioD(dia, mes);
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

int funcao_opcao(int dia, int mes, int ano) {
    int escolha;
    do {
        cout << "Data:" << dia << "/" << mes << "/" << ano << endl << endl;
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
    do {
        cout << "1 - Veiculo" << endl;
        cout << "2 - Cliente" << endl;
        cin >> escolher;
        if (escolher != 1 and escolher != 2)
            cout << "Digite apenas 1 ou 2" << endl;
    } while (escolher != 1 and escolher != 2);
    return escolher;
}

void inserir_veiculo(string placa) {
    Veiculo carro;
    ofstream arq("FROTA.TXT", ios::app);
    string linha;

    carro.placa = placa; // Talvez de para botar direto
    arq << carro.placa << endl;

    cout << "Informe o codigo do veiculo: ";
    getline(cin, carro.codigo);
    arq << carro.codigo << endl;

    cout << "Informe a categoria (1 - Basico / 2 - Intermediario / 3 - Super): ";
    getline(cin, carro.categoria);
    arq << carro.categoria << endl;

    cout << "Informe a marca: ";
    getline(cin, carro.marca);
    arq << carro.marca << endl;

    cout << "Informe o modelo: ";
    getline(cin, carro.modelo);
    arq << carro.modelo << endl;

    carro.situacao = "D";
    arq << carro.situacao << endl;
    carro.quantidade = 0;
    arq << carro.quantidade << endl;

    cout << "Veiculo inserido com sucesso" << endl;
    arq.close();
}

void excluir_veiculo(string nome) {
    string linha;
    ifstream arq("frota.txt", ios::in);
    ofstream temp("temp.txt", ios::out);

    while (getline(arq, linha)) {
        if (linha == nome) {
            for (int i = 0; i < 7; i++)
                getline(arq, linha);
        } else
            temp << linha << endl;
    }

    temp.close();
    arq.close();
    remove("frota.txt");
    rename("temp.txt", "frota.txt");
    cout << "Veiculo excluido!" << endl;
}

bool verificar_existente(string nome, string escolha) {
    ifstream arq(escolha.c_str());
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

    cout << "Cliente inserido com sucesso!" << endl;
    gravar.close();
}

void excluir_cliente(string nome) {
    string linha;
    ifstream arq("CLIENTE.TXT", ios::in);
    ofstream temp("temp.txt", ios::out);

    while (getline(arq, linha)) {
        if (linha == nome) {
            getline(arq, linha);
            getline(arq, linha);
        } else
            temp << linha << endl;
    }

    temp.close();
    arq.close();
    remove("CLIENTE.TXT");
    rename("temp.txt", "CLIENTE.TXT");
    cout << "Cliente excluido!" << endl;
}

int escolher_categoria() {
    int opcao;
    do {
        cout << "Qual a categoria do veiculo que voce deseja fazer a locacao?" << endl;
        cout << "Categoria 1: Basica (R$10 por dia)" << endl;
        cout << "Categoria 2: Intermediaria (R$20 por dia)" << endl;
        cout << "Categoria 3: Super (R$30 por dia)" << endl;
        cin >> opcao;
        cin.ignore();
    } while (opcao < 1 or opcao > 3);
    return opcao;
}

bool mostrar_categoria(int categoria) {
    ifstream arq("frota.txt", ios::in);
    Veiculo carro;
    bool mostrar = false;
    string linha;
    string marca, modelo, placa, situacao, categoria2, catStr = to_string(categoria), codigo, quantidade;

    cout << "Mostrando veiculos disponiveis por categoria: " << endl;
    cout << "---------------------------------" << endl;

    while (!arq.eof()) {
        getline(arq, linha);
        placa = linha;

        getline(arq, linha);
        codigo = linha;

        getline(arq, linha);
        categoria2 = linha;

        getline(arq, linha);
        marca = linha;

        getline(arq, linha);
        modelo = linha;

        getline(arq, linha);
        situacao = linha;

        getline(arq, linha);
        quantidade = linha;

        if (categoria2 == catStr and situacao == "D") {
            mostrar = true;
            cout << "Placa: " << placa << endl;
            cout << "Codigo: " << codigo << endl;
            cout << "Categoria: " << categoria2 << endl;
            cout << "Marca: " << marca << endl;
            cout << "Modelo: " << modelo << endl;
            cout << "Situacao: Disponivel" << endl;
            cout << "Quantidade: " << quantidade << endl;
            cout << "--------------------------------------" << endl;
        }
    }
    arq.close();
    return mostrar;
}

void locacao(string placa, string nome, int categoria) {
    ofstream gravar("locacao.txt", ios::out | ios::app);
    ifstream cliente("cliente.txt", ios::in);
    ifstream frota;
    ofstream new_frota;

    string linha;
    Locacao carro;
    int dias, meses, quantidade, i = 0;
    bool achou = false;

    while (getline(cliente, linha)) { // Abriu cliente
        if (linha == nome) {
            getline(cliente, linha);
            gravar << linha << endl; // Grava o CPF do cliente achado
            break;
        }
    }
    cliente.close();

    frota.open("frota.txt", ios::in);
    new_frota.open("new_frota.txt", ios::out);
    while (getline(frota, linha)) {
        i++;
        if (linha == placa)
            achou = true;
        if (achou == true and i == 2)
            gravar << linha << endl; // Gravar o código
        if (achou and i == 6)
            new_frota << "L" << endl;
        else
            new_frota << linha << endl;
    }

    cout << "Informe o dia da locacao:";
    cin >> carro.dia;
    cout << "Informe o mes da locacao: ";
    cin >> carro.mes;
    cout << "Informe o dia da devolucao: ";
    cin >> carro.diaE;
    cout << "Informe o mes da devolucao: ";
    cin >> carro.mesE;

    if (carro.mes == carro.mesE)
        dias = carro.diaE - carro.dia;
    else if (carro.mes < carro.mesE) {
        meses = carro.mesE - carro.mes;
        dias = (30 - carro.dia) + ((meses - 1) * 30) + carro.diaE;
    }
    // Ex: 15/07 - 23/10
    //(30 - 15) + ((3-1)*30) + 23; = 15 + 60 + 23 = 98 dias

    carro.valor = (10 * categoria) * dias;
    cout << "Valor a ser pago: R$" << carro.valor << ",00" << endl;

    gravar << carro.dia << endl;
    gravar << carro.mes << endl;
    gravar << carro.diaE << endl;
    gravar << carro.mesE << endl;
    gravar << carro.valor << endl;
    gravar << 0 << endl; // Valor

    gravar.close();
    frota.close();
    new_frota.close();
    remove("frota.txt");
    rename("new_frota.txt", "frota.txt");
    cout << "Veiculo locado com sucesso!" << endl;
}

void relatorioA() {
    ifstream arq("frota.txt", ios::in);
    string linha, teste;

    system("cls");
    cout << "Mostrando veiculos..." << endl;
    cout << "---------------------------------" << endl;
    while (getline(arq, linha)) {
        cout << "Placa: " << linha << endl;
        getline(arq, linha);
        cout << "Codigo: " << linha << endl;
        getline(arq, linha);
        cout << "Categoria: " << linha << endl;
        getline(arq, linha);
        cout << "Marca: " << linha << endl;
        getline(arq, linha);
        cout << "Modelo: " << linha << endl;
        getline(arq, linha);
        if (linha == "D")
            teste = "Disponivel";
        else
            teste = "Locado";
        cout << "Situacao: " << teste << endl;
        getline(arq, linha);
        cout << "Quantidade de locacoes: " << linha << endl;
        cout << "---------------------------------" << endl;
    }
    arq.close();
}

void relatorioB() {
    ifstream arq("CLIENTE.TXT", ios::in);
    string linha;

    system("cls");
    cout << "Mostrando Clientes..." << endl;
    cout << "---------------------------------" << endl;
    while (getline(arq, linha)) {
        cout << "Nome: " << linha << endl;
        getline(arq, linha);
        cout << "CPF: " << linha << endl;
        getline(arq, linha);
        cout << "Telefone: " << linha << endl;
        cout << "---------------------------------" << endl;
    }
    cout << endl;
    arq.close();
}

void relatorioC() {
    ifstream arq("locacao.txt");
    string linha;

    cout << "Mostrando veiculos locados.. " << endl;
    cout << "---------------------------------" << endl;
    while (getline(arq, linha)) {
        cout << "CPF: " << linha << endl;
        getline(arq, linha);

        cout << "Codigo: " << linha << endl;
        getline(arq, linha);

        cout << "Data de locacao: " << linha;
        getline(arq, linha);
        cout << "/" << linha << endl;
        getline(arq, linha);

        cout << "Data de devolucao: " << linha;
        getline(arq, linha);
        cout << "/" << linha << endl;
        getline(arq, linha);

        cout << "Valor a pagar: R$" << linha << ",00" << endl;
        getline(arq, linha);

        cout << "Valor pago: R$" << linha << ",00" << endl;
        cout << "---------------------------------" << endl;
    }

    arq.close();
}

void relatorioD(int dia, int mes) {
    ifstream arq("LOCACAO.DAD", ios::binary);
    Locacao carro;

    arq.seekg(0, ios::end);
    int n = arq.tellg() / sizeof(Locacao);
    arq.seekg(0, ios::beg);

    cout << "Mostrando veiculos para serem devolvidos hoje..." << endl;
    cout << "Data de Hoje: " << dia << "/" << mes << endl;
    cout << "---------------------------------" << endl;

    for (int i = 0; i < n; i++) {
        arq.read((char *)(&carro), sizeof(Locacao));

        if (carro.diaE == dia and carro.mesE == mes) {
            cout << "Codigo: " << carro.codigo << endl;
            cout << "CPF: " << carro.cpf << endl;
            cout << "Valor: " << carro.valor << endl;
            cout << "Valor pago: " << carro.valorP << endl;
            cout << "Data de locacao: " << carro.dia << "/" << carro.mes << endl;
            cout << "Data de devolucao: " << carro.diaE << "/" << carro.mesE << endl;
            cout << "---------------------------------" << endl;
        }
    }
    arq.close();
}

void devolucao(string cpf, int dia, int mes) {
    fstream arq1("FROTA.DAD", ios::binary);
    fstream arq2("LOCACAO.DAD", ios::binary);
    Locacao carro2;
    Veiculo carro1;
    bool multa;
    int aux, dias;

    arq2.seekg(0, ios::end);
    int n = arq2.tellg() / sizeof(Locacao);
    arq2.seekg(0, ios::beg);

    arq1.seekg(0, ios::end);
    int n2 = arq1.tellg() / sizeof(Veiculo);
    arq1.seekg(0, ios::beg);

    for (int i = 0; i < n; i++) {
        arq2.read((char *)(&carro2), sizeof(Locacao));

        if (carro2.cpf == cpf) { // talvez nao funcione
            for (int j = 0; j < n2; i++) {
                arq1.read((char *)(&carro1), sizeof(Veiculo));
                if (carro2.codigo == carro1.codigo) {
                    carro1.situacao = 'D';
                    arq1.seekp(-sizeof(Veiculo), ios::cur);
                    arq1.write((char *)(&carro1), sizeof(Veiculo));
                    break;
                }
            }
            break;
        }
        break;
    }
    if (mes > carro2.mesE) {
        aux = mes - carro2.mesE;
        dias = (30 - carro2.diaE) + ((aux - 1) * 30) + dia;
        // 15/07 - 23/10
        //(30 - 15) + ((3-1)*30) + 23; = 15 + 60 + 23 = 98 dias
        multa = true;
    } else if (mes == carro2.mesE and dia > carro2.diaE) {
        dias = dia - carro2.diaE;
        multa = true;
    } else { // dentro do prazo
        carro2.valorP = carro2.valor;
        cout << "Valor total a pagar: R$" << carro2.valorP << ",00" << endl;
    }
    if (multa == true) {
        cout << "ATENCAO! Devolucao fora do prazo! " << endl;
        carro2.valorP = carro2.valor * (1.20 + (0.01 * dias));
        cout << "Valor total a pagar: R$" << carro2.valorP << ",00" << endl;
    }
    arq1.close();
    arq2.close();
}