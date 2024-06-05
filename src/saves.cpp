#include "saves.h"

bool isChaoSave(string filename)
{
  if (filename.contains("SONIC2B__ALF"))
    return true;
  if (filename.contains(".chao"))
    return true;
  if (filename.contains(".ChaoSave"))
    return true;

  return false;
}

string getFormattedDate(CopyInterval interval)
{
  time_t now = time(0);
  tm t_struct;
  localtime_s(&t_struct, &now);

  char buf[80];

  if (interval == CopyInterval::Daily)
  {
    strftime(buf, sizeof(buf), "%Y-%m-%d", &t_struct);
  }
  else if (interval == CopyInterval::Weekly)
  {
    strftime(buf, sizeof(buf), "%Y-W%U", &t_struct);
  }
  else
  {
    return "";
  }
  return string(buf);
}

void BackupIncrementally(Configuration *config)
{
  string main_dirname = getFormattedDate(config->main_copy_interval);
  string chao_dirname = getFormattedDate(config->chao_copy_interval);

  path main_backups = std::filesystem::absolute(config->backup_main_dir / main_dirname);
  path chao_backups = std::filesystem::absolute(config->backup_chao_dir / chao_dirname);

  bool doMainBackups = config->enable_main_backups &&
                       !std::filesystem::exists(main_backups);
  bool doChaoBackups = config->enable_chao_backups &&
                       !std::filesystem::exists(chao_backups);

  if (doMainBackups)
  {
    std::filesystem::create_directories(main_backups);
    for (path my_save : std::filesystem::directory_iterator(config->source_main_dir))
    {
      // Skip directories and chao saves
      if (std::filesystem::is_directory(my_save))
        continue;
      if (isChaoSave(my_save.filename().string()))
        continue;

      auto source = std::filesystem::absolute(my_save);
      auto destination = std::filesystem::absolute(main_backups / my_save.filename());
      std::filesystem::copy_file(my_save, destination);
    }
  }

  if (doChaoBackups)
  {
    std::filesystem::create_directories(chao_backups);

    for (path my_save : std::filesystem::directory_iterator(config->source_chao_dir))
    {
      // Skip directories and main saves
      if (std::filesystem::is_directory(my_save))
        continue;
      if (!isChaoSave(my_save.filename().string()))
        continue;

      auto source = std::filesystem::absolute(my_save);
      auto destination = std::filesystem::absolute(chao_backups / my_save.filename());
      std::filesystem::copy_file(my_save, destination);
    }
  }
}

void PushSave(Configuration *config, char *filepath)
{
  string filename = std::filesystem::path(filepath).filename().string();

  // Chao saves
  if (isChaoSave(filename))
  {
    PushSave(filename, config->source_chao_dir, config->backup_chao_dir);
    return;
  }

  // Main saves
  PushSave(filename, config->source_main_dir, config->backup_main_dir);
}

void PushSave(const string filename, const path dir_original, const path dir_backup)
{
  path dir_latest = dir_backup / "latest";

  path file_original = std::filesystem::absolute(dir_original / filename);
  path file_latest = std::filesystem::absolute(dir_latest / filename);
  path file_old = std::filesystem::absolute(dir_latest / (filename + ".old"));

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