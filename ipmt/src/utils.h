#include <getopt.h>
#include <vector>
#include <string.h>
#include <fstream>


#include "lz77.h"
#include "SArray.h"

#define DEBUG_UTILS 0


namespace utils {   
    struct option long_options[] = {
        {"pattern", required_argument, NULL, 'p'},
        {"count", no_argument, NULL, 'c'},
        {"index", no_argument, NULL, 'i'},
        {"compress", no_argument, NULL, 'z'},
        {"help", no_argument, NULL, 'h'},
        {0, 0, 0, 0}};

    typedef struct argmnts
    {
        std::vector<std::string> patterns;
        uint max_pattern = 0;
        std::vector<std::string> txt_files;
        char *pattern_file = nullptr;
        bool count_only = false;
        bool index_only = false;
        bool compress_only = false;
        int option = 0;
    } argmnts;

    void print_help()
    {
        printf("\n ipmt [-c] [-p FILE]|PATTERN INDEX \n");
        printf("Search pattern in a indexed file, and INDEX should end with .idx .\n");
        printf("\n ipmt [-z | -i] FILE \n");
        printf("Index the FILE, and it should end with .txt .\n");
        printf("\t--index     -i               Index and compress the FILE\n");
        printf("\t--compress  -z               Only compress the FILE\n");
        printf("\t--pattern   -p FILE          Search each pattern on file, one per line\n");
        printf("\t--count     -c               Print only occurrences count\n");
        printf("\t--help      -h               Show help\n");
        printf("Made by: Lucas Cavalcanti and Roberto Fernandes  - {lhcs, rcf6}@cin.ufpe.br\n");
    }

    bool getArguments(argmnts *arg, int argc, char *argv[])
    {
        char opt;
        while ((opt = getopt_long(argc, argv, "p:cizh", long_options, NULL)) != -1)
        {
            switch (opt)
            {
            case 'i':
                arg->index_only = true;
                break;
            case 'z':
                arg->compress_only = true;
                break;
            case 'p':
                arg->pattern_file = strdup(optarg);
                break;
            case 'c':
                arg->count_only = true;
                break;
            case 'h':
                print_help();
                return false;
                break;
            default:
                printf("Invalid option selected \n");
                exit(0);
            }
        }
        
        if(arg->index_only){
            arg->option = 1;
        } else if (arg->compress_only){
            arg->option = 2;
        } else {
            if (arg->pattern_file == nullptr)
            {
                arg->patterns.push_back(argv[optind]);
            }
            else
            {
                std::ifstream f(arg->pattern_file);
                std::string str;
                while (getline(f, str))
                {
                    arg->patterns.push_back(str);
                    if(str.size() > arg->max_pattern)
                        arg->max_pattern = str.size();
                }
            }
            arg->option = 3;
        }

        if(arg->option < 3){
            arg->txt_files.push_back(argv[argc-1]);
        }else {
            arg->txt_files.push_back(argv[optind + (arg->pattern_file == nullptr)]);     
        }
    

#if DEBUG_UTILS
        printf("Pattern File: %s\n", arg->pattern_file);
        printf("Patterns: ");
        for (auto a : arg->patterns)
        {
            printf("%s, ", a.c_str());
        }
        printf("\nFiles: ");
        for (auto a : arg->txt_files)
        {
            printf("%s, ", a.c_str());
        }
        printf("\n");
        printf("Count: %d\n", arg->count_only);
#endif
        return true;
    }



    char* readFile(const char* f){
        FILE *file = fopen(f, "rb");
        if (file == NULL) {
            printf("Couldn't read file: %s.", f);
            exit(0);
        }

        fseek(file, 0, SEEK_END);
        int tam = (int)ftell(file);
        fseek(file, 0, SEEK_SET);

        char *data = new char[tam + 1];
        data[tam] = '\0';
        size_t fread_result = fread(data, 1, tam, file);
        if (fread_result != (size_t) tam) {
                printf("Couldn't read file");
                exit(0);
        }
        fclose(file);
        return data;
    }

    void encode(std::string &dest, std::vector<long long int> &src) {
        long long int n = (long long int)src.size();
        for (long long int i = 0; i < n; ++i) {
            dest += std::to_string(src[i]);
            dest += "$";
        }
        dest += "#";
        
    }

    void decode(std::string &src, std::vector<long long int> &dest) {
        long long int n = (long long int)src.size();
        std::string temp;
        for (long long int i = 0; i < n; ++i) {
            if(src[i] == '$'){
                dest.push_back(stoll(temp));
                temp.clear();
            } else if (src[i] == '#'){
                src = src.substr(i+1);
                return;
            }
            else
                temp += src[i];           
        }
    }
}   

