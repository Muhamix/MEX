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

/* ANSI codes */

/* colors */
#define BLACK   "\x1b[30m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define WHITE   "\x1b[37m"

/* background colors */
#define BLACK_BG    "\x1b[40m"
#define RED_BG      "\x1b[41m"
#define GREEN_BG    "\x1b[42m"
#define YELLOW_BG   "\x1b[43m"
#define BLUE_BG     "\x1b[44m"
#define MAGENTA_BG  "\x1b[45m"
#define CYAN_BG     "\x1b[46m"
#define WHITE_BG    "\x1b[47m"

/* styles */
#define BOLD          "\x1b[1m"
#define DIM           "\x1b[2m"
#define ITALIC        "\x1b[3m"
#define UNDERLINE     "\x1b[4m"
#define BLINK         "\x1b[5m"
#define STRIKETHROUGH "\x1b[9m"

/* reset */
#define RESET "\x1b[0m"

/* prints */
#define DEBUG(s) std::cout << MAGENTA << BOLD << "[DEBUG] " << RESET << RED << s << RESET << std::endl
#define INFO(s) std::cout << MAGENTA << BOLD << "[INFO] " << RESET << GREEN << s << RESET << std::endl

#endif
