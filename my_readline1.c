#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>

#define READLINE_READ_SIZE 500

//checks if newline exists
bool is_newline(char* s){
    int i = 0;
    while (s[i] != '\0'){ 
        if (s[i] == '\n'){
            return true;
        }
        i++;
    }
    return false;
}

void append(char* buf, char* res, int index){
    int j = 0;
    while(buf[j] != '\0' && buf[j] != '\n'){
        res[index] = buf[j];
        j++;
        index++;
    }
    res[index] = '\0';
}

// reads leftover from  static x
int my_read(char *x, char* s){
    int i = 0;
    int j = 0;

    while (x[i] != '\n' && x[i] != '\0'){
        s[i] = x[i];
        i++;
    }
    s[i] = '\0';
    int char_sum = i;
    i++;
    while (x[i] != '\0'){
        x[j] = x[i];
        i++;
        j++; 
    }
    x[j] = '\0';
    return char_sum;
}

char *my_readline(int fd){
    if (fd < 0 || fd > 1023 || READLINE_READ_SIZE <= 0){
        return NULL;
    }
    static char x [1000];
    char *line = malloc(sizeof(char)*1000);
    int bytes_read_x = 0;

    if (strlen(x) > 0){
        bool new_line_exists = is_newline(x);
        bytes_read_x = my_read(x, line);
        if (new_line_exists){
            return line;
        }
    }
    char* buf = malloc((READLINE_READ_SIZE+1)*sizeof(char));
    int index = bytes_read_x;
    int bytes_read = 0;
    int j = 0;

    do {
        //printf("%s", x);
        bytes_read = read(fd, buf, (READLINE_READ_SIZE)*sizeof(char));
        buf[bytes_read] = '\0';
        append(buf, line, index);
        //printf("%s\n", line);
        if (is_newline(buf) || bytes_read < READLINE_READ_SIZE){
            //printf("%s\n", buf);
            int k = 0;
            int z = 0;
            //printf("%s\n", line);
            while (k < bytes_read){
                if (buf[k] == '\n'){
                    break;
                }
                k++;
            }
            k++;
            while (k < bytes_read){
                x[z] = buf[k];
                k++;
                z++;
            }
            x[z] = '\0';
            break;
        }
        index = index + bytes_read;
        j++;
    } while (bytes_read == READLINE_READ_SIZE && bytes_read > 0);
    
    if (bytes_read == 0) {
        if (strlen(line) > 0){
            free(buf);
            return line;
        }
        else{
            free(buf);
            free(line);
            return NULL;
        }
    }
    free(buf);
    //printf("%s", line);
    return line;
}

int main(int ac, char **av)
{
    char *str = NULL;
    int fd = open("./a.txt", O_RDONLY);
    while ((str = my_readline(fd)) != NULL){
        printf("%s\n", str);
        free(str);
    }
    close(fd);
  //
  //  Yes it's also working with stdin :-)
  //  printf("%s", my_readline(0));
  //
    return 0;
}