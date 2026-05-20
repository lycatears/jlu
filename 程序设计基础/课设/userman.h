#pragma once

#ifndef USERMAN_H_INCLUDED
#define USERMAN_H_INCLUDED

#endif 
struct customer
{//客户结构体
    int			id;				//编号
    char		name[20];		//名称
    double		cost;			//累计消费
    int			vip;			//会员等级
    char		password[16];	//密码
};

struct userinfo
{
    //用户信息链表节点
    struct customer data;
    struct userinfo* next;
};

struct suggest//建议
{
    char propose[100];//建议内容
    int num;//建议编号
};

struct suggestlian//建议节点
{
    struct suggest cell;
    struct suggestlian* next;
};

void AdminMain(void);
int ManagementMenu(void);
void FindUser(struct userinfo* head);
struct userinfo* CreateChain(void);
struct userinfo* AddNewUser(struct userinfo* head);
void WriteToFile(struct userinfo* head);
struct userinfo* DeleteUserById(struct userinfo* head);
struct userinfo* ChangeUser(struct userinfo* head);
struct suggestlian* ReadSuggestions(void);
void Suggest(void);
struct suggestlian* AddSuggest(struct suggestlian* head2);
void WriteSuggestToFile(struct suggestlian* head2);
void ShowSuggestions(struct suggestlian* head2);
void DeleteAllSuggestion(void);
void VipSystem(struct userinfo* head);
void ShowVip(void);
void ChangeVip(void);
void SearchUserByVip(struct userinfo* head);
void Promotion();
void UserManageMain(void);
struct userinfo* ReadAllUser(struct userinfo* head);
int UserCount(struct userinfo* head);
void ShowStatus(void);
void ReleaseList(struct userinfo* head);
void SearchUserByName(struct userinfo* head);
int MaxUserId(struct userinfo* head);
void SearchForUserCost(struct userinfo* head);
void ReleaseSuggestions(struct suggestlian* head);
int IsSameNode(char input[], char asseredname[]);
struct userinfo* FindUserPos(struct userinfo* head, char username[]);
struct userinfo* FindUserPosById(struct userinfo* head, int target_id);
void NewUser(void);
void ShowPersonalInfo(void);
void ChangePersonalInfo(void);
void UserMain(void);
void Setting(void);
void BestGood(void);
void BestSale(void);
void BackupAll(void);
void RecoverAll(void);
void BackupMain(void);
void WorstSale(void);
void ShowVipGift(void);
void ChangeVipGift(void);