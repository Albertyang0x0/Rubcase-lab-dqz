#include "storage/disk_manager.h"

#include <assert.h>  // for assert
#include <fcntl.h>
#include <string.h>    // for memset
#include <sys/stat.h>  // for stat
#include <sys/stat.h>
#include <unistd.h>  // for lseek

#include "defs.h"

DiskManager::DiskManager() { memset(fd2pageno_, 0, MAX_FD * (sizeof(std::atomic<page_id_t>) / sizeof(char))); }

/**
 * @brief Write the contents of the specified page into disk file
 *
 */
void DiskManager::write_page(int fd, page_id_t page_no, const char *offset, int num_bytes) {
    // Todo:
    // 1.lseek()定位到文件头，通过(fd,page_no)可以定位指定页面及其在磁盘文件中的偏移量
    // 2.调用write()函数
    // 注意处理异常
    // 计算目标位置的文件偏移量

    // 计算目标位置的文件偏移量，page_no 乘以 PAGE_SIZE 是页面在文件中的偏移量
    lseek(fd, page_no * PAGE_SIZE, SEEK_SET);

    // 调用 write() 函数将数据写入指定位置
    // 如果写入的字节数不等于期望的字节数，抛出 UnixError 异常
    if (write(fd, offset, num_bytes) != num_bytes) throw UnixError();
}

/**
 * @brief Read the contents of the specified page into the given memory area
 */
void DiskManager::read_page(int fd, page_id_t page_no, char *offset, int num_bytes) {
    // Todo:
    // 1.lseek()定位到文件头，通过(fd,page_no)可以定位指定页面及其在磁盘文件中的偏移量
    // 2.调用read()函数
    // 注意处理异常
    // 计算目标位置的文件偏移量
    // 计算目标位置的文件偏移量，page_no 乘以 PAGE_SIZE 是页面在文件中的偏移量
    lseek(fd, page_no * PAGE_SIZE, SEEK_SET);

    // 调用 read() 函数读取数据
    // 如果读取的字节数小于 0，表示读取失败，抛出 UnixError 异常
    if (read(fd, offset, num_bytes) < 0) throw UnixError();
}

/**
 * @brief Allocate new page (operations like create index/table)
 * For now just keep an increasing counter
 */
page_id_t DiskManager::AllocatePage(int fd) {
    // Todo:
    // 简单的自增分配策略，指定文件的页面编号加1
    return fd2pageno_[fd]++;
}

/**
 * @brief Deallocate page (operations like drop index/table)
 * Need bitmap in header page for tracking pages
 * This does not actually need to do anything for now.
 */
void DiskManager::DeallocatePage(__attribute__((unused)) page_id_t page_id) {}

bool DiskManager::is_dir(const std::string &path) {
    struct stat st;
    return stat(path.c_str(), &st) == 0 && S_ISDIR(st.st_mode);
}

void DiskManager::create_dir(const std::string &path) {
    // Create a subdirectory
    std::string cmd = "mkdir " + path;
    if (system(cmd.c_str()) < 0) {  // 创建一个名为path的目录
        throw UnixError();
    }
}

void DiskManager::destroy_dir(const std::string &path) {
    std::string cmd = "rm -r " + path;
    if (system(cmd.c_str()) < 0) {
        throw UnixError();
    }
}

/**
 * @brief 用于判断指定路径文件是否存在
 */
bool DiskManager::is_file(const std::string &path) {
    // Todo:
    // 用struct stat获取文件信息
    struct stat info;
    if (stat(path.c_str(), &info) == 0)

        return true;

    else

        return false;
}

/**
 * @brief 用于创建指定路径文件
 */
