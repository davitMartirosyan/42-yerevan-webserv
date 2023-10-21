/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 23:56:30 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/21 11:35:24 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPSERVER_HPP
#define HTTPSERVER_HPP
#include "Libs.hpp"
#include "../Location/Location.hpp"

class HTTPServer : public http_core_module_conf_t
{
    public:
        HTTPServer(int sock);
        ~HTTPServer();
    public:
        int getServerSocket( void );
    private:
        int fd;
        int backlog;
    private:
        // std::map<int, Client> clnt;              [Clients]
        std::map<std::string, Location> locations; // <path, LocationDirective>
    private:
        struct addrinfo address_info;
        struct sockaddr_in socket_info;
        struct sockaddr socket_address;
    private:
        
};

#endif