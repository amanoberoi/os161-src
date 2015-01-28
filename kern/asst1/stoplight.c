/* 
 * stoplight.c
 *
 * 31-1-2003 : GWA : Stub functions created for CS161 Asst1.
 *
 * NB: You can use any synchronization primitives available to solve
 * the stoplight problem in this file.
 */


/*
 * 
 * Includes
 *
 */

#include <types.h>
#include <lib.h>
#include <test.h>
#include <thread.h>
#include <synch.h>


/*
 *
 * Constants
 *
 */

/*
 * Number of cars created.
 */

#define NCARS 20
static struct lock *lock0;
static struct lock *lock1;
static struct lock *lock2;
static struct lock *lock3;
int count;


/*
 *
 * Function Definitions
 *
 */

 
static const char *directions[] = { "N", "E", "S", "W" };

static const char *msgs[] = {
        "APPROACHING:",
        "region0:    ",
        "region1:    ",
        "region2:    ",
		"region3:    ",
        "LEAVING:    "
};

/* use these constants for the first parameter of message */
enum { APPROACHING, REGION1, REGION2, REGION3, LEAVING };

static void
message(int msg_no, int carnumber, int cardirection, int destdirection)
{
        kprintf("%s car = %2d, direction = %s, destination = %s\n",
                msgs[msg_no], carnumber,
                directions[cardirection], directions[destdirection]);
}
 

/*
 * gostraight()
 *
 * Arguments:
 *      unsigned long cardirection: the direction from which the car
 *              approaches the intersection.
 *      unsigned long carnumber: the car id number for printing purposes.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      This function should implement passing straight through the
 *      intersection from any direction.
 *      Write and comment this function.
 */

static
void
gostraight(unsigned long cardirection,
           unsigned long carnumber,
		   unsigned long destdirection)
{	
        
		int lockrequired[2];
		int acquiredAll;
		//Checking the number of locks required
		lockrequired[0]=cardirection;
		if (cardirection==0){
		lockrequired[1]=cardirection+3;
		}
		else{
		lockrequired[1]=cardirection-1;
		}
		
		message(0,carnumber,cardirection,destdirection);
		//if N to S
		do{
		if(lockrequired[0]==0 && lockrequired[1]==3)
		{
		if(lock0->owner==NULL)
		{
		lock_acquire(lock0);
		assert(lock_do_i_hold(lock0));
		if(lock3->owner==NULL)
		{
		 lock_acquire(lock3);
		 assert(lock_do_i_hold(lock3));
		 message(1,carnumber,cardirection,destdirection);
		 message(4,carnumber,cardirection,destdirection);
		 lock_release(lock0);
		 lock_release(lock3);
		 acquiredAll=2;
		}
		else lock_release(lock0);
		}}
		
		//if S to N
		else if(lockrequired[0]==2 && lockrequired[1]==1)
		{if(lock2->owner==NULL)
		{
		lock_acquire(lock2);
		assert(lock_do_i_hold(lock2));
		if(lock1->owner==NULL)
		{
		 lock_acquire(lock1);
		 assert(lock_do_i_hold(lock1));
		 message(3,carnumber,cardirection,destdirection);
		 message(2,carnumber,cardirection,destdirection);
		 lock_release(lock2);
		 lock_release(lock1);
		 acquiredAll=2;
		}
		else lock_release(lock2);
		}
		}
		
		//if W to E
		else if(lockrequired[0]==0 && lockrequired[1]==1)
		{
		 if(lock0->owner==NULL)
		{
		lock_acquire(lock0);
		assert(lock_do_i_hold(lock0));
		if(lock1->owner==NULL)
		{
		 lock_acquire(lock1);
		 assert(lock_do_i_hold(lock1));
		 message(1,carnumber,cardirection,destdirection);
		 message(2,carnumber,cardirection,destdirection);
		 lock_release(lock0);
		 lock_release(lock1);
		 acquiredAll=2;
		}
		else lock_release(lock0);
		}}
		
		// if E to W
		else
		{if(lock2->owner==NULL)
		{
		lock_acquire(lock2);
		assert(lock_do_i_hold(lock2));
		if(lock3->owner==NULL)
		{
		 lock_acquire(lock3);
		 assert(lock_do_i_hold(lock3));
		 message(3,carnumber,cardirection,destdirection);
		 message(4,carnumber,cardirection,destdirection);
		 lock_release(lock2);
		 lock_release(lock3);
		 acquiredAll=2;
		}
		else lock_release(lock2);
		}
		}
		}while(acquiredAll!=2);
		message(5,carnumber,cardirection,destdirection);
		count--;
		
}


