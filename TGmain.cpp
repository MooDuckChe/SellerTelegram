#include "include.h"

// Inactive. Need fix
std::vector<std::string> Delivering_Send_Info(nlohmann::json request, std::vector<std::string>& response)
{
    response.push_back("Номер отправления:");
    response.push_back(request["result"]["postings"][0]["posting_number"]);
    response.push_back("Номер акта:");
    response.push_back(request["result"]["postings"][0]["order_number"]);
    response.push_back("Наименование проданного товара:");
    std::string Brainfuck_name = request["result"]["postings"][0]["products"][0]["name"];
    std::cout << Brainfuck_name << std::endl;
    response.push_back("Цена проданного товара:");
    response.push_back(request["result"]["postings"][0]["products"][0]["price"]);
    response.push_back("Дата отгрузки:");
    std::string date = request["result"]["postings"][0]["shipment_date"];
    response.push_back(date.erase(date.length() - 10, 10));

    return response;
}

void Out_Info(nlohmann::json boby)
{
    // future inline button, 10 strs in msg. And after ten, make next page

    for (int i = 0; i < boby["result"]["count"]; i++)
    {
        std::cout << "#" << boby["result"]["postings"][i]["posting_number"] << std::endl;

        for (int j = 0; j < boby["result"]["postings"][i]["products"].size(); j++)
            std::cout << "Product " << boby["result"]["postings"][i]["products"][j]["name"] << std::endl;

        std::cout << std::endl;
    }
}





void Get_Info_Orders(bool& sort, std::string status)
{
    // Сборка
    std::string url = "https://api-seller.ozon.ru/v3/posting/fbs/unfulfilled/list";
    // awaiting_packaging
    POST_Request(url, Check_Status_Order(Take_Past_Time(), Take_Future_Time(), sort, status));
}

nlohmann::json Check_Status_Order(std::string date_from, std::string date_to, bool sort, std::string status)
{
    // 2024-01-01T00:00:01Z
    // sorting ? ASC : DESC;
    // Global set? /revers
    // asc — по возрастанию,
    // desc — по убыванию.
    // std::string
    // Формат: YYYY-MM-DDThh:mm:ssZ. Пример: 2020-01-31T08:30:59Z.
    nlohmann::json json_obj =
    {
        {"dir", sort ? "DESC" : "ASC"},
        {"filter",
            {
                {"cutoff_from",        date_from },
                {"cutoff_to",          date_to   },
                {"delivery_method_id", nlohmann::json::array()},
                {"provider_id",        nlohmann::json::array()},
                {"status",             status},
                {"warehouse_id",       nlohmann::json::array()}
            }
        },
        {"limit", 100},
        {"offset", 0},
        {"with",
            {
                {"analytics_data", false},
                {"barcodes", false},
                {"financial_data", false},
                {"translit", false}
            }
        }
    };
    return json_obj;
}

nlohmann::json Make_Array_Posting_Number(std::vector<std::string> vec_number)
{
    nlohmann::json arr_number;
    for (int i = 0; i < vec_number.size(); i++)
        arr_number.push_back(vec_number[i]);

    nlohmann::json json_obj =
    {
        {"posting_number", arr_number}
    };
    return json_obj;
}

//nlohmann:json Out_all_Info()
//{
//    nlohmann::json json_obj = {
//        "dir": "ASC",
//            "filter" : {
//            "delivery_method_id": [
//                "string"
//            ] ,
//                "last_changed_status_date" : {
//                "from": "2023-11-03T11:47:39.878Z",
//                    "to" : "2023-11-03T11:47:39.878Z"
//            },
//                "order_id" : 0,
//                "provider_id" : [
//                    "string"
//                ] ,
//                "since" : "2023-11-03T11:47:39.878Z",
//                "status" : "awaiting_packaging",
//                "to" : "2023-11-03T11:47:39.878Z",
//                "warehouse_id" : [
//                    "string"
//                ]
//        },
//            "limit": 100,
//            "offset" : 0,
//            "with" : {
//            "analytics_data": false,
//                "barcodes" : false,
//                "financial_data" : false,
//                "translit" : false
//        }
//    };
//    return json_obj;
//}

void Print_Json(nlohmann::json r)
{
    std::cout << "\n\nResponse: " << std::setw(4) << r << std::endl << std::endl;
}

