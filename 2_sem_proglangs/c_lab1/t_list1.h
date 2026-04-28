#include <stdio.h>
#include <stdlib.h>

void* xmalloc(size_t);

typedef struct Node1{
    int key;
    int data;
    struct Node1 *next;
} t_list1;

void* xmalloc(size_t size){
    void *cur = malloc(size);
    if (cur == NULL){
        exit(123);
    }
    return cur;
}

/* Вывод списка*/
void printList1(t_list1 *head){
    printf("HEAD -> ");

    while (head != NULL){
        printf("[%d %d] -> ", head->key, head->data);
        head = head->next;
        }
    printf("NULL");
    }


/* Удаление головы, возвращает новую голову*/
t_list1* del_head1(t_list1 *head){
    t_list1 *tmp;
    if (head == NULL)
        return NULL;
    tmp = head->next;
    free(head);
    return tmp;
}

/* Удаление хвоста*/
t_list1* del_tail1(t_list1 *head){
    t_list1 *end, *cur = head;
    
    /*Если список состоит из одного элемента или голова пустая*/
    if (cur == NULL || cur->next == NULL){
        free(head);
        return NULL;
    }
    
    while (cur->next->next != NULL){
        cur = cur->next;
    }
    end = cur->next;
    cur->next = NULL;
    free(end);
    return head;
}

/*Удаление по ключу*/
t_list1* del_key1(t_list1 *head, int key){
    t_list1 *tmp, *cur = head;  
    
    /*Если удаляем голову*/
    if (cur == NULL){
        return NULL;
    }
    
    if (cur->key == key){
        head = del_head1(head);
        return head;
    }
    
    while (cur->next != NULL && cur->next->key != key){
        cur = cur->next;
    }
    
    if (cur->next != NULL){
        tmp = cur->next;
        cur->next = cur->next->next;
        free(tmp);
    }
    return head; 
}

/*Удаление по узлу*/
t_list1* del_ptr1(t_list1 *head, t_list1 *ptr){
    t_list1 *cur = head;
    
    if (head == ptr){
        head = del_head1(head);
        return head;
    }
    
    /*Находим элемент до удаляемого*/
    while (cur != NULL && cur->next != ptr){
        cur = cur->next;
    }
    
    /*Если узел найден*/
    if (cur != NULL){
        cur->next = ptr->next;
        free(ptr);
    }
    return head;
}

t_list1 *create_new_node1(int key, int data){
    t_list1 *new_node = xmalloc(sizeof(t_list1));
    new_node->key = key;
    new_node->data = data;
    new_node->next = NULL;
    return new_node;  
}

/*Добавление после узла с каким-то ключом*/
t_list1* add_akey1(t_list1 *head, int key, int data){
    t_list1 *new_node = create_new_node1(key + 1, data), *cur = head;
    
    while (cur != NULL && cur->key != key){
        cur = cur->next;
    }
    
    if (cur != NULL){
        new_node->next = cur->next;
        cur->next = new_node;
    } else {
        free(new_node);  /*Если не был найден ключ удаляем новый узел*/
    }
    return head;
}

/*Добавление узла до*/
t_list1 *add_bkey1(t_list1 *head, int key, int data){
    t_list1 *new_node = create_new_node1(key - 1, data), *cur = head;
    
    if(cur == NULL){
        cur = new_node;
        return new_node;
    }
    
    if (cur->key == key){
        new_node->next = cur;
        return new_node;
    }
    
    while(cur->next != NULL && cur->next->key != key){
        cur = cur->next;
    }
    
    if (cur->next != NULL){
        new_node->next = cur->next;
        cur->next = new_node;
    } else {
        /*Если не был найден ключ удаляем новый узел*/
        free(new_node);  
    }
    
    return head;
}

t_list1* add_in_tail(t_list1* head, int key, int data){
    t_list1 *new_node = create_new_node1(key, data);  
    t_list1 *cur = head;
    
    if(head == NULL){
        return new_node;
    }
    
    while(cur->next != NULL){
        cur = cur->next;
    }
    cur->next = new_node;
    return head;
}

/*Поиск узла по ключу*/
t_list1* search_by_key1(t_list1* head, int key){
    while(head != NULL){
        if (head->key == key){
            return head;
        }
        head = head->next;
    }
    return NULL;
}