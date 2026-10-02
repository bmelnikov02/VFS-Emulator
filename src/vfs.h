#ifndef VFS_H
#define VFS_H
#include "vfsnode.h"
#include <QString>

class VFS
{
    std::unique_ptr<VFSnode> rootNode;
    void loadDirectory(const QString& physicalPath, VFSnode* parentNode);
public:
    VFS(const QString& physicalPath);
};

#endif // VFS_H
