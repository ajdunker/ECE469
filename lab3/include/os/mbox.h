#ifndef __MBOX_OS__
#define __MBOX_OS__

#define MBOX_NUM_MBOXES 16           // Maximum number of mailboxes allowed in the system
#define MBOX_NUM_BUFFERS 50          // Maximum number of message buffers allowed in the system
#define MBOX_MAX_BUFFERS_PER_MBOX 10 // Maximum number of buffer slots available to any given mailbox
#define MBOX_MAX_MESSAGE_LENGTH 100   // Buffer size of 100 for each message

#define MBOX_FAIL -1
#define MBOX_SUCCESS 1

//---------------------------------------------
// Define your mailbox structures here
//--------------------------------------------

typedef struct mbox_message {
	char message[MBOX_MAX_MESSAGE_LENGTH];
	int msize;
	uint32 inuse;
} mbox_message;

typedef struct mbox {
 	uint32 inuse;
 	int pids[PROCESS_MAX_PROCS]; 	
 	int used;						// A counter (used) to track number of processes that have opened the mailbox 
 	int count;						// A counter (count) to track number of variable length, queued messages 
 	Queue msg;
	// Synchronization Variables
 	//A lock (l) and two condition variables (moreSpace and moreData) for producers and consumers to wait on 
 	lock_t l;						// lock for the mbox
 	sem_t s_empty;				// moreSpace: producer’s message doesn’t fit it waits on moreSpace 
 	sem_t s_full;					// moreData: consumer finds no messages it waits on moreData
} mbox;

typedef int mbox_t; // This is the "type" of mailbox handles

//-------------------------------------------
// Prototypes for Mbox functions you have to write
//-------------------------------------------

void MboxModuleInit();
mbox_t MboxCreate();
int MboxOpen(mbox_t m);
int MboxClose(mbox_t m);
int MboxSend(mbox_t m, int length, void *message);
int MboxRecv(mbox_t m, int maxlength, void *message);
int MboxCloseAllByPid(int pid);

#ifndef false
#define false 0
#endif

#ifndef true
#define true 1
#endif

#endif
