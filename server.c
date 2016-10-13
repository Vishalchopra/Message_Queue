#include "header.h"

uint32_t mq_key[6];
int32_t mq_msg_id[6];

int req_client();
int create_mq();

int process_client();
int main()
{
	req_client();
	process_client();
	return 0;
}

int req_client()
{
	int32_t count;
	struct client_data_mq *client_data;
	count = 0;
	client_data = ( struct client_data_mq * )malloc( sizeof(  struct client_data_mq  ) );
	
	create_mq();
	printf("Before receive\n");	
	count = msgrcv(mq_msg_id[0], client_data, sizeof(struct client_data_mq), 0, 0);
	if( count == -1 ){
		perror("msgrcv");
	//	exit("EXIT_FAILURE");
	}
	printf("After receive\n");	
	printf("operand = %c, oper1 = %d, oper2 = %d\n", (client_data -> operand), (client_data -> oper1), (client_data -> oper2));
	printf("Number of byte copied in structure: %d\n", count);
	sleep(2);
	create_mq();
	if( msgsnd(mq_msg_id[1], client_data, sizeof( struct client_data_mq ), 0) == -1 )
	{
		perror("msgsnd");
		return 0;
	}	
	return 0;
}

int create_mq()
{
	static char index = 0;
	static uint32_t key = 964;
	//key = 964;
	//index = 0;
	mq_key[ index ] = key;
	mq_msg_id[index] = msgget(mq_key[index], 0666|IPC_CREAT);
	
	if( mq_msg_id[index] == -1){
		perror("msgget");
		exit("EXIT_FAILURE");
	}
	
	printf("Before receive\n");	
	printf("Value of index %d %d\n", index, key);
	++index;
	++key;
	printf("Value of index %d %d\n", index, key);
	return 0;
}

int process_client()
{
	int32_t count;
	struct client_pro_data_mq *client_data;
	count = 0;
	client_data = ( struct client_pro_data_mq * )malloc( sizeof(  struct client_pro_data_mq  ) );

	create_mq();
	
	printf("Before receive\n");	
	count = msgrcv(mq_msg_id[2], client_data, sizeof(struct client_pro_data_mq), 0, 0);
	if( count == -1 ){
		perror("msgrcv");
		exit("EXIT_FAILURE");
	}
	printf("Before receive\n");	
	printf("RESULT = %d\n", client_data -> result);
	printf("Number of byte copied in structure: %d\n", count);
	create_mq();
	if( msgsnd(mq_msg_id[3], client_data, sizeof( struct client_pro_data_mq ), 0) == -1 )
	{
		perror("msgsnd");
		return 0;
	}	
	return 0;
}
