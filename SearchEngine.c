#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "SearchEngine.h"
int total_doc=0;
int indexing_comparison; // indexingΩ√ ∫Ò±≥ø¨ªÍ »Ωºˆ
int searching_comparison; // searchingΩ√ ∫Ò±≥ø¨ªÍ »Ωºˆ
int total_words; // ¿¸√º ¥‹æÓ ºˆ

int main()
{
    char* search = malloc(sizeof(char) * WORD_SIZE); // ∞Àªˆ«“ ¥‹æÓ
    char c;
    //getFile ø√¿⁄∏Æ
    //0~9«ÿΩ√Ω√≈∞¥¬∞≈
    printf("ªˆ¿Œ ¿€æ˜ Ω««‡...\n\n");
    getFilelist();
    chaining_insert();


    printf("Total number of doucuments : %d\n",total_doc);
    printf("Total number of indexed words : %d\n", total_words);
    printf("Total number of comparison : %d\n\n", indexing_comparison);

    printf("\n*********** Command ***********\n");
    printf("S: SEARCH, Q; Quit\n");
    printf("*******************************\n\n");

    while (1) {

        printf("\nCommand> ");
        c = _getch();
        _putch(c);
        c = toupper(c);

        switch (c) {

        case 'S':
            searching_comparison = 0;
            printf("\n\nSearching for : ");
            scanf("%s", search);
            search = strlwr(search); // ¥ÎπÆ¿⁄∑Œ ¿‘∑¬«ÿµµ ∞Àªˆ«“ ºˆ ¿÷∞‘ º≥¡§
            printf("\n");

            infor_pointer a = chaining_search(search); // «ÿΩ√ ≈◊¿Ã∫Ìø°º≠ ∞Àªˆ«— ¥‹æÓ∏¶ √£∞Ì, ±◊ ¡÷º“∞™¿ª π›»Ø
            if (a == NULL) { continue; } // ∞Àªˆ∞·∞˙∞° æ¯¿ªΩ√ aø°¥¬ NULL¿Ã ¥Î¿‘µ«π«∑Œ ¿ß∑Œ ø√∂Û∞°º≠ while(1)πÆ Ω««‡

            sort(a->e, 10); // count º¯¿∏∑Œ ¡§∑ƒ (ø¿∏ß¬˜º¯)

            for (int i = 9; i >= 0; i--) // ø¿∏ß¬˜º¯¿Ãπ«∑Œ ∏« µ⁄ø°∞‘ ∞°¿Â ∏π¿∫ count
            {
                if (a->e[i].count != 0)
                {
                    int index = 0;
                    int front; // √‚∑¬«œ∞Ì¿⁄ «œ¥¬ ∞°¿Â æ’∫Œ∫–
                    int rear; // √‚∑¬«œ∞Ì¿⁄ «œ¥¬ ∞°¿Â µﬁ∫Œ∫–
                    int flag; // ¿¸»ƒ "3" π¯¬∞∏¶ ≥—æ˘¥Ÿ∏È forπÆ ≥°≥ª∞Ì √‚∑¬¿∏∑Œ ≥—æÓ∞°±‚¿ß«— ∫Øºˆ

                    printf("< doc%.2d.txt > %s : %d\n\n", a->e[i].txt, search, a->e[i].count);

                    while (a->e[i].position[index] >= 0) // ¿˙¿Âµ» ¿ßƒ°¡§∫∏∞° æ¯¿ª ∂ß ±Ó¡ˆ
                    {
                        flag = 0;
                        for (front = a->e[i].position[index]; file[(a->e[i].txt) - 1][front] != NULL && (flag < 3); front--, flag++) {} // ∞Àªˆ«œ∞Ì¿⁄ «œ¥¬ ¥‹æÓ¿« fileªÛø°º≠ ¿ßƒ° - 3¿Œ front∏¶ √£±‚ ¿ß«ÿº≠ 
                        if (front < 0) front = 0; // ∞Àªˆ«œ∞Ì¿⁄ «œ¥¬ ¥‹æÓ∞° æ’¬ ø° ¿÷æÓº≠ πŸ∑Œ ¿ß¿« forπÆ¿ª µπ∏Æ¥Ÿ∞° front∞° ¿Ωºˆ∞° µ«¥¬ «ˆªÛ¿Ã πﬂª˝Ω√ ¥‹æÓ √‚∑¬¿ª ¿ß«ÿ 0¿∏∑Œ ¡∂¡§

                        flag = 0;
                        for (rear = a->e[i].position[index]; file[(a->e[i].txt) - 1][rear] != NULL && (flag < 3); rear++, flag++) {} // ∞Àªˆ«œ∞Ì¿⁄ «œ¥¬ ¥‹æÓ¿« fileªÛø°º≠ ¿ßƒ° + 3¿Œ rear¿ª √£±‚ ¿ß«ÿº≠ 

                        if (front >= 1) // front∞° 0¿œ ∂ß¥¬ ... √‚∑¬ æ»«‘
                        {
                            printf("...");
                        }

                        for (; front != rear + 1; front++) // front∫Œ≈Õ rear±Ó¡ˆ¿« ¥‹æÓ∏¶ √‚∑¬
                        {
                            if (file[a->e[i].txt - 1][front]) // «ˆ¿Á √‚∑¬«œ∞Ì ¿÷¥¬ file_πËø≠ø° ¥‹æÓ∞° ¡∏¿Á«—¥Ÿ∏È
                            {
                                printf(" %s", file_[a->e[i].txt - 1][front]);
                            }

                            else
                            {
                                break;
                            }
                        }

                        if (file[a->e[i].txt - 1][rear + 1] != NULL) // ∞Àªˆ«œ∞Ì¿⁄ «œ¥¬ ¥‹æÓ∞° µ⁄¬ ø° ¿÷æÓº≠ «ˆ¿Á±Ó¡ˆ √‚∑¬«— ¥‹æÓ∞° ±◊ ≈ÿΩ∫∆Æ ∆ƒ¿œ¿« ∏∂¡ˆ∏∑¿Ã∂Û∏È ... √‚∑¬æ»«‘
                        {
                            printf(" ...");
                        }

                        printf("\n\n");

                        index++; // ±◊ ¥Ÿ¿Ω ≈ÿΩ∫∆Æ ∆ƒ¿œ∑Œ ≥—æÓ∞°±‚
                    }
                }
            }

            printf("∞ÀªˆΩ√ ∫Ò±≥ø¨ªÍ »Ωºˆ : %d\n\n", searching_comparison);

            break;

        case 'Q':
            printf("\n");
            exit(1);

        default:
            printf("\n¿ﬂ∏¯µ» ¿‘∑¬¿‘¥œ¥Ÿ!!!\n\n");
            break;

        }
    }

    return 0;
}
void getFilelist()
{

    char* a = "doc01.txt";
    char* b = "doc02.txt";
    char* c = "doc03.txt";
    char* d = "doc04.txt";
    char* e = "doc05.txt";
    char* f = "doc06.txt";
    char* g = "doc07.txt";
    char* h = "doc08.txt";
    char* i = "doc09.txt";
    char* j = "doc10.txt";

    getFile(a);
    total_doc++;
    getFile(b);
    total_doc++;
    getFile(c);
    total_doc++;
    //getFile(d);
    //total_doc++;
    //getFile(e);
    //total_doc++;
    //getFile(f);
    //total_doc++;
    //getFile(g);
    //getFile(h);
    //total_doc++;
    //getFile(i);
    //total_doc++;
    //getFile(j);
    //total_doc++;
}
void getFile(char* file_name)
{
    char* buffer = NULL;
    FILE* fp;
    int size;
    if ((fp = fopen(file_name, "r")) == NULL)
    {
        printf("error:txt01\n");
    }
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    buffer = malloc(size + 1);
    memset(buffer, 0, size + 1);;
    fseek(fp, 0, SEEK_SET);
    fread(buffer, size, 1, fp);
    _strlwr(buffer);
    indexing1(buffer);
	fclose(fp);
    if ((fp = fopen(file_name, "r")) == NULL)
    {
        printf("error:txt01\n");
    }
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    buffer = malloc(size + 1);
    memset(buffer, 0, size + 1);;
    fseek(fp, 0, SEEK_SET);
    fread(buffer, size, 1, fp);
    indexing2(buffer);
	fclose(fp);
}
void indexing1(char* text) // πÆ¿⁄ø≠¿ª ∫–∏Æ«œ±‚ ¿ß«— «‘ºˆ
{
    char* word = NULL;
    int i = 0;
    static int c = 0;
    word = strtok(text, ",.!\"\'[]\t\v1234567890{}|\\@#$%^&*-?()%:>< \n");
    while (word != NULL)
    {
        file[c][i] = word;
        i++;
        word = strtok(NULL, ",.!\"\'[]\t\v1234567890{}|\\@#$%^&*-?()%:>< \n");
    }
    c++;
}

