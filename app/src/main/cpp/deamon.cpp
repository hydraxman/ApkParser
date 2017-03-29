//
// Created by MrBu on 2015/12/18.
//
#include "deamon.h"

/**
* 方法
*/
JavaVM *gVM;
JNIEnv *g_env = NULL;
#define JNIREG_CLASS "com/bushaopeng/android/apkparser/MainActivity"

//======================================================================
char *jstringTostr(JNIEnv *env, jstring jstr) {
    char *rtn = NULL;
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("utf-8");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid, strencode);
    jsize alen = env->GetArrayLength(barr);
    jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char *) malloc(alen + 1);
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    env->ReleaseByteArrayElements(barr, ba, 0);
    return rtn;
}

char *jstringToChar(JNIEnv *env, jstring jstr) {
    const char *constUrlChar = env->GetStringUTFChars(jstr, 0);
    char *result = new char[strlen(constUrlChar) + 1];
    strcpy(result, constUrlChar);
    env->ReleaseStringUTFChars(jstr, constUrlChar);
    return result;
}

void thread(void *service_name) {
    LOGE(" thread ");
    while (1) {
        check_and_restart_service((char *) service_name); // 应该要去判断service状态，这里一直restart 是不足之处
        LOGE(" looping ");
        sleep(4);
    }
}

/**
* 检测服务，如果不存在服务则启动.
* 通过am命令启动一个laucher服务,由laucher服务负责进行主服务的检测,laucher服务在检测后自动退出
*/
void check_and_restart_service(char *service) {
    LOGE("当前所在的进程pid=", getpid());
    char cmdline[200];
    sprintf(cmdline, "am startservice --user 0 -n %s", service);
    char tmp[200];
    sprintf(tmp, "cmd=%s", cmdline);
    LOGE("当前所在的进程pid=", getpid());
    ExecuteCommandWithPopen(cmdline, tmp, 200);
    LOGE(tmp, " deamon ");
}

/**
* 执行命令
*/
void ExecuteCommandWithPopen(char *command, char *out_result,
                             int resultBufferSize) {
    FILE *fp;
    out_result[resultBufferSize - 1] = '\0';
    LOGE("22 22,so exit %s ", command);
    fp = popen(command, "r");
    LOGE("11 1,so 111");
    if (fp) {
        fgets(out_result, resultBufferSize - 1, fp);
        out_result[resultBufferSize - 1] = '\0';
        pclose(fp);
    } else {
        LOGE("popen null,so exit");
        exit(0);
    }
}

/**
* srvname  进程名
* sd 之前创建子进程的pid写入的文件路径
*/
int start(int argc, char *service_name, char *sd) {
    pthread_t id;
    int ret;
    struct rlimit r;

    int pid = fork();
    LOGE("fork pid: %d", pid);
    if (pid < 0) {
        LOGE("first fork() error pid %d,so exit", pid);
        exit(0);
    } else if (pid != 0) {
        LOGE("first fork(): I'am father pid=%d", getpid());
        //exit(0);
    } else { //  第一个子进程
        LOGE("first fork(): I'am child pid=%d", getpid());
        setsid();
        LOGE("first fork(): setsid=%d", setsid());
        umask(0); //为文件赋予更多的权限，因为继承来的文件可能某些权限被屏蔽
        pid = fork();
        if (pid == 0) { // 第二个子进程
            // 这里实际上为了防止重复开启线程，应该要有相应处理

            LOGE("I'am child-child pid=%d", getpid());
//            chdir("/"); //修改进程工作目录为根目录，chdir(“/”)
            //关闭不需要的从父进程继承过来的文件描述符。
            if (r.rlim_max == RLIM_INFINITY) {
                r.rlim_max = 1024;
            }
            LOGE("2 I'am child-child pid=%d", getpid());
//            int i;
//            for (i = 0; i < r.rlim_max; i++) {
//                close(i);
//            }
            LOGE("2 I'am child-child pid=%d", getpid());
            umask(0);
            ret = pthread_create(&id, NULL, (void *(*)(void *)) thread,
                                 service_name); // 开启线程，轮询去监听启动服务
            if (ret != 0) {
                LOGE("Create pthread error!\n");
                exit(1);
            } else {
                LOGE("Create pthread success!\n");
            }
            int stdfd = open("/dev/null", O_RDWR);
            dup2(stdfd, STDOUT_FILENO);
            dup2(stdfd, STDERR_FILENO);
            LOGE("dup2 pthread success!\n");
        } else {
            exit(0);
        }
    }
    return 0;
}

/**
* 启动Service
*/
int startService(JNIEnv *env, jobject thiz,
                 jstring processName, jstring sdpath) {
    char *service_name = jstringToChar(env, processName); // 得到进程名称
    char *sd = jstringToChar(env, sdpath);
    LOGE("startService run....ProcessName:%s", service_name);
    return start(1, service_name, sd);
}


static JNINativeMethod gMethods[] = {
        {"startService", "(Ljava/lang/String;Ljava/lang/String;)I", (void *) startService}
};


/*
* 注册本地
*/
static int registerNativeMethods(JNIEnv *env, const char *className,
                                 JNINativeMethod *gMethods, int numMethods) {
    jclass clazz;
    clazz = env->FindClass(className);
    if (clazz == NULL) {
        return JNI_FALSE;
    }
    if (env->RegisterNatives(clazz, gMethods, numMethods) < 0) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}


/*
* 注册
*/
static int registerNatives(JNIEnv *env) {
    if (!registerNativeMethods(env, JNIREG_CLASS, gMethods,
                               sizeof(gMethods) / sizeof(gMethods[0])))
        return JNI_FALSE;

    return JNI_TRUE;
}

/**
 * 加载时
 */
JNIEXPORT jint

JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    LOGE("JNI_OnLoad");
    JNIEnv *env = NULL;
    jint result = -1;
    gVM = vm;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
        return -1;
    }
    if (!registerNatives(env)) {
        LOGE("JNI_OnLoad_REG_FAIL");
        return -1;
    }
    LOGE("JNI_OnLoad_REG_SUCC");
    /* success -- return valid version number */
    result = JNI_VERSION_1_4;
    g_env = env;
    return result;
}

void voidMethod(...) {

}