#include "include.h"


int main()
{
    system("chcp 1251 > nul"); // ●
    TgBot::Bot bot(tkn_tg::token);

    bot.getApi().sendMessage("621963054", "/start");

    bot.getEvents().onCommand("cmd", [&bot](TgBot::Message::Ptr message)
    {
        bot.getApi().sendMessage(message->chat->id, "/cmd\n/forward\n/start");
    });
    // Take client-id and api-key
    bot.getEvents().onCommand("forward", [&bot](TgBot::Message::Ptr message)
        {
            //bot.getApi().sendMessage(message->chat->id, "Введите ваш client-id");
            //Sleep(100); // ? need wait response
            //std::string client_id = message->text;
            //bot.getApi().sendMessage(message->chat->id, "Введите ваш Api-Key");
            //Sleep(100); // ? need wait response
            //std::string api_key = message->text;
            //message->forwardFrom
            // on any message save in client_id
            //
        });
    // 

    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message)
        {
            std::vector<std::string> menu = {
            "[1] Вывести заказы в ожидающие подтверждения.",
            "[2] Вывести заказы в ожидающие доставки в ПВЗ.",
            "[3] Вывести заказы в доставке.",
            "[4] Статус доставки по номеру отгрузки.\n",

            "[9] Глобальные настройки."
            };
            std::string str = "";
            for (int i = 0; i < menu.size(); i++)
            {
                str += Telegram::Prepare_MSG(menu[i]);
                str += '\n';
            }

            TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
            std::vector<TgBot::InlineKeyboardButton::Ptr> row;

            Telegram::Create_Inline_Button("[1]", "print_awaiting_packaging", *&row);
            Telegram::Create_Inline_Button("[2]", "print_awaiting_deliver", *&row);
            Telegram::Create_Inline_Button("[3]", "print_delivering", *&row);
            Telegram::Create_Inline_Button("[4]", "Get_info_by_num", *&row);
            keyboard->inlineKeyboard.push_back(row);

            std::vector<TgBot::InlineKeyboardButton::Ptr> row1;
            Telegram::Create_Inline_Button("[9]", "Set_Settings", *&row1);
            keyboard->inlineKeyboard.push_back(row1);


            // Send message with inline keyboard
            bot.getApi().sendMessage(message->chat->id, str, false, 0, keyboard);
        });

    
    bot.getEvents().onCallbackQuery([&bot](TgBot::CallbackQuery::Ptr query)
    {
            if (query->data == "print_awaiting_packaging")
            {
                nlohmann::json json_response = Ozon::Get_Info_By_Status("awaiting_packaging");
                if (json_response["result"]["count"] == 0)
                    bot.getApi().sendMessage(query->message->chat->id, Telegram::Prepare_MSG("Заказов ожидающих подтверждения нет."));
                else
                {       // Add inline button
                    for (int i = 0; i < json_response["result"]["postings"].size(); i++)
                    {
                        std::string msg = Telegram::Prepare_MSG("Заказ #") + std::to_string(i+1) + '\n';
                        double summary_price = 0;
                        msg += Telegram::Prepare_MSG("Номер отгрузки: ");
                        msg += (std::string)json_response["result"]["postings"][i]["posting_number"] + '\n';
                        msg += Telegram::Prepare_MSG("Состав:") + '\n';
                        for (int j = 0; j < json_response["result"]["postings"][i]["products"].size(); j++)
                        {
                            // 1) quantity - Name - Price \n
                            msg += std::to_string(j+1) + ") ";
                            msg += std::to_string((int)json_response["result"]["postings"][i]["products"][j]["quantity"]);
                            msg += Telegram::Prepare_MSG(" шт.");
                            msg += " - " + (std::string)json_response["result"]["postings"][i]["products"][j]["name"];
                            msg += Telegram::Prepare_MSG(" - Цена:") + (std::string)json_response["result"]["postings"][i]["products"][j]["price"];
                            summary_price += ((double)json_response["result"]["postings"][i]["products"][j]["quantity"] * std::stod((std::string)json_response["result"]["postings"][i]["products"][j]["price"]));
                            msg += '\n';
                        }
                        msg += Telegram::Prepare_MSG("Общая сумма заказа: ") + std::to_string(summary_price);
                        
                        // make func
                        TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
                        std::vector<TgBot::InlineKeyboardButton::Ptr> row; row.clear();
                        Telegram::Create_Inline_Button(Telegram::Prepare_MSG("Готов к отгрузке"), "switch_to_awaiting_deliver", *&row);
                        keyboard->inlineKeyboard.push_back(row);
                        // 

                        bot.getApi().sendMessage(query->message->chat->id, msg, false, 0, keyboard);
                    }
                }
                bot.getApi().answerCallbackQuery(query->id);
            }

            if (query->data == "print_awaiting_deliver" || query->data == "show_next_day")
            {
                nlohmann::json json_response = Ozon::Get_Info_By_Status("awaiting_deliver");
                if (json_response["result"]["count"] == 0)
                    bot.getApi().sendMessage(query->message->chat->id, Telegram::Prepare_MSG("Заказов ожидающих отгрузки в ПВЗ нет."));
                else
                {
                    std::string Founded_Date = Settings::Get_Date_Today(query->data == "print_awaiting_deliver" ? 0 : 1);
                    std::string msg = Telegram::Prepare_MSG("Отгрузка на ") + Founded_Date + '\n';

                    std::set<std::string> dates;
                    for (int i = 0; i < json_response["result"]["postings"].size(); i++)
                        dates.insert(((std::string)json_response["result"]["postings"][i]["shipment_date"]).erase(10, 10));

                    int count = 1;




                    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
                    std::vector<TgBot::InlineKeyboardButton::Ptr> row;

                    // Check f tomorow availble but actualy not
                    if (dates.size() > 1)
                    {
                        Telegram::Create_Inline_Button(Telegram::Prepare_MSG("Отгрузка на завтра"), "show_next_day", *&row);
                        keyboard->inlineKeyboard.push_back(row);
                    }

                    for (int i = 0; i < json_response["result"]["postings"].size(); i++)
                    {
                        if (((std::string)json_response["result"]["postings"][i]["shipment_date"]).erase(10, 10) != Founded_Date)
                            continue;
                        msg += std::to_string(count++) + ") ";
                        msg += json_response["result"]["postings"][i]["posting_number"];
                        int summary_price = 0;
                        int quantity = 0;
                        for (int j = 0; j < json_response["result"]["postings"][i]["products"].size(); j++)
                        {
                            quantity += ((double)json_response["result"]["postings"][i]["products"][j]["quantity"]);
                            summary_price += std::stod((std::string)json_response["result"]["postings"][i]["products"][j]["price"]);
                        }
                        msg += " - " + std::to_string(quantity) + Telegram::Prepare_MSG("шт. - ");
                        msg += Telegram::Prepare_MSG("Цена: ") + std::to_string(summary_price);
                        msg += '\n';
                    }

                    bot.getApi().sendMessage(query->message->chat->id, msg, 0, false, keyboard);
                }



                bot.getApi().answerCallbackQuery(query->id);
            }

            if (query->data == "print_delivering")
            {
                try
                {
                    nlohmann::json json_response = Ozon::Get_Info_By_Status("delivering");

                    if (json_response["result"]["count"] == 0)
                        bot.getApi().sendMessage(query->message->chat->id, Telegram::Prepare_MSG("Заказов в доставке нет."));

                    std::vector<std::string> send = {
                        Telegram::Prepare_MSG("Номер отправления:\n"),
                        "", // 1
                        Telegram::Prepare_MSG("\nНаименование проданного товара:\n"),
                        "", // 3
                        Telegram::Prepare_MSG("\nЦена проданного товара:\n"),
                        "", // 5
                        Telegram::Prepare_MSG("\nДата отгрузки:\n"),
                        "", // 7
                    };
                    for (int i = 0; i < json_response["result"]["postings"].size(); i++)
                    {
                        send[1] = json_response["result"]["postings"][i]["posting_number"];
                        send[3] = json_response["result"]["postings"][i]["products"][0]["name"];
                        send[5] = json_response["result"]["postings"][i]["products"][0]["price"]; // multiply order
                        send[7] = ((std::string)json_response["result"]["postings"][i]["shipment_date"]).erase(10, 10);

                        std::string response = "";
                        for (int i = 0; i < send.size(); i++)
                            response += send[i];

                        bot.getApi().sendMessage(query->message->chat->id, response);
                    }
                    
                    bot.getApi().answerCallbackQuery(query->id);
                }
                catch (const std::exception& e) {
                    std::cerr << "\n Callback print_delivering.\nCaught exception: " << e.what() << std::endl;
                }
                
                bot.getApi().answerCallbackQuery(query->id);
            }
            if (query->data == "Get_status_by_num") {}
            if (query->data == "Get_info_by_num")
            {
                // Не работает так как любой пользователь может изменить глобальную переменную для другого пользователя
                // 
                //bot.getApi().sendMessage(query->message->chat->id, Telegram::Prepare_MSG("Введите номер огрузки"));
                // Global var. Any user can change for another user
                //StateVar::Check_by_num = true;
            }
            if (query->data == "Set_Settings")
            {
                bot.getApi().sendMessage(query->message->chat->id, "Not completed...");
                bot.getApi().answerCallbackQuery(query->id);
            }
            if (query->data == "switch_to_awaiting_deliver")
            {
                std::string text = query->message->text; std::string str_num = "";
                for (int i = 12; i < text.size(); i++)
                {
                    if (text[i] == '\n')
                        break;
                    else
                        str_num += text[i];
                }
                int num = std::stoi(str_num) - 1;

                nlohmann::json json_response = Ozon::Get_Info_By_Status("awaiting_packaging");

                std::string post_num = json_response["result"]["postings"][num]["posting_number"];

                nlohmann::json response = Ozon::POST_Request("https://api-seller.ozon.ru/v4/posting/fbs/ship", Ozon::Make_Ready_to_Deliver(post_num));
                std::string msg = Telegram::Prepare_MSG("Заказ #") + post_num + Telegram::Prepare_MSG(" успешно подготовлен к отгрузке");
                bot.getApi().sendMessage(query->message->chat->id, msg);

                bot.getApi().answerCallbackQuery(query->id);
            }
    });
    

    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        if (StateVar::Check_by_num)
        {
            bot.getApi().sendMessage(message->chat->id, Ozon::Get_Status_By_Number(message->text));
            StateVar::Check_by_num = false;
        }
        });


    try {
        bot.getApi().deleteWebhook(true);
        std::cout << "Bot username: " << bot.getApi().getMe()->username.c_str() << std::endl;
        TgBot::TgLongPoll longPoll(bot);
        while (true)
        {
            std::cout << "Long poll started\n";
            longPoll.start();
        }
    }
    catch (const TgBot::TgException& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    return 0;
}