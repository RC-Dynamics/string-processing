
#include <string>

class FileParser {
    public:
      FileParser(const std::string &filename);
      char* readLine();
      unsigned long int filesize();
      void close();
    private:
      unsigned int buf_size = 30000;
      char *txt_piece = NULL;
      char *ptr = NULL;
      char *ptr_r = NULL;
      int txt_piece_len;
      FILE *txt = NULL;
      bool ended;
};