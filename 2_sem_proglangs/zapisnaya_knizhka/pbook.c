#include "pbook.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void prnlistdata(t_list *tmp) {
    while (tmp) {
        if (tmp->dt == PERSON) {
            t_person *p = (t_person*)tmp->data;
            printf("PERSON: key=%d, name=%s, surname=%s, phone=%s\n", 
                   tmp->key, p->name, p->surname, p->phone);
        } else if (tmp->dt == NOTE) {
            t_note *n = (t_note*)tmp->data;
            printf("NOTE: key=%d, note=%s\n", tmp->key, n->note);
        } else {
            printf("OTHER: key=%d\n", tmp->key);
        }
        tmp = tmp->next;
    }
}

t_list *add_head(t_list *head, int key, t_data dt) {
    t_list *new_node = (t_list*)malloc(sizeof(t_list));
    if (!new_node) return head;

    new_node->key = key;
    new_node->dt = dt;
    new_node->data = NULL;
    new_node->prev = NULL;
    new_node->next = head;

    if (dt == PERSON) {
        new_node->data = malloc(sizeof(t_person));
        if (new_node->data) memset(new_node->data, 0, sizeof(t_person));
    } else if (dt == NOTE) {
        new_node->data = malloc(sizeof(t_note));
        if (new_node->data) memset(new_node->data, 0, sizeof(t_note));
    }

    if (head) head->prev = new_node;
    return new_node;
}

t_list *del_head(t_list *head) {
    if (!head) return NULL;
    t_list *new_head = head->next;
    if (head->data) free(head->data);
    free(head);
    if (new_head) new_head->prev = NULL;
    return new_head;
}

int findk_tmp(t_list *head, const char *tmp) {
    while (head) {
        if (head->dt == PERSON) {
            t_person *p = (t_person*)head->data;
            if (strstr(p->surname, tmp)) return head->key;
        }
        head = head->next;
    }
    return -1;
}

t_list *findp_tmp(t_list *head, const char *tmp) {
    while (head) {
        if (head->dt == PERSON) {
            t_person *p = (t_person*)head->data;
            if (strstr(p->surname, tmp)) return head;
        }
        head = head->next;
    }
    return NULL;
}

t_list *del_key(t_list *head, int key) {
    t_list *curr = head;
    while (curr) {
        if (curr->key == key) {
            if (curr->prev) curr->prev->next = curr->next;
            else head = curr->next;
            if (curr->next) curr->next->prev = curr->prev;
            if (curr->data) free(curr->data);
            free(curr);
            return head;
        }
        curr = curr->next;
    }
    return head;
}

t_list *del_ptr(t_list *head, int key) {
    return del_key(head, key);
}

int save_pbook(const char *fname, t_list *head) {
    FILE *f = fopen(fname, "wb");
    if (!f) return 1;
    t_list *curr = head;
    while (curr) {
        fwrite(&curr->key, sizeof(int), 1, f);
        fwrite(&curr->dt, sizeof(t_data), 1, f);
        if (curr->dt == PERSON && curr->data) {
            fwrite(curr->data, sizeof(t_person), 1, f);
        } else if (curr->dt == NOTE && curr->data) {
            fwrite(curr->data, sizeof(t_note), 1, f);
        }
        curr = curr->next;
    }
    fclose(f);
    return 0;
}

t_list *load_pbook(const char *fname) {
    FILE *f = fopen(fname, "rb");
    if (!f) return NULL;
    t_list *head = NULL, *tail = NULL;
    int key;
    t_data dt;

    while (fread(&key, sizeof(int), 1, f) && fread(&dt, sizeof(t_data), 1, f)) {
        t_list *new_node = (t_list*)malloc(sizeof(t_list));
        if (!new_node) {
            purge_pbook(head);
            fclose(f);
            return NULL;
        }
        new_node->key = key;
        new_node->dt = dt;
        new_node->data = NULL;
        new_node->prev = tail;
        new_node->next = NULL;

        if (dt == PERSON) {
            new_node->data = malloc(sizeof(t_person));
            if (!new_node->data || !fread(new_node->data, sizeof(t_person), 1, f)) {
                free(new_node->data);
                free(new_node);
                purge_pbook(head);
                fclose(f);
                return NULL;
            }
        } else if (dt == NOTE) {
            new_node->data = malloc(sizeof(t_note));
            if (!new_node->data || !fread(new_node->data, sizeof(t_note), 1, f)) {
                free(new_node->data);
                free(new_node);
                purge_pbook(head);
                fclose(f);
                return NULL;
            }
        }

        if (!head) {
            head = new_node;
        } else {
            tail->next = new_node;
        }
        tail = new_node;
    }
    fclose(f);
    return head;
}

void purge_pbook(t_list *head) {
    while (head) {
        t_list *next = head->next;
        if (head->data) free(head->data);
        free(head);
        head = next;
    }
}

static t_list *merge_sorted(t_list *a, t_list *b) {
    if (!a) return b;
    if (!b) return a;
    t_person *pa = (t_person*)a->data;
    t_person *pb = (t_person*)b->data;
    if (strcmp(pa->surname, pb->surname) <= 0) {
        a->next = merge_sorted(a->next, b);
        if (a->next) a->next->prev = a;
        a->prev = NULL;
        return a;
    } else {
        b->next = merge_sorted(a, b->next);
        if (b->next) b->next->prev = b;
        b->prev = NULL;
        return b;
    }
}

static t_list *split_list(t_list *head) {
    if (!head || !head->next) return NULL;
    t_list *slow = head, *fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    t_list *second = slow->next;
    slow->next = NULL;
    if (second) second->prev = NULL;
    return second;
}

static t_list *merge_sort_persons(t_list *head) {
    if (!head || !head->next) return head;
    t_list *second = split_list(head);
    head = merge_sort_persons(head);
    second = merge_sort_persons(second);
    return merge_sorted(head, second);
}

t_list *sort_pbook(t_list *head) {
    if (!head) return NULL;
    t_list *person_head = NULL, *person_tail = NULL;
    t_list *other_head = NULL, *other_tail = NULL;
    t_list *curr = head;

    while (curr) {
        t_list *next = curr->next;
        curr->prev = NULL;
        curr->next = NULL;
        if (curr->dt == PERSON) {
            if (!person_head) {
                person_head = person_tail = curr;
            } else {
                person_tail->next = curr;
                curr->prev = person_tail;
                person_tail = curr;
            }
        } else {
            if (!other_head) {
                other_head = other_tail = curr;
            } else {
                other_tail->next = curr;
                curr->prev = other_tail;
                other_tail = curr;
            }
        }
        curr = next;
    }

    person_head = merge_sort_persons(person_head);

    if (!person_head) return other_head;
    if (!other_head) return person_head;

    t_list *tmp = person_head;
    while (tmp->next) tmp = tmp->next;
    tmp->next = other_head;
    other_head->prev = tmp;
    return person_head;
}