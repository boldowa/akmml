#include "gstdafx.hpp"
#include "file.hpp"
#include "exefile.hpp"

namespace akmml
{
	ExeFile::ExeFile(std::string path) : File(path)
	{
	}

	ExeFile::ExeFile(ExeFile& f) : File(f)
	{
	}

	ExeFile::~ExeFile()
	{
	}

	bool ExeFile::open(std::ios::openmode m)
	{
		// 実行ファイルのオープンは、常に失敗とする
		return false;
	}
}
