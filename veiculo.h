/* TAD: veiculo */


typedef struct veiculo Veiculo;


/* Função obtem marca
** Operação que obtém marca do veículo
*/
void veic_ins_marca( Veiculo* );


/* Função obtém modelo
** Operação que obtém modelo do veículo
*/
void veic_ins_modelo( Veiculo* );


/* Função obtém ano
** Operação que obtém ano do veículo
*/
void veic_ins_ano( Veiculo* );


/* Função obtém renavam
** Operação que obtém renavam do veículo
*/
void veic_ins_renavam( Veiculo* );


/* Função obtém placa
** Operação que obtém placa do veículo
*/
void veic_ins_placa( Veiculo* );


/* Função mostra marca
** Operação que mostra na tela a marca do veículo
*/
void veic_mostra_marca( Veiculo* );


/* Função mostra modelo
** Operação que mostra na tela o modelo do veículo
*/
void veic_mostra_modelo( Veiculo* );


/* Função mostra ano
** Operação que mostra na tela o ano do veículo
*/
void veic_mostra_ano( Veiculo* );


/* Função mostra renavam
** Operação que mostra na tela o renavam do veículo
*/
void veic_mostra_renavam( Veiculo* );


/* Função mostra placa
** Operação que mostra na tela a placa do veículo
*/
void veic_mostra_placa( Veiculo* );


/* Função libera veiculo
** Operação que libera o espaço alocado na memória para
** a estrutura de um veículo
*/
void veic_libera( Veiculo* );


/* Função cria veiculo
** Operação que inicia uma estrutura de veículo e aloca
** na memória o espaço necessário
*/
Veiculo* veic_cria( void );


/* Função mostra veículo
** Operação que mostra os dados de um veículo na tela
*/
void veic_mostra( Veiculo* );


/* Função cadastra veículo
** Operação que recebe os dados de um veículo
*/
void veic_cad( void );