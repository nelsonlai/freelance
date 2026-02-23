#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 105
#define MAXL 105
#define MAXCARDS 11000
#define HSIZE 20011   // hash buckets (prime)

typedef struct Entry Entry;

typedef struct Node {
    int v;

    // main doubly-linked list (either table queue or a player's hand queue)
    struct Node *prev, *next;

    // same-value doubly-linked list while node is in table queue
    struct Node *psame, *nsame;

    // which hash entry this node belongs to (only meaningful when in table queue)
    Entry *ent;
} Node;

typedef struct Deque {
    Node *head, *tail;
    int sz;
} Deque;

struct Entry {
    int key;
    Node *h, *t;     // head/tail of same-value list in table queue
    Entry *next;     // bucket chaining
};

static Entry *buckets[HSIZE];

// ---------- Fast-ish input ----------
static int read_int(int *out) {
    int c = getchar();
    while (c != EOF && c <= ' ') c = getchar();
    if (c == EOF) return 0;
    int sign = 1;
    if (c == '-') { sign = -1; c = getchar(); }
    long long x = 0;
    while (c > ' ') {
        x = x * 10 + (c - '0');
        c = getchar();
    }
    *out = (int)(x * sign);
    return 1;
}

// ---------- Deque ops ----------
static void dq_init(Deque *d) { d->head = d->tail = NULL; d->sz = 0; }

static void dq_push_back(Deque *d, Node *x) {
    x->prev = d->tail;
    x->next = NULL;
    if (d->tail) d->tail->next = x;
    else d->head = x;
    d->tail = x;
    d->sz++;
}

static Node* dq_pop_front(Deque *d) {
    Node *x = d->head;
    if (!x) return NULL;
    Node *n = x->next;
    d->head = n;
    if (n) n->prev = NULL;
    else d->tail = NULL;
    x->prev = x->next = NULL;
    d->sz--;
    return x;
}

// append an entire segment [segH..segT] to back of deque d
static void dq_append_segment(Deque *d, Node *segH, Node *segT, int segSz) {
    if (!segH) return;
    segH->prev = d->tail;
    if (d->tail) d->tail->next = segH;
    else d->head = segH;
    d->tail = segT;
    segT->next = NULL;
    d->sz += segSz;
}

// ---------- Hash helpers ----------
static unsigned hash_int(int x) {
    // simple mix
    unsigned u = (unsigned)x;
    u ^= u >> 16;
    u *= 0x7feb352d;
    u ^= u >> 15;
    u *= 0x846ca68b;
    u ^= u >> 16;
    return u % HSIZE;
}

static void hash_clear(void) {
    for (int i = 0; i < HSIZE; i++) {
        Entry *e = buckets[i];
        while (e) {
            Entry *nx = e->next;
            free(e);
            e = nx;
        }
        buckets[i] = NULL;
    }
}

static Entry* get_entry(int key, int create) {
    unsigned h = hash_int(key);
    Entry *e = buckets[h];
    while (e) {
        if (e->key == key) return e;
        e = e->next;
    }
    if (!create) return NULL;

    e = (Entry*)malloc(sizeof(Entry));
    e->key = key;
    e->h = e->t = NULL;
    e->next = buckets[h];
    buckets[h] = e;
    return e;
}

// link node into same-value list tail
static void same_append(Node *x, Entry *e) {
    x->ent = e;
    x->psame = e->t;
    x->nsame = NULL;
    if (e->t) e->t->nsame = x;
    else e->h = x;
    e->t = x;
}

// unlink node from same-value list
static void same_remove(Node *x) {
    Entry *e = x->ent;
    if (!e) return;
    Node *p = x->psame, *n = x->nsame;
    if (p) p->nsame = n;
    else e->h = n;
    if (n) n->psame = p;
    else e->t = p;
    x->psame = x->nsame = NULL;
    x->ent = NULL;
}

// ---------- Table queue ops with same-value tracking ----------
static void table_push_back(Deque *table, Node *x) {
    dq_push_back(table, x);
    Entry *e = get_entry(x->v, 1);
    same_append(x, e);
}

// detach whole table and return segment head/tail/size
static void table_take_all(Deque *table, Node **outH, Node **outT, int *outSz) {
    *outH = table->head;
    *outT = table->tail;
    *outSz = table->sz;
    table->head = table->tail = NULL;
    table->sz = 0;
}

// detach suffix from 'start' (which is inside table) to tail, return segment
static void table_detach_suffix(Deque *table, Node *start, Node **outH, Node **outT, int *outSz) {
    *outH = start;
    *outT = table->tail;

    // compute size of suffix by walking from start to tail (amortized OK)
    int cnt = 0;
    Node *cur = start;
    while (cur) { cnt++; cur = cur->next; }
    *outSz = cnt;

    // cut from main table list
    Node *before = start->prev;
    if (before) {
        before->next = NULL;
        table->tail = before;
    } else {
        table->head = table->tail = NULL;
    }

    // fix start prev
    start->prev = NULL;

    // adjust table size
    table->sz -= cnt;
}

