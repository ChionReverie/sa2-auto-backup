#include "pch.h"
#include "config.h"

void BackupIncrementally(Configuration *config);

void PushSave(Configuration *config, char *filepath);

void PushSave(const string filename, const path dir_backup, const path dir_original);