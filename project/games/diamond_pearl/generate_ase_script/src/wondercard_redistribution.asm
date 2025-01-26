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
add r3,r0

@ load flags
strh r1,[r0]
mov r4,#0xEE
strb r4,[r0,#0x1]

pop {r0-r7, pc}

_data:
.hword 0x9FD2           @ offset to redistribution flags
.hword 0x1D80           @ redistribution flags
