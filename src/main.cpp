#include <dpp/dpp.h>
#include <dpp/fmt/format.h>
#include <dpp/nlohmann/json.hpp>
#include <iomanip>
#include <sstream>
#include <dpp/discordevents.h>
#include <dpp/message.h>
#include <templatebot/templatebot.h>

using json = nlohmann::json;

int main(int argc, char const *argv[])
{
    json configdocument;
    std::ifstream configfile("../config.json");
    configfile >> configdocument;

    /* Setup the bot */
    dpp::cluster bot(configdocument["token"], dpp::i_default_intents, 1);

    /* Log event */
    bot.on_log([&bot](const dpp::log_t &event) {
	if (event.severity >= dpp::ll_debug)
	{
		std::cout << dpp::utility::current_date_time() << " [" << dpp::utility::loglevel(event.severity) << "] " << event.message << "\n";
	}
    });

    /* Use the on_message_create event to look for commands */
    bot.on_message_create([&bot](const dpp::message_create_t &event) {

	std::stringstream ss(event.msg->content);
	std::string command;
	ss >> command;

	if (command == "!hello")
	{
		bot.message_create(dpp::message(event.msg->channel_id, "Hello to you too."));
	}

    });

    /* Start bot */
    bot.start(false);
    return 0;
}

