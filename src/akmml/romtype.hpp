#pragma once

class RomType
{
	public:
		typedef enum {
			FinalFantasy4 = 1,
			FinalFantasy5,
			FinalFantasy6,
			RomancingSaGa1,
			RomancingSaGa2,
			RomancingSaGa3,
			SeikenDensetsu2,
			SeikenDensetsu3,
			ChronoTrigger,
			MysticQuest,
			RudoranoHihou,
			LiveALive,
			FrontMission,
			GunHazard,
			HanjukuHero,
			SuperMarioRPG,
			/*----------------*/
			Unknown
		} Type;

		typedef enum {
			LoRom = 1,
			HiRom,
			ExLoRom,
			ExHiRom
		} Map;

	private:
		static std::map<RomType::Type, std::string> typeName;

	public:
		static std::string getTypeName(const Type t)
		{
			return RomType::typeName[t];
		}

};

