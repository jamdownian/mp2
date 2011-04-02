#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sys/wait.h>

#define PORT 29384

using namespace std;

// function definitions
int main(int argc, char ** argv);
pid_t launchListener(int port);
pid_t launchIntroducer(int m, int port);

pid_t launchListener(int port){
    pid_t pid = fork();

    // a 16-bit number will be at most 5 characters
    char portString[6] = {0};
    sprintf(portString, "%d", port);

    if( pid == 0 ){
        // launch listener process
        execlp("./listener", "./listener", "localhost", portString, (char *)0 );
    } 

    return pid;
}

pid_t launchIntroducer(int m, int port){
    pid_t pid = fork();

    // a 16-bit number will be at most 5 characters
    char portString[6] = {0};
    sprintf(portString, "%d", port);

    char mString[6] = {0};
    sprintf(mString, "%d", m);

    if( pid == 0 ){
        // launch listener process
        execlp("./introducer", "./introducer", mString, portString, (char *)0 );
    } 

    return pid;
}

int main(int argc, char ** argv){

    if( argc != 2){
       cerr << "Usage: " << argv[0] << " <m (#bits)>" << endl;
       return EXIT_FAILURE;
    }

    int m = atoi(argv[1]);

    // launch the listener process
    launchListener(PORT);
    launchIntroducer(m, PORT);

    // wait for the processes to quit
    int status;
    wait(&status);
    wait(&status);

    return EXIT_SUCCESS;
}