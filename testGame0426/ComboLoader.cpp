#include "ComboLoader.h"
#include <fstream>
#include "include/nlohmann/json.hpp"
using json = nlohmann::json;

std::vector<AttackStep> LoadCombo(const std::string& path)
{
	std::ifstream file(path);
	json j;
	file >> j;

	std::vector<AttackStep> combo;

	for (auto& item : j["combo"])
	{
		AttackStep step{};

		step.windupTime = item["windupTime"];
		step.activeTime = item["activeTime"];
		step.recoveryTime = item["recoveryTime"];

		step.damage = item["damage"];
		step.stunPower = item["stunPower"];

		step.attackMoveSpeed = item["attackMoveSpeed"];
		step.attackHitRadius = item["attackHitRadius"];
		step.attackForwardOffset = item["attackForwardOffset"];
		step.knockBackPower = item["knockBackPower"];

		combo.push_back(step);
	}

	return combo;
}