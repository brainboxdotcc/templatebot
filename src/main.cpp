#include <templatebot/templatebot.h>
#include <sstream>
namespace fs = std::filesystem;

/* When you invite the bot, be sure to invite it with the
 * scopes 'bot' and 'applications.commands', e.g.
 * https://discord.com/oauth2/authorize?client_id=940762342495518720&scope=bot+applications.commands&permissions=139586816064
 */

using json = nlohmann::json;

int main(int argc, char const *argv[])
{
    if(!fs::exists("../config.json")) {
        std::cout << canonical(fs::path("..")).append("config.json").string() << " does not exist!" << std::endl;
        return 1;
    }

    json configdocument;
    std::ifstream configfile("../config.json");
    configfile >> configdocument;

    /* Setup the bot */
    dpp::cluster bot(configdocument["token"]);

    /* Output simple log messages to stdout */
    bot.on_log(dpp::utility::cout_logger());

    /* Handle slash command */
    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
         if (event.command.get_command_name() == "ping") {
            event.reply("Pong!");
        }
    });

    /* Register slash command here in on_ready */
    bot.on_ready([&bot](const dpp::ready_t& event) {
        /* Wrap command registration in run_once to make sure it doesnt run on every full reconnection */
        if (dpp::run_once<struct register_bot_commands>()) {
            bot.global_command_create(dpp::slashcommand("ping", "Ping pong!", bot.me.id));
        }
    });

    /* Start the bot */
    bot.start(false);

    return 0;
}
