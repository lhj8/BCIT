#include "linked_list.h"


int main() {
    LinkedList *proc_list = NULL;
    proc_list = createLinkedList();
    save_processes(proc_list);
    process_directory_processing(proc_list);
    deleteLinkedList(proc_list);
    puts("Fished Process");
    exit(EXIT_SUCCESS);
}

