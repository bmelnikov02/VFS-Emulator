#ifndef VFSNODE_H
#define VFSNODE_H

#include <vector>
#include <memory>
#include <QString>

enum class NodeType
{
    File,
    Directory
};

class VFSnode
{
    QString name;
    NodeType type;
    VFSnode* parent;
    std::vector<std::unique_ptr<VFSnode>> children;

public:
    VFSnode(const QString& name, NodeType type, VFSnode* parent = nullptr);
    VFSnode* addChild(const QString& name, NodeType type);
    const QString& getName() const;
    NodeType getType() const;
    VFSnode* getParent() const;
    const std::vector<std::unique_ptr<VFSnode>>& getChildren() const;
};

#endif // VFSNODE_H
