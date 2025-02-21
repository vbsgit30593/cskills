#!/usr/bin/python
from bcc import BPF
from time import sleep

# BPF program
program = r"""
// this is a macro to define bpf hash maps
BPF_HASH(counter_table);
int hello(void* ctx) {
	u64 uid;
	u64 counter = 0;
	u64* p;

	// lower 32 bits give us the uid and upper 32 gives gid
	uid = bpf_get_current_uid_gid() & 0xFFFFFFFF;

	// this is different from classic C syntax as BCC would rewrite it before
	// sending the code to the compiler. BCC is loosely typed C.
	p = counter_table.lookup(&uid);

	if (p != NULL) counter = *p;

	counter++;

	// update the BPF hash
	counter_table.update(&uid, &counter);
	return 0;
}
"""


# get a bpf obj using kernel program
bpf = BPF(text=program)

syscall = bpf.get_syscall_fnname("execve")

bpf.attach_kprobe(event=syscall, fn_name="hello")

while True:
	sleep(2)
	for k, v in bpf["counter_table"].items():
		print(f"(uid, count) = ({k.value}, {v.value})")
		print()
