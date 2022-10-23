/*You have to define the MAX_SIZE constant the that include this header*/

#define READ 0
#define WRITE 1

int TUBE[2];

char READ_BUFFER[MAX_SIZE];
char WRITE_BUFFER[MAX_SIZE];

void replace_standard_input()
{
        close(WRITE);
        dup(TUBE[WRITE]);
        close(TUBE[WRITE]);
        close(TUBE[READ]);
}

void replace_standard_output()
{
        close(READ);
        dup(READ);
        close(TUBE[READ]);
        close(TUBE[WRITE]);
}

