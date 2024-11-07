#include "Telegram.h"

void Telegram::Create_Inline_Button(std::string text, std::string callback, std::vector<TgBot::InlineKeyboardButton::Ptr>& vec)
{
    TgBot::InlineKeyboardButton::Ptr button(new TgBot::InlineKeyboardButton);
    button->text = text;
    button->callbackData = callback;
    vec.push_back(button);
}

void Telegram::Send_Message(std::string data, TgBot::Message::Ptr ptr_message, TgBot::Bot& bot)
{
    bot.getApi().sendMessage(ptr_message->chat->id, data);
}
void Telegram::Send_Message(std::string data, TgBot::InlineKeyboardMarkup::Ptr keyboard, TgBot::Message::Ptr ptr_message, TgBot::Bot& bot)
{
    bot.getApi().sendMessage(ptr_message->chat->id, data, false, 0, keyboard);
}
// Move to other class
std::string Telegram::Merge_to_String(std::vector<std::string> vec)
{
    std::string result = "";
    for (int i = 0; i < vec.size(); i++)
    {
        //result += vec[i];
        result += Telegram::cp1251_to_utf8(&vec[i][0]);
        result += '\n';
    }

    return result;
}

// From someone github
std::string Telegram::cp1251_to_utf8(const char* str)
{
    std::string res;
    WCHAR* ures = NULL;
    char* cres = NULL;

    int result_u = MultiByteToWideChar(1251, 0, str, -1, 0, 0);
    if (result_u != 0)
    {
        ures = new WCHAR[result_u];
        if (MultiByteToWideChar(1251, 0, str, -1, ures, result_u))
        {
            int result_c = WideCharToMultiByte(CP_UTF8, 0, ures, -1, 0, 0, 0, 0);
            if (result_c != 0)
            {
                cres = new char[result_c];
                if (WideCharToMultiByte(CP_UTF8, 0, ures, -1, cres, result_c, 0, 0))
                {
                    res = cres;
                }
            }
        }
    }

    delete[] ures;
    delete[] cres;

    return res;
}
// Для удобства написания кода, если отправить русские символы в сообщении
// или inline кнопке, программа крашится
std::string Telegram::Prepare_MSG(std::string msg)
{
    return Telegram::cp1251_to_utf8(&msg[0]);
}
std::string Telegram::Check_Access(std::string chat_member_id)
{
    for (int i = 0; i < WhiteList::id.size(); i++)
        if (WhiteList::id[i].first == chat_member_id)
            return WhiteList::id[i].second;
    return "Undefined";
}