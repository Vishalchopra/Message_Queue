/* File: header.h
   Author: Vishal Chopra
   Date: 9-oct-2016
   Purpose: Include all the header files, define all the structure used in IPC mechanism and type def all the variable
*/


typedef int int32_t;
typedef unsigned int uint32_t;
//typedef char int16_t;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>


struct client_data_mq{
	long int type;
	int16_t operand;
	int32_t oper1, oper2;
};

struct client_pro_data_mq{
	long int type;
	int32_t result;
};
