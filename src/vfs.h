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
    VFSnode* copySubtree(const VFSnode* source, VFSnode* newParent, const QString& newName);
public:
    VFS(const QString& physicalPath);
    QStringList listCurrentDirectory() const;
    bool changeDirectory(const QString& name);
    QString tree() const;
    bool changePermissions(const QString& name, int permissions);
    bool copyNode(const QString& sourceName, const QString& destinationName);
};

#endif // VFS_H
