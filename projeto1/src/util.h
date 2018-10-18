
namespace utils {
    struct option long_options[] = {
        {"algorithm", required_argument, NULL, 'a'},
        {"edit", required_argument, NULL, 'e'},
        {"pattern", required_argument, NULL, 'p'},
        {"count", no_argument, NULL, 'c'},
        {"help", no_argument, NULL, 'h'},
        {0, 0, 0, 0}};

    typedef struct argmnts
    {
        char *algorithm = nullptr;
        std::vector<std::string> patterns;
        std::vector<std::string> txt_files;
        uint8_t edit_dist = 0;
        char *pattern_file = nullptr;
        bool count_only = false;
    } argmnts;

    void getArguments(argmnts *arg, int argc, char *argv[]);
    bool choseAlg(argmnts *arg);
}
