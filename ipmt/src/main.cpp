#include <iostream>
#include <string>

#include "utils.h"

#define LS 4096
#define LL 256

int main (int argc, char* argv[]) {
   utils::argmnts arg;
    if(argc == 1){
        printf("No option selected.\n");
        utils::print_help();
        return 0;
    }
    if (!utils::getArguments(&arg, argc, argv))
        return 0;
    
    FILE *index_file;
    std::string compressed;
    int size;
    std::string code;
    char* txt;
    std::string index_fname;
    LZ77 lz(LS, LL);
    SArray SA;
    size_t fread_result;

    // FILE* lala;
    // std::string teste_comp;

    switch(arg.option){
        default:
            printf("Invalid option selected \n");
            utils::print_help();
            break;
        case 1: // Index - Compress
            txt = utils::readFile((arg.txt_files)[0].c_str());
            SA.init(txt);

            index_fname = ((arg.txt_files)[0]).substr(0, (arg.txt_files[0]).size()-4) + ".idx";
            index_file = fopen(index_fname.c_str(), "wb");
            if (index_file == NULL) {
                printf("Couldn't create Index file\n");
                exit(0);
            }
            
            fwrite(&(SA.n), sizeof(long long int), 1, index_file);
            fwrite(&(lz.search_buffer), sizeof(long long int), 1, index_file);
            fwrite(&(lz.lookahead_buffer), sizeof(long long int), 1, index_file);

            // for (auto a : SA.SArr)
            // {
            //     printf("%d ", a);
            // }
            // printf("\n");
            // for (auto a : SA.Llcp)
            // {
            //     printf("%d ", a);
            // }
            // printf("\n");
            // for (auto a : SA.Rlcp)
            // {
            //     printf("%d ", a);
            // }
            // printf("\n");
            // std::cout << strlen(SA.txt) << std::endl;

            utils::encode(code, SA.SArr);
            utils::encode(code, SA.Llcp);
            utils::encode(code, SA.Rlcp);

            code += txt;
            // std::cout << code << std::endl;
            compressed = lz.encode(code);
            // compressed += '\0';

            // teste_comp = lz.decode(compressed);
            // std::cout << teste_comp;

            // index_fname = ((arg.txt_files)[0]).substr(0, (arg.txt_files[0]).size() - 4) + "--.txt";
            // lala = fopen(index_fname.c_str(), "w");
            // fwrite(teste_comp.c_str(), sizeof(char), teste_comp.size(), lala);
            // fclose(lala);
            // std::cout << compressed.size() << std::endl;

            fwrite(compressed.c_str(), sizeof(char), compressed.size(), index_file);
            fclose(index_file);
            break;

        case 2: // Compress
            
            txt = utils::readFile((arg.txt_files)[0].c_str());

            index_fname = ((arg.txt_files)[0]).substr(0, (arg.txt_files[0]).size()-4) + ".idx";
            index_file = fopen(index_fname.c_str(), "wb");
            if (index_file == NULL) {
                printf("Couldn't create Index file\n");
                exit(0);
            }
            
            code += txt;

            // code = "This is the 100th Etext file presented by Project Gutenberg, and is presented in cooperation with World Library, Inc., from their Library of the Future and Shakespeare CDROMS.  Project Gutenberg often releases Etexts that are NOT placed in the Public Domain!!";

            // code = "cbacbacbcacbacbcaac";
            // std::cout << code << std::endl;
            compressed = lz.encode(code);
            // std::cout << compressed << std::endl;

            // teste_comp = lz.decode(compressed);
            // std::cout << teste_comp;

            fwrite(compressed.c_str(), sizeof(char), compressed.size(), index_file);
            fclose(index_file);
            break;

        case 3: // Search
            index_fname = ((arg.txt_files)[0]);
            
            index_file = fopen(index_fname.c_str(), "rb");
            if (index_file == NULL) {
                printf("Couldn't open Index file\n");
                exit(0);
            }

            fread_result = fread(&(SA.n), sizeof(long long int), 1, index_file);
            if (fread_result != 1) {
                printf("Couldn't open Index file\n");
                exit(0);
            }
            fread_result = fread(&(lz.search_buffer), sizeof(long long int), 1, index_file);
            if (fread_result != 1) {
                printf("Couldn't open Index file\n");
                exit(0);
            }
            fread_result = fread(&(lz.lookahead_buffer), sizeof(long long int), 1, index_file);
            if (fread_result != 1) {
                printf("Couldn't open Index file\n");
                exit(0);
            }

            int where = ftell(index_file);
            fseek(index_file, 0, SEEK_END);
            size = ftell(index_file) - where;
            fseek(index_file, where, SEEK_SET);

            char *compressed_ = new char[size+1];
            
            fread_result = fread(compressed_, sizeof(char), size, index_file);
            if (fread_result != (size_t) size) {
                printf("Couldn't open Index file\n");
                exit(0);
            }
            compressed_[size] = '\0';
            std::string sstr(compressed_, size);

            // std::cout << sstr.size() << std::endl;

            code = lz.decode(sstr);
        
            utils::decode(code, SA.SArr);
            utils::decode(code, SA.Llcp);
            utils::decode(code, SA.Rlcp);

            // for(auto a : SA.SArr){
            //     printf("%d ", a);
            // }
            // printf("\n");
            // for (auto a : SA.Llcp)
            // {
            //     printf("%d ", a);
            // }
            // printf("\n");
            // for (auto a : SA.Rlcp)
            // {
            //     printf("%d ", a);
            // }
            // printf("\n");

            SA.txt = new char[code.size()+1];
            strcpy(SA.txt, code.c_str());
            SA.txt[code.size()] = '\0';
            
            // std::cout << strlen(SA.txt) << std::endl;

            for (std::string pat : arg.patterns) {
                char *p = new char[pat.size() + 1];
                strcpy(p, pat.c_str());
                p[pat.size()] = '\0';
                if(arg.count_only){
                    printf("%s occurs: %lld times\n", p, SA.search(p));    
                } else {
                    SA.search(p, true);
                }
            }
            fclose(index_file);
            break;
    }


    return 0;
}
