extern "C"
{
#include "FilePath.h"
#include "File.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(File)
{
	File file;

	void setup()
	{
		file = File_Create(FilePath_Create("/dev/null"));
	}

	void teardown()
	{
		File_Destroy(file);
	}
};

TEST(File, Create)
{
	/* init check */
	CHECK_EQUAL(0, File_GetSize(file));
}

TEST(File, Open)
{
	/* open check */
	CHECK_EQUAL(File_Open_NoMode, File_Open(file));

	/* multiple call check */
	CHECK_EQUAL(File_Open_NoMode, File_Open(file));

	CHECK_EQUAL(0, File_GetSize(file));
}

