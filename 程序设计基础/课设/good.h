#pragma once

struct item
{
    int     id;         //编号
    int     volume;     //体积
    char    brand[100]; //品牌
    int     number;     //包装内每箱数量
    double  in_price;   //进货价格
    double  out_price;  //售卖价格
    char    zhizaoshang[100];   //制造商
    char    gonghuoshang[100];  //供货商
    int     storage;            //库存
    int     duration;           //保质期
};

typedef struct ItemNode
{
    struct item thing;
    struct ItemNode* next1;
}ItemNode;

struct buyitem
{
    int goods_id;
    int goods_volume;
    char goods_brand[100];
    int goods_number; // 一箱的瓶数
    double goods_price;
    int num; // 购买的数量
};
typedef struct cart
{
    struct buyitem data;
    struct cart* next;
}List;

int ItemMenu(void);
ItemNode* CreateLink(ItemNode* goods_head);
ItemNode* AddItem(ItemNode* goods_head);
ItemNode* ChangeItem(ItemNode* goods_head);
ItemNode* DeleteItem(ItemNode* goods_head);
int FindItem(ItemNode* goods_head);
void StoreItem(ItemNode* goods_head);
void DisplayItem(ItemNode* goods_head);
void FindItem2(ItemNode* goods_head);
int ItemMain(void);
int ItemCount(ItemNode* head);
int MaxItemId(ItemNode* head);
void Buy(void);
List* AddToCart(ItemNode* allgoods, List* goods_head);
int BuyMenu(void);
List* ChangeCart(List* goods_head, ItemNode* head);
void FindCart(List* goods_head);
void ShowCart(List* goods_head);
void SearchCart(ItemNode* goods_head);
List* DeleteCart(List* goods_head);
void DisplayItemForUser(ItemNode* goods_head);
ItemNode* FindItemPos(ItemNode* head, int item_id);
void Settle(ItemNode* goods_head, List* cart_head, struct deal* record_head, struct userinfo* user_head);
void UpdateVip(struct userinfo* info);
void CheckDuration(void);
void ChangeItemInfo(ItemNode* goods_head);
void FindItemForUser(ItemNode* goods_head);
void LossProcess(ItemNode* goods_head);
void SpiltItem(ItemNode* goods_head);
void CreateSingleItem(ItemNode* head, int init_storage, ItemNode* original_info);
void SendGift(ItemNode* goods_head, struct userinfo* user);
void CreateSale(ItemNode* head, ItemNode* original_info, int sale_count, double discount);