/*
 * @author  duruyao
 * @date    2023-03-14
 * @desc    save files to and load files from protobuf messages
 * @usage   EXECUTABLE <SRC_FILENAME> <DST_FILENAME>
 */

#include <cstdio>
#include <string>

#include "protobuf_rw_file.pb.h"

const int BUFF_SIZE = (UINT16_MAX << 8) + 2; // 16 M + 1

int main(int argc, char **argv) {
    // handle arguments
    if (3 != argc || 0 == strcmp(argv[1], argv[2])) {
        fprintf(stdout,
                "Usage:\n"
                "    %s <SRC_FILENAME> <DST_FILENAME>\n"
                "Description:\n"
                "    Read a file into protobuf messages and write protobuf messages to another file.\n", argv[0]);
        return 0;
    }

    // read data from a binary file to a buffer
    FILE *fp;
    if (nullptr == (fp = fopen(argv[1], "rb"))) {
        fprintf(stderr, "Error: cannot open file: '%s'\n", argv[1]);
        return 1;
    }
    char *dataBuff1 = new char[BUFF_SIZE];
    auto dataSize1 = fread(dataBuff1, sizeof(char), BUFF_SIZE, fp);
    fclose(fp);
    if (dataSize1 >= BUFF_SIZE) {
        fprintf(stderr, "Error: file size greater than 16 MB: '%s'\n", argv[1]);
        return 1;
    }

    // assign values to the object pbFile1
    PBFile pbFile1;
    pbFile1.set_data_size(dataSize1);
    pbFile1.set_data_buff(dataBuff1, dataSize1);

    // serialize the object pbFile1 to a string
    auto serializedStr = pbFile1.SerializeAsString();

    // deserialize a string to the object pbFile2
    PBFile pbFile2;
    pbFile2.ParseFromString(serializedStr);

    // read data from pbFile2 to a buffer
    char *dataBuff2 = new char[BUFF_SIZE];
    auto dataSize2 = pbFile2.data_size();
    memcpy(dataBuff2, pbFile2.data_buff().c_str(), pbFile2.data_size());

    // compare dataBuff1 with dataBuff2
    if (0 != memcmp(dataBuff1, dataBuff2, dataSize2)) {
        fprintf(stderr, "Error: dataBuff1 != dataBuff2\n");
        return 1;
    }

    // write data from a buffer to a binary file
    if (nullptr == (fp = fopen(argv[2], "wb"))) {
        fprintf(stderr, "Error: cannot open file: '%s'\n", argv[2]);
        return 1;
    }
    fwrite(dataBuff2, sizeof(char), dataSize2, fp);
    fclose(fp);

    return 0;
}
