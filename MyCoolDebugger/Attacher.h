#pragma once

#include <vector>
#include <string>
#include <optional>

namespace Attacher
{
  enum class AttachResult
  {
    kSuccess
  };

  std::optional<std::vector<std::pair<int, std::wstring>>> GetListOfProcesses();

  AttachResult Attach(int pid);
}
