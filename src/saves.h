#include "pch.h"
#include "config.h"

void BackupSaves();

void PushSave(Configuration *config, char *filepath);

void PushSave(const string filename, const path dir_backup, const path dir_original);