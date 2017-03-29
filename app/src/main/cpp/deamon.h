//
// Created by MrBu on 2015/12/18.
//

#ifndef BEEPER_ANDROID_LIB_ENCRYPTER_H
#define BEEPER_ANDROID_LIB_ENCRYPTER_H
#include <jni.h>
#include <android/log.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <sys/time.h>

#include <unistd.h>
#include <sys/resource.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <pthread.h>

#define LOG_TAG "<<Native>>"
//#define PROC_DIRECTORY "/proc/"
//#define CASE_SENSITIVE    1
//#define CASE_INSENSITIVE  0
//#define EXACT_MATCH       1
//#define INEXACT_MATCH     0
//#define MAX_LINE_LEN 5
#define DEBUG
void voidMethod(...);
#ifdef DEBUG
    #define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#endif
#ifndef DEBUG
    #define LOGE(...) voidMethod(__VA_ARGS__);
#endif
int start(int argc, char* srvname, char* sd);
void check_and_restart_service(char* service);
void ExecuteCommandWithPopen(char* command, char* out_result,int resultBufferSize);
#endif //BEEPER_ANDROID_LIB_ENCRYPTER_H
