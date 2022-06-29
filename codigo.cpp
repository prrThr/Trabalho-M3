#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>
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
bool verificar_existente(string, string);
void continuar();

void inserir_veiculo(string);
void excluir_veiculo(string);
void inserir_ordenado_cliente(string);
void excluir_cliente(string);

int escolher_categoria();
bool mostrar_categoria(int);
void locacao(string, string, int);
void devolucao(string, int, int);

void relatorioA();
void relatorioB();
void relatorioC();
void relatorioD(int, int);

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
                if (!existente) {
                    inserir_veiculo(nome_ou_placa);
                } else
                    cout << "Veiculo ja cadastrado!" << endl;
            } else {
                cout << "Digite o nome do cliente que deseja inserir: ";
                getline(cin, nome_ou_placa);
                existente = verificar_existente(nome_ou_placa, "cliente.txt");
                if (!existente)
                    inserir_ordenado_cliente(nome_ou_placa);
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
            cin.ignore();
            break;

        case 4:
            cout << "Digite o cpf do cliente que deseja fazer a devolucao: ";
            cin.ignore();
            getline(cin, aux);
            existente = verificar_existente(aux, "cliente.txt");
            if (existente == true)
                devolucao(aux, dia, mes);
            else
                cout << "Cliente nao cadastrado!" << endl;
            break;

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
            cin.ignore();
            break;

        case 6:
            cout << "Saindo..." << endl;
            break;
        }
        continuar();
        system("cls");
    } while (opcao != 6);
    return 0;
}