// remove same-value links for every node in a segment [h..t] (segment is linked by next)
static void remove_same_for_segment(Node *h) {
    Node *cur = h;
    while (cur) {
        Node *nx = cur->next;
        // segment end is indicated by cur->next == NULL once detached/collected
        same_remove(cur);
        cur = nx;
    }
}

// ---------- Debug: print state for "each round execution process" ----------
static void deque_to_string(Deque *d, char *buf, int cap) {
    int pos = 0;
    Node *cur = d->head;
    while (cur && pos < cap - 2) {
        pos += snprintf(buf + pos, (size_t)(cap - pos), "%d", cur->v);
        cur = cur->next;
    }
    if (pos == 0) buf[0] = '\0';
}

static void print_round_state(int n, int round, int player_just_acted,
                             Deque *table, Deque *hand, int *out_round) {
    char buf[1024];
    printf("Round %d.%d\n", round, player_just_acted);

    deque_to_string(table, buf, sizeof(buf));
    printf("  Card queue: %s\n", buf[0] ? buf : "(empty)");

    for (int i = 1; i <= n; i++) {
        if (out_round[i]) {
            printf("  Player %d: (out)\n", i);
        } else {
            deque_to_string(&hand[i], buf, sizeof(buf));
            printf("  Player %d: %s\n", i, buf[0] ? buf : "(empty)");
        }
    }
    putchar('\n');
}

// ---------- Main ----------
int main(void) {
    int n, m, l, s, T;

    while (1) {
        if (!read_int(&n)) return 0;
        read_int(&m); read_int(&l); read_int(&s); read_int(&T);
        if (n == -1 && m == -1 && l == -1 && s == -1 && T == -1) break;

        // clear hash table for each test case
        hash_clear();

        // init players' hands
        Deque hand[MAXN];
        int out_round[MAXN]; // 0 = not out
        for (int i = 1; i <= n; i++) {
            dq_init(&hand[i]);
            out_round[i] = 0;
        }

        // allocate nodes for all cards
        static Node pool[MAXCARDS];
        int pool_idx = 0;

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < l; j++) {
                int x; read_int(&x);
                Node *nd = &pool[pool_idx++];
                nd->v = x;
                nd->prev = nd->next = NULL;
                nd->psame = nd->nsame = NULL;
                nd->ent = NULL;
                dq_push_back(&hand[i], nd);
            }
        }

        // table queue
        Deque table;
        dq_init(&table);

        int alive = n;
        int last_round = 0;

        // simulate rounds
        for (int round = 1; round <= T; round++) {
            // each alive player acts in order
            for (int i = 1; i <= n; i++) {
                if (out_round[i]) continue; // already out

                // play first card
                Node *card = dq_pop_front(&hand[i]);
                if (!card) {
                    // should not happen (a player with empty hand should have been out after previous round)
                    continue;
                }

                int table_was_empty = (table.sz == 0);
                table_push_back(&table, card);

                // apply collect rules
                if (card->v == s) {
                    if (!table_was_empty) {
                        // collect whole table
                        Node *segH, *segT;
                        int segSz;
                        table_take_all(&table, &segH, &segT, &segSz);

                        // break same-value chains for all nodes in seg
                        // after table_take_all, the list is still linked; ensure segT->next == NULL
                        if (segT) segT->next = NULL;
                        remove_same_for_segment(segH);

                        // append to player's hand
                        dq_append_segment(&hand[i], segH, segT, segSz);
                    }
                } else {
                    Entry *e = get_entry(card->v, 0);
                    // if at least 2 occurrences in table
                    if (e && e->h && e->h->nsame) {
                        Node *start = e->h; // earliest occurrence

                        // detach suffix from start
                        Node *segH, *segT;
                        int segSz;
                        table_detach_suffix(&table, start, &segH, &segT, &segSz);

                        // ensure segment tail ends properly
                        if (segT) segT->next = NULL;

                        // remove same-value links for nodes in segment
                        remove_same_for_segment(segH);

                        // append segment to player's hand
                        dq_append_segment(&hand[i], segH, segT, segSz);
                    }
                }

                // 輸出該 round 中此玩家行動後的狀態 (Round x.y)
                print_round_state(n, round, i, &table, hand, out_round);
            }

            // after round: eliminate players with empty hand
            for (int i = 1; i <= n; i++) {
                if (out_round[i]) continue;
                if (hand[i].sz == 0) {
                    out_round[i] = round;
                    alive--;
                }
            }

            last_round = round;

            if (alive <= 1) break; // game over early
        }
        (void)last_round; /* used when not printing per-round */

        // output: if ended early, we output status after last_round; if T=0, last_round stays 0.
        // first line: n integers
        for (int i = 1; i <= n; i++) {
            if (i > 1) putchar(' ');
            if (out_round[i]) {
                printf("-%d", out_round[i]);
            } else {
                printf("%d", hand[i].sz);
            }
        }
        putchar('\n');

        // next n lines: each player's hand cards in order (blank line if out)
        for (int i = 1; i <= n; i++) {
            if (out_round[i]) {
                putchar('\n');
                continue;
            }
            Node *cur = hand[i].head;
            int first = 1;
            while (cur) {
                if (!first) putchar(' ');
                first = 0;
                printf("%d", cur->v);
                cur = cur->next;
            }
            putchar('\n');
        }
    }
    return 0;
}