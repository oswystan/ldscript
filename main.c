/*
 **************************************************************************************
 *       Filename:  main.c
 *    Description:   source file
 *
 *        Version:  1.0
 *        Created:  2016-12-22 15:42:29
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */

#include <stdio.h>

typedef struct _initcall_t { 
    int (*init)();
    void (*exit)();
} initcall_t;

#define __section(s) __attribute__((__section__(#s)))

#define CORE_INIT(c, d) __section(._local_init.1) \
    static initcall_t __init_call_1_##c##_##d = {\
        .init = c,\
        .exit = d,\
    }

#define MODULE_INIT(c, d) __section(._local_init.2) \
    static initcall_t __init_call_2_##c##_##d = {\
        .init = c,\
        .exit = d,\
    }
extern char g_initcall_start[];
extern char g_initcall_end[];

int core_init() {
    printf("enter %s\n", __func__);
}
void core_exit() {
    printf("enter %s\n", __func__);
}
int module_init() {
    printf("enter %s\n", __func__);
}
void module_exit() {
    printf("enter %s\n", __func__);
}

int sys_init() {
    printf("enter %s\n", __func__);
}
void sys_exit() {
    printf("enter %s\n", __func__);
}
MODULE_INIT(module_init, module_exit);
MODULE_INIT(sys_init, sys_exit);
CORE_INIT(core_init, core_exit);

void __attribute((constructor)) my_init() {
    initcall_t* ic = (initcall_t*)g_initcall_start;                    
    int cnt = (g_initcall_end - g_initcall_start) / sizeof(initcall_t);
    int i = 0;                                                         
    for (i = 0; i < cnt; i++) {                                        
        (*ic[i].init)();                                               
    }                                                                  
    printf("before main\n");
}
void __attribute((destructor)) my_exit() {
    initcall_t* ic = (initcall_t*)g_initcall_start;                    
    int cnt = (g_initcall_end - g_initcall_start) / sizeof(initcall_t);
    int i = 0;                                                         
    for (i = cnt-1; i >=0 ; i--) {                                        
        (*ic[i].exit)();                                               
    }                                                                  
    printf("after main\n");
}

int main(int argc, const char *argv[]) {
    printf("================================\n");
    printf("this is main\n");
    printf("================================\n");
    return 0;
}

/********************************** END **********************************************/

