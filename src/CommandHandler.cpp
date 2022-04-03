#include "CommandHandler.hpp"
#include "CommandHandler/CwdHandler.hpp"
#include "CommandHandler/UsernameHandler.hpp"
#include "CommandHandler/PasswordHandler.hpp"
#include "CommandHandler/PwdHandler.hpp"
#include "CommandHandler/RenameHandler.hpp"
#include "CommandHandler/RetrHandler.hpp"
#include "CommandHandler/LoginRequiredHandler.hpp"
#include "CommandHandler/MkdHandler.hpp"
#include "CommandHandler/LsHandler.hpp"
#include "CommandHandler/HelpHandler.hpp"
#include "CommandHandler/QuitHandler.hpp"
#include "CommandHandler/DeleHandler.hpp"

#include "UserManager.hpp"

using namespace std;

CommandHandler::CommandHandler(UserConfig user_config)
{
    command_handler_collection[USER_COMMAND] = new UsernameHandler();
    command_handler_collection[PASS_COMMAND] = new PasswordHandler();
    command_handler_collection[PWD_COMMAND] = new LoginRequiredHandler(new PwdHandler());
    command_handler_collection[MKD_COMMAND] = new LoginRequiredHandler(new MkdHandler());
    command_handler_collection[DELE_COMMAND] = new LoginRequiredHandler(new DeleHandler());
    command_handler_collection[LS_COMMAND] = new LoginRequiredHandler(new LsHandler());
    command_handler_collection[CWD_COMMAND] = new LoginRequiredHandler(new CwdHandler());
    command_handler_collection[RENAME_COMMAND] = new LoginRequiredHandler(new RenameHandler());
    command_handler_collection[RETR_COMMAND] = new LoginRequiredHandler(new RetrHandler());
    command_handler_collection[HELP_COMMAND] = new LoginRequiredHandler(new HelpHandler());
    command_handler_collection[QUIT_COMMAND] = new LoginRequiredHandler(new QuitHandler());
}

CommandHandler::~CommandHandler()
{
}

vector<string> CommandHandler::do_command(int user_socket, char *command)
{
    vector<string> command_parts = parse_command(command);

    User *user = UserManager::get_instance()->get_user_by_socket(user_socket);

    if(command_handler_collection.find(command_parts[COMMAND]) == command_handler_collection.end()) {
        return {SYNTAX_ERROR, EMPTY};
    }

    return command_handler_collection[command_parts[COMMAND]]->handle_command(command_parts, user);

}
