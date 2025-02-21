#!/usr/bin/python
from bcc import BPF

# build a program that will run in the kernel
# this prog needs to be compiled before use but BPF takes
# care of that for us.
prog = r"""
int hello(void *ctx) {
    bpf_trace_printk("hello: function was called");
    return 0;
}
"""

"""
User space code
* load the BPF code in the kernel
* read out the generated tracee
"""

# get a bpf object
bpf = BPF(text=prog)

# specify the syscall to track
# Note: Different chip arch could have a different name for execve
# but this lookup gives us the name based on the arch
# At this point syscall contains the name of the kernel fn to attach to
syscall = bpf.get_syscall_fnname("execve")

# attach a kprobe to this syscall such that when this event hits
# then we should make a specific function call used for tracing
bpf.attach_kprobe(event=syscall, fn_name="hello")
# As a result of the above, `hello` to attached to `execve` event

# print the traced data - this would loop indefinitely
bpf.trace_print()

"""
Whenever an execve is called, hello is called and it writes to a pseudofile
The python program reads from that pseudofile and displays to the use
"""
