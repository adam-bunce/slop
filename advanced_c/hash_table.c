#include <stdio.h>
#include <search.h>

void print_entry(ENTRY *entry) {
    if (entry == NULL) {
        printf("NULL\n");
        return;
    } else {
        printf("%s -> %d\n", entry->key, entry->data);
    }
}


int main(void) {

    // only one at a time
    hcreate(30);

    ENTRY entry = {.key = "hello", .data=(void *) 1};
    ENTRY *result = hsearch(entry, ENTER);
    print_entry(result);

    hdestroy();
    return 0;
}
