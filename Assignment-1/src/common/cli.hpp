#include <functional>
#include <string>

void cli(std::function<std::string()> display,
         std::function<std::string(std::string)> search,
         std::function<std::string()> purchaseBook,
         std::function<std::string(int)> payForBook,
         std::function<void()> exit);