/*
 * turnleft()
 *
 * Arguments:
 *      unsigned long cardirection: the direction from which the car
 *              approaches the intersection.
 *      unsigned long carnumber: the car id number for printing purposes.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      This function should implement making a left turn through the 
 *      intersection from any direction.
 *      Write and comment this function.
 */

static
void
turnleft(unsigned long cardirection,
         unsigned long carnumber,
		 unsigned long destdirection)
{
        /*
         * Avoid unused variable warnings.
         */

		int lockrequired[3];
		int acquiredAll;
		lockrequired[0]=cardirection;
		
		//Checking the number of locks required
		if (cardirection==0){
		lockrequired[1]=3;
		}
		else{
		lockrequired[1]=cardirection-1;
		}
		if (lockrequired[1]==0){
		lockrequired[2]=3;
		}
		else{
		lockrequired[2]=lockrequired[1]-1;
		}
		
		message(0,carnumber,cardirection,destdirection);
		do{
		
		// if N to E
		if(lockrequired[0]==0 && lockrequired[1]==3 && lockrequired[2]==2)
		{
		if(lock0->owner==NULL)
		{
		lock_acquire(lock0);
		assert(lock_do_i_hold(lock0));
		if(lock3->owner==NULL)
		{
		 lock_acquire(lock3);
		 assert(lock_do_i_hold(lock3));
		 if(lock2->owner==NULL)
		{
		 lock_acquire(lock2);
		 assert(lock_do_i_hold(lock2));
		 message(1,carnumber,cardirection,destdirection);
		 message(4,carnumber,cardirection,destdirection);
		 message(3,carnumber,cardirection,destdirection);
		 lock_release(lock0);
		 lock_release(lock3);
		 lock_release(lock2);
		 acquiredAll=3;
		 }
		 else{
		 lock_release(lock0);
		 lock_release(lock3);
		 }
		}
		else lock_release(lock0);
		}
		}
		
		// if S to W
		else if(lockrequired[0]==2 && lockrequired[1]==1&& lockrequired[2]==0)
		{if(lock2->owner==NULL)
		{
		lock_acquire(lock2);
		assert(lock_do_i_hold(lock2));
		if(lock1->owner==NULL)
		{
		 lock_acquire(lock1);
		 assert(lock_do_i_hold(lock1));
		 if(lock0->owner==NULL)
		{
		 lock_acquire(lock0);
		 assert(lock_do_i_hold(lock0));
		 message(3,carnumber,cardirection,destdirection);
		 message(2,carnumber,cardirection,destdirection);
		 message(1,carnumber,cardirection,destdirection);
		 lock_release(lock2);
		 lock_release(lock1);
		 lock_release(lock0);
		 acquiredAll=3;
		 }
		 else{
		 lock_release(lock2);
		 lock_release(lock1);
		 }
		}
		else lock_release(lock2);
		}
		}
		
		//if E to S
		else if(lockrequired[0]==1 && lockrequired[1]==0&& lockrequired[2]==3)
		{
		 if(lock1->owner==NULL)
		{
		lock_acquire(lock1);
		assert(lock_do_i_hold(lock1));
		if(lock0->owner==NULL)
		{
		 lock_acquire(lock0);
		 assert(lock_do_i_hold(lock0));
		 if(lock3->owner==NULL)
		{
		 lock_acquire(lock3);
		 assert(lock_do_i_hold(lock3));
		 message(2,carnumber,cardirection,destdirection);
		 message(1,carnumber,cardirection,destdirection);
		 message(4,carnumber,cardirection,destdirection);
		 lock_release(lock1);
		 lock_release(lock0);
		 lock_release(lock3);
		 acquiredAll=3;
		 }
		 else{
		 lock_release(lock1);
		 lock_release(lock0);
		 }
		}
		else lock_release(lock1);
		}
		}
		
		//if W to N
		else
		{
		if(lock3->owner==NULL)
		{
		lock_acquire(lock3);
		assert(lock_do_i_hold(lock3));
		if(lock2->owner==NULL)
		{
		 lock_acquire(lock2);
		 assert(lock_do_i_hold(lock2));
		 if(lock1->owner==NULL)
		{
		 lock_acquire(lock1);
		 assert(lock_do_i_hold(lock1));
		 message(4,carnumber,cardirection,destdirection);
		 message(3,carnumber,cardirection,destdirection);
		 message(2,carnumber,cardirection,destdirection);
		 lock_release(lock3);
		 lock_release(lock2);
		 lock_release(lock1);
		 acquiredAll=3;
		 }
		 else{
		 lock_release(lock3);
		 lock_release(lock2);
		 }
		}
		else lock_release(lock3);
		}
		}
		}while(acquiredAll!=3);	//while loop till you get all three locks else release all locks
		
		message(5,carnumber,cardirection,destdirection);
		count--;
		
} //end of turnleft


