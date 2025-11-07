#include <dpp/dpp.h>
#include "token.hpp"
#include "macros.hpp"


// TODO: ADD BAN AND HELP COMMANDS


/* get user ID from mention */
ull mention_to_id(sstr mention) {

    /* discord mentions are not @username
     * a discord mention can be one of these:
     * <@ID> for normal mentions 
     * <@!ID> for users with nicknames
     * we check for both */

    /* check if the string starts with <@ */
    if (!mention.rfind("<@", 0)) {

        /* ID starts at index 2 */
        sstr id = mention.substr(2);

        /* check if it's a nickname mention */
        if (id[0] == '!') id = id.substr(1); // consume the !
        
        /* remove the trailing > */
        id.pop_back();

        /* convert to unsigned long long and return*/
        return std::stoull(id);
    }

    /* not a mention, error */
    DEBUG("expected mention, got " << mention << " instead");
    return 0;
}

int main(void) {

    /* create bot */
    dpp::cluster bot(TOKEN, INTENTS);

    /* initialise bot */
    bot.on_log(dpp::utility::cout_logger());
    
    /* bot is ready */ 
    SEND_MSG("I'm online!");
    std::cout << "\x1b[32;1mOnline\x1b[0m\n";

    /* event handlers */
    bot.on_message_create([&bot](const dpp::message_create_t &e) {

	    /* initialise channel and guild */
    	const auto MX_G = dpp::find_guild(MX_GUILD_ID);
    	const auto BOT_C = dpp::find_channel(BOT_CHANNEL_ID);

        /* make sure the guild and channel aren't null */
        if (!(MX_G && BOT_C)) {
            
            DEBUG("guild or channel is null");

            return;
        }
        
        /* macro > constant, in this case */
#       define content e.msg.content

        /* print received message, mostly for debugging */
        INFO("received message: \x1b[1m" << content);

        /* check if the message is a command */
        if (content[0] != '$') return;

        /* make sure the command is in the designated channel */
        if (e.msg.channel_id != BOT_CHANNEL_ID) {

            /* log */
            INFO("attempted to call a command from an undesignated channel");

            e.reply("I only listen to commands from <#" + std::to_string(BOT_CHANNEL_ID) + ">");

            return;
        }

        /* get event creator */
        const auto &tmp = MX_G->members.find(e.msg.author.id);

        /* make sure user exists */
        if (tmp == MX_G->members.end()) {
            
            DEBUG("event author not found");

            return;
        }

        /* save user */
        dpp::guild_member &sender = tmp->second;
        dpp::user *user = sender.get_user();

        /* make sure the user isn't a bot */
        if (user->is_bot()) {

            DEBUG("message author is a bot");

            return;
        }

        /* get permissions */
        ull perms = MX_G->permission_overwrites(MX_G->base_permissions(user), user, BOT_C);

        /* make sure it was sent in this specific channel in this specific server and starts with the command prefix, $ */
        if (e.msg.channel_id == BOT_CHANNEL_ID && e.msg.guild_id == MX_GUILD_ID && !content.compare(0, 1, "$")) {

            /* split content by spaces, makes it easier to manage the command */
            auto cmd = split_s(content, ' ');

            /* ping command */
            if (cmd[1] == "ping") {
                e.reply("pong!");
                return;
            }

            /* kick command */
            if (cmd[1] == "kick") {

                /* check for syntax, you need 3 objects, "$", "kick", "username" */
                if (cmd.size() != 3) {

                    e.reply("Make sure you're using correct syntax:\n```$ kick @user```\n**OR**\n```$ kick ID```");

                    return;
                }

                /* check for perms */
                if (perms & dpp::p_kick_members) {
                    
                    /* first, we need to check whether it's a ping or a user id */
                    
                    /* look for user id */
                    if (IS_DIGIT(cmd[2][0])) {

                        ull id = std::stoull(cmd[2]);

                        /* check if the id belongs to the owner of the server */
                        if (id == MX_G->owner_id) {

                            /* log */
                            INFO("attempted to kick owner");

                            e.reply("I cannot kick the owner.");

                            return;
                        }

                        /* get member to kick */
                        const auto kick = MX_G->members.find(id);

                        /* make sure the user exists within the server */
                        if (kick == MX_G->members.end()) {
                            
                            /* log */
                            INFO("attempted to kick non-member user");

                            e.reply("Make sure the user you want to kick is in the server.");

                            return;
                        }

                        /* kick member */
                        bot.guild_member_kick(MX_GUILD_ID, id);
                    }
                }
                
                /* author doesn't have necessary permissions */
                else {
                    
                    /* log */
                    INFO("unqualified member attempted to kick");

                    e.reply("You do not have the necessary permissions to kick a member");

                    return;
                }
            }
        }

        /* unknown command */
        e.reply("Unknown command, maybe try\n```$ help```\nfor a list of commands.");
        INFO("attempted to invoke unknown command: \x1b[1m" << content);
    });

    /* keep the bot running and listen for events */
    bot.start(dpp::st_wait);

    /* unneeded, but why not? */
    return 0;
}
