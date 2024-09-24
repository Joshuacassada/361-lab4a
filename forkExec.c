/*
    CS-361 Demo of fork() + waitpid() and execl() with fixed-value arguments  
*/

#include <stdio.h>      // fprintf()
#include <unistd.h>     // fork(), exec*()
#include <sys/types.h>  // wait(), waitpid()
#include <sys/wait.h>   // wait(), waitpid()
#include <unistd.h>

int main( int argc, char **argv)
{
    // we only have one process at this point
    printf( "\t### parent: no children yet\n" );

    // use fork to create a copy of this code
    pid_t childPID;

    childPID = fork();

    switch ( childPID )
    {    // first check for an error
        case -1:
            printf( "Failed to create child process\n" );
            return -1;
            
        case  0:
            // I am the child, so do the child stuff
            printf( "\t\t*** child: childPID = %d\n" , childPID );
            char *arg = "Calculator";
            double principle, rate;
            int amount, year;

            printf("principle: ");
            scanf("%lf", &principle);

            printf("interestRate: ");
            scanf("%lf", &rate);

            printf("number of compounds: ");
            scanf("%d", &amount);

            printf("years: ");
            scanf("%d", &year);
            char argp[25];
            char argr[25];
            char arga[25];
            char argy[25];
            snprintf(argp, sizeof(argp), "%lf", principle);
            snprintf(argr, sizeof(argr), "%lf", rate);
            snprintf(arga, sizeof(arga), "%d", amount);
            snprintf(argy, sizeof(argy), "%d", year);

            // Overwrite the child's inherited image with a new executable. Pass fixed args. 
            if( execl( "./investCalc" , arg , argp , argr , arga ,  argy , NULL ) < 0 )
                perror("Mohamed ");

            // we should never get to here unless the exec*() failed
            printf( "\t\t*** child: The execl() failed\n" );
            break ;
            
        default:
            // I am the parent, so do the parent stuff
            printf( "\t### parent: childPID = %d\n" , childPID );

            // be sure to wait for the child to exit or you might create a zombie
            int status;
            printf( "\t### parent: waiting for child to complete execution and exit\n" );

            // read the man page on waitpid() to see how to make it do different things
            if ( waitpid( childPID, &status, 0 ) < 0 )   
            {
                printf( "\tparent: failed in waitpid() for child %d\n" , childPID );
                return -1;
            }
            
            printf( "\n\t### parent: child returned with %d\n" , WEXITSTATUS( status ) );
		    
    }

    printf( "\n\nWho am I?  (HINT: my value of childPID = %d\n", childPID );

    return 0;
}



