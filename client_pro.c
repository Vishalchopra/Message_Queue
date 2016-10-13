#include "header.h"

uint32_t mq_key[6];
int32_t mq_msg_id[6];

int process_client();
int create_mq();
int detect_client( struct client_data_mq *);

int main()
{
	process_client();
	return 0;
}

int process_client()
{
	int32_t count;
	struct client_data_mq *client_data;
	struct client_pro_data_mq *client_process;
	count = 0;
	client_data = ( struct client_data_mq * )malloc( sizeof(  struct client_data_mq  ) );
	client_process = ( struct client_pro_data_mq *)malloc( sizeof(  struct client_pro_data_mq  ) );
//	for(lv = 0; lv < 3; lv ++)
//	{
		create_mq();
	
		count = msgrcv(mq_msg_id[0], client_data, sizeof(struct client_data_mq), 0, 0);
		if( count == -1 ){
			perror("msgrcv");
			exit("EXIT_FAILURE");
		}
//	}
	count = detect_client( client_data );
	printf("Number of byte copied in structure: %d %d %d\n", count, client_data -> oper1, client_data -> oper2);
	create_mq();
	client_process -> type = 5555;
	client_process -> result = count;
	if(msgsnd(mq_msg_id[1], client_process, sizeof(struct client_pro_data_mq),0) == -1){
		perror("msgsnd");
		exit("EXIT_FAILURE");
	}
	printf("Send data successfully\n");
	return 0;
}

int create_mq()
{
	static char index = 0;
	static uint32_t key = 965;
	mq_key[ index ] = key;
	mq_msg_id[index] = msgget(mq_key[index], 0666|IPC_CREAT);
	if( mq_msg_id[index] == -1){
		perror("msgget");
		exit("EXIT_FAILURE");
	}
	printf("value of index %d %d\n", index, key);
	index++;
	key++;
	return 0;
}


int detect_client( struct client_data_mq *client )
{
	int result;
	switch (client -> operand){
	
	case '+':
		result = client -> oper1 + client -> oper2;
	break;
	case '-':
		result = (( client + 1 ) -> oper1) - ((client + 1) -> oper2);
	break;
	
	}
	return result;
}
