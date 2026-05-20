#pragma once

void ClearBuffer(void);
void InitNew(void);
void PrintLine(int n, char c);
int SafeNumberInput(int* target);
double SafeDoubleInput(double* target);
int Max(int x, int y);
int Min(int x, int y);
void SaveConfig(void);
int InputIntWithLimit(int* target, int max, int min);
int TimeCheck(int year, int month, int day, int hour, int minute);
int VerifyCode(void);
void HiddenPassword(char password[]);
void Gotoxy(HANDLE hout, int x, int y);
void PrintToxy(char* text, int x, int y);
double InputDoubleWithLimit(double* target, double max, double min);