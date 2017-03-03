//------------------------------------------------
// ファイル基底クラス
//------------------------------------------------
#include "gstdafx.hpp"
#include "file.hpp"

namespace akmml
{
	File::File(std::string sPath)
	{
		std::string::size_type pos;
		std::string sWork;

		this->sPath = sPath;

		//----------------------------
		// ディレクトリ名と、
		// ファイル名をセット
		//----------------------------
		sWork = sPath;
		pos = sWork.find_last_of('/');
#ifdef WIN32
		if(std::string::npos == pos)
		{
			pos = sWork.find_last_of('\\');
		}
#endif
		this->sDir = "";
		this->sName = sPath;
		if(std::string::npos != pos)
		{
			sWork.erase(pos+1, sWork.length());
			this->sDir = sWork;

			sWork = sPath;
			sWork.erase(0, pos+1);
			this->sName = sWork;
		}

		//----------------------------
		// 拡張子をセット
		//----------------------------
		pos = sWork.find_last_of('.');
		
		this->sExt = "";
		if(std::string::npos != pos)
		{
			sWork.erase(0, pos);
			this->sExt = sWork;
		}
	}

	//--------------------------------------
	// コピーコンストラクタ
	//--------------------------------------
	File::File(File& file) :
		sPath(file.getPath()),
		sName(file.getName()),
		sDir(file.getDir()),
		sExt(file.getExt()),
		oMode(file.getOpenMode()){}

	//--------------------------------------
	// オブジェクトの破棄
	//--------------------------------------
	File::~File()
	{
		this->stream.close();
	}

	//--------------------------------------
	// 拡張子変更
	//--------------------------------------
	void File::changeExt(std::string sExt)
	{
		uint32_t replaceLen;

		// 既存ファイル名の拡張子を削除します
		if(false == this->sExt.empty())
		{

			replaceLen = sPath.length() - sPath.find_last_of('.');

			sPath.erase(sPath.length()-replaceLen, replaceLen);
			sName.erase(sName.length()-replaceLen, replaceLen);
		}

		// 拡張子を追加します
		this->sPath.append(".");
		this->sPath.append(sExt);
		this->sName.append(".");
		this->sName.append(sExt);
		this->sExt = ".";
		this->sExt.append(sExt);
		return;
	}

	bool File::_open()
	{
		// TODO: mode指定がないときに例外を送出する
		// TODO: ファイル名がないときに例外を送出する
		stream.open(this->sPath, this->oMode);
		if(stream.fail())
		{
			return false;
		}
		// ファイル先頭に移動できるかチェックします
		// 移動できない(-1 が返る)場合、ディレクトリとみなします
		stream.seekg(0, std::ios::end);
		if(stream.fail() || (0 > static_cast<int>(stream.tellg())))
		{
			stream.close();
			return false;
		}
		stream.clear();
		return true;
	}

	void File::close()
	{
		stream.close();
	}

	size_t File::size()
	{
		std::ios::pos_type pos;
		size_t size;

		pos = stream.tellg();

		stream.seekg(0, std::fstream::end);
		std::ios::pos_type end = stream.tellg();

		stream.seekg(0, std::fstream::beg);
		std::ios::pos_type beg = stream.tellg();

		size = end - beg;

		stream.clear();
		stream.seekg(pos, std::fstream::beg);

		return size;
	}

}
