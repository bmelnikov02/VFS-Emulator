#ifndef VFS_H
#define VFS_H
#include "vfsnode.h"
#include <QString>
#include <QStringList>

class VFS
{
    std::unique_ptr<VFSnode> rootNode;
    VFSnode* currentNode;
    void loadDirectory(const QString& physicalPath, VFSnode* parentNode);
    void buildTree(const VFSnode* node, int depth, QString& result) const;
public:
    VFS(const QString& physicalPath);
    QStringList listCurrentDirectory() const;
    bool changeDirectory(const QString& name);
    QString tree() const;
};

#endif // VFS_H
