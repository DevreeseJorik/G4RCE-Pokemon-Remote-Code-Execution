#define CLOBBER_1 "r0"
#define CLOBBER_2 "r0", "r1"
#define CLOBBER_3 "r0", "r1", "r2"
#define CLOBBER_4 "r0", "r1", "r2", "r3"
#define CLOBBER_5 "r0", "r1", "r2", "r3", "r4"
#define CLOBBER_6 "r0", "r1", "r2", "r3", "r4", "r5"
#define CLOBBER_7 "r0", "r1", "r2", "r3", "r4", "r5", "r6"
#define CLOBBER_8 "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"

#define CLOBBER_LIST(num) CLOBBER_##num

#define WITH_CURRENT_REGSTATE(func, num_regs)               \
    __asm__ volatile (                                      \
        "blx %[target_func] \n"                             \
        :                                                   \
        : [target_func] "r" (func)                          \
        : CLOBBER_LIST(num_regs)                            \
    )

#define WITH_CURRENT_REGSTATE_SAFE(func, num_regs)          \
    __asm__ volatile (                                      \
        "push {r0-r" #num_regs "} \n"                       \
        "blx %[target_func] \n"                             \
        "pop {r0-r" #num_regs "} \n"                        \
        :                                                   \
        : [target_func] "r" (func)                          \
        : CLOBBER_LIST(num_regs)                            \
    )