int funcao_opcao(int dia, int mes, int ano) {
    int escolha;
    do {
        cout << "Data:" << dia << "/" << mes << "/" << ano << endl;
        cout << "Digite a opcao desejada: " << endl;
        cout << "1 - Incluir um veiculo ou cliente" << endl;
        cout << "2 - Excluir veiculo ou cliente" << endl;
        cout << "3 - Locacao de um veiculo" << endl;
        cout << "4 - Devolucao de um veiculo" << endl;
        cout << "5 - Relatorios" << endl;
        cout << "6 - Sair" << endl;
        cin >> escolha;
        if (escolha < 1 or escolha > 6)
            cout << "Digite um numero entre 1 e 6" << endl;
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

bool verificar_existente(string nome_ou_placa, string escolha) {
    ifstream arq(escolha.c_str());
    string linha;

    while (getline(arq, linha))
        if (linha == nome_ou_placa) {
            arq.close();
            return true;
        }
    arq.close();
    return false;
}

void continuar() {
    cout << "Pressione ENTER para continuar" << endl;
    cin.get();
}

void inserir_veiculo(string placa) {
    Veiculo carro;
    ofstream arq("frota.txt", ios::app);
    string linha;

    carro.placa = placa;
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

void excluir_veiculo(string placa) {
    string linha;
    ifstream frota("frota.txt", ios::in);
    ofstream new_frota("new_frota.txt", ios::out);
    Veiculo carro;
    string qntd;
    bool locado = false;

    while (getline(frota, linha)) {
        if (linha == placa) {
            getline(frota, linha);
            carro.codigo = linha;
            getline(frota, linha);
            carro.categoria = linha;
            getline(frota, linha);
            carro.marca = linha;
            getline(frota, linha);
            carro.modelo = linha;
            getline(frota, linha);
            carro.situacao = linha;
            getline(frota, linha);
            qntd = linha;
            if (carro.situacao == "L") {
                cout << "Nao e possivel excluir veiculo enquanto ele estiver locado" << endl;
                new_frota << placa << endl;
                new_frota << carro.codigo << endl;
                new_frota << carro.categoria << endl;
                new_frota << carro.marca << endl;
                new_frota << carro.modelo << endl;
                new_frota << carro.situacao << endl;
                new_frota << qntd << endl;
                locado = true;
            }
        } else
            new_frota << linha << endl;
    }
    new_frota.close();
    frota.close();
    remove("frota.txt");
    rename("new_frota.txt", "frota.txt");
    if (!locado)
        cout << "Veiculo excluido!" << endl;
}

void inserir_ordenado_cliente(string nome) {
    Cliente pessoa;
    ifstream cliente("cliente.txt", ios::in);
    ofstream new_cliente("new_cliente.txt", ios::out);
    string linha;
    vector<Cliente> pessoaVector;

    pessoa.nome = nome;
    cout << "Digite o cpf: ";
    getline(cin, pessoa.cpf);
    cout << "Digite o telefone: ";
    getline(cin, pessoa.telefone);
    pessoaVector.push_back(pessoa);

    while (getline(cliente, linha)) {
        pessoa.nome = linha;
        getline(cliente, linha);
        pessoa.cpf = linha;
        getline(cliente, linha);
        pessoa.telefone = linha;
        pessoaVector.push_back(pessoa);
    }

    // --------------------Ordenação-------------------------------//
    for (int i = 0; i < pessoaVector.size(); i++) {
        for (int j = i+1; j < (pessoaVector.size()); j++)
            if (pessoaVector[i].cpf > pessoaVector[j].cpf)
                swap(pessoaVector[i], pessoaVector[j]);
    }

    for (int i = 0; i < pessoaVector.size(); i++) {
        new_cliente << pessoaVector[i].nome << endl;
        new_cliente << pessoaVector[i].cpf << endl;
        new_cliente << pessoaVector[i].telefone << endl;
    }
    // -----------------------------------------------------------//

    new_cliente.close();
    cliente.close();
    remove("cliente.txt");
    rename("new_cliente.txt", "cliente.txt");
    cout << "Cliente inserido com sucesso!" << endl;
}

void excluir_cliente(string nome) {
    string linha;
    ifstream cliente("cliente.txt", ios::in);
    ofstream new_cliente("new_cliente.txt", ios::out);

    while (getline(cliente, linha)) {
        if (linha == nome) {
            getline(cliente, linha);
            getline(cliente, linha);
        } else
            new_cliente << linha << endl;
    }
    new_cliente.close();
    cliente.close();
    remove("cliente.txt");
    rename("new_cliente.txt", "cliente.txt");
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
    string linha, catStr = to_string(categoria), quantidade;
    bool mostrar = false;

    cout << "Mostrando veiculos disponiveis por categoria: " << endl;
    cout << "---------------------------------" << endl;
    if (!arq) {
        cout << "Nao foi possivel abrir o arquivo." << endl;
        return 0;
    }
    while (!arq.eof()) {
        getline(arq, linha);
        carro.placa = linha;

        getline(arq, linha);
        carro.codigo = linha;

        getline(arq, linha);
        carro.categoria = linha;

        getline(arq, linha);
        carro.marca = linha;

        getline(arq, linha);
        carro.modelo = linha;

        getline(arq, linha);
        carro.situacao = linha;

        getline(arq, linha);
        quantidade = linha;

        if (carro.categoria == catStr and carro.situacao == "D") {
            mostrar = true;
            cout << "Placa: " << carro.placa << endl;
            cout << "Codigo: " << carro.codigo << endl;
            cout << "Categoria: " << carro.categoria << endl;
            cout << "Marca: " << carro.marca << endl;
            cout << "Modelo: " << carro.modelo << endl;
            cout << "Situacao: Disponivel" << endl;
            cout << "Quantidade de vezes locado: " << quantidade << endl;
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
    int dias, meses, i = 0;
    bool achou = false;

    while (getline(cliente, linha)) {
        if (linha == nome) {
            getline(cliente, linha);
            gravar << linha << endl;
            break;
        }
    }
    cliente.close();

    frota.open("frota.txt", ios::in);
    new_frota.open("new_frota.txt", ios::out);
    while (getline(frota, linha)) {
        if (linha == placa)
            achou = true;
        if (achou)
            i++;
        if (achou and i == 2)
            gravar << linha << endl;
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
    carro.valor = (10 * categoria) * dias;
    cout << "Valor a ser pago: R$" << carro.valor << ",00" << endl;
    gravar << carro.dia << endl;
    gravar << carro.mes << endl;
    gravar << carro.diaE << endl;
    gravar << carro.mesE << endl;
    gravar << carro.valor << endl;
    gravar << 0 << endl;

    gravar.close();
    frota.close();
    new_frota.close();
    remove("frota.txt");
    rename("new_frota.txt", "frota.txt");
    cout << "Veiculo locado com sucesso!" << endl;
}

void devolucao(string cpf, int dia, int mes) {
    Locacao locado;
    string linha, codigo;
    bool multa, achou = false;
    int aux, dias, i = 0, intLinha;

    ifstream locacao("locacao.txt", ios::in);
    ofstream new_locacao("new_locacao.txt", ios::out);
    while (getline(locacao, linha)) {
        if (linha == cpf) {
            getline(locacao, linha);
            codigo = linha;

            getline(locacao, linha);
            intLinha = stoi(linha);
            locado.dia = intLinha;

            getline(locacao, linha);
            intLinha = stoi(linha);
            locado.mes = intLinha;

            getline(locacao, linha);
            intLinha = stoi(linha);
            locado.diaE = intLinha;

            getline(locacao, linha);
            intLinha = stoi(linha);
            locado.mesE = intLinha;

            getline(locacao, linha);
            intLinha = stoi(linha);
            locado.valor = intLinha;

            getline(locacao, linha);
        } else
            new_locacao << linha << endl;
    }
    locacao.close();
    new_locacao.close();
    remove("locacao.txt");
    rename("new_locacao.txt", "locacao.txt");

    i = 0;
    ifstream frota("frota.txt", ios::in);
    ofstream new_frota("new_frota.txt", ios::out);
    while (getline(frota, linha)) {
        if (linha == codigo)
            achou = true;

        if (achou)
            i++;

        if (i == 5)
            new_frota << "D" << endl;

        if (i == 6) {
            intLinha = stoi(linha);
            new_frota << intLinha + 1 << endl;
        }
        if (i != 5 and i != 6)
            new_frota << linha << endl;
    }
    if (achou == false) {
        cout << "Nenhuma locacao realizada! Retornando..." << endl;
        return;
    }
    if (mes > locado.mesE) {
        aux = mes - locado.mesE;
        dias = (30 - locado.diaE) + ((aux - 1) * 30) + dia;
        multa = true;
    } else if (mes == locado.mesE and dia > locado.diaE) {
        dias = dia - locado.diaE;
        multa = true;
    }
    if (!multa) {
        locado.valorP = locado.valor;
        cout << "Valor total a pagar: R$" << locado.valorP << ",00" << endl;
    }
    if (multa) {
        cout << "ATENCAO! Devolucao fora do prazo! " << endl;
        locado.valorP = locado.valor * (1.20 + (0.01 * dias));
        cout << "Valor total a pagar: R$" << locado.valorP << endl;
    }
    frota.close();
    new_frota.close();
    remove("frota.txt");
    rename("new_frota.txt", "frota.txt");
    cout << "Devolucao executada com sucesso!" << endl;
}

void relatorioA() {
    ifstream arq("frota.txt", ios::in);
    string linha, trocar;

    system("cls");
    if (!arq) {
        cout << "Nenhum veiculo registrado" << endl;
        return;
    }
    cout << "Mostrando veiculos..." << endl;
    cout << "---------------------------------" << endl;
    while (getline(arq, linha)) {
        cout << "Placa: " << linha << endl;

        getline(arq, linha);
        cout << "Codigo: " << linha << endl;

        getline(arq, linha);
        if (linha == "1")
            trocar = "Basica";
        else if (linha == "2")
            trocar = "Intermediaria";
        else
            trocar = "Super";
        cout << "Categoria: " << trocar << endl;

        getline(arq, linha);
        cout << "Marca: " << linha << endl;

        getline(arq, linha);
        cout << "Modelo: " << linha << endl;

        getline(arq, linha);
        if (linha == "D")
            trocar = "Disponivel";
        else
            trocar = "Locado";
        cout << "Situacao: " << trocar << endl;

        getline(arq, linha);
        cout << "Quantidade de locacoes: " << linha << endl;
        cout << "---------------------------------" << endl;
    }
    if (arq.peek() == EOF)
        cout << "Nenhum veiculo registrado" << endl;
    arq.close();
}

void relatorioB() {
    ifstream arq("cliente.txt", ios::in);
    string linha;

    system("cls");
    if (!arq) {
        cout << "Nenhum cliente registrado" << endl;
        return;
    }
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
    if (arq.peek() == EOF)
        cout << "Nenhum cliente registrado" << endl;
    arq.close();
}

void relatorioC() {
    ifstream arq("locacao.txt");
    string linha;

    system("cls");
    if (!arq) {
        cout << "Nenhuma locacao no momento" << endl;
        return;
    }

    cout << "Mostrando veiculos locados... " << endl;
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
    if (arq.peek() == EOF)
        cout << "Nenhuma locacao no momento" << endl;
    arq.close();
}

void relatorioD(int dia, int mes) {
    ifstream arq("locacao.txt", ios::in);
    Locacao locado;
    string linha;

    system("cls");
    if (!arq) {
        cout << "Nenhuma devolucao para hoje" << endl;
        return;
    }

    cout << "Mostrando veiculos para serem devolvidos hoje..." << endl;
    cout << "Data de Hoje: " << dia << "/" << mes << endl;
    cout << "---------------------------------" << endl;
    while (getline(arq, linha)) {
        locado.cpf = linha;

        getline(arq, linha);
        locado.codigo = linha;

        getline(arq, linha);
        locado.dia = stoi(linha);

        getline(arq, linha);
        locado.mes = stoi(linha);

        getline(arq, linha);
        locado.diaE = stoi(linha);

        getline(arq, linha);
        locado.mesE = stoi(linha);

        getline(arq, linha);
        locado.valor = stof(linha);

        getline(arq, linha);
        locado.valorP = stof(linha);
        ;

        if (locado.diaE == dia and locado.mesE == mes) {
            cout << "Codigo: " << locado.codigo << endl;
            cout << "CPF: " << locado.cpf << endl;
            cout << "Valor: R$" << locado.valor << ",00" << endl;
            cout << "Valor pago: R$" << locado.valorP << ",00" << endl;
            cout << "Data de locacao: " << locado.dia << "/" << locado.mes << endl;
            cout << "Data de devolucao: " << locado.diaE << "/" << locado.mesE << endl;
            cout << "---------------------------------" << endl;
        }
    }
    if (arq.peek() == EOF)
        cout << "Nenhuma devolucao para hoje " << endl;
    arq.close();
}
