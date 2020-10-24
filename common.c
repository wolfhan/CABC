#include <stdlib.h>
#include "common.h"

/* Allocate buffer for struct book node. */
struct book *balloc() {
    return (struct book *) malloc(sizeof(struct book));
}
