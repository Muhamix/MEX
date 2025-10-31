#include <dpp/dpp.h>
#include "token.hpp"
#include "macros.hpp"

int main(void) {
    /* create bot */
    dpp::cluster bot(TOKEN);

    /* initialise bot */
    bot.on_log(dpp::utility::cout_logger());
    

    /* bot is ready */
    
    SEND_MSG("I'm online!");
    CMD_R(
        if (msg.find("ping")) e.reply("pong!");
    );

    /* finished executing */
    bot.start(dpp::st_wait);
    return 0;
}
