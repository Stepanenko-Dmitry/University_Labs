#ifndef PBOOK_H
#define PBOOK_H

#include "pbook_types.h"

void prnlistdata(t_list *tmp);
t_list *add_head(t_list *head, int key, t_data dt);
t_list *del_head(t_list *head);
int findk_tmp(t_list *head, const char *tmp);
t_list *findp_tmp(t_list *head, const char *tmp);
t_list *del_key(t_list *head, int key);
t_list *del_ptr(t_list *head, int key);
int save_pbook(const char *fname, t_list *head);
t_list *load_pbook(const char *fname);
void purge_pbook(t_list *head);
t_list *sort_pbook(t_list *head);

#endif