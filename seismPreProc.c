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
#include <string.h>
#include <stddef.h>
#include <sys/stat.h>

/*
 * Program to pre process traces
 */


/*
 * The struct param and the readConf function have to go together
 */

typedef struct{
	char *datasetName;
	char *rootDirRaw;
	char *rootDirOut;
	char *outFormat;
	char *catType;
	char *summStr;
} param;

void readConf(const char* filename){
	char *ignore = " \t\n#[";
	char *delim = " =\n";
	char *key, *val;
	size_t flag;
	FILE *file = fopen ( filename, "r" );
    char lineR [256];
    param cfgPar;

    while ( fgets ( lineR, sizeof lineR, file ) != NULL ){
    	flag = strcspn( lineR, ignore );
    	if (flag){
    		key = strtok (lineR, delim);
    		val = strtok (NULL, delim);
    		if ( strcmp(key, "datasetName") == 0 ){
    			cfgPar.datasetName = val;
    			printf("Got dsName\n");
    		}
    		if ( strcmp(key, "rootDirRaw") == 0 ) cfgPar.rootDirRaw = val;
    		if ( strcmp(key, "rootDirOut") == 0 ) cfgPar.rootDirOut = val;
    		if ( strcmp(key, "outFormat") == 0 ) cfgPar.outFormat = val;
    		if ( strcmp(key, "catType") == 0 ) cfgPar.catType = val;
    		if ( strcmp(key, "summStr") == 0 ) cfgPar.summStr = val;
			printf("Key |%s|  Value |%s|   cfgPar |%s|\n", key, val, cfgPar.datasetName);
    	}
    }
	printf("\nThe value |%s|\n", cfgPar.datasetName);
	printf("The value |%s|\n", cfgPar.rootDirRaw);
	printf("The value |%s|\n", cfgPar.catType);

    fclose ( file );
}



void print_usage() {
    printf("Usage: seismPreProc -c <CONF_FILE> -i num -n num\n");
}

int fileExists(const char* filename){
    struct stat buffer;
    int exist = stat(filename, &buffer);
    if(exist == 0)
        return 1;
    else // -1
        return 0;
}


int main(int argc, char **argv) {
	// setvbuf(stdout, NULL, _IONBF, 0); // to solve bug in eclipse console on win8
	// setvbuf(stderr, NULL, _IONBF, 0);

    int option = 0;
    char *conf = "traces.conf";
    int inst = 1, nsub = 1;

    /* These lines go to a new function to read and parse the config */

    /* end read/parse */

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
    if(fileExists(conf)){
    	printf("Configuration file: %s\n", conf);
    	readConf(conf);
    } else {
    	printf("Configuration file %s not found\n", conf);
    	exit(EXIT_FAILURE);
    }


    printf("Instance number: %d\n", inst);
    printf("Number of submissions: %d\n", nsub);


    /* These lines go to a new function to read and parse the config */

    /* end read/parse */




    return (EXIT_SUCCESS);
}