void DiskManager::create_file(const std::string &path) {
    // Todo:
    // 调用open()函数，使用O_CREAT模式
    // 注意不能重复创建相同文件
    int flags =
        O_CREAT | O_WRONLY | O_EXCL;  // 设置打开文件的模式，允许只写入数据和创建文件，O_EXCL表示禁止覆盖现有文件

    int fd = ::open(path.c_str(), flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);  // 打开并创建新文件

    // 检查文件是否已存在并捕获错误
    if (fd < 0) {
        throw FileExistsError(path);
    }

    // 成功创建并关闭文件描述符
    else {
        close(fd);
    }
}

/**
 * @brief 用于删除指定路径文件
 */
void DiskManager::destroy_file(const std::string &path) {
    // Todo:
    // 调用unlink()函数
    // 注意不能删除未关闭的文件

    if (!is_file(path)) {  // 如果文件不存在则抛出异常
        throw FileNotFoundError(path);
    }

    auto it = path2fd_.find(path);
    if (it != path2fd_.end())  // 检测文件是否打开
    {
        throw UnixError();
    }

    int ret = unlink(path.c_str());  // 删除文件
    if (ret < 0)                     // 捕获并打印错误信息
    {
        perror("Failed to remove file");
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief 用于打开指定路径文件
 */
int DiskManager::open_file(const std::string &path) {
    // Todo:
    // 调用open()函数，使用O_RDWR模式
    // 注意不能重复打开相同文件，并且需要更新文件打开列表

    if (!is_file(path))  // 检查文件是否存在
    {
        throw FileNotFoundError(path);
    }
    if (path2fd_.find(path) != path2fd_.end()) {  // 检查文件是否已被打开
        throw UnixError();
    }

    // 打开或新建文件，并防止覆盖已存在的文件
    int fd = open(path.c_str(), O_RDWR);

    // 捕获错误信息
    if (fd < 0) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    path2fd_.insert(std::make_pair(path, fd));
    fd2path_.insert(std::make_pair(fd, path));
    return fd;
}

/**
 * @brief 用于关闭指定路径文件
 */
void DiskManager::close_file(int fd) {
    // Todo:
    // 调用close()函数
    // 注意不能关闭未打开的文件，并且需要更新文件打开列表

    // 检查文件描述符是否已存在
    auto it = fd2path_.find(fd);
    if (it == fd2path_.end()) {  // 如果文件描述符不存在，则输出错误信息并退出程序
        perror("Cannot close the file descriptor");
        exit(EXIT_FAILURE);
    }
    // 删除文件描述符
    close(fd);
    // 删除文件描述符与文件路径之间的映射关系
    path2fd_.erase(it->second);
    fd2path_.erase(it->first);
    close(fd);
}

int DiskManager::GetFileSize(const std::string &file_name) {
    struct stat stat_buf;
    int rc = stat(file_name.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

std::string DiskManager::GetFileName(int fd) {
    if (!fd2path_.count(fd)) {
        throw FileNotOpenError(fd);
    }
    return fd2path_[fd];
}

int DiskManager::GetFileFd(const std::string &file_name) {
    if (!path2fd_.count(file_name)) {
        return open_file(file_name);
    }
    return path2fd_[file_name];
}

bool DiskManager::ReadLog(char *log_data, int size, int offset, int prev_log_end) {
    // read log file from the previous end
    if (log_fd_ == -1) {
        log_fd_ = open_file(LOG_FILE_NAME);
    }
    offset += prev_log_end;
    int file_size = GetFileSize(LOG_FILE_NAME);
    if (offset >= file_size) {
        return false;
    }

    size = std::min(size, file_size - offset);
    lseek(log_fd_, offset, SEEK_SET);
    ssize_t bytes_read = read(log_fd_, log_data, size);
    if (bytes_read != size) {
        throw UnixError();
    }
    return true;
}

void DiskManager::WriteLog(char *log_data, int size) {
    if (log_fd_ == -1) {
        log_fd_ = open_file(LOG_FILE_NAME);
    }

    // write from the file_end
    lseek(log_fd_, 0, SEEK_END);
    ssize_t bytes_write = write(log_fd_, log_data, size);
    if (bytes_write != size) {
        throw UnixError();
    }
}
