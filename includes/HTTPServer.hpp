/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:44:02 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/02 18:09:29 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPSERVER_HPP
#define HTTPSERVER_HPP
#include "Lib.hpp"
#include "HTTPRequestParser.hpp"

class HTTPServer
{
    public:
        HTTPServer(int domain, int type, int protocol);
        ~HTTPServer();
    public: //interface
        HTTPRequestParser httpReq;
    public:
        void bindServer(std::string const &ip, int port);
        void startListening(int backlog);
    private:
        struct sockaddr_in remoteAddr;
        int domain;
        int type;
        int protocol;
        int sock;
        int binding;
        int newSock;
        int backlog;
};

#endif