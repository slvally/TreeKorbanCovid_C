//library
#include "header.h"

//membuat tree
void makeTree(char c[], int x, char k[], tree *T){
    simpul *node;
    node  = (simpul *) malloc (sizeof(simpul));

    strcpy(node->kontainer, c);
    node->korban = x;
    strcpy(node->korbanstr, k);

    node->sibling = NULL;
    node->child = NULL;
    (*T).root = node;
}
//menambahkan anak
void addchild(char c[], int x, char k[], simpul *root){
    //jika simpul kosong maka lakukan proses penambahan
    if(root != NULL){
        //alokasi memori untuk elemen baru
        simpul *baru;
        baru = (simpul *) malloc (sizeof(simpul));
        strcpy(baru->kontainer, c);
        strcpy(baru->korbanstr, k);
        baru->korban = x;
        baru->child = NULL;

        simpul *bantu;
        //apabila child kosong maka baru langsung ditambahkan
        if(root->child == NULL){
            baru->sibling = NULL; //sibling kosong
            root->child = baru;
        }else{ //apabila root memiliki satu child/lebih
            if(root->child->sibling == NULL){ //untuk satu child
                //apabila jumlah korban sama dengan 0
                if(baru->korban == 0){
                    //baru langsung menjadi sibling dari child
                    baru->sibling = root->child;
                    root->child->sibling = baru;
                }else{
                    //mencari tempat dimana jumlah korban baru lebih kecil dari root
                    bantu = root->child;
                    bantu->sibling = baru;
                    if(baru->korban >= root->child->korban){
                        baru->sibling = bantu;
                        root->child = baru;
                    }else{
                        baru->sibling = root->child;
                        root->child->sibling = baru;
                    }
                }
            }else{ //lebih dari satu child
                if(baru->korban == 0){ //untuk jumlah korban == 0 tidak perlu disort
                    simpul *bantu2 = root->child;
                    while(bantu2->sibling != root->child){
                        //cari sibling terakhir
                        bantu2 = bantu2->sibling;
                    }
                    //elemen baru menjadi sibling bantu2
                    baru->sibling = root->child;
                    bantu2->sibling = baru;
                }else{  //untuk jumlah korban > 0 tidak 
                    bantu = root->child;
                    simpul *prev = NULL;
                    int found = 0;
                    //mencari posisi simpul dimana jumlah korban akan lebih besar
                    while(bantu->sibling != root->child && found == 0){
                        if(baru->korban > bantu->korban){ 
                            //apabila ditemukan sesuai posisi
                            found++;
                            if(bantu != root->child){
                                prev->sibling = baru;
                                baru->sibling = bantu;
                            }else{
                                simpul *bantu2 = root->child;
                                while(bantu2->sibling != root->child){
                                    bantu2 = bantu2->sibling;
                                }
                            root->child = baru;
                            baru->sibling =bantu;
                            bantu2->sibling = root->child;
                            }
                        }else{
                            prev = bantu;
                            bantu = bantu->sibling;
                        }
                    }
                    if(found == 0){ //apabila tidak ditemukan
                        if(baru->korban > bantu->korban){
                            prev->sibling = baru;
                            baru->sibling = bantu;
                            bantu->sibling = root->child;
                        }else{
                            baru->sibling = root->child;
                            bantu->sibling = baru;
                        }
                    }
                }
            }
        }
    }
}
//menghapus root pada tree
void delAll(simpul *root){
    if(root != NULL){
        if(root->child != NULL){
            
            if(root->child->sibling = NULL){
                delAll(root->child);
                free(root);
            }else{
                simpul *bantu, *proses;
                bantu = root->child;
                while(bantu->sibling != root->child){
                    proses = bantu;
                    bantu = bantu->sibling;
                    delAll(proses);
                }
                delAll(bantu);
            }
            free(root);
        }else{
            free(root);
        }
    }
}
//menghapus child
void delChild(char c[], int x, char k[], simpul *root){
    if(root != NULL){
        simpul *hapus = root->child;
        if(hapus != NULL){
            if(hapus->sibling == NULL){
                if(strcmp(root->child->kontainer, c)==0){
                    delAll(root->child);
                    root->child = NULL;
                }else printf("Tidak ada simpul anak dengan data masukan\n");
            }else{
                simpul *prev = NULL;
                int found = 0;
                while(hapus->sibling != root->child && found == 0){
                    if(strcmp(hapus->kontainer, c)==0){
                        found = 1;
                    }else{
                        prev = hapus;
                        hapus = hapus->sibling;
                    }
                }
                if((found == 0) && (strcmp(hapus->kontainer, c)==0)) found = 1;
                if(found == 1){
                    simpul *bantu2 = root->child;
                    while(bantu2->sibling != root->child){
                        bantu2 = bantu2->sibling;
                    }
                    if(prev == NULL){
                        if((hapus->sibling == bantu2) && (bantu2->sibling == root->child)){
                            root->child = bantu2;
                            bantu2->sibling = NULL;
                        }else{
                            root->child = hapus->sibling;
                            bantu2->sibling = root->child;
                        }
                    }else{
                        if((prev == root->child) && (bantu2->sibling == root->child) && (hapus->sibling == root->child)) root->child->sibling = NULL;
                        else{
                            prev->sibling = hapus->sibling;
                            hapus->sibling = NULL;
                        }
                    }
                    delAll(hapus);
                }else printf("tidak ada child dengan kontainer masukan\n");
            }
        }
    }
}
//mencari simpul
simpul* findsimpul(char c[], int x, char k[], simpul *root){
    simpul *result = NULL;
    if (root != NULL){
        if (strcmp(root->kontainer, c) == 0){
            result = root;
        }else{
            simpul *bantu = root->child;
            if (bantu != NULL){
                if (bantu->sibling == NULL){
                    if (strcmp(bantu->kontainer, c) == 0){
                        result = bantu;
                    }else{
                        result = findsimpul(c, x, k, bantu);
                    }
                }else{ 
                    int found = 0;
                    while (bantu->sibling != root->child && found == 0){
                        if (strcmp(bantu->kontainer, c) == 0){
                            result = bantu;
                            found = 1;
                        }else{
                            result = findsimpul(c, x, k, bantu);
                            if (result != NULL){
                                found = 1;
                            }
                            bantu = bantu->sibling;
                        }
                    }
                    if (found == 0){
                        if (strcmp(bantu->kontainer, c) == 0){
                            result = bantu;
                        }else{
                            result = findsimpul(c, x, k, bantu);
                        }
                    }
                }
            }
        }
    }
    return result;
}
//print secara pre order untuk pohon lengkap
void findDepth(int x, simpul *root){
    int space;
    if(root != NULL){
        if(x==0){
            space=strlen(root->kontainer)+strlen(root->korbanstr)+4;
            depth[x]=space;
        }else{
            space=strlen(root->kontainer)+strlen(root->korbanstr)+4;
            if(space>depth[x]){
                depth[x]=space;
            }
            
        }
        simpul *bantu = root->child;
        x++;
        if(bantu != NULL){
            if(bantu->sibling == NULL) findDepth(x, bantu);
            else{
                while(bantu->sibling != root->child){
                    findDepth(x, bantu);
                    bantu = bantu->sibling;
                }
                findDepth(x, bantu);
            }
        }
    }
}
void printTreePreOrderP(int x, simpul *root){
    int i, j, space;
    int panjang=0;
    if(root != NULL){
        printf("\n");
        if(x==0){
            printf("|%s - %d\n", root->kontainer, root->korban);
        }else{
            for(i=0; i<x; i++){
                panjang=panjang+depth[i];
            }
            for(i=0; i<panjang; i++){
                printf(" ");
            }
            printf("|%s - %d\n", root->kontainer, root->korban);
        }
        simpul *bantu = root->child;
        x++;
        if(bantu != NULL){
            if(bantu->sibling == NULL) printTreePreOrderP(x, bantu);
            else{
                while(bantu->sibling != root->child){
                    printTreePreOrderP(x, bantu);
                    bantu = bantu->sibling;
                }
                printTreePreOrderP(x, bantu);
            }
        }
    }
}
//mengubah string ke integer
int chartoint(char kata[]){
    int i;
    int res = 0;
    for (i=0; i<strlen(kata); i++){
        res = res * 10;
        res = res + kata[i]-'0';
    }
    return res;
}

