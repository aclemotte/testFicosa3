

#include <stdio.h>
#include <stdlib.h>

/* Definitions */
typedef enum eEvent
{
	EVENT1,
	EVENT2,
	NUM_OF_EVENTS
} tevent;

typedef struct{
	tevent		event_id;
	unsigned char 	param[2];
} tCommand;

#define MAX_NUM_COMMANDS 10
tCommand  commandBuffer[MAX_NUM_COMMANDS];
int front = -1, rear =-1;


int isFull()
{
    if((front == rear + 1) || (front == 0 && rear == MAX_NUM_COMMANDS-1))
    	return 1;
    return 0;
}

int isEmpty()
{
    if(front == -1)
    	return 1;
    return 0;
}

void SetCommand (tevent commandNum, unsigned char *data)
{
	/* Insert command into the circular buffer to store received commands */
	// ADD YOUR C CODE HERE
	if(isFull())
		printf("\n Queue is full!! \n");
	else
	{
		if(front == -1)
			front = 0;
		rear = (rear + 1) % MAX_NUM_COMMANDS;
		//items[rear] = element;
		commandBuffer[rear].event_id = commandNum;
		commandBuffer[rear].param[0] = *(data+0);
		commandBuffer[rear].param[1] = *(data+1);
		printf("Inserted -> event_id:%d, data[0]:%d, data[1]:%d\n", commandBuffer[rear].event_id, commandBuffer[rear].param[0], commandBuffer[rear].param[1]);
	}
}

void GetCommand (tCommand *command)
{
	/* Extract command from circular buffer and fill command */
	// ADD YOUR C CODE HERE
	tCommand element;
    if(isEmpty())
    {
        printf("\n Queue is empty !! \n");
        return;
    }
    else
    {
        element = commandBuffer[front];
        if (front == rear)
        {
            front = -1;
            rear = -1;
        } /* Q has only one element, so we reset the queue after dequeing it. */
        else
        {
            front = (front + 1) % MAX_NUM_COMMANDS;

        }
        printf("Deleted -> event_id:%d, data[0]:%d, data[1]:%d\n", element.event_id, element.param[0], element.param[1]);
        return;
    }
}

int main(void) {

	unsigned char data[2];
	tCommand receivedCommand;

	/* Send first command */
	data [0]  = 0x01;
	data [1]  = 0x02;
	SetCommand(EVENT1, data);


	/* Send second command */
	data [0]  = 0x03;
	data [1]  = 0x04;
	SetCommand(EVENT2, data);

	/* Receive first command */
	GetCommand(&receivedCommand);
	/* Command is processed */

	/* Receive second command */
	GetCommand(&receivedCommand);
	/* Command is processed */

	return EXIT_SUCCESS;
}
