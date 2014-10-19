#include <iostream>

int strstr(const char *str, const char *pattern) {
    int i = 0;
    int k = 0;    
    for (; str[i] != '\0'; ++i) {
        k = 0;
        for (; pattern[k] != '\0'; ++k) {           
           if (str[k+i] != pattern[k]) {
                break;
           }
        }
        if (pattern[k] == '\0'){
            return i;
        }
    }
    return -1;
}

int main() {
    const char * str = "HHHello";    
    const char * pattern = "HHello";
    std::cout << strstr(str, pattern) << std::endl;
    return 0;
}
