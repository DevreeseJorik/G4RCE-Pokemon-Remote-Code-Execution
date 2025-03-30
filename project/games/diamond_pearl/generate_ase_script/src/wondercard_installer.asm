@ A loop to copy data packets, meant for installing wondercards
@ packets should follow right after code
@ Expected packet structure:
@ hword offset -> offset from current instruction location (r3) to target location
@ hword size
@ data

.arch armv5te
.text
.code   16
.thumb
.global start

_start:
add r3, #0x17                           @ Advance current instruction(r3) to data packets
mov r0, r3                              @ copy r3 to r0 in prep for copy call

_loop:
ldrh r1, [r0]                           @ if offset blank end
cmp  r1, #0
beq  _end

ldrh r2, [r0, #2] @ in bytes
add r1, r0, r1                          @ calculate dest by adding offset to current instruction position
add r0, r0, #4
swi 0xB                                 @ copy, requires BIOS, r0 = src, r1 = dest, r2 = size
b _loop

_end:
pop  {r4, pc}