#include <stdio.h>
#include "dbExport.h"

void getSeproDataFromKebaOne(int *data4repsys, int faultID)
{
    (void)faultID;
    int row = 0;

    // printf("tab[%d][%d] = %d", 0, 0, tab[0][0]);
    while(row < MAX_ROW)
    {
        int col = 0;
        while(col < MAX_COL)
        {
            if (faultID == tab[row][0])
            {
                // printf("found ! faultID [%d]\n", faultID);
                data4repsys[0] = tab[row][2]; // keba_comp_nr
                data4repsys[1] = tab[row][1]; // keba_msg_nr
                data4repsys[2] = tab[row][3]; // sepro_id_ref
                data4repsys[3] = tab[row][4]; // sepro_id_helper
            }
            col++;
        }
        row++;
    }
}

int main()
{
    // memo : tab[row][col]
    // printf("tab[%d][%d] = %d\n", 1, 0, tab[1][0]); // test ok retourne 4

    int *data4repsys = (int*) malloc( 4 * sizeof(int) );
    
    getSeproDataFromKebaOne(data4repsys, 3);

    int i = 2;
    // printf("data4repsys[%d] = [%d]\n", i, *(data4repsys + i)); // test ok
    
    i = 0;
    while (i < 4)
    {
        switch (i)
        {
            case 0:
                printf("compNr : ");
                break;
            case 1:
                printf("msgNr : ");
                break;
            case 2:
                printf("idRef : ");
                break;
            case 3:
                printf("idHelper : ");
                break;
        }

        printf("%d\n", data4repsys[i]);
        i++;
    }

    return 0;
}