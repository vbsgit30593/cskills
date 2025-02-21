#!/usr/bin/python
from bcc import BPF

with open("bpf_ring_buffer.c", "r") as f:
	program = f.read()

bpf = BPF(text=program)
syscall = bpf.get_syscall_fnname("execve")
bpf.attach_kprobe(event=syscall, fn_name="hello")

# here cpu tells the CPU core which triggered the event
def print_event(cpu, data, size):
	# parses raw binary event data and stores it in a python obj
	data = bpf["output"].event(data)
	print(
		f"{cpu=}, {data.pid}, {data.uid}, {data.command}, {data.message}"
	)

# this defines the callback to use whenever there is data to be read from buffer
bpf["output"].open_perf_buffer(print_event)

while True:
	# keeps polling the perf ring buffer
	bpf.perf_buffer_poll()
