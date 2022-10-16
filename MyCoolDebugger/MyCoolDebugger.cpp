#include "Attacher.h"

#include <iostream>

int main()
{
  auto result = Attacher::GetListOfProcesses();
  if (!result)
  {
    exit(1);
  }

  auto& processes = *result;

  std::cout << "Processes: " << std::endl;
  for (const auto& process : processes)
    std::wcout << process.first << L" " << process.second << std::endl;

  int process = 0;
  std::cin >> process;

  Attacher::Attach(process);
}
