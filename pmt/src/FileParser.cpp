#include "FileParser.h"

FileParser::FileParser(const std::string &filename)
{
    txt = fopen(filename.c_str(), "rb");
    if (txt == NULL)
    {
        printf("Error openning file.\n");
        exit(0);
    }

    txt_piece = new char[2 * buf_size + 1];
    txt_piece[0] = '\0';
    txt_piece_len = 0;
    ptr_r = txt_piece - 1;
    ended = false;
}

char* FileParser::readLine(){
    if (ended) {
        return NULL;
    }

    ptr = ptr_r + 1;
    ptr_r = NULL;
    int size = (int)(txt_piece + txt_piece_len - ptr);

    if (size > 0)
        ptr_r = (char *)memchr(ptr, '\n', size);
    if (ptr_r == NULL)
    {
        if (feof(txt)) { // last line
            ended = true;
            return ptr;
        }
        else if (ptr == txt_piece && txt_piece[0] != '\0') { // not enoght for a line
            buf_size *= 2;
            char *new_str = new char[buf_size + 1];
            free(txt_piece);
            txt_piece = new_str;
        }
        int cpy_size = std::max(0, size);
        fseek(txt, -cpy_size, SEEK_CUR);
        txt_piece_len = (int)fread(txt_piece, 1, buf_size, txt);
        txt_piece[txt_piece_len] = '\0';
        ptr_r = txt_piece - 1;

        return readLine();
    }
    else
    {
        *ptr_r = '\0';
        return ptr;
    }
}
unsigned long int  FileParser::filesize(){
    fseek(txt, 0, SEEK_END); // seek to end of file
    unsigned long int size = ftell(txt); // get current file pointer
    fseek(txt, 0, SEEK_SET); // seek back to beginning of file
    return size;
}
void FileParser::close(){
    free(txt_piece);
    fclose(txt);
    txt_piece = nullptr;
    txt = nullptr;
}