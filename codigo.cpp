#include <ctime>
#include <fstream>
#include <iostream>
using namespace std;

typedef struct {
    string nome, telefone;
    char cpf[11];
} Cliente;

typedef struct {
    char marca[10] = {}, modelo[10] = {}, situacao; //? Verificar se é necessario zerar todas as variaveis
    int quantidade = 0, categoria = 0, codigo = 0, placa = 0;
} Veiculo;

typedef struct {
    char cpf[11];
    int dia, mes, diaE, mesE, codigo;
    float valor = 0, valorP = 0;
} Locacao;

int funcao_opcao(int, int, int);
int veiculo_ou_cliente();

void incluir_veiculo(); // Verifica junto
void excluir_veiculo();

bool verificar_cliente(string);
void inserir_cliente(string);
void excluir_cliente(string);

bool mostrar_categoria(int);
void locacao(int, string, int);
void devolucao(string, int, int);

void relatorioA();
void relatorioB();
void relatorioC();
void relatorioD(int, int);

// TODO: Relatorios C e D, case 4, ordenação, corrigir bugs e limpar código (zerar variaveis, cin.ignore, do-while's, etc...)

int main() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int dia = ltm->tm_mday, mes = 1 + ltm->tm_mon, ano = 1900 + ltm->tm_year;
    int opcao, opcao2, opcao3, placa;
    bool existente, existente2 = false;
    string nome, aux;
    Veiculo carro;

    do {
        opcao = funcao_opcao(dia, mes, ano);
        switch (opcao) {
        case 1:
            system("cls");
            opcao2 = veiculo_ou_cliente(); // TODO: fazer do-while quando terminar
            cin.ignore();
            if (opcao2 == 1)
                incluir_veiculo();
            else {
                cout << "Digite o nome do cliente que deseja inserir: ";
                getline(cin, nome);
                existente = verificar_cliente(nome);
                if (!existente) {
                    inserir_cliente(nome);
                    cout << "Cliente inserido com sucesso!" << endl;
                } else
                    cout << "Cliente ja cadastrado!" << endl;
            }
            break;

        case 2:
            system("cls");
            opcao2 = veiculo_ou_cliente();
            cin.ignore();
            if (opcao2 == 1) {
                excluir_veiculo();
                cout << "Veiculo excluido!" << endl;
            } else {
                cout << "Digite o nome do cliente que deseja excluir: ";
                getline(cin, nome);
                existente = verificar_cliente(nome);
                if (existente) {
                    excluir_cliente(nome);
                    cout << "Cliente excluido!" << endl;
                } else
                    cout << "Cliente inexistente!" << endl;
            }
            break;

        case 3:
            system("cls");
            cout << "Digite o nome do cliente: ";
            cin.ignore();
            getline(cin, nome);
            existente = verificar_cliente(nome);
            if (!existente) {
                cout << "Cliente inexistente! Retornando..." << endl;
                break;
            } else {
                do { //TODO: Passar os cout's para dentro da função mostrar_categoria
                    cout << "Qual a categoria do veiculo que voce deseja fazer a locacao?" << endl;
                    cout << "Categoria 1: Basica (R$10 por dia)" << endl;
                    cout << "Categoria 2: Intermediaria (R$20 por dia)" << endl;
                    cout << "Categoria 3: Super (R$30 por dia)" << endl;
                    cin >> opcao3;
                } while (opcao3 < 1 or opcao3 > 3);
                existente2 = mostrar_categoria(opcao3); //! Erro aqui
                if (existente2 == true) {
                    cout << "Informe a placa do veiculo que deseja lotar: ";
                    cin >> placa;
                    locacao(placa, nome, opcao3);
                }
            }
            break;

        case 4: //! FAZENDO
            cout << "Digite o cpf do cliente que deseja fazer a devolucao: ";
            cin.ignore();
            getline(cin, aux);
            existente = verificar_cliente(aux);
            if (existente == true) {
                devolucao(aux, dia, mes);
                cout << "Devolucao realizada!" << endl;
            } else
                cout << "Cliente nao cadastrado!" << endl;
            break;

        case 5: //! Falta arrumar relatórios C e D
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
    cout << "1 - Veiculo" << endl;
    cout << "2 - Cliente" << endl;
    cin >> escolher;
    return escolher;
}

void incluir_veiculo() { //! Talvez esteja errado
    int n;
    Veiculo carro;
    fstream arq("FROTA.DAD", ios::binary | ios::in | ios::out | ios::app);
    string aux;
    int procurar;

    cout << "Informe a placa do veiculo: ";
    cin >> procurar;

    arq.seekg(0, ios::end);
    n = arq.tellg() / sizeof(Veiculo);
    arq.seekg(0, ios::beg);

    for (int i = 0; i < n; i++) {
        arq.read((char *)(&carro), sizeof(Veiculo));
        if (carro.placa == procurar) {
            cout << "Veiculo ja cadastrado!" << endl;
            system("pause");
            return;
        }
    }
    carro.placa = procurar;
    cout << "Informe o codigo do veiculo: ";
    cin >> carro.codigo;
    cout << "Informe a categoria (1 - Basico / 2 - Intermediario / 3 - Super): ";
    cin >> carro.categoria;
    cin.ignore();
    cout << "Informe a marca: ";
    getline(cin, aux);
    for (unsigned int i = 0; i < aux.size(); i++)
        carro.marca[i] = aux[i];

    cout << "Informe o modelo: ";
    getline(cin, aux);
    for (unsigned int i = 0; i < aux.size(); i++)
        carro.modelo[i] = aux[i];

    carro.situacao = 'D';

    arq.write((char *)(&carro), sizeof(Veiculo));
    cout << "Veiculo inserido com sucesso!" << endl;
    arq.close();
}

void excluir_veiculo() //! Talvez esteja errado
{
    int n, procurar;
    Veiculo carro;
    ifstream arq("FROTA.DAD", ios::binary | ios::in);
    ofstream temp("temp.DAD", ios::binary | ios::out | ios::app);

    cout << "Informe a placa do veiculo: ";
    cin >> procurar;

    arq.seekg(0, ios::end);
    n = arq.tellg() / sizeof(Veiculo);
    arq.seekg(0, ios::beg);

    for (int i = 0; i < n; i++) {
        arq.read((char *)(&carro), sizeof(Veiculo));
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
    string aux;
    ofstream gravar("CLIENTE.TXT", ios::app);

    gravar << nome << endl;
    cout << "Informe o CPF do cliente: ";
    getline(cin, aux);
    for (unsigned int i = 0; i < aux.size(); i++)
        pessoa.cpf[i] = aux[i];
    gravar << pessoa.cpf << endl;
    cout << "Informe o telefone do cliente: ";
    getline(cin, pessoa.telefone);
    gravar << pessoa.telefone << endl;

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
}

bool mostrar_categoria(int categoria) {
    ifstream arq("FROTA.DAD", ios::binary);
    Veiculo carro;
    bool mostrar = false;

    arq.seekg(0, ios::beg);
    cout << "Mostrando veiculos disponiveis por categoria: " << endl;
    cout << "---------------------------------" << endl;
    while (arq.read((char *)(&carro), sizeof(Veiculo))) {
        //TODO: Tirar os couts quando terminar de fazer
        cout << "Categoria inserida: " << carro.categoria << endl;
        cout << "Categoria: " << categoria << endl;
        cout << "Situacao: " << carro.situacao << endl;
        if (carro.categoria == categoria and carro.situacao == 'D') {
            mostrar = true;
            cout << "Codigo: " << carro.codigo << endl;
            cout << "Marca: " << carro.marca << endl;
            cout << "Modelo: " << carro.modelo << endl;
            cout << "Placa: " << carro.placa << endl;
            cout << "---------------------------------" << endl;
        }
    }
    if (mostrar == false)
        cout << "nenhum veiculo disponivel nessa categoria..." << endl;
    arq.close();
    return mostrar;
}

void locacao(int placa, string nome, int categoria) //! Provavelmente está errado
{
    ofstream gravar("LOCACAO.DAD", ios::out | ios::binary | ios::app);
    fstream arq("FROTA.DAD", ios::ate | ios::binary); // Abre e vai pro final
    ifstream arq2("CLIENTE.TXT", ios::in);

    string linha, aux;
    Locacao carro;
    Veiculo carroV;
    int dias = 0;

    while (!arq2.eof()) {
        getline(arq2, linha);
        if (linha == nome) {
            getline(arq, linha);
            aux = linha;
            for (unsigned int i = 0; i < aux.size(); i++)
                carro.cpf[i] = aux[i];
            break;
        }
    }

    arq.seekg(0, ios::beg);
    do {
        arq.read((char *)(&carroV), sizeof(Veiculo));
        if (carroV.placa == placa) {
            carro.codigo = carroV.codigo;
            carroV.quantidade++;
            carroV.situacao = 'L';
            arq.seekp(-sizeof(Veiculo), ios::cur);
            arq.write((char *)(&carroV), sizeof(Veiculo));
            break;
        }
    } while (arq.eof());

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
    else if (carro.mes < carro.mesE)
        dias = (30 - carro.dia) + carro.diaE;

    carro.valor = (10 * categoria) * dias;
    cout << "Valor a ser pago: R$" << carro.valor << ",00" << endl;

    gravar.write((char *)(&carro), sizeof(Locacao));

    gravar.close();
    arq.close();
    arq2.close();
}

void relatorioA() // VEICULOS
{
    ifstream arq("FROTA.DAD", ios::binary);
    Veiculo carro;
    string teste;

    arq.seekg(0, ios::end);
    int n = arq.tellg() / sizeof(Veiculo);
    arq.seekg(0, ios::beg);

    cout << "Mostrando veiculos... " << endl;
    cout << "---------------------------------" << endl;
    for (int i = 0; i < n; i++) {
        arq.read((char *)(&carro), sizeof(Veiculo));

        if (carro.situacao == 'D')
            teste = "Disponivel";
        else
            teste = "Locado";

        cout << "Codigo: " << carro.codigo << endl;
        cout << "Marca: " << carro.marca << endl;
        cout << "Modelo: " << carro.modelo << endl;
        cout << "Placa: " << carro.placa << endl;
        cout << "Situacao: " << teste << endl;
        cout << "Quantidade de locacoes: " << carro.quantidade << endl;
        cout << "Categoria: " << carro.categoria << endl;
        cout << "---------------------------------" << endl;
    }

    arq.close();
}

void relatorioB() // CLIENTES
{
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

void relatorioC() // LOCACOES
{
    ifstream arq("LOCACAO.DAD", ios::binary | ios::in);
    Locacao carro;

    arq.seekg(0, ios::end);
    int n = arq.tellg() / sizeof(Locacao);
    arq.seekg(0, ios::beg);

    cout << "Mostrando veiculos... " << endl;
    cout << "---------------------------------" << endl;
    for (int i = 0; i < n; i++) {
        arq.read((char *)(&carro), sizeof(Locacao));

        cout << "Codigo: " << carro.codigo << endl; 
        cout << "CPF: " << carro.cpf << endl;       // Transformado para char
        cout << "Valor: " << carro.valor << endl;
        cout << "Valor pago: " << carro.valorP << endl;
        cout << "Data de locacao: " << carro.dia << "/" << carro.mes << endl;
        cout << "Data de devolucao: " << carro.diaE << "/" << carro.mesE << endl;
        cout << "---------------------------------" << endl;
    }

    arq.close();
}

void relatorioD(int dia, int mes) // DIA DE HOJEdia, mes
{
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

void devolucao(string aux_cpf, int dia, int mes){
    Veiculo carro;

}