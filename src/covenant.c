/**
 * covenant.c
 *
 * 1928 Moorish Divine Covenant Trust Structure
 * Implementation of the Sovereign Covenant Framework
 *
 * "This Divine Covenant is from your Holy Prophet Noble Drew Ali,
 *  through the guidance of his Father God Allah."
 *
 * Love, Truth, Peace, Freedom, Justice
 */

#include "sovereign_covenant.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* ======================================================================
 * DIVINE PRINCIPLES
 * ====================================================================== */

const DivinePrinciple DIVINE_ORDER[PRINCIPLE_COUNT] = {
    LOVE, TRUTH, PEACE, FREEDOM, JUSTICE
};

static const char *PRINCIPLE_NAMES[] = {
    "Love", "Truth", "Peace", "Freedom", "Justice"
};

const char *principle_name(DivinePrinciple p) {
    if (p < PRINCIPLE_COUNT) return PRINCIPLE_NAMES[p];
    return "Unknown";
}

int principles_satisfied(const int observed[PRINCIPLE_COUNT]) {
    for (int i = 0; i < PRINCIPLE_COUNT; i++) {
        if (!observed[i]) return 0;
    }
    return 1;
}

const char *covenant_declaration(void) {
    return
        "Love, Truth, Peace, Freedom, and Justice — "
        "these are the five divine principles upon which all covenants "
        "of the Moorish Science Temple of America are formed. "
        "Every subordinate temple, every article of faith, every seal "
        "of authority must observe these principles. "
        "This is the covenant of our forefathers.";
}

/* ======================================================================
 * HASH — Simplified SHA-256-like (64-char hex)
 * ====================================================================== */

void covenant_hash_init(CovenantHash *ctx) {
    /* FNV-1a inspired initialization */
    ctx->state[0] = 0xcbf29ce484222325ULL;
    ctx->state[1] = 0x100000001b3ULL;
    ctx->state[2] = 0xcbf29ce484222325ULL;
    ctx->state[3] = 0x100000001b3ULL;
    ctx->state[4] = 0xcbf29ce484222325ULL;
    ctx->state[5] = 0x100000001b3ULL;
    ctx->state[6] = 0xcbf29ce484222325ULL;
    ctx->state[7] = 0x100000001b3ULL;
    ctx->count = 0;
    memset(ctx->buffer, 0, sizeof(ctx->buffer));
}

void covenant_hash_update(CovenantHash *ctx, const void *data, size_t len) {
    const uint8_t *p = (const uint8_t *)data;
    for (size_t i = 0; i < len; i++) {
        size_t word_idx = ctx->count % 8;
        ctx->state[word_idx] ^= ((uint64_t)p[i]) << ((ctx->count * 7) % 64);
        ctx->state[word_idx] *= 0x100000001b3ULL;
        ctx->count++;
    }
}

void covenant_hash_final(CovenantHash *ctx, char out[HASH_BUF_LEN]) {
    /* Mix state into 4 words = 32 bytes = 64 hex chars */
    uint64_t mix[4];
    mix[0] = ctx->state[0] ^ ctx->state[4];
    mix[1] = ctx->state[1] ^ ctx->state[5];
    mix[2] = ctx->state[2] ^ ctx->state[6];
    mix[3] = ctx->state[3] ^ ctx->state[7];

    for (int i = 0; i < 4; i++) {
        mix[i] ^= mix[i] >> 33;
        mix[i] *= 0xff51afd7ed558ccdULL;
        mix[i] ^= mix[i] >> 33;
        mix[i] *= 0xc4ceb9fe1a85ec53ULL;
        mix[i] ^= mix[i] >> 33;
    }

    /* Convert to hex: 4 x 16 chars = 64 chars */
    for (int i = 0; i < 4; i++) {
        snprintf(out + (i * 16), 17, "%016llx", (unsigned long long)mix[i]);
    }
    out[HASH_LEN] = '\0';
}

void covenant_hash_string(const char *input, char out[HASH_BUF_LEN]) {
    CovenantHash ctx;
    covenant_hash_init(&ctx);
    covenant_hash_update(&ctx, input, strlen(input));
    covenant_hash_final(&ctx, out);
}

