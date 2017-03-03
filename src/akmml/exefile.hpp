#pragma once
namespace akmml
{
	class ExeFile : public File
	{
		public:
			ExeFile(std::string);
			ExeFile(ExeFile&);
			~ExeFile();
			bool open(std::ios::openmode);
	};
}
