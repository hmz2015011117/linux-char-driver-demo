#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define DEVICE_PATH "/dev/simple_char_dev"

int main() {
    int fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        perror("Failed to open device");
        return 1;
    }

    const char *msg = "Hello from user space!";
    write(fd, msg, strlen(msg));
    printf("Wrote: %s\n", msg);

    char buf[128] = {0};
    lseek(fd, 0, SEEK_SET); // 回到开头，准备读
    read(fd, buf, sizeof(buf));
    printf("Read: %s\n", buf);

    close(fd);
    return 0;
}

