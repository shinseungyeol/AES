//
//  AESDecrypt.h
//  AES
//
//  Created by ShinSeungYeol on 2018. 10. 21..
//  Copyright © 2018년 ShinSeungYeol. All rights reserved.
//


#include "AESMath.h"
#ifndef AESDecrypt_h
#define AESDecrypt_h





void invSubBytes(unsigned char state[]){
    for(int i=0; i<16; i++)
        state[i] = inv_sbox[state[i]];
}//sub byte




void invShiftRows(unsigned char state[]){
    unsigned char tmp[16];
    for(int i=0; i<16; i++)
        tmp[i] = state[i]; //tmp에 state 임시로 복사
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            state[4*i+j] = tmp[4*i+(j+(4-i))%4];
}




void invMixColumns(unsigned char state[]){
    unsigned char tmp[16];
    for(int i=0; i<16; i++)
        tmp[i]=state[i];
    
    for(int i=0; i<4; i++){
        state[0+i] = multiple(tmp[0+i],0x0e)^multiple(tmp[4+i],0x0b)^multiple(tmp[8+i],0x0d)^multiple(tmp[12+i],0x09);
        state[4+i] = multiple(tmp[0+i],0x09)^multiple(tmp[4+i],0x0e)^multiple(tmp[8+i],0x0b)^multiple(tmp[12+i],0x0d);
        state[8+i] = multiple(tmp[0+i],0x0d)^multiple(tmp[4+i],0x09)^multiple(tmp[8+i],0x0e)^multiple(tmp[12+i],0x0b);
        state[12+i] = multiple(tmp[0+i],0x0b)^multiple(tmp[4+i],0x0d)^multiple(tmp[8+i],0x09)^multiple(tmp[12+i],0x0e);
    }
}//mix columns 실행




#endif /* AESDecrypt_h */
