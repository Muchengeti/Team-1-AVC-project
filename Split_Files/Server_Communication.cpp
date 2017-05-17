#include "Server_Communication.h"

void open_gate(){
	char addr[15] = {'1','3','0','.','1','9','5','.','6','.','1','9','6'};
	connect_to_server(addr, 1024);
	char to_serv[24]={'P','l','e','a','s','e',0};
	send_to_server(to_serv);
	char from_serv[19];
	receive_from_server(from_serv);
	for(int length = 0; length < 6; length++){
		to_serv[length] = from_serv[length];
	}
	send_to_server(to_serv);
	sleep1(0,500000); 
}
