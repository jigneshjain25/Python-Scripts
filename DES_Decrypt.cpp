#include<iostream>
#include<string.h>
#include<cstdio>
#define ll unsigned long long
#include "DES.H"
using namespace std;

string tobinary(ll n){
	if(n==0)return "0";
	string ans="";
	while(n>0){
	    int a = n%2;
		if(a)ans='1'+ans;
		else ans='0'+ans;
		n/=2;
	}
	return ans;
}
// just binary to decimal
unsigned int ascii(string bin){
	unsigned int ans=0;
	for(int i=0;i<bin.length();i++)
		{
			int b = bin[i]=='1' ? 1:0;
			if(b)	ans|=(1u<<(bin.length()-1-i));
		}
	return ans;
}


void printAscii(string bin){
	while(bin.length()!=64)bin="0"+bin;
	for(int i=0;i<bin.length();i+=8){
		string temp="";
		for(int j=i;j<i+8;j++)
			temp+=bin[j];
		cout<<char(ascii(temp));
	}
}


ll getKey(unsigned int &L, unsigned int &R,int round){
    unsigned int term = (1u<<28) - 1;
    int shifts = rotate_schedule[round-1];
    for(int i=0;i<shifts;i++){
        int highest_bit = L & (1u << 27);
        L<<=1;
        if(highest_bit)L|=1;
    }
    L&=term;
    for(int i=0;i<shifts;i++){
        int highest_bit = R & (1u << 27);
        R<<=1;
        if(highest_bit)R|=1;
    }
    R&=term;
    ll finalans=0;
    for(int i=0;i<48;i++){
        int bit = PC_2[i];
        if(bit < 29){
            if(L & (1u<<(28-bit)))
                finalans|=1;
        }
        else{
            bit-=28;
            if(R & (1u<<(28-bit)))
                finalans|=1;
        }
        finalans<<=1;
    }
    finalans>>=1;
    return finalans;
}

ll hexToLong(char key[17]){
    ll keyLong=0;
	for(int i=0;i<16;i++){
		unsigned int ch = (key[i] >= '0' && key[i] <='9') ? key[i]-'0' : key[i]-'a'+10;
		for(int j=0;j<4;j++){
			unsigned int bit = ch & (1u<<(3-j));
			keyLong|=bit;
		}
		if(i!=15)keyLong<<=4;
	}
//    cout<<"JJ "<<keyLong<<endl;
    return keyLong;
}


ll charToLong(char key[9]){
    ll keyLong=0;
	for(int i=0;i<8;i++){
		unsigned int ch = key[i];
		for(int j=0;j<8;j++){
			unsigned int bit = ch & (1u<<(7-j));
			keyLong|=bit;
		}
		if(i!=7)keyLong<<=8;
	}
    return keyLong;
}

unsigned int fiestal(unsigned int Rd,ll key){
    ll R=0;
    for(int i=0;i<48;i++) {
        if(Rd & (1u<<(32-EP[i])))
            R|=1;
        R<<=1;
    }
    R>>=1;
    R^=key;
    
    ll finalans=0;
    int sno=-1;
    for(int i=47;i>=0;i-=6){
        sno++;
        string row="",col="";
        if(R & (1ull<<i))row+='1';
        else row+='0';
        if(R & (1ull<<(i-5)))row+='1';
        else row+='0';

        for(int j=(i-1);j>=(i-4);j--)
            if(R & (1ull<<j))col+='1';
            else col+='0';
        
        unsigned int term = S[sno][ascii(row)][ascii(col)];
        for(int j=3;j>=0;j--)
        {
            if(term & (1u<<j))finalans|=1;
            finalans<<=1;
        }
    }

    finalans>>=1;
    unsigned int fR = finalans;
    unsigned int ffR=0;

    for(int i=0;i<32;i++){
        int bit = P[i];
        if(fR & (1u<<(32-bit))) ffR|=1;
        if(i!=31)ffR<<=1;
    }

    return ffR;
}

void encrypt(ll roundKeys[16],char text[17]){
    
    ll textLong = hexToLong(text);

   // cout<<"\nJJE "<<textLong<<endl;

    ll temp=0;
	//check(tobinary(textLong));
   
   // Initial Permutation
    for(int i=0;i<64;i++){
        if(textLong & (1ull<<(64-IP[i]))) temp|=1;
        if(i!=63)temp<<=1;
    }
    
    textLong = temp;
    unsigned int text_l=0, text_r=0,ntext_l=0,ntext_r=0;
    
    //break into two 32 bit halves
    for(int i=63;i>=32;i--){
		ll d = textLong & (1ull<<i);
		if(d) text_l|=1;
		if(i!=32)text_l<<=1;
	}
	for(int i=31;i>=0;i--){
		ll d = textLong & (1ull<<i);
		if(d) text_r|=1;
		if(i!=0)text_r<<=1;
	}

    for(int i=0;i<16;i++){
        ntext_l = text_r;
        ntext_r = text_l ^ fiestal(text_r,roundKeys[15-i]);
        text_r = ntext_r;
        text_l = ntext_l;
    }

    ll ciphertext=0;

    for(int i=0;i<64;i++){
        int bit = FP[i];
        if(bit < 33){
            if(ntext_r & (1u<<(32-bit)))
                ciphertext|=1;
        }
        else{
            bit-=32;
            if(ntext_l & (1u<<(32-bit)))
                ciphertext|=1;
        }
        if(i!=63)   ciphertext<<=1;
    }
//    cout<<"\nJJ "<<ciphertext<<endl;
	printAscii(tobinary(ciphertext));
}

void generateKeys(char key[9], ll roundKeys[16]){

    ll keyLong = charToLong(key);
	//check(tobinary(keyLong));

	unsigned int key_l=0,key_r=0;
	for(int i=0;i<28;i++){
		ll d = keyLong & (1ull<<(64-PC_1[i]));
		if(d) key_l|=1;
		key_l<<=1;
	}
    key_l>>=1;	
	for(int i=28;i<56;i++){
	    ll d = keyLong & (1ull<<(64-PC_1[i]));
		if(d) key_r|=1;
		key_r<<=1;
	}
    key_r>>=1;	
    
    for(int i=1;i<17;i++)
        roundKeys[i-1] = getKey(key_l,key_r,i);
}

int main(int argc,char **argv){
    
    char key[9],T[17];
    ll roundKeys[16];
    string text;
    
    puts("Enter key:");
    scanf("%s",key);

    if(strlen(key)!=8){
        puts("Error: Key must be of length 8!");
        return 1;
    }

    generateKeys(key,roundKeys);

  //  for(int i=0;i<16;i++)
    //    cout<<"\nJJK "<<roundKeys[i]<<endl;
    
    puts("Enter text:");
    cin.ignore();
    getline(cin,text);
    while(text.length()%16)text+="f";

    for(int i=0;i<text.length();i+=16){
        for(int j=i;j<i+16;j++)  T[j-i]=text[j];
        encrypt(roundKeys,T);
    }
    puts("");
}
