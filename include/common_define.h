#pragma once

// 文件路径最大长度
#define D_FILE_PATH_MAX_LENGTH 1024

// 文本最大长度
#define D_TEXT_MAX_LENGTH 512

// 拷贝构造函数
#define D_DISABLE_COPY(typeName)           \
    typeName &typeName(const typeName &);  \
    typeName &operator=(const typeName &);