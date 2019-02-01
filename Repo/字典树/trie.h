#ifndef TRIE_H
#define TRIE_H

typedef struct word_trie_t word_trie_t;
typedef enum bool bool;

enum bool
{
    false = 0,
    true = 1,
};

struct word_trie_t
{
    bool (*insert)(word_trie_t *this, char *str);
    bool (*find_word)(word_trie_t *this, char *str);
    int (*find_prefix)(word_trie_t *this, char *str);
    bool (*delete)(word_trie_t *this, char *str);
    void (*destroy)(word_trie_t *this);
};

word_trie_t *word_trie_create();
#endif
