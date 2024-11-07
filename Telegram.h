#pragma once
#include "include.h"

class Telegram
{
public:
	static void Create_Inline_Button(std::string text, std::string callback, std::vector<TgBot::InlineKeyboardButton::Ptr>& vec);
	static void Send_Message(std::string data, TgBot::Message::Ptr ptr_message, TgBot::Bot& bot);
	static void Send_Message(std::string data, TgBot::InlineKeyboardMarkup::Ptr keyboard, TgBot::Message::Ptr ptr_message, TgBot::Bot& bot);
	static std::string Check_Access(std::string chat_member_id);

	// Debug-Help function
	static std::string cp1251_to_utf8(const char* str);
	static std::string Prepare_MSG(std::string msg);
	static std::string Merge_to_String(std::vector<std::string> vec);
};

