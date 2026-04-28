#include <stdio.h>
#include "t_list1.h"
#include "t_list2.h"



int main(){
    int i;
    t_list1 *head = NULL, *cur;
    t_list2 *head2 = NULL, *cur2;
    printf("Односвязный список\n\n");

    printf("\nСоздание списка\n");
    for(i = 0; i < 5; ++i){
        head = add_in_tail(head, i, i * 10);
    }
    printList1(head);
    
    printf("\nДобавление после 3\n");
    head = add_akey1(head, 3, 90);
    printList1(head);
    
    printf("\nДобавление до 2\n");
    head = add_bkey1(head, 2, 90);  
    printList1(head);
    
    printf("\nУдаление конца\n");
    head = del_tail1(head);
    printList1(head);
    
    printf("\nУдаление головы\n");
    head = del_head1(head);
    printList1(head);
    
    printf("\nУдаление по key: 4\n");
    head = del_key1(head, 4);
    printList1(head);

    printf("\nПоиск по ключу (2)\n");
    cur = search_by_key1(head, 2);
    if (cur != NULL){
        printf("Результат: %d\n", cur->data);
    }
    

    printf("\n\n\nДвусвязный список\n\n");

    printf("\nСоздание списка\n");
    for(i = 0; i < 5; ++i){
        head2 = add_in_tail2(head2, i, i * 10);
    }
    printList2(head2);
    
    printf("\nДобавление после 3\n");
    head2 = add_akey2(head2, 3, 90);
    printList2(head2);
    
    printf("\nДобавление до 2\n");
    head2 = add_bkey2(head2, 2, 90);  
    printList2(head2);
    
    printf("\nУдаление конца\n");
    head2 = del_tail2(head2);
    printList2(head2);
    
    printf("\nУдаление головы\n");
    head2 = del_head2(head2);
    printList2(head2);
    
    printf("\nУдаление по key: 4\n");
    head2 = del_key2(head2, 4);
    printList2(head2);

    printf("\nПоиск по ключу (2)\n");
    cur2 = search_by_key2(head2, 2);
    if (cur2 != NULL){
        printf("Результат: %d\n", cur2->data);
    }
    return 0;
}

