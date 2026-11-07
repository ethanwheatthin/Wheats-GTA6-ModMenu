#include <windows.h>

// Entry point for the .asi plugin, loaded by an ASI loader into the game
// process. Unimplemented: wiring to adapters/gtav + ui is future M1+ work,
// blocked on a developer with the real SHV SDK.
//
// Per AGENTS.md hard rules: before doing anything else, this must check
// GameAdapter::is_online_session() and unload itself if true.
BOOL APIENTRY DllMain(HMODULE /*module*/, DWORD reason, LPVOID /*reserved*/) {
  switch (reason) {
    case DLL_PROCESS_ATTACH:
      break;
    case DLL_PROCESS_DETACH:
      break;
    default:
      break;
  }
  return TRUE;
}
