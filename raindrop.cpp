#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <unistd.h>

using namespace std;

int hp=5, sleeptime=3;
string arr[20];

class option{
    public:
    virtual void d()=0;
};

class o2 : public option{
    public:
    virtual void d(){
        cout<<"추가로 숫자가 문자열에 포함됩니다."<<endl;
    }
};
class o3 : public option{
    public:
    virtual void d(){
        cout<<"추가로 특수문자가 문자열에 포함됩니다."<<endl;
    }
};

class option_ : public option{
    protected:
    option* o;
    public:
    option_(option* o_){
        o=o_;
    }
    virtual void d(){
        o->d();
    }
};

class option__ : public option_{
    public:
    option__(option* o):option_(o){}
    virtual void d(){
        o->d();
        d2();
    }
    private:
    void d2(){
        cout<<"추가로 특수문자가 문자열에 포함됩니다."<<endl;
    }
};

void ptrscr(){
    for(int i=0; i<20; i++){
        cout<<i<<arr[i];
    }
    cout<<"--------------------------------------------------"<<endl;
    cout<<"hp : "<<hp<<endl;
}

void func1(){
    string temp;
    while (hp){
        cin>>temp;
        for(int i=0; i<20; i++){
            string t=arr[i]; 
            if(arr[i].find(temp)!=string::npos){
                arr[i]="\n";
                ptrscr();
            }
        }
    }
    return;
}

int main(){
    string temp;
    
    string a="abcdefghijklnmopqrstuvwxyz";
    string b="~!@#$%^&*()-+=*.,?/<>:;";
    
    srand(time(NULL));
    bool option1=true, option2=false, option3=false;

    cout<<"문자열에 숫자를 넣을까요? Y/N"<<endl;
    cin>>temp;
    if(!temp.compare("Y")||!temp.compare("y")){
        option2=true;
    }

    cout<<"문자열에 특수문자를 넣을까요? Y/N"<<endl;
    cin>>temp;
    if(!temp.compare("Y")||!temp.compare("y")){
        option3=true;
    }

    cout<<"\n알파벳은 기본적으로 문자열에 포함됩니다."<<endl;
    if(option2&&!option3){
        o2* option=new o2();
        option->d();
        delete(option);
    }
    if(!option2&&option3){
        o3* option=new o3();
        option->d();
        delete(option); 
    }
    if(option2&&option3){
        option__* option=new option__(new o2());
        option->d();
        delete(option);
    }
    cout<<"\n"<<endl;

    for(int i=0; i<20; i++){
        arr[i]="\n";
        cout<<i<<"\n";
    }
    cout<<"------------------------------------------------------"<<endl;
    cout<<"hp : "<<hp<<"        시작하려면 아무키나 입력하세요."<<endl;
    cin>>temp;
    thread t1(func1);

    while(hp){
        string word="";
        int x, y;
        x=rand()%40+1;
        y=rand()%4+2;
        sleeptime=y;
        for(int i=0; i<x; i++){
            word+=" ";
        }
        if(arr[19].compare("\n")){
            hp--;
        }
        for(int i=19; i>0; i--){
            arr[i]=arr[i-1];
        }
        if(option2&&!option3){
            for(int i=0; i<10; i++){
                int o=rand()%2;
                if(o){
                    int t=rand()%26;
                    word+=a.at(t);
                }else{
                    int t=rand()%10;
                    word+=to_string(t);
                }
            }
        }else if(!option2&&option3){
            for(int i=0; i<10; i++){
                int o=rand()%2;
                if(o){
                    int t=rand()%26;
                    word+=a.at(t);
                }else{
                    int t=rand()%23;
                    word+=b.at(t);
                }
            }
        }else if(option2&&option3){
            for(int i=0; i<10; i++){
                int o=rand()%3;
                if(o==1){
                    int t=rand()%10;
                    word+=to_string(t);
                }else if(o==2){
                    int t=rand()%23;
                    word+=b.at(t);
                }else{
                    int t=rand()%26;
                    word+=a.at(t);
                }
            }
        }else{
            for(int i=0; i<10; i++){
                int t=rand()%26;
                word+=a.at(t);
            }
        }
        word+="\n";
        arr[0]=word;
    sleep(sleeptime);   
    cout<<"\n";
    ptrscr();
    }
    t1.join();
    for(int i=0; i<20; i++){
        cout<<"\n";
    }
    cout<<"게임 종료\n";
    return 0;
}