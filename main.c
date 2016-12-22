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

#define __ctors         __attribute__((constructor))
#define __dtors         __attribute__((destructor))
#define __section(s)    __attribute__((__section__(#s)))
#define __align(n)      __attribute__((aligned(n)))
#define __used          __attribute__((__used__))
#define __define_initcall(c, d, n) \
    static initcall_t __init_call_##n##_##c##_##d               \
        __used __align(4) __section(._local_init.##n) = {       \
            .init = c,                                          \
            .exit = d,                                          \
        }

#define CORE_INIT(c, d)   __define_initcall(c, d, 1)
#define MODULE_INIT(c, d) __define_initcall(c, d, 2)

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

void __ctors my_init() {
    initcall_t* ic = (initcall_t*)g_initcall_start;                    
    int cnt = (g_initcall_end - g_initcall_start) / sizeof(initcall_t);
    int i = 0;                                                         
    for (i = 0; i < cnt; i++) {                                        
        (*ic[i].init)();                                               
    }                                                                  
    printf("before main\n");
}
void __dtors my_exit() {
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

