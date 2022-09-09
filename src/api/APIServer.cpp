#include "api/APIServer.h"
#include "utils/Keys.h"
#include "utils/Log.h"

#define APISERVER_UNIT "APISERVER"

#define API_REGISTER_USER      "/register_user"         // POST
#define API_LOGIN_USER         "/login_user"            // POST
#define API_FETCH_TEAM         "/fetch_home"            // GET
#define API_FETCH_PLAYERS      "/fetch_characters"      // GET
#define API_UPDATE_TEAM        "/update_home"           // PUT
#define API_UPDATE_PLAYER      "/update_character"      // PUT
#define API_PLAYER_TO_TRANSFER "/character_to_transfer" // POST
#define API_FETCH_TRANSFERS    "/fetch_transfers"       // GET
#define API_TRANSFER_PLAYER    "/transfer_character"    // PUT

// PATH - <HANDLER, TOKEN VALIDATION>
ControllerMap postControllers {
        {API_REGISTER_USER,      {APIHandlers::registerUser,        false}},
        {API_LOGIN_USER,         {APIHandlers::loginUser,           false}},
        {API_PLAYER_TO_TRANSFER, {APIHandlers::characterToTransfer, true}}
};

ControllerMap getControllers {
        {API_FETCH_TEAM,      {APIHandlers::fetchHome,       true}},
        {API_FETCH_PLAYERS,   {APIHandlers::fetchCharacters, true}},
        {API_FETCH_TRANSFERS, {APIHandlers::fetchTransfers,  true}}
};

ControllerMap putControllers {
        {API_UPDATE_TEAM,     {APIHandlers::updateHome,        true}},
        {API_UPDATE_PLAYER,   {APIHandlers::updateCharacter,   true}},
        {API_TRANSFER_PLAYER, {APIHandlers::transferCharacter, true}}
};

ControllerMap deleteControllers {};

class http_connection : public enable_shared_from_this<http_connection> {
public:
    explicit http_connection(tcp::socket socket,
                             GetHandler getHandler,
                             PostHandler postHandler,
                             PutHandler putHandler,
                             DeleteHandler deleteHandler):

            socket_(std::move(socket)),
            getHandler(getHandler),
            postHandler(postHandler),
            putHandler(putHandler),
            deleteHandler(deleteHandler) {}

    void start() {
        read_request();
    }

private:
    tcp::socket socket_;
    beast::flat_buffer buffer_{8192};
    Request request_;
    Response response_;

    GetHandler getHandler;
    PostHandler postHandler;
    PutHandler putHandler;
    DeleteHandler deleteHandler;

    void read_request() {
        auto self = shared_from_this();

        http::async_read(socket_, buffer_, request_,
                         [self](beast::error_code ec, size_t bytes_transferred) {
                             boost::ignore_unused(bytes_transferred);
                             if(!ec) {
                                 self->process_request();
                             }
                         });
    }

    void process_request() {
        response_.version(request_.version());
        response_.keep_alive(false);
        pair<SStatus, string> result;

        switch(request_.method()) {
            case http::verb::get: {
                result = getHandler(request_.target().to_string(), request_);
            } break;

            case http::verb::post: {
                result = postHandler(request_.target().to_string(), request_);
            } break;

            case http::verb::put: {
                result = putHandler(request_.target().to_string(), request_);
            } break;

            case http::verb::delete_: {
                result = deleteHandler(request_.target().to_string(), request_);
            } break;

            default: break;
        }

        response_.result(result.first);
        response_.body() = result.second;

        write_response();
    }

    void write_response() {
        auto self = shared_from_this();

        response_.content_length(response_.body().size());

        http::async_write(socket_, response_,
                          [self](beast::error_code ec, size_t) {
                              self->socket_.shutdown(tcp::socket::shutdown_send, ec);
                          });
    }
};

// HTTP Handlers ===============================
// =============================================

pair<SStatus, string> APIServer::controllerHandler(const string &target, Request& request, ControllerMap& controllerHandlers) {
    Log::LOG_INFO(APISERVER_UNIT, target);
    try {
        auto data = json::parse(request.body());

        if (controllerHandlers.find(target) != controllerHandlers.end()) {
            auto value = controllerHandlers[target];

            if (value.second) {
                string email;
                string token{request[KEY_TOKEN]};

                if (!Controller::isAuthorized(token, email)) return { S_AUTH_ERROR, "" };

                data[KEY_EMAIL] = email;
            }

            return value.first(target, data);
        }

        return { S_ERROR, "" };
    } catch(exception& ex) {
        Log::LOG_ERROR(APISERVER_UNIT, ex.what());
        return { S_ERROR, "" };
    }
}

pair<SStatus, string> APIServer::getHandler(const string &target, Request& request) {
    return controllerHandler(target, request, getControllers);
}

pair<SStatus, string> APIServer::postHandler(const string& target, Request& request) {
    return controllerHandler(target, request, postControllers);
}

pair<SStatus, string>  APIServer::putHandler(const string& target, Request& request) {
    return controllerHandler(target, request, putControllers);
}

pair<SStatus, string>  APIServer::deleteHandler(const string &target, Request& request) {
    return controllerHandler(target, request, deleteControllers);
}

// =============================================
// =============================================

void APIServer::server(tcp::acceptor &acceptor, tcp::socket &socket) {
    acceptor.async_accept(socket,
                          [&](beast::error_code ec) {
                              if (!ec) {
                                  make_shared<http_connection>(std::move(socket),
                                                               &APIServer::getHandler,
                                                               &APIServer::postHandler,
                                                               &APIServer::putHandler,
                                                               &APIServer::deleteHandler)->start();
                              }

                              server(acceptor, socket);
                          });

}

void APIServer::run(const string& host, unsigned short port) {
    auto const address = net::ip::make_address(host);

    net::io_context ioc;

    tcp::acceptor acceptor{ioc, {address, port}};
    tcp::socket socket{ioc};
    server(acceptor, socket);

    ioc.run();
}
