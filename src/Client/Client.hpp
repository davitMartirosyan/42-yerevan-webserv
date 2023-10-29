/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 10:29:10 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/29 15:27:46 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP
#include "Libs.hpp"

class Client
{
    public:
        Client(sock_t clfd);
        ~Client();
    public:
        sock_t getFd( void ) const;
    private:
        sock_t fd;
        const char* http;
    private:
        std::string httpRequest;
        std::string requestLine;
        std::string body;
    private:
        std::map<std::string, std::string> httpHeaders;
    private:
        unsigned long int bodySize;
    private:
        struct sockaddr_in ClientInfo;
        struct sockaddr ClientAddress;
        struct sockaddr_storage addressStorage;
};

#endif