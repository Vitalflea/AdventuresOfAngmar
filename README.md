# Adventures of Angmar
[![C++](https://img.shields.io/badge/language-C%2B%2B-%23f34b7d.svg?style=plastic)](https://en.wikipedia.org/wiki/C%2B%2B) 
[![LOTRO](https://img.shields.io/badge/game-Echoes%20of%20Angmar-yellow.svg?style=plastic)](https://www.echoesofangmar.com/) 

Echoes of Angmar Unethical Refugees:

for hackers, cheaters, botters, and exploiters; and any other unethical players of LOTRO/EOA, Welcome!

https://discord.gg/m6Gqs2tQaA

## Reverse Engineering

### PL.DLL
A dll that gets loaded into the game in order to access player information such as player ID. I think it is also used for Russian localization but thats not what we are after. Lets have a look at the starting function in pseudocode.

```cpp
DWORD __usercall StartAddress@<eax>(int a1@<ebp>)
{
  HANDLE CurrentThread; // eax
  char v3; // al
  void *v4; // edx
  __int64 v6; // [esp-200h] [ebp-20Ch] BYREF
  int v7; // [esp-1F8h] [ebp-204h]
  int v8; // [esp-1F4h] [ebp-200h]
  int v9; // [esp-1F0h] [ebp-1FCh]
  int v10; // [esp-1ECh] [ebp-1F8h]
  _DWORD v11[4]; // [esp-1D4h] [ebp-1E0h] BYREF
  int v12; // [esp-1C4h] [ebp-1D0h]
  unsigned int v13; // [esp-1C0h] [ebp-1CCh]
  char v14; // [esp-1B9h] [ebp-1C5h]
  struct WSAData v15; // [esp-1B8h] [ebp-1C4h] BYREF
  int *v16; // [esp-10h] [ebp-1Ch]
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // [esp-Ch] [ebp-18h]
  void *v18; // [esp-8h] [ebp-14h]
  unsigned int v19; // [esp-4h] [ebp-10h]
  _DWORD v20[2]; // [esp+0h] [ebp-Ch] BYREF
  int v21; // [esp+8h] [ebp-4h] BYREF
  void *retaddr; // [esp+Ch] [ebp+0h]

  v20[0] = a1;
  v20[1] = retaddr;
  v19 = 0xFFFFFFFF;
  v18 = &loc_10013310;
  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v16 = &v21;
  sub_1000AA50();
  sub_10010120();
  CurrentThread = GetCurrentThread();
  sub_10010600(CurrentThread);
  HookFunction((int)&dword_1001804C, sub_1000B080);
  HookFunction((int)&dword_1001805C, sub_1000ACB0);
  HookFunction((int)&dword_10018044, sub_1000B9C0);
  HookFunction((int)&unk_10018024, sub_1000BA00);
  HookFunction((int)&dword_10018040, sub_1000BA10);
  HookFunction((int)&dword_10018034, sub_1000BA70);
  HookFunction((int)&unk_1001802C, sub_1000BB10);
  HookFunction((int)&dword_10018030, sub_1000B180);
  HookFunction((int)&dword_10018038, sub_1000BB20);
  HookFunction((int)&unk_1001803C, sub_1000BB30);
  HookFunction((int)&dword_10018028, sub_1000BB40);
  sub_1000AA50();
  v11[0] = 0;
  v12 = 0;
  v13 = 0;
  sub_10005BB0(v11, "echoespatch/local/xlat.dat", 0x1Au);
  v19 = 0;
  v3 = sub_1000D600(v11);
  v19 = 0xFFFFFFFF;
  v14 = v3;
  if ( v13 >= 0x10 )
  {
    v4 = (void *)v11[0];
    if ( v13 + 1 >= 0x1000 )
    {
      v4 = *(void **)(v11[0] - 4);
      if ( (unsigned int)(v11[0] - (_DWORD)v4 - 4) > 0x1F )
        invalid_parameter_noinfo_noreturn();
    }
    sub_10011C48(v4);
    v3 = v14;
  }
  v12 = 0;
  v13 = 0xF;
  LOBYTE(v11[0]) = 0;
  if ( v3 )
    HookFunction((int)&dword_10018048, &sub_1000BB80);
  if ( sub_10010180() || (sub_10006DA0(), MEMORY[0xEBEFC4] = 0, WSAStartup(0x202u, &v15)) )
  {
    sub_1000AA50();
  }
  else
  {
    s = socket(2, 2, 0x11);
    if ( s != 0xFFFFFFFF )
    {
      byte_1001897E = 1;
      v6 = 0i64;
      v7 = 0;
      v8 = 0;
      v9 = 0;
      v10 = 0;
      while ( byte_10018058 )
      {
        sub_1000B250((int)&v6, (int)v20, (int)Sleep);
        Sleep(0);
      }
    }
    sub_1000AA50();
    WSACleanup();
  }
  return 0;
}
```
The first thing you may have noticed are the Hooks. we will get to those in a bit, but lets look at the function sub_1000B250 in the while loop first. It's constantly being called so this must be where most of the stuff is happening.
```cpp
char __usercall sub_1000B250@<al>(int a1@<ecx>, int a2@<ebp>, int a4@<esi>)
{
  int v4; // eax
  int v5; // edi
  char v6; // cl
  bool v7; // zf
  int v8; // eax
  int v9; // edi
  int v10; // ecx
  unsigned int v11; // edx
  const wchar_t *v12; // eax
  FILE *v13; // esi
  std::codecvt_base *v14; // esi
  void (__thiscall ***v15)(_DWORD, int); // eax
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // eax
  int v23; // ecx
  int v24; // edx
  SOCKET v26; // [esp+Ch] [ebp-168h]
  int v27; // [esp+20h] [ebp-154h]
  int v29; // [esp+40h] [ebp-134h] BYREF
  int v30; // [esp+44h] [ebp-130h]
  __int128 v31; // [esp+48h] [ebp-12Ch] BYREF
  __int128 v32; // [esp+58h] [ebp-11Ch]
  __int64 v33; // [esp+84h] [ebp-F0h] BYREF
  int *v34; // [esp+8Ch] [ebp-E8h] BYREF
  _DWORD v35[53]; // [esp+90h] [ebp-E4h] BYREF
  int v36; // [esp+164h] [ebp-10h]
  int v37; // [esp+168h] [ebp-Ch]
  int v38; // [esp+16Ch] [ebp-8h]
  int v39; // [esp+170h] [ebp-4h] BYREF
  int retaddr; // [esp+174h] [ebp+0h]

  v37 = a2;
  v38 = retaddr;
  v36 = 0xFFFFFFFF;
  v35[0x34] = &loc_10013277;
  v35[0x33] = NtCurrentTeb()->NtTib.ExceptionList;
  v35[0x32] = &v39;
  if ( !byte_100189E1 )
  {
    byte_100189E1 = 1;
    sub_1000AA50();
  }
  byte_1001897C = 0;
  v33 = MEMORY[0xEA88F8];
  LOBYTE(v4) = MEMORY[0xEA88FC] | MEMORY[0xEA88F8];
  if ( MEMORY[0xEA88F8] )
  {
    if ( !byte_100189E5 )
    {
      byte_100189E5 = 1;
      LOBYTE(v4) = sub_1000AA50();
    }
    if ( s != 0xFFFFFFFF && byte_1001897D )
    {
      if ( !byte_100189D9 )
      {
        byte_100189D9 = 1;
        LOBYTE(v4) = sub_1000AA50();
      }
      if ( !byte_100189E0 )
      {
        byte_100189E0 = 1;
        LOBYTE(v4) = sub_1000AA50();
      }
      if ( dword_10018800 )
      {
        LOBYTE(v4) = v33;
        if ( *(_DWORD *)(dword_10018800 + 0x90) == (_DWORD)v33 )
        {
          LOBYTE(v4) = BYTE4(v33);
          if ( *(_DWORD *)(dword_10018800 + 0x94) == HIDWORD(v33) )
          {
            v5 = *(_DWORD *)(dword_10018800 + 4);
            if ( v5 )
            {
              if ( *(_DWORD *)v5 == 0xBC5FB8 )
              {
                if ( !byte_100189E4 )
                {
                  byte_100189E4 = 1;
                  sub_1000AA50();
                }
                v6 = *(_BYTE *)(v5 + 0xA0);
                v4 = v5 + 0xA1;
                v34 = (int *)(v5 + 0xA1);
                if ( v6 )
                {
                  if ( v6 != (char)0xFF )
                  {
LABEL_24:
                    if ( !byte_100189E3 )
                    {
                      byte_100189E3 = 1;
                      sub_1000AA50();
                    }
                    LOBYTE(v4) = dword_10018800;
                    if ( dword_10018800 && *(_DWORD *)(dword_10018800 + 0x60) )
                    {
                      if ( !byte_100189D8 )
                      {
                        byte_100189D8 = 1;
                        sub_1000AA50();
                      }
                      byte_1001897C = 1;
                      *(_QWORD *)&v31 = v33;
                      LODWORD(v32) = 0;
                      *((_QWORD *)&v31 + 1) = *(_QWORD *)(v5 + 0xA8);
                      LODWORD(v32) = *(_DWORD *)(v5 + 0xB0);
                      BYTE4(v32) = *(_BYTE *)(v5 + 0xA0);
                      BYTE5(v32) = *(_BYTE *)v34;
                      v8 = Mtx_lock((_Mtx_t)&unk_100188EC);
                      if ( v8 )
                        std::_Throw_C_error(v8);
                      BYTE6(v32) = dword_10018980;
                      BYTE7(v32) = dword_10018978;
                      Mtx_unlock((_Mtx_t)&unk_100188EC);
                      if ( WORD2(v32) != *(_WORD *)(a1 + 0x14)
                        || fabs(*((float *)&v31 + 2) - *(float *)(a1 + 8)) > 0.0099999998
                        || fabs(*((float *)&v31 + 3) - *(float *)(a1 + 0xC)) > 0.0099999998
                        || fabs(*(float *)&v32 - *(float *)(a1 + 0x10)) > 0.0099999998
                        || BYTE6(v32) != *(_BYTE *)(a1 + 0x16)
                        || (LOBYTE(v4) = BYTE7(v32), BYTE7(v32) != *(_BYTE *)(a1 + 0x17)) )
                      {
                        if ( !byte_100189E2 )
                        {
                          byte_100189E2 = 1;
                          sub_1000AA50();
                        }
                        *(_OWORD *)a1 = v31;
                        v26 = s;
                        *(_OWORD *)(a1 + 0x10) = v32;
                        v9 = sendto(v26, (const char *)&v31, 0x20, 0, &to, 0x10);
                        if ( dword_10018A00 > *(_DWORD *)(*((_DWORD *)NtCurrentTeb()->ThreadLocalStoragePointer
                                                          + TlsIndex)
                                                        + 4) )
                        {
                          sub_100120C6(&dword_10018A00);
                          if ( dword_10018A00 == 0xFFFFFFFF )
                          {
                            v36 = 0;
                            LOBYTE(v34) = 0;
                            sub_1000CF80(FileName, (int)v34, "position.log", 0xC);
                            sub_10011F7E(sub_10013A00);
                            v36 = 0xFFFFFFFF;
                            sub_1001207C(&dword_10018A00);
                          }
                        }
                        LOBYTE(v4) = sub_1000A800(FileName);
                        if ( (_BYTE)v4 )
                        {
                          v10 = dword_100189DC;
                          v11 = (int)((unsigned __int64)(0x66666667i64 * dword_100189DC++) >> 0x20) >> 2;
                          v4 = 0xA * (v11 + (v11 >> 0x1F));
                          if ( v10 == v4 )
                          {
                            memset(v35, 0, 0xB0u);
                            sub_1000C2C0(v35, v27);
                            v36 = 1;
                            v12 = FileName;
                            if ( (unsigned int)dword_100189FC >= 8 )
                              v12 = *(const wchar_t **)FileName;
                            if ( v35[0x14] || (v13 = std::_Fiopen(v12, 0xA, 0x40)) == 0 )
                            {
                              std::ios::setstate((char *)v35 + *(_DWORD *)(v35[0] + 4), 2, 0);
                            }
                            else
                            {
                              LOBYTE(v35[0x13]) = 1;
                              BYTE1(v35[0x10]) = 0;
                              std::streambuf::_Init(&v35[1]);
                              v33 = 0i64;
                              v34 = 0;
                              get_stream_buffer_pointers(v13, (char ***)&v33, (char ***)&v33 + 1, &v34);
                              std::streambuf::_Init(&v35[1], v33, HIDWORD(v33), v34, v33, HIDWORD(v33), v34);
                              v35[0x11] = dword_100187F4;
                              v35[0x12] = dword_100187F8;
                              v35[0x14] = v13;
                              v35[0xF] = 0;
                              std::streambuf::getloc(&v35[1], &v29);
                              LOBYTE(v36) = 2;
                              v14 = (std::codecvt_base *)sub_10007FD0(a4);
                              if ( std::codecvt_base::always_noconv(v14) )
                              {
                                v35[0xF] = 0;
                              }
                              else
                              {
                                v35[0xF] = v14;
                                std::streambuf::_Init(&v35[1]);
                              }
                              LOBYTE(v36) = 1;
                              if ( v30 )
                              {
                                v15 = (void (__thiscall ***)(_DWORD, int))(*(int (__thiscall **)(int))(*(_DWORD *)v30 + 8))(v30);
                                if ( v15 )
                                  (**v15)(v15, 1);
                              }
                              std::ios::clear((char *)v35 + *(_DWORD *)(v35[0] + 4));
                            }
                            if ( v35[0x14] )
                            {
                              v16 = sub_1000C8D0();
                              std::ostream::operator<<(v16, v9);
                              v17 = sub_1000C8D0();
                              std::ostream::operator<<(v17, BYTE4(v32));
                              v18 = sub_1000C8D0();
                              std::ostream::operator<<(v18, BYTE5(v32));
                              v19 = sub_1000C8D0();
                              std::ostream::operator<<(v19, DWORD2(v31));
                              v20 = sub_1000C8D0();
                              std::ostream::operator<<(v20, HIDWORD(v31));
                              v21 = sub_1000C8D0();
                              std::ostream::operator<<(v21, v32);
                              v22 = sub_1000C8D0();
                              std::ostream::operator<<(v22, sub_1000CAF0);
                            }
                            if ( !sub_10007D00((int)&v35[1]) )
                              std::ios::setstate((char *)v35 + *(_DWORD *)(v35[0] + 4), 2, 0);
                            *(_DWORD *)((char *)v35 + *(_DWORD *)(v35[0] + 4)) = &std::ofstream::`vftable';
                            *(_DWORD *)((char *)&v35[0xFFFFFFFF] + *(_DWORD *)(v35[0] + 4)) = *(_DWORD *)(v35[0] + 4)
                                                                                            - 0x68;
                            v36 = 3;
                            v35[1] = &std::filebuf::`vftable';
                            if ( v35[0x14] && *(_DWORD **)v35[4] == &v35[0x10] )
                            {
                              v23 = v35[0x15];
                              v24 = v35[0x16] - v35[0x15];
                              *(_DWORD *)v35[4] = v35[0x15];
                              *(_DWORD *)v35[8] = v23;
                              *(_DWORD *)v35[0xC] = v24;
                            }
                            if ( LOBYTE(v35[0x13]) )
                              sub_10007D00((int)&v35[1]);
                            std::streambuf::~streambuf<char,std::char_traits<char>>(&v35[1]);
                            std::ostream::~ostream<char,std::char_traits<char>>(&v35[2]);
                            LOBYTE(v4) = std::ios::~ios<char,std::char_traits<char>>();
                          }
                        }
                      }
                    }
                    return v4;
                  }
                  v7 = *(_BYTE *)v4 == 0xFF;
                }
                else
                {
                  v7 = *(_BYTE *)v4 == 0;
                }
                if ( v7 )
                  return v4;
                goto LABEL_24;
              }
            }
          }
        }
      }
    }
  }
  return v4;
}
```
At first, nothing really catches the eye. Lets take a look at some strings to try and gain some context clues.
```cpp
00                                      align 4
.rdata:100148EC 57 72 69 74 65 50 6F 73+aWritepositionS db 'WritePosition started',0
.rdata:100148EC 69 74 69 6F 6E 20 73 74+                                        ; DATA XREF: sub_1000B250+4C↑o
.rdata:10014902 00 00                                   align 4
.rdata:10014904 57 72 69 74 65 50 6F 73+aWritepositionP db 'WritePosition - PlayerID ready',0
.rdata:10014904 69 74 69 6F 6E 20 2D 20+                                        ; DATA XREF: sub_1000B250+8E↑o
.rdata:10014923 00                                      align 4
.rdata:10014924 57 72 69 74 65 50 6F 73+aWritepositionN db 'WritePosition - networking initialized',0
.rdata:10014924 69 74 69 6F 6E 20 2D 20+                                        ; DATA XREF: sub_1000B250+C2↑o
.rdata:1001494B 00                                      align 4
.rdata:1001494C 57 72 69 74 65 50 6F 73+aWritepositionW db 'WritePosition - WorldEntityFactory ready',0
.rdata:1001494C 69 74 69 6F 6E 20 2D 20+                                        ; DATA XREF: sub_1000B250+DC↑o
.rdata:10014975 00 00 00                                align 4
.rdata:10014978 57 72 69 74 65 50 6F 73+aWritepositionP_0 db 'WritePosition - player physics ready',0
.rdata:10014978 69 74 69 6F 6E 20 2D 20+                                        ; DATA XREF: sub_1000B250+13F↑o
.rdata:1001499D 00 00 00                                align 10h
.rdata:100149A0 57 72 69 74 65 50 6F 73+aWritepositionP_1 db 'WritePosition - player in world',0
.rdata:100149A0 69 74 69 6F 6E 20 2D 20+                                        ; DATA XREF: sub_1000B250+180↑o
.rdata:100149C0 57 72 69 74 65 50 6F 73+aWritepositionP_2 db 'WritePosition - player properties ready',0
.rdata:100149C0 69 74 69 6F 6E 20 2D 20+                                        ; DATA XREF: sub_1000B250+1B1↑o
.rdata:100149E8 57 72 69 74 65 50 6F 73+aWritepositionS_0 db 'WritePosition - sent first position',0
.rdata:100149E8 69 74 69 6F 6E 20 2D 20+ 
```

Well would you look at that, player data! And it's being used in the function we just looked at. Lets go back to our function and try to understand whats going on. Also There are multiple locations/bytes that are being set only once, for example:
```cpp
if ( !byte_100189E5 )
    {
      byte_100189E5 = 1;
      LOBYTE(v4) = sub_1000AA50();
    }
```
following sub_1000AA50 we will see that its a function used for logging text/data. this is probably where the WritePosition strings are being used so we can ignore these locations. Here is the functions cleaned up to make it easier to view.
```cpp
      v33 = MEMORY[0xEA88F8];
  LOBYTE(v4) = MEMORY[0xEA88FC] | MEMORY[0xEA88F8];
  if ( MEMORY[0xEA88F8] )
  {
    if ( s != 0xFFFFFFFF && byte_1001897D )
    {
      if ( dword_10018800 )
      {
        LOBYTE(v4) = v33;
        if ( *(_DWORD *)(dword_10018800 + 0x90) == (_DWORD)v33 )
        {
          LOBYTE(v4) = BYTE4(v33);
          if ( *(_DWORD *)(dword_10018800 + 0x94) == HIDWORD(v33) )
          {
            v5 = *(_DWORD *)(dword_10018800 + 4);
            if ( v5 )
            {
```
wait, what is MEMORY[0xEA88F8] and MEMORY[0xEA88FC]?  following the xref we are taken to the functions sub_1000BB40
```cpp
int __cdecl sub_1000BB40(int a1)
{
  if ( *(_DWORD *)(a1 + 0x90) == MEMORY[0xEA88F8] && *(_DWORD *)(a1 + 0x94) == MEMORY[0xEA88FC] )
    dword_10018800 = a1;
  return dword_10018028();
}
```
referencing this function will take us back to our main function, the one with the hooks. So we are hooking one of the games functions and whenver its called, we are verifying that its correct using offsets 0x90 and 0x94. but what the hell is it verifying and what/where is MEMORY[0xEA88F8] ? Lets bust out our debugger. I will be using cheat engine since its extremely easy to use. First things to do is to try and see where MEMORY[0xEA88F8] is located, we can do this by simply taking a look at the memory at that address.

```cpp
pl.dll.text+AB43 - 8B 4D 08              - mov ecx,[ebp+08]
pl.dll.text+AB46 - 8B 81 90000000        - mov eax,[ecx+00000090]
pl.dll.text+AB4C - 3B 05 F888EA00        - cmp eax,[lotroclient.exe+AA88F8] { (-675801332) }
pl.dll.text+AB52 - 75 14                 - jne pl.dll.text+AB68
pl.dll.text+AB54 - 8B 81 94000000        - mov eax,[ecx+00000094]
pl.dll.text+AB5A - 3B 05 FC88EA00        - cmp eax,[lotroclient.exe+AA88FC] { (33685504) }
pl.dll.text+AB60 - 75 06                 - jne pl.dll.text+AB68
pl.dll.text+AB62 - 89 0D 0088EF53        - mov [pl.dll+18800],ecx { (26CFB29C) }
pl.dll.text+AB68 - A1 2880EF53           - mov eax,[pl.dll.data+28] { (02F703A8) }
pl.dll.text+AB6D - 89 4D 08              - mov [ebp+08],ecx
pl.dll.text+AB70 - 5D                    - pop ebp
pl.dll.text+AB71 - FF E0                 - jmp eax
```
And it's located at lotroclient.exe+AA88F8 ! the base address for lotroclient.exe just happens to be 0x40000. 0xEA88F8 - 0x40000 = 0xAA88F8. So lets go find out where who is writing to this address.

![alt text](https://i.imgur.com/SIKAWS0.png)

The address we are looking for is 0059DFD8. lets add it to our list and browse the region, you should be taken to the middle of the function and now you can simply copy & paste the bytes of this function to search for them in IDA. The signature for the function that is setting these two MEMORY's is 
```cpp
8B 44 24 04 8B 4C 24 08 A3 F8 88 EA 00 89 0D FC 88 EA 00 C3
```
pop it into IDA and we are met with this function
```cpp
int __cdecl sub_19DFD0(int a1, int a2)
{
  int result; // eax

  result = a1;
  MEMORY[0xEA88F8] = a1;
  MEMORY[0xEA88FC] = a2;
  return result;
}
```
simple enough, lets go up the chain to our first reference.

```cpp
int __stdcall sub_24EC70(__int64 a1, int a2)
{
  int v3[2]; // [esp+Ch] [ebp-8h] BYREF

  v3[0] = 3;
  v3[1] = 0;
  sub_5A03D0(v3, "CObjectMaint::RecvNotice_SetPlayerIDplayer: 0x%016I64X\n", a1);
  sub_19DFD0(a1, SHIDWORD(a1));
  sub_BA0E0(a2);
  return sub_24EA50(dword_EC1390, dword_EC1394);
}
```
Perfect! now we know how to get the players ID! So what exactly is going? The game calls function sub_24EC70 with the first parameter being the players ID. The pl.dll has the function sub_19DFD0 hooked so whenever the game calls it, the dll can intercept the id of the player and then the devs can do whatever they want with it all while being a part of the game still. If we look back at function sub_1000B250 we can see a pointer labeled dword_10018800 being used with 0x90 and 0x94. lets see if we can find the ID's in cheat engine.

![alt text](https://i.imgur.com/y9fjqeU.png)

looks promising! Hitting the ID with a HIDWORD does infact match the ID that is at 0x94. From here we can easily traverse through the games code to find other import things likes position, angles, entity list and so on. So how do we get the players position ?
