#ifndef PAGEINFO_H
#define PAGEINFO_H

#define PAGESIZE 8
#define PAGES 8192
#define MEMSIZE 65536

struct entry{
    uint16_t page_addr;
    uint16_t offset;
};

struct page{
    uint16_t page_addr;
    uint8_t *mem;
    uint8_t *op;
};


#endif
