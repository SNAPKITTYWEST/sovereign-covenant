/**
 * sovereign_covenant.h
 *
 * 1928 Moorish Divine Covenant Trust Structure
 * Prophet Noble Drew Ali — Moorish Science Temple of America
 *
 * Love, Truth, Peace, Freedom, Justice
 *
 * "This Divine Covenant is from your Holy Prophet Noble Drew Ali,
 *  through the guidance of his Father God Allah."
 */

#ifndef SOVEREIGN_COVENANT_H
#define SOVEREIGN_COVENANT_H

#include <stdint.h>
#include <stddef.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================
 * CIRCLE SEVEN
 * ====================================================================== */

/** The Circle Seven — sacred symbol of the Moorish Science Temple. */
#define CIRCLE_SEVEN 7

/** The five divine principles. */
typedef enum {
    LOVE    = 0,
    TRUTH   = 1,
    PEACE   = 2,
    FREEDOM = 3,
    JUSTICE = 4
} DivinePrinciple;

/** Number of divine principles. */
#define PRINCIPLE_COUNT 5

/** String names for principles. */
extern const char *principle_name(DivinePrinciple p);

/** The 1928 Divine Constitution principle order. */
extern const DivinePrinciple DIVINE_ORDER[PRINCIPLE_COUNT];

/* ======================================================================
 * HASH — SHA-256 SIMPLIFIED (64-char hex)
 * ====================================================================== */

#define HASH_LEN 64
#define HASH_BUF_LEN (HASH_LEN + 1)

/** Simple hash context. */
typedef struct {
    uint64_t state[8];
    uint64_t count;
    uint8_t  buffer[64];
} CovenantHash;

/** Initialize hash. */
void covenant_hash_init(CovenantHash *ctx);

/** Update hash with data. */
void covenant_hash_update(CovenantHash *ctx, const void *data, size_t len);

/** Finalize hash into out (must be at least HASH_BUF_LEN bytes). */
void covenant_hash_final(CovenantHash *ctx, char out[HASH_BUF_LEN]);

/** Hash a string, write hex to out (must be at least HASH_BUF_LEN bytes). */
void covenant_hash_string(const char *input, char out[HASH_BUF_LEN]);

/* ======================================================================
 * DIVINE PRINCIPLES — THE FIVE PILLARS
 * ====================================================================== */

/** Check if a set of principles satisfies the covenant. */
int principles_satisfied(const int observed[PRINCIPLE_COUNT]);

/** Get the covenant principle declaration. */
const char *covenant_declaration(void);

/* ======================================================================
 * TEMPLE — Subordinate Body
 * ====================================================================== */

#define TEMPLE_NAME_MAX 128
#define TEMPLE_ID_LEN   16

/**
 * A subordinate Temple of the Moorish Science Temple of America.
 * Formed under the covenant of Love, Truth, Peace, Freedom, and Justice.
 */
typedef struct {
    char    id[HASH_LEN + 1];           /** Unique temple identifier. */
    char    name[TEMPLE_NAME_MAX];       /** Temple name. */
    char    city[TEMPLE_NAME_MAX];       /** City. */
    uint32_t member_count;               /** Number of faithful members. */
    int     principles[PRINCIPLE_COUNT]; /** Observed principles (0 or 1). */
    time_t  charter_date;                /** Date chartered under Grand Temple. */
    char    charter_hash[HASH_BUF_LEN];      /** Hash of charter document. */
    int     is_active;                   /** Temple in good standing. */
} Temple;

/** Create a new subordinate temple. */
int temple_create(Temple *t, const char *name, const char *city);

/** Verify a temple's charter against its hash. */
int temple_verify_charter(const Temple *t, const char *charter_text);

/** Check if a temple is in good standing (all principles observed). */
int temple_in_good_standing(const Temple *t);

/** Proclaim temple nationality — "Moorish American". */
const char *temple_proclaim(const Temple *t);

/* ======================================================================
 * GRAND SHEIK — Authority
 * ====================================================================== */

#define SHEIK_NAME_MAX 128

/**
 * The Grand Sheik and Chairman of the Moorish Science Temple of America.
 * "In power to make law and enforce laws with the assistance of the Prophet."
 */
typedef struct {
    char    name[SHEIK_NAME_MAX];    /** Sheik name. */
    time_t  term_start;              /** When authority began. */
    int     principles[PRINCIPLE_COUNT]; /** Observed principles. */
    char    seal_hash[HASH_BUF_LEN];     /** Seal of office hash. */
} GrandSheik;

