#ifndef expandFileName_h
#define expandFileName_h
#include "TString.h"

namespace expandFileName {
    int expandFileName(TString &fileName) {
        char tmp_buff[400];
        FILE *tmp_f = popen(Form("echo %s", fileName.Data()), "r");
        if (tmp_f == NULL)
        {
            printf("ERROR not able to expand the input file name\n");
            return -1;
        }
        if (fgets(tmp_buff, 400, tmp_f) == NULL)
        {
            printf("ERROR not able to get the input file name\n");
            return -1;
        };
        fclose(tmp_f);
        tmp_buff[strlen(tmp_buff) - 1] = '\0';
        printf("expandend input file name: %s\n", tmp_buff);
        fileName = tmp_buff;
        return 1;
    };

};

#endif