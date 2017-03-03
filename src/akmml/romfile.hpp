#pragma once
namespace akmml
{
	class RomFile : public File
	{
		private:
			static const std::array<uint8_t, 13> initSpcCode;

			RomType::Type type = RomType::Unknown;
			RomType::Map romMap = RomType::LoRom;
			bool hasHeader = false;
			//std::vector<uint8_t> buffer;

			bool checkRomSum(std::ios::pos_type);
			void checkLoRomType();
			void checkHiRomType();

		public:
			RomFile(std::string);
			RomFile(RomFile&);
			~RomFile();
			bool open(std::ios::openmode=(std::ios::openmode)0);
			void checkType();
			inline RomType::Type getType(){ return this->type; }
	};
}
