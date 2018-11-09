//
//  main.c
//  AES
//
//  Created by ShinSeungYeol on 2018. 9. 20..
//  Copyright © 2018년 ShinSeungYeol. All rights reserved.
//
/*
 
 Cipher(byte in[4*Nb], byte out[4*Nb], word w[Nb*(Nr+1)])
 begin
 byte state[4, Nb]
 state = in
 AddRoundKey(state, w[0, Nb-1])// 초기키값이add 됨
 for round = 1 step 1 to Nr–1 // 라운드수보다한번적게돌아감
 SubBytes(state)
 ShiftRows(state)
 MixColumns(state)
 AddRoundKey(state, w[round*Nb, (round+1)*Nb-1])
 end for
 SubBytes(state)
 ShiftRows(state)
 AddRoundKey(state, w[Nr*Nb, (Nr+1)*Nb-1])
 // 마지막라운드에서는MixColumns수행안함*/




#include "AESEncrypt.h"
#include "AESDecrypt.h"
#include <stdio.h>


void reverse_matrix (unsigned char state[]){
    unsigned char tmp[16]; //state 배열을 변환하기 위해서 임시 저장할 임시 배열
    int i=0,j=0;
    for(i=0; i<16; i++)
        tmp[i] = state[i];
    for(i=0; i<4; i++)
        for(j=0; j<4; j++)
            state[j*4+i] = tmp[i*4+j];
}//state row랑 col 바꿈


int main(int argc, const char * argv[]) {
    
    unsigned char state[16]={0x32,0x43,0xf6,0xa8,0x88,0x5a,0x30,0x8d,0x31,0x31,0x98,0xa2,0xe0,0x37,0x07,0x34};
    
    
    unsigned int w[44];
    w[0] = 0x2b7e1516;
    w[1] = 0x28aed2a6 ;
    w[2] = 0xabf71588;
    w[3] = 0x09cf4f3c;
    //2b7e1516 28aed2a6 abf71588 09cf4f3c
    
////////////////////////////////////////////////////////
    reverse_matrix(state); //state의 row랑 col 뒤집기
    AddRoundKey(state, w, 0);
    
    for(int i=1; i<=10; i++){
        SubBytes(state);
        ShiftRows(state);
        
        if(i!=10)MixColumns(state);
        AddRoundKey(state, w, i);
    }
///////////암호화////////////////////////////////////////
    
    //암호화 한 후에 state:
    printf("암호화: \n");
    for(int i=0; i<16; i++){
        printf("%02x ",state[i]);
        if(i%4==3) printf("\n");
    }
    
    
    
///////////////////////////////////////////////////////
   
    
    AddRoundKey(state, w, 10);
    
    
    for(int i=1; i<=10; i++){

        invShiftRows(state);
        invSubBytes(state);
        AddRoundKey(state, w, 10-i);
        if(i!=10) invMixColumns(state);
        
        
       
    }
    reverse_matrix(state); //state의 row랑 col 뒤집기
    
/////////////복구화////////////////////////////////////////
    

    

    //복호화 한 후에 state:
    printf("복호화: \n");
    for(int i=0; i<16; i++){
        printf("%02x ",state[i]);
        if(i%4==3) printf("\n");
    }
    printf("\n");

    
    
    
    return 0;
}