void Main_Menu(int& choose)
{
    system("chcp 1251 > nul");
    std::vector<std::string> menu = {
        "[1] Вывести информацию о всех заказах.",
        "[2] Вывести заказы в ожидании.",
        "[3] Вывести заказы в сборке.",
        "[4] Вывести заказы в доставке.",
        "[5] Вывести доставленные заказы.",

        "[5] Вывести json запрос.",
        "[9] Глобальные настройки.",
        "\n[0] Выход.\n"
    };

    for (int i = 0; i < menu.size(); i++)
        std::cout << menu[i] << std::endl;

    std::cout << "Выбор: ";
    std::cin >> choose;

    switch (choose)
    {
    case 1:
    {
        break;
    }
    case 2:
    {
        bool sort2;
        std::cout << "Sort true/false: ";
        std::cin >> sort2;
        Get_Info_Orders(*&sort2, "awaiting_packaging");
        break;
    }
    case 3:
    {
        bool sort3;
        std::cout << "Sort true/false: ";
        std::cin >> sort3;
        Get_Info_Orders(*&sort3, "awaiting_deliver");
        break;
    }
    case 4:
    {
        bool sort4;
        std::cout << "Sort true/false: ";
        std::cin >> sort4;
        Get_Info_Orders(*&sort4, "delivering");
        break;
    }
    case 5:
    {
        break;
    }
    case 6:
    {
        break;
    }
    }

}

std::vector<std::string> all_info;

void TEst(std::vector<int>& vec)
{
    vec.push_back(1);
}


