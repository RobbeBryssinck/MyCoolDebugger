#include "Attacher.h"

#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>

namespace Attacher
{
  std::pair<int, std::wstring> GetNameFromPID(int pid)
  {
    TCHAR name[MAX_PATH] = TEXT("<unknown>");

    HANDLE process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);

    if (process)
    {
      HMODULE mod;
      DWORD needed;

      if (EnumProcessModules(process, &mod, sizeof(mod), &needed))
        GetModuleBaseName(process, mod, name, sizeof(name)/sizeof(TCHAR));

      CloseHandle(process);
    }

    return { pid, {name} };
  }

  std::optional<std::vector<std::pair<int, std::wstring>>> GetListOfProcesses()
  {
    DWORD processes[1024]{};
    DWORD needed{};

    if (!EnumProcesses(processes, sizeof(processes), &needed))
      return std::nullopt;

    auto processCount = needed / sizeof(DWORD);

    std::vector<std::pair<int, std::wstring>> processList{};

    for (int i = 0; i < processCount; i++)
    {
      if (processes[i] != 0)
        processList.push_back(GetNameFromPID(processes[i]));
    }

    return processList;
  }

  AttachResult Attach(int pid)
  {
    return AttachResult::kSuccess;
  }
}