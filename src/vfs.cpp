#include "vfs.h"
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>
#include <QDebug>

VFS::VFS(const QString& physicalPath)
{
    rootNode = std::make_unique<VFSnode>("/", NodeType::Directory);
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