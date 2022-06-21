#include <fstream>
#include <iostream>
using namespace std;

// Veículo: código, marca, modelo, placa, categoria, situação, Quantidade de locações
// Cliente: Nome, CPF, telefone
// Locação: Data, CPF, código, data entrega, valor, valor pago

int funcao_opcao();

int main() {
    int opcao;

    do {
        opcao = funcao_opcao();

        switch (opcao) {
        case 1:
            //Verificar se veículo existe (placa)
            //Verificar se cliente existe (nome)
            //Incluir um veiculo ou cliente
            break;

        case 2:
            //Verificar se veículo existe (placa)
            //Verificar se cliente existe (nome)
            //Excluir veiculo ou cliente
            break;

        case 3:
            //Verificar se cliente existe (nome)
            //Listar veículos disponíveis. Emitir mensagem de erro caso não existir nenhum veículo
            //Locacao de um veiculo
            break;

        case 4:
            //Verificar pelo CPF do cliente e multa caso a data seja posterior a prevista
            //Devolucao de um veiculo
            break;

        case 5:
            //Relatorios
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
