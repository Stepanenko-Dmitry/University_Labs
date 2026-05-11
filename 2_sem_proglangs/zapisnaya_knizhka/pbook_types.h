#ifndef PBOOK_TYPES_H
#define PBOOK_TYPES_H

typedef struct Data1 {
  char name[25];
  char surname[25];
  char phone[12];
} t_person;

typedef struct Data2 {
  char note[81];
} t_note;

typedef enum Data_type {
  OTHER = 0,
  PERSON = 1,
  NOTE = 2
} t_data;

typedef struct Node {
  int key;
  t_data dt;
  void *data;
  struct Node *prev;
  struct Node *next;
} t_list;

#endif