/*
 * turnright()
 *
 * Arguments:
 *      unsigned long cardirection: the direction from which the car
 *              approaches the intersection.
 *      unsigned long carnumber: the car id number for printing purposes.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      This function should implement making a right turn through the 
 *      intersection from any direction.
 *      Write and comment this function.
 */

static void turnright(unsigned long cardirection, unsigned long carnumber,  unsigned long destdirection){
        /*
         * Avoid unused variable warnings.
         */

		int lockrequired;
		lockrequired=cardirection;
		message(0,carnumber,cardirection,destdirection);
		//checking for locks required and then acquiring them, after use releasing them
		if(lockrequired==0)
		{
		lock_acquire(lock0);
		assert(lock_do_i_hold(lock0)==1);
		message(1,carnumber,cardirection,destdirection);
		lock_release(lock0);
		}
		else if(lockrequired==1)
		{
		lock_acquire(lock1);
		assert(lock_do_i_hold(lock1)==1);
		message(2,carnumber,cardirection,destdirection);
		lock_release(lock1);
		}
		else if(lockrequired==2)
		{
		lock_acquire(lock2);
		assert(lock_do_i_hold(lock2)==1);
		message(3,carnumber,cardirection,destdirection);
		lock_release(lock2);
		}
		else
		{
		lock_acquire(lock3);
		assert(lock_do_i_hold(lock3)==1);
		message(4,carnumber,cardirection,destdirection);
		lock_release(lock3);
		}
		message(5,carnumber,cardirection,destdirection);
		count--;
		
}

/*
 * approachintersection()
 *
 * Arguments: 
 *      void * unusedpointer: currently unused.
 *      unsigned long carnumber: holds car id number.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      Change this function as necessary to implement your solution. These
 *      threads are created by createcars().  Each one must choose a direction
 *      randomly, approach the intersection, choose a turn randomly, and then
 *      complete that turn.  The code to choose a direction randomly is
 *      provided, the rest is left to you to implement.  Making a turn
 *      or going straight should be done by calling one of the functions
 *      above.
 */
 
static void approachintersection(void * unusedpointer, unsigned long carnumber)
{ 
		
        int cardirection;
		int destdirection;
		int car_no=carnumber;
		
        /*
         * Avoid unused variable and function warnings.
         */
		 
        (void) unusedpointer;
		
        /*
         * cardirection is set randomly.
         */

        cardirection = random() % 4;
		destdirection = random() % 3;
		destdirection = (cardirection + destdirection + 1) % 4;
		
		
		if(cardirection-destdirection==2 || destdirection-cardirection==2) //if car wants to go straight
		gostraight(cardirection,car_no,destdirection);
		else if(destdirection-cardirection==1 || cardirection-destdirection==3) //if car wants to turn left
		turnleft(cardirection,car_no,destdirection);
		else 																	//else the car wants to turn right
		turnright(cardirection,car_no,destdirection);
		
}


/*
 * createcars()
 *
 * Arguments:
 *      int nargs: unused.
 *      char ** args: unused.
 *
 * Returns:
 *      0 on success.
 *
 * Notes:
 *      Driver code to start up the approachintersection() threads.  You are
 *      free to modiy this code as necessary for your solution.
 */

int createcars(int nargs, char ** args)
{
        int index, error;
		count=NCARS;
        lock0 = lock_create("lock0");
		lock1=lock_create("lock1");
		lock2=lock_create("lock2");
		lock3=lock_create("lock3");
		
		
        /*
         * Avoid unused variable warnings.
         */

       (void) nargs;
        (void) args;

        /*
         * Start NCARS approachintersection() threads.
         */

        for (index = 0; index < NCARS; index++) {
				
                error = thread_fork("approachintersection thread",
                                    NULL,
                                    index,
                                    approachintersection,
                                    NULL
                                    );

                /*
                 * panic() on error.
                 */

                if (error) {
                        
                        panic("approachintersection: thread_fork failed: %s\n",strerror(error));
                }
				
        }
		while(1)
		{
		if(count==0)
		{
		lock_destroy(lock0);
		lock_destroy(lock1);
		lock_destroy(lock2);
		lock_destroy(lock3);
		kprintf("All locks destroyed. \n");
		break;
		}
		}
        return 0;
}
