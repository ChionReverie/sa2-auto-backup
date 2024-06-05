#include "pch.h"
#include "debug.h"

const char* MESSAGE_HEADER = "Automatic Backups";

void Debug::DisplayMessage(std::string message) {
  MessageBoxA(MainWindowHandle, message.c_str(), MESSAGE_HEADER, MB_ICONINFORMATION);
}

void Debug::Log(std::string message) {
  PrintDebug(message.c_str());
}