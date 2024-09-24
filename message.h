#include <sys/types.h>

typedef struct {
    long msgType ;            /* 1: request , 2: reply , etc. */
    struct {
        pid_t sender ;         /* PID of sending process */
        int  num1, num2 ;      /* two operands */
        char operation ;       /* arithmetic operation '+' , '-' , 'x' , '/' */
        int result ;           /* result of  num1 operation num2 */
    } body ;
} msgBuf ;

#define MSG_INFO_SIZE ( sizeof(msgBuf) - sizeof(long) )

#define BASE_MAILBOX_NAME 0x300

void printMsg( msgBuf *m ) ;

