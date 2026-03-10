# Dlib 示例（Optional）

## 目录结构
```
dlib_example/
├── CMakeLists.txt      // CMake 配置文件
└── src/                
    └── dlib_example.cpp // 测试代码  
```

## 使用说明

我们可以使用 [Dlib](https://dlib.net) 库来使用简单的神经网络，这是一个 C++ 的机器学习算法库，需要配置安装后方可使用。

- Step 1: 从[这里](https://github.com/davisking/dlib/releases/tag/v19.24.6)下载到 Dlib 库的源码，解压到合适的目录下。

- Step 2: 到解压出来的 dlib-19.24.6/ 目录下，用 CMake 配置生成。下面是通用的命令行方案（也可以使用熟悉的 vscode 或者 CMake GUI 来进行 CMake）
  - 创建并进入构建目录
    ```shell
    mkdir build
    cd build
    ```
  - 指定安装路径并配置 CMake
    ```shell
    cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_INSTALL_PREFIX=/your/install/path  # 不要放在C盘，否则需要管理员权限
    ```
  - 编译库
    ```shell
    cmake --build . --config Release
    cmake --build . --config Debug
    ```
  - 安装库到指定目录下
    ```shell
    cmake --install
    ```
  现在 Dlib 库已经安装到指定目录下了，其中包含 Dlib 的头文件和静态库

- Step 3: 将安装目录下的 /your/install/path/lib/cmake/dlib 添加为系统环境变量 `dlib_DIR` ，使得 CMake 可以找到 dlib 包
- Step 4: 配置完以上步骤后，CMake 当前 dlib_example 项目，应该就可以 cmake 成功，可以找到以下头文件

```cpp
#include <dlib/dnn.h>
```


## 如何在作业项目中使用

按照以上说明配置完成后，重新CMake作业项目，就可以使用 Dlib。