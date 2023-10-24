/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 10:29:10 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/24 10:44:21 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP
#include "Libs.hpp"

class Client
{
    public:
        Client( void );
        ~Client();
    private:
        int fd;
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
        struct sockaddr_in ClientAddress;
};

#endif