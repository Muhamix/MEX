#ifndef MACROS_HPP
#define MACROS_HPP

/* All the macros this code might need for convenience */

#define PLACE_HOLDER_ID 000000000000000000

#define BOT_CHANNEL PLACE_HOLDER_ID
#define MX_GUILD PLACE_HOLDER_ID

#define SEND_MSG(S) bot.message_create(dpp::message(BOT_CHANNEL, S))
#define CMD_R(c) bot.on_message_create([&bot](const dpp::message_create_t &e) {\
        const std::string msg = e.msg.content;\
        if (e.msg.channel_id == BOT_CHANNEL && e.msg.guild_id == MX_GUILD && !msg.compare(0, 1, "$")) {\
            c\
        }\
    })

#endif
