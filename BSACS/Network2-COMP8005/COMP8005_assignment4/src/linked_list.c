#include "linked_list.h"


LinkedList *createLinkedList(void) {
    LinkedList *pReturn = NULL;

    pReturn = (LinkedList *) malloc(sizeof(LinkedList));

    if (pReturn != NULL) {
        memset(pReturn, 0, sizeof(LinkedList));
    } else {
        printf("ERROR: Memory allocation failed.\n");
        return NULL;
    }

    return pReturn;
}


FDLinkedList *createFDLinkedList(void) {
    FDLinkedList *pReturn = NULL;

    pReturn = (FDLinkedList *) malloc(sizeof(FDLinkedList));

    if (pReturn != NULL) {
        memset(pReturn, 0, sizeof(FDLinkedList));
    } else {
        printf("ERROR: Memory allocation failed.\n");
        return NULL;
    }

    return pReturn;
}


int addLLElement(LinkedList *pList, int position, ListNode element) {
    int ret = FALSE;
    int i = 0;
    ListNode *pPreNode = NULL;
    ListNode *pNewNode = NULL;

    if (pList != NULL) {
        if (position >= 0 && position <= pList->currentElementCount) {
            pNewNode = (ListNode *) malloc(sizeof(ListNode));
            if (pNewNode != NULL) {
                *pNewNode = element;
                pNewNode->pLink = NULL;

                pPreNode = &(pList->headerNode);
                for (i = 0; i < position; i++) {
                    pPreNode = pPreNode->pLink;
                }

                pNewNode->pLink = pPreNode->pLink;
                pPreNode->pLink = pNewNode;

                pList->currentElementCount++;

                ret = TRUE;
            } else {
                printf("ERROR: Memory allocation failed : addLLElement()\n");
                return ret;
            }
        } else {
            printf("ERROR: [%d] Index out of rage: addLLElement()\n", position);
        }
    }
    return ret;
}


int addLLFDElement(FDLinkedList *pList, int position, FDListNode element) {
    int ret = FALSE;
    int i = 0;
    FDListNode *pPreNode = NULL;
    FDListNode *pNewNode = NULL;

    if (pList != NULL) {
        if (position >= 0 && position <= pList->currentElementCount) {
            pNewNode = (FDListNode *) malloc(sizeof(FDListNode));
            if (pNewNode != NULL) {
                *pNewNode = element;
                pNewNode->pLinkFD = NULL;

                pPreNode = &(pList->headerNode);
                for (i = 0; i < position; i++) {
                    pPreNode = pPreNode->pLinkFD;
                }

                pNewNode->pLinkFD = pPreNode->pLinkFD;
                pPreNode->pLinkFD = pNewNode;

                pList->currentElementCount++;

                ret = TRUE;
            } else {
                printf("ERROR: Memory allocation failed : addLLFDElement()\n");
                return ret;
            }
        } else {
            printf("ERROR: [%d] Index out of rage: addLLFDElement()\n", position);
        }
    }
    return ret;
}


int removeLLElement(LinkedList *pList, int position) {
    int ret = FALSE;
    int arrayCount = 0;
    ListNode *pPreNode = NULL;
    ListNode *pDelNode = NULL;

    if (pList != NULL) {
        arrayCount = getLinkedListLength(pList);
        if (position >= 0 && position < arrayCount) {
            pPreNode = &(pList->headerNode);
            for (int i = 0; i < position; i++) {
                pPreNode = pPreNode->pLink;
            }

            pDelNode = pPreNode->pLink;
            pPreNode->pLink = pDelNode->pLink;
            free(pDelNode);

            pList->currentElementCount--;

            ret = TRUE;
        } else {
            printf("ERROR: [%d] Index out of rage: deleteLLElement()\n", position);
        }
    }

    return ret;
}


int removeLLFDElement(FDLinkedList *pList, int position) {
    int ret = FALSE;
    int arrayCount = 0;
    FDListNode *pPreNode = NULL;
    FDListNode *pDelNode = NULL;

    if (pList != NULL) {
        arrayCount = getFDLinkedListLength(pList);
        if (position >= 0 && position < arrayCount) {
            pPreNode = &(pList->headerNode);
            for (int i = 0; i < position; i++) {
                pPreNode = pPreNode->pLinkFD;
            }

            pDelNode = pPreNode->pLinkFD;
            pPreNode->pLinkFD = pDelNode->pLinkFD;
            free(pDelNode);

            pList->currentElementCount--;

            ret = TRUE;
        } else {
            printf("ERROR: [%d] Index out of rage: deleteLLElement()\n", position);
        }
    }

    return ret;
}