/** Initialize the Grand Sheik. */
int sheik_create(GrandSheik *s, const char *name);

/** Verify sheik authority (must observe all 5 principles). */
int sheik_has_authority(const GrandSheik *s);

/** Sign a document with sheik authority. */
int sheik_sign(const GrandSheik *s, const char *document, char out_hash[HASH_BUF_LEN]);

/* ======================================================================
 * COVENANT — The Binding Agreement
 * ====================================================================== */

#define COVENANT_TITLE_MAX 256
#define COVENANT_ARTICLES_MAX 32

/**
 * A Divine Covenant — the binding agreement from the Prophet.
 * Not a contract. A covenant. It runs with the people, not against them.
 */
typedef struct {
    char    title[COVENANT_TITLE_MAX];     /** Covenant title. */
    char    articles[COVENANT_ARTICLES_MAX][256]; /** Article text. */
    int     article_count;                  /** Number of articles. */
    int     principles[PRINCIPLE_COUNT];    /** Observed principles. */
    char    grand_sheik_hash[HASH_BUF_LEN];     /** Grand Sheik seal. */
    char    covenant_hash[HASH_BUF_LEN];        /** Hash of this covenant. */
    char    prev_hash[HASH_BUF_LEN];            /** Previous covenant hash (chain). */
    time_t  seal_date;                       /** When covenant was sealed. */
    int     is_ratified;                     /** Has been ratified by Grand Body. */
} Covenant;

/** Initialize a new covenant. */
int covenant_create(Covenant *c, const char *title);

/** Add an article to the covenant. */
int covenant_add_article(Covenant *c, const char *article_text);

/** Seal the covenant — compute hash, set date. */
int covenant_seal(Covenant *c, const GrandSheik *sheik);

/** Chain a new covenant to the previous one. */
int covenant_chain(Covenant *new_c, const Covenant *prev, const char *title, const GrandSheik *sheik);

/** Verify covenant integrity. */
int covenant_verify(const Covenant *c);

/** Ratify the covenant (requires all 5 principles). */
int covenant_ratify(Covenant *c);

/** Check if covenant is fully ratified. */
int covenant_is_ratified(const Covenant *c);

/* ======================================================================
 * COVENANT CHAIN — WORM-Style Integrity
 * ====================================================================== */

#define CHAIN_MAX 16

/**
 * A chain of covenants — each sealed to its predecessor.
 * Write Once Read Many. Tamper-evident.
 */
typedef struct {
    Covenant entries[CHAIN_MAX];
    int      length;
} CovenantChain;

/** Initialize an empty chain. */
void chain_init(CovenantChain *chain);

/** Append a covenant to the chain. */
int chain_append(CovenantChain *chain, Covenant *c);

/** Verify the entire chain. */
int chain_verify(const CovenantChain *chain);

/** Get the head (latest) covenant. */
const Covenant *chain_head(const CovenantChain *chain);

/* ======================================================================
 * NATION WITHIN A NATION
 * ====================================================================== */

/**
 * The Divine Plan of the Ages — Moorish American nationhood.
 * "We have made you a Nation within a Nation."
 */
typedef struct {
    char     nation_name[128];    /** "Moorish American" */
    GrandSheik grand_sheik;       /** Governing authority. */
    CovenantChain covenants;      /** Sealed covenant chain. */
    Temple   temples[64];         /** Subordinate temples. */
    int      temple_count;        /** Number of temples. */
    time_t   founding_date;       /** Date of incorporation. */
    char     charter_hash[HASH_BUF_LEN]; /** Founding charter hash. */
} MoorishNation;

/** Create the Moorish American nation. */
int nation_create(MoorishNation *n, const char *grand_sheik_name);

/** Chartered a new temple under the nation. */
int nation_charter_temple(MoorishNation *n, const char *name, const char *city);

/** Verify the nation's covenant chain. */
int nation_verify(const MoorishNation *n);

/** The nation's proclamation. */
const char *nation_proclamation(void);

/* ======================================================================
 * COVENANT TEXT — The 1928 Divine Constitution
 * ====================================================================== */

/** The full covenant text from the 1928 Divine Constitution. */
extern const char *DIVINE_CONSTITUTION_TEXT;

/** The five principles declaration. */
extern const char *PRINCIPLES_DECLARATION;

#ifdef __cplusplus
}
#endif

#endif /* SOVEREIGN_COVENANT_H */