void fool() {
    //std::vector<int> test;
    //TEst(*&test);

    //bot.getToken()
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message)
        {
            bot.getApi().sendMessage(message->chat->id, "/start\n/button\n/menu\n/MarSerg\n/check\n/api");
        });


    bot.getEvents().onCommand("menu", [&bot](TgBot::Message::Ptr message)
        {
            std::vector<std::string> menu = {
            "[1] Вывести информацию о всех заказах.",
            "[2] Вывести заказы в ожидании.",
            "[3] Вывести заказы в сборке.",
            "[4] Вывести заказы в доставке.",
            "[5] Вывести доставленные заказы.\n",

            "[8] Вывести json запрос.",
            "[9] Глобальные настройки.\n",

            "[0] Выход.\n"
            };

            std::vector<std::string> code_menu = {
                "print_all_orders",
                "print_awaiting_packaging",
                "print_awaiting_deliver",
                "print_delivering",
                "print_completed_orders",

                "print_json_body",
                "Set_Settings",

                "Exit"
            };

            std::string str = "";

            for (int i = 0; i < menu.size(); i++)
            {
                str += cp1251_to_utf8(&menu[i][0]);
                str += '\n';
            }

            TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);

            int kount = 0;
            // Добавление 8 кнопок в ряд
            std::vector<TgBot::InlineKeyboardButton::Ptr> row;
            for (int i = 1; i < 6; i++)
            {
                TgBot::InlineKeyboardButton::Ptr button(new TgBot::InlineKeyboardButton);
                button->text = "[" + std::to_string(i) + "]";
                button->callbackData = code_menu[kount++];
                row.push_back(button);
            }
            keyboard->inlineKeyboard.push_back(row);

            std::vector<TgBot::InlineKeyboardButton::Ptr> row1;
            for (int i = 7; i < 9; i++)
            {
                TgBot::InlineKeyboardButton::Ptr button(new TgBot::InlineKeyboardButton);
                button->text = "[" + std::to_string(i) + "]";
                button->callbackData = code_menu[kount++];
                row1.push_back(button);
            }
            keyboard->inlineKeyboard.push_back(row1);

            TgBot::InlineKeyboardButton::Ptr button(new TgBot::InlineKeyboardButton);
            button->text = "Exit";
            button->callbackData = code_menu[kount++];
            keyboard->inlineKeyboard.push_back({ button });

            bot.getApi().sendMessage(message->chat->id, str, false, 0, keyboard);
        });

    bot.getEvents().onCommand("button", [&bot](TgBot::Message::Ptr message)
        {
            // Разметка для клавиатуры
            TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);

            //// Кнопка калвиатуры
            //TgBot::InlineKeyboardButton::Ptr button(new TgBot::InlineKeyboardButton);
            //button->text = "1";
            //button->callbackData = "button_clicked";
            //keyboard->inlineKeyboard.push_back({ button });


            // Добавление 12 кнопок в ряд
            std::vector<TgBot::InlineKeyboardButton::Ptr> row;
            for (int i = 1; i <= 12; i++)
            {
                TgBot::InlineKeyboardButton::Ptr button(new TgBot::InlineKeyboardButton);
                button->text = std::to_string(i);
                button->callbackData = std::to_string(i);
                row.push_back(button);
            }

            keyboard->inlineKeyboard.push_back(row);

            bot.getApi().sendMessage(message->chat->id, "Click the button:", false, 0, keyboard);
        });

    bot.getEvents().onCommand("MarSerg", [&bot](TgBot::Message::Ptr message)
        {
            // Вся информация по отгрузкам
            TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
            std::vector<TgBot::InlineKeyboardButton::Ptr> row;

            nlohmann::json str = nlohmann::json::parse(POST_Request("https://api-seller.ozon.ru/v3/posting/fbs/unfulfilled/list", Check_Status_Order(Take_Past_Time(), Take_Future_Time(), false, "delivering")));

            //nlohmann::json test = POST_Request("", Check_Status_Order(Take_Past_Time(), Take_Future_Time(), true, ""));
            //nlohmann::json request = nlohmann::json::parse((std::string)test);

            TgBot::InlineKeyboardButton::Ptr left(new TgBot::InlineKeyboardButton);
            left->text = "<-";
            left->callbackData = "left_mar";
            row.push_back(left);

            TgBot::InlineKeyboardButton::Ptr rigth(new TgBot::InlineKeyboardButton);
            rigth->text = "->";
            rigth->callbackData = "right_mar";
            row.push_back(rigth);
            keyboard->inlineKeyboard.push_back(row);

            bot.getApi().sendMessage(message->chat->id, "str", false, 0, keyboard);
        });

    

    bot.getEvents().onCallbackQuery([&bot](TgBot::CallbackQuery::Ptr query)
        {
            if (query->data == "check")
            {

                bot.getApi().sendMessage(query->message->chat->id, "1"); // POST_Request("", Check_Status_Order(Take_Past_Time(), Take_Future_Time(), true, "delivered")));
                bot.getApi().answerCallbackQuery(query->id);
            }
            if (query->data == "button_clicked")
            {
                bot.getApi().sendMessage(query->message->chat->id, "1"); // POST_Request("", Check_Status_Order(Take_Past_Time(), Take_Future_Time(), true, "delivered")));
                bot.getApi().answerCallbackQuery(query->id);
            }
            if (query->data == "true")
            {
                std::vector<std::string> out_message;
                nlohmann::json test = POST_Request("", Check_Status_Order(Take_Past_Time(), Take_Future_Time(), true, ""));

                nlohmann::json request = nlohmann::json::parse((std::string)test);
                //std::string out;
                //int in = 0;
                //for (int i = 0; i < out_message.size(); i++)
                //{
                //    const char* ptr_char = &out_message[i][0];
                //    out += cp1251_to_utf8(ptr_char);
                //    //std::cout << out << std::endl;
                //    //for (int j = 0; j < out_message[i].size(); j++)
                //    //{
                //    //    // 
                //    //    std::cout << cp1251_to_utf8(ptr_char) << std::endl;
                //    //    std::cin >> in;
                //    //}
                //    out += '\n';
                //    //std::cout << out_message[i] << std::endl;
                //}

                Out_Info(request);
                /*response.push_back("Номер отправления:");
                response.push_back(request["result"]["postings"][0]["posting_number"]);
                response.push_back("Номер акта:");
                response.push_back(request["result"]["postings"][0]["order_number"]);
                response.push_back("Наименование проданного товара:");
                std::string Brainfuck_name = request["result"]["postings"][0]["products"][0]["name"];
                std::cout << Brainfuck_name << std::endl;
                response.push_back("Цена проданного товара:");
                response.push_back(request["result"]["postings"][0]["products"][0]["price"]);
                response.push_back("Дата отгрузки:");
                std::string date = request["result"]["postings"][0]["shipment_date"];
                response.push_back(date.erase(date.length() - 10, 10));*/

                bot.getApi().sendMessage(query->message->chat->id, "Done"); //const char* str

                bot.getApi().answerCallbackQuery(query->id);
            }
            else
            {
                bot.getApi().sendMessage(query->message->chat->id, "Callback: " + query->data);
                bot.getApi().answerCallbackQuery(query->id);
            }
        });

    

}