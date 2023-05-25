//library
#include "header.h"

int main (){

    //deklarasi banyak inputan
    int banyakS;
    //deklarasi tree
    tree T;

    //iterator lokal
    int i, j, k;
    //string penampung input dan jumlah korban
    char tempinput[100];
    char tempkorban[100];

    //meminta masukkan user untuk banyak inputan
    scanf("%d", &banyakS);
    temp data[100]; //array struktur sementara
    //melakukan perulangan sebnayak inputan
    for(i=0; i<banyakS; i++){
        //korban int sementara inisalisasi 0
        data[i].tkorban=0;
        //meminta masukan user untuk input
        scanf("%s", &tempinput);
        int checkpoint=0; //set checkpoint 0 untuk mengecek pagar
        k=0;
        //lakukan perulangan sebanyak panjang string inputan
        for(j=0; j<strlen(tempinput); j++){
            //selama bukan pagar tampung inputan ke variabel sementara untuk parent, child, dan jumlah korban string
            if((tempinput[j]!='#')&&(checkpoint==0)){
                data[i].tparent[k]=tempinput[j];
                k++;
            }else if((tempinput[j]!='#')&&(checkpoint==1)){
                data[i].tchild[k]=tempinput[j];
                k++;
            }else if((j<(strlen(tempinput)-1))&&(checkpoint==2)){
                tempkorban[k]=tempinput[j];
                k++;
            }else{
                //apabila bertemu pagar
                if(checkpoint==0){
                    data[i].tparent[k]='\0'; //jadikan string parent
                }else if(checkpoint==1){
                    data[i].tchild[k]='\0'; //jadikan string child
                }else if(checkpoint==2){
                    tempkorban[k]=tempinput[j];
                    tempkorban[k+1]='\0'; //jadikan string korban
                    if(strcmp(tempkorban, "-1")==0){ //apabila string korban -1
                        //berarti 0
                        data[i].tkorban=0;
                        tempkorban[0]='0';
                        tempkorban[1]='\0';
                        strcpy(data[i].tkorbanstr, tempkorban);
                    }else{
                        //selain itu, konversi string ke integer
                        data[i].tkorban=chartoint(tempkorban);
                        strcpy(data[i].tkorbanstr, tempkorban);
                    }
                }
                k=0; //k set kembali ke 0
                checkpoint++; //checkpoint bertambah
            }
        }
        //abila parent == null
        if(strcmp(data[i].tparent, "null")==0){
            //buat tree
            makeTree(data[i].tchild, data[i].tkorban, tempkorban, &T);
        }else{
            //selain itu cari simpul parent dan lakukan input
            simpul *node = findsimpul(data[i].tparent, data[i].tkorban, tempkorban, T.root);
            if(node!=NULL){
                //node->korban=node->korban+tempkorbanint;
                addchild(data[i].tchild, data[i].tkorban, tempkorban, node);
            }
        }
    }
    //meminta masukkan untuk print pohon lain
    int banyakSpohon;
    scanf("%d", &banyakSpohon);
    char tempsubpohon[100][100];
    for(i=0; i<banyakSpohon; i++){
        scanf("%s", tempsubpohon[i]);
    }

    //mengisi dan akumulasi jumlah korban dari bawah
    simpul *node = T.root;
    //panggil prosedur isi korban
    isikorban(T.root);

    //print tree
    printf("pohon lengkap:\n");
    for(i=0;i<banyakS;i++){
        depth[i] = 0;
    }
    findDepth(0, T.root);
    /*
    for(j=0; j<15; j++){
        printf("%d-", depth[j]);
    }
    */
    printTreePreOrderP(0, T.root);
    printf("\nSub-pohon:\n");
    for(i=0; i<banyakSpohon; i++){
        for(int j=0;j<banyakS;j++){
            depth[j] = 0;
        }
        node=findsimpul(tempsubpohon[i], data[i].tkorban, data[i].tkorbanstr, T.root);
        findDepth(0, node);
        printTreePreOrderP(0, node);
        /*
        for(j=0; j<15; j++){
            printf("%d-", depth[j]);
        }
        printf("\n");
        */
    }
    
    return 0; //selesai
}