
#include <functional>
#include <string>

void cli(std::function<std::string()> displayCatalogue,
         std::function<std::string(std::string)> search,
         std::function<std::string()> purchaseBook,
         std::function<std::string(int)> payForBook);
