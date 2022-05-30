
#ifndef LIFE_ON_CANVAS_CANVASCONTROLLER_H
#define LIFE_ON_CANVAS_CANVASCONTROLLER_H

#include <QCoreApplication>
#include <QDebug>
#include <QTcpSocket>
#include <QGraphicsScene>
#include <QObject>
#include <QMouseEvent>
#include <QHostAddress>
#include <QGraphicsItemGroup>
#include <QtWebSockets/QWebSocket>
#include <QUrl>

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/strand.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;

#include "serializer.h"


//
//class WebSocketSession : public std::enable_shared_from_this<WebSocketSession> {
//    tcp::resolver resolver_;
//    websocket::stream<beast::tcp_stream> ws_;
//    beast::flat_buffer buffer_;
//    std::string host_;
//    std::string text_;
//
//public:
//    explicit
//    WebSocketSession(net::io_context& ioc)
//    : resolver_(net::make_strand(ioc))
//    , ws_(net::make_strand(ioc))
//    {
//    }
//
//    // Start the asynchronous operation
//    void
//    run(
//            char const* host,
//            char const* port,
//            char const* text)
//    {
//        // Save these for later
//        host_ = host;
//        text_ = text;
//
//        // Look up the domain name
//        resolver_.async_resolve(
//                host,
//                port,
//                beast::bind_front_handler(
//                        &WebSocketSession::on_resolve,
//                        shared_from_this()));
//    }
//
//    void
//    on_resolve(
//            beast::error_code ec,
//            tcp::resolver::results_type results)
//    {
//        if(ec)
//            return fail(ec, "resolve");
//
//        // Set the timeout for the operation
//        beast::get_lowest_layer(ws_).expires_after(std::chrono::seconds(30));
//
//        // Make the connection on the IP address we get from a lookup
//        beast::get_lowest_layer(ws_).async_connect(
//                results,
//                beast::bind_front_handler(
//                        &WebSocketSession::on_connect,
//                        shared_from_this()));
//    }
//
//    void
//    on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type ep)
//    {
//        if(ec)
//            return fail(ec, "connect");
//
//        // Turn off the timeout on the tcp_stream, because
//        // the websocket stream has its own timeout system.
//        beast::get_lowest_layer(ws_).expires_never();
//
//        // Set suggested timeout settings for the websocket
//        ws_.set_option(
//                websocket::stream_base::timeout::suggested(
//                        beast::role_type::client));
//
//        // Set a decorator to change the User-Agent of the handshake
//        ws_.set_option(websocket::stream_base::decorator(
//                [](websocket::request_type& req)
//                {
//                    req.set(http::field::user_agent,
//                            std::string(BOOST_BEAST_VERSION_STRING) +
//                            " websocket-client-async");
//                }));
//
//        // Update the host_ string. This will provide the value of the
//        // Host HTTP header during the WebSocket handshake.
//        // See https://tools.ietf.org/html/rfc7230#section-5.4
//        host_ += ':' + std::to_string(ep.port());
//
//        // Perform the websocket handshake
//        ws_.async_handshake(host_, "/",
//                            beast::bind_front_handler(
//                                    &WebSocketSession::on_handshake,
//                                    shared_from_this()));
//    }
//
//    void
//    on_handshake(beast::error_code ec)
//    {
//        if(ec)
//            return fail(ec, "handshake");
//
//        // Send the message
//        ws_.async_write(
//                net::buffer(text_),
//                beast::bind_front_handler(
//                        &WebSocketSession::on_write,
//                        shared_from_this()));
//    }
//
//    void
//    on_write(
//            beast::error_code ec,
//            std::size_t bytes_transferred)
//    {
//        boost::ignore_unused(bytes_transferred);
//
//        if(ec)
//            return fail(ec, "write");
//
//        // Read a message into our buffer
//        ws_.async_read(
//                buffer_,
//                beast::bind_front_handler(
//                        &WebSocketSession::on_read,
//                        shared_from_this()));
//    }
//
//    void
//    on_read(
//            beast::error_code ec,
//            std::size_t bytes_transferred)
//    {
//        boost::ignore_unused(bytes_transferred);
//
//        if(ec)
//            return fail(ec, "read");
//
//        // Close the WebSocket connection
//        ws_.async_close(websocket::close_code::normal,
//                        beast::bind_front_handler(
//                                &WebSocketSession::on_close,
//                                shared_from_this()));
//    }
//
//    void
//    on_close(beast::error_code ec)
//    {
//        if(ec)
//            return fail(ec, "close");
//
//        // If we get here then the connection is closed gracefully
//
//        // The make_printable() function helps print a ConstBufferSequence
//        std::cout << beast::make_printable(buffer_.data()) << std::endl;
//    }
//};

class CanvasController: public QObject {
    Q_OBJECT
public:
    explicit CanvasController(QGraphicsScene* mainScene);
    ~CanvasController();

private:

    QGraphicsScene* mainScene;
    QTimer* timer;
    QWebSocket* socket;
    const std::vector<GraphicsItem> buffer;

    unsigned int CanvasId;

    QVector<QGraphicsLineItem*> currentFreeLineItems;


    void setTimer(QTimer* timer);
    void sendDiff( const std::vector<GraphicsItem> &diffArr);
    void displayItems(const std::vector<GraphicsItem> &itemsToDisplay);
    std::vector<GraphicsItem> convertQLineItems(const QVector<QGraphicsLineItem*>& lineItems);

public slots:
    void initCanvas();

    //network processing slots
    void sendRegularRequest();
    void onReadyRead();
    void onResponseReceived(const QString &responseStr);

    //free curve draw tracking slots
    void onMousePressedFreeCurve();
    void onMouseMovedFreeCurve(QGraphicsLineItem *lineItem);
    void onMouseReleasedFreeCurve();

    //single line item draw tracking slot
    void onMouseReleasedSingleLine(QGraphicsLineItem* lineItem);

    //ellipse item draw tracking slot
    void onMouseReleasedEllipse(QGraphicsEllipseItem* ellipseItem);

    // rectangle item draw tracking slot
    void onMouseReleasedRectangle(QGraphicsRectItem* rectItem);

signals:

    void responseReceived(QString responseStr);
};

#endif //LIFE_ON_CANVAS_CANVASCONTROLLER_H
