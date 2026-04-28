#include <stdio.h>
#include <stdlib.h>



typedef struct Node2{
    int key;
    int data;

    struct Node2 *next;
    struct Node2 *prev;

} t_list2;

t_list2* xmalloc2(size_t size){
    t_list2* cur = malloc(size);
    if (cur == NULL){
        exit(123);
    }
    return cur;
}
/*Вывод списка*/
void printList2(t_list2 *head){
    printf("HEAD -> \n");
    while (!(head == NULL)){
        if (head->prev == NULL){
            /*Если это первый узел*/
            printf("NULL <-> [%d %d] <-> ", head->key, head->data);
        }
        else{
            printf("[%d %d] <-> ", head->key, head->data);
        }
        head = head->next;
    }
    printf("NULL");
}

/*Удаление хвоста*/
t_list2* del_tail2(t_list2 *head){
    t_list2 *tmp, *cur = head;

    /*Крайние случаи*/
    if (head == NULL)
        return NULL;
    
    if (head->next == NULL){
        free(head);
        return NULL;
    }

    /*Основной случай, двигаем до предыдущего*/
    while (!(cur->next->next == NULL)){
        cur = cur->next;
    }

    tmp = cur->next;
    cur->next = NULL;
    free(tmp);
    return head;
}

/*Удаление по узлу*/
t_list2* del_ptr2(t_list2 *head, t_list2 *ptr){
    if (ptr->prev == NULL){
        if (!(ptr->next == NULL))
            /*Переназначаем следующий, если он существует*/
            ptr->next->prev = NULL;
    }
    else{
        /*Переназначаем у прошлого узла следующий элемент*/
        ptr->prev->next = ptr->next;
        if(!(ptr->next == NULL))
            /*Переназначаем следующий, если он существует*/
            ptr->next->prev = ptr->prev;
    }

    free(ptr);
    return head;
}

/*Удаление по ключу*/
t_list2* del_key2(t_list2 *head, int key){
    t_list2 *cur = head, *tmp;
    /*Крайние случаи*/
    if (head == NULL)
        return NULL;

    if (head->next == NULL && head->key == key){
        free(head);
        return NULL;
    } else if(head->next == NULL){
        return head;
    }
    /*Основной, двигаем до предыдущего до key*/
    while(!(cur ->next == NULL) && !(cur->next->key == key)){
        cur = cur->next;
    }
    if (cur->next->key == key){
        if (!(cur->next->next == NULL)){
            /*Если есть, изменяем свзязь следующего элемента*/
            cur->next->next->prev = cur;
        }
        tmp = cur->next;
        cur->next = cur->next->next;
        free(tmp);
    }
    return head;
}
/*Удаление головы*/
t_list2* del_head2(t_list2 *head){
    t_list2* tmp = head;
    if (head == NULL){
        return NULL;
    }
    if(!(head->next ==NULL)){
        head->next->prev = NULL;
    }
    head = head->next;
    free(tmp);
    return head;
    
}
/*Создание нового узла*/
t_list2* create_new_node2(int key, int data){
    t_list2 *new_node2 = xmalloc2(sizeof(t_list2));
    new_node2->key = key;
    new_node2->data = data;

    new_node2->prev = NULL;
    new_node2->next = NULL;

    return new_node2;
}

/*Добавление в конец*/
t_list2* add_in_tail2(t_list2* head, int key, int data){
    t_list2* new_node2 = create_new_node2(key, data);
    t_list2 *cur = head;

    if (cur == NULL){
        free(head);
        return new_node2;
    }
    while(!(cur->next == NULL)){
        cur = cur->next;
    }
    cur->next = new_node2;
    new_node2->prev = cur;
    return head;
}
t_list2 *add_akey2(t_list2 *head, int key, int data){
    t_list2 *new_node2 = create_new_node2(key + 1, data);
    t_list2 *cur = head;

    while(!(cur == NULL) && !(cur->key == key)){
        cur = cur -> next;
    }
    
    if (cur->key == key){
        new_node2->prev = cur;
        new_node2->next = cur->next;
        /*Если следующий не NULL*/
        if (!(cur->next == NULL))
            cur->next->prev = new_node2;

        cur->next = new_node2;
    } else{
        free(new_node2);
    }
    return head;
}

/*Добавление до какого-то ключа*/
t_list2 *add_bkey2(t_list2 *head, int key, int data){
    t_list2 *new_node2 = create_new_node2(key, data);
    t_list2 *cur = head;

    if (cur == NULL)
        cur = new_node2;
        return cur;

    while (!(cur->next == NULL) && !(cur->next->key == key)){
        cur = cur -> next;
    }
    if (cur->next->key == key){
        new_node2->prev = cur;
        new_node2->next = cur->next;

        if (!(new_node2->next == NULL)){
            new_node2->next->prev = new_node2;
        }
        cur -> next = new_node2; 
    } else{
        free(new_node2);
    }
    return head;

}

/*Поиск узла по ключу*/
t_list2* search_by_key2(t_list2* head, int key){
    while(head != NULL){
        if (head->key == key){
            return head;
        }
        head = head->next;
    }
    return NULL;
}