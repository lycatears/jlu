#ifndef SEVER_TIME_H_INCLUDED
#define SEVER_TIME_H_INCLUDED

time_t GetOriginalTime(void);
struct tm* GetNormalTime(time_t original_time);
void TimeOutput(struct tm* normaltime);
void DateOutput(struct tm* normaltime);
void ShowTime(void);
void ShowDate(void);

#endif // SEVER_TIME_H_INCLUDED
