#include <stdarg.h>
#include <unistd.h> 
#include <stdlib.h>
#include <string.h> 
#include <stdio.h>


char* my_reversed_str(char *str, int i, int len){
    for(int k = i; k < len-k-1; k++){
        int temp = str[k];
        str[k] = str[len-k-1];
        str[len-k-1] = temp;
    }
    return str;
}
char* my_utoa(char *s, unsigned int x, int base){
    int i = 0;
    int k = 0;
    if (x == 0){
        s[0] = '0';
    }
    else{
        while (x!=0){
            k = x % base;
            if (k > 9){
                s[i] = k + 'a' - 10;
            }
            else{
                s[i] = k + '0';
            }
            x = x / base;
            i++;
        }
        s[i] = '\0';
    }
    return my_reversed_str(s, 0, strlen(s));
}
char* my_itoa(char *s, int x, int base){
    int i = 0;
    int k = 0;
    if (x < 0){
        s[0] = '-';
        x = -x;
        while (x!=0){
            k = x % base;
            s[i+1] = k + '0';
            x = x / base;
            i++;
        }
        s[i+1] = '\0';
        return my_reversed_str(s, 1, strlen(s)+1);
    }
    else {
        return my_utoa(s, x, base);
    }
}

int my_printf(char *format, ...){
    int count = 0;
    va_list args;
    va_start(args, format);
    char *i = format;
    while (*i != '\0') {
        while ((*i != '%') && (*i != '\0')){
            write(1, i, 1);
            i++;
            count++;
        }
        if (*i != '\0') {
            i++;
        }
        if (*i == 'c'){
            int a = va_arg(args, int);
            unsigned char chr = (unsigned char) a;
            write(1, &chr, 1);
            count++;
            i++;
        }
        
        
        else if(*i == 'p'){
            char *str_val = malloc(sizeof(char)*10);
            int *p = va_arg(args, void*);
            unsigned long long_val  = (unsigned long) p;
            char *ptr = my_utoa(str_val, long_val, 16);
            char *str_ptr = malloc(sizeof(char)*20);
            str_ptr[0] = '0';
            str_ptr[1] = 'x';
            int k = 2;
            for (int j = 0; j!= strlen(ptr); j++){
                str_ptr[k] = ptr[j];
                k++;
            }
            write(1, str_ptr, strlen(ptr)+2);
            count += strlen(ptr)+2;
            i++;
            free(str_val);
            free(str_ptr);
        }
    }
    va_end(args);
    return count;
}

int main(){
    int x = 99;
    int *pt1;
    pt1 = &x;
    my_printf("%p", (void*)pt1);
    printf("%p", (void*)pt1);
}