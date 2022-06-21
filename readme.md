## Trabalho M3

Implemente um programa de controle de locação de veículos. Para cada veículo têm-se as 
informações: código, marca, modelo, placa, categoria (1- básico, 2-intermediário, 3-super), situação 
(disponível/locado), qtde de locações (inicia com 0). A frota de veículos deverá estar armazenada em 
um arquivo de acesso direto FROTA.DAD. 
Para locar um veículo, o cliente precisa ser cadastrado (nome, cpf, telefone de contato). Os clientes 
estarão armazenados em um arquivo sequencial CLIENTE.TXT. 
Cada locação realizada deve ser armazenada em outro arquivo de acesso direto LOCACAO.DAD, e 
suas informações são data da locação, cpf cliente, código veículo, data entrega, valor a pagar, valor 
efetivamente pago. Cada categoria tem um valor de diária diferenciado (fica a seu critério definir os 
valores). Devoluções em atraso gerarão multa de 20% sobre o valor contratado mais 1% ao dia de 
atraso. 
O programa a ser implementado deve permitir as seguintes operações (através de menu/subrotinas):
1. Inclusão de veículo/cliente. Antes de incluir efetivamente veja se o cliente/veículo já existe 
(pesquise por placa/nome). Caso exista, emita mensagem de erro. Se não existir, cadastre o cliente, 
grave-o no respectivo arquivo e emita mensagem de sucesso. 
2. Exclusão de veículo/cliente. Caso não exista, emita mensagem de erro. Se existir, retire o registro 
do arquivo e emita mensagem de sucesso. 
3. Locação de veículo. Verifique se o cliente está cadastrado. Caso não esteja, emita mensagem de 
erro e cancele o processo. Liste para o cliente os veículos disponíveis conforme a categoria 
desejada. Caso não exista nenhum veículo, emita mensagem de erro e cancele o processo. Escolha 
o veículo a ser locado pela placa e atualize suas informações. Gere a locação, grave-a no respectivo 
arquivo e emita mensagem de sucesso. 
4. Devolução de veículo (cpf cliente). Caso não exista, emita mensagem de erro. Se existir, atualize a 
situação do veículo. Ainda, se a data da devolução for posterior a data de entrega prevista, 
apresente mensagem de MULTA juntamente com o valor total a pagar. Se necessário, atualize o 
registro desta locação no respectivo arquivo (deve-se manter a posição no arquivo). 
5. Relatórios: 
a) listagem dos veículos da frota. 
b) listagem dos clientes (ordenados por cpf). 
c) listagem das locações. 
d) listagem dos veículos a serem devolvidos “hoje”. 
O programa deverá apresentar uma interface básica com menus e controle de rolamento de tela. A 
qualquer entrada de dados deve-se realizar tratamento de dados/validação. Serão considerados para 
efeitos de avaliação: i) a corretude das funcionalidades do programa; ii) a otimização do programa; iii) a 
adequação/validação da entrada/saída de dados; iv) a interface e v) a utilização de 
modularização/parametrização no desenvolvimento das tarefas – não usar variáveis globais. Haverá 
desconto de 0,5 por item não apresentado.