#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include <iostream>
#include "msg.h"    /* For the message struct */

using namespace std;

/* The size of the shared memory chunk */
#define SHARED_MEMORY_CHUNK_SIZE 1000

/* The ids for the shared memory segment and the message queue */
int shmid, msqid;
int exitCounter = 9;

/* The pointer to the shared memory */
void *sharedMemPtr;

/* The name of the received file */
const char recvFileName[] = "recvfile";


/**
 * Sets up the shared memory segment and message queue
 * @param shmid - the id of the allocated shared memory
 * @param msqid - the id of the shared memory
 * @param sharedMemPtr - the pointer to the shared memory
 */

void init(int& shmid, int& msqid, void*& sharedMemPtr)
{




	/* TODO: 1. Create a file called keyfile.txt containing string "Hello world" (you may do
 		    so manually or from the code).
	         2. Use ftok("keyfile.txt", 'a') in order to generate the key.
		 3. Use the key in the TODO's below. Use the same key for the queue
		    and the shared memory segment. This also serves to illustrate the difference
		    between the key and the id used in message queues and shared memory. The id
		    for any System V object (i.e. message queues, shared memory, and sempahores)
		    is unique system-wide among all System V objects. Two objects, on the other hand,
		    may have the same key.
	 */


 	//System call to return a key from keyfile.txt which contains "Hello World"
 	 key_t key_for_mem = ftok("keyfile.txt", 'a');

 	 //cout << key_for_mem << endl;

	/* TODO: Allocate a piece of shared memory. The size of the segment must be SHARED_MEMORY_CHUNK_SIZE. */
    shmid = shmget(key_for_mem, SHARED_MEMORY_CHUNK_SIZE, 0666 | IPC_CREAT);

	 if(shmid == -1 ){
     perror("shmget");
     exit(1);
   }


	/* Store the IDs and the pointer to the shared memory region in the corresponding parameters */

  msqid = msgget(key_for_mem, 0666 | IPC_CREAT);
 if(msqid == -1){
   perror("msgget");
   exit(1);
 }
	/* TODO: Attach to the shared memory */

	sharedMemPtr = shmat(shmid, (void *)0, 0);

  if(sharedMemPtr == (char *)(-1)){
    perror("shmat");
    exit(1);
  }


	/* TODO: Create a message queue */
	//Attach to the message queue






}


/**
 * The main loop
 */
void mainLoop()
{
	/* The size of the mesage */
	int msgSize = 0;
  message MyKeyFileMessage;
	/* Open the file for writing */
	FILE* fp = fopen(recvFileName, "w");

	/* Error checks */
	if(!fp)
	{
		perror("fopen");
		exit(-1);
	}
    /* TODO: Receive the message and get the message size. The message will
     * contain regular information. The message will be of SENDER_DATA_TYPE
     * (the macro SENDER_DATA_TYPE is defined in msg.h).  If the size field
     * of the message is not 0, then we copy that many bytes from the shared
     * memory region to the file. Otherwise, if 0, then we close the file and
     * exit.
     *
     * NOTE: the received file will always be saved into the file called
     * "recvfile"
     */


		 //From header file "msg.h"


		 if(msgrcv(msqid, &MyKeyFileMessage, sizeof(message),SENDER_DATA_TYPE, 0) == -1){
       perror("msgrcv");
       fclose(fp);
       exit(1);
     }
////////////////////////////////////////////////////////////////////////////////////////////
		 msgSize = MyKeyFileMessage.size; //Added
		 /* Keep receiving until the sender set the size to 0, indicating that
		  * there is no more data to send
		  */

	while(msgSize != 0)
	{
		/* If the sender is not telling us that we are done, then get to work */
		if(msgSize != 0)
		{
			/* Save the shared memory to file */
			if(fwrite(sharedMemPtr, sizeof(char), msgSize, fp) < 0)
			{
				perror("fwrite");
			}

			/* TODO: Tell the sender that we are ready for the next file chunk.
 			 * I.e. send a message of type RECV_DONE_TYPE (the value of size field
 			 * does not matter in this case).
 			 */
			 MyKeyFileMessage.mtype=RECV_DONE_TYPE;


       if(msgsnd(msqid,&MyKeyFileMessage,0,0) == -1){
         perror("msgsnd");
         exit(1);
       }

       if(msgrcv(msqid, &MyKeyFileMessage, sizeof(message) - 8, SENDER_DATA_TYPE, 0) == -1){
         perror("msgrcv");
         exit(1);
       }
			 msgSize = MyKeyFileMessage.size;

		}
		/* We are done */
		else
		{
			/* Close the file */
			fclose(fp);
		}
	}
}



/**
 * Perfoms the cleanup functions
 * @param sharedMemPtr - the pointer to the shared memory
 * @param shmid - the id of the shared memory segment
 * @param msqid - the id of the message queue
 */

void cleanUp(const int& shmid, const int& msqid, void* sharedMemPtr)
{
	/* TODO: Detach from shared memory */

	shmdt(sharedMemPtr);

	/* TODO: Deallocate the shared memory chunk */
	//Mark segment to be destroyed (IPC_RMID)
	shmctl(shmid, IPC_RMID, NULL);
	/* TODO: Deallocate the message queue */
	msgctl(msqid, IPC_RMID, NULL);
}

/**
 * Handles the exit signal
 * @param signal - the signal type
 */


void ctrlCSignal(int signal)
{
	/* Free system V resources */

  if(exitCounter > 0){
    fprintf(stderr, "Haha I have %d lives!\n", exitCounter);
  }else{
    fprintf(stderr, "Ahh you got me!\n");
    exit(0);
  }

  --exitCounter;
  cleanUp(shmid, msqid, sharedMemPtr);
}



int main()
{

	/* TODO: Install a singnal handler (see signaldemo.cpp sample file).
 	 * In a case user presses Ctrl-c your program should delete message
 	 * queues and shared memory before exiting. You may add the cleaning functionality
 	 * in ctrlCSignal().
 	 */

	 signal(SIGINT, ctrlCSignal);

	/* Initialize */
	init(shmid, msqid, sharedMemPtr);

	/* Go to the main loop */
	mainLoop();

	/** TODO: Detach from shared memory segment, and deallocate shared memory and message queue (i.e. call cleanup) **/
	cleanUp(shmid, msqid, sharedMemPtr);
	cout << "DONE" << endl;
	return 0;
}
