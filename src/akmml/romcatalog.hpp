#pragma once
//----------------------------------------------------------
// ROMファイルカタログ
//----------------------------------------------------------
namespace akmml
{
	class RomCatalog
	{
		private:
			std::map<RomType::Type, RomFile*> roms;

		public:
			RomCatalog(std::string);
			~RomCatalog();
			inline bool empty(){ return this->roms.empty(); }
	};
}
