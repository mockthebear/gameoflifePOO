#include "../include/RuleReader.h"
/*!
 Estrutura:
 [8;0;0;255;8:1,2,3,4,5,6,7,8]
 Celula para reviver
 R
 G
 B
 Quantidade de regras para se manter viva
 [N termos]
*/

RuleReader::RuleReader(){
    fp = fopen("../content/rules.txt","r");
    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    file = (char*)malloc(sizeof(char)*size);
    fseek(fp,0L,SEEK_SET);
    int i;
    for (i=0;i<size;i++)
        file[i] = fgetc(fp);
    //Read done.
}
void RuleReader::parseRules(struct rule *r){
    int i;
    struct rule *aux = r;
    while (aux->next != NULL){
        aux = aux->next;
    }
    for (i=0;i<size;i++){
        //[8;0;0;255;8:1,2,3,4,5,6,7,8]
        if (file[i] == '['){
            int toBorn = -1,R=0,G=0,B=0,AMNT=0;
            if (file[i+1] >= '0' and file[i+1] <= '9' and file[i+2] == ';'){
                toBorn = file[i+1]-'0';
            }else{
                exit(10);
            }
            i = i+3;
            int F,d=0;
            for (F=0;F<3;F++){

                if (file[i+F] >= '0' and file[i+F] <= '9'){
                    d++;

                }
                if (file[i+F] == ';'){
                    break;
                }
            }
            for (F=0;F<d;F++){
                R = R + ( ((int)pow(10,d-F-1))*(file[i+F]-'0') );
            }
            i = i+F+1;
            d = 0;
            for (F=0;F<3;F++){

                if (file[i+F] >= '0' and file[i+F] <= '9'){
                    d++;

                }
                if (file[i+F] == ';'){
                    break;
                }
            }
            for (F=0;F<d;F++){
                G = G + ( ((int)pow(10,d-F-1))*(file[i+F]-'0') );
            }
            i = i+F+1;
            d = 0;
            for (F=0;F<3;F++){
                printf("%c",file[i+F]);
                if (file[i+F] >= '0' and file[i+F] <= '9'){

                    d++;

                }
                if (file[i+F] == ';'){
                    break;
                }
            }
            for (F=0;F<d;F++){
                B = B + ( (pow(10.0,d-F-1))*(file[i+F]-'0') );
            }
            i = i+d+1;
            AMNT = file[i]-'0';
            aux->next = (struct rule*)malloc(sizeof(struct rule));
            aux = aux->next;
            aux->next = NULL;
            aux->id = rand()%500;
            aux->cellToLive = toBorn;
            aux->amnt = AMNT;
            aux->cellToDie = (int*)malloc(sizeof(int)*AMNT);
            //for (tmp=1;tmp<=8;tmp++){
              //  aux->cellToDie[tmp-1] = tmp;
              //}
              aux->color[0] = R;
              aux->color[1] = G;
              aux->color[2] = B;
            //printf(" -- %d %d %d %d %d     i: %d = %c ->",toBorn,R,G,B,AMNT,i,file[i]);
            int k;
            i++;
            i++;
            for (k=0;k<AMNT;k++){
                //
                printf("%d - ",file[i+k]-'0');
                aux->cellToDie[k] = file[i+k]-'0';
                i++;
            }

        }
    }
}