/* ======================================================================
 * TEMPLE
 * ====================================================================== */

int temple_create(Temple *t, const char *name, const char *city) {
    if (!t || !name || !city) return 0;
    memset(t, 0, sizeof(*t));
    strncpy(t->name, name, TEMPLE_NAME_MAX - 1);
    strncpy(t->city, city, TEMPLE_NAME_MAX - 1);
    t->charter_date = time(NULL);
    t->is_active = 1;
    t->member_count = 0;

    /* Generate temple ID from name + city */
    char raw[256];
    snprintf(raw, sizeof(raw), "%s:%s:%ld", name, city, (long)t->charter_date);
    covenant_hash_string(raw, t->id);

    return 1;
}

int temple_verify_charter(const Temple *t, const char *charter_text) {
    if (!t || !charter_text) return 0;
    char hash[HASH_BUF_LEN];
    covenant_hash_string(charter_text, hash);
    return strcmp(t->charter_hash, hash) == 0;
}

int temple_in_good_standing(const Temple *t) {
    if (!t || !t->is_active) return 0;
    return principles_satisfied(t->principles);
}

const char *temple_proclaim(const Temple *t) {
    if (!t) return "Unknown Temple";
    static char proclamation[512];
    snprintf(proclamation, sizeof(proclamation),
        "We, the members of %s, Temple of the Moorish Science Temple of America, "
        "do hereby proclaim our nationality as Moorish Americans. "
        "We are the descendants of the ancient Moabites. "
        "We are a Nation within a Nation.",
        t->name);
    return proclamation;
}

/* ======================================================================
 * GRAND SHEIK
 * ====================================================================== */

int sheik_create(GrandSheik *s, const char *name) {
    if (!s || !name) return 0;
    memset(s, 0, sizeof(*s));
    strncpy(s->name, name, SHEIK_NAME_MAX - 1);
    s->term_start = time(NULL);

    /* Generate seal hash */
    char raw[256];
    snprintf(raw, sizeof(raw), "GRAND_SHEIK:%s:%ld", name, (long)s->term_start);
    covenant_hash_string(raw, s->seal_hash);

    return 1;
}

int sheik_has_authority(const GrandSheik *s) {
    if (!s) return 0;
    return principles_satisfied(s->principles);
}

int sheik_sign(const GrandSheik *s, const char *document, char out_hash[HASH_BUF_LEN]) {
    if (!s || !document || !out_hash) return 0;
    if (!sheik_has_authority(s)) return 0;

    char raw[1024];
    snprintf(raw, sizeof(raw), "%s:%s:%s", s->seal_hash, document, s->name);
    covenant_hash_string(raw, out_hash);
    return 1;
}

/* ======================================================================
 * COVENANT
 * ====================================================================== */

int covenant_create(Covenant *c, const char *title) {
    if (!c || !title) return 0;
    memset(c, 0, sizeof(*c));
    strncpy(c->title, title, COVENANT_TITLE_MAX - 1);
    c->seal_date = time(NULL);
    c->is_ratified = 0;
    return 1;
}

int covenant_add_article(Covenant *c, const char *article_text) {
    if (!c || !article_text) return 0;
    if (c->article_count >= COVENANT_ARTICLES_MAX) return 0;
    strncpy(c->articles[c->article_count], article_text, 255);
    c->articles[c->article_count][255] = '\0';
    c->article_count++;
    return 1;
}

int covenant_seal(Covenant *c, const GrandSheik *sheik) {
    if (!c || !sheik) return 0;

    /* Grand Sheik must observe all 5 principles to seal */
    if (!sheik_has_authority(sheik)) return 0;

    /* Copy sheik seal */
    strcpy(c->grand_sheik_hash, sheik->seal_hash);

    /* Compute covenant hash from title + articles + sheik hash */
    char raw[8192];
    char *p = raw;
    p += snprintf(p, sizeof(raw) - (size_t)(p - raw), "%s:%s:", c->title, c->grand_sheik_hash);
    for (int i = 0; i < c->article_count; i++) {
        p += snprintf(p, sizeof(raw) - (size_t)(p - raw), "%s:", c->articles[i]);
    }
    covenant_hash_string(raw, c->covenant_hash);

    c->seal_date = time(NULL);
    return 1;
}

