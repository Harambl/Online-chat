#ifndef CMESSAGE_H
#define CMESSAGE_H

#define MAX_USERNAME_SIZE		128
#define MAX_MESSAGE_SIZE		256
#define MAX_TIME_SIZE			16

struct cMessage {
	char userName[MAX_USERNAME_SIZE];	
	char text[MAX_MESSAGE_SIZE];	
	char time[MAX_TIME_SIZE];	
};


#endif
