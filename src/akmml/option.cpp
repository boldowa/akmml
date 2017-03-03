#include "gstdafx.hpp"
#include "file.hpp"
#include "exefile.hpp"
#include "option.hpp"

const AkMmlOption::Options AkMmlOption::Ops[] = {
	{OptionType::Debug, "debug", 'd', "verbose debug info."},
	{OptionType::Help, "help", '?', "show usage"},
	{OptionType::Version, "version", 'v', "show version"},
	{0, "", 0, ""},
};

//----------------------------------------------------------
// バージョン情報の表示
void AkMmlOption::putVersion()
{
	std::cout << "akmml v" AKMML_VERSION << std::endl;
	std::cout << "  by boldowa" << std::endl;
	std::cout << "  since    : Dec  1 2016" << std::endl;
	std::cout << "  compiled : " << __DATE__ << std::endl;
	return;
}

//----------------------------------------------------------
// コンストラクタ
AkMmlOption::AkMmlOption(char* pg) : programName(pg)
{
}


//----------------------------------------------------------
// デストラクタ
AkMmlOption::~AkMmlOption()
{
	// ファイル名キューを空にします
	while(false == this->sInputs.empty())
	{
		sInputs.pop();
	}
}

//----------------------------------------------------------
// オプション展開
bool AkMmlOption::parseArgsOption(int argc, char** argv)
{
	bool isSucceed = true;
	const Options *op;
	int op_id;
	char *cmd = nullptr;
	char *param = nullptr;

	for(int index=1; index<argc; index++)
	{
		op_id = 0;
		cmd = (char*)argv[index];
		bool conCmd = false;

		if('-' == cmd[0])
		{
			for(op = Ops; op->id != 0; op++)
			{
				if('-' == cmd[1])
				{
					if(0 == op->name.compare(&cmd[2]))
					{
						op_id = op->id;
					}
				}
				else
				{
					if(cmd[1] != op->sname)
					{
						continue;
					}

					op_id = op->id;
					if('\0' != cmd[2])
					{
						conCmd = true;
					}
				}

			}

			if(0 == op_id)
			{
				puterror("Invalid command %s", cmd);
				isSucceed = false;
				continue;
			}

			param = &cmd[2];
			/*
			if(false == conCmd)
			{
				param = (char*)argv[++index];
				if(index >= argc)
				{
					puterror("Invalid command %s", cmd);
					err = true;
					continue;
				}
			}
			*/
			switch(op_id)
			{
				case OptionType::Debug:
					vdebug = true;
					break;

				case OptionType::Version:
					isPutVersion = true;
					break;

				case OptionType::Help:
					isPutUsage = true;
					break;

				default:
					break;
			}
		}
		else
		{
			sInputs.push(cmd);
		}
	}
	if(isPutVersion)
	{
		AkMmlOption::putVersion();
	}
	if(isPutUsage)
	{
		std::cout << "Usage: " << this->programName.getName()
			<< " [options] <input files>..." << std::endl;
		AkMmlOption::putOptions();
		return true;
	}

	if(this->sInputs.empty())
	{
		puterror("Missing input file.");
		isSucceed = false;
	}

	if(false == isSucceed)
	{
		std::cout << "Please try '-?' or '--help' option, and you can get more information." << std::endl;
		return false;
	}
	return isSucceed;
}

//----------------------------------------------------------
// オプションの取得
bool AkMmlOption::isPutUsageEnabled() const
{
       return this->isPutUsage;
}

//----------------------------------------------------------
// オプションの表示
void AkMmlOption::putOptions()
{
	const Options *op;
	std::cout << "Options: " << std::endl;
	for(op = Ops; op->id != 0; op++)
	{
		printf("  -%c, --%-14s %.45s\n", op->sname, op->name.c_str(), op->description.c_str());
	}
}

//----------------------------------------------------------
// 入力ファイル名の取得
std::string AkMmlOption::dequeInputs()
{
	if(this->sInputs.empty())
	{
		return std::string("");
	}

	std::string sInput = this->sInputs.front();
	this->sInputs.pop();
	return sInput;
}

