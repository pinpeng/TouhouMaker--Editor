#ifndef FILEOPERATOR_H
#define FILEOPERATOR_H

#include <QString>

namespace ToolKit {
    enum FileModule{
        LOG,                    // 日志
        CRASH,                  // 崩溃文件
        SETTING,                // 编辑器配置
        SOURCE_FONT             // 资源文件
    };

    enum ProjectModule{
        IMAGE,                  // 图片
        DATA,                   // 数据
        AUDIO,                  // 音频
    };

    class FileOperator
    {
    public:
        static QString getEditorPath();
        /**
         * @brief 获取模块配置路径，该路径不存在时会创建该路径
        */
        static QString getEditorSubModulePath(FileModule module);
        static bool checkDirExists(const QString& folderPath);
        static bool createFolder(const QString& folderPath);
        /**
         * @brief 设置当前项目路径值，项目初始化时使用
        */
        static QString setProjectPath(const QString& path);
        /**
         * @brief 获取项目子模块文件夹路径
        */
        static QString getProjectSubModulePath(ProjectModule module);

        /**
         * @brief 获取文件名称，注意带后缀
        */
        static QString getFileName(const QString& filePath);
    private:
        static QString _projectPath;
    };
}

#endif // FILEOPERATOR_H
