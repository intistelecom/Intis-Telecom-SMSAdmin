#include <iostream>
#include <libxml++/libxml++.h>
#include <curl/curl.h>
#include <sms16xapi/constants.h>

using namespace std;
using namespace Glib;
using namespace xmlpp;

///объявляем буфер, для хранения возможной ошибки, размер определяется в самой библиотеке
static char errorBuffer[CURL_ERROR_SIZE];
///объялвяем буфер принимаемых данных
static ustring buffer;
static int writer(char *data, size_t size, size_t nmemb, ustring *buffer);
CURLcode send_xml_request();

int main()
{
    cout << sms16xapi::SMS_URL << endl;
    CURLcode result2;
    result2 = send_xml_request();

    /// проверяем успешность выполнения операции
    if (result2 == CURLE_OK)
    {
        /// выводим полученные данные на стандартный вывод (консоль)
        cout << buffer << "\n";

        /// Parse the file
        DomParser parser;
        parser.parse_memory(buffer);
        Node* rootNode = parser.get_document()->get_root_node();

        /// Xpath query
        NodeSet result = rootNode->find("/response/error");

        /// Get first node from result
        Node *firstNodeInResult = result.at(0);
        Element *el = dynamic_cast<Element*>(firstNodeInResult);
        // Cast to Attribute node (dynamic_cast on reference can throw [fail fast])
        // Attribute &attribute = dynamic_cast<Attribute&>(*firstNodeInResult);

        /// Get value of the attribute
        // ustring attributeValue = attribute.get_value();
        ustring attributeValue = el->get_child_text()->get_content();

        /// Print attribute value
        cout << attributeValue << endl;

    } else {
        ///выводим сообщение об ошибке
        cout << "Ошибка! " << errorBuffer << endl;
    }

    return 0;
}

CURLcode send_xml_request()
{
    /// необходимые CURL объекты
    CURL *curl;
    CURLcode result;
    /// инициализируем curl
    curl = curl_easy_init();
    /// проверяем результат инициализации
    if (curl)
    {
        ///задаем все необходимые опции
        ///определяем, куда выводить ошибки
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
        ///задаем опцию - получить страницу по адресу http://google.com
        curl_easy_setopt(curl, CURLOPT_URL, sms16xapi::SMS_URL.c_str());
        ///задаем опцию отображение заголовка страницы
        curl_easy_setopt(curl, CURLOPT_HEADER, 0);
        //curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        ///указываем функцию обратного вызова для записи получаемых данных
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
        ///указываем куда записывать принимаемые данные
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        ///запускаем выполнение задачи
        result = curl_easy_perform(curl);
    }
    ///завершаем сессию
    curl_easy_cleanup(curl);
    return result;
}

///функция обратного вызова
static int writer(char *data, size_t size, size_t nmemb, ustring *buffer)
{
    ///переменная - результат, по умолчанию нулевая
    int result = 0;
    ///проверяем буфер
    if (buffer != NULL)
    {
        ///добавляем к буферу строки из data, в количестве nmemb
        buffer->append(data, size * nmemb);
        ///вычисляем объем принятых данных
        result = size * nmemb;
    }
    ///вовзращаем результат
    return result;
}

