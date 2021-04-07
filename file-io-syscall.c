#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

extern int errno;
const unsigned short records = 10;
const size_t size = 20;
const char* dbName = "database.bin";
struct record {
 char name[20];
 char phone_number[20];
};

void info(void)
{
printf("\n****************** Program mode ******************************\n");
  printf("initial run create 10 random entries.               Enter : (1)\n");
  printf("only read names and list them, one on a line.       Enter : (2)\n");
  printf("only read numbers and list them, one on a line.     Enter : (3)\n");
  printf("list every name and number (on a line each).        Enter : (4)\n");
  printf("update record with arguments 3 \"Blue Sky\" \"5551212\" Enter : (5)\n");
  printf("Exit                                                Enter : (x)\n");
}

char* RemoveChar(char* input)
{
	char* line = input;
	for (int i = 0, j; line[i] != '\0'; ++i) {
	while (!(line[i] >= '0' && line[i] <= '9') && !(line[i] == '-') && !(line[i] == '\0')) {
		for (j = i; line[j] != '\0'; ++j) {
            		line[j] = line[j + 1];
         		}
		line[j] = '\0';
		}
	}
	return line;
}

char* RemoveSpecialChar(char* input)
{
	char* line = input;
	for (int i = 0, j; line[i] != '\0'; ++i) {
	while (!(line[i] >= 'a' && line[i] <= 'z') && !(line[i] >= 'A' && line[i] <= 'Z') && !(line[i] == '\0')  && !(line[i] == ' ')) {
		for (j = i; line[j] != '\0'; ++j) {
            		line[j] = line[j + 1];
         		}
		line[j] = '\0';
		}
	}
	return line;
}

static char *rand_string(char *str, size_t size)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (size) {
        --size;
        for (size_t n = 0; n < size; n++) {
            int key = rand() % (int) (sizeof charset - 1);
            str[n] = charset[key];
        }
        str[size] = '\0';
    }
    return str;
}

char* rand_string_alloc(size_t size)
{
     char *s = malloc(size + 1);
     if (s) {
         rand_string(s, size);
     }
     return s;
}

static char *rand_number(char *str, size_t size)
{
    const char charset[] = "0123456789-";
    if (size) {
        --size;
        for (size_t n = 0; n < size; n++) {
            int key = rand() % (int) (sizeof charset - 1);
            str[n] = charset[key];
        }
        str[size] = '\0';
    }
    return str;
}

char* rand_number_alloc(size_t size)
{
     char *s = malloc(size + 1);
     if (s) {
         rand_number(s, size);
     }
     return s;
}

void display_names(void) {
    struct record tmp;
    int fd, offset = 0;
    fd = open(dbName, O_RDONLY, 00660);
    if (fd ==-1)
    {
        printf("Error Number % d\n", errno);
        perror("File");
        exit(1);
    }
    lseek (fd, offset, SEEK_SET);
    while ( read (fd, &tmp, sizeof(struct record)) )
    {
      printf ("\nFull  Name      : %s\n",tmp.name);
      lseek (fd, offset+=sizeof(struct record), SEEK_SET);
    }
    if (close(fd) < 0)
    {
     perror("File");
     exit(1);
    }
}

void display_numbers(void) {
    struct record tmp;
    int fd, offset = 0;
    fd = open(dbName, O_RDONLY, 00660);
    if (fd ==-1)
    {
        printf("Error Number % d\n", errno);
        perror("File");
        exit(1);
    }
    lseek (fd, offset, SEEK_SET);
    while ( read (fd, &tmp, sizeof(struct record)) )
    {
      printf ("\nPhone Number    : %s\n", tmp.phone_number);
      lseek (fd, offset+=sizeof(struct record), SEEK_SET);
    }
    if (close(fd) < 0)
    {
     perror("File");
     exit(1);
    }
}
void display_records(void) {
    struct record tmp;
    int fd, offset = 0;
    fd = open(dbName, O_RDONLY, 00660);
    if (fd ==-1)
    {
        printf("Error Number % d\n", errno);
        perror("File");
        exit(1);
    }
    lseek (fd, offset, SEEK_SET);
    while ( read (fd, &tmp, sizeof(struct record)) )
    {
      printf ("\nFull  Name : %-20s",tmp.name);
      printf ("\tPhone Number : %-20s\n", tmp.phone_number);
      lseek (fd, offset+=sizeof(struct record), SEEK_SET);
    }
    if (close(fd) < 0)
    {
     perror("File");
     exit(1);
    }
}

void populate(void)
{
    struct record array[records];
    struct record tmp;
    int fd, i, offset = 0;
    fd = open(dbName,  O_CREAT | O_TRUNC | O_WRONLY, 00660);
    if (fd ==-1)
    {
        printf("Error Number % d\n", errno);
        perror("File");
        exit(1);
    }
    for(i=0; i<records; i++)
    {
     strcpy(array[i].name , rand_string_alloc(size));
     strcpy(array[i].phone_number , rand_number_alloc(size));
     write(fd, &array[i], sizeof(struct record));
    }
}

void update(void)
{
   struct record tmp;
   char buffer[size * 3];
   const char delimiter[2] = "\"";
   char *token;
   char **tokens = malloc(size * 3 * sizeof(char*));
   int fd, count, position, offset  = 0;
   count = read(0, buffer, sizeof(buffer));
   if (count <= 0)
   {
	printf("Error Number % d\n", errno);
        perror("read");
        exit(1);
   }
   fd = open(dbName, O_WRONLY, 00660);
   if (fd ==-1)
    {
        printf("Error Number % d\n", errno);
        perror("open");
        exit(1);
    }
   // get the first token 
   token = strtok(buffer, delimiter);
   offset = 40 * atoi(token);
   // walk through other tokens
   while( token != NULL ) {
      tokens[position] = token;
      position++;
      token = strtok(NULL, delimiter);
   }
   tokens[position] = NULL;
   strncpy(tmp.name , RemoveSpecialChar(tokens[1]), size);
   tmp.name[size - 1] = '\0';
   strncpy(tmp.phone_number , RemoveChar(tokens[3]), size);
   tmp.phone_number[size - 1] = '\0';
   lseek (fd, offset, SEEK_SET);
   write(fd, &tmp, sizeof(struct record));
   if (close(fd) < 0)
    {
     perror("File");
     exit(1);
    }
}

int main()
{
	char operator[1];
	do {
		info();  
		printf ("\nEnter your choice : ");
		scanf("%s", operator);
		switch(operator[0])
		{
			case 'x':
				exit(0);
				break;
			case '1':
				populate();	
				break;
			case '2':
				display_names();
				break;
			case '3':
				display_numbers();
				break;
			case '4':
				display_records();
				break;
			case '5': 
        			update(); 
				break;
     		}
	} while (1);
	
	return 0;
}
