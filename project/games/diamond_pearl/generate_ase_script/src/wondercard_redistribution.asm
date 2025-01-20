.arch armv5te
.text
.code   16
.thumb
.global start

_start:
push {r0-r7, lr}

@ load data
add r3,#0x14
ldrh r0,[r3]            @ redistribution offset
ldrh r1,[r3,#0x2]       @ load redistribution flags

@ load flags
str r1,[r3,r0]
add r0,#0x2
mov r4,#0xEE
str r4,[r3,r2]

pop {r0-r7, pc}

_data:
.hword 0x9FD2           @ offset to redistribution flags
.hword 0x1D80           @ redistribution flags
