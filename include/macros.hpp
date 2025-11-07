#ifndef MACROS_HPP
#define MACROS_HPP
#include <dpp/dpp.h>

/* All the macros this code might need for convenience */

/* type shortcuts */
#define sstr std::string
#define npos sstr::npos
#define sstream std::istringstream
#define svec std::vector<sstr>
#define ull unsigned long long

/* split string into array of strings by token */
#define split_s(str, delim) ([](const std::string& s, char d){ \
    svec tokens; \
    sstr token; \
    sstream iss(s); \
    while (std::getline(iss, token, d)) tokens.push_back(token); \
    return tokens; \
}(str, delim))

/* check if a character is a digit */
#define IS_DIGIT(c) (c >= '0' && c <= '9')

/* channel and guild */
#define BOT_CHANNEL_ID  1429064036896608367
#define MX_GUILD_ID     1429062699488378964

/* command shortcuts */
#define SEND_MSG(S) bot.message_create(dpp::message(BOT_CHANNEL_ID, S))

/* bot intents */
#define INTENTS dpp::i_default_intents | dpp::i_message_content | dpp::i_guild_members

/* prints */
#define DEBUG(s)    std::cout << "\x1b[35;1m[DEBUG]\x1b[0;31m " << s << "\x1b[0m\n"
#define INFO(s)     std::cout << "\x1b[35;1m[INFO]\x1b[0;32m " << s << "\x1b[0m\n"

#endif
