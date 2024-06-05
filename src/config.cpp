#include "pch.h"
#include "config.h"
#include <IniFile.hpp>
#include <expected>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;

const string CONFIGGROUP_GENERAL = "General";

static const std::unordered_map<string, CopyInterval> s_to_copyinterval = {
		{"latest", Latest},
		{"weekly", Weekly},
		{"daily", Daily},
};

auto configure(const char *mod_dir, const HelperFunctions &helperFunctions) -> std::expected<Configuration *, vector<string>>
{
	auto configPath = std::filesystem::path(mod_dir) / "config.ini";
	configPath = std::filesystem::absolute(configPath);
	if (!std::filesystem::exists(configPath))
	{
		vector<string> vec = {"Error: Automatic Backups needs configuration."};
		return std::unexpected(vec);
	}

	// Read config
	auto result = readConfigFile(configPath.string());
	if (!result.has_value())
	{
		return result;
	}

	Configuration *config = result.value();

	// Save directories
	config->source_main_dir = path(helperFunctions.GetMainSavePath());
	config->source_chao_dir = path(helperFunctions.GetChaoSavePath());
	config->backup_main_dir = config->backup_root / "vanilla";
	config->backup_chao_dir = config->backup_root / "vanilla";
	chooseModSaveFolders(config, helperFunctions.Mods);

	return config;
}

auto readConfigFile(string configPath) -> std::expected<Configuration *, vector<string>>
{
	IniFile ini = IniFile(configPath);
	Configuration config;
	vector<string> errorList;

	// Backup Root
	string backup_root = ini.getString(CONFIGGROUP_GENERAL, "BackupDirectory", "");
	if (backup_root == "")
		errorList.push_back("BackupsDirectory is empty. You must configure a backups location.");
	else
		config.backup_root = backup_root;

	// Main copy Interval
	{
		string copy_interval = ini.getString(CONFIGGROUP_GENERAL, "MainCopyInterval", "Latest");
		transform(
				copy_interval.begin(),
				copy_interval.end(),
				copy_interval.begin(),
				tolower);
		if (s_to_copyinterval.count(copy_interval) == 0)
			errorList.push_back("MainCopyInterval is an unsupported string.");
		else
			config.main_copy_interval = s_to_copyinterval.at(copy_interval);
	}

	// Chao copy Interval
	{
		string copy_interval = ini.getString(CONFIGGROUP_GENERAL, "ChaoCopyInterval", "Latest");
		transform(
				copy_interval.begin(),
				copy_interval.end(),
				copy_interval.begin(),
				tolower);
		if (s_to_copyinterval.count(copy_interval) == 0)
			errorList.push_back("ChaoCopyInterval is an unsupported string.");
		else
			config.chao_copy_interval = s_to_copyinterval.at(copy_interval);
	}

	if (errorList.size() > 0)
	{
		return std::unexpected(errorList);
	}

	return new Configuration(config);
}

void chooseModSaveFolders(Configuration *config, const ModList *mods)
{
	unsigned int main_redirect_modcount = 0;
	unsigned int chao_redirect_modcount = 0;
	// Read mods
	const unsigned int modcount = mods->size();
	for (unsigned int i = 0; i < modcount; i++)
	{
		const Mod mod = mods->at(i);
		if (mod.MainSaveRedirect)
		{
			main_redirect_modcount++;
			config->source_main_dir = path(mod.Folder) / "SAVEDATA";
			config->backup_main_dir = config->backup_root / mod.Folder;
		}
		if (mod.ChaoSaveRedirect)
		{
			chao_redirect_modcount++;
			config->source_chao_dir = path(mod.Folder) / "SAVEDATA";
			config->backup_chao_dir = config->backup_root / mod.Folder;
		}
	}
	// Error checking
	if (main_redirect_modcount > 1)
	{
		Debug::DisplayMessage("Warning: You have more than one save-redirecting mod enabled for main saves. Main backups have been disabled.");
		config->enable_main_backups = false;
	}
	if (chao_redirect_modcount > 1)
	{
		Debug::DisplayMessage("Warning: You have more than one save-redirecting mod enabled for Chao saves. Chao backups have been disabled.");
		config->enable_chao_backups = false;
	}
}