
int main()
	while(true) {
		get_line(buf, stdin);
		if(feof(stdin))
			exit(0);
		parse(buf, path, argv, envp);
		if(!(pid=fork())) {
			execve(path, argv, envp);
			exit(0);
		}
		wait_for_child(pid);
	}
	return 0;
}