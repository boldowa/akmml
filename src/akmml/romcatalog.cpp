#include "gstdafx.hpp"
#include "file.hpp"
#include "romtype.hpp"
#include "romfile.hpp"
#include "romcatalog.hpp"
//----------------------------------------------------------
// ROMファイルカタログ(データベース)
//----------------------------------------------------------
namespace akmml
{
	//------------------------------------------------
	// 指定されたディレクトリ以下のROMを検索し、
	// ROMデータベースを構築します
	//------------------------------------------------
	RomCatalog::RomCatalog(std::string searchDir)
	{
		dirent *entry;
		DIR *dp;

		dp = opendir(searchDir.c_str());
		if(NULL == dp) return;

		do {
			entry = readdir(dp);
			//if(NULL != entry && DT_REG == entry->d_type)
			if(NULL != entry)
			{
				std::string romPath = searchDir;
				romPath.append(entry->d_name);
				RomFile* rom = new RomFile(romPath);
				putdebug("Rom found: %s", rom->getPath().c_str());
				rom->checkType();
				if(RomType::Unknown == rom->getType())
				{
					putdebug("  -> Unknown Rom.");
					delete rom;
					continue;
				}
				putinfo("ROM data detect: %s", RomType::getTypeName(rom->getType()).c_str());
				roms.insert(std::make_pair(rom->getType(), rom));
			}
		} while(NULL != entry);
	}

	//------------------------------------------------
	// ROMデータベースを廃棄します
	//------------------------------------------------
	RomCatalog::~RomCatalog()
	{
		for(auto it=begin(roms); it != end(roms); it++)
		{
			putdebug("delete rom catalog: %s", it->second->getPath().c_str());
			delete it->second;
			roms.erase(it);
		}
	}
}
