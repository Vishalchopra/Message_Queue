#include "header.h"

uint32_t mq_key[3];
int32_t mq_msg_id[3];

int req_client();
int create_mq();

int main()
{
	req_client();
	return 0;
}

int req_client()
{
	int32_t count;
	struct client_data_mq *client_data;
	count = 0;
	client_data = ( struct client_data_mq * )malloc( sizeof(  struct client_data_mq  ) );

	create_mq();
	
	count = msgrcv(mq_msg_id[1], client_data, sizeof(struct client_data_mq), 0, 0);
	if( count == -1 ){
		perror("msgrcv");
		exit("EXIT_FAILURE");
	}
	printf("operand = %c, oper1 = %d, oper2 = %d\n", (client_data -> operand), (client_data -> oper1), (client_data -> oper2));
	printf("Number of byte copied in structure: %d\n", count);
	
	return 0;
}

int create_mq()
{
	char index;
	static uint32_t key;
	key = 994;
	mq_key[ index ] = key;
	mq_msg_id[index] = msgget(mq_key[index], 0666|IPC_CREAT);
	
	if( mq_msg_id[index] == -1){
		perror("msgget");
		exit("EXIT_FAILURE");
	}
	index++;
	key++;
	return 0;
}
