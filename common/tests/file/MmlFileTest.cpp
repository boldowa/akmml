extern "C"
{
#include "FilePath.h"
#include "File.h"
#include "MmlFile.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(MmlFile)
{
    MmlFile mmlfile;

    void setup()
    {
        mmlfile = MmlFile_Create(FilePath_Create("tests/file/mml/open.mml"));
    }

    void teardown()
    {
        MmlFile_Destroy(mmlfile);
    }
};

TEST(MmlFile, Create)
{
	LONGS_EQUAL(0, MmlFile_GetSize(mmlfile));
}

TEST(MmlFile, Open)
{
	/* Open success test */
	LONGS_EQUAL(File_Open_NoError, MmlFile_Open(mmlfile));
	LONGS_EQUAL(10, MmlFile_GetSize(mmlfile));

	/* Open fail test */
	LONGS_EQUAL(File_Open_AlreadyOpen, MmlFile_Open(mmlfile));

	/* Open fail test */
	MmlFile x = MmlFile_Create(FilePath_Create(""));
	LONGS_EQUAL(File_Open_CantOpen, MmlFile_Open(x));
	MmlFile_Destroy(x);
}

