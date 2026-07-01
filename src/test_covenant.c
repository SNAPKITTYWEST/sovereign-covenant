#include <stdio.h>
#include <string.h>
#include "sovereign_covenant.h"

int main(void) {
    int passed = 0, total = 0;
    
    printf("SOVEREIGN COVENANT - 1928 Moorish Divine Trust Structure\n");
    printf("Love, Truth, Peace, Freedom, Justice\n\n");
    
    /* Hash tests */
    printf("[HASH]\n");
    {
        char h1[HASH_BUF_LEN], h2[HASH_BUF_LEN];
        covenant_hash_string("test", h1);
        covenant_hash_string("test", h2);
        total++; if (strcmp(h1, h2) == 0) { printf("  deterministic: PASS\n"); passed++; } else printf("  deterministic: FAIL\n");
    }
    {
        char h1[HASH_BUF_LEN], h2[HASH_BUF_LEN];
        covenant_hash_string("hello", h1);
        covenant_hash_string("world", h2);
        total++; if (strcmp(h1, h2) != 0) { printf("  different: PASS\n"); passed++; } else printf("  different: FAIL\n");
    }
    {
        char h[HASH_BUF_LEN];
        covenant_hash_string("anything", h);
        total++; if (strlen(h) == 64) { printf("  length 64: PASS\n"); passed++; } else printf("  length 64: FAIL\n");
    }
    
    /* Principle tests */
    printf("\n[PRINCIPLES]\n");
    {
        int obs[5] = {1, 1, 1, 1, 1};
        total++; if (principles_satisfied(obs)) { printf("  all observed: PASS\n"); passed++; } else printf("  all observed: FAIL\n");
    }
    {
        int obs[5] = {1, 1, 1, 1, 0};
        total++; if (!principles_satisfied(obs)) { printf("  missing one: PASS\n"); passed++; } else printf("  missing one: FAIL\n");
    }
    {
        total++; if (covenant_declaration()) { printf("  declaration: PASS\n"); passed++; } else printf("  declaration: FAIL\n");
    }
    
    /* Temple tests */
    printf("\n[TEMPLE]\n");
    {
        Temple t;
        temple_create(&t, "Temple No. 1", "Chicago");
        total++; if (strcmp(t.name, "Temple No. 1") == 0) { printf("  create: PASS\n"); passed++; } else printf("  create: FAIL\n");
    }
    {
        Temple t;
        temple_create(&t, "Temple No. 2", "Newark");
        for (int i = 0; i < 5; i++) t.principles[i] = 1;
        total++; if (temple_in_good_standing(&t)) { printf("  good standing: PASS\n"); passed++; } else printf("  good standing: FAIL\n");
    }
    {
        Temple t;
        temple_create(&t, "Temple No. 3", "Detroit");
        total++; if (!temple_in_good_standing(&t)) { printf("  not standing: PASS\n"); passed++; } else printf("  not standing: FAIL\n");
    }
    {
        Temple t;
        temple_create(&t, "Unity Temple", "Philadelphia");
        const char *p = temple_proclaim(&t);
        total++; if (strstr(p, "Unity Temple")) { printf("  proclaim: PASS\n"); passed++; } else printf("  proclaim: FAIL\n");
    }
    
    /* Grand Sheik tests */
    printf("\n[GRAND SHEIK]\n");
    {
        GrandSheik s;
        sheik_create(&s, "Prophet Noble Drew Ali");
        total++; if (strcmp(s.name, "Prophet Noble Drew Ali") == 0) { printf("  create: PASS\n"); passed++; } else printf("  create: FAIL\n");
    }
    {
        GrandSheik s;
        sheik_create(&s, "Prophet Noble Drew Ali");
        for (int i = 0; i < 5; i++) s.principles[i] = 1;
        total++; if (sheik_has_authority(&s)) { printf("  authority: PASS\n"); passed++; } else printf("  authority: FAIL\n");
    }
    {
        GrandSheik s;
        sheik_create(&s, "Prophet Noble Drew Ali");
        for (int i = 0; i < 5; i++) s.principles[i] = 1;
        char hash[HASH_BUF_LEN];
        total++; if (sheik_sign(&s, "Test", hash)) { printf("  sign: PASS\n"); passed++; } else printf("  sign: FAIL\n");
    }
    
    /* Covenant tests */
    printf("\n[COVENANT]\n");
    {
        Covenant c;
        covenant_create(&c, "Test Covenant");
        covenant_add_article(&c, "Article 1");
        total++; if (c.article_count == 1) { printf("  add article: PASS\n"); passed++; } else printf("  add article: FAIL\n");
    }
    {
        GrandSheik s;
        sheik_create(&s, "Prophet Noble Drew Ali");
        for (int i = 0; i < 5; i++) s.principles[i] = 1;
        Covenant c;
        covenant_create(&c, "Sealed");
        covenant_seal(&c, &s);
        total++; if (covenant_verify(&c)) { printf("  verify: PASS\n"); passed++; } else printf("  verify: FAIL\n");
    }
    {
        GrandSheik s;
        sheik_create(&s, "Prophet Noble Drew Ali");
        for (int i = 0; i < 5; i++) s.principles[i] = 1;
        Covenant c;
        covenant_create(&c, "Tamper");
        covenant_add_article(&c, "Original article");
        covenant_seal(&c, &s);
        strcpy(c.articles[0], "TAMPERED");
        total++; if (!covenant_verify(&c)) { printf("  tamper detect: PASS\n"); passed++; } else printf("  tamper detect: FAIL\n");
    }
    {
        Covenant c;
        covenant_create(&c, "Ratify");
        total++; if (!covenant_ratify(&c)) { printf("  ratify fail: PASS\n"); passed++; } else printf("  ratify fail: FAIL\n");
        for (int i = 0; i < 5; i++) c.principles[i] = 1;
        total++; if (covenant_ratify(&c)) { printf("  ratify ok: PASS\n"); passed++; } else printf("  ratify ok: FAIL\n");
    }
    
    /* Chain tests */
    printf("\n[CHAIN]\n");
    {
        CovenantChain chain;
        chain_init(&chain);
        total++; if (chain_verify(&chain)) { printf("  empty valid: PASS\n"); passed++; } else printf("  empty valid: FAIL\n");
    }
    {
        GrandSheik s;
        sheik_create(&s, "Prophet Noble Drew Ali");
        for (int i = 0; i < 5; i++) s.principles[i] = 1;
        CovenantChain chain;
        chain_init(&chain);
        for (int i = 0; i < 5; i++) {
            char title[32];
            snprintf(title, sizeof(title), "Covenant %d", i+1);
            Covenant c;
            covenant_create(&c, title);
            covenant_seal(&c, &s);
            chain_append(&chain, &c);
        }
        total++; if (chain.length == 5) { printf("  append 5: PASS\n"); passed++; } else printf("  append 5: FAIL\n");
        total++; if (chain_verify(&chain)) { printf("  verify chain: PASS\n"); passed++; } else printf("  verify chain: FAIL\n");
    }
    
    /* Nation tests */
    printf("\n[NATION]\n");
    {
        MoorishNation n;
        nation_create(&n, "Prophet Noble Drew Ali");
        total++; if (strcmp(n.nation_name, "Moorish American") == 0) { printf("  create: PASS\n"); passed++; } else printf("  create: FAIL\n");
    }
    {
        MoorishNation n;
        nation_create(&n, "Prophet Noble Drew Ali");
        nation_charter_temple(&n, "Temple No. 1", "Chicago");
        nation_charter_temple(&n, "Temple No. 2", "Newark");
        total++; if (nation_verify(&n)) { printf("  verify: PASS\n"); passed++; } else printf("  verify: FAIL\n");
    }
    {
        const char *p = nation_proclamation();
        total++; if (strstr(p, "Asiatics")) { printf("  proclamation: PASS\n"); passed++; } else printf("  proclamation: FAIL\n");
    }
    
    printf("\n==========================================================\n");
    printf("  Results: %d/%d passed\n", passed, total);
    printf("==========================================================\n");
    
    return passed == total ? 0 : 1;
}
