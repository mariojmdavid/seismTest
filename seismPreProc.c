/*
 * Name        : seismPreProc.c
 * Author      : Mario David <mariojmdavid@gmail.com
 * Version     :
 * Copyright   : ...
 * Description : Pre-processing of traces
 *
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/stat.h>

/*
 * Program to pre process traces
 */

void print_usage() {
    printf("Usage: seismPreProc -c <CONF_FILE> -i num -n num\n");
}

int fileexists(const char* filename){
    struct stat buffer;
    int exist = stat(filename, &buffer);
    if(exist == 0)
        return 1;
    else // -1
        return 0;
}

int main(int argc, char *argv[]) {
	setvbuf(stdout, NULL, _IONBF, 0); // to solve bug in eclipse console on win8
	setvbuf(stderr, NULL, _IONBF, 0);

    int option = 0;
    char *conf = "traces.conf";
    int inst = 1, nsub = 1;

    while ((option = getopt(argc, argv,"c:i:n:")) != -1) {
        switch (option) {
             case 'c': conf = optarg;
                 break;
             case 'i': inst = atoi(optarg);
                 break;
             case 'n': nsub = atoi(optarg);
                 break;
             default: print_usage();
                 exit(EXIT_FAILURE);
        }
    }

    // Check if conf file exists
    if(fileexists(conf))
    	printf("Configuration file: %s\n", conf);
    else
    {
    	printf("Configuration file %s not found\n", conf);
    	exit(EXIT_FAILURE);
    }

    printf("Instance number: %d\n", inst);
    printf("Number of submissions: %d\n", nsub);

    return 0;
}
