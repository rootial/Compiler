#include<bits/stdc++.h>

#define in freopen("solve_in.txt", "r", stdin);
#define out freopen("out.txt", "w", stdout);
#define END -1
#define OKAY 1
#define ERR 0
#define bug(x) cerr << "Line " << (x) << ": >>>>>>>>>>" << endl;
#define stop system("pause");
using namespace std;
const int KEYWORDS = 32;

const int NUM_ID = KEYWORDS + 10;
const int NUM_CHA = NUM_ID + 1;
const int NUM_STR = NUM_CHA + 1;
const int NUM_INT = NUM_STR + 1;
const int NUM_DBL = NUM_INT + 1;


#define ERR_RMVCOM "Error occurs while removing comments!"
#define ERR_ANACODE "Error occurs while analyzing code!"
const int maxn = (int)1e5 + 10;
char keywords[KEYWORDS][100] = {
    "auto", "break", "case",  "char",//
    "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float",
    "for", "goto", "if", "int", "long", "register",
    "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned",
    "void", "volatile", "while"
};

struct WordType {
    string word;
    int type;
    WordType() {
        word = "";
        type = -1;
    }
} word;
/** 处理去掉注释包括注释的两种形式：

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


bool removeComments(FILE *fin, string &saved) {
    //
    /* */
    char ch, nextCh;
    while (~(ch = fgetc(fin))) {
        if (~(nextCh = fgetc(fin))) {
            if (ch == '/' && nextCh == '*') {
                saved += '\n';
                while (~(ch = fgetc(fin)) && ~(nextCh = fgetc(fin)) &&
                        !(ch == '*' && nextCh == '/')) {
                    ungetc(nextCh, fin);
                }
                if (!(~ch) || !(~nextCh))  {
                    return false;
                }
            } else if (ch == '/' && nextCh == '/') {
                saved += '\n';
                while (~(ch = fgetc(fin)) && ch != '\n') ;
            } else {
                saved += ch;
                ungetc(nextCh, fin);
            }
        } else {
            saved += ch;
        }
    }
    return true;
}
void Revc(string &str, stringstream &strIn) {
    for (int i = (int)str.size()-1; i >= 0; i--) {
        strIn.putback(str[i]);
    }
}
int cnt = 0;
void writeWord(WordType typeRes, FILE *fout) {
    cnt++;
    fprintf(fout, "(%s, %d)\n", typeRes.word.data(), typeRes.type);
}
//checked
int readInt(string &fres, stringstream &strIn, bool can = true) {
    if (can)
        fres = "";
    string res = "";
    char ch;
    while (~(ch = strIn.get()) &&
            (ch == ' ' || ch == '\n' || ch == '\t')) {
        ;
    }

    if (strIn.eof()) return END;
    if (ch == '+' || ch == '-' || (ch >= '0' && ch <= '9')) {
        res += ch, fres += ch;
    } else {
        strIn.putback(ch);
        return ERR;
    }
    while (~(ch = strIn.get()) &&
            (ch >= '0' && ch <= '9')) {
        res += ch, fres += ch;
    }
    int st = strIn.eof();

    if (st) {
        if (isdigit(res[0]) || (int)res.size() > 1)
            return OKAY;
        else return ERR;
    }
    strIn.putback(ch);
    if ((int)res.size() == 1 && !isdigit(res[0])) {
        strIn.putback(res[0]);
    }
    return isdigit(res[0]) || (int)res.size() > 1 ? OKAY : ERR;
}
int readFloat(string &res, stringstream &strIn) {
//    cout << strIn.str() << endl;
    res = "";
    char ch;
    while (~(ch = strIn.get()) &&
            (ch == ' ' || ch == '\n' || ch == '\t')) {
        ;
    }
    if (strIn.eof()) return END;
    if (ch != '.' && ch != '+' && ch != '-' && !(ch <= '9' && ch >= '0')) {
        return ERR;
    }
    if (ch == '.') {
        res += ch;
        if ((ch = strIn.get()) == -1 || !isdigit(ch)) {

            if (!strIn.eof()) {
                strIn.putback(ch);
            }
            strIn.putback(res[0]);
            return ERR;
        } else {
//        cout << res << endl;
            strIn.putback(ch);
//            cout << ch << endl;
            readInt(res, strIn, false);
//            cout << res << endl;
            if ((ch = strIn.get()) == -1 || ch != 'e') {
                if (!strIn.eof()) {
                    strIn.putback(ch);
                }
                return OKAY;
            } else {
                res += ch;
                if ((ch = strIn.get()) == -1 || !(ch == '+' || ch == '-' || isdigit(ch))) {
                    return ERR;
                } else {
                    strIn.putback(ch);
                    if (readInt(res, strIn, false) == ERR) return ERR;
                }
            }
        }
    } else if (isdigit(ch)) {
        strIn.putback(ch);
        readInt(res, strIn, false);

        if ((ch = strIn.get()) == -1 || ch != '.') {

            if (ch != 'e') {

                if (ch != -1)
                    strIn.putback(ch);
                Revc(res, strIn);
                return ERR;
            } else {
                res += ch;
                if ((ch = strIn.get()) == -1 || !(ch == '+' || ch == '-' || isdigit(ch))) {
                    return ERR;
                } else {
                    strIn.putback(ch);
                    if (readInt(res, strIn, false) == ERR) return ERR;
                }
            }

        } else {
            res += ch;
            if ((ch = strIn.get()) == -1) {
                return OKAY;
            } else if (isdigit(ch)) {
                strIn.putback(ch);
                readInt(res, strIn, false);
                if ((ch = strIn.get()) == -1 || ch != 'e') {
                    if (!strIn.eof())strIn.putback(ch);
                    return OKAY;
                } else {
                    res += ch;
                    if ((ch = strIn.get()) == -1 || !(ch == '+' || ch == '-' || isdigit(ch))) {
                        return ERR;
                    } else {
                        strIn.putback(ch);
                        if (readInt(res, strIn, false) == ERR) return ERR;
                    }
                }
            } else if (ch == 'e') {
                res += ch;
                if ((ch = strIn.get()) == -1 || !(ch == '+' || ch == '-' || isdigit(ch))) {
                    return ERR;
                } else {
                    strIn.putback(ch);
                    if (readInt(res, strIn, false) == ERR) return ERR;
                }
            } else {
                strIn.putback(ch);
                return OKAY;
            }
        }
    } else {

    }
    return OKAY;
}
int readCha(string &res, stringstream &strIn) {
    res = "";
    char ch;
    while (~(ch = strIn.get()) &&
            (ch == ' ' || ch == '\n' || ch == '\t')) {
        ;
    }
    if (strIn.eof()) return END;
    if (ch == '\'') {
        res += ch;
        strIn >> ch;
        if (strIn.eof()) {
            strIn.putback(ch);
            return ERR;
        }
        if (ch == '\\') {
            res += ch;
            if ((ch = strIn.get()) == -1) return ERR;
            res += ch;
            if ((ch = strIn.get()) == -1 || ch != '\'') {
                return ERR;
            }
            res += ch;
        } else {
            res += ch;
//            cout << ch << endl;
            if ((ch = strIn.get()) == -1 || ch != '\'') {
                return ERR;
            }
            res += ch;
        }
    } else {
        strIn.putback(ch);
        return ERR;
    }
    return OKAY;
}
int readString(string &res, stringstream &strIn) {
    res = "";
    char ch;
    while (~(ch = strIn.get()) &&
            (ch == ' ' || ch == '\n' || ch == '\t')) {
        ;
    }
    if (strIn.eof()) return END;

    if (ch == '"') {
        res += ch;
        char last = ch;
        bool found = false;
        while (~(ch = strIn.get())) {

            res += ch;
            if (ch == '"' && last != '\\') {
                found = true;
                break;
            }
            last = ch;
        }
        if (!found) {
            if (strIn.eof()) return ERR;
            else {
//                    bug(1)
                strIn.putback(ch);
                for (int i = (int)res.size()-1; i >= 0; i--) {
                    strIn.putback(res[i]);
//                    cout << res[i];
                }

            }
        }
    } else {
        strIn.putback(ch);
        return ERR;
    }
    return OKAY;
}
int main(int argc, char *argv[]) {

    char sourcefile[50] = {"in7.txt"};
    char destfile[50] = {"out7.txt"};
    FILE *fin, *fout;
    if (argc > 1)	{
        strcpy(sourcefile,argv[1]);
        strcpy(destfile,argv[2]);
    } else {
        printf("input sourcefile and destfile:");
        scanf("%s",sourcefile);
        scanf("%s",destfile);
    }
    string code;

    if ((fin=fopen(sourcefile,"r")) == NULL) {
        printf("open source file failed\n");
        exit(-1);
    }
    if ((fout=fopen(destfile, "w")) == NULL) {
        printf("open dest file failed\n");
        exit(-1);
    }
    if (!removeComments(fin, code)) {
        puts(ERR_RMVCOM);
        exit(-1);
    }
//    cout << code << endl;
    stringstream strIn(code);
//    WordType word;
//    cout << readFloat(word.word, strIn) << ' ';
//    cout << word.word << endl;
//    return 0;
    while (!strIn.eof()) {
        char ch = strIn.get();
        while (ch  == ' ' || ch == '\t' || ch == '\n') {
            ch = strIn.get();
            if (strIn.eof()) break;
        }
        if (strIn.eof()) break;
        WordType wordRes;

        if (isalpha(ch) || ch == '_') {
            wordRes.word += ch;
            while (~(ch = strIn.get()) &&
                    (isalpha(ch) || ch == '_' || isdigit(ch))) {
                wordRes.word +=ch;
            }
            int type;
            if (~(type = isKeyWords(wordRes.word))) { //keywords
                wordRes.type = type;
            } else { //identifier
                wordRes.type = NUM_ID;
            }
//            cout << wordRes.word << endl;
            if (!strIn.eof()) {//not eof put back to strIn
                strIn.putback(ch);
            }
        } else if (isdigit(ch)) {//if starts with digit , read int or float

            strIn.putback(ch);
            if (readFloat(wordRes.word, strIn) == OKAY) {
                wordRes.type = NUM_DBL;
            } else if (readInt(wordRes.word, strIn) == OKAY) {
                wordRes.type = NUM_INT;
            }
        } else if(ch == '.') {//if starts with . , read float
            char nextCh;
            nextCh = strIn.get();
//            cout << nextCh << endl;
//            cout << wordRes.word << endl;
            if (strIn.eof() || !isdigit(nextCh)) {
                if (!strIn.eof()) {
                    strIn.putback(nextCh);
                }
                wordRes.word += ch;
                wordRes.type = 138;
            } else {
                strIn.putback(nextCh);
                strIn.putback(ch);
                if (readFloat(wordRes.word, strIn) == OKAY) {
                    wordRes.type = NUM_DBL;
                } else {
                    puts(ERR_ANACODE);
                    exit(-1);
                }
            }
        } else if (ch == '\'') {//if starts with ' , read character
            strIn.putback(ch);
            if (readCha(wordRes.word, strIn) == OKAY) {
                wordRes.type = NUM_CHA;
            } else {
                puts(ERR_ANACODE);
                exit(-1);
            }
        } else if (ch == '"') {//if starts with " , read string
            strIn.putback(ch);
            if (readString(wordRes.word, strIn) == OKAY) {
                wordRes.type = NUM_STR;
            } else {
                puts(ERR_ANACODE);
                exit(-1);
            }
        } else {
            char nextCh1, nextCh2;

            switch (ch) {
            case '+':
                nextCh1 = strIn.get();
                if (strIn.eof()) {
                    wordRes.word += ch;
                    wordRes.type = 101;
                } else {

                    wordRes.word += ch;
                    if (nextCh1 == '+') { //++
                        wordRes.word += nextCh1;
                        wordRes.type = 112;
                    } else if (nextCh1 == '=') {//+=
                        wordRes.word += nextCh1;
                        wordRes.type = 107;
                    } else {
                        strIn.putback(nextCh1);
                        wordRes.type = 101;
                    }
                }
                break;
            case '-':
                nextCh1 = strIn.get();
                if (strIn.eof()) {
                    wordRes.word += ch;
                    wordRes.type = 102;
                } else {

                    wordRes.word += ch;
                    if (nextCh1 == '-') { //++
                        wordRes.word += nextCh1;
                        wordRes.type = 113;
                    } else if (nextCh1 == '=') {//+=
                        wordRes.word += nextCh1;
                        wordRes.type = 108;
                    } else if (nextCh1 == '>') {
                        wordRes.word += nextCh1;
                        wordRes.type = 114;
                    } else {
                        strIn.putback(nextCh1);
                        wordRes.type = 102;
                    }
                }
                break;
            case '*':
                nextCh1 = strIn.get();
                if (strIn.eof()) {
                    wordRes.word += ch;
                    wordRes.type = 103;
                } else {
                    wordRes.word += ch;
                    if (nextCh1 == '=') {//+=
                        wordRes.word += nextCh1;
                        wordRes.type = 109;
                    } else {
                        strIn.putback(nextCh1);
                        wordRes.type = 103;
                    }
                }
                break;

            case '/':
                nextCh1 = strIn.get();
                if (strIn.eof()) {
                    wordRes.word += ch;
                    wordRes.type = 104;
                } else {
                    wordRes.word += ch;
                    if (nextCh1 == '=') {//+=
                        wordRes.word += nextCh1;
                        wordRes.type = 110;
                    } else {
                        strIn.putback(nextCh1);
                        wordRes.type = 104;
                    }
                }
            case '%':
                nextCh1 = strIn.get();
                if (strIn.eof()) {
                    wordRes.word += ch;
                    wordRes.type = 105;
                } else {
                    wordRes.word += ch;
                    if (nextCh1 == '=') {//+=
                        wordRes.word += nextCh1;
                        wordRes.type = 111;
                    } else {
                        strIn.putback(nextCh1);
                        wordRes.type = 105;
                    }
                }
                break;
            case '>':
                nextCh1 = strIn.get();
                wordRes.word += ch;
                if (strIn.eof()) {
                    wordRes.type = 115;
                } else {
                    if (nextCh1 == '>') {
                        nextCh2 = strIn.get();
                        wordRes.word += nextCh1;
                        if (strIn.eof()) {
                            wordRes.type = 117;
                        } else {
                            if (nextCh2 == '=') {
                                wordRes.word += nextCh2;
                                wordRes.type = 118;
                            } else {
                                wordRes.type = 117;
                                strIn.putback(nextCh2);
                            }
                        }
                    } else if (nextCh1 == '=') {
                        wordRes.word += nextCh1;
                        wordRes.type = 116;
                    } else {
                        strIn.putback(nextCh1);
                        wordRes.type = 115;
                    }
                }
                break;
            case '<':
                nextCh1 = strIn.get();
                wordRes.word += ch;
                if (strIn.eof()) {
                    wordRes.type = 119;
                } else {
                    if (nextCh1 == '<') {
                        nextCh2 = strIn.get();
                        wordRes.word += nextCh1;
                        if (strIn.eof()) {
                            wordRes.type = 121;
                        } else {
                            if (nextCh2 == '=') {
                                wordRes.word += nextCh2;
                                wordRes.type = 122;
                            } else {
                                wordRes.type = 121;
                                strIn.putback(nextCh2);
                            }
                        }
                    } else if (nextCh1 == '=') {
                        wordRes.word += nextCh1;
                        wordRes.type = 120;
                    } else {
                        strIn.putback(nextCh1);
                        wordRes.type = 119;
                    }
                }
                break;
            case '=':
                nextCh1 = strIn.get();
                if (strIn.eof()) {
                    wordRes.word += ch;
                    wordRes.type = 123;
                } else {
                    wordRes.word += ch;
                    if (nextCh1 == '=') { //++
                        wordRes.word += nextCh1;
                        wordRes.type = 124;
                    } else {
                        strIn.putback(nextCh1);
                        wordRes.type = 123;
                    }
                }
                break;
            case '!':
                nextCh1 = strIn.get();
                if (strIn.eof()) {
                    wordRes.word += ch;
                    wordRes.type = 125;
                } else {
                    wordRes.word += ch;
                    if (nextCh1 == '=') { //++
                        wordRes.word += nextCh1;
                        wordRes.type = 126;
                    } else {
                        strIn.putback(nextCh1);
                        wordRes.type = 125;
                    }
                }
                break;
            case '&':
                nextCh1 = strIn.get();
                if (strIn.eof()) {
                    wordRes.word += ch;
                    wordRes.type = 128;
                } else {
                    wordRes.word += ch;
                    if (nextCh1 == '&') { //++
                        wordRes.word += nextCh1;
                        wordRes.type = 127;
                    } else if (nextCh1 == '=') {//+=
                        wordRes.word += nextCh1;
                        wordRes.type = 129;
                    } else {
                        strIn.putback(nextCh1);
                        wordRes.type = 128;
                    }
                }
                break;
            case '|':
                nextCh1 = strIn.get();
                if (strIn.eof()) {
                    wordRes.word += ch;
                    wordRes.type = 131;
                } else {
                    wordRes.word += ch;
                    if (nextCh1 == '|') { //++
                        wordRes.word += nextCh1;
                        wordRes.type = 130;
                    } else if (nextCh1 == '=') {//+=
                        wordRes.word += nextCh1;
                        wordRes.type = 132;
                    } else {
                        strIn.putback(nextCh1);
                        wordRes.type = 131;
                    }
                }
                break;
            case '^':
                nextCh1 = strIn.get();
                if (strIn.eof()) {
                    wordRes.word += ch;
                    wordRes.type = 133;
                } else {
                    wordRes.word += ch;
                    if (nextCh1 == '=') { //++
                        wordRes.word += nextCh1;
                        wordRes.type = 134;
                    } else {
                        strIn.putback(nextCh1);
                        wordRes.type = 133;
                    }
                }
                break;
            case '~':
                wordRes.word += ch;
                wordRes.type = 135;
                break;
            case '?':
                wordRes.word += ch;
                wordRes.type = 136;
                break;
            case ':':
                wordRes.word += ch;
                wordRes.type = 137;
                break;
            case '[':
                wordRes.word += ch;
                wordRes.type = 139;
                break;
            case ']':
                wordRes.word += ch;
                wordRes.type = 140;
                break;
            case ',':
                wordRes.word += ch;
                wordRes.type = 141;
                break;
            case ';':
                wordRes.word += ch;
                wordRes.type = 141+1;
                break;
            case '{':
                wordRes.word += ch;
                wordRes.type = 141+2;
                break;
            case '}':
                wordRes.word += ch;
                wordRes.type = 141+3;
                break;
            case '(':
                wordRes.word += ch;
                wordRes.type = 141+4;
                break;
            case ')':
                wordRes.word += ch;
                wordRes.type = 141+5;
                break;
            case '#':
                wordRes.word += ch;
                wordRes.type = 141+6;
                break;
            default:
                puts(ERR_ANACODE);
                exit(-1);
            }
        }
        writeWord(wordRes, fout);
    }
//    bug(cnt)
    return 0;
}
