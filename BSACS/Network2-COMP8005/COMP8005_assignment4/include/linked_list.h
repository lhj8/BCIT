#ifndef PROJECT_LINKEDLIST_H
#define PROJECT_LINKEDLIST_H
#include "common.h"

typedef struct ListNodeType {
    int pid;
    int ppid;
    char comm[256];
    char cmdline[512];
    struct ListNodeType *pLink;
} ListNode;

typedef struct FDListNodeType {
    int fd;
    char fd_info[128];
    struct FDListNodeType *pLinkFD;
} FDListNode;


typedef struct LinkedListType {
    int currentElementCount;
    ListNode headerNode;
} LinkedList;


typedef struct FDLinkedListType {
    int currentElementCount;
    FDListNode headerNode;
} FDLinkedList;

LinkedList *createLinkedList(void);
FDLinkedList *createFDLinkedList(void);
int addLLElement(LinkedList *pList, int position, ListNode element);
int addLLFDElement(FDLinkedList *pList, int position, FDListNode element);
int removeLLElement(LinkedList *pList, int position);
int removeLLFDElement(FDLinkedList *pList, int position);
ListNode *getLLElement(LinkedList *pList, int position);
FDListNode *getLLFDElement(FDLinkedList *pList, int position);

void clearLinkedList(LinkedList *pList);
void clearFDLinkedList(FDLinkedList *pList);
int getLinkedListLength(LinkedList *pList);
int getFDLinkedListLength(FDLinkedList *pList);
void deleteLinkedList(LinkedList *pList);
void deleteFDLinkedList(FDLinkedList *pList);
int isEmpty(LinkedList *pList);

void save_processes(LinkedList* proc_list);
void save_pid_to_linked_list(LinkedList *proc_list, char *pid_str, int i);
void process_directory_processing(LinkedList *proc_list);
void save_ppid_to_linked_list(char *path, LinkedList *proc_list, int index);
void save_comm_to_linked_list(char *path, LinkedList *proc_list, int index);
void save_cmdline_to_linked_list(char *path, LinkedList *proc_list, int index);
void save_fd_to_linked_list(char *path, int pid);
void find_fd_port_number(FDListNode* fd_node, int pid);



#define FALSE 0
#define TRUE 1

#endif // PROJECT_LINKEDLIST_H