void indexing2(char* text) // πÆ¿⁄ø≠¿ª ∫–∏Æ«œ±‚ ¿ß«— «‘ºˆ
{
    char* word = NULL;
    char* word_ = NULL; // ∞¯πÈ∞˙ ∞≥«‡πÆ¿⁄ ªÁ¿Ãø° ∆ØºˆπÆ¿⁄∞° ¿÷¥¬¡ˆ »Æ¿Œ«œ±‚ ¿ß«— øÎµµ
    int i = 0;
    static int c = 0;
    word = strtok(text, "\v\t \n");
    word_ = word;
    while (word != NULL)
    {
        // ¿⁄∏• πÆ¿⁄ø≠¿ª πÆ¿⁄ ¥‹¿ß∑Œ √º≈©«ÿº≠ ¿¸∫Œ¥Ÿ ∆ØºˆπÆ¿⁄∂Û∏È file_ø° ¿˙¿Â«œ¡ˆ æ ∞Ì, øµæÓ∞° ¿÷¥Ÿ∏È fileø° ¥‹æÓ∑Œ ¿˙¿Âµ«æÓ ¿÷¿ª ∞Õ¿Ãπ«∑Œ file_ø° ¿˙¿Â
        if (!isalpha(*word_)) // ∏∏æ‡ ¿⁄∏• πÆ¿⁄ø≠ø° ∆ØºˆπÆ¿⁄∞° ¿÷¥Ÿ∏È
        {
            for (int m = 0; m < strlen(word_); m++)
            {
                if (isalpha(word_[m])) // πÆ¿⁄ø≠ø° øµæÓ∞° ¿÷¥Ÿ∏È
                {
                    break;
                }

                else if (!isalpha(word_[m]) && m + 1 >= strlen(word_)) // πÆ¿⁄ø≠ ¿¸√º∞° ∆ØºˆπÆ¿⁄∂Û∏È
                {
                    goto a;
                }
            }
        }

        file_[c][i] = word; // file_ø° ¥‹æÓ ¿˙¿Â
        i++;

    a:
        word = strtok(NULL, "\v\t \n");
        word_ = word;
    }
    c++;
}

