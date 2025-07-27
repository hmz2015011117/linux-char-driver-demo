# Simple Linux Character Device Driver

<p align="center">
  <a href="https://github.com/hmz2015011117/linux-char-driver-demo/stargazers">
    <img src="https://img.shields.io/github/stars/hmz2015011117/linux-char-driver-demo?style=flat-square&color=brightgreen" alt="Stars">
  </a>
  <a href="https://github.com/hmz2015011117/linux-char-driver-demo/blob/master/LICENSE">
    <img src="https://img.shields.io/github/license/hmz2015011117/linux-char-driver-demo?style=flat-square&color=blue" alt="License">
  </a>
  <img src="https://img.shields.io/github/languages/top/hmz2015011117/linux-char-driver-demo?style=flat-square&color=orange" alt="Top Language">
</p>

A basic Linux kernel module demonstrating how to implement a simple character device driver with read/write support, along with a user-space test application.

## 📁 Project Structure

```
linux_driver_project/
├── driver/             # 内核模块源代码
│   ├── char_driver.c
│   └── Makefile
└── user/               # 用户态程序
    └── test_app.c
```

## ✨ Features

- Basic character device registration
- Supports `read()` and `write()` syscalls
- Logs user-space messages via `printk()`
- Custom `/dev` entry creation
- Compatible with Linux kernel 5.x–6.x

## 🔧 Build & Run Instructions

### 1. Install dependencies

```bash
sudo apt update
sudo apt install build-essential linux-headers-$(uname -r) gcc-12 -y
```

### 2. Build kernel module

```bash
cd driver
make
```

### 3. Insert module and check logs

```bash
sudo insmod char_driver.ko
dmesg | tail
```

Note the **major device number** printed.

### 4. Create device node

```bash
sudo mknod /dev/simple_char_dev c <major> 0
sudo chmod 666 /dev/simple_char_dev
```

Replace `<major>` with actual major number from `dmesg`.

### 5. Build and run user application

```bash
cd ../user
gcc test_app.c -o test_app
./test_app
```

### 6. Remove module when done

```bash
sudo rmmod char_driver
```

## 🧠 Learning Purpose

This project is part of my journey to become a Linux driver/embedded developer.

It demonstrates key concepts like:

- `register_chrdev`
- `file_operations`
- `copy_to_user` / `copy_from_user`
- Module insert/remove
- Kernel-user communication

## 👤 Author

**hmz**  
GitHub: [hmz2015011117](https://github.com/hmz2015011117)

## 📄 License

This project is open-sourced under the MIT license.

