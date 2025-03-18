#include <iostream>
#include <filesystem>
#include <chrono>
#include <iomanip>
#include <sstream>

namespace fs = std::filesystem;

std::string getCurrentDate()
{
    auto now = std::chrono::system_clock::now();
    auto timeT = std::chrono::system_clock::to_time_t(now);
    std::tm localTime;
    localtime_s(&localTime, &timeT);

    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y%m%d-%H%M%S");
    return oss.str();
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    fs::path originalFile(argv[1]);
    if (!fs::exists(originalFile))
    {
        std::cerr << "File does not exist: " << originalFile << std::endl;
        return 1;
    }

    std::string dateStr = getCurrentDate();
    fs::path newFile = originalFile.parent_path() / (originalFile.stem().string() + "_" + dateStr + originalFile.extension().string());

    try
    {
        fs::rename(originalFile, newFile);
        std::cout << "Renamed to: " << newFile << std::endl;
    }
    catch (const fs::filesystem_error& e)
    {
        std::cerr << "Error renaming file: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
