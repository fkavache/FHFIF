#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include <boost/json.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <nlohmann/json.hpp>

#include <functional>
#include <iostream>
#include <string>

#include "controller/Controller.h"
#include "api/APIHandlers.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;
using json = nlohmann::json;

using namespace std;

typedef pair<SStatus, string> (*GetHandler)(const string&, http::request<http::string_body>& request);
typedef pair<SStatus, string> (*PostHandler)(const string&, http::request<http::string_body>& request);
typedef pair<SStatus, string> (*PutHandler)(const string&, http::request<http::string_body>& request);
typedef pair<SStatus, string> (*DeleteHandler)(const string&, http::request<http::string_body>& request);

typedef unordered_map<string, pair<ControllerHandler, bool>> ControllerMap;

typedef http::request<http::string_body> Request;
typedef http::response<http::string_body> Response;

class APIServer {
public:
    APIServer() = delete;

    static void run(const string& host, unsigned short port);

private:
    static pair<SStatus, string> getHandler(const string& target, http::request<http::string_body>& request);
    static pair<SStatus, string> postHandler(const string& target, http::request<http::string_body>& request);
    static pair<SStatus, string> putHandler(const string& target, http::request<http::string_body>& request);
    static pair<SStatus, string> deleteHandler(const string& target, http::request<http::string_body>& request);

    static pair<SStatus, string> controllerHandler(const string &target, Request& request, ControllerMap& controllerHandlers);
    static void server(tcp::acceptor& acceptor, tcp::socket& socket);
};