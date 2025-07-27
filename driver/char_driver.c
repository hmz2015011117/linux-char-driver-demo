#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "simple_char_dev"
#define BUF_LEN 128

static int major;
static char msg[BUF_LEN];
static int msg_len = 0;

static int dev_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Device opened\n");
    return 0;
}

static int dev_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Device closed\n");
    return 0;
}

static ssize_t dev_read(struct file *filp, char *buffer, size_t len, loff_t *offset) {
    int bytes_read = 0;
    if (*offset >= msg_len) return 0;
    while (len && *offset < msg_len) {
        put_user(msg[*offset], buffer++);
        len--;
        bytes_read++;
        (*offset)++;
    }
    printk(KERN_INFO "Read %d bytes\n", bytes_read);
    return bytes_read;
}

static ssize_t dev_write(struct file *filp, const char *buffer, size_t len, loff_t *offset) {
    msg_len = len > BUF_LEN ? BUF_LEN : len;
    if (copy_from_user(msg, buffer, msg_len)) {
    	printk(KERN_WARNING "copy_from_user failed!\n");
    	return -EFAULT;
    }
    printk(KERN_INFO "Received %d bytes: %.*s\n", msg_len, msg_len, msg);
    return msg_len;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = dev_read,
    .write = dev_write,
    .open = dev_open,
    .release = dev_release
};

static int __init char_init(void) {
    major = register_chrdev(0, DEVICE_NAME, &fops);
    if (major < 0) {
        printk(KERN_ALERT "Registering char device failed\n");
        return major;
    }
    printk(KERN_INFO "Registered char device with major number %d\n", major);
    return 0;
}

static void __exit char_exit(void) {
    unregister_chrdev(major, DEVICE_NAME);
    printk(KERN_INFO "Char device unregistered\n");
}

module_init(char_init);
module_exit(char_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("你自己的名字");
MODULE_DESCRIPTION("Simple Character Device Driver");