void chaining_insert() // «ÿΩ√ ≈◊¿Ã∫Ìø° ª¿‘«œ±‚ ¿ß«— «‘ºˆ
{
    for (int i = 0; i < 10; i++) { // i¥¬ ≈ÿΩ∫∆Æ π¯»£ - 1, ex) 1π¯ ≈ÿΩ∫∆Æ¿« πÆ¿⁄µÈ¿ª «ÿΩ√ ≈◊¿Ã∫Ìø° ª¿‘Ω√ i = 0

        for (int j = 0; file[i][j]; j++) { // fileø° ¡∏¿Á«œ¥¬ ¥‹æÓµÈ¿ª ¿–æÓø¬ ¥Ÿ¿Ω, hashing »ƒ hash ≈◊¿Ã∫Ìø° ¿˙¿Â, file πËø≠ø° ¥‹æÓ∞° æ¯¿ª ∂ß ±Ó¡ˆ π›∫π

            int flag = 0; // ¡ﬂ∫πµ» ¥‹æÓ∞° ≥™ø”¥¬¡ˆ∏¶ ∆«¥‹«œ±‚ ¿ß«— ∫Øºˆ

            int w = hash(file[i][j]); // file πËø≠ø°º≠ ¥‹æÓ∏¶ ¿–æÓø¬ ¥Ÿ¿Ω, hashing

            infor_pointer temp = NULL;
            infor_pointer lead = NULL;
            infor_pointer trail = NULL;

            // ≈ÿΩ∫∆Æ ∆ƒ¿œµÈ¿ª ¿–¥Ÿ∞° ∞∞¿∫ hash ∞™¿Ã ≥™ø‘¿ª ∞ÊøÏ, √≥∏Æ«ÿ¡÷±‚ ¿ß«— for πÆ
            for (lead = Table[w]; lead; trail = lead, lead = lead->link) // ∞∞¿∫ ¥‹æÓ∏¶ √£∞≈≥™ ≈◊¿Ã∫Ì¿« ≥°±Ó¡ˆ ∞¨¿ª ∞ÊøÏ forπÆ ¡æ∑·
            {
                indexing_comparison++;
                if (strcmp(lead->key, file[i][j]) == 0) // ∞∞¿∫ ¥‹æÓ∞° µÈæÓø¬ ∞Õ¿Ã∂Û∏È
                {
                    lead->e[i].position[lead->e[i].count++] = j; // position √ﬂ∞°
                    flag = 1; // ∞∞¿∫ ¥‹æÓ∞° µÈæÓø”¥Ÿ¥¬ «•Ω√
                    break;
                }
            }

            if (flag == 0) // ∏∏æ‡ ∞∞¿∫¥‹æÓ∞° µÈæÓø¬ ∞Õ¿Ã æ∆¥œ∂Û∏È
            {
                temp = (infor_pointer)malloc(sizeof(information)); // information ¿˙¿Â«œ±‚ ¿ß«— ∞¯∞£¿ª µø¿˚«“¥Á

                for (int i = 0; i < 10; i++) // ¡§∫∏µÈ ª¿‘
                {
                    temp->e[i].txt = i + 1;
                    temp->e[i].count = 0;
                }

                temp->e[i].position[temp->e[i].count++] = j; // ¥‹æÓ¿« ¿ßƒ°∏¶ ª¿‘

                temp->key = file[i][j]; // ¥‹æÓ ª¿‘
                temp->link = NULL; // chainingø°º≠ ø¨∞·

                if (trail) trail->link = temp;
                else Table[w] = temp;

                total_words++; // ªı∑ŒøÓ ¥‹æÓ∞° √ﬂ∞°µ«æ˙¿∏π«∑Œ total_wordsø° π›øµ
            }
        }
    }
}

