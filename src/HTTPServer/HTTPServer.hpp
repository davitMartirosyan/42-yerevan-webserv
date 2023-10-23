/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 23:56:30 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/22 23:49:12 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPSERVER_HPP
#define HTTPSERVER_HPP
#include "Libs.hpp"
#include "../Location/Location.hpp"

class HTTPServer : public IListener, public http_core_module_conf
{
    public:
        HTTPServer(std::string const &ip, std::string const &port);
        ~HTTPServer();
        int getServerSocket( void );
    public: //ip port interface
        virtual void setListenerIpPort(std::string const &ip, std::string const &port);
        virtual std::string const &getIp( void ) const;
        virtual std::string const &getPort( void ) const;
    private:
        int fd;
        int backlog;
    private:
        std::vector<std::string> server_name;
    private:
        // std::map<int, Client> clnt;              [Clients]
        std::map<std::string, Location> locations; // <prefix, LocationDirective>
    private:
        struct addrinfo address_info;
        struct sockaddr_in socket_info;
        struct sockaddr socket_address;
    private:
        
};

#endif