//
//  AESEncrypt.h
//  AES
//
//  Created by ShinSeungYeol on 2018. 10. 21..
//  Copyright © 2018년 ShinSeungYeol. All rights reserved.
//

#include "AESMath.h"

#ifndef AESEncrypt_h
#define AESEncrypt_h



void AddRoundKey(unsigned char state[],unsigned int w[],int num_of_round){
    unsigned char key[16];
    unsigned char tmp[16]; //state 저장할 임시 배열
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            key[i+j*4] = (w[num_of_round*4+i]>>(32-(j+1)*8))&0x000000ff;
            //32bit w를 8bit key로 사용하기 위해서 4분할, row,col reverse
            tmp[i*4+j] = state[i*4+j];
            //tmp에 state 임시 저장
        }
    }//w값을 key값으로 만들기 위해 일차원 배열을 이차원 배열처럼 사용, row,col을 반대로 사용
    
\
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            state[i+j*4] = tmp[i+j*4]^key[i+j*4];
        }
    }//128비트 라운드키와 state를 xor
    
    
    if(num_of_round<10){ //마지막 라운드에선 실행하지 않는다.
        for(int i=0; i<4; i++){
            w[(num_of_round+1)*4+i] = w[num_of_round*4+i];
        }//다음 키 값 인덱스에 지금 키 값 복사(계산을 용이하게 하려고)
        
        
        unsigned init_xor_value = (w[(num_of_round+1)*4+3]<<8)|(w[(num_of_round+1)*4+3]>>24);
        //w3 1byte rotation해서 w0과 xor할 변수의 초기값을 설정
        
        unsigned int xor_value = 0;
        for(int i=0; i<4; i++){
            unsigned char idx = init_xor_value>>(32-8*(i+1))&0xff; //subByte->8비트로 분할한 init_xor_value가 s의 인덱스가 됨
            unsigned char tmp = s_box[idx]; //임시 값에 저장한 후
            xor_value|=(tmp<<(32-(i+1)*8)); // w0과 xor할 변수의 bit 위치에 저장
        }//SubBytes
        
        w[(num_of_round+1)*4]^=xor_value^round_constant[num_of_round]; //w0 = w0^xor_value^costant
        for(int i=1; i<4; i++){
            w[(num_of_round+1)*4+i]^=w[(num_of_round+1)*4+i-1];  //if(n!=0) w[n] = w[n]^w[n-1]
        }//w 값 모두 생성
    }
}

void SubBytes(unsigned char state[]){
    for(int i=0; i<16; i++)
        state[i] = s_box[state[i]];
}//sub byte




void ShiftRows(unsigned char state[]){
    unsigned char tmp[16];
    for(int i=0; i<16; i++)
        tmp[i] = state[i]; //tmp에 state 임시로 복사
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            state[i*4+j] = tmp[i*4+(i+j)%4];
        }
    }
}

void MixColumns(unsigned char state[]){
    unsigned char tmp[16];
    for(int i=0; i<16; i++)
        tmp[i]=state[i];
    
    for(int i=0; i<4; i++){
        state[0+i] = multiple(tmp[0+i],2)^multiple(tmp[4+i],3)^multiple(tmp[8+i],1)^multiple(tmp[12+i],1);
        state[4+i] = multiple(tmp[0+i],1)^multiple(tmp[4+i],2)^multiple(tmp[8+i],3)^multiple(tmp[12+i],1);
        state[8+i] = multiple(tmp[0+i],1)^multiple(tmp[4+i],1)^multiple(tmp[8+i],2)^multiple(tmp[12+i],3);
        state[12+i] = multiple(tmp[0+i],3)^multiple(tmp[4+i],1)^multiple(tmp[8+i],1)^multiple(tmp[12+i],2);
    }
}//mix columns 실행



#endif /* AESEncrypt_h */