ListNode *getLLElement(LinkedList *pList, int position) {
    ListNode *pReturn = NULL;
    ListNode *pNode = NULL;

    if (pList != NULL) {
        if (position >= 0 && position < pList->currentElementCount) {
            pNode = &(pList->headerNode);
            for (int i = 0; i <= position; i++) {
                pNode = pNode->pLink;
            }
            pReturn = pNode;
        }
    }
    return pReturn;
}


FDListNode *getLLFDElement(FDLinkedList *pList, int position) {
    FDListNode *pReturn = NULL;
    FDListNode *pNode = NULL;

    if (pList != NULL) {
        if (position >= 0 && position < pList->currentElementCount) {
            pNode = &(pList->headerNode);
            for (int i = 0; i <= position; i++) {
                pNode = pNode->pLinkFD;
            }
            pReturn = pNode;
        }
    }
    return pReturn;
}


void deleteLinkedList(LinkedList *pList) {
    if (pList != NULL) {
        clearLinkedList(pList);
        free(pList);
    }
}


void deleteFDLinkedList(FDLinkedList *pList) {
    if (pList != NULL) {
        clearFDLinkedList(pList);
        free(pList);
    }
}


void clearLinkedList(LinkedList *pList) {
    if (pList != NULL) {
        if (pList->currentElementCount > 0) {
            removeLLElement(pList, 0);
        }
    }
}


void clearFDLinkedList(FDLinkedList *pList) {
    if (pList != NULL) {
        if (pList->currentElementCount > 0) {
            removeLLFDElement(pList, 0);
        }
    }
}


int getLinkedListLength(LinkedList *pList) {
    int ret = 0;

    if (pList != NULL) {
        ret = pList->currentElementCount;
    }

    return ret;
}


int getFDLinkedListLength(FDLinkedList *pList) {
    int ret = 0;

    if (pList != NULL) {
        ret = pList->currentElementCount;
    }

    return ret;
}


int isEmpty(LinkedList *pList) {
    int ret = FALSE;

    if (pList != NULL) {
        if (pList->currentElementCount == 0) {
            ret = TRUE;
        }
    }

    return ret;
}


void save_processes(LinkedList* proc_list) {
    FILE *fp = NULL;
    uid_t uid = getuid();
    char command[128] = {0};
    char pid_str[10] = {0};
    int i = 0;
    int pid = 0;


    sprintf(command, "sudo ps aux | grep -v PID | awk '{print $2}'", uid);
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("ERROR: saveUserProcesses() - Cannot execute command\n");
        exit(1);
    }

    while(fgets(pid_str , sizeof(pid_str), fp) != NULL) {
        save_pid_to_linked_list(proc_list, pid_str, i);
        i++;
    }
    pclose(fp);
}


void save_pid_to_linked_list(LinkedList *proc_list, char *pid_str, int i) {
    ListNode proc = {0};
    proc.pid = atoi(pid_str);
    addLLElement(proc_list, i, proc);
    memset(pid_str, 0, 10);
}


void process_directory_processing(LinkedList *proc_list) {
    char path[64] = {0};
    for (int i = 0; i < proc_list->currentElementCount; i++) {
        sprintf(path, "/proc/%d/", getLLElement(proc_list, i)->pid);
        DIR* dir = opendir(path);
        if (dir == NULL) {
            break;
            fprintf(stderr, "Failed to open directory %s\n", path);
        }

        puts("======================================================================================");
        save_ppid_to_linked_list(path, proc_list, i);
        save_comm_to_linked_list(path, proc_list, i);
        save_cmdline_to_linked_list(path, proc_list, i);
        strcat(path, "fd/");
        save_fd_to_linked_list(path, getLLElement(proc_list, i)->pid);
        puts("======================================================================================\n");


        closedir(dir);
    }
}


void save_ppid_to_linked_list(char *path, LinkedList *proc_list, int index) {
    int result = 0;
    FILE *fp;
    char line[30];
    char *token;

    result = chdir(path);
    if (result == 0) {
        fp = popen("cat status | grep -E '^(PPid):'", "r");
        if (fp == NULL) {
            puts("save_ppid_to_linked_list() - Cannot execute: \"cat status\"");
            exit(1);
        }
        while (fgets(line, sizeof(line), fp) != NULL) {
            token = strtok(line, "PPid:\t");
            token[strlen(token)] = 0;
            getLLElement(proc_list, index)->ppid = atoi(token);
        }
        pclose(fp);
    }
    else {
        puts("ppid - Doesn't exist");
    }
    printf("Pid : %d\n", getLLElement(proc_list, index)->pid);
    printf("PPid: %d\n", getLLElement(proc_list, index)->ppid);
}