infor_pointer chaining_search(char* insert) // ¿‘∑¬µ» ¥‹æÓ∏¶ «ÿΩ√≈◊¿Ã∫Ìø°º≠ √£∞Ì ¡÷º“∞™¿ª π›»Ø«ÿ¡÷¥¬ «‘ºˆ
{
    int i = hash(insert);
    infor_pointer ptr;

    for (ptr = Table[i]; ptr; ptr = ptr->link)
    {
        searching_comparison++;

        if (strcmp(ptr->key, insert) == 0)
        {
            return ptr;
        }
    }

    printf("no such word !!!\n\n");
    return NULL;
}

int hash(char* key) // «ÿΩÃ«‘ºˆ - division«‘ºˆ
{
    return (transform(key) % TABLE_SIZE);
}

int transform(char* key) // «ÿΩÃ«‘ºˆ - folding «‘ºˆ
{
    int number = 0;
    while (*key) {
        number += *key++;
    }
    return number;
}
void sort(element list[], int n) // ¥‹æÓ¿« µÓ¿Â»Ωºˆ∏¶ ø¿∏ß¬˜º¯¿∏∑Œ ¡§∑ƒ«œ±‚ ¿ß«— «‘ºˆ
{
    element next;
    int j;

    for (int i = 1; i < n; i++)
    {
        next = list[i];

        for (j = i - 1; j >= 0 && next.count < list[j].count; j--)
        {
            list[j + 1] = list[j];
        }

        list[j + 1] = next;
    }
}
