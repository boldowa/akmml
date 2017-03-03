#pragma once
//------------------------------------------------
// ファイル基底クラス
//------------------------------------------------
namespace akmml
{
	class File
	{
		protected:
			//----------------------------
			// ファイルパス
			//----------------------------
			std::string sPath;
			//----------------------------
			// ファイル名
			//----------------------------
			std::string sName;
			//----------------------------
			// ファイルのあるディレクトリ
			//----------------------------
			std::string sDir;
			//----------------------------
			// 拡張子
			//----------------------------
			std::string sExt;
			//----------------------------
			// ファイルストリーム
			//----------------------------
			std::fstream stream;
			//----------------------------
			// ファイルオープンモード
			//----------------------------
			std::ios::openmode oMode;


			//----------------------------
			// ファイルオープン
			//----------------------------
			bool _open();

			//----------------------------
			// ファイルクローズ
			//----------------------------
			void close();

		public:
			File(std::string);
			File(File&);
			virtual ~File();
			virtual bool open(std::ios::openmode) = 0;

			//----------------------------
			// 各要素の取得関数
			//----------------------------
			inline std::string getPath() const{ return this->sPath; }
			inline std::string getName() const{ return this->sName; }
			inline std::string getDir() const{ return this->sDir; }
			inline std::string getExt() const{ return this->sExt; }
			inline std::ios::openmode getOpenMode() const{ return this->oMode; }

			//----------------------------
			// 拡張子変更
			//----------------------------
			void changeExt(std::string);

			//----------------------------
			// ファイルストリームサイズを返す
			//----------------------------
			size_t size();
	};
}