int covenant_chain(Covenant *new_c, const Covenant *prev, const char *title, const GrandSheik *sheik) {
    if (!new_c || !prev || !title || !sheik) return 0;

    if (!covenant_create(new_c, title)) return 0;
    strcpy(new_c->prev_hash, prev->covenant_hash);

    /* Copy principles from previous */
    for (int i = 0; i < PRINCIPLE_COUNT; i++) {
        new_c->principles[i] = prev->principles[i];
    }

    return covenant_seal(new_c, sheik);
}

int covenant_verify(const Covenant *c) {
    if (!c) return 0;
    if (strlen(c->covenant_hash) == 0) return 0;

    /* Recompute hash */
    char raw[8192];
    char *p = raw;
    p += snprintf(p, sizeof(raw) - (size_t)(p - raw), "%s:%s:", c->title, c->grand_sheik_hash);
    for (int i = 0; i < c->article_count; i++) {
        p += snprintf(p, sizeof(raw) - (size_t)(p - raw), "%s:", c->articles[i]);
    }

    char expected[HASH_BUF_LEN];
    covenant_hash_string(raw, expected);

    return strcmp(c->covenant_hash, expected) == 0;
}

int covenant_ratify(Covenant *c) {
    if (!c) return 0;
    if (!principles_satisfied(c->principles)) return 0;
    c->is_ratified = 1;
    return 1;
}

int covenant_is_ratified(const Covenant *c) {
    return c && c->is_ratified;
}

/* ======================================================================
 * COVENANT CHAIN
 * ====================================================================== */

void chain_init(CovenantChain *chain) {
    if (!chain) return;
    chain->length = 0;
}

int chain_append(CovenantChain *chain, Covenant *c) {
    if (!chain || !c) return 0;
    if (chain->length >= CHAIN_MAX) return 0;

    /* If chain is not empty, chain to the last covenant */
    if (chain->length > 0) {
        Covenant *prev = &chain->entries[chain->length - 1];
        strcpy(c->prev_hash, prev->covenant_hash);
    }

    chain->entries[chain->length] = *c;
    chain->length++;
    return 1;
}

int chain_verify(const CovenantChain *chain) {
    if (!chain) return 0;
    if (chain->length == 0) return 1; /* Empty chain is valid */

    for (int i = 0; i < chain->length; i++) {
        /* Verify each covenant's hash */
        if (!covenant_verify(&chain->entries[i])) return 0;

        /* Verify chain linkage (except first) */
        if (i > 0) {
            if (strcmp(chain->entries[i].prev_hash,
                       chain->entries[i - 1].covenant_hash) != 0) {
                return 0;
            }
        }
    }
    return 1;
}

const Covenant *chain_head(const CovenantChain *chain) {
    if (!chain || chain->length == 0) return NULL;
    return &chain->entries[chain->length - 1];
}

/* ======================================================================
 * NATION WITHIN A NATION
 * ====================================================================== */

const char *DIVINE_CONSTITUTION_TEXT =
    "THE DIVINE CONSTITUTION AND BY-LAWS\n"
    "OF THE MOORISH SCIENCE TEMPLE OF AMERICA\n"
    "\n"
    "Act 1. The Grand Sheik and the chairman of the Moorish Science Temple of America\n"
    "is in power to make law and enforce laws with the assistance of the Prophet and\n"
    "the Grand Body of the Moorish Science Temple of America.\n"
    "\n"
    "Act 2. All meetings are to be opened and closed promptly according to the\n"
    "Circle Seven and Love, Truth, Peace, Freedom, and Justice must be proclaimed\n"
    "and practiced at all times.\n"
    "\n"
    "Act 6. All members must proclaim their nationality and we are teaching our people\n"
    "their nationality and their divine creed that they may know that they are a part\n"
    "and a partial of this said government.\n"
    "\n"
    "Act 7. All members must promptly attend their meetings and become a part and a\n"
    "partial of all uplifting acts of the Moorish Science Temple of America.\n"
    "\n"
    "This Divine Covenant is from your Holy Prophet Noble Drew Ali,\n"
    "through the guidance of his Father God Allah. Amen.";

