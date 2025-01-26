.arch armv5te
.text
.code   16
.thumb
.global start

_start:
push {r0-r7, lr}

add r3,#0xC
ldmia r3,{r0,r1}
add r3,r1
str r0,[r3]

pop {r0-r7, pc}

_data:
.word 0x2083B8ED        @ magic number to enable card
.word 0x9696            @ dots -> magic number offset
