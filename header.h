//library
#include <stdio.h>
#include <malloc.h>
#include <string.h>

//deklarasi tree beserta pointer
typedef struct smp *alamatsimpul;
typedef struct smp{
    char kontainer[100]; //kontainer nama daerah
    int korban; //jumlah korban dalam bil.bulat
    char korbanstr[100]; //jumlah korban dalam string
    alamatsimpul sibling; //saudara
    alamatsimpul child; //anak
}simpul;
typedef struct{
    simpul *root;
}tree;
//prosedur fungsi olah tree
void makeTree(char c[], int x, char k[], tree *T); //membuat tree
void addchild(char c[], int x, char k[], simpul *root); //menambahkan anak
void delAll(simpul *root); //menghapus root pada tree
void delChild(char c[], int x, char k[], simpul *root); //menghapus child
simpul* findsimpul(char c[], int x, char k[], simpul *root); //mencari simpul
void findDepth(int x, simpul *root); //cari level tree
void printTreePreOrderP(int x, simpul *root); //print secara pre order untuk pohon utama
int depth[100]; //variabel penampung kedalaman
//prosedur lainnya
int chartoint(char kata[]); //mengubah string ke integer
int isikorban(simpul *root); //mengisi korban dan akumulasi
//array terstruktur sementara
typedef struct{
    char tparent[100]; //penampung parent
    char tchild[100]; //penampung child
    int tkorban; //penampug jumlah korban int
    char tkorbanstr[100]; //jumalh korban string
}temp;
