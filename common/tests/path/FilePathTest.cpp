extern "C"
{
#include "FilePath.h"
}

#include "CppUTest/TestHarness.h"

#define Dir "/foo/"
#define Name "bar"
#define Ext ".biz"
#define Path "/foo/bar.biz"
TEST_GROUP(FilePath)
{
	FilePath filePath;
	FilePath filePath2;
	FilePath filePathClone;

	void setup()
	{
		filePath = FilePath_Create(Path);
		filePath2 = FilePath_Create(NULL);
		filePathClone = FilePath_Clone(filePath);
	}

	void teardown()
	{
		FilePath_Destroy(filePath);
		FilePath_Destroy(filePath2);
		FilePath_Destroy(filePathClone);
	}
};

TEST(FilePath, Create)
{
	STRCMP_EQUAL(Dir, FilePath_GetDir(filePath));
	STRCMP_EQUAL(Name, FilePath_GetName(filePath));
	STRCMP_EQUAL(Ext, FilePath_GetExt(filePath));
	STRCMP_EQUAL(Path, FilePath_GetPath(filePath));

	STRCMP_EQUAL(NULL, FilePath_GetDir(filePath2));
	STRCMP_EQUAL(NULL, FilePath_GetName(filePath2));
	STRCMP_EQUAL(NULL, FilePath_GetExt(filePath2));
	STRCMP_EQUAL(NULL, FilePath_GetPath(filePath2));

	STRCMP_EQUAL(Dir, FilePath_GetDir(filePathClone));
	STRCMP_EQUAL(Name, FilePath_GetName(filePathClone));
	STRCMP_EQUAL(Ext, FilePath_GetExt(filePathClone));
	STRCMP_EQUAL(Path, FilePath_GetPath(filePathClone));
}

TEST(FilePath, Set_Success)
{
	/* Set Dir */
	CHECK(FilePath_SetDir(filePath, "/bar/"));
	STRCMP_EQUAL("/bar/", FilePath_GetDir(filePath));
	STRCMP_EQUAL(Name, FilePath_GetName(filePath));
	STRCMP_EQUAL(Ext, FilePath_GetExt(filePath));
	STRCMP_EQUAL("/bar/" Name Ext, FilePath_GetPath(filePath));
	CHECK(FilePath_SetDir(filePath, Dir));

	/* Set Name */
	CHECK(FilePath_SetName(filePath, "foo"));
	STRCMP_EQUAL(Dir, FilePath_GetDir(filePath));
	STRCMP_EQUAL("foo", FilePath_GetName(filePath));
	STRCMP_EQUAL(Ext, FilePath_GetExt(filePath));
	STRCMP_EQUAL(Dir "foo" Ext, FilePath_GetPath(filePath));
	CHECK(FilePath_SetName(filePath, Name));

	/* Set Extension */
	CHECK(FilePath_SetExt(filePath, ".z"));
	STRCMP_EQUAL(Dir, FilePath_GetDir(filePath));
	STRCMP_EQUAL(Name, FilePath_GetName(filePath));
	STRCMP_EQUAL(".z", FilePath_GetExt(filePath));
	STRCMP_EQUAL(Dir Name ".z", FilePath_GetPath(filePath));
	CHECK(FilePath_SetExt(filePath, Ext));

	/* Set Path */
	CHECK(FilePath_SetPath(filePath, "../aaa/bbb/cc.dddddd"));
	STRCMP_EQUAL("../aaa/bbb/", FilePath_GetDir(filePath));
	STRCMP_EQUAL("cc", FilePath_GetName(filePath));
	STRCMP_EQUAL(".dddddd", FilePath_GetExt(filePath));
	STRCMP_EQUAL("../aaa/bbb/cc.dddddd", FilePath_GetPath(filePath));

	/* Clone */
	FilePath clone = FilePath_Clone(filePath);
	STRCMP_EQUAL("../aaa/bbb/", FilePath_GetDir(clone));
	STRCMP_EQUAL("cc", FilePath_GetName(clone));
	STRCMP_EQUAL(".dddddd", FilePath_GetExt(clone));
	STRCMP_EQUAL("../aaa/bbb/cc.dddddd", FilePath_GetPath(clone));
	FilePath_Destroy(clone);
	CHECK(FilePath_SetPath(filePath, Path));

	/* Set dir-less path */
	CHECK(FilePath_SetPath(filePath, "xxx.yyy"));
	STRCMP_EQUAL("", FilePath_GetDir(filePath));
	STRCMP_EQUAL("xxx", FilePath_GetName(filePath));
	STRCMP_EQUAL(".yyy", FilePath_GetExt(filePath));
	STRCMP_EQUAL("xxx.yyy", FilePath_GetPath(filePath));

	/* Set name-less path */
	CHECK(FilePath_SetPath(filePath, "/xxx/.yyy"));
	STRCMP_EQUAL("/xxx/", FilePath_GetDir(filePath));
	STRCMP_EQUAL("", FilePath_GetName(filePath));
	STRCMP_EQUAL(".yyy", FilePath_GetExt(filePath));
	STRCMP_EQUAL("/xxx/.yyy", FilePath_GetPath(filePath));

	/* Set extention-less path */
	CHECK(FilePath_SetPath(filePath, "/xxx/yyy"));
	STRCMP_EQUAL("/xxx/", FilePath_GetDir(filePath));
	STRCMP_EQUAL("yyy", FilePath_GetName(filePath));
	STRCMP_EQUAL("", FilePath_GetExt(filePath));
	STRCMP_EQUAL("/xxx/yyy", FilePath_GetPath(filePath));

	/* Set dir only path */
	CHECK(FilePath_SetPath(filePath, "/xxx/yyy/"));
	STRCMP_EQUAL("/xxx/yyy/", FilePath_GetDir(filePath));
	STRCMP_EQUAL("", FilePath_GetName(filePath));
	STRCMP_EQUAL("", FilePath_GetExt(filePath));
	STRCMP_EQUAL("/xxx/yyy/", FilePath_GetPath(filePath));

	/* Set name only path */
	CHECK(FilePath_SetPath(filePath, "xxx"));
	STRCMP_EQUAL("", FilePath_GetDir(filePath));
	STRCMP_EQUAL("xxx", FilePath_GetName(filePath));
	STRCMP_EQUAL("", FilePath_GetExt(filePath));
	STRCMP_EQUAL("xxx", FilePath_GetPath(filePath));

	/* Set ext only path */
	CHECK(FilePath_SetPath(filePath, ".yyy"));
	STRCMP_EQUAL("", FilePath_GetDir(filePath));
	STRCMP_EQUAL("", FilePath_GetName(filePath));
	STRCMP_EQUAL(".yyy", FilePath_GetExt(filePath));
	STRCMP_EQUAL(".yyy", FilePath_GetPath(filePath));

	CHECK(FilePath_SetPath(filePath, Path));
}