//mengisi korban dan akumulasi
int isikorban(simpul *root){
    int total;
    if(root != NULL){
        //variabel lokal
        int tkorb; //total korban int
        char tkorbstr[100]; //total korban str
        char tempstr[100]; //str korban sementara
        total = root->korban;
        if(root->child != NULL){
            //apabila punya 1 child
            if(root->child->sibling == NULL) {
                simpul *bantu = root->child;
                int temp = isikorban(bantu);
                total = total + temp;
                sprintf(tempstr, "%d", total);
                strcpy(root->korbanstr, tempstr);
                //sprintf(root->korbanstr, "%d", temp);
            }else{
                simpul *bantu = root->child;
                //strcpy(tkorbstr, root->child->korbanstr);
                while(bantu->sibling != root->child){ //untuk semua anak, jumlahkan
                    int temp = isikorban(bantu);
                    total += temp;
                    sprintf(tempstr, "%d", total); //mengubah integer menjadi string
                    strcpy(root->korbanstr, tempstr); //update
                    bantu = bantu->sibling;
                }
                int temp = isikorban(bantu);
                total += temp;
                root->korban=temp;
                sprintf(tempstr,"%d",total);
                strcpy(root->korbanstr, tempstr); //update
                //strcpy(root->korbanstr, tkorbstr);
            }
        }
        sprintf(tempstr,"%d",total);
        strcpy(tkorbstr, tempstr);
        root->korban = total;
    }
    return total;
}