const char *PRINCIPLES_DECLARATION =
    "Love, Truth, Peace, Freedom, and Justice — "
    "these are the five divine principles. "
    "They are the foundation of our nation, "
    "the covenant of our people, "
    "the law of our temples. "
    "All who observe these principles are Moorish Americans. "
    "All who observe these principles are a Nation within a Nation.";

int nation_create(MoorishNation *n, const char *grand_sheik_name) {
    if (!n || !grand_sheik_name) return 0;
    memset(n, 0, sizeof(*n));
    strncpy(n->nation_name, "Moorish American", sizeof(n->nation_name) - 1);
    n->founding_date = time(NULL);

    /* Create Grand Sheik */
    sheik_create(&n->grand_sheik, grand_sheik_name);
    n->grand_sheik.principles[LOVE] = 1;
    n->grand_sheik.principles[TRUTH] = 1;
    n->grand_sheik.principles[PEACE] = 1;
    n->grand_sheik.principles[FREEDOM] = 1;
    n->grand_sheik.principles[JUSTICE] = 1;

    /* Initialize covenant chain */
    chain_init(&n->covenants);

    /* Create founding covenant */
    Covenant founding;
    covenant_create(&founding, "The Founding Covenant of the Moorish American Nation");
    covenant_add_article(&founding, "We are a Nation within a Nation.");
    covenant_add_article(&founding, "Our principles are Love, Truth, Peace, Freedom, and Justice.");
    covenant_add_article(&founding, "We proclaim our nationality as Moorish Americans.");
    covenant_add_article(&founding, "We are the descendants of the ancient Moabites.");
    covenant_seal(&founding, &n->grand_sheik);
    covenant_ratify(&founding);

    chain_append(&n->covenants, &founding);

    /* Hash of founding charter */
    covenant_hash_string(DIVINE_CONSTITUTION_TEXT, n->charter_hash);

    return 1;
}

int nation_charter_temple(MoorishNation *n, const char *name, const char *city) {
    if (!n || !name || !city) return 0;
    if (n->temple_count >= 64) return 0;

    Temple t;
    temple_create(&t, name, city);

    /* All new temples observe all 5 principles */
    for (int i = 0; i < PRINCIPLE_COUNT; i++) {
        t.principles[i] = 1;
    }

    /* Hash the charter */
    char charter[512];
    snprintf(charter, sizeof(charter), "CHARTER:%s:%s:%s", name, city, DIVINE_CONSTITUTION_TEXT);
    covenant_hash_string(charter, t.charter_hash);

    n->temples[n->temple_count++] = t;
    return 1;
}

int nation_verify(const MoorishNation *n) {
    if (!n) return 0;

    /* Verify Grand Sheik authority */
    if (!sheik_has_authority(&n->grand_sheik)) return 0;

    /* Verify covenant chain */
    if (!chain_verify(&n->covenants)) return 0;

    /* Verify all temples in good standing */
    for (int i = 0; i < n->temple_count; i++) {
        if (!temple_in_good_standing(&n->temples[i])) return 0;
    }

    return 1;
}

const char *nation_proclamation(void) {
    return
        "Come, all ye Asiatics of America, and hear the truth about your nationality "
        "and birthrights, because you are not Negroes. Learn of your forefathers' "
        "ancient and divine Creed, that you will learn to love instead of hate. "
        "We are trying to uplift fallen humanity. Come and link yourselves with the "
        "families of nations. We honor all the true and Divine Prophets. "
        "\n\n"
        "We, as a clean and pure nation descended from the inhabitants of Africa, "
        "do hereby proclaim our nationality as Moorish Americans. "
        "We are a Nation within a Nation. "
        "Our covenant is Love, Truth, Peace, Freedom, and Justice. "
        "\n\n"
        "This is the Divine Plan of the Ages. "
        "This is the covenant of our forefathers. "
        "This is the law of our temples. "
        "This is the seal of our nation. "
        "\n\n"
        "— Prophet Noble Drew Ali, 1928";
}
