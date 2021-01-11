#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#define BLOCK_SIZE 512


int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 2)
    {
        printf("Rembember you have to execute the program with one command-line argument, examp: ./recover image.raw ");
        return 1;
    }

//  Forensic image cannot be opened for reading,return 1.

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Error while opening de memory card please check it");
        return 1;
    }

    typedef uint8_t BYTE;

    BYTE buffer[BLOCK_SIZE];

    int bytes_read = 0;

    bool first_time_jpeg_found = false;

    char file_name[8];

    int jpg_counter = 0;

    FILE *current_file = NULL;

    bool jpg_already_found = false;


    while (true)
    {
        bytes_read = fread(buffer, sizeof(BYTE), BLOCK_SIZE, file);

        if (bytes_read == 0)
        {
            break;
        }

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0Xf0) == 0xe0)
        {
            jpg_already_found = true;

            if (first_time_jpeg_found == false)
            {
                first_time_jpeg_found =  true;
            }
            else
            {
                fclose(current_file);
            }

            sprintf(file_name, "%03i.jpg", jpg_counter);
            current_file = fopen(file_name, "w");
            fwrite(buffer, sizeof(BYTE), bytes_read, current_file);
            jpg_counter += 1;
        }

        else
        {
            if (jpg_already_found == true)
            {
                fwrite(buffer, sizeof(BYTE), bytes_read, current_file);
            }

        }
    }

    fclose(file);
    fclose(current_file);

    return 0;

}


