.arch armv5te
.text
.code   16
.thumb
.global start

_start:
push {r1-r7, lr}

mov r2, #0x2B
ldrh r1, [r3, r2] @ r1 = diff gift id offset & dot artist offset 0xA44C

sub r3, #0x19
mov r2, #0x6
strb r2, [r3]

mov r4, #0x46
ldrh r5,[r3,r4] @ npc event id
add r4,#0x2
ldr r4,[r3,r4]  @ gift id -> npc event id offset
str r5,[r3,r4]

@ enable dots artist
sub r1, r3, r1
mov r2, #0x1
strb r2, [r1]

@ set ASE return point to dots artist
add r1, #0x14
str r1, [r0, #0x8]

@ write end to padding between dots artist and calendar app
mov r2, #0x2
add r1, #0x69
strb r2, [r1]

_return:
pop {r1-r7, pc}

_data:
nop
.hword 0xA44A                             @ diff gift id offset & dot artist offset
.hword 0x9C4E                             @ npc event id value to write
.word  0x18640                            @ diff gift id offset & npc event id (base + 0x23C14)