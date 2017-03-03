#include "gstdafx.hpp"
#include "file.hpp"
#include "mmlfile.hpp"

namespace akmml
{
	MmlFile::MmlFile(std::string path) : File(path)
	{
	}

	MmlFile::MmlFile(MmlFile& f) : File(f)
	{
	}

	MmlFile::~MmlFile()
	{
	}

	bool MmlFile::open(std::ios::openmode m)
	{
		if(!m)
		{
			m = std::ios::in;
		}

		this->oMode = m;
		return this->_open();
	}

	char MmlFile::getch()
	{
	}

	char MmlFile::getforward()
	{
	}

	char MmlFile::getusp()
	{
	}

	bool MmlFile::cmpstr(std::string str)
	{
	}

	void MmlFile::skipchars()
	{
	}

	void MmlFile::skipspaces()
	{
	}
}
