#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>


int main() {
    char *path = ".txt";
    int fd;
    if ((fd = creat(path, S_IRUSR | S_IWUSR)) < 0) {
        perror("ошибка создания файла");
        return 1;
    }
    close(fd);

    char current_link[] = "aa.txt";
    remove(current_link);
    if (symlink(path, current_link) != 0) {
        perror("ошибка при создании символической связи");
    }

    int i = 0;
    current_link[i]++;
    int deep = 2;
    char old_link[] = "aa.txt";
    while (1) {
        remove(current_link);
        int check = symlink(old_link, current_link);
        if (check != 0) {
            perror("ошибка при создании символической связи");
        }
        if (access(current_link, F_OK) == -1) {
            break;
        }
        if (current_link[i] == 'z') {
            old_link[++i - 1]++;
            old_link[i]--;
        }
        deep++;
        current_link[i]++;
        old_link[i]++;
    }
    printf("%d", deep);
}