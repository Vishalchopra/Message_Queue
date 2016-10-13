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
	struct client_pro_data_mq *client;
	count = 0;
	client_data = ( struct client_data_mq * )malloc( sizeof(  struct client_data_mq  ) );
	client = ( struct client_pro_data_mq * )malloc( sizeof(  struct client_pro_data_mq  ) );
	client_data -> type = 1;
	client_data -> operand = '+';
	client_data -> oper1 = 5;
	client_data -> oper2 = 5;
	create_mq();
	
	count = msgsnd(mq_msg_id[0], client_data, sizeof(struct client_data_mq), 0);
	if( count == -1 ){
		perror("msgrcv");
		exit("EXIT_FAILURE");
	}
	printf("Number of byte copied in structure: %d\n", count);
	create_mq();
	printf("before msgrcv");
	if( msgrcv(mq_msg_id[1], client, sizeof( struct client_pro_data_mq ), 0, 0 ) )
	{
		perror("msgrcv");
	}
	printf("Message received:%d\n", client -> result);
	return 0;
}

int create_mq()
{
	static char index = 0;
	static uint32_t key = 964;
	//index = 0;
	//key = 964;
	mq_key[ index ] = key;
	mq_msg_id[index] = msgget(mq_key[index], 0666|IPC_CREAT);
	
	if( mq_msg_id[index] == -1){
		perror("msgget");
		exit("EXIT_FAILURE");
	}
	printf("value of index: %d %d\n", index, key);
	index++;
	key += 3;
	printf("value of index: %d %d\n", index, key);
	return 0;
}
