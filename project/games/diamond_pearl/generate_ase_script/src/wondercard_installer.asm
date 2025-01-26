.arch armv5te
.text
.code   16
.thumb
.global start

_start:
push {r0-r7, lr}

add r3,#0x19
ldmia r3,{r4,r5}
mov r0,r3
add r1,r3,r5

@ Copy payload
mov r2,#0x4C
blx r4

pop {r0-r7, pc}

_data:
.word  0x20CE3E0            @ Copy function DP: call to 0x20CE3E0, r0 = dest, r1=src, r2=size, size is 4C
.word  0x9E7E               @ dots -> gift offset
