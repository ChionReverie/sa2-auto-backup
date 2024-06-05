#include "saves.h"

void BackupSaves()
{
  // Check lastplayed.ini for if a new cycle has begun
  // Create new folder for the current cycle
  // Copy latest saves to the new folder
  // Update lastplayed.ini
}

void PushSave(Configuration *config, char *filepath)
{
  string filename = std::filesystem::path(filepath).filename().string();

  const string CHAO_SAVENAME = "SONIC2B__ALF";
  if (filename.contains(CHAO_SAVENAME))
  {
    PushSave(filename, config->source_chao_dir, config->backup_chao_dir);
  }
  else
  {
    PushSave(filename, config->source_main_dir, config->backup_main_dir);
  }
}

void PushSave(const string filename, const path dir_original, const path dir_backup)
{
  path dir_latest = dir_backup / "latest";

  path file_original = std::filesystem::absolute(dir_original / filename);
  path file_latest = std::filesystem::absolute(dir_latest / filename);
  path file_old = std::filesystem::absolute(dir_latest / (filename + ".old"));

  Debug::DisplayMessage(
      file_original.string() + "\n" +
      file_latest.string() + "\n" +
      file_old.string() + "\n");

  std::filesystem::create_directories(dir_latest);
  // Delete old
  if (std::filesystem::exists(file_old))
  {
    std::filesystem::remove(file_old);
  }
  // Rename latest to old
  if (std::filesystem::exists(file_latest))
  {
    std::filesystem::rename(file_latest, file_old);
  }
  // Copy current to latest
  if (std::filesystem::exists(file_original))
  {
    std::filesystem::copy_file(file_original, file_latest);
  }
}