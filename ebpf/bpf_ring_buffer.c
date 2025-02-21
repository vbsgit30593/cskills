// this is a BPF map that is used to pass messages from kernel to userspace
BPF_PERF_OUTPUT(output);

typedef struct {
	int uid;
	int pid;
	char command[64];
	char message[64];
} data_t;

int hello(void* ctx) {
	char *msg = "hello world!";
	data_t data = {};
	
	// top 32 bits contain the pid
	data.pid = bpf_get_current_pid_tgid() >> 32;
	data.uid = bpf_get_current_uid_gid() & 0xFFFFFFFF;

	// get name of the function that made the syscall
	bpf_get_current_comm(&data.command, sizeof(data.command));
	// special function for kernel level memory copy
	bpf_probe_read_kernel(&data.message, sizeof(data.message), msg);

	// put the data in the map
	output.perf_submit(ctx, &data, sizeof(data));

	return 0;
} 


