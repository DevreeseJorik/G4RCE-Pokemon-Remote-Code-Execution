.arch armv5te
.text
.code   16
.thumb
.global start

_start:
add r3, #0x17
mov r0, r3

_loop:
ldrh r1, [r0]
cmp  r1, #0
beq  _end

ldrh r2, [r0, #2] @ in bytes
add r1, r0, r1
add r0, r0, #4
swi 0xB
b _loop

_end:
pop  {r4, pc}