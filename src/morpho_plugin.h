#pragma once

#include "eth_internals.h"
#include "eth_plugin_interface.h"
#include <string.h>

// Number of decimals used when the token wasn't found in the Crypto Asset List.
#define DEFAULT_DECIMAL WEI_TO_ETHER
#define ETH_DECIMAL     WEI_TO_ETHER

// Enumeration of the different selectors possible.
// Should follow the exact same order as the array declared in main.c
typedef enum {
    COMPOUND_SUPPLY,
    COMPOUND_REPAY,
    COMPOUND_WITHDRAW,
    COMPOUND_BORROW,
    COMPOUND_CLAIM_REWARDS,
    AAVE_SUPPLY,
    AAVE_REPAY,
    AAVE_WITHDRAW,
    AAVE_BORROW,
    AAVE_CLAIM_REWARDS,
    COMMON_CLAIM,
} selector_t;

// Number of selectors defined in this plugin. Should match the enum `selector_t`.
#define NUM_SELECTORS 11

extern const uint32_t MORPHO_SELECTORS[NUM_SELECTORS];

// Shared global memory with Ethereum app. Must be at most 5 * 32 bytes.
// 124 / 160
typedef struct __attribute__((__packed__)) context_t {
    uint8_t pool_token_address[ADDRESS_LENGTH];
    uint8_t token_address[ADDRESS_LENGTH];
    char token_ticker[MAX_TICKER_LEN];
    uint8_t token_decimals;
    uint8_t amount[INT256_LENGTH];
    uint8_t user_address[ADDRESS_LENGTH];
    uint16_t next_param;
    uint8_t trade_for_morpho;
    uint8_t on_behalf;
    uint8_t token_warning;
    selector_t selectorIndex;  // method id
} context_t;

typedef struct token_info_t {
    const uint8_t collateral_address[ADDRESS_LENGTH];
    const char ticker[MAX_TICKER_LEN];  // ticker and decimal of the original token corresponding to
                                        // collateral address.
    const uint8_t decimals;
} token_info_t;

typedef enum {
    _POOL_TOKEN_ADDRESS_SUPPLY_REPAY,
    _ON_BEHALF,
    _AMOUNT_SUPPLY_REPAY,
    _SUPPLY_REPAY_IGNORED,
} supply_repay_parameters;

typedef enum {
    _POOL_TOKEN_ADDRESS_WITHDRAW_BORROW,
    _AMOUNT_WITHDRAW_BORROW,
    _WITHDRAW_BORROW_IGNORED,
} withdraw_borrow_parameters;

typedef enum {
    OFFSET_C_TOKEN_ADDRESSES,
    _TRADE_FOR_MORPHO_TOKEN,
    CLAIM_REWARDS_IGNORED,
} claim_rewards_parameters;

typedef enum {
    _ACCOUNT,
    CLAIM_IGNORED,
} claim_parameters;

// Piece of code that will check that the above structure is not bigger than 5 * 32. Do not remove
// this check.
_Static_assert(sizeof(context_t) <= 5 * 32, "Structure of parameters too big.");

void handle_provide_parameter(void *parameters);
void handle_query_contract_ui(void *parameters);
void handle_init_contract(void *parameters);
void handle_finalize(void *parameters);
void handle_provide_token(void *parameters);
void handle_query_contract_id(void *parameters);