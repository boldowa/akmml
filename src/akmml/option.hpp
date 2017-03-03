#pragma once
//--------------------------------------------------------------------
// オプション情報クラス
//--------------------------------------------------------------------

class AkMmlOption
{
	public:
		//----------------------------
		// オプション構造体
		//----------------------------
		typedef struct {
			int  id;
			std::string name;
			char sname;
			std::string description;
		}Options;

		//----------------------------
		// 実行ファイル名
		//----------------------------
		const akmml::ExeFile programName;
	private:
		//----------------------------
		// オプション
		//----------------------------
		typedef enum {
			Debug = 1,
			Help,
			Version,
		}OptionType;

		//----------------------------
		// リンク種別
		//----------------------------
		typedef enum {
			LinkSpc = 0,
			LinkSnsf,
			LinkNothing,
		}LinkType;

		//----------------------------
		// オプション
		//----------------------------
		static const Options Ops[];

		//----------------------------
		// 使い方の表示
		//----------------------------
		bool isPutUsage = false;

		//----------------------------
		// バージョン情報の表示
		//----------------------------
		bool isPutVersion = false;

		//----------------------------
		// リンク種別
		//----------------------------
		LinkType linkType = LinkSpc;

		//----------------------------
		// 入力ファイル
		//----------------------------
		std::queue<std::string> sInputs;

	public:
		AkMmlOption(char*);
		~AkMmlOption();
		bool parseArgsOption(int, char**);
		bool isPutVersionEnabled() const;
		bool isPutUsageEnabled() const;
		static void putOptions();
		static void putVersion();
		std::string dequeInputs();
};