TEST(FilePath, Set_Fail)
{
	/* Check path overflow */
	CHECK_FALSE(FilePath_SetPath(filePath, "/aaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/bbbbbbbb.cc"));
	STRCMP_EQUAL(Dir, FilePath_GetDir(filePath));
	STRCMP_EQUAL(Name, FilePath_GetName(filePath));
	STRCMP_EQUAL(Ext, FilePath_GetExt(filePath));
	STRCMP_EQUAL(Path, FilePath_GetPath(filePath));

	/* Check dir overflow */
	CHECK_FALSE(FilePath_SetDir(filePath, "/aaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/aaaaaaaaa/xxxx/"));
	STRCMP_EQUAL(Dir, FilePath_GetDir(filePath));
	STRCMP_EQUAL(Name, FilePath_GetName(filePath));
	STRCMP_EQUAL(Ext, FilePath_GetExt(filePath));
	STRCMP_EQUAL(Path, FilePath_GetPath(filePath));

	/* Check name overflow */
	CHECK_FALSE(FilePath_SetName(filePath, "x12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901"));
	STRCMP_EQUAL(Dir, FilePath_GetDir(filePath));
	STRCMP_EQUAL(Name, FilePath_GetName(filePath));
	STRCMP_EQUAL(Ext, FilePath_GetExt(filePath));
	STRCMP_EQUAL(Path, FilePath_GetPath(filePath));

	/* Check extension overflow */
	CHECK_FALSE(FilePath_SetExt(filePath, ".x12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901"));
	STRCMP_EQUAL(Dir, FilePath_GetDir(filePath));
	STRCMP_EQUAL(Name, FilePath_GetName(filePath));
	STRCMP_EQUAL(Ext, FilePath_GetExt(filePath));
	STRCMP_EQUAL(Path, FilePath_GetPath(filePath));

	/* Check limit */
	CHECK(FilePath_SetExt(filePath, ".x1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"));
	STRCMP_EQUAL(".x1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890", FilePath_GetExt(filePath));
}

