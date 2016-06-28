#define CONS_CGREEN     0xa0
#define CONS_CRED       0xc0
#define CONS_CBLUE      0x90
#define CONS_CDEFAULT   0x70
#define CONS_NO_BUFFER  0x1 | CONS_CDEFAULT
#define CONS_BUFFER    	0x0 | CONS_CDEFAULT

struct stat;
struct rtcdate;

// system calls
int fork(void);
int exit(void) __attribute__((noreturn));
int wait(void);
int pipe(int*);
int write(int, void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(char*, char**);
int open(char*, int);
int mknod(char*, short, short);
int unlink(char*);
int fstat(int fd, struct stat*);
int link(char*, char*);
int mkdir(char*);
int chdir(char*);
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int uptime(void);
void write_at(int, int, char);
void clear_screen(void);
void set_console_parameters(int);
void set_cursor(int, int);
// ulib.c
int stat(char*, struct stat*);
char* strcpy(char*, char*);
void *memmove(void*, void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void printf(int, char*, ...);
char* gets(char*, int max);
uint strlen(char*);
void* memset(void*, int, uint);
void* malloc(uint);
void free(void*);
int atoi(const char*);
void mysrand(unsigned int);
void myrand();
int random(int, int);
