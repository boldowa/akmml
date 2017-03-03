#pragma once
namespace akmml
{
	class MmlFile : public File
	{
		private:
			// 曲名
			std::string title;

			// ゲーム名
			std::string game;

			// 作曲者
			std::string composer;

			// 作成者
			std::string author;

			// コメント
			std::string comment;

			// 曲の長さ
			int playingTime;

			// フェード時間
			int fadeTime;

			// EDL最大値
			int maxEDL;

			// mml読み込みバッファ
			std::string buffer;
			uint32_t buffInx;
			uint32_t mmlReadTimes;

			// ファイル末尾かどうか
			bool iseof;

			// 改行があったかどうか
			bool isnewline;

			// 行
			uint32_t line;

			// 列
			uint32_t column;

			// 行内で最初のスペース以外の文字の位置
			uint32_t firstCharColumn;

			// TODO: マクロ(辞書 - (定義保存) /スタック - (実行))


		public:
			MmlFile(std::string);
			MmlFile(MmlFile&);
			~MmlFile();
			bool open(std::ios::openmode);

			//--------------------------------------
			// 関数
			//--------------------------------------

			char getch();
			char getforward();
			char getusp();
			bool cmpstr(std::string);
			bool isFirstChar();
			void skipchars();
			void skipspaces();
	};
}