void save_comm_to_linked_list(char *path, LinkedList *proc_list, int index) {
    int result = 0;
    FILE *fp;
    char line[256];

    result = chdir(path);
    if (result == 0) {
        fp = popen("cat comm", "r");
        if (fp == NULL) {
            puts("save_comm_to_linked_list() - Cannot execute: \"cat comm\"");
            exit(1);
        }
        while (fgets(line, sizeof(line), fp) != NULL) {
            line[strlen(line) - 1] = 0;
            strcpy(getLLElement(proc_list, index)->comm, line);
        }
        pclose(fp);
        printf("comm: %s\n", getLLElement(proc_list, index)->comm);
    }
    else {
        puts("comm - Directory doesn't exist");
    }
}


void save_cmdline_to_linked_list(char *path, LinkedList *proc_list, int index) {
    int result = 0;
    FILE *fp;
    char line[512];

    result = chdir(path);
    if (result == 0) {
        fp = popen("cat cmdline", "r");
        if (fp == NULL) {
            puts("save_cmdline_to_linked_list() - Cannot execute: \"cat cmdline\"");
            exit(1);
        }
        while (fgets(line, sizeof(line), fp) != NULL) {
            strcpy(getLLElement(proc_list, index)->cmdline, line);
        }
        pclose(fp);
        printf("cmdline: %s\n", getLLElement(proc_list, index)->cmdline);
    }
    else {
        puts("cmdline - Directory doesn't exist");
    }
}


void save_fd_to_linked_list(char *path, int pid) {
    int result = 0;
    FILE *fp;
    char line[350], port[60];
    int count = 0;
    int i = 0, j = 0;
    FDLinkedList *fd_list = NULL;

    fd_list = createFDLinkedList();
    result = chdir(path);
    if (result == 0) {
        fp = popen("ls -al", "r");
        if (fp == NULL) {
            puts("save_fd_to_linked_list() - Cannot execute: \"ls -al\"");
            exit(1);
        }
        while (fgets(line, sizeof(line), fp) != NULL) {
            FDListNode fd_node = {0,};
            line[strlen(line) - 1] = 0;
            if (count >= 3) {
                char *token = strtok(line, " ");
                while (i < 10) {
                    token = strtok(NULL, " ");
                    if (i == 7) fd_node.fd = atoi(token);
                    if (i == 9) {
                        if(strstr(token, "socket")) find_fd_port_number(&fd_node, pid);
                        else strcpy(fd_node.fd_info, token);
                    }
                    memset(port, 0, 60);
                    i++;
                }
                addLLFDElement(fd_list, j, fd_node);
                j++;
                i = 0;
            }
            count++;
        }
        count = 0;
        pclose(fp);
    }
    for (int f = 0; f < fd_list->currentElementCount; f++) {
        printf("\tfd: %d\t->\t%s\n", getLLFDElement(fd_list, f)->fd, getLLFDElement(fd_list, f)->fd_info);
    }
    deleteFDLinkedList(fd_list);
}


void find_fd_port_number(FDListNode* fd_node, int pid) {
    FILE *fp;
    char cmd[32] = {0};
    char line[250] = {0};
    char* port;

    sprintf(cmd, "lsof -np %d | grep %du", pid, fd_node->fd);
    fp = popen(cmd, "r");
    if (fp == NULL) {
        puts("find_fd_port_number() - Cannot execute: \"lsof -np {pid}\"");
        exit(1);
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        line[strlen(line) - 1] = 0;
        if (strstr(line, "TCP")) {
            port = strstr(line, "TCP");
            strcpy(fd_node->fd_info, port);
        }
        if (strstr(line, "UDP")) {
            port = strstr(line, "UDP");
            strcpy(fd_node->fd_info, port);
        }
        if (strstr(line, "protocol")) {
            port = strstr(line, "protocol");
            strcpy(fd_node->fd_info, port);
        }
        if (strstr(line, "KOBJECT_UEVENT")) {
            port = strstr(line, "KOBJECT_UEVENT");
            strcpy(fd_node->fd_info, port);
        }
        if (strstr(line, "ROUTE")) {
            port = strstr(line, "ROUTE");
            strcpy(fd_node->fd_info, port);
        }
        if (strstr(line, "GENERIC")) {
            port = strstr(line, "GENERIC");
            strcpy(fd_node->fd_info, port);
        }
        if (strstr(line, "type")) {
            port = strstr(line, "type");
            strcpy(fd_node->fd_info, port);
        }
    }
    pclose(fp);
}
