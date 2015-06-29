#include<bits/stdc++.h>
using namespace std;
#define KEYWORDS 13
#define ERR_RMVCOM "Error occurs while removing comments!"

const int maxn = (int)1e5 + 10;
char keywords[KEYWORDS][100] = {"main", "int", "char", "long", "float", "double", "if", "else", "for", "do", "switch",
"while", "void"};
char code[maxn];//存放去掉注释之后的代码

struct WordType {
    string word;
    int type;
    WordType() {
        word = "";
        type = -1;
    }
} word;
/** 处理去掉注释包括注释的两种形式：
#1 //
#2 /* * /
 *  返回值表示处理过程中注释是否正确
 *  处理好的代码存放在char saved[] 数组
*/
bool cmp(string s1, char *s2) {
    int index = 0;
    while (index < (int)s1.size() && s2[index]) {
        if (s1[index] != s2[index]) return false;
        index++;
    }
    if (index == (int)s1.size() && !s2[index]) return true;
    return false;
}
int isKeyWords(string word) {
    for (int index = 0; index < KEYWORDS; index++) {
        if (cmp(word, keywords[index])) return index;
    }
    return -1;
}
bool removeComments(FILE *fin, char *saved) {
     int len = 0;
     return true;
}
void writeWord(WordType typeRes, FILE *fout) {
    fprintf(fout, "(%s, %d)\n", typeRes.word.data(), typeRes.type);
}
int main(int argc,char *argv[]) {
    FILE *fin,*fout;
    char sourcefile[30], destfile[30];

    if (argc>1)	{
        strcpy(sourcefile,argv[1]);
        strcpy(destfile,argv[2]);
    } else {
        printf("input sourcefile and destfile:");
        scanf("%s",sourcefile);
        scanf("%s",destfile);
    }

    if ((fin=fopen(sourcefile,"r"))==NULL)	{
        printf("open source file fail\n");
        exit(-1);
    }

    if ((fout=fopen(destfile,"w")) == NULL) {
        printf("open dest file fail\n");
        exit(-1);
    }
    if (!removeComments(fin, code)) {
        puts(ERR_RMVCOM);
        exit(-1);
    }
    int index = 0;
    int cdLen = strlen(code);

    while (index < cdLen) {
        char ch;
        while ((ch = code[index++]) == ' ' || ch == '\t' ||ch == '\n') ;
        WordType wordRes;
//
        if (isalpha(ch) || ch == '_')	{
            do {
                wordRes.word +=ch;
            } while (isalpha(ch=code[index++]) || ch == '_' || isdigit(ch));
            int type;
            if (~(type = isKeyWords(wordRes.word))) {//查询是否为关键字
                wordRes.type = type;
            } else { //为标识符
                wordRes.type = 14;
            }
            index--;
        } else if (isdigit(ch)) {
//            int i=0;
//            do {
//                w.value[i++]=ch;
//            } while (isdigit(ch=fgetc(fin)));
//            w.value[i]='\0';
//            w.kind=11;
//            ungetc(c,fin);
        } else {
//            switch (c) {
//            case EOF:
//                continue;
//            case '=':
//                c=fgetc(fin);
//                if (c!='=') {
//                    w.kind=12;
//                    strcpy(w.value,"=");
//                    ungetc(c,fin);
//                } else {
//                    w.kind=12;
//                    strcpy(w.value,"==");
//                }
//                break;
//            case ';':
//                w.kind=12;
//                strcpy(w.value,";");
//                break;
//            default:
//                printf("ERROR!");
//                exit(-2);
//            }
        }
         writeWord(wordRes, fout);
    }
    fclose(fout);
    return 0;
}
