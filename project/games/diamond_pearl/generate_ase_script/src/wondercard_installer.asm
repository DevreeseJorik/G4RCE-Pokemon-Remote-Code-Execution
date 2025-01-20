.arch armv5te
.text
.code   16
.thumb
.global start

_start:
push {r0-r7, lr}

mov r0,#0x0
add r0,r3               @ copy r3 (current location) into r0
add r3,#0x23            @ advance current location to data
ldr r4,[r3]
add r0,r4               @ add value of data (gift offset) to r0 (current location) to get gift location
add r3,#0x2             @ advance to first data packet
ldr r4,[r3,#0x48]       @ load loop end value

_loop:
ldr r2,[r3]
str r2,[r0]
cmp r2,r4
beq _end
add r0,#0x4
add r3,#0x4
b _loop

_end:
pop {r0-r7, pc}

_data:
.hword 0x0
.hword 0x9E99            @ dots -> gift offset
.word 0x00000006
.word 0x00000001
.word 0x0001D76E
.word 0x00070000
.word 0x02042785
.word 0x0100C847
.word 0xB5FE0271
.word 0x5A99222B
.word 0x22063B19
.word 0x2446701A
.word 0x34025B1D
.word 0x511D591C
.word 0x22011A59
.word 0x3114700A
.word 0x22026081
.word 0x700A3169
.word 0x46C0BDFE
.word 0x9C4AA44A
.word 0xB0018640
