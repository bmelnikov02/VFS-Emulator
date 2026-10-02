#include "vfs.h"
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>
#include <QDebug>


VFS::VFS(const QString& physicalPath)
{
    rootNode = std::make_unique<VFSnode>("/", NodeType::Directory);
    currentNode = rootNode.get();
    QDir dir(physicalPath);
    if (!dir.exists())
    {
        return;
    }
    loadDirectory(physicalPath, rootNode.get());
    qDebug() << "Root children:" << rootNode->getChildren().size();
}

void VFS::loadDirectory(const QString& physicalPath, VFSnode* parentNode)
{
    QDir dir(physicalPath);
    QFileInfoList entries = dir.entryInfoList(
        QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot
    );
    for(auto entry : entries)
    {
        if (entry.isDir())
        {
            VFSnode* childNode = parentNode->addChild(entry.fileName(), NodeType::Directory);
            loadDirectory(entry.absoluteFilePath(), childNode);

        }
        else if (entry.isFile())
        {
            parentNode->addChild(entry.fileName(), NodeType::File);
        }
    }
}

QStringList VFS::listCurrentDirectory() const
{
    QStringList result;
    for (const auto& child : currentNode->getChildren())
    {
        result.append(child->getName());
    }
    return result;
}

bool VFS::changeDirectory(const QString& name)
{
    if (name == "..")
    {
        if (currentNode->getParent() != nullptr)
        {
            currentNode = currentNode->getParent();
            return true;
        }
        return false;
    }
    for (const auto& child : currentNode->getChildren())
    {
        if (child->getName() == name && child->getType() == NodeType::Directory)
        {
            currentNode = child.get();
            return true;
        }
    }
    return false;
}

QString VFS::tree() const
{
    QString result;
    buildTree(rootNode.get(), 0, result);
    return result;
}

void VFS::buildTree(const VFSnode* node, int depth, QString& result) const
{
    result += QString(depth * 2,' ') + node->getName() + '\n';
    for (const auto& child : node->getChildren())
    {
        buildTree(child.get(),depth+1,result);
    }
}