#include "pch.h"
#include "config.h"
#include "saves.h"
#include <filesystem>
#include <UsercallFunctionHandler.h>

Configuration *config;

int On_WriteSaveFile(char *path, void *a2, size_t count);
UsercallFunc(
    int,
    WriteSaveFile_t,
    (char *mypath, void *a2, size_t count),
    (mypath, a2, count),
    0x426760,
    rEAX,
    rECX, rEDX, stack4);
int On_WriteSaveFile(char *path, void *a2, size_t count)
{
  auto result = WriteSaveFile_t.Original(path, a2, count);
  PushSave(config, path); // My function
  return result;
}

void ApplyHooks()
{
  WriteSaveFile_t.Hook(On_WriteSaveFile);
}

extern "C"
{
  // Optional.
  // This function runs code one time when the game starts up. Great for loading assets and setting things up.
  __declspec(dllexport) void __cdecl Init(const char *mod_dir, const HelperFunctions &helperFunctions)
  {

    ApplyHooks();

    auto result = configure(mod_dir, helperFunctions);
    if (!result.has_value())
    {
      std::stringstream message;
      message << "Errors were found in your Automatic Backups configuration file.\n\n";
      for (auto err : result.error())
      {
        message << err << "\n";
      }
      message << "\n"
              << "Please reconfigure your Automatic Backups mod. See README.md for further detail.";
      Debug::DisplayMessage(message.str().c_str());
    }
    config = result.value();

    BackupSaves();
  }

  __declspec(dllexport) void __cdecl OnExit()
  {
    delete config;
  }
  __declspec(dllexport) ModInfo SA2ModInfo = {ModLoaderVer}; // This is needed for the Mod Loader to recognize the DLL.
}
