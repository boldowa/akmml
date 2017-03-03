#include "gstdafx.hpp"
#include "romtype.hpp"

std::map<RomType::Type, std::string> RomType::typeName = {
	{ FinalFantasy4,   "Final Fantasy IV" },
	{ FinalFantasy5,   "Final Fantasy V" },
	{ FinalFantasy6,   "Final Fantasy VI" },
	{ RomancingSaGa1,  "Romancing SaGa" },
	{ RomancingSaGa2,  "Romancing SaGa 2" },
	{ RomancingSaGa3,  "Romancing SaGa 3" },
	{ SeikenDensetsu2, "聖剣伝説 2" },
	{ SeikenDensetsu3, "聖剣伝説 3" },
	{ ChronoTrigger,   "Chrono Trigger" },
	{ MysticQuest,     "Final Fantasy USA - Mystic Quest" },
	{ RudoranoHihou,   "ルドラの秘宝" },
	{ LiveALive,       "LIVE A LIVE" },
	{ FrontMission,    "FRONT MISSION" },
	{ GunHazard,       "FRONT MISSION SERIES GUN HAZARD" },
	{ HanjukuHero,     "半熟英雄 - ああ、世界よ半熟なれ…!!" },
	{ SuperMarioRPG,   "スーパーマリオRPG" },
};

