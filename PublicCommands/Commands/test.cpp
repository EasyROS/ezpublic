//#include <string>
//#include <iostream>
//#include <vector>
//#include <stdio.h>
//#include <cstdlib>
//
//#define TTY_PATH "/dev/tty"
//#define STTY_CLOSE             "stty raw -echo -F "
//#define STTY_OPEN            "stty -raw echo -F "
//
//using namespace std;
//static string str;
//static string pre;
//static vector <string> mem;
//static string last;
//
//void getNode(string str){
//
//}
//
//int main() {
//    pre = ">";
//    while (true) {
//        str = "";
//        printf("%s",pre.c_str());
//        while (true) {
//            system(STTY_CLOSE TTY_PATH);
//            char c = (char)getchar();
//
//            if(c == '\n' || c == 13){
//                printf("%c", c);
//                system(STTY_OPEN TTY_PATH);
//                break;
//            }
//            switch (c){
//                case 3:;
//                    system(STTY_OPEN TTY_PATH);
//                    printf("\nExit with code 3\n");
//                    return 0;
//                case 9:
//                    //cout << "tab";
//                    break;
//                case 127:
//                    if(str.length() > 0){
//                        str = str.substr(0,str.length() - 1);
//                        printf("\b \b");
//                    }
//                    break;
//                case 27:
//                    c = (char)getchar();
//                    switch (c){
//                        case 3:;
//                            system(STTY_OPEN TTY_PATH);
//                            printf("\nExit with code 3\n");
//                            return 0;
//                        case 9:
//                            //cout << "tab";
//                            break;
//                        case 127:
//                            if(str.length() > 0){
//                                str = str.substr(0,str.length() - 1);
//                                printf("\b \b");
//                            }
//                            break;
//                        case 91:
//                            c = (char)getchar();
//                            switch (c){
//                                case 3:;
//                                    system(STTY_OPEN TTY_PATH);
//                                    printf("\nExit with code 3\n");
//                                    return 0;
//                                case 9:
//                                    //cout << "tab";
//                                    break;
//                                case 127:
//                                    if(str.length() > 0){
//                                        str = str.substr(0,str.length() - 1);
//                                        printf("\b \b");
//                                    }
//                                    break;
//                                case 65:
//                                    printf("UP");
//                                    break;
//                                case 66:
//                                    printf("DN");
//                                    break;
//                                case 68:
//                                    printf("LF");
//                                    break;
//                                case 67:
//                                    printf("RT");
//                                    break;
//                                default:
//                                    str += c;
//                                    printf("%c", c);
//                            }
//                            break;
//                        default:
//                            str += c;
//                            printf("%c", c);
//                    }
//                    break;
//                default:
//                    str += c;
//                    printf("%c", c);
//            }
//
//        }
//
//
//
//        if (str == "exit"){
//            printf("\n");
//            break;
//        }
//        mem.push_back(str);
//        printf("\n%s\t\t\t%d\n",str.c_str(),str.length());
//        //cout << str << "\t\t\t" << str.length() << endl;
//    }
//    return 0;
//}
#include "lsCommand.hpp"
#include <iostream>
using namespace std;
int main(){
    cout << "ls" << endl;
    return 0;
}