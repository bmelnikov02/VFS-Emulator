#include <QtTest>
#include "../src/vfs.h"

class VFSTest : public QObject
{
    Q_OBJECT

private slots:
    void chmodChangesPermissions();
    void chmodNonexistentFile();
    void cpCopiesFile();
    void cpCopiesDirectory();
    void cpExistingDestination();
};

void VFSTest::chmodChangesPermissions()
{
    VFS vfs(TEST_VFS_DIR);

    QCOMPARE(vfs.getPermissions("a.txt"), 0644);

    bool result = vfs.changePermissions("a.txt", 0700);

    QVERIFY(result);
    QCOMPARE(vfs.getPermissions("a.txt"), 0700);
}

void VFSTest::chmodNonexistentFile()
{
    VFS vfs(TEST_VFS_DIR);

    bool result = vfs.changePermissions("nonexistent.txt", 0700);

    QVERIFY(!result);
    QCOMPARE(vfs.getPermissions("nonexistent.txt"), -1);
}

void VFSTest::cpCopiesFile()
{
    VFS vfs(TEST_VFS_DIR);

    bool result = vfs.copyNode("a.txt", "a_copy.txt");

    QVERIFY(result);

    QVERIFY(vfs.listCurrentDirectory().contains("a_copy.txt"));

    QCOMPARE(
        vfs.getPermissions("a_copy.txt"),
        vfs.getPermissions("a.txt")
        );
}

void VFSTest::cpCopiesDirectory()
{
    VFS vfs(TEST_VFS_DEEP_DIR);

    bool result = vfs.copyNode("level1", "level1_copy");

    QVERIFY(result);
    QVERIFY(vfs.listCurrentDirectory().contains("level1_copy"));
    QVERIFY(vfs.changeDirectory("level1_copy"));
    QVERIFY(vfs.changeDirectory("level2"));
    QVERIFY(vfs.changeDirectory("level3"));

    QVERIFY(vfs.listCurrentDirectory().contains("file.txt"));
}

void VFSTest::cpExistingDestination()
{
    VFS vfs(TEST_VFS_DIR);

    bool result = vfs.copyNode("a.txt", "a.txt");

    QVERIFY(!result);

    QCOMPARE(vfs.listCurrentDirectory().count("a.txt"), 1);
    QCOMPARE(vfs.getPermissions("a.txt"), 0644);
}

QTEST_MAIN(VFSTest)

#include "test_vfs.moc"