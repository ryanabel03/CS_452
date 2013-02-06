
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>

static void signal_handler(int);
int pid1, pid2, status;

int main( int argc, char *argv[] )
{
	//seed random generator 
	srand(time(NULL));
      
    if( signal( SIGUSR1, signal_handler) == SIG_ERR  )
    {
        printf("Pærent: Unable to create handler for SIGUSR1\n");
    }
    if( signal( SIGUSR2, signal_handler) == SIG_ERR  )
    {
        printf("Pærent: Unable to create handler for SIGUSR2\n");
    }	
	if(signal(SIGINT, signal_handler) == SIG_ERR )
	{
		printf("Parent: Unable to create handler for crl-c \n");
	}

    printf( "Parent pid: %d\n", pid1=getpid() );
	
    if( (pid2 = fork() ) == 0 )
    {			
		printf( "Child pid: %d\n", pid2 = getpid() );
		
		printf("Waiting...");
		fflush(stdout);
		
		while(1){ 
			
			int num = rand()%5;
			sleep(num);
			if(num%2){
				kill( pid1, SIGUSR1 );
			}
			else{
				kill( pid1, SIGUSR2 );
			}
			
		}
				
			
    }	
	
    wait(&status);
	
	return 0;
    
}

static void signal_handler(int signo)
{
	switch( signo )
    {
        //Signal is a SIGUSR1 
        case SIGUSR1:
            printf( "Process %d: received SIGUSR1 \n", getpid() );
            printf("Waiting...");
			fflush(stdout);
			break;
        
        // Signal is a SIGUSR2 
        case SIGUSR2:
            printf( "Process %d: received SIGUSR2 \n", getpid() );
            printf("Waiting...");
			fflush(stdout);
			break;
			
		//Exit
		case SIGINT:		
			kill(pid2, SIGTERM);
			printf("\nShutting down... <ENTER>\n");
			getchar();
			
			exit(0);			

        default:
		
            break;
				
    }

}