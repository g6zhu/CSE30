/*
 * CSE30 WI22 HW3
 * Username: cse30wi22xx (Fill in your username)
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    /* Local Variables */
    int c_flag = 0;
    int num_cols = 0;
    int n_sel = 0;
    int *sel_arry = NULL;
    int longest = 0;
    int line_cnt = 0;


    /* save the other cli args */
    if (argc > 1 && strcmp(argv[1], "-c") == 0) {
        c_flag = 1;
//        printf("c_flag:%d\n", c_flag);
    }

    if (argc > 1 + c_flag) {
        num_cols = atoi(argv[1 + c_flag]);
//        printf("num_cols:%d\n", num_cols);
    }

    n_sel = argc - 2 - c_flag;
//    printf("n_sel:%d\n", argc, n_sel);
    if (n_sel > 0) {
        sel_arry = malloc(sizeof(int) * n_sel);
        for (int i = 2 + c_flag; i < argc; i++) {
            sel_arry[i - 2 + c_flag] = atoi(argv[i]);
//            printf("%d\n", sel_arry[i - 2 + c_flag]);
        }
    }

    /* process the input as described in the writeup */
    for (int i = 0; i < num_cols; i++) {
        char *pline = NULL;
        size_t len = 0;
        int read_len = getline(&pline, &len, stdin);
        if (read_len >= 0) {
            char *delim = " \t\n";
            int status = 0;
            char **ppstr = NULL;
            int str_cnt = 0;

            line_cnt++;
            for (int i = 0; i < read_len; i++) {
                int delim_flag = 0;
                for (int j = 0; j < strlen(delim); j++) {
                    if (delim[j] == pline[i]) {
                        delim_flag = 1;
                    }
                }
                if (status == 0 && delim_flag == 0) {
                    status = 1;
                    char **ptemp = malloc(sizeof(char *) * (str_cnt + 1));
                    memcpy(ptemp, ppstr, sizeof(char *) * str_cnt);
                    ptemp[str_cnt++] = &pline[i];
                    if (ppstr)
                        free(ppstr);
                    ppstr = ptemp;
                } else if (status == 1 && delim_flag == 1) {
                    pline[i] = 0;
                    status = 0;
                }

            }
//            for(int i=0; i<str_cnt; i++){
//                printf("\"%s\"\n", ppstr[i]);
//            }
//            printf("-----------------------\n");

            for (int i = 0; i < str_cnt; ++i) {
                if (strlen(ppstr[i]) > longest)
                    longest = strlen(ppstr[i]);
            }

            for (int i = 0; i < n_sel; i++) {
                char *sel_str = NULL;
                if (sel_arry[i] >= 0 && sel_arry[i] < str_cnt) {
                    sel_str = ppstr[sel_arry[i]];
                } else if (sel_arry[i] < 0 && str_cnt + sel_arry[i] >= 0) {
                    sel_str = ppstr[str_cnt + sel_arry[i]];
                }
                if (sel_str != NULL)
                    if (i < n_sel - 1)
                        printf("%s ", sel_str);
                    else
                        printf("%s\n", sel_str);
            }

            free(ppstr);
            free(pline);
        } else {
            break;
        }
    }
	free(sel_arry);




//     Format string for output to be printed when -c option is given

    printf("Number of lines: %d\n"
           "Longest field: %d characters\n",
           line_cnt, longest);
}
