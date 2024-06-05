#pragma once

#include <string>
#include <expected>
#include <vector>
#include <filesystem>

using std::string;
using std::vector;
using std::expected;
using std::filesystem::path;

enum CopyInterval {
	// Keep latest saves only
	Latest,
	// Make a extra copy each week in additional to the latest
	Weekly,
	// Make an extra copy every day in addition to the latest
	Daily,
};

class Configuration {
	public:
		path backup_root;

		bool enable_main_backups = true;
		path backup_main_dir;
		path source_main_dir;
		CopyInterval main_copy_interval;
		
		bool enable_chao_backups = true;
		path backup_chao_dir;
		path source_chao_dir;
		CopyInterval chao_copy_interval;
};

auto configure(const char* mod_dir, const HelperFunctions& helperFunctions) -> std::expected<Configuration*, vector<string>>;

auto readConfigFile(string configPath) -> std::expected<Configuration*, vector<string>>;

void chooseModSaveFolders(Configuration* config, const ModList* mods);
