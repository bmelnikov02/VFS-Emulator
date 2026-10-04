#include "VFSnode.h"


VFSnode::VFSnode(const QString& name, NodeType type, VFSnode* parent)
    : name(name)
    , type(type)
    , parent(parent)
    , permissions(type == NodeType::Directory ? 0755 : 0644)
{
}

VFSnode* VFSnode::addChild(const QString& name, NodeType type)
{
    auto child = std::make_unique<VFSnode>(name, type, this);
    VFSnode* child_ptr = child.get();
    children.push_back(std::move(child));
    return child_ptr;
}

const QString& VFSnode::getName() const
{
    return name;
}

NodeType VFSnode::getType() const
{
    return type;
}

VFSnode* VFSnode::getParent() const
{
    return parent;
}

const std::vector<std::unique_ptr<VFSnode>>& VFSnode::getChildren() const
{
    return children;
}

int VFSnode::getPermissions() const
{
    return permissions;
}

void VFSnode::setPermissions(int permissions)
{
    this->permissions = permissions;
}