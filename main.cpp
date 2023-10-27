#include <fstream>

int main(int argc, char const *argv[])
{
    std::ifstream fileStream(RunConfig::inputFilePath.data());
    return 0;
